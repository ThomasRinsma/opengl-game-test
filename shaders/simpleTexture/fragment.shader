#version 150

in vec3 var_normal;
in vec3 var_lightDir;
in vec2 var_texcoord;

uniform sampler2D tex;

out vec4 outColor;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

void main()
{
	vec3 normNormal = normalize(var_normal);
	vec3 normLightDir = normalize(var_lightDir);

	float diff = max(0.0f, dot(normNormal, normLightDir));

	vec3 texColor = vec3(texture(tex, var_texcoord));
    vec3 diffuseColor = texColor * diff;
	vec3 ambientColor = vec3(0.0f, 0.0f, 0.0f);
	//vec3 specularColor = vec3(1.0f) * pow(max(dot(reflect, light), 0.0f), 8.0f);

    
    outColor = vec4(diffuseColor, 1.0f);
    //outColor = vec4(diffuseColor + ambientColor + specularColor, 1.0f);

}