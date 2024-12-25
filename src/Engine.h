#pragma once

#include <GLFW/glfw3.h>
#include <webgpu/webgpu_cpp.h>

class Engine {
 public:
  bool Initialize();
  void Terminate();
  void MainLoop();
  bool IsRunning() const;

 private:
  void logAdapterDetails(const wgpu::Adapter& adapter);

  GLFWwindow* window = nullptr;
};
