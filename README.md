# Vulkan-First
Vulkan-First is my first project working with Vulkan.

based on [this](https://vulkan-tutorial.com)

## goals
- The long term intent is to make this into a game engine, though I am starting with getting stuff on the screen and will work my way to other stuff
- The short term intent is to use this as a template to build specific applications from.

## dependencies
- VulkanSDK 1.2.148.1
- GLFW
- GLM
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) (is included in libs/)

Install on Arch:

`pacman -S glfw-x11 glm`

`glfw-wayland` *should* work but is untested

Make sure that $VULKAN_SDK is set to the path of the SDK (ex; `~/VulkanSDK/x86_64`)

## why bother?
- Making my own seemed easier than learning to use a different engine
- I have some inherent interest in this kind of stuff and the best way to learn was to make something useful