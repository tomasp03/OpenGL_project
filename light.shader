#shader vertex
#version 460 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * model * vec4(aPos, 1.0f);
}

#shader fragment
#version 460 core

out vec4 FragColor;
uniform vec4 u_lightColor;



void main()
{
	FragColor = u_lightColor;
}