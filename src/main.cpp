#include <GLFW/glfw3.h>
#include <webgpu/webgpu_cpp.h>
#include <webgpu/webgpu_glfw.h>

#include <iostream>

#include "Engine.h"

int main(int, char**) {
  Engine engine;

  if (!engine.Initialize()) {
    std::cerr << "Failed to initialize engine" << std::endl;
    return 1;
  }

  while (engine.IsRunning()) {
    engine.MainLoop();
  }

  engine.Terminate();

  return 0;
}
