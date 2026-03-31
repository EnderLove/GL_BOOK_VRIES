#version 330 core 
out vec4 FragColor;

//in vec3 ourColor;
in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform sampler2D texture1; // Here we pass the texture
uniform sampler2D texture2;
uniform float alphaBlend;

void main(){
    float ambientStrength = 0.1;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), alphaBlend) * vec4(result, 1.0);
}


