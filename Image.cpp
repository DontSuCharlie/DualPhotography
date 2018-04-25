#include "Image.h"

unsigned int Image::getHeight()
{
	return this->height;
}
unsigned int Image::getWidth()
{
	return this->width;
}

int Image::getNumChannels()
{
	return this->num_channels;
}

unsigned char* Image::getRaw()
{
	return this->data;
}

unsigned char Image::at(unsigned int channel, unsigned int x, unsigned int y)
{
	/*
	printf("Number of channels = %d\n", this->num_channels);
	printf("heigth = %d\n", height);
	printf("Size per channel = %d\n", sizeof(char));
	printf("Channel requested = %d\n", channel);
	printf("Pixel requested = (%d, %d)\n", x, y);
	printf("Starting point = %p\n", this->data);
	printf("Calculated = %p\n", (this->data + (x * this->height + y) * this->num_channels + ((channel * sizeof(char)))));
	printf("start is at %p, x = %d, y = %d, calculated data is at %p\n", 
		this->data,
		x,
		y,
		this->data + (x * this->height + y) * this->num_channels + ((channel * sizeof(char))));*/
	return *(this->data + (x * this->height + y) * this->num_channels + ((channel * sizeof(char))));
	/*
	unsigned int pos = (x * this->height) + y;
	unsigned int offset = (pos * this->num_channels) + (channel * sizeof(unsigned char));
	return *(this->data + offset);
	*/
}

void Image::set(unsigned int channel, unsigned int x, unsigned int y, unsigned char val)
{
	*(this->data + (x * this->height + y) * this->num_channels + ((channel * sizeof(char)))) = val;
}

void Image::set(unsigned int x, unsigned int y, Matrix<unsigned char, 3, 1> vals)
{
	for(int i = 0; i < 3; i++)
		this->set(i, x, y, vals(i));
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
	this->data = (unsigned char*) calloc(width * height * num_channels, sizeof(unsigned char));
	this->width = width;
	this->height = height;
	this-> num_channels = num_channels;
	// Image(width, height, num_channels, data);
}

Image::~Image()
{
	// free(this->data);
}