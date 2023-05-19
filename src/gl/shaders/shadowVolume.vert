#version 450 core

layout(location = 0) in vec3 pos;
layout(location	= 1) in vec3 normal;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform vec3 lightPos;

out int facingLight;	// 0 = facing away, 1 = facing towards

void main()
{
	gl_Position = worldMatrix * vec4(pos, 1.0);
	vec4 vectorToLight = vec4(lightPos, 1.0) - gl_Position;
	// world matrix is only rotation and translation, so we can use it to transform the normal
	vec4 globalNormal = worldMatrix * vec4(normal, 1.0f);
	facingLight = int(dot(vectorToLight, globalNormal) > 0.0);
}
