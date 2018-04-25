#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#include "ImageLoader.h"
#include <stdio.h>
#ifdef DEBUG
	#include <string>
	#include "Logger.h"
	Logger debug_imgLoader;
	using namespace std;
#endif

Image loadImage(string file)
{
	// x = width, y = height, n = number of channels
	int x, y, n;
	int numComponents(0);
	unsigned char* data = stbi_load(file.c_str(), &x, &y, &n, numComponents);

	#ifdef DEBUG
		debug_imgLoader.log("Opened file!");
		debug_imgLoader.log(to_string(x));
		debug_imgLoader.log(to_string(y));
		debug_imgLoader.log(to_string(n));
		// debug_imgLoader.log(to_string(data));
	#endif
	if (!data)
	{
		printf("ERROR: Unable to load %s\n", file);
	}
	return Image((unsigned int)(x), (unsigned int)(y), (unsigned int)(n), data);
}

// vector<Image> loadAllImages(string directory)
// {

// }

void writeImage(Image image, string name)
{
	stbi_write_png(name.c_str(), image.getWidth(), image.getHeight(), image.getNumChannels(), image.getRaw(), 0);
}