#version 330 core
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
};

struct SpotLight {
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
};


#define NR_POINT_LIGHTS 4

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;


uniform Material material;

// UNiforms ------------------------------------------------------------------


in vec3 FragPos;
in vec3 Normal; 
in vec2 oTexture;

uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    // POINT LIGHT ------------------------------------------------------------

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
    light.quadratic * (distance * distance));

    // BASIC LIGHT ------------------------------------------------------------

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, oTexture));

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(light.position - FragPos));
    
    // DIFFUSE ---------------------------------------------

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, oTexture)); 

    // SPECULAR ---------------------------------------------------------------

    float specularStrength = 0.5;
    
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, oTexture));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;


    FragColor = vec4(result, 1.0);



}