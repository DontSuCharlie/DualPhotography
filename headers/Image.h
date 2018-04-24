#pragma once
#include <vector>
#include <stdlib.h>
#include "Eigen/Dense"

using namespace Eigen;

class Image
{
public:
	unsigned int getHeight();
	unsigned int getWidth();
	unsigned char* getRaw();
	unsigned char at(unsigned int channel, unsigned int x, unsigned int y);
	void set(unsigned int channel, unsigned int x, unsigned int y, unsigned char val);
	void set(unsigned int x, unsigned int y, Matrix<unsigned char, 3, 1> vals);
	// char operator[](unsigned int x, unsigned int y);
	Image(unsigned int width, unsigned int height, unsigned int num_channels);
	Image(unsigned int width, unsigned int height, unsigned int num_channels, unsigned char* data);
	~Image();
private:
	// the type of PNG given the following number of channels
	const unsigned int GREY = 1;
	const unsigned int GREY_ALPHA = 2;
	const unsigned int RGB = 3;
	const unsigned int RGBA = 4;
	unsigned int height;
	unsigned int width;
	unsigned int num_channels;
	unsigned char* data;
};