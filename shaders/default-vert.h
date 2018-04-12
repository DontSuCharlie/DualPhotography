#pragma once
#ifndef GLSL
#define GLSL(version, source) "#version " #version " core\n" #source
#endif

const char* vertexShaderSource = GLSL(450, 
	layout (location = 0) in vec3 pos;
	layout(location = 1) in vec2 texCoordRaw;

	out vec2 texCoord;
	
	void main()
	{
		gl_Position = vec4(pos, 1.0);
		texCoord = texCoordRaw;
	}
);