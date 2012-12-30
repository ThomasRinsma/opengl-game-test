#version 150

in vec3 position;
in vec2 texcoord;

out vec2 texCoord;

uniform mat4 mvp;

void main()
{
	texCoord = texcoord;
	gl_Position = mvp * vec4(position, 1.0);
}