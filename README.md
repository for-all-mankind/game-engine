# IceEngine

A game engine written in C++ with it's own custom scripting language.

## Dependencies
The libraries that this engine uses are:
* OpenGL
* [GLFW3](http://www.glfw.org/)
* [GLEW](http://glew.sourceforge.net/)
* [YSE](http://attr-x.net/yse/)
* [Newton Dynamics](http://newtondynamics.com/forum/newton.php)

## Ice

Ice is a custom programming language used by the IceEngine for configuration
and modding.

This guide will give a brief overview of the constructs in Ice.

* [Variables](#variables)
* [Constants](#constants)
* [Printing](#printing)
* [Comments](#comments)
* [Basic Types](#basic-types)
* [Literals](#literals)
* [If Statements](#if-statements)
* [Loops](#loops)
* [Arrays](#arrays)
* [Strings](#strings)
* [Slices](#slices)
* [Functions](#functions)
* [Structs](#structs)
* [Anonymous Scopes](#anonymous-scopes)
* [Pointers](#pointers)
* [Enums](#enums)
* [Classes](#classes)
* [Objects](#objects)
* [Interfaces](#interfaces)
* [Custom Types](#custom-types)
* [Import](#import)

### Variables

Just like the vast majority of programming languages, Ice uses variables to
store modifiable values. These are written as follows:

    a: int;
    a = 10;

    b: int = 10;
    b = 20;

    c := 10;
    c = 20;

All variables are declared with an identifier followed by either a `:` and a
[type](#basic-types) or a `:=`. Variables don't have to be initialised at the same time they are
declared. Ice is a strictly typed language, but does provide type inference
as a convenience. See the [types](#basic-types) section for more details.

Identifiers are defined by the following regular expression:
`[_a-zA-Z][_a-zA-Z0-9]*`

Which basically says:
The first character can be any letter, upper or lower case, between 'a' and 'z'
or an underscore. Then the following zero or more letters can be any combination
of upper or lower case letters and numbers.

[Contents](#ice)

### Constants

Constants are very similar to variables except for the fact that their value
cannot change after they are declared. They are declared with a `::`.

    d :: 20;
    d = 10; // Error: b already has a value.

[Contents](#ice)

### Printing

TODO: start this section.

[Contents](#ice)

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

[Contents](#ice)

### Basic Types

There are a few basic types in the language that can be used. Once we get to
[structs](#structs), [enums](#enums), [classes](#classes), [objects](#objects), [interfaces](#interfaces) and [custom types](#custom-types) we will see
how a program can define it's own types.

Unlike C, all types in Ice have a default value.

The basic types are:

| Type Name | Bytes | Default Value | Range of Values                                             |
| --------- | ----- | ------------- | ----------------------------------------------------------- |
| byte      | 1     | `0`           | `-128` to `127`                                             |
| short     | 2     | `0`           | `-32,768` to `32,767`                                       |
| int       | 4     | `0`           | `–2,147,483,648` to `2,147,483,647`                         |
| long      | 8     | `0`           | `–9,223,372,036,854,775,808` to `9,223,372,036,854,775,807` |
| ubyte     | 1     | `0`           | `0` to `255`                                                |
| ushort    | 2     | `0`           | `0` to `65,535`                                             |
| uint      | 4     | `0`           | `0` to `4,294,967,295`                                      |
| ulong     | 8     | `0`           | `0` to `18,446,744,073,709,551,615`                         |
| float     | 4     | `0.0`         | `3.4E +/- 38`  ( 7 digits  )                                |
| double    | 8     | `0.0`         | `1.7E +/- 308` ( 15 digits )                                |
| bool      | 1     | `false`       | `true` or `false`                                           |
| string    | N/A   | `""`          | N/A                                                         |

It's not super important to learn these numbers. In fact most people don't.

[Contents](#ice)

### Literals

These are all the literals in this language.

    int         := 42;
    hexidecimal := 0xDEADBEEF;
    octal       := 0o76543210;
    uint        := 42u;
    float       := 3.14159f;
    double      := 3.14159;
    bool        := true;
    char        := 'a';
    string      := "Hello World";

[Contents](#ice)

### If Statements

If statements are one the control flow mechanics within Ice. They are used
to conditionally execute code at runtime.

    if ( true )
      print( "This will always print" );
    else
      print( "This will never print" );
    end

Types in Ice are very strict. The if statement only works on boolean values
or expressions that evaluate to boolean values.

    if ( 1 == 2 )
      print( "This will also never print" );
    else if ( 5 > 4 )
      print( "This will also always print" );
    else
      print( "Finally, this will never print" );
    end

[Contents](#ice)

### Loops

The second kind of control flow statement is the loop. This repeats a section of
code until some condition evaluates to false.

The `while` loop is probably the simplest of the three loops. It will execute a
block of code while the boolean expression evaluates to `true`.

This loop will print the numbers `0` to `9`:

    count := 1;

    while ( count < 10 )
      print( count );

      ++count;
    end

Something to keep in mid when using the `while` loop is that the expression is
evaluated before the loop body starts. This means it is possibly to create
loops that will never run.

Consider the following:

    while( 1 > 2 )
      print( "I don't run!" );
    end

The second kind of loop is the `for` loop. This loop is used to iterate over the
elements of a static array or any class that implements the `Indexable` interface.
Don't worry about that right now though, we'll talk about [interfaces](#interfaces) later.

Here we have an example of a static `array of strings` and we're going to loop
though the `array`, taking a view of each `string` and printing the result. Again,
don't worry about [views](#pointers), we'll cover them later.

    active_mods :: []string{
      "base_0.1.0",
      "other_0.1.0"
    };

    for ( mod^ in active_mods )
      print( mod );
    end

Another version of the `for` loop exists. It is the most complex looking of the
three, but it is in fact quite simple. It starts with an initialisation statement
followed by a boolean expression and finally it has a post statement. The initialisation
statement is run once just before the loop is run. The boolean expression is evaluated
every time the loop starts, and the loop will stop once it evaluates to `false`. Finally
the post statement is executed at the end of every loop iteration.

The following loop implements the simple [FizzBuzz](#http://blog.codinghorror.com/why-cant-programmers-program/) program.

    fizz := "Fizz";
    buzz := "Buzz";

    for ( count := 1; count < 101; ++count )
      if ( count % 15 == 0 )
        print( fizz ~ buzz );
      else if ( count % 3 == 0 )
        print( fizz );
      else if ( count % 5 == 0 )
        print( buzz );
      else
        print( count );
      end

      ++count;
    end

You may be wondering what the point of this `for` loop is since we could have done
this just as easily with the `while` loop. This is true, but the `count` variable
for the `while` loop exists outside of the scope of the loop body and will remain
until the end of the block containing the loop. On the other hand, the initialisation
statement of the `for` loop lives within the scope of the loop body.

[Contents](#ice)

### Arrays

[Contents](#ice)

### Slices

[Contents](#ice)

### Strings

[Contents](#ice)

### Functions

Functions provide a great way to structure code. They allow the programmer to
encapsulate functionality into reusable code blocks that can be called from else
where in the program.

Take for example this rather trivial and pointless program:

    print_hello: func() -> void
      print( "Hello" );
    end

    print_hello();

First we have a function header. It consists of the function name, in this case
`print_hello`, and the function signature, which for this function is `func()->void`.
There isn't much to say about the function name other than it is the identifier
that is used to call the function later. All the interesting parts are in the
signature, so lets break it down. The first part, `func`, defines this identifier
as a function. It's similar to the [types](#basic-types) that are used by variables,
except that you can't just write it on it's own. It has to be followed by the
arguments and the return type. The arguments go inside the `(` and the `)` and the
return type is after the `->`. This function has no arguments and returns `void`.
The keyword `void` just means that this function returns no value.

Right, now about those arguments. This is an example of how to define and use them:

    add_int: func( a: int, b: int ) -> int
      return a + b;
    end

    answer := add_int( 12, 42 );

    print( answer );

to be continued...

[Contents](#ice)

### Structs

Structs are one way create custom types. They consist entirely of data, in C they
are referred to as POD or plain old data.

    struct Item
      name : string;
      value: float;
    end

    struct Player
      health   : float;
      inventory: [ 6 ]Item;
    end

    player := Player{ health = H_MAX };

to be continued...

[Contents](#ice)

### Enums

    enum Days
      MONDAY,
      TUESDAY,
      WEDNESDAY,
      THURSDAY,
      FRIDAY,
      SATURDAY,
      SUNDAY
    end

[Contents](#ice)

### Anonymous Scopes

TODO: start this section.

[Contents](#ice)

### Pointers

Before we can learn how Ice handles pointers we have to know what a pointer is.
In it's simplest for a pointer is just a memory address. It points to an address
ad which resides a value.

Two important concepts to know about when working with pointers are:

* [The Stack](#the-stack)
* [The Heap](#the-heap)

#### The Stack
#### The Heap

---

Okay. Now that we have learnt how pointers can be dangerous. Lets examine how Ice
deals with them and tries to make them safe without losing the power that they hold.
There are three main concepts to grasp when using pointers in Ice, they are:

* [Owners](#owners)
* [Views](#views)
* [Borrows](#borrows)

#### Owners

The way to have a variable that is an owner of memory is to declare that memory on
the heap. This, as seen [above](#the-heap), is done with the keyword `new`.

    // Allocate enough memory to store a
    // 32 bit integer and place the value '10'
    // at the address.
    my_int_ptr := new int{ 10 };

    // Do some code here...

    delete my_int_ptr;

The type of `my_int_ptr` is `owner ^int`. The following syntax could be used to
declare an owner:

    my_int_ptr: owner ^int = new int{ 10 };

This works, but is unnecessary. The only time you have to specify the `owner` keyword
is when you want to transfer ownership of the memory to a function parameter.

Owners are not allowed to go out of scope without being deleted. The compiler will
not compile your code if there is a non-deleted owner in any scope. There are only
three valid choices for the owner variable in any scope:

1. delete the owner, freeing the memory.
2. pass the owner to a function.
3. return the owner from a function.

With these three rules it means that no memory that was allocated from the heap can
be left non-deleted.

#### Views
#### Borrows

[Contents](#ice)

### Classes

    class Vec3:
      X := 0.0f;
      Y := 0.0f;
      Z := 0.0f;

      Cross: func( other: ^Vec3 ) -> Vec3
        return Vec3{ Y * other.Z - Z * other.Y,
                     Z * other.X - X * other.Z,
                     X * other.Y - Y * other.X };
      end
    end

[Contents](#ice)

### Objects

TODO: start this section.

[Contents](#ice)

### interfaces

    interface Entity
      GetPosition: func() -> borrow ^Vec3;
    end

    class Player
      position: Vec3;

      this: func( x: Float, y: Float, z: Float )
        position.X = x;
        position.Y = y;
        position.Z = z;
      end

      GetPosition: func() -> borrow ^Vec3
        return &position;
      end
    end

    do_something_with_entity_position: func( entity: view ^Entity ) -> void
      position := entity.GetPosition();

      // ...
    end

    main: func() -> void
      player := Player{ 1.0f, 2.0f, 3.0f };

      do_something_with_entity_position( &player );
    end

[Contents](#ice)

### Custom Types

    type ResizeCallback: func( ^Window, uint, uint ) -> void;

    class Window
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

[Contents](#ice)

### Import

[Contents](#ice)