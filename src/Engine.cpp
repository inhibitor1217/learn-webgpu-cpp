#include "Engine.h"

#include <webgpu/webgpu_glfw.h>

#include <iostream>

const uint32_t kWindowWidth = 800;
const uint32_t kWindowHeight = 600;

void wgpuRequestAdapterSync(const wgpu::Instance instance,
                            const wgpu::RequestAdapterOptions* options,
                            wgpu::Adapter& pAdapter) {
  instance.RequestAdapter(
      options,
      [](WGPURequestAdapterStatus status, WGPUAdapter adapter,
         struct WGPUStringView, void* userdata) {
        WGPUAdapter* pAdapter = reinterpret_cast<WGPUAdapter*>(userdata);
        if (status == WGPURequestAdapterStatus_Success) {
          *pAdapter = adapter;
        } else {
          *pAdapter = nullptr;
        }
      },
      reinterpret_cast<void*>(&pAdapter));
}

void wgpuRequestDeviceSync(const wgpu::Adapter adapter,
                           const wgpu::DeviceDescriptor* descriptor,
                           wgpu::Device& pDevice) {
  adapter.RequestDevice(
      descriptor,
      [](WGPURequestDeviceStatus status, WGPUDevice device,
         struct WGPUStringView, void* userdata) {
        WGPUDevice* pDevice = reinterpret_cast<WGPUDevice*>(userdata);
        if (status == WGPURequestDeviceStatus_Success) {
          *pDevice = device;
        } else {
          *pDevice = nullptr;
        }
      },
      reinterpret_cast<void*>(&pDevice));
}

bool Engine::Initialize() {
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

  wgpu::InstanceDescriptor instanceDesc{.nextInChain = nullptr};
  wgpu::Instance instance = wgpu::CreateInstance(&instanceDesc);
  if (!instance) {
    return false;
  }

  wgpu::Surface surface = wgpu::glfw::CreateSurfaceForWindow(instance, window);

  wgpu::RequestAdapterOptions options{.compatibleSurface = surface};
  wgpu::Adapter adapter;
  wgpuRequestAdapterSync(instance, &options, adapter);
  if (!adapter) {
    return false;
  }
  logAdapterDetails(adapter);

  wgpu::DeviceDescriptor deviceDesc{};
  deviceDesc.SetDeviceLostCallback(
      wgpu::CallbackMode::WaitAnyOnly,
      [](const wgpu::Device&, wgpu::DeviceLostReason reason,
         const char* message, void*) {
        std::cerr << "Device lost. Reason: " << static_cast<uint32_t>(reason)
                  << " message: " << message << std::endl;
      },
      static_cast<void*>(nullptr));
  deviceDesc.SetUncapturedErrorCallback(
      [](const wgpu::Device&, wgpu::ErrorType type, const char* message,
         void*) {
        std::cerr << "Error type: " << static_cast<uint32_t>(type)
                  << " message: " << message << std::endl;
      },
      static_cast<void*>(nullptr));
  wgpu::Device device;
  wgpuRequestDeviceSync(adapter, &deviceDesc, device);
  if (!device) {
    return false;
  }

  return true;
}

void Engine::logAdapterDetails(const wgpu::Adapter& adapter) {
  wgpu::AdapterInfo info;
  if (adapter.GetInfo(&info)) {
    std::cout << "Adapter properties:" << std::endl;
    std::cout << "  vendor: " << info.vendor.data << std::endl;
    std::cout << "  architecture: " << info.architecture.data << std::endl;
    std::cout << "  device: " << info.device.data << std::endl;
    std::cout << "  description: " << info.description.data << std::endl;
    std::cout << std::hex;
    std::cout << "  backendType: 0x" << static_cast<uint32_t>(info.backendType)
              << std::endl;
    std::cout << "  adapterType: 0x" << static_cast<uint32_t>(info.adapterType)
              << std::endl;
    std::cout << std::dec;
    std::cout << "  vendorID: " << info.vendorID << std::endl;
    std::cout << "  deviceID: " << info.deviceID << std::endl;
  } else {
    std::cerr << "Failed to get adapter info" << std::endl;
  }
}

void Engine::Terminate() {
  if (window) {
    glfwDestroyWindow(window);
    window = nullptr;
  }

  glfwTerminate();
}

void Engine::MainLoop() { glfwPollEvents(); }

bool Engine::IsRunning() const { return !glfwWindowShouldClose(window); }
