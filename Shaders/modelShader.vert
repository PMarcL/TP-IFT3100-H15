#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
	Normal = normal;
	FragPos = vec3(model * vec4(position, 1.0));
}
