#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout (binding = 0) uniform UBO 
{
	mat4 depthMVP;
} ubl;

layout(binding = 2) uniform UniformBufferObject 
{
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo[];

layout(push_constant) uniform PushConstants
{
    uint ubo;
	uint material;
} index;

out gl_PerVertex 
{
    vec4 gl_Position;   
};
 
void main()
{
	gl_Position = ubl.depthMVP * ubo[index.ubo].model * vec4(inPosition, 1.0);
}