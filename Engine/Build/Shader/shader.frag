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
	uint light;
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

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 Color;
layout(location = 3) in vec3 WorldPos;

layout(location = 0) out vec4 outColor;

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor, float range)
{
    // diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(ubc.camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // simple attenuation
    float max_distance = 1.5;
    float distance = length(lightPos - fragPos);
    float attenuation = range / (distance * distance);
    
    diffuse *= attenuation;
    specular *= attenuation;
    
    return diffuse + specular;
}

void main()
{	
	vec3 color = texture(texSampler[ubm[index.material].albedoMap], fragTexCoord).rgb * ubm[index.material].albedo;
	vec3 ambiantWolrdLight = color*0.001f;
    vec3 lighting = vec3(0.0);
    for(int i = 0; i < ubd.maxLight; i++)
	{
        lighting += BlinnPhong(normalize(Normal), WorldPos, ubl[i].position, ubl[i].lightColor,ubl[i].range);
	}
    color *= lighting;
	color += ambiantWolrdLight;
    color = pow(color, vec3(1.0/ubd.gamma));
    outColor = vec4(color, 1.0);
}