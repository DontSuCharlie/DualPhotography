#pragma once
#include <string>
#include <vector>

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"
#include "Image.h"

using namespace std;
/*
// A wrapper class for stb/stb_image.h
Loads images

Using stb/stb_image.h

int x, y, n
unsigned char *data = stbi_load(filename, &x, &y, &n, numComponents);

filename = image file to open (only supports PNG, JPEG, GIF)
x = width
y = height
n = number of 8 bit components per pixel
numComponents = (if >0) forces the number of 8 bit components per pixel; if == 0 sets a default number of 8-bit components per pixel (and sets n to the number set)

*/

Image loadImage(string file);
// Image loadAllImages(string directory);

void writeImage(Image image, string name);