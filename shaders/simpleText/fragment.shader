#version 150

in vec2 var_texcoord;

uniform sampler2D tex;
uniform int c; // character
uniform vec3 color;

out vec4 outColor;

void main()
{
	if (var_texcoord.x < 0.0 || var_texcoord.y < 0.0 || var_texcoord.x > 1.0 || var_texcoord.y > 1.0)
	{
		outColor = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else
	{
		vec2 charCoord;

		charCoord.x = (c & 0x0F) + var_texcoord.x;
		charCoord.y = ((c >> 4) & 0x0F) + var_texcoord.y;
		charCoord /= 16.0;

		vec4 texCol = texture(tex, charCoord);
	    outColor = vec4(color, texCol.x);
	}
}