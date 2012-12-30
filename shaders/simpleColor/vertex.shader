#version 150

in vec3 position;
in vec3 color;

out vec3 fragColor;

uniform mat4 mvp;

void main()
{
	fragColor = color;
	gl_Position = mvp * vec4(position, 1.0);
}