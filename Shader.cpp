#include "Shader.h"

#ifdef DEBUG
	Logger shader_debug;
#endif

unsigned int Shader::compileVertShader(const char* shader_src)
{
	unsigned int vert_shader;
	vert_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_shader, 1, &shader_src, nullptr);
	glCompileShader(vert_shader);
	// check if compilation was successful
	#ifdef DEBUG
		int isSuccessful;
		char info[1024];
		glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &isSuccessful);
		if(!isSuccessful)
		{
			glGetShaderInfoLog(vert_shader, 1024, nullptr, info);
			string info_str(info);
			shader_debug.log(info);
		}
		else
		{
			shader_debug.log("Compiled the vert shader with no errors");
		}
	#endif
	return vert_shader;
}

unsigned int Shader::compileFragShader(const char* shader_src)
{
	unsigned int frag_shader;
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &shader_src, nullptr);
	glCompileShader(frag_shader);
	// check if compilation was successful
	#ifdef DEBUG
		int isSuccessful;
		char info[1024];
		glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &isSuccessful);
		if(!isSuccessful)
		{
			glGetShaderInfoLog(frag_shader, 1024, nullptr, info);
			string info_str(info);
			shader_debug.log(info);
		}
		else
		{
			shader_debug.log("Compiled the frag shader with no errors");
		}
	#endif
	return frag_shader;
}

Shader::Shader(const char* vert_src, const char* frag_src, bool use_shader)
{
	this->shader_program = glCreateProgram();
	auto vert_shader = this->compileVertShader(vert_src);
	auto frag_shader = this->compileFragShader(frag_src);
	glAttachShader(this->shader_program, vert_shader);
	glAttachShader(this->shader_program, frag_shader);
	glLinkProgram(this->shader_program);

	// check if linking was successful
	#ifdef DEBUG
		int isSuccessful;
		char info[1024];
		glGetProgramiv(this->shader_program, GL_LINK_STATUS, &isSuccessful);
		if(!isSuccessful)
		{
			glGetProgramInfoLog(this->shader_program, 1024, nullptr, info);
			string info_str(info);
			shader_debug.log(info);
		}
		else
		{
			shader_debug.log("Linked shader program with no errors");
		}
	#endif

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	if(use_shader)
	{
		#ifdef DEBUG
			shader_debug.log("Using this shader");
		#endif
		this->useShader();
	}
}

void Shader::useShader()
{
	glUseProgram(shader_program);
}