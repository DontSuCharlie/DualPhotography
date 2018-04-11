
// for compiling stb_image_write
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

// for Microsoft Visual Studio for secure writes
#ifndef STBI_MSC_SECURE_CRT
#define STBI_MSC_SECURE_CRT
#endif

#include "DualPhotography.h"

vector<Image> DualPhotography::generateProjectorPatterns(Vector2d wantedRes, Vector2d projectorRes)
{

}

// row by row basis
VectorXd DualPhotography::imageToCol(Image img)
{
	int len = img.getWidth() * img.getHeight();
	VectorXd output(len);
	for(int i = 0; i < len; i++)
	{
		output(i) = img
	}
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
	for (int x = 0; x < projectorPattern.getWidth(); x++)
	{
		for (int y = 0; y < projectorPattern.getHeight(); y++)
		{
			cDoublePrime[x * projectorPattern.getHeight() + y] = images[x * projectorPattern.getHeight() + y][x][y];
		}
	}
	VectorXd pDoublePrime;// the p'' vector
	pDoublePrime = T_matrix * cDoublePrime;

	// decode the 1D vector back to an image

	Image final_img;
	final_img.getWidth() = projectorPattern.getWidth();
	final_img.getHeight() = projectorPattern.getHeight();
	for (int i = 0; i < pDoublePrime.length; i++)
	{
		int x = i / final_img.getHeight();
		int y = i % final_img.getHeight();
		// the final_img.getWidth() is implicit, i.e. at the end, there should ONLY be w different values for x I think
		final_img[x][y] = pDoublePrime[i];
	}
	return final_img;
}