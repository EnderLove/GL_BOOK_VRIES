#version 330

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture1;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor;

void main(){
    //vec3 ambient = lightColor * material.ambient;
    vec3 ambient = vec3(1.0) * material.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = lightColor * (diff * material.diffuse);
    vec3 diffuse = vec3(1.0) * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = lightColor * (spec * material.specular);
    vec3 specular = vec3(1.0) * (spec * material.specular);

    vec3 result = (ambient + diffuse + specular);

    FragColor = texture(texture1, texCoord) * vec4(result, 1.0);
}


