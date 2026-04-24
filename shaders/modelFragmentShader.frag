/*
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords); 
}
*/

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_diffuse4;
    sampler2D texture_diffuse5;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_specular3;
};

uniform Material material;

void main()
{   
    // Combine diffuse textures
    vec4 diffuse = texture(material.texture_diffuse1, TexCoords);
    //diffuse += texture(material.texture_diffuse2, TexCoords);
    //diffuse += texture(material.texture_diffuse3, TexCoords);
    //diffuse += texture(material.texture_diffuse4, TexCoords);

    // Specular as a mask
    //vec4 specular = texture(material.texture_specular1, TexCoords);

    FragColor =  diffuse;
}


