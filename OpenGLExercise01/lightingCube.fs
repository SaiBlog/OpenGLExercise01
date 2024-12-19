#version 330 core
out vec4 FragColor;

struct LightColor{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform LightColor light;

void main()
{
    FragColor = vec4(light.ambient.x+light.diffuse.x+light.specular.x,light.ambient.y+light.diffuse.y+light.specular.y,light.ambient.z+light.diffuse.z+light.specular.z,1.0f); 
}