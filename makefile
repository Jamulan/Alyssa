VULKAN_SDK_PATH = $(VULKAN_SDK)

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -Ilibs
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

all: Vulkan_First Vulkan_First-Debug

Vulkan_First-Debug: main.cpp Shaders Textures Models
	g++ $(CFLAGS) -g -o make-build/Vulkan_First-Debug main.cpp $(LDFLAGS)

Vulkan_First: main.cpp Shaders Textures Models
	g++ $(CFLAGS) -O3 -o make-build/Vulkan_First main.cpp $(LDFLAGS)

.PHONY: test clean

test: Vulkan_First
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./make-buildVulkanTest

clean:
	rm -rf make-build/Vulkan_First
	rm -rf make-build/shaders/*.spv

Shaders: shaders/shader.vert shaders/shader.frag
	mkdir -p make-build/shaders
	$(VULKAN_SDK_PATH)/bin/glslc shaders/shader.vert -o make-build/shaders/vert.spv
	$(VULKAN_SDK_PATH)/bin/glslc shaders/shader.frag -o make-build/shaders/frag.spv

Textures: textures/*
	mkdir -p make-build/textures
	cp textures/* make-build/textures/

Models: models/*
	mkdir -p make-build/models
	cp models/* make-build/models/