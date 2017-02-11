#version 330 core
in vec3 inColor;
in vec2 inTexCoordinate;

out vec4 outColor;

uniform sampler2D inTexture;

void main()
{
	outColor = texture(inTexture, inTexCoordinate);
}