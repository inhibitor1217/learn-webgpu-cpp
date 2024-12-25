#include "Application.h"

const uint32_t kWindowWidth = 800;
const uint32_t kWindowHeight = 600;

bool Application::Initialize() {
  if (!glfwInit()) {
    return false;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(kWindowWidth, kWindowHeight, "Learn WebGPU",
                            nullptr, nullptr);
  if (!window) {
    return false;
  }

  return true;
}

void Application::Terminate() {
  if (window) {
    glfwDestroyWindow(window);
    window = nullptr;
  }

  glfwTerminate();
}

void Application::MainLoop() { glfwPollEvents(); }

bool Application::IsRunning() const { return !glfwWindowShouldClose(window); }
