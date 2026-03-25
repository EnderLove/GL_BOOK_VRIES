#version 330 core 

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D floorTexture;

void main(){
    FragColor = texture(floorTexture, texCoord) * vec4(0.5f, 0.2f, 0.5f, 1.0f);
}


