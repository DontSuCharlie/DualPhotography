#pragma once
#ifndef GLSL
#define GLSL(version, source) "#version " #version " core\n" #source
#endif

const char* vertexShaderSource = GLSL(450, 
	layout (location = 0) in vec3 pos;
	
	void main()
	{
		gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	}
);