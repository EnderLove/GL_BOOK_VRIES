#version 330 core 
out vec4 FragColor;

//in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1; // Here we pass the texture
uniform sampler2D texture2;
uniform float alphaBlend;

void main(){
    //FragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0);
    //FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2) * vec4(ourColor, 1.0);
    //FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord * vec2(-1.0, 1.0)), 0.2);
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), alphaBlend);
}


