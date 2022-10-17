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

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 Color;
layout(location = 3) in vec3 WorldPos;
layout(location = 4) in mat3 TBN;

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

float DistributionGGX(vec3 N, vec3 H, float a)
{
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
	
    float denom  = (NdotH*NdotH * (a2 - 1.0) + 1.0);
    denom        = PI * denom * denom;
    return a2 / denom;
}

float GeometrySchlickGGX(float NdotV, float k)
{
    return NdotV / (NdotV * (1.0 - k) + k);
}
  
float GeometrySmith(vec3 N, vec3 V, vec3 L, float k)
{
    return GeometrySchlickGGX(max(dot(N, V), 0.0), k) * GeometrySchlickGGX(max(dot(N, L), 0.0), k);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main()
{	
	vec3 color = texture(texSampler[ubm[index.material].albedoMap], fragTexCoord).rgb * ubm[index.material].albedo; 
    vec3 ambient = vec3(0.0003) * color * ubm[index.material].ao * texture(texSampler[ubm[index.material].aoMap], fragTexCoord).rgb;
    vec3 N = texture(texSampler[ubm[index.material].normalMap], fragTexCoord).rgb * ubm[index.material].normal;
    N = normalize(TBN * fma(N, vec3(2.0), vec3(-1.0)));
    //N = normalize(Normal);

    //outColor = vec4(N, 1.0);
    //return;

    vec3 V = normalize(-ubc.camPos - WorldPos);

    vec3 F0 = vec3(0.04); 
    vec3 metallic = texture(texSampler[ubm[index.material].metallicMap], fragTexCoord).rgb * ubm[index.material].metallic;
    float roughness = texture(texSampler[ubm[index.material].roughnessMap], fragTexCoord).r * ubm[index.material].roughness;
    F0 = mix(F0, color, metallic);

     // reflectance equation
     vec3 Lo = vec3(0.0);
     for(int i = 0; i < ubd.maxLight; i++)
	 {
        vec3 L = normalize(ubl[i].position - WorldPos);
        vec3 H = normalize(V + L);
        float distance    = length(ubl[i].position - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = ubl[i].lightColor * attenuation * ubl[i].range;
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, roughness);        
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular     = numerator / denominator;  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * color / PI + specular) * radiance * NdotL; 
     }
     color = ambient + Lo;
	    
     color = color / (color + vec3(1.0));
     color = pow(color, vec3(1.0/2.2));  
   
     outColor = vec4(color, 1.0);
}

/*
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
*/