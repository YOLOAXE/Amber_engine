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
	float metallic;
	float roughness;
	float normal;
	float ao;
	uint albedoMap;
	uint normalMap;
	uint metallicMap;
	uint roughnessMap;
	uint aoMap;
	bool light;
} ubm[];

layout(binding = 3) uniform UniformBufferLight
{
	vec3 lightPositions;
	vec3 lightColors;
	float distance;
} ubl[];

layout(binding = 4) uniform UniformBufferDiver
{
	vec3 camPos;
	uint maxLight;
	float u_time;
	float gamma;
}ubd;

layout(push_constant) uniform PushConstants
{
    uint ubo;
	uint material;
} index;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 WorldPos;
layout(location = 2) in vec3 NormalPos;

layout(location = 0) out vec4 outColor;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

//Calculer le rapport entre la réflexion spéculaire et la réflexion diffuse, ou combien la surface réfléchit la lumière par rapport à combien elle réfracte la lumière.
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) 
{
	return F0 + (max(vec3(1.0f - roughness), F0) - F0) * pow(1.0f - cosTheta, 5.0f);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a		 = roughness*roughness;
	float a2	 = a*a;
	float NdotH  = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;
	
	float num	= a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom		= PI * denom * denom;
	
	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0f);
    float k = (r*r) / 8.0f;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2  = GeometrySchlickGGX(NdotV, roughness);
	float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
	return ggx1 * ggx2;
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

    return normalize(TBN * tangentNormal);
}

void main() 
{
    vec3 albedo     = pow(texture(texSampler[ubm[index.material].albedoMap], fragTexCoord).rgb, vec3(ubd.gamma)) * ubm[index.material].albedo;
    vec3 normal     = getNormalFromMap() * ubm[index.material].normal;
    float metallic  = texture(texSampler[ubm[index.material].metallicMap], fragTexCoord).r * ubm[index.material].metallic;
    float roughness = texture(texSampler[ubm[index.material].roughnessMap], fragTexCoord).r * ubm[index.material].roughness;
    float ao        = texture(texSampler[ubm[index.material].aoMap], fragTexCoord).r * ubm[index.material].ao;

	vec3 N = normal;
    vec3 V = normalize(ubd.camPos - WorldPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
	           
    // Equation de reflectivite
    vec3 L0 = vec3(0.0);
	if(ubm[index.material].light)
	{
		for(int i = 1; i < ubd.maxLight ; i++) 
		{
			// calculer le rayonnement par lumiere
			vec3 L = normalize(ubl[i].lightPositions.xyz - WorldPos);
			vec3 H = normalize(V + L);

			float distance    = length(ubl[i].lightPositions.xyz - WorldPos);
			float attenuation = 1.0 / (distance * distance);
			vec3 radiance     = ubl[i].lightColors * attenuation * ubl[i].distance;
        
			// cook-torrance reflection http://www.codinglabs.net/article_physically_based_rendering_cook_torrance.aspx
			float NDF = DistributionGGX(N, H, roughness);        
			float G   = GeometrySmith(N, V, L, roughness);      
			vec3 F    = fresnelSchlick(max(dot(H, V), 0.0f), F0);       
        
			vec3 kS = F;
			vec3 kD = vec3(1.0f) - kS;
			kD *= 1.0f - metallic;	  
	        
			vec3 numerator    = NDF * G * F;
			float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
			vec3 specular     = numerator / max(denominator, 0.001);  
	            
			// Ajouter au rayonnement sortant L0
			float NdotL = max(dot(N, L), 0.0f);                
	        L0 += (kD * albedo / PI + specular) * radiance * NdotL; 
		}   
	}
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + L0;
	
	// HDR tonemapping
    color = color / (color + vec3(1.0));
	// gamma correct
    color = pow(color, vec3(1.0f/ubd.gamma));
   
    outColor = vec4(color, 1.0);
}
