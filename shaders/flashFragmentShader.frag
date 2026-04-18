#version 330

struct Light{
    vec4 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float cutOff; // Light aperture
};
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

uniform Light    light;
uniform Material material;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float time;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor; // Final fragment color of the pixel
                
void main(){

    float distance = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord)) * vec3(0.3);

    vec3 norm = normalize(normal);
    
    vec3 lightDir = vec3(1.0);
    if (light.position.w == 0.0){
        lightDir = normalize(vec3(light.position));
    } else if (light.position.w == 1.0){
        lightDir = normalize(vec3(light.position) - fragPos);
    }

    float emissionIntensity = dot(norm, lightDir);
    vec3 emission;
    if (emissionIntensity < 0.0 && texture(material.specular, texCoord).r == 0.0){
        emission = vec3(1.0) * (-emissionIntensity * vec3(texture(material.emission, texCoord + vec2(0.0, time))));
    } else {
        emission = vec3(0.0);
    }

    float theta = dot(lightDir, normalize(-light.direction));
    vec3 result; 
    if (theta > light.cutOff){
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCoord)));

        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoord)));

        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;

        result = (ambient + diffuse + specular + emission);

    } else {
        result = (ambient);
    }
        FragColor = vec4(result, 1.0);
}


