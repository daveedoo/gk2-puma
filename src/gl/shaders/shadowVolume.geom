#version 450 core

layout (lines_adjacency) in;
layout (triangle_strip, max_vertices = 4) out;
//layout (line_strip, max_vertices = 2) out;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform vec3 lightPos;

in int facingLight[];
out vec4 color;

void main ()
{
	vec3 normal1 = cross(gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[2].gl_Position.xyz);
	vec3 normal2 = -cross(gl_in[0].gl_Position.xyz - gl_in[3].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[3].gl_Position.xyz);
	vec3 vecToLight1 = normalize(lightPos - gl_in[2].gl_Position.xyz);
	vec3 vecToLight2 = normalize(lightPos - gl_in[3].gl_Position.xyz);
	bool facingLight1 = dot(normal1, vecToLight1) > 0.0;
	bool facingLight2 = dot(normal2, vecToLight2) > 0.0;
	// The third and fourth vertices are only used to check whether the edge is between a lit and an unlit face
	if (facingLight1 == facingLight2) return;

	// extrude the vertices 0 and 1 in the direction the light is shining towards
	vec4 v0 = gl_in[0].gl_Position;
	vec4 v1 = gl_in[1].gl_Position;

//	color = vec4(1.0, 0.0, 0.0, 1.0);
//
//	gl_Position = projMatrix * viewMatrix * v0;
//	EmitVertex();
//
//	gl_Position = projMatrix * viewMatrix * v1;
//	EmitVertex();
//
//	return;

	vec3 dir1 = normalize(v0.xyz - lightPos);
	vec3 dir2 = normalize(v1.xyz - lightPos);

	vec4 v0e = v0 + vec4(dir1, 0.0) * 1000.0;
	vec4 v1e = v1 + vec4(dir2, 0.0) * 1000.0;

	color = vec4(0.0, 0.0, 0.0, 1.0);

	// Emit all four vertices in the correct order
	if (facingLight1) 
	{
		gl_Position = projMatrix * viewMatrix * v0e;
		EmitVertex();

		gl_Position = projMatrix * viewMatrix * v1e;
		EmitVertex();

		gl_Position = projMatrix * viewMatrix * v0;
		EmitVertex();

		gl_Position = projMatrix * viewMatrix * v1;
		EmitVertex();
	}
	else
	{
		gl_Position = projMatrix * viewMatrix * v0;
		EmitVertex();

		gl_Position = projMatrix * viewMatrix * v1;
		EmitVertex();

		gl_Position = projMatrix * viewMatrix * v0e;
		EmitVertex();

		gl_Position = projMatrix * viewMatrix * v1e;
		EmitVertex();
	}

	EndPrimitive();
}