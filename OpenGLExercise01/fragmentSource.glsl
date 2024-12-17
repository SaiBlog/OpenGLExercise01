#version 330 core		
in vec3 Normal
in vec3 lightPos;

uniform vec3 lightColor;
uniform vec3 objectColor;	

out vec4 FragColor;

void main()
{										
	FragColor = vec4(lightColor * objectColor, 1.0);
}		        