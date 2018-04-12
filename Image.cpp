#include "Image.h"

unsigned int Image::getHeight()
{
	return this->height;
}
unsigned int Image::getWidth()
{
	return this->width;
}

unsigned char Image::at(unsigned int channel, unsigned int x, unsigned int y)
{
	return *(this->data + (x * this->height + y) * this->num_channels + ((channel * sizeof(char))));
}

/*
char Image::operator[](unsigned int x, unsigned int y)
{
	return (this->data + x) + (width * y);
}*/

Image::Image(unsigned int width, unsigned int height, unsigned int num_channels, unsigned char* data)
{
	this->width = width;
	this->height = height;
	this->num_channels = num_channels;
	this->data = data;
}
