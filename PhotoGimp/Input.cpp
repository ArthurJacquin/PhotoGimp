#pragma once
#include "Input.h"
#include "Vertex.h"
#include "UI.h"
#include <iostream>
#include <vector>

extern int width, height;
extern std::vector<Vertex> vertices;
extern std::vector<Vertex> tabMenuFormeVertices;
extern std::vector<Vertex> tabMenuFenetreVertices;
extern bool closeFigure;
extern UI button;

bool canCreatePoint = false;

bool clickMenuForme = false;
bool clickMenuFenetre = false;
bool clickMenuRemplissage = false;
int start = 0;

std::vector<float> color = { 1.f, 1.f, 1.f };


void SetEndAndStartDraw(int start)
{
	std::cerr << "start before : " << start << std::endl;

	if (clickMenuFenetre == true)
	{
		start = vertices.size();
		std::cerr << "start after : " << start << std::endl;
	}
}
void Input::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{ 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (xpos < 100)
		{
			if (ypos <= height/3)
			{
				clickMenuForme = true;
				closeFigure = false;
				canCreatePoint = true;

				std::cerr << " I clicked on tabMenuForme" << std::endl;
			}
			else if (ypos > height / 3 && ypos <= height - height / 3)
			{
				canCreatePoint = true;
				closeFigure = false;

				clickMenuForme = false;
				clickMenuFenetre = true;

				color = { 1.0, 0.0, 0.0 };
				std::cerr << " I clicked on tabMenuFenetre" << std::endl;
			}
			else if (ypos > height - height / 3.f && ypos <= height)
			{
				std::cerr << "prendre le pot de peinture" << std::endl;
				std::cerr << " I clicked on tabMenuRemplissage" << std::endl;
			}
		}


		if (xpos > 100 )
		{
			if (canCreatePoint == true)
			{
				Vertex newPoint = Vertex(-1.0f + 2 * xpos / width, 1.0f - 2 * ypos / height, color[0], color[1], color[2]);
				vertices.push_back(newPoint);
				//std::cerr << "Cursor Position at :" << newPoint.x << " , " << newPoint.y << std::endl;
				//std::cerr << "vertices size:" << vertices.size() << std::endl;
			}
		}

	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		if (vertices.empty() == false)
		{
			vertices.pop_back();
		}
		
		//std::cerr << "Right Click Pressed -> vertices size : "<< vertices.size() << std::endl;
	}
}

void Input::cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		std::cout << "entered window" << std::endl;
	}
	else
	{
		std::cout << "leave window" << std::endl;
	}
}

void Input::keyboard_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		closeFigure = true;
		canCreatePoint = false;
		tabMenuFormeVertices = vertices;
		start = vertices.size();

		std::cerr << "start after : " << start << std::endl;
		//SetEndAndStartDraw(start);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		vertices.clear();
		//std::cerr << "clear vertices size : " << vertices.size() << std::endl;
	}
}



