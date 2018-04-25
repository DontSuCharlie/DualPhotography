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
		output(i) = img.at(2, i % img.getWidth(), i / img.getWidth());
		// printf("output(%d) = %f\n", i, output(i));
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

	int cam_dim = images[0].getWidth() * images[0].getHeight();
	VectorXd cDoublePrime(cam_dim); // the c'' vector
	for (int i = 0; i < cam_dim; i++)
	{
		cDoublePrime(i) = 255.0f;
	}

	VectorXd pDoublePrime(width * height);// the p'' vector
	pDoublePrime = T_matrix * cDoublePrime;

	// decode the 1D vector back to an image
	double max = -INFINITY;
	double min = -max;
	for (int i = 0; i < pDoublePrime.size(); i++)
	{
		if (pDoublePrime[i] > max)
		{
			max = pDoublePrime[i];
		}
		if (pDoublePrime[i] < min)
		{
			min = pDoublePrime[i];
		}
	}

	Image final_img(width, height, 3);

	for (int i = 0; i < pDoublePrime.size(); i++)
	{
		int x = i / height;
		int y = i % height;
		// the final_img.getWidth() is implicit, i.e. at the end, there should ONLY be w different values for x I think
		pDoublePrime[i] = (pDoublePrime[i] - min) / (max - min) * 255.0f;
		printf("Assigning (%d, %d) with %f\n", height - x - 1, y, pDoublePrime[i]);

		// height - x - 1 instead of x bc it prints the original image upside down
		final_img.set(0, height - x - 1, y, pDoublePrime[i]);
		final_img.set(1, height - x - 1, y, pDoublePrime[i]);
		final_img.set(2, height - x - 1, y, pDoublePrime[i]);
	}
	return final_img;
}