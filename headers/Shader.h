#pragma once
#include "WindowUtilities.h" // for OpenGL
#include "Logger.h"

using namespace std;

class Shader
{
public:
	// compiles and links a shader program
	// if use_shader is true, it'll use shader immediately
	// otherwise it doesn't
	Shader(const char* vert_src, const char* frag_src, bool use_shader);
	// tells OpenGL to use **this** shader
	void useShader();

private:
	unsigned int shader_program;
	unsigned int compileVertShader(const char* shader_src);
	unsigned int compileFragShader(const char* shader_src);
};