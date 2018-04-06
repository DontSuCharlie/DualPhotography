#pragma once
#include <tuple>
#include "glm/glm.hpp"

using namespace std;

class Camera : public GameObject
{
public:
// Functions involving getting/setting the FOV
	// getters for FOV
	tuple<double, double> getFOVs(); // gets both the horizontal and vertical field of view. (i.e. returns (hFOV, vFOV))
	double gethFOV(); // gets the horizontal field of view
	double getvFOV(); // gets the vertical field of view
	double getFOV(); // if your camera only has a single FOV, gets the FOV

	// setters for FOV
	void setFOVs(double hFOV, double vFOV); // sets both the horizontal and vertical FOVs
	void sethFOV(double hFOV);
	void setvFOV(double vFOV);
	void setFOV(double FOV);
// Functions involving the camera extrinsics
	void pan(double radians);
	void tilt(double radians);
	void roll(double radians);
	void rotate(double pan, double tilt, double roll); // in radians
	void translate(double x, double y, double z);

private:
	// variables involving FOV
	double hFOV; // horizontal field of view
	double vFOV; // vertical field of view
	double focal_length;

	// clipping plane
	double zFar; // far clipping plane
	double zNear; // near clipping plane
	double res_gate_width;
	double res_gate_height;
	double film_gate_width;
	double film_gate_height;

	// actual view and projection matrices
	glm::mat4 view; // holds the camera extrinsics
	glm::mat4 proj; // holds the camera intrinsics (including zFar and zNear)

	Framebuffer image; // holds the rendered image. Useful for if you want to print out what the camera sees to a PNG

	/*
	To implement later

	*/

};