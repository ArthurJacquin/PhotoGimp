#include "Cursor.h"
#pragma once 
#include "Vertex.h"

void cursor::mouse_button_callback(GLFWwindow * window, int button, int action, int mods, Vertex cursor, Vertex* posClick)
{ 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &cursor.x, &cursor.y);
	}
}
