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
* [Printing](#printing)
* [Comments](#comments)
* [Basic Types](#basic-types)
* [Literals](#literals)
* [If Statements](#if-statements)
* [Loops](#loops)
* [Functions](#functions)
* [Structs](#structs)
* [Anonymous Scopes](#anonymous-scopes)
* [Pointers](#pointers)
* [Enums](#enums)
* [Classes](#classes)
* [Objects](#objects)
* [interfaces](#interfaces)
* [Custom Types](#custom-types)

### Variables

Just like the vast majority of programming languages IceScript uses variables to
store modifiable values. These are written as follows:

    a: int;
    a = 10;

    b: int = 10;
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
cannot change after they are declared. They are declared with a `::`.

    d :: 20;
    d = 10; // Error: b already has a value.

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

| Type Name | Bytes | Range of Values                                             |
| --------- | ----- | ----------------------------------------------------------- |
| byte      | 1     | `-128` to `127`                                             |
| short     | 2     | `-32,768` to `32,767`                                       |
| int       | 4     | `–2,147,483,648` to `2,147,483,647`                         |
| long      | 8     | `–9,223,372,036,854,775,808` to `9,223,372,036,854,775,807` |
| ubyte     | 1     | `0` to `255`                                                |
| ushort    | 2     | `0` to `65,535`                                             |
| uint      | 4     | `0` to `4,294,967,295`                                      |
| ulong     | 8     | `0` to `18,446,744,073,709,551,615`                         |
| float     | 4     | `3.4E +/- 38`  ( 7 digits  )                                |
| double    | 8     | `1.7E +/- 308` ( 15 digits )                                |
| bool      | 1     | `true` or `false`                                           |
| char      | 1     | `-128` to `127`                                             |
| string    | N/A   | N/A                                                         |

It's not super important to learn these numbers. In fact most people don't.

[Contents](#icescript)

### Literals

These are all the literals in this language.

    int         := 42;
    hexidecimal := 0xDEADBEEF;
    octal       := 0o76543210;
    binary      := 0b10;

    uint := 42u;

    Float := 3.14159f;

    double := 3.14159;

    bool := true;

    char := 'a';

    string := "Hello World";

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

    active_mods :: Array<string>{
      "base_0.1.0",
      "other_0.1.0"
    };

    for ( mod := active_mods )
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

    print_hello: func() -> void
      print( "Hello" );
    end

    print_hello();

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

### Anonymous Scopes

TODO: start this section.

[Contents](#icescript)

### Pointers

Pointers are a bit of a complex subject, but hopefully I'll be able to explain
their usage in a clear enough manner that you'll be able to grasp them easily.

Pointers in IceScript are similar to pointers in C, but there are a few
differences that are worth noting. Pointers in C are just memory addresses, this
is the same in IceScript, however IceScript doesn't just let you do what ever
you want with them. IceScript follows the style of thinking that Rust employs.

Pointers + mutations = hard to track down bugs.

    foo := 10;
    foo  = 20; // Okay, because foo is a variable and there are no borrows at the moment.

    bar := &foo;
    foo  = 10; // Error, Can't modify foo while it is being viewed.
    *bar = 10; // Error, Can't modify the value pointed to by bar.

Okay, so there are a few new

This would be a pointer to an integer. This is what is known as a view. This says
that you would like to have a pointer to see some data, but can't modify it.
You can have as many of these at any one time as you like.

[Contents](#icescript)

### Classes

    glm::vec3: class
      X := 0.0f;
      Y := 0.0f;
      Z := 0.0f;

      Cross: func( other: ^glm::vec3 ) -> glm::vec3
        return glm::vec3{ Y * other.Z - Z * other.Y,
                     Z * other.X - X * other.Z,
                     X * other.Y - Y * other.X };
      end
    end

[Contents](#icescript)

### Objects

TODO: start this section.

[Contents](#icescript)

### interfaces

    Entity: interface
      GetPosition: func() -> borrow ^glm::vec3;
    end

    Player: class
      position: glm::vec3;

      this: func( x: Float, y: Float, z: Float )
        position.X = x;
        position.Y = y;
        position.Z = z;
      end

      GetPosition: func() -> borrow ^glm::vec3
        return &position;
      end
    end

    do_something_with_entity_position: func( entity: ^Entity ) -> void
      position := entity.GetPosition();

      // ...
    end

    main: func() -> void
      player := Player{ 1.0f, 2.0f, 3.0f };

      do_something_with_entity_position( &player );
    end

[Contents](#icescript)

### Custom Types

    ResizeCallback: type ^func( ^Window, uint, uint ) -> void;

    Window: class
      resize_callback: ResizeCallback?;

      width : uint;
      height: uint;

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

    on_window_resize: func( window: ^Window, width: uint, height: uint ) -> void
      glViewPort( 0, 0, width, height );
    end

    main: func() -> void
      window := Window{};
      window.SetResizeCallback( &on_window_resize );
    end

[Contents](#icescript)