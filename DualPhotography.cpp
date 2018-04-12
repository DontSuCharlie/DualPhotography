
// for compiling stb_image_write
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

// for Microsoft Visual Studio for secure writes
#ifndef MINGW
	#define MINGW
	#ifndef STBI_MSC_SECURE_CRT
	#define STBI_MSC_SECURE_CRT
	#endif
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
	int num_imgs = images.size();
	int width = projectorPattern.getWidth();
	int height = projectorPattern.getHeight();
	MatrixXd T_matrix(images[0].getWidth() * images[0].getHeight(), width * height); // the transport matrix
	for (int i = 0; i < num_imgs; i++)
	{
		T_matrix.col(i) = imageToCol(images[i]);
	}
	T_matrix.transposeInPlace();

	VectorXd cDoublePrime(images[0].getWidth() * images[0].getHeight()); // the c'' vector
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			cDoublePrime(x * height + y) = images[x * height + y].at(0, x, y);
		}
	}
	VectorXd pDoublePrime(width * height);// the p'' vector
	pDoublePrime = T_matrix * cDoublePrime;

	// decode the 1D vector back to an image
	Image final_img(width, height, 1);
	for (int i = 0; i < pDoublePrime.size(); i++)
	{
		int x = i / height;
		int y = i % height;
		// the final_img.getWidth() is implicit, i.e. at the end, there should ONLY be w different values for x I think
		final_img.set(0, x, y, pDoublePrime[i]);
	}
	return final_img;
}