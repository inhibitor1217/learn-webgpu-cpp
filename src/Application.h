#pragma once

#include <GLFW/glfw3.h>

class Application {
 public:
  bool Initialize();
  void Terminate();
  void MainLoop();
  bool IsRunning() const;

 private:
  GLFWwindow* window = nullptr;
};
