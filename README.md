# IceEngine

A game engine written in C++ with it's own custom scripting language.

## Dependencies
The libraries that this engine uses are:
* OpenGL
* [GLFW3](http://www.glfw.org/)
* [GLEW](http://glew.sourceforge.net/)
* [YSE](http://attr-x.net/yse/)
* [Newton Dynamics](http://newtondynamics.com/forum/newton.php)

## IceScript

IceScript is a custom programming language used by IceEngine for configuration
and modding.

This guide will give a brief overview of the constructs in IceScript.

* [Variables](#variables)
* [Constants](#constants)
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

### Variables

Just like the vast majority of programming languages IceScript uses variables to
store modifiable values. These are written as follows:

    a: Int;
    a = 10;

    b: Int = 10;
    b = 20;

    c := 10;
    c = 20;

All variables are declared with an identifier followed by either a `:` and a
[type](#basic-types) or a `:=`. Variables don't have to be initialised at the same time they are
declared. IceScript is a strictly typed language, but does provide type inference
as a convenience. See the [types](#basic-types) section for more details.

Identifiers are defined by the following regular expression:
`[_a-zA-Z][_a-zA-Z0-9]*`

Which basically says:
The first character can be any letter, upper or lower case, between 'a' and 'z'
or an underscore. Then the following zero or more letters can be any combination
of upper or lower case letters and numbers.

[Contents](#icescript)

### Constants

Constants are very similar to variables except for the fact that their value
cannot change after they are declared.

    d :: 20;
    d = 10; // Error: b already has a value.


The type annotations are optional as long as the compiler can work out what type
the variable or constant is.

    add: func( a: Int, b: Int ) -> Int
      return a + b;
    end

    foo := add( 1, 2 );

The compiler can infer the type of `foo` by looking at the return type of the
function `add`.

[Contents](#icescript)

### Printing

TODO: start this section.

[Contents](#icescript)

### Comments

    // This is a single comment.

    /*
      This is a comment that is
      written across multiple lines.

      /*
        Unlike C/C++, Java and other such languages, multi-line comments can
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

    int         := 42;
    uint        := 42u;
    float       := 3.14159f;
    double      := 3.14159;
    hexidecimal := 0xDEADBEEF;
    octal       := 0o76543210;
    binary      := 0b10;

Hexidecimal, octal and binary are all 32 bit integers.

[Contents](#icescript)

### Pointers

TODO: start this section.

[Contents](#icescript)

### If Statements

    if ( true )
      print( "This will always print" );
    else
      print( "This will never print" );
    end

    if ( false )
      print( "This will also never print" );
    else if ( true )
      print( "This will also always print" );
    else
      print( "Finally, this will never print" );
    end

[Contents](#icescript)

### Loops

    for ( index := 0; index < 10; ++index )
      print( index );
    end

    active_mods :: []String{
      "base_0.1.0",
      "other_0.1.0"
    };

    for ( mod in active_mods )
      print( mod );
    end

    start := 1;
    stop  := 101;

    while ( true )
      if ( start == stop )
        break;
      end

      if ( start % 3 == 0 && start % 5 == 0 )
        print( "FizzBuzz" );
      else if ( start % 3 == 0 )
        print( "Fizz" );
      else if ( start % 5 == 0 )
        print( "Buzz" );
      else
        print( start );
      end

      ++start;
    end

[Contents](#icescript)

### Functions

    main: func( args :: []String ) -> Int
      print( "Hello World" );
    end

    main();

[Contents](#icescript)

### Structs

TODO: start this section.

[Contents](#icescript)

### Enums

    Days: enum
      MONDAY,
      TUESDAY,
      WEDNESDAY,
      THURSDAY,
      FRIDAY,
      SATURDAY,
      SUNDAY
    end

[Contents](#icescript)

### Classes

    Vec3: class
      X := 0.0f;
      Y := 0.0f;
      Z := 0.0f;

      Cross: func( other: ^Vec3 ) -> Vec3
        return Vec3{ Y * other.Z - Z * other.Y,
                     Z * other.X - X * other.Z,
                     X * other.Y - Y * other.X };
      end
    end

[Contents](#icescript)

### Objects

TODO: start this section.

[Contents](#icescript)

### Interfaces

    Entity: interface
      GetPosition: func() -> mut ^Vec3;
    end

    Player: class
      position: Vec3;

      this: func( x: float, y: float, z: float )
        position.X = x;
        position.Y = y;
        position.Z = z;
      end

      GetPosition: func() -> mut ^Vec3
        return &position;
      end
    end

    do_something_with_entity_position: func( entity: ^Entity ) -> void
      position := entity.GetPosition();

      // ...
    end

    main: func( args :: []String ) -> Int
      player := Player{ 1.0f, 2.0f, 3.0f };

      do_something_with_entity_position( &player );
    end

[Contents](#icescript)

### Custom Types

    ResizeCallback: type ^func( ^Window, UInt, UInt ) -> void;

    Window: class
      resize_callback: ResizeCallback?;

      width : Uint;
      height: Uint;

      this: func()
        resize_callback = null;
      end

      SetResizeCallback: func( callback: ResizeCallback ) -> void
        resize_callback = callback;
      end

      OnResizeEvent: func() -> void
        if ( resize_callback != null )
          resize_callback( this, width, height );
      end
    end

    on_window_resize: func( window: ^Window, width: UInt, height: UInt ) -> void
      glViewPort( 0, 0, width, height );
    end

    main: func( args :: []String ) -> Int
      window := Window{};
      window.SetResizeCallback( &on_window_resize );
    end

[Contents](#icescript)