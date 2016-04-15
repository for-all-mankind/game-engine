#include "util/types.h"
#include "core/engine.h"

i32 main( i32 argc, char* argv[] )
{
  Ice::Engine engine;

  engine.InitWindow(); // Window and rendering systems.
  engine.InitAudio();  // Audio playback systems.
  engine.InitMods();   // Game and mod content.

  engine.Run();
}