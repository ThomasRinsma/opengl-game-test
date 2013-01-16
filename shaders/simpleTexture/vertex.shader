#version 150

in vec3 position;
in vec3 normal;
in vec2 texcoord;

uniform mat4 m; // model
uniform mat4 v; // view
uniform mat4 p; // projection
uniform mat3 n; // transpose of inverse of model

out vec3 var_position;
out vec3 var_normal;
out vec2 var_texcoord;

void main()
{
	var_position = vec3(m * vec4(position, 1.0f));
	var_normal = normalize(n * normal);
	var_texcoord = texcoord;

	gl_Position = p * v * m * vec4(position, 1.0f);	
}