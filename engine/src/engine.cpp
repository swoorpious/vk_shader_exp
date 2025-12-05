// copyright 2025 swaroop.

#include "../include/Engine.h"

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <vector>
#include <stdexcept>


Engine::Engine() {
    initSDL();
    initWindow();
    initVulkan();
}

Engine::~Engine() {
    if (surface) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }
    if (instance) {
        vkDestroyInstance(instance, nullptr);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    std::cout << "shutdown complete\n";
}

void Engine::run() {
    std::cout << "app running\n";
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }
}

void Engine::initSDL()  {
    SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        // Detailed diagnostic if init fails
        const char* err = SDL_GetError();
        std::cerr << "SDL_Init failed: " << (err ? err : "unknown error") << "\n";
            
        int numDrivers = SDL_GetNumVideoDrivers();
        std::cerr << "available video drivers: " << numDrivers << "\n";
        for(int i=0; i < numDrivers; i++) {
            std::cerr << " - " << SDL_GetVideoDriver(i) << "\n";
        }
            
        if (numDrivers == 0) {
            std::cerr << "CRITICAL: SDL was built without any video backends. \n"
                      << "if on Linux, install X11/Wayland dev headers before running CMake.\n";
        }
        throw std::runtime_error("failed to initialize SDL Video");
    }
}

void Engine::initWindow() {
    {
        window = SDL_CreateWindow(
            "sdl+vulkan Engine test",
            800, 600,
            SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
        );

        // TODO: use and implement viewport.h
        
        if (!window) {
            throw std::runtime_error(std::string("failed to create window: ") + SDL_GetError());
        }
    }
}

void Engine::initVulkan() {
    Uint32 extCount = 0;
    const char* const* extNames = SDL_Vulkan_GetInstanceExtensions(&extCount);
    if (!extNames) {
        throw std::runtime_error("SDL could not get Vulkan extensions.");
    }
    std::vector<const char*> extensions(extNames, extNames + extCount);

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instanceInfo.ppEnabledExtensionNames = extensions.data();

    if (vkCreateInstance(&instanceInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create Vulkan instance");
    }

    if (!SDL_Vulkan_CreateSurface(window, instance, nullptr, &surface)) {
        throw std::runtime_error(std::string("failed to create Vulkan Surface: ") + SDL_GetError());
    }
}
