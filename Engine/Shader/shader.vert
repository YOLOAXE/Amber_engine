#version 450
#extension GL_EXT_nonuniform_qualifier : enable

layout(set = 0, binding = 0) uniform UniformBufferCamera 
{
	vec3 camPos;
    mat4 view;
    mat4 proj;
} ubc;

layout(set = 1, binding = 0) uniform sampler2D texSampler[];

layout(set = 2, binding = 0) uniform UniformBufferModel
{
    mat4 model;
} ubo[];


layout(set = 3, binding = 0) uniform UniformBufferMaterial
{
	vec3  albedo;
	vec2 offset;
	float metallic;
    float roughness;	
	float normal;
	float ao;
	uint albedoMap;
	uint normalMap;
	uint metallicMap;
    uint roughnessMap;
	uint aoMap;
	uint castShadow;
} ubm[];

layout(set = 4, binding = 0) uniform UniformBufferLight
{
	vec3 position;
    vec3 lightColor;
	float range;
	uint status;//DirLight = 0 ; PointLight = 1 ; SpotLight = 2
} ubl[];

layout(set = 5, binding = 0) uniform UniformBufferDiver
{
	uint maxLight;
	float u_time;
	float gamma;
}ubd;

layout (set = 6, binding = 0) uniform samplerCube samplerCubeMap;

layout(push_constant) uniform PushConstants
{
    uint ubo;
	uint material;
} index;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 inTexCoord;
layout(location = 4) in vec3 inTangent;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 Normal;
layout(location = 2) out vec3 Color;
layout(location = 3) out vec3 WorldPos;
layout(location = 4) out mat3 TBN;

void main() 
{
	fragTexCoord = inTexCoord * ubm[index.material].offset;
	WorldPos = vec3(ubo[index.ubo].model * vec4(inPosition, 1.0));
	Normal = mat3(transpose(ubo[index.ubo].model)) * inNormal;
	Color = inColor;
	vec3 T = normalize(vec3(ubo[index.ubo].model * vec4(inTangent, 0.0)));
	vec3 N = normalize(vec3(ubo[index.ubo].model * vec4(inNormal, 0.0)));	
	T = normalize(T - dot(T, N) * N);
	TBN = transpose(mat3(T, cross(N, T), N));
    gl_Position = ubc.proj * ubc.view * ubo[index.ubo].model * vec4(inPosition, 1.0);
}