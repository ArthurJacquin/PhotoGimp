#pragma once
#include <GLFW/glfw3.h>
#pragma once
#include "Vertex.h"

class cursor
{
public:
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods, Vertex cursor, Vertex* posClick);


};