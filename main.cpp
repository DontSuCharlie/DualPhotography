// Custom Headers
#include "Logger.h"
#include "WindowUtilities.h"
#include "Shader.h"
#include "ImageLoader.h"
#include "DualPhotography.h"
	
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
	float vertices[] = {
		// vertex position		// texture coords
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f};
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int indices[] = {0, 1, 2, 0, 2, 3};
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vertex attribute pointer for the position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // enables the attrib pointer, i.e. the shader can now access it, I think
	// vertex attribute pointer for the texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glBindVertexArray(0);
	Shader my_shader(vertexShaderSource, fragmentShaderSource, true);

	// testing Image
	Image img = loadImage("images/SampleA/IMAG1349.jpg");
	

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.getWidth(), img.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.getRaw());
	glGenerateMipmap(GL_TEXTURE_2D);

// testing Dual Photography
	// create the projector pattern (aka all white)
	Image projectorPattern(4, 4, 1);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4 ; j++)
		{
			projectorPattern.set(0, i, j, 255);			
		}
	}
	vector<Image> samples;
	const int sampleANum = 1349;
	const int sampleBNum = 1366;
	const int sampleCNum = 1383;
	const int sampleDNum = 1406;
	for(int i = 0; i < 16; i++)
	{
		samples.push_back(loadImage("images/SampleD/IMAG" + to_string(sampleDNum + i) + ".jpg"));
		// note to self: need to figure out how to deal with vector<Image> being able to assigned a const Image w/o a default constructor?
	}
	DualPhotography experim1;
	Image orig1 = experim1.computeDualImage(samples, projectorPattern);
	// render images
	GLuint experim1Tex;
	glGenTextures(1, &experim1Tex);
	glBindTexture(GL_TEXTURE_2D, experim1Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glTextureParameteri(experim1Tex, GL_MIN)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, orig1.getWidth(), orig1.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, orig1.getRaw());
	glGenerateMipmap(GL_TEXTURE_2D);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}