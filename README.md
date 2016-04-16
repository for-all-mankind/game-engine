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
* [Pointers](#pointers)
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

### Basic Types

There are a few basic types in the language that can be used. Once we get to
[structs](#structs), [enums](#enums), [classes](#classes), [objects](#objects), [interfaces](#interfaces) and [custom types](#custom-types) we will see
how a program can define it's own types.

The basic types are:

* Int8
* Int16
* Int32
* Int64
* UInt8
* UInt16
* UInt32
* UInt64
* Float
* Double
* Bool
* Char
* String

### Pointers
### If Statements
### Loops
### Functions
### Structs
### Enums
### Classes
### Objects
### Interfaces
### Custom Types