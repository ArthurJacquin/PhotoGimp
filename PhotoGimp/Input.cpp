#pragma once
#include "Input.h"
#include "Vertex.h"
#include "UI.h"
#include <iostream>
#include <vector>
#include "Fenetrage.h"
#include "Remplissage.h"
#include "Color.h"
#include "imgui.h"

extern int width, height;
extern std::vector<Vertex> vertices;
extern std::vector<Vertex> verticesToDraw;
extern std::vector<int> shapesSizes;
extern std::vector<Vertex> tabMenuFormeVertices;
extern std::vector<Vertex> tabMenuFenetreVertices;
extern UI button;

extern std::vector<Vertex> rectangleEnglobant;

bool canCreatePoint = false;

extern bool clickMenuForme;
extern bool clickMenuFenetre;
extern bool clickMenuEnter;
extern bool clickMenuRemplissage;
extern bool clickDelete;

extern Color choosedColor;

void Input::waitForBool()
{
	if (clickMenuForme == true)
	{
		clickMenuForme = true;
		canCreatePoint = true;
		clickMenuEnter = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickDelete = false;
	}
	else if (clickMenuFenetre == true)
	{
		clickMenuForme = false;
		canCreatePoint = true;
		clickMenuEnter = false;
		clickMenuFenetre = true;
		clickMenuRemplissage = false;
		clickDelete = false;
	}
	else if (clickMenuRemplissage == true)
	{
		clickMenuForme = false;
		canCreatePoint = true;
		clickMenuEnter = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = true;
		clickDelete = false;
	}
	else if (clickMenuEnter)
	{
		clickMenuForme = false;
		canCreatePoint = false;
		clickMenuEnter = true;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickDelete = false;
	}
	else if (clickDelete == true)
	{
		clickMenuForme = false;
		canCreatePoint = false;
		clickMenuEnter = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickDelete = true;
	}
}

void Input::deleteVertex()
{
	vertices.clear();
	shapesSizes.clear();
	tabMenuFormeVertices.clear();
	tabMenuFenetreVertices.clear();
}

void Input::decoupeForme()
{
	if (tabMenuFenetreVertices.size() > 0)
	{
		vertices.clear();
		vertices = Fenetrage(tabMenuFormeVertices, tabMenuFenetreVertices);
		shapesSizes.clear();
		shapesSizes.push_back(vertices.size());

		for (int i = 0; i < vertices.size(); i++)
			std::cerr << vertices[i] << std::endl;
	}
}

void Input::remplirForme()
{
	//vertices = RectEG(vertices);
	rectangleEnglobant = RectEG(vertices);
	for (int i = 0; i < rectangleEnglobant.size(); ++i)
	{
		vertices.push_back(rectangleEnglobant[i]);
	}
	verticesToDraw = Remplissage(vertices);
	/*for (int i = 0; i < verticesToDraw.size(); ++i)
	{
		vertices.push_back(verticesToDraw[i]);
	}*/
	
}

void Input::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (canCreatePoint == true)
		{
			if (xpos > 220)
			{
				Vertex newPoint = Vertex(-1.0f + 2 * xpos / width, 1.0f - 2 * ypos / height, choosedColor.x, choosedColor.y, choosedColor.z);
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

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		if (vertices.empty() == false)
		{
			vertices.pop_back();
		}
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
		int sumVerticesInShapes = 0;
		for (int i = 0; i < shapesSizes.size(); ++i)
			sumVerticesInShapes += shapesSizes[i];

		shapesSizes.push_back(vertices.size() - sumVerticesInShapes);

		canCreatePoint = false;
		clickMenuForme = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickMenuEnter = false;
		clickDelete = false;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		deleteVertex();
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



