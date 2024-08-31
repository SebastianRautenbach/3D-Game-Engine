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


#define MAX_POINT_LIGHTS 100

uniform DirLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_POINT_LIGHTS];

uniform int ammount_of_pointlights;
uniform int ammount_of_spotlights;

uniform Material material;

// UNiforms ------------------------------------------------------------------


in vec3 FragPos;
in vec3 Normal; 
in vec2 oTexture;

uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec3 camFront;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    
    
     for(int i = 0; i < ammount_of_pointlights; i++)
     { 
        if(length(pointLights[i].position - FragPos) < pointLights[i].radius)
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 
     }

    for(int i = 0; i < ammount_of_spotlights; i++) {
        if(length(spotLights[i].position - FragPos) < spotLights[i].distance)
            result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
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