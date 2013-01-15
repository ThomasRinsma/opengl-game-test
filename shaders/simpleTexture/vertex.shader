#version 150

in vec3 position;
in vec3 normal;
in vec2 texcoord;

uniform mat4 m; // model
uniform mat4 v; // view
uniform mat4 p; // projection
uniform mat3 n; // transpose of inverse of model

out vec3 var_normal;
out vec3 var_lightDir;
out vec2 var_texcoord;

vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);

void main()
{
	vec4 pos4 = (v * m) * vec4(position, 1.0f);
	vec3 pos3 = pos4.xyz / pos4.w;

	var_normal = n * normal;
	var_lightDir = normalize(lightPos - pos3);
	var_texcoord = texcoord;

	gl_Position = p * v * m * vec4(position, 1.0f);
}