#include "Image.h"

unsigned int Image::getHeight()
{
	return this->height;
}
unsigned int Image::getWidth()
{
	return this->width;
}

unsigned int Image::red(unsigned int x, unsigned int y)
{
	return ( this->data + ((x * this->height + y) * this->num_channels));
}

unsigned int Image::green(unsigned int x, unsigned int y)
{
	return ( this->data + ((x * this->height + y) * this->num_channels) + sizeof(char));	
}

unsigned int Image::blue(unsigned int x, unsigned int y)
{
	return ( this->data + ((x * this->height + y) * this->num_channels) + (2 * sizeof(char)));
}

unsigned int Image::alpha(unsigned int x, unsigned int y)
{
	if(this->num_channels < 4)
	{
		cerr << "The image doesn't have an alpha channel!" << endl;
		return 0;
	}
	return ( this->data + ((x * this->height + y) * this->num_channels) + (3 * sizeof(char)));
}

unsigned int Image::at(unsigned int x, unsigned int y)
{
	vector<unsigned int> color(this->num_channels);
	for(int i = 0; i < )
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
