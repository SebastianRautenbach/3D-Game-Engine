#version 460 core
out vec4 FragColor;

// MATERIAL SETUP ------------------------------------------------------------

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float radius;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float distance;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};


struct Cluster
{
    vec4 minPoint;
    vec4 maxPoint;
    uint count;
    uint pointLightIndices[50];
    uint spotLightIndices[50];
};


layout(std430, binding = 1) buffer clusterSSBO
{
    Cluster clusters[];
};

layout(std430, binding = 2) buffer pointLightSSBO
{
    PointLight pointLight[];
};

layout(std430, binding = 3) buffer spotLightSSBO
{
    SpotLight spotLight[];
};

uniform DirLight dirLight;
uniform Material material;

uniform float zNear;
uniform float zFar;
uniform uvec3 gridSize;
uniform uvec2 screenDimensions;


// UNiforms ------------------------------------------------------------------


in vec3 FragPos;
in vec3 Normal; 
in vec2 oTexture;

uniform vec3 camPos;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);


    uint zTile = uint((log(abs(FragPos.z) / zNear) * gridSize.z) / log(zFar / zNear));
    vec2 tileSize = screenDimensions / gridSize.xy;
    uvec3 tile = uvec3(gl_FragCoord.xy / tileSize, zTile);
    uint tileIndex =
        tile.x + (tile.y * gridSize.x) + (tile.z * gridSize.x * gridSize.y);

    uint lightCount = clusters[tileIndex].count;

    for (int i = 0; i < lightCount; ++i)
    {
        uint lightIndex = clusters[tileIndex].pointLightIndices[i];
        PointLight light = pointLight[lightIndex];
        if(length(light.position - FragPos) < light.radius)
            result += CalcPointLight(light, norm, FragPos, viewDir); 
    }

    for (int i = 0; i < lightCount; ++i)
    {
        uint lightIndex = clusters[tileIndex].spotLightIndices[i];
        SpotLight light = spotLight[lightIndex];
        if(length(light.position - FragPos) < light.distance)
            result += CalcSpotLight(light, norm, FragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);

}



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
   vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, oTexture));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, oTexture));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, oTexture));
    return (ambient + diffuse + specular);

}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, oTexture));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, oTexture));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, oTexture));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    
    float diff = max(dot(normal, lightDir), 0.0);
    
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, oTexture));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, oTexture));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, oTexture));
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular);
}