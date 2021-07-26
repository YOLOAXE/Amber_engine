#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

float PI = 3.1415926535897932384626433832795f;

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

layout (binding = 5) uniform sampler2D shadowMap;

layout(push_constant) uniform PushConstants
{
    uint ubo;
	uint material;
} index;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 WorldPos;
layout(location = 2) in vec3 NormalPos;
layout (location = 3) in vec3 inViewVec;
layout (location = 4) in vec3 inLightVec;
layout (location = 5) in vec4 inShadowCoord;

layout(location = 0) out vec4 outColor;

float textureProj(vec4 shadowCoord, vec2 off)
{
	float shadow = 1.0;
	if ( shadowCoord.z > -1.0 && shadowCoord.z < 1.0 ) 
	{
		float dist = texture( shadowMap, shadowCoord.st + off ).r;
		if ( shadowCoord.w > 0.0 && dist < shadowCoord.z ) 
		{
			shadow = 0.1;
		}
	}
	return shadow;
}

float filterPCF(vec4 sc)
{
	ivec2 texDim = textureSize(shadowMap, 0);
	float scale = 1.5;
	float dx = scale * 1.0 / float(texDim.x);
	float dy = scale * 1.0 / float(texDim.y);

	float shadowFactor = 0.0;
	int count = 0;
	int range = 1;
	
	for (int x = -range; x <= range; x++)
	{
		for (int y = -range; y <= range; y++)
		{
			shadowFactor += textureProj(sc, vec2(dx*x, dy*y));
			count++;
		}
	
	}
	return shadowFactor / count;
}

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(texSampler[ubm[index.material].normalMap], fragTexCoord).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(fragTexCoord);
    vec2 st2 = dFdy(fragTexCoord);

    vec3 N   = normalize(NormalPos);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * (tangentNormal * ubm[index.material].normal));
}

// Calcule la couleur lors de l'utilisation d'une lumière directionnelle.
vec3 CalcDirLight(int ind, vec3 viewDir, vec3 normal, vec3 specMap, vec3 diffuseMap, float shadow)
{
    vec3 lightDir = normalize(-ubl[ind].direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading PHONG
	/* 
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ubm[index.material].metallic);
	*/
	vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), ubm[index.material].metallic);
    // combine results
    vec3 ambient = ubl[ind].ambient * diffuseMap;
    vec3 diffuse = ubl[ind].diffuse * diff * diffuseMap;
    vec3 specular = ubl[ind].specular * spec * specMap;
	if(ubd.indShadowLight == ind)
	{
		return (ambient + diffuse + specular) *((shadow * diff)+ubl[ind].ambient);
	}
	else
	{
		return (ambient + diffuse + specular);
	}
}

// Calcule la couleur lors de l'utilisation d'une lumière ponctuelle.
vec3 CalcPointLight(int ind, vec3 viewDir, vec3 normal, vec3 specMap, vec3 diffuseMap)
{
    vec3 lightDir = normalize(ubl[ind].position - WorldPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), ubm[index.material].metallic);
    // attenuation
    float distance = length(ubl[ind].position - WorldPos);
    float attenuation = 1.0 / (ubl[ind].constant + ubl[ind].linear * distance + ubl[ind].quadratic * (distance * distance));    
    // combine results
    vec3 ambient = ubl[ind].ambient * diffuseMap;
    vec3 diffuse = ubl[ind].diffuse * diff * diffuseMap;
    vec3 specular = ubl[ind].specular * spec * specMap;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// Calcule la couleur lors de l'utilisation d'un spot.
vec3 CalcSpotLight(int ind, vec3 viewDir, vec3 normal, vec3 specMap, vec3 diffuseMap)
{
    vec3 lightDir = normalize(ubl[ind].position - WorldPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), ubm[index.material].metallic);
    // attenuation
    float distance = length(ubl[ind].position - WorldPos);
    float attenuation = 1.0 / (ubl[ind].constant + ubl[ind].linear * distance + ubl[ind].quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-ubl[ind].direction)); 
    float epsilon = ubl[ind].cutOff - ubl[ind].outerCutOff;
    float intensity = clamp((theta - ubl[ind].outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = ubl[ind].ambient * diffuseMap;
    vec3 diffuse = ubl[ind].diffuse * diff * diffuseMap;
    vec3 specular = ubl[ind].specular * spec * specMap;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main() //Multiple light
{	
	if(!ubm[index.material].light)
	{
		outColor = vec4(texture(texSampler[ubm[index.material].albedoMap], fragTexCoord).rgb * ubm[index.material].albedo, 1.0);
	}
	else if(ubm[index.material].hdrMap > 0)
	{
		vec3 hdrColor = texture(texSampler[ubm[index.material].hdrMap], fragTexCoord).rgb * ubm[index.material].albedo;
		vec3 mapped = vec3(1.0) - exp(-hdrColor * ubm[index.material].hdr);
		mapped = pow(mapped, vec3(1.0 / ubd.gamma));
		outColor = vec4(mapped, 1.0);
	}
	else
	{

	vec3 norm = ubm[index.material].normalMap == 0 ? normalize(NormalPos) : getNormalFromMap();
    vec3 viewDir = normalize(ubd.camPos - WorldPos);
    vec3 diffuse = pow(texture(texSampler[ubm[index.material].albedoMap], fragTexCoord).rgb * ubm[index.material].albedo,vec3(ubd.gamma));
	vec3 specular = vec3(texture(texSampler[ubm[index.material].metallicMap], fragTexCoord));
	float shadow = filterPCF(inShadowCoord / inShadowCoord.w);

    vec3 result = vec3(0.0f);
    for(int i = 1; i < ubd.maxLight ; i++) 
	{	
		if(ubl[i].status == 0)
		{
			result += CalcDirLight(i,viewDir,norm,specular,diffuse,shadow);
		}
		else if(ubl[i].status == 1)
		{
			result += CalcPointLight(i,viewDir,norm,specular,diffuse);    
		}
		else if(ubl[i].status == 2)
		{
			result += CalcSpotLight(i,viewDir,norm,specular,diffuse);
		}
	}
    
	outColor.rgb = pow(outColor.rgb, vec3(1.0/ubd.gamma));

    outColor = vec4(result, 1.0);
	}
}