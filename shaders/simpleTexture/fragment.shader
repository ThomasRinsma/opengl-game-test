#version 150

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

uniform lightData light0;
uniform lightData light1;
uniform lightData light2;

void main()
{
	vec3 normalDir = normalize(var_normal);
	vec3 viewDir = normalize(vec3(inverse(v) * vec4(vec3(0.0), 1.0)) - var_position);

	vec3 texColor = vec3(texture(tex, var_texcoord));
	vec3 ambientColor = sceneAmbient * mat.ambient * texColor;
	vec3 diffuseColor = vec3(0.0);
	vec3 specularColor = vec3(0.0);

	vec3 toLight0 = vec3(light0.pos - var_position);
	vec3 toLight1 = vec3(light1.pos - var_position);
	vec3 toLight2 = vec3(light2.pos - var_position);

	float distance0 = length(toLight0);
	float distance1 = length(toLight1);
	float distance2 = length(toLight2);

	vec3 lightDir0 = normalize(toLight0);
	vec3 lightDir1 = normalize(toLight1);
	vec3 lightDir2 = normalize(toLight2);

	float attenuation0 = 1.0 /
		(light0.constAtt +
		 light0.linAtt * distance0 +
		 light0.quadAtt * distance0 * distance0);

	float attenuation1 = 1.0 /
		(light1.constAtt +
		 light1.linAtt * distance1 +
		 light1.quadAtt * distance1 * distance1);

	float attenuation2 = 1.0 /
		(light2.constAtt +
		 light2.linAtt * distance2 +
		 light2.quadAtt * distance2 * distance2);

	if (light0.spotCutoff <= 90.0)
	{
		float clampedCos = max(0.0, dot(-lightDir0, light0.spotDir));
		if (clampedCos < cos(radians(light0.spotCutoff)))
			attenuation0 = 0.0;
		else
			attenuation0 *= pow(clampedCos, light0.spotExp);
	}

	if (light1.spotCutoff <= 90.0)
	{
		float clampedCos = max(0.0, dot(-lightDir1, light0.spotDir));
		if (clampedCos < cos(radians(light1.spotCutoff)))
			attenuation1 = 0.0;
		else
			attenuation1 *= pow(clampedCos, light1.spotExp);
	}

	if (light2.spotCutoff <= 90.0)
	{
		float clampedCos = max(0.0, dot(-lightDir2, light2.spotDir));
		if (clampedCos < cos(radians(light2.spotCutoff)))
			attenuation2 = 0.0;
		else
			attenuation2 *= pow(clampedCos, light2.spotExp);
	}


	diffuseColor += attenuation0 * vec3(light0.color) *
		max(0.0, dot(normalDir, lightDir0)) * texColor;

	diffuseColor += attenuation1 * vec3(light1.color) *
		max(0.0, dot(normalDir, lightDir1)) * texColor;

	diffuseColor += attenuation2 * vec3(light2.color) *
		max(0.0, dot(normalDir, lightDir2)) * texColor;

	
	if (dot(normalDir, lightDir0) >= 0.0)
		specularColor += attenuation0 * light0.spec * mat.spec *
			pow(max(0.0, dot(reflect(-lightDir0, normalDir), viewDir)), mat.shininess);

	if (dot(normalDir, lightDir1) >= 0.0)
		specularColor += attenuation1 * light1.spec * mat.spec *
			pow(max(0.0, dot(reflect(-lightDir1, normalDir), viewDir)), mat.shininess);

	if (dot(normalDir, lightDir2) >= 0.0)
		specularColor += attenuation2 * light2.spec * mat.spec *
			pow(max(0.0, dot(reflect(-lightDir2, normalDir), viewDir)), mat.shininess);


	outColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}