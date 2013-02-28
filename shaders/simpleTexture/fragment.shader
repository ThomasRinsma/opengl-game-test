#version 150

in vec3 var_position;
in vec3 var_normal;
in vec2 var_texcoord;

uniform sampler2D tex;
uniform mat4 m; // model
uniform mat4 v; // view
uniform mat4 p; // projection

out vec4 outColor;

vec3 sceneAmbient = vec3(0.2f, 0.2f, 0.2f);

struct matData
{
	vec3 spec;
	vec3 ambient;
	float shininess;
};

matData mat = matData(
	vec3(1.0f, 1.0f, 1.0f),
	vec3(0.2f, 0.2f, 0.2f),
	5.0f);

struct lightData
{
	vec3 pos;
	vec3 color;
	vec3 spec;
	float constAtt;
	float linAtt;
	float quadAtt;

	vec3 spotDir;
	float spotCutoff;
	float spotExp;
};

uniform lightData light;


void main()
{
	
	vec3 texColor = vec3(texture(tex, var_texcoord));


	vec3 normalDir = normalize(var_normal);
	vec3 viewDir = normalize(
		vec3(inverse(v) * vec4(vec3(0.0f), 1.0f)) - var_position);

	vec3 toLight = vec3(light.pos - var_position);
	float distance = length(toLight);
	vec3 lightDir = normalize(toLight);

	float attenuation = 1.0 /
		(light.constAtt +
		 light.linAtt * distance +
		 light.quadAtt * distance * distance);

	if (light.spotCutoff <= 90.0f)
	{
		float clampedCos = max(0.0f, dot(-lightDir, light.spotDir));
		if (clampedCos < cos(radians(light.spotCutoff)))
			attenuation = 0.0f;
		else
			attenuation *= pow(clampedCos, light.spotExp);
	}

	vec3 ambientColor = sceneAmbient * mat.ambient * texColor;

	
	vec3 diffuseColor = attenuation * vec3(light.color) *
		max(0.0f, dot(normalDir, lightDir)) * texColor;

	vec3 specularColor;
	if (dot(normalDir, lightDir) < 0.0f)
		specularColor = vec3(0.0f, 0.0f, 0.0f);
	else
		specularColor = attenuation * light.spec * mat.spec *
			pow(max(0.0f, dot(reflect(-lightDir, normalDir), viewDir)), mat.shininess);


	outColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}