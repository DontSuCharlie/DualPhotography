#include "WindowUtilities.h"
#include "Logger.h"

Logger windowUtilities_debug;

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	// maintain context size
	glViewport(0, 0, width, height);
}


GLFWwindow* createMainWindow()
{
	int window_width{640}, window_height{360};
	// initialize GLFW
	if(!glfwInit())
	{
		windowUtilities_debug.log("Unable to initalize GLFW3");
		exit(-1);
	}

// create window
	glfwWindowHint(GLFW_SAMPLES, 4);
	//OpenGL 4.5 is the version *I* have
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
	auto window = glfwCreateWindow(window_width, window_height, "Engine 63500", nullptr, nullptr);
	if(!window)
	{
		glfwTerminate();
		windowUtilities_debug.log("Unable to open a window with GLFW3");
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		windowUtilities_debug.log("Unable to initialize GLAD");
		exit(-1);
	}
	glfwSetWindowAspectRatio(window, window_width, window_height);
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
	glViewport(0, 0, window_width, window_height);
	return window;
}
