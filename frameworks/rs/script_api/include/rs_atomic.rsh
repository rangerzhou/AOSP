/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Don't edit this file!  It is auto-generated by frameworks/rs/api/generate.sh.

/*
 * rs_atomic.rsh: Atomic Update Functions
 *
 * To update values shared between multiple threads, use the functions below.
 * They ensure that the values are atomically updated, i.e. that the memory
 * reads, the updates, and the memory writes are done in the right order.
 *
 * These functions are slower than their non-atomic equivalents, so use
 * them only when synchronization is needed.
 *
 * Note that in RenderScript, your code is likely to be running in separate
 * threads even though you did not explicitely create them.  The RenderScript
 * runtime will very often split the execution of one kernel across multiple
 * threads.  Updating globals should be done with atomic functions.  If possible,
 * modify your algorithm to avoid them altogether.
 */

#ifndef RENDERSCRIPT_RS_ATOMIC_RSH
#define RENDERSCRIPT_RS_ATOMIC_RSH

/*
 * rsAtomicAdd: Thread-safe addition
 *
 * Atomicly adds a value to the value at addr, i.e. *addr += value.
 *
 * Parameters:
 *   addr: Address of the value to modify.
 *   value: Amount to add.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicAdd(volatile int32_t* addr, int32_t value);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 20))
extern int32_t __attribute__((overloadable))
    rsAtomicAdd(volatile uint32_t* addr, uint32_t value);
#endif

/*
 * rsAtomicAnd: Thread-safe bitwise and
 *
 * Atomicly performs a bitwise and of two values, storing the result back at addr,
 * i.e. *addr &= value.
 *
 * Parameters:
 *   addr: Address of the value to modify.
 *   value: Value to and with.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicAnd(volatile int32_t* addr, int32_t value);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 20))
extern int32_t __attribute__((overloadable))
    rsAtomicAnd(volatile uint32_t* addr, uint32_t value);
#endif

/*
 * rsAtomicCas: Thread-safe compare and set
 *
 * If the value at addr matches compareValue then the newValue is written at addr,
 * i.e. if (*addr == compareValue) { *addr = newValue; }.
 *
 * You can check that the value was written by checking that the value returned
 * by rsAtomicCas() is compareValue.
 *
 * Parameters:
 *   addr: Address of the value to compare and replace if the test passes.
 *   compareValue: Value to test *addr against.
 *   newValue: Value to write if the test passes.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicCas(volatile int32_t* addr, int32_t compareValue, int32_t newValue);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern uint32_t __attribute__((overloadable))
    rsAtomicCas(volatile uint32_t* addr, uint32_t compareValue, uint32_t newValue);
#endif

/*
 * rsAtomicDec: Thread-safe decrement
 *
 * Atomicly subtracts one from the value at addr.  This is equivalent to rsAtomicSub(addr, 1).
 *
 * Parameters:
 *   addr: Address of the value to decrement.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicDec(volatile int32_t* addr);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 20))
extern int32_t __attribute__((overloadable))
    rsAtomicDec(volatile uint32_t* addr);
#endif

/*
 * rsAtomicInc: Thread-safe increment
 *
 * Atomicly adds one to the value at addr.  This is equivalent to rsAtomicAdd(addr, 1).
 *
 * Parameters:
 *   addr: Address of the value to increment.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicInc(volatile int32_t* addr);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 20))
extern int32_t __attribute__((overloadable))
    rsAtomicInc(volatile uint32_t* addr);
#endif

/*
 * rsAtomicMax: Thread-safe maximum
 *
 * Atomicly sets the value at addr to the maximum of *addr and value, i.e.
 * *addr = max(*addr, value).
 *
 * Parameters:
 *   addr: Address of the value to modify.
 *   value: Comparison value.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern uint32_t __attribute__((overloadable))
    rsAtomicMax(volatile uint32_t* addr, uint32_t value);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicMax(volatile int32_t* addr, int32_t value);
#endif

/*
 * rsAtomicMin: Thread-safe minimum
 *
 * Atomicly sets the value at addr to the minimum of *addr and value, i.e.
 * *addr = min(*addr, value).
 *
 * Parameters:
 *   addr: Address of the value to modify.
 *   value: Comparison value.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern uint32_t __attribute__((overloadable))
    rsAtomicMin(volatile uint32_t* addr, uint32_t value);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicMin(volatile int32_t* addr, int32_t value);
#endif

/*
 * rsAtomicOr: Thread-safe bitwise or
 *
 * Atomicly perform a bitwise or two values, storing the result at addr,
 * i.e. *addr |= value.
 *
 * Parameters:
 *   addr: Address of the value to modify.
 *   value: Value to or with.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicOr(volatile int32_t* addr, int32_t value);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 20))
extern int32_t __attribute__((overloadable))
    rsAtomicOr(volatile uint32_t* addr, uint32_t value);
#endif

/*
 * rsAtomicSub: Thread-safe subtraction
 *
 * Atomicly subtracts a value from the value at addr, i.e. *addr -= value.
 *
 * Parameters:
 *   addr: Address of the value to modify.
 *   value: Amount to subtract.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicSub(volatile int32_t* addr, int32_t value);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 20))
extern int32_t __attribute__((overloadable))
    rsAtomicSub(volatile uint32_t* addr, uint32_t value);
#endif

/*
 * rsAtomicXor: Thread-safe bitwise exclusive or
 *
 * Atomicly performs a bitwise xor of two values, storing the result at addr,
 * i.e. *addr ^= value.
 *
 * Parameters:
 *   addr: Address of the value to modify.
 *   value: Value to xor with.
 *
 * Returns: Value of *addr prior to the operation.
 */
#if (defined(RS_VERSION) && (RS_VERSION >= 14))
extern int32_t __attribute__((overloadable))
    rsAtomicXor(volatile int32_t* addr, int32_t value);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 20))
extern int32_t __attribute__((overloadable))
    rsAtomicXor(volatile uint32_t* addr, uint32_t value);
#endif

#endif // RENDERSCRIPT_RS_ATOMIC_RSH
