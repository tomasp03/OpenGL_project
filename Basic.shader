#shader vertex
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 aNorm;

out vec3 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 camMatrix;

// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;


void main()
{
	gl_Position = camMatrix * model * vec4(aPos, 1.0f);
	crntPos = vec3(model * vec4(aPos, 1.0f));
	texCoord = aTex;
	Normal = mat3(transpose(inverse(model))) * aNorm;
}


#shader fragment
#version 460 core

// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec4 u_lightColor;
uniform vec3 u_lightPos;

void main()
{
	float ambient = 0.2f;
	vec3 normal = normalize(vec3(Normal.x, Normal.y, Normal.z));
	vec3 lightDirection = normalize(u_lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	FragColor = texture(tex0, texCoord) * u_lightColor * (diffuse + ambient);

}