#version 450 core

uniform vec3 color;
uniform vec3 lightPos;

in vec3 fragNormal;
in vec3 fragPos;

out vec4 FragColor;

void main()
{
	float kA = 0.1f;
	vec3 ambient = kA * vec3(1.0f);	// assume white light

	float kD = 0.5f;
	vec3 lightDir = normalize(lightPos - fragPos);  
	float diff = kD * max(dot(fragNormal, lightDir), 0.0f);
	vec3 diffuse = diff * vec3(1.0f);

	vec3 result = (ambient + diffuse) * color;

	FragColor = vec4(result, 1.f);
}
