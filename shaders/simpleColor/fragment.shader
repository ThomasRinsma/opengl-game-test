#version 150

in vec3 fragColor;

out vec4 outColor;
uniform float trans;

void main()
{
    outColor = vec4(fragColor, trans);
}