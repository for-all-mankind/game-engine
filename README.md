# IceEngine

A game engine written in C++ with it's own custom scripting language.

## Dependencies
The libraries that this engine uses are:
* [GLFW3](http://www.glfw.org/)
* [GLEW](http://glew.sourceforge.net/)
* OpenGL


## IceScript

IceScript is a custom programming language used by IceEngine for configuration
and modding.

This guide will give a brief overview of the constructs in IceScript.

* [Variables and Constants](#variables-and-constants)
* [Basic Types](#basic-types)
* [Printing](#printing)
* [Comments](#comments)
* [Pointers](#pointers)
* [Numeric Literals](#numeric-literals)
* [If Statements](#if-statements)
* [Loops](#loops)
* [Functions](#functions)
* [Structs](#structs)
* [Enums](#enums)
* [Classes](#classes)
* [Objects](#objects)
* [Interfaces](#interfaces)
* [Custom Types](#custom-types)

### Variables and Constants

Just like the vast majority of programming languages IceScript uses variables to
store values. These are written as follows:

    var x = 10;
    var a: Int;

All variables are declared with the keyworld `var`, followed by an identifier.
Variables don't have to be initialised at the same time they are declared, but
IceScript is a strictly typed language and so must be able to deduce a type for
all the variables in any given program. As a result you will either have to
supply a value or declare a [type](#basic-types).

Constants are very similar to variables except for the fact that their value
cannot change after they are declared. They can be lazy initialised.

    let b = 20;
    let n: Int;

    b = 10; // Error: b already has a value.
    n = 10; // Okay : lazy initialisation of n.

Identifiers are defined by the following regular expression:
`[_a-zA-Z][_a-zA-Z0-9]*`

Which basically says:
The first character can be any letter, upper or lower case, between 'a' and 'z'
or an underscore. Then the following zero or more letters can be any combination
of upper or lower case letters and numbers.

The type annotations are optional as long as the compiler can work out what type
the variable or constant is.

    add: func( let a: Int, let b: Int ) -> Int
      return a + b;
    end

    let foo = add( 1, 2 );

The compiler can infer the type of `foo` by looking at the return type of the
function `add`.

[Contents](#icescript)

### Printing

[Contents](#icescript)

### Comments

    // This is a single comment.

    /*
      This is a comment that is
      written across multiple lines.

      /*
        Unlike C/C++, Java and such comments can
        be nested.
      */
    */

[Contents](#icescript)

### Basic Types

There are a few basic types in the language that can be used. Once we get to
[structs](#structs), [enums](#enums), [classes](#classes), [objects](#objects), [interfaces](#interfaces) and [custom types](#custom-types) we will see
how a program can define it's own types.

The basic types are:

| Type Name | Bytes | Other Names | Range of Values                                             |
| --------- | ----- | ----------- | ----------------------------------------------------------- |
| Int8      | 1     |             | `-128` to `127`                                             |
| Int16     | 2     |             | `-32,768` to `32,767`                                       |
| Int32     | 4     | Int         | `–2,147,483,648` to `2,147,483,647`                         |
| Int64     | 8     |             | `–9,223,372,036,854,775,808` to `9,223,372,036,854,775,807` |
| UInt8     | 1     |             | `0` to `255`                                                |
| UInt16    | 2     |             | `0` to `65,535`                                             |
| UInt32    | 4     | UInt        | `0` to `4,294,967,295`                                      |
| UInt64    | 8     |             | `0` to `18,446,744,073,709,551,615`                         |
| Float     | 4     |             | `3.4E +/- 38`  ( 7 digits  )                                |
| Double    | 8     |             | `1.7E +/- 308` ( 15 digits )                                |
| Bool      | 1     |             | `true` or `false`                                           |
| Char      | 1     |             | `-128` to `127`                                             |
| String    | N/A   |             | N/A                                                         |

[Contents](#icescript)

### Numeric Literals

There are seven types of numeric literal in this language. They are:

    let int         = 42;
    let uint        = 42u;
    let float       = 3.14159f;
    let double      = 3.14159;
    let hexidecimal = 0xDEADBEEF;
    let octal       = 0o76543210;
    let binary      = 0b10;

[Contents](#icescript)

### Pointers

[Contents](#icescript)

### If Statements

If

[Contents](#icescript)

### Loops

[Contents](#icescript)

### Functions

[Contents](#icescript)

### Structs

[Contents](#icescript)

### Enums

[Contents](#icescript)

### Classes

[Contents](#icescript)

### Objects

[Contents](#icescript)

### Interfaces

[Contents](#icescript)

### Custom Types

[Contents](#icescript)
