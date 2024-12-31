#version 330 core

out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main()
{
    vec3 ambient=light.ambient*texture(material.diffuse,TexCoords).rgb;

    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(0.0f,dot(lightDir,norm));
    vec3 diffuse=light.diffuse*texture(material.diffuse,TexCoords).rgb*diff;

    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(0.0f,dot(viewDir,reflectDir)),material.shininess);
    vec3 specular=light.specular*texture(material.specular,TexCoords).rgb*spec;

    float distance=length(light.position-FragPos);
    float attenuation=1.0f/(light.constant+light.linear*distance+light.quadratic*distance*distance);

    ambient*=attenuation;
    diffuse*=attenuation;
    specular*=attenuation;

    vec3 result=ambient+diffuse+specular;
    FragColor=vec4(result,1.0f);

}