#include "Cursor.h"
#pragma once 
#include "Vertex.h"
#pragma once
#include <iostream>

void Cursor::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)// Vertex* posClick)
{ 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cerr << "Cursor Position at (" << xpos << " : " << ypos << std::endl;
	}
}

void Cursor::cursorEnterCallback(GLFWwindow* window, int entered)
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
