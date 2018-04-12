#include "Image.h"

unsigned int Image::getHeight()
{
	return this->height;
}
unsigned int Image::getWidth()
{
	return this->width;
}

unsigned char* Image::getRaw()
{
	return this->data;
}

unsigned char Image::at(unsigned int channel, unsigned int x, unsigned int y)
{
	return *(this->data + (x * this->height + y) * this->num_channels + ((channel * sizeof(char))));
}

void Image::set(unsigned int channel, unsigned int x, unsigned int y, unsigned char val)
{
	*(this->data + (x * this->height + y) * this->num_channels + ((channel * sizeof(char)))) = val;
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

// create a new empty image; does the memory allocation for you
Image::Image(unsigned int width, unsigned int height, unsigned int num_channels)
{
	unsigned char* data = (unsigned char*) malloc(sizeof(unsigned char) * width * height * num_channels);
	Image(width, height, num_channels, data);
}

Image::~Image()
{
	free(this->data);
}