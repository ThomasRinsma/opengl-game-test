#version 150

#define NUM_LIGHTS 8

in vec3 var_position;
in vec3 var_normal;
in vec2 var_texcoord;

uniform sampler2D tex;
uniform mat4 m; // model
uniform mat4 v; // view
uniform mat4 p; // projection

out vec4 outColor;

vec3 sceneAmbient = vec3(0.2, 0.2, 0.2);

struct matData
{
	vec3 spec;
	vec3 ambient;
	float shininess;
};

matData mat = matData(
	vec3(1.0, 1.0, 1.0),
	vec3(0.2, 0.2, 0.2),
	5.0);

struct lightData
{
	bool enabled;

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

uniform lightData light[NUM_LIGHTS];



void main()
{
	vec3 normalDir = normalize(var_normal);
	vec3 viewDir = normalize(vec3(inverse(v) * vec4(vec3(0.0), 1.0)) - var_position);

	vec3 texColor = vec3(texture(tex, var_texcoord));
	vec3 ambientColor = sceneAmbient * mat.ambient * texColor;
	vec3 diffuseColor = vec3(0.0);
	vec3 specularColor = vec3(0.0);

	for (int i = 0; i != NUM_LIGHTS; ++i)
	{
		// If this light is disabled, all lights after this one will be too
		if (!light[i].enabled)
			break;

		vec3 toLight = vec3(light[i].pos - var_position);
		vec3 lightDir = normalize(toLight);
		float distance = length(toLight);
		
		float attenuation = 1.0 /
			(light[i].constAtt +
			 light[i].linAtt * distance +
			 light[i].quadAtt * distance * distance);

		if (light[i].spotCutoff <= 90.0)
		{
			float clampedCos = max(0.0, dot(-lightDir, light[i].spotDir));
			if (clampedCos < cos(radians(light[i].spotCutoff)))
				attenuation = 0.0;
			else
				attenuation *= pow(clampedCos, light[i].spotExp);
		}

		diffuseColor += attenuation * vec3(light[i].color) *
			max(0.0, dot(normalDir, lightDir)) * texColor;

		if (dot(normalDir, lightDir) >= 0.0)
			specularColor += attenuation * light[i].spec * mat.spec *
				pow(max(0.0, dot(reflect(-lightDir, normalDir), viewDir)), mat.shininess);
	}

	outColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}