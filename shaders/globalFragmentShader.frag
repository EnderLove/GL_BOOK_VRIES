#version 330

#define NR_POINT_LIGHTS 4

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct FlashLight{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

uniform Material material;
uniform DirLight dirLight;
uniform FlashLight flashLight;

uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 calcDirLight  (DirLight   light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcFlashLight(FlashLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform vec3 viewPos;
uniform float time;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor;

// TODO:REFACTOR CALCULATIONS
void main(){
    // Properties
    vec3 norm = normalize(normal); 
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 result = vec3(0.0);

    // Directional lighting
    //result = calcDirLight(dirLight, norm, viewDir);

    // Point lights 
    for (int i = 0; i < NR_POINT_LIGHTS; i++){
        result += calcPointLight(pointLights[i], norm, fragPos, viewDir);
    }

    // Flash light
    result += calcFlashLight(flashLight, norm, fragPos, viewDir); 

    FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);

    // Diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);

    // Combine results 
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse , texCoord)) * vec3(0.3);
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse , texCoord));
    vec3 specular = light.specular * vec3(texture(material.specular, texCoord));

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

    // Combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse , texCoord)) * vec3(0.3);
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse , texCoord));
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoord))); 

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 calcFlashLight(FlashLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(vec3(light.position) - fragPos); 

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Diffuse shading 
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading 
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(0.0) * vec3(texture(material.diffuse , texCoord));
    vec3 diffuse  = light.diffuse  *         vec3(texture(material.diffuse , texCoord));
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoord))); 

    //ambient  *= attenuation;
    diffuse  *= intensity * attenuation;
    specular *= intensity * attenuation;

    return (ambient + diffuse + specular);
}

