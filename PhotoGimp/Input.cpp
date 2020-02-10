#pragma once
#include "Input.h"
#include "Vertex.h"
#include "UI.h"
#include <iostream>
#include <vector>
#include "Fenetrage.h"

extern int width, height;
extern std::vector<Vertex> vertices;
extern std::vector<int> shapesSizes;
extern std::vector<Vertex> tabMenuFormeVertices;
extern std::vector<Vertex> tabMenuFenetreVertices;
extern UI button;

bool canCreatePoint = false;

bool clickMenuForme = false;
bool clickMenuFenetre = false;
bool clickMenuRemplissage = false;

std::vector<float> color = { 1.f, 1.f, 1.f };

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
				canCreatePoint = true;
				clickMenuFenetre = false;

				color = { 1.0, 1.0, 1.0 };
				std::cerr << " I clicked on tabMenuForme" << std::endl;
			}
			else if (ypos > height / 3 && ypos <= height - height / 3)
			{
				canCreatePoint = true;

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

				if (clickMenuForme == true)
				{
					tabMenuFormeVertices.push_back(newPoint);

					std::cerr << "Point Forme : " << newPoint << std::endl;
				}
				else if (clickMenuFenetre == true)
				{
					tabMenuFenetreVertices.push_back(newPoint);
					std::cerr << "Point Vertices : " << newPoint << std::endl;
				}
			}
		}

	}
	if (button == GLFW_KEY_BACKSPACE && action == GLFW_PRESS)
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
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && canCreatePoint)
	{
		canCreatePoint = false;

		int sumVerticesInShapes = 0;
		for (int i = 0; i < shapesSizes.size(); ++i)
			sumVerticesInShapes += shapesSizes[i];

		shapesSizes.push_back(vertices.size() - sumVerticesInShapes);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		vertices.clear();
		shapesSizes.clear();
		tabMenuFormeVertices.clear();
		tabMenuFenetreVertices.clear();
		std::cerr << "clear vertices size : " << vertices.size() << std::endl;
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		std::cerr << "Press F To pay respect" << std::endl;

		vertices.clear();
		vertices = Fenetrage(tabMenuFormeVertices, tabMenuFenetreVertices);
		shapesSizes.clear();
		shapesSizes.push_back(vertices.size());

		for(int i = 0; i < vertices.size(); i++)
			std::cerr << vertices[i] << std::endl;
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		Vertex v = intersection(vertices[0], vertices[1], vertices[2], vertices[3]);
		vertices.push_back(v);
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		/*Vertex a(0, 0, 1, 1, 1);
		Vertex b(0, 1, 1, 1, 1);
		Vertex c(1, 0, 1, 1, 1);
		Vertex d(1, 1, 1, 1, 1);*/
		std::cout << coupe(vertices[0], vertices[1], vertices[2], vertices[3]);
	}
}



