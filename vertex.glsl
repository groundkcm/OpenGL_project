#version 330 core

layout (location = 0) in vec3 vPos; 
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 

void main(void)
{
	gl_Position = projection * view *  model* vec4(vPos, 1.0f); 
	FragPos = vec3(model * vec4(vPos, 1.0f));
	Normal = vec3(model * vec4(vNormal,1.0f));
	TexCoord = vTexCoord; 
}