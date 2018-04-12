
// for compiling stb_image_write
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

// for Microsoft Visual Studio for secure writes
#ifndef STBI_MSC_SECURE_CRT
#define STBI_MSC_SECURE_CRT
#endif

#include "DualPhotography.h"

// row by row basis
VectorXd DualPhotography::imageToCol(Image img)
{
	int len = img.getWidth() * img.getHeight();
	VectorXd output(len);
	for(int i = 0; i < len; i++)
	{
		output(i) = img.at(0, i % img.getWidth(), i / img.getWidth());
	}
	return output;
}

Image DualPhotography::computeDualImage(vector<Image> images, Image projectorPattern)
{
	MatrixXd T_matrix(projectorPattern.getWidth() * projectorPattern.getHeight(), images[0].getWidth() * images[0].getHeight()); // the transport matrix
	for (int i = 0; i < num_imgs; i++)
	{
		T_matrix.col(i) = imageToCol(images[i]);
	}
	T_matrix.transposeInPlace();

	VectorXd cDoublePrime; // the c'' vector
	int width = projectorPattern.getWidth();
	int height = projectorPattern.getHeight();
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			cDoublePrime(x * height + y) = images[x * height + y].red(x, y);
		}
	}
	VectorXd pDoublePrime;// the p'' vector
	pDoublePrime = T_matrix * cDoublePrime;

	// decode the 1D vector back to an image
	Image final_img;
	final_img.getWidth() = width;
	final_img.getHeight() = height;
	for (int i = 0; i < pDoublePrime.length; i++)
	{
		int x = i / height;
		int y = i % height;
		// the final_img.getWidth() is implicit, i.e. at the end, there should ONLY be w different values for x I think
		final_img.set(0, x,y) = pDoublePrime[i];
	}
	return final_img;
}