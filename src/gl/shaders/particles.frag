#version 450 core

uniform vec3 color;
uniform float maxAge;

in vec3 fragNormal;
in vec3 fragPos;
in float fragAge;

out vec4 FragColor;

void main()
{
	FragColor = vec4(color, 0.7f*(1.f - fragAge/maxAge));
}
