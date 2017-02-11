#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoordinate;

out vec3 outColor;
out vec2 outTexCoordinate;
  
uniform mat4 inWorldTransform;

void main()
{
    outColor = inColor;
    outTexCoordinate = vec2(inTexCoordinate.x, 1.0 - inTexCoordinate.y);
    gl_Position = inWorldTransform * vec4(inPosition, 1.0f);
} 