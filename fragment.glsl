#version 330 core

in vec3 FragPos; 
in vec3 Normal; 
in vec2 TexCoord;

out vec4 FragColor; 

uniform vec3 viewPos;
uniform vec3 lightPos; 
uniform vec3 lightColor; 
uniform vec3 objectColor;
uniform sampler2D texture1; 

void main(void) 
{
	vec3 ambientLight = vec3(0.7f, 0.7f, 0.7f);
	vec3 ambient = ambientLight * lightColor;

	vec3 normalVector = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diffuseLight = max(dot(normalVector, lightDir), 0.0f); 
	vec3 diffuse = diffuseLight * lightColor; 

	int shininess = 128; 
	vec3 viewDir = normalize(viewPos - FragPos); 
	vec3 reflectDir = reflect(-lightDir, normalVector);  
	float specularLight = max(dot(viewDir, reflectDir), 0.0f); 
	specularLight = pow(specularLight, shininess); 
	vec3 specular = specularLight * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	vec4 lightcolor = vec4 (result, 1.0f);

	FragColor = texture(texture1, TexCoord) * lightcolor;
}