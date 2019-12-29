#pragma once
#include <GLFW/glfw3.h>
#pragma once
#include "Vertex.h"

class Cursor
{
public:
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);// Vertex cursor, Vertex* posClick);
	static void cursorEnterCallback(GLFWwindow* window, int entered);
};