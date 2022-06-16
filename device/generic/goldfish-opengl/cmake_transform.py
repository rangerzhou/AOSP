#!/bin/python
import argparse
import hashlib
import json
import logging
import os
import sys


def cleanup_json(data):
    """Cleans up the json structure by removing empty "", and empty key value
    pairs."""
    if (isinstance(data, unicode)):
        copy = data.strip()
        return None if len(copy) == 0 else copy

    if (isinstance(data, dict)):
        copy = {}
        for key, value in data.iteritems():
            rem = cleanup_json(value)
            if (rem is not None):
                copy[key] = rem
        return None if len(copy) == 0 else copy

    if (isinstance(data, list)):
        copy = []
        for elem in data:
            rem = cleanup_json(elem)
            if (rem is not None):
                if rem not in copy:
                    copy.append(rem)

        if len(copy) == 0:
            return None
        return copy


class AttrDict(dict):
    def __init__(self, *args, **kwargs):
        super(AttrDict, self).__init__(*args, **kwargs)
        self.__dict__ = self

    def as_list(self, name):
        v = self.get(name, [])
        if (isinstance(v, list)):
            return v

        return [v]


def remove_lib_prefix(module):
    """Removes the lib prefix, as we are not using them in CMake."""
    if module.startswith('lib'):
        return module[3:]
    else:
        return module


def escape(msg):
    """Escapes the "."""
    return '"' + msg.replace('"', '\\"') + '"'


def header():
    """The auto generate header."""
    return [
        '# This is an autogenerated file! Do not edit!',
        '# instead run make from .../device/generic/goldfish-opengl',
        '# which will re-generate this file.'
    ]


def checksum(fname):
    """Calculates a SHA256 digest of the given file name."""
    m = hashlib.sha256()
    with open(fname, 'r') as mk:
        m.update(mk.read())
    return m.hexdigest()


def generate_module(module):
    """Generates a cmake module."""
    name = remove_lib_prefix(module['module'])
    make = header()
    mkfile = os.path.join(module['path'], 'Android.mk')
    sha256 = checksum(mkfile)
    make.append(
        'android_validate_sha256("${GOLDFISH_DEVICE_ROOT}/%s" "%s")' % (mkfile, sha256))
    make.append('set(%s_src %s)' % (name, ' '.join(module['src'])))
    if module['type'] == 'SHARED_LIBRARY':
        make.append('android_add_library(TARGET {} SHARED LICENSE Apache-2.0 SRC {})'.format(name, ' '.join(module['src'])))
    elif module['type'] == 'STATIC_LIBRARY':
        make.append('android_add_library(TARGET {} LICENSE Apache-2.0 SRC {})'.format(name, ' '.join(module['src'])))
    else:
        raise ValueError('Unexpected module type: %s' % module['type'])

    # Fix up the includes.
    includes = ['${GOLDFISH_DEVICE_ROOT}/' + s for s in module['includes']]
    make.append('target_include_directories(%s PRIVATE %s)' %
                (name, ' '.join(includes)))

    # filter out definitions
    defs = [escape(d) for d in module['cflags'] if d.startswith('-D')]

    #  And the remaining flags.
    flags = [escape(d) for d in module['cflags'] if not d.startswith('-D')]

    # Make sure we remove the lib prefix from all our dependencies.
    libs = [remove_lib_prefix(l) for l in module.get('libs', [])]
    staticlibs = [remove_lib_prefix(l) for l in
                      module.get('staticlibs', [])
                      if l != "libandroidemu"]

    # Configure the target.
    make.append('target_compile_definitions(%s PRIVATE %s)' %
                (name, ' '.join(defs)))
    make.append('target_compile_options(%s PRIVATE %s)' %
                (name, ' '.join(flags)))

    if len(staticlibs) > 0:
        make.append('target_link_libraries(%s PRIVATE %s PRIVATE %s)' %
                    (name, ' '.join(libs), " ".join(staticlibs)))
    else:
        make.append('target_link_libraries(%s PRIVATE %s)' %
                    (name, ' '.join(libs)))
    return make


def main(argv=None):
    parser = argparse.ArgumentParser(
        description='Generates a set of cmake files'
        'based up the js representation.'
        'Use this to generate cmake files that can be consumed by the emulator build')
    parser.add_argument('-i', '--input', dest='input', type=str, required=True,
                        help='json file containing the build tree')
    parser.add_argument('-v', '--verbose',
                        action='store_const', dest='loglevel',
                        const=logging.INFO, default=logging.ERROR,
                        help='Log what is happening')
    parser.add_argument('-o', '--output',
                        dest='outdir', type=str, default=None,
                        help='Output directory for create CMakefile.txt')
    parser.add_argument('-c', '--clean', dest='output', type=str,
                        default=None,
                        help='Write out the cleaned up js')
    args = parser.parse_args()

    logging.basicConfig(level=args.loglevel)

    with open(args.input) as data_file:
        data = json.load(data_file)

    modules = cleanup_json(data)

    # Write out cleaned up json, mainly useful for debugging etc.
    if (args.output is not None):
        with open(args.output, 'w') as out_file:
            out_file.write(json.dumps(modules, indent=2))

    # Location --> CMakeLists.txt
    cmake = {}

    # The root, it will basically just include all the generated files.
    root = os.path.join(args.outdir, 'CMakeLists.txt')
    mkfile = os.path.join(args.outdir, 'Android.mk')
    sha256 = checksum(mkfile)
    cmake[root] = header()
    cmake[root].append('set(GOLDFISH_DEVICE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})')
    cmake[root].append(
        'android_validate_sha256("${GOLDFISH_DEVICE_ROOT}/%s" "%s")' % (mkfile, sha256))

    # Generate the modules.
    for module in modules:
        location = os.path.join(args.outdir, module['path'], 'CMakeLists.txt')

        # Make sure we handle the case where we have >2 modules in the same dir.
        if location not in cmake:
            cmake[root].append('add_subdirectory(%s)' % module['path'])
            cmake[location] = []
        cmake[location].extend(generate_module(module))

    # Write them to disk.
    for (loc, cmklist) in cmake.iteritems():
        logging.info('Writing to %s', loc)
        with open(loc, 'w') as fn:
            fn.write('\n'.join(cmklist))


if __name__ == '__main__':
    sys.exit(main())