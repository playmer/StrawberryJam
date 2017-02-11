#version 330 core
in vec3 inColor;
in vec2 inTexCoordinate;

out vec4 outColor;

// Texture samplers
uniform sampler2D inTexture;

void main()
{
	// Linearly interpolate between both textures (second texture is only slightly combined)
	outColor = texture(inTexture, inTexCoordinate);
}