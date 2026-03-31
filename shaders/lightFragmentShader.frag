#version 330

uniform vec3 objectColor; // Color of the boject 
uniform vec3 lightColor;  // Color of the light source
uniform vec3 lightPos;    // Position of the light source 

out vec4 FragColor;
in  vec3 fragPos;
in  vec3 normal;

void main(){
    float ambientStrength = 0.1;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
  
    //float diff = max(dot(lightDir, norm), 0.0);
    float diff = dot(lightDir, norm);
    vec3 diffuse = diff * lightColor;


    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = vec4(result, 1.0);
}

