#include "Image.h"

unsigned int Image::getHeight()
{
	return this->height;
}
unsigned int Image::getWidth()
{
	return this->width;
}

/*
char Image::operator[](unsigned int x, unsigned int y)
{
	return (this->data + x) + (width * y);
}*/

Image::Image(unsigned int width, unsigned int height, unsigned char* data)
{
	this->width = width;
	this->height = height;
	this->data = data;
}
