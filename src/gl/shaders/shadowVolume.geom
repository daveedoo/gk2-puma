#version 450 core

layout (lines_adjacency) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform vec3 lightPos;

in int facingLight[];

void main ()
{
	// The third and fourth vertices are only used to check whether the edge is between a lit and an unlit face
	if (facingLight[2] == facingLight[3]) return;

	// extrude the vertices 0 and 1 in the direction the light is shining towards
	vec4 v0 = gl_in[0].gl_Position;
	vec4 v1 = gl_in[1].gl_Position;

	vec3 dir1 = normalize(v0.xyz - lightPos);
	vec3 dir2 = normalize(v1.xyz - lightPos);

	vec4 v0e = v0 + vec4(dir1, 0.0) * 1000.0;
	vec4 v1e = v1 + vec4(dir2, 0.0) * 1000.0;

	// Emit all four vertices in the correct order
	gl_Position = projMatrix * viewMatrix * v0e;
	EmitVertex();

	gl_Position = projMatrix * viewMatrix * v1e;
	EmitVertex();

	gl_Position = projMatrix * viewMatrix * v0;
	EmitVertex();

	gl_Position = projMatrix * viewMatrix * v1;
	EmitVertex();

	EndPrimitive();
}