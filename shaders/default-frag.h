#pragma once
#ifndef GLSL
#define GLSL(version, source) "#version " #version " core\n" #source
#endif

const char* fragmentShaderSource = GLSL(450, 
	out vec4 outColor;

	in vec2 texCoord;

	uniform sampler2D textureData;
	
	void main()
	{
		outColor = texture(textureData, texCoord);
	}
);