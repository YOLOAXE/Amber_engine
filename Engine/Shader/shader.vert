#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout(binding = 0, set = 0) uniform UniformBufferCamera 
{
	vec3 camPos;
    mat4 view;
    mat4 proj;
} ubc;

layout(binding = 0, set = 1) uniform sampler2D texSampler[];

layout(binding = 0, set = 2) uniform UniformBufferModel
{
    mat4 model;
} ubo[];


layout(binding = 0, set = 3) uniform UniformBufferMaterial
{
	vec3  albedo;
	vec2 offset;
	float metallic;//shiniess
	float hdr;
	float normal;
	float ao;
	uint albedoMap;
	uint normalMap;
	uint metallicMap;
	uint hdrMap;
	uint aoMap;
	bool light;
} ubm[];

layout(binding = 0,set = 4) uniform UniformBufferLight
{
	vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 
	uint status;//DirLight = 0 ; PointLight = 1 ; SpotLight = 2
	mat4 LightSpaceMatrix;
} ubl[];

layout(binding = 0, set = 5) uniform UniformBufferDiver
{
	uint maxLight;
	float u_time;
	float gamma;
}ubd;

layout(push_constant) uniform PushConstants
{
    uint ubo;
	uint material;
} index;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 WorldPos;
layout(location = 2) out vec3 NormalPos;
layout (location = 3) out vec3 outViewVec;

void main() 
{
	fragTexCoord = inTexCoord * ubm[index.material].offset;
	WorldPos = vec3(ubo[index.ubo].model * vec4(inPosition, 1.0));
	NormalPos = mat3(transpose(inverse(ubo[index.ubo].model))) * inNormal;

	vec4 pos = ubo[index.ubo].model * vec4(inPosition, 1.0);
    outViewVec = -pos.xyz;			
	
    gl_Position = ubc.proj * ubc.view * ubo[index.ubo].model * vec4(inPosition, 1.0);
}