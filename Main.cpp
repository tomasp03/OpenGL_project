#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<sstream>
#include<math.h>
#include <time.h>  

#include"WindowClass.h"
#include"TimerClass.h"
#include"Texture.h"
#include"Camera.h"
#include"Lighting.h"
#include"TexturedCube.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<stb/stb_image.h>

#define WINDOW_HEIGHT 1500
#define WINDOW_WIDTH 1900
#define FOV 80.0f

unsigned int samples = 8;

GLfloat verticesLight[] =
{
	//Possitive Z
	-0.5f, -0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 //Negative Z		
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f 
};

GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
						 
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
						 
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
						 
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
						 
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
						 
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f
};

GLuint indices[] =
{
	0, 1, 2, //front
	1, 2, 3,
	4, 5, 6, //back
	5, 6, 7,
	0, 1, 4, //left
	4, 5, 1,
	2, 3, 6, //right
	6, 7, 3,
	1, 3, 5, //up
	5, 7, 3,
	0, 2, 4, //low
	4, 6, 2
};

glm::vec3 cubePositions[] = 
{
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


int main()
{
	srand(time(NULL));
	int rotNum[] =
	{
		rand()%130 + 20,
		rand()%130 + 20,
		rand()%130 + 20,
		rand()%130 + 20,
		rand()%130 + 20,
		rand()%130 + 20,
		rand()%130 + 20,
		rand()%130 + 20,
		rand()%130 + 20
	};
	WindowClass mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "hello");
	TexturedCube bedna(vertices, sizeof(vertices), "Basic.shader", "container.jpg");
	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), FOV);
	Lighting light(verticesLight, sizeof(verticesLight), indices, sizeof(indices), "light.shader");
	light.SetPos(glm::vec3(0.0f, 0.0f, -9.0f));


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	mainWindow.Vsync(ON);
	double dt;
	float speed = 5.0f;
	while (!mainWindow.ShouldClose())
	{
		light.SetColor(glm::vec4(abs(sin(glfwGetTime()*speed)), abs(cos(glfwGetTime() * speed)), abs(cos(glfwGetTime() * speed + 1.0f)), 1.0f));

		TimerClass time(&dt);
		camera.Inputs(mainWindow.window, dt);

		bedna.Light(light.GetPos(), light.GetColor());

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		light.Draw(camera);

		for (int i = 0; i < 9; i++)
		{
			bedna.SetPos(cubePositions[i]);
			bedna.Draw(camera);
		}

		mainWindow.SwapBuffers();
		mainWindow.PollEvents();
		mainWindow.ShowFPS();
	}

	mainWindow.~WindowClass();
	bedna.~TexturedCube();
	light.~Lighting();
}