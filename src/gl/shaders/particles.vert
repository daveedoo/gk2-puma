#version 450 core

layout(location = 0) in vec3 pos;
layout(location	= 1) in vec3 normal;
layout(location = 2) in float age;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec3 fragNormal;
out vec3 fragPos;
out float fragAge;

void main()
{
	vec4 gPos = worldMatrix * vec4(pos, 1.0);
	fragPos = gPos.xyz;
	gl_Position = projMatrix * viewMatrix * gPos;

	//world matrix is only rotations and translations, so we can simplify:
	fragNormal = normalize(worldMatrix * vec4(normal, 0.0)).xyz;

	fragAge = age;
}
