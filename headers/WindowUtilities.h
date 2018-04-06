#pragma once
#include "glad/glad.h"
#include "glfw3/glfw3.h"
#include "glm/glm.hpp"
#include <tuple>
/*
Hides GLFW3 and GLAD from whoever uses this engine
*/

using namespace std;

// initializes GLFW and GLAD, and creates a main window. This should only be called once.
GLFWwindow* createMainWindow();

// call back for when a person resizes the window. It enforces the defined aspect ratio while making sure the OpenGL context's dimensions equal the window size
void windowResizeCallback(GLFWwindow* window, int width, int height);
