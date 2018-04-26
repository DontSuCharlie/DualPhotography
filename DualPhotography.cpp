// for Microsoft Visual Studio for secure writes
#ifndef MINGW
	#define MINGW
	#ifndef STBI_MSC_SECURE_CRT
	#define STBI_MSC_SECURE_CRT
	#endif
#endif

#include "DualPhotography.h"

// row by row basis
VectorXd DualPhotography::imageToCol(unsigned int channel, Image img)
{
	int len = img.getWidth() * img.getHeight();
	VectorXd output(len);
	for(int i = 0; i < len; i++)
	{
		output(i) = img.at(channel, i % img.getWidth(), i / img.getWidth());
		// printf("output(%d) = %f\n", i, output(i));
	}
	return output;
}

void DualPhotography::bigBrush(Image &img, pair<int, int> pos, pair<int, int> area, Matrix<unsigned char, 3, 1> color)
{
	/*
	int counter = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			img.set(i, j, color);
			writeImage(img, "projector-patterns/frames/a" + to_string(counter++) + ".png");
		}
	}*/
	
	for (int i = pos.first; i < pos.first + area.first; i++)
	{
		for (int j = pos.second; j < pos.second + area.second; j++)
		{
			img.set(i, j, color);
		}
	}
}

// currently implementing the brute force way
Image DualPhotography::generateProjectorPatterns(string file_base_name, pair<int, int> resolution)
{
	// hardcoding this for now
	Image projectorPattern(3840, 2160, 3);
	int block_size = 216;
	// start at 216, end 216 away
	Matrix<unsigned char, 3, 1> white(255, 255, 255);
	Matrix<unsigned char, 3, 1> black(0, 0, 0);
	int counter = 0;
	for(int i = 1056; i < 3840 - 1056; i+=block_size)
	{
		for(int j = 216; j < 2160 - 216; j+=block_size)
		{
			// set entire group to white
			this->bigBrush(projectorPattern, pair<int, int>(i, j), pair<int, int>(block_size, block_size), white);
			writeImage(projectorPattern, file_base_name + to_string(counter) + ".png");
			++counter;
			this->bigBrush(projectorPattern, pair<int, int>(i, j), pair<int, int>(block_size, block_size), black);
		}
	}
	return projectorPattern;
}



Image DualPhotography::computeDualImage(vector<Image> images, Image projectorPattern)
{
	int num_imgs = images.size();
	int width = projectorPattern.getWidth();
	int height = projectorPattern.getHeight();
	MatrixXd T_matrixR(images[1].getWidth() * images[1].getHeight(), width * height); // the transport matrix
	MatrixXd T_matrixG(images[1].getWidth() * images[1].getHeight(), width * height); // the transport matrix
	MatrixXd T_matrixB(images[1].getWidth() * images[1].getHeight(), width * height); // the transport matrix
	for (int i = 0; i < num_imgs; i++)
	{
		T_matrixR.col(i) = imageToCol(0, images[i]);
		T_matrixG.col(i) = imageToCol(1, images[i]);
		T_matrixB.col(i) = imageToCol(2, images[i]);
	}
	T_matrixR.transposeInPlace();
	T_matrixG.transposeInPlace();
	T_matrixB.transposeInPlace();

	int cam_dim = images[1].getWidth() * images[1].getHeight();
	VectorXd cDoublePrime(cam_dim); // the c'' vector
	for (int i = 0; i < cam_dim; i++)
	{
		cDoublePrime(i) = 255.0f;
	}

	VectorXd pDoublePrimeR(width * height);// the p'' vector
	VectorXd pDoublePrimeG(width * height);// the p'' vector
	VectorXd pDoublePrimeB(width * height);// the p'' vector
	pDoublePrimeR = T_matrixR * cDoublePrime;
	pDoublePrimeG = T_matrixG * cDoublePrime;
	pDoublePrimeB = T_matrixB * cDoublePrime;

	// decode the 1D vector back to an image
	double min[3] = {INFINITY, INFINITY, INFINITY};
	double max[3] = {-min[0], -min[0], -min[0]};
	for (int i = 0; i < pDoublePrimeR.size(); i++)
	{
		if (pDoublePrimeR[i] > max[0])
		{
			max[0] = pDoublePrimeR[i];
		}
		if (pDoublePrimeR[i] < min[0])
		{
			min[0] = pDoublePrimeR[i];
		}

		if (pDoublePrimeG[i] > max[1])
		{
			max[1] = pDoublePrimeG[i];
		}
		if (pDoublePrimeG[i] < min[1])
		{
			min[1] = pDoublePrimeG[i];
		}
		
		if (pDoublePrimeB[i] > max[2])
		{
			max[2] = pDoublePrimeB[i];
		}
		if (pDoublePrimeB[i] < min[2])
		{
			min[2] = pDoublePrimeB[i];
		}
	}

	Image final_img(width, height, 3);

	for (int i = 0; i < pDoublePrimeR.size(); i++)
	{
		int x = i / height;
		int y = i % height;
		// the final_img.getWidth() is implicit, i.e. at the end, there should ONLY be w different values for x I think
		pDoublePrimeR[i] = (pDoublePrimeR[i] - min[0]) / (max[0] - min[0]) * 255.0f;
		pDoublePrimeG[i] = (pDoublePrimeG[i] - min[1]) / (max[1] - min[1]) * 255.0f;
		pDoublePrimeB[i] = (pDoublePrimeB[i] - min[2]) / (max[2] - min[2]) * 255.0f;

		Matrix<unsigned char, 3, 1> color(pDoublePrimeR[i], pDoublePrimeG[i], pDoublePrimeB[i]);
		final_img.set(height - x - 1, y, color);
	}
	return final_img;
}