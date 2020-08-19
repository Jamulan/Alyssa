VULKAN_SDK_PATH = /home/jamulan/Dev/Vulkan/1.2.148.1/x86_64

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

all: Vulkan_First Vulkan_First-Debug


Vulkan_First-Debug: main.cpp
	g++ $(CFLAGS) -g -o make-build/Vulkan_First-Debug main.cpp $(LDFLAGS)

Vulkan_First: main.cpp
	g++ $(CFLAGS) -o make-build/Vulkan_First main.cpp $(LDFLAGS)

.PHONY: test clean

test: Vulkan_First
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./make-buildVulkanTest

clean:
	rm -rf make-build/Vulkan_First
