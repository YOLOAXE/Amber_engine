#version 450
#extension GL_EXT_nonuniform_qualifier : enable

float PI = 3.1415926535897932384626433832795f;

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
	vec3 albedo;
	vec2 offset;
	float metallic;
	float hdr;
	float normal;
	float ao;
	uint albedoMap;
	uint normalMap;
	uint metallicMap;
	uint hdrMap;
	uint aoMap;
	uint light;
} ubm[];

layout(set = 4, binding = 0) uniform UniformBufferLight
{
	vec3 position;
    vec3 lightColor;
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

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 WorldPos;
layout(location = 2) in vec3 Normal;
layout (location = 3) in vec3 inViewVec;

layout(location = 0) out vec4 outColor;

void main()
{	
	float ambientStrength = 0.1;
	float specularStrength = 0.8;

    vec3 ambient = ambientStrength * ubl[0].lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(ubl[0].position - WorldPos); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * ubl[0].lightColor;

	vec3 viewDir = normalize(ubc.camPos - WorldPos);
	vec3 reflectDir = reflect(-lightDir, norm);  

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * ubl[0].lightColor;  

    vec3 result = (ambient + diffuse + specular) * ubm[index.material].albedo;
	outColor = vec4(result, 1.0);
}