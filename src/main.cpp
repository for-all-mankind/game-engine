#include "util/types.h"
#include "core/engine.h"

i32 main( i32 argc, char* argv[] )
{
  Ice::Engine engine;

  engine.InitWindow( Ice::WindowConfig{ "Ice Engine", 800, 600 } );

  engine.Run();
}