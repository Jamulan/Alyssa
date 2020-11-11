#!/bin/sh

mkdir -p libs
curl "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" > stb_image.h
curl "https://raw.githubusercontent.com/tinyobjloader/tinyobjloader/master/tiny_obj_loader.h" > tiny_obj_loader.h