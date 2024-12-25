#include <GLFW/glfw3.h>
#include <webgpu/webgpu_cpp.h>
#include <webgpu/webgpu_glfw.h>

#include <iostream>

#include "Application.h"

int main(int, char**) {
  Application app;

  if (!app.Initialize()) {
    std::cerr << "Failed to initialize application" << std::endl;
    return 1;
  }

  while (app.IsRunning()) {
    app.MainLoop();
  }

  app.Terminate();

  return 0;
}
