#pragma once
#ifndef GLSL
#define GLSL(version, source) "#version " #version " core\n" #source
#endif

const char* fragmentShaderSource = GLSL(450, 
	out vec4 outColor;
	
	void main()
	{
		outColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
);