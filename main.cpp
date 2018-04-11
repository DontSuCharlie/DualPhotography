// Custom Headers
#include "Logger.h"
#include "WindowUtilities.h"
#include "Shader.h"
#include "ImageLoader.h"
	
// Shader Source Code
#include "default-vert.h"
#include "default-frag.h"

// defines a macro that prints out what's in the parenthesis (so it prints the variable's name)

#ifdef DEBUG

#define varName(var) #var // for printing the name of the variable
Logger debug; // for printing to stdout and a log file at the same time

#endif

int main(void)
{
	#ifdef DEBUG
		debug.log("Hello World!");
	#endif
	auto window = createMainWindow();

	// vao = the object that holds the properties of the vertex attribute (i.e. how should OpenGL read the VBO)
	// we have to set the VAO up first, and it'll save the state of the next glVertexAttribPointer() call
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// load all the information needed to render stuff
	float vertices[] = {-0.5f, -0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f, 
		0.5f, 0.5f, 0.0f, 
		-0.5f, 0.5f, 0.0f};
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int indices[] = {0, 1, 2, 0, 2, 3};
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glBindVertexArray(0);
	Shader my_shader(vertexShaderSource, fragmentShaderSource, true);

	// testing Image
	Image img = loadImage("images/test.jpg");

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}