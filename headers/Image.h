#pragma once

class Image
{
public:
	unsigned int getHeight();
	unsigned int getWidth();
	// char operator[](unsigned int x, unsigned int y);
	Image(unsigned int width, unsigned int height, unsigned char* data);
private:
	unsigned int height;
	unsigned int width;
	unsigned char* data;
};