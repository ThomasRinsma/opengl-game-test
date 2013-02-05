#version 150

in vec3 position;
in vec2 texcoord;

uniform mat4 mvp;
// TODO: color, uniform 'c'

out vec2 var_texcoord;

void main()
{
	var_texcoord = texcoord;

	gl_Position = mvp * vec4(position, 1.0);
}