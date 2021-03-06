# Copyright (C) 2008 The Android Open Source Project


- Description -
---------------

Layoutlib_create generates a JAR library used by the Android Studio graphical layout editors to perform
layout and rendering.


- Usage -
---------

 ./layoutlib_create destination.jar path/to/android1.jar path/to/android2.jar


- Design Overview -
-------------------

Layoutlib_create uses a few jars from the framework containing the Java code used by Android as
generated by the Android build, right before the classes are converted to a DEX format.

These jars can't be used directly in Android Studio as:
- they contains references to native code (which we cannot support in Android Studio at the moment, but working on it),
- some classes need to be overridden, for example all the drawing code that is replaced by Java 2D
  calls.
- some of the classes that need to be changed are final and/or we need access to their private
  internal state.

Consequently this tool:
- parses the input JAR,
- modifies some of the classes directly using some bytecode manipulation,
- filters some packages and removes those we don't want in the output JAR,
- injects some new classes,
- generates a modified JAR file that is suitable for the Android Studio to perform
  rendering.

The ASM library is used to do the bytecode modification using its visitor pattern API.

The layoutlib_create is *NOT* generic. There is no configuration file. Instead all the configuration
is done in the main() method and the CreateInfo structure is expected to change with the Android
platform as new classes are added, changed or removed. See src/com/android/tools/layoutlib/create/CreateInfo.java
for more details. Some configuration that may be platform dependent is also present elsewhere in code.

The resulting JAR is used by layoutlib_bridge (a.k.a. "the bridge"), also part of the platform, that
provides all the necessary missing implementation for rendering graphics in Android Studio.



- Implementation Notes -
------------------------

The tool works in two phases:
- first analyze the input jar (AsmAnalyzer class)
- then generate the output jar (AsmGenerator class),


- Analyzer
----------

The goal of the analyzer is to create a graph of all the classes from the input JAR with their
dependencies and then only keep the ones we want.

To do that, the analyzer is created with a list of base classes to keep -- everything that derives
from these is kept. Currently the one such class is android.view.View: since we want to render
layouts, anything that is sort of a view needs to be kept.

The analyzer is also given a list of class names to keep in the output. This is done using
shell-like glob patterns that filter on the fully-qualified class names, for example "android.*.R**"
("*" does not match dots whilst "**" does, and "." and "$" are interpreted as-is). In practice we
almost but not quite request the inclusion of full packages.

The analyzer is also given a list of classes to exclude. A fake implementation of these classes is
injected by the Generator.

With this information, the analyzer parses the input zip to find all the classes. All classes
deriving from the requested base classes are kept. All classes whose name match the glob pattern
are kept. The analysis then finds all the dependencies of the classes that are to be kept using an
ASM visitor on the class, the field types, the method types and annotations types. Classes that
belong to the current JRE are excluded.

The output of the analyzer is a set of ASM ClassReader instances which are then fed to the
generator.


- Generator
-----------

The generator is constructed from a CreateInfo struct that acts as a config file and lists:
- the classes to inject in the output JAR -- these classes are directly implemented in
  layoutlib_create and will be used to interface with the Java 2D renderer.
- specific methods to override (see method stubs details below).
- specific methods for which to delegate calls.
- specific methods to remove based on their return type.
- specific classes to rename.
- specific classes to refactor.

Each of these are specific strategies we use to be able to modify the Android code to fit within the
Java 2D renderer. These strategies are explained below.

The core method of the generator is transform(): it takes an input ASM ClassReader and modifies it
to produce a byte array suitable for the final JAR file.

The first step of the transformation is to implement the method delegates.

The TransformClassAdapter is then used to process the potentially renamed class.  All protected or
private classes are marked as public. All classes are made non-final. Interfaces are left as-is.

If a method has a return type that must be erased, the whole method is skipped.  Methods are also
changed from protected/private to public. The code of the methods is then kept as-is, except for
native methods which are replaced by a stub. Methods that are to be overridden are also replaced by
a stub.

Finally fields are also visited and changed from protected/private to public.

The next step of the transformation is changing the name of the class in case we requested the class
to be renamed. This uses the RenameClassAdapter to also rename all inner classes and references in
methods and types. Note that other classes are not transformed and keep referencing the original
name.

The class is then fed to RefactorClassAdapter which is like RenameClassAdapter but updates the
references in all classes. This is used to update the references of classes in the java package that
were added in the Dalvik VM but are not a part of the Desktop VM. The existing classes are
modified to update all references to these non-desktop classes. An alternate implementation of
these (com.android.tools.layoutlib.java.*) is injected.

ReplaceMethodCallsAdapter replaces calls to certain methods. This is different from the
DelegateMethodAdapter since it doesn't preserve the original copy of the method and more importantly
changes the calls to a method in each class instead of changing the implementation of the method.
This is useful for methods in the Java namespace where we cannot add delegates. The configuration
for this is not done through the CreateInfo class, but done in the ReplaceMethodAdapter.

The ClassAdapters are chained together to achieve the desired output. (Look at section 2.2.7
Transformation chains in the asm user guide, link in the References.) The order of execution of
these is:
ClassReader -> [DelegateClassAdapter] -> TransformClassAdapter -> [RenameClassAdapter] ->
RefactorClassAdapter -> [ReplaceMethodCallsAdapter] -> ClassWriter

- Method stubs
--------------

As indicated above, all native and overridden methods are replaced by a stub.  We don't have the
code to replace with in layoutlib_create. Instead the StubCallMethodAdapter replaces the code of the
method by a call to OverrideMethod.invokeX(). When using the final JAR, the bridge can register
listeners from these overridden method calls based on the method signatures.

The listeners are currently pretty basic: we only pass the signature of the method being called, its
caller object and a flag indicating whether the method was native. We do not currently provide the
parameters. The listener can however specify the return value of the overridden method.

This strategy is now obsolete and replaced by the method delegates.


- Strategies
------------

We currently have 6 strategies to deal with overriding the rendering code and make it run in
Android Studio. Most of these strategies are implemented hand-in-hand by the bridge (which runs in Android Studio)
and the generator.


1- Class Injection

This is the easiest: we currently inject the following classes:
- OverrideMethod and its associated MethodListener and MethodAdapter are used to intercept calls to
  some specific methods that are stubbed out and change their return value.
- CreateInfo class, which configured the generator. Not used yet, but could in theory help us track
  what the generator changed.
- AutoCloseable and Objects are part of Java 7. To enable us to still run on Java 6, new classes are
  injected. The implementation for these classes has been taken from Android's libcore
  (platform/libcore/luni/src/main/java/java/...).
- Charsets, IntegralToString and UnsafeByteSequence are not part of the Desktop VM. They are
  added to the Dalvik VM for performance reasons. An implementation that is very close to the
  original (which is at platform/libcore/luni/src/main/java/...) is injected. Since these classees
  were in part of the java package, where we can't inject classes, all references to these have been
  updated (See strategy 4- Refactoring Classes).


2- Overriding methods

As explained earlier, the creator doesn't have any replacement code for methods to override. Instead
it removes the original code and replaces it by a call to a specific OveriddeMethod.invokeX(). The
bridge then registers a listener on the method signature and can provide an implementation.

This strategy is now obsolete and replaced by the method delegates (See strategy 6- Method
Delegates).


3- Renaming classes

This simply changes the name of a class in its definition, as well as all its references in internal
inner classes and methods. Calls from other classes are not modified -- they keep referencing the
original class name. This allows the bridge to literally replace an implementation.

An example will make this easier: android.graphics.Paint is the main drawing class that we need to
replace. To do so, the generator renames Paint to _original_Paint. Later the bridge provides its own
replacement version of Paint which will be used by the rest of the Android stack. The replacement
version of Paint can still use (either by inheritance or delegation) all the original non-native
code of _original_Paint if it so desires.

Some of the Android classes are basically wrappers over native objects and since we don't have the
native code in Android Studio, we need to provide a full alternate implementation. Sub-classing doesn't
work as some native methods are static and we don't control object creation.

This won't rename/replace the inner static methods of a given class.


4- Refactoring classes

This is very similar to the Renaming classes except that it also updates the reference in all
classes. This is done for classes which are added to the Dalvik VM for performance reasons but are
not present in the Desktop VM. An implementation for these classes is also injected.


5- Method erasure based on return type

This is mostly an implementation detail of the bridge: in the Paint class mentioned above, some
inner static classes are used to pass around attributes (e.g. FontMetrics, or the Style enum) and
all the original implementation is native.

In this case we have a strategy that tells the generator that anything returning, for example, the
inner class Paint$Style in the Paint class should be discarded and the bridge will provide its own
implementation.


6- Method Delegates

This strategy is used to override method implementations. Given a method SomeClass.MethodName(), 1
or 2 methods are generated:
a- A copy of the original method named SomeClass.MethodName_Original(). The content is the original
method as-is from the reader. This step is omitted if the method is native, since it has no Java
implementation.
b- A brand new implementation of SomeClass.MethodName() which calls to a non-existing static method
named SomeClass_Delegate.MethodName(). The implementation of this 'delegate' method is done in
layoutlib_bridge.

The delegate method is a static method. If the original method is non-static, the delegate method
receives the original 'this' as its first argument. If the original method is an inner non-static
method, it also receives the inner 'this' as the second argument.



- References -
--------------


The JVM Specification 2nd edition:
  http://java.sun.com/docs/books/jvms/second_edition/html/VMSpecTOC.doc.html

Understanding bytecode:
  http://www.ibm.com/developerworks/ibm/library/it-haggar_bytecode/

Bytecode opcode list:
  http://en.wikipedia.org/wiki/Java_bytecode_instruction_listings

ASM user guide:
  http://download.forge.objectweb.org/asm/asm4-guide.pdf


--
end
