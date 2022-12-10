# Chess Clock

A step by step *Flipped Classroom Exercise* to preparare for an
*Advanced C++ Training*.

## Overview of Steps

On the basis on a code example which is a mix of more or less
"Classic Procedural" design mixed with "Modern C++" (post C++98)
language features.

---

1. Review code and split single source file into more manageable
   modules (`*.cpp` and `*.h` files):

   * start with the source code in folder `Step-00`
   * result (for comparison) is in folder `Step-01`

---

2. Turn a classic `enum` into an `enum class` (aka "scoped" or
   "type safe" enumeration as introduced with C++11):

   * start with the source code in folder `Step-01`
   * result (for comparison) is in folder `Step-02`

---

3. Replace an ordinary function (creating some output) with
   `operator<<`:

   * start with the source code in folder `Step-01` (or `Step-02`)
   * result (for comparison) is in folder `Step-03`

---

4. Some aspects of correctly handling character strings on heap
   memory (from not at all, to do it all manually, to using a
   smart pointer):

   * start with the source code in folder `Step-03`
   * result (for comparison) is in folder `Step-04` (only the
     smart pointer version based on `std::unique_ptr<char[]>`)

---

5. Replacing a `struct` with a `class` and handling access
   protection of private data members with adequate public query
   and modifier member function:

   * start with the source code in folder `Step-03` (or `Step-04`)
   * result (for comparison) is in folder `Step-05`

---

6. Adding some more operator member functions as (for now just as
   aliases for existing query and modifier member functions):

   * start with the source code in folder `Step-05`
   * result (for comparison) is in folder `Step-06`

---

7. Remove the classic query and modifier member functions, leaving
   only the operator versions, and make `value_type` configurable
   via a template argument:

   * start with the source code in folder `Step-06`
   * result (for comparison) is in folder `Step-07`

---

8. Wrap the builtin arithmetic type used for the data member
   `count_` in a small class of its own, with a type conversion
   to the basic type's reference type and an `operator<<`:

   * start with the source code in folder `Step-07`
   * result (for comparison) is in folder `Step-08`

---
