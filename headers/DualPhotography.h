#pragma once

class DualPhotography
{
public:
	// creates the dual image (the image of the scene from the projector's point of view)
	Image computeDualImage(vector<Image> images, Image projectorPattern);
	/*
	// Pseudo code
	Matrix T_matrix; // the T matrix
	int num_imgs = images.size();
	for(int i = 0; i < num_imgs; i++)
	{
		T_matrix[i] = matToCol(images[i]);
	}
	T_matrix.transpose();
	
	Vector cDoublePrime; // the c'' vector
	for(int x = 0; x < projectorPattern.w; x++)
	{
		for(int y = 0; y < projectorPattern.h; y++)
		{
			cDoublePrime[x * projectorPattern.h + y] = images[x * projectorPattern.h + y][x][y];
		}
	}
	Vector pDoublePrime;// the p'' vector
	pDoublePrime = T_matrix * cDoublePrime;

	// decode the 1D vector back to an image

	Image final_img;
	final_img.w = projectorPattern.w;
	final_img.h = projectorPattern.h;
	for(int i = 0; i < pDoublePrime.length; i++)
	{
		int x = i / final_img.h;
		int y = i % final_img.h;
		// the final_img.w is implicit, i.e. at the end, there should ONLY be w different values for x I think
		final_img[x][y] = pDoublePrime[i];
	}
	return final_img;
	*/
private:
	// load the sequence of images (e.g. "images0, images1, images2, ...")
	// nomenclature is "images"
	// num_imgs is the number of images there are (so it goes from "images0" to "imagesn")
	void loadSequence(string nomenclature, int num_imgs);

};
