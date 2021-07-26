#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo[];

layout(binding = 1) uniform sampler2D texSampler[];

layout(binding = 2) uniform UniformBufferMaterial
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

layout(binding = 3) uniform UniformBufferLight
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

layout(binding = 4) uniform UniformBufferDiver
{
	vec3 camPos;
	uint maxLight;
	float u_time;
	float gamma;
	uint indShadowLight;
}ubd;

layout(push_constant) uniform PushConstants
{
    uint ubo;
	uint material;
} index;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 WorldPos;
layout(location = 2) out vec3 NormalPos;
layout (location = 3) out vec3 outViewVec;
layout (location = 4) out vec3 outLightVec;
layout (location = 5) out vec4 outShadowCoord;

const mat4 biasMat = mat4( 
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.5, 0.5, 0.0, 1.0 );

void main() 
{
	fragTexCoord = inTexCoord * ubm[index.material].offset;
	WorldPos = vec3(ubo[index.ubo].model * vec4(inPosition, 1.0));
	NormalPos = mat3(transpose(inverse(ubo[index.ubo].model))) * inColor;

	vec4 pos = ubo[index.ubo].model * vec4(inPosition, 1.0);
	outLightVec = normalize(ubl[ubd.indShadowLight].position - inPosition);
    outViewVec = -pos.xyz;			
	outShadowCoord = ( biasMat * ubl[ubd.indShadowLight].LightSpaceMatrix * ubo[index.ubo].model ) * vec4(inPosition, 1.0);
	
    gl_Position = ubo[index.ubo].proj * ubo[index.ubo].view * ubo[index.ubo].model * vec4(inPosition, 1.0);
}