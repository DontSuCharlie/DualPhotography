#pragma once
#include "Image.h"
#include "ImageLoader.h"
#include "Eigen/Dense"
#include <vector>

using namespace std;
using namespace Eigen;

class DualPhotography
{
public:
	// generates the projector patterns based on the wanted resolution *and* actual resolution
	// vector<Image> generateProjectorPatterns(Vector2d wantedRes, Vector2d projectorRes);
	// creates the dual image (the image of the scene from the projector's point of view)
	Image computeDualImage(vector<Image> images, Image projectorPattern);
	void generateProjectorPatterns(string file_base_name, pair<int, int> resolution);
private:
	// load the sequence of images (e.g. "images0, images1, images2, ...")
	// nomenclature is "images"
	// num_imgs is the number of images there are (so it goes from "images0" to "imagesn")
	// void loadSequence(string nomenclature, int num_imgs);

	// converts an Image into a Vector. Does it on a row by row basis
	VectorXd imageToCol(unsigned int channel, Image img);

	// sets a m x n area to the color at x, y
	void bigBrush(Image &img, pair<int, int> pos, pair<int, int> area, Matrix<unsigned char, 3, 1> color);
};
