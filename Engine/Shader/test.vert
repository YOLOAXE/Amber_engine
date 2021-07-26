#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() 
{
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
	fragColor = vec3(0.0, 0.0, 0.0);
	fragTexCoord = vec2(0.0, 0.0);
}