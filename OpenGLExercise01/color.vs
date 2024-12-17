#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

out vec3 LightingColor;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	
	vec3 Position=vec3(model*vec4(aPos,1.0f));
	vec3 Normal=mat3(transpose(inverse(model)))*aNormal;

	float ambientStrength=0.1f;
	vec3 ambient=ambientStrength*lightColor;

	vec3 norm=normalize(Normal);
	vec3 lightDir=normalize(lightPos-Position);
	float diff=max(0.0f,dot(lightDir,norm));
	vec3 diffuse=diff*lightColor;

	float specularStrength=1.0f;
	vec3 viewDir=normalize(viewPos-Position);
	vec3 reflectDir=normalize(reflect(-lightDir,norm));
	float spec=pow(max(0.0f,dot(viewDir,reflectDir)),32);
	vec3 specular=specularStrength*spec*lightColor;
	
	LightingColor=ambient+diffuse+specular;
}