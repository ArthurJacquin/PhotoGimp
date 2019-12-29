#include "Input.h"
#pragma once 
#include "Vertex.h"
#pragma once
#include <iostream>
#pragma once
#include <vector>

extern std::vector<Vertex> vertices;

void Input::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{ 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cerr << "Cursor Position at :" << xpos << " - " << ypos << std::endl;

		Vertex newPoint = Vertex(xpos, ypos, 1, 1, 1);
		vertices.push_back(newPoint);
		std::cerr << "vertices size:" << vertices.size() << std::endl;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		if (vertices.empty() == false)
		{
			vertices.pop_back();
		}
		
		std::cerr << "Right Click Pressed -> vertices size : "<< vertices.size() << std::endl;
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
		std::cerr << "TODO: fermer la forme " << std::endl;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		vertices.clear();
		std::cerr << "clear vertices size : " << vertices.size() << std::endl;
	}
}
