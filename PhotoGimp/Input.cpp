#pragma once
#include "Input.h"
#include "Vertex.h"
#include "UI.h"
#include <iostream>
#include <vector>
#include "Fenetrage.h"
#include "Color.h"
#include "imgui.h"

# define M_PI           3.14159265358979323846  /* pi */

extern int width, height;
extern std::vector<Vertex> vertices;
extern std::vector<int> shapesSizes;
extern std::vector<Vertex> tabMenuFormeVertices;
extern std::vector<int> idFisrtVertexForme;
extern std::vector<Vertex> tabMenuFenetreVertices;
extern std::vector<int> idFisrtVertexFenetre;
extern UI button;

bool canCreatePoint = false;

extern bool clickMenuForme;
extern bool clickMenuFenetre;
extern bool clickMenuDecoupe;
extern bool clickMenuRemplissage;
extern bool clickDelete;
extern bool clickCercle;

extern Color choosedColor;

void Input::waitForBool()
{
	if (clickMenuForme == true)
	{
		clickMenuForme = true;
		canCreatePoint = true;
		clickMenuDecoupe = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickDelete = false;
		clickCercle = false;
	}
	if (clickCercle == true)
	{
		clickCercle = true;
		canCreatePoint = true;
		clickMenuForme = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickDelete = false;
	}
	else if (clickMenuFenetre == true)
	{
		clickMenuForme = false;
		canCreatePoint = true;
		clickMenuDecoupe = false;
		clickMenuFenetre = true;
		clickMenuRemplissage = false;
		clickDelete = false;
		clickCercle = false;
	}
	else if (clickMenuRemplissage == true)
	{
		clickMenuForme = false;
		canCreatePoint = true;
		clickMenuDecoupe = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = true;
		clickDelete = false;
	}
	else if (clickMenuDecoupe)
	{
		clickMenuForme = false;
		canCreatePoint = false;
		clickMenuDecoupe = true;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickDelete = false;
		clickCercle = false;
	}
	else if (clickDelete == true)
	{
		clickMenuForme = false;
		canCreatePoint = false;
		clickMenuDecoupe = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickDelete = true;
		clickCercle = false;
	}
}

void Input::deleteVertex()
{
	vertices.clear();
	shapesSizes.clear();

	tabMenuFormeVertices.clear();
	idFisrtVertexForme.clear();

	tabMenuFenetreVertices.clear();
	idFisrtVertexFenetre.clear();
}

void Input::decoupeForme()
{
	if (tabMenuFenetreVertices.size() > 0)
	{
		std::vector<Vertex> newVertices;
		std::vector<int> newIdForme;

		shapesSizes.clear();
		int currentFenetre = 0;

		for (int i = 0; i < idFisrtVertexFenetre.size(); ++i)
		{
			std::vector<Vertex> fenetre;

			if (currentFenetre == idFisrtVertexFenetre.size() - 1)
			{
				//Recuperation d'une des fenetres
				for (int j = idFisrtVertexFenetre[currentFenetre]; j < tabMenuFenetreVertices.size(); ++j)
				{
					fenetre.push_back(tabMenuFenetreVertices[j]);
				}
			}
			else 
			{
				//Recuperation d'une des fenetres
				for (int j = idFisrtVertexFenetre[currentFenetre]; j < idFisrtVertexFenetre[currentFenetre + 1]; ++j)
				{
					fenetre.push_back(tabMenuFenetreVertices[j]);
				}
			}
			
			int currentForme = 0;

			for (int j = 0; j < idFisrtVertexForme.size(); ++j)
			{
				std::vector<Vertex> forme;
				

				if (currentForme == idFisrtVertexForme.size() - 1)
				{
					//Recuperation d'une des formes
					for (int k = idFisrtVertexForme[currentForme]; k < tabMenuFormeVertices.size(); ++k)
					{
						forme.push_back(tabMenuFormeVertices[k]);
					}
				}
				else
				{
					//Recuperation d'une des formes
					for (int k = idFisrtVertexForme[currentForme]; k < idFisrtVertexForme[currentForme + 1]; ++k)
					{
						forme.push_back(tabMenuFormeVertices[k]);
					}
				}
				
				//Fenetrage de cette forme
				std::vector<Vertex> newForme = Fenetrage(forme, fenetre);

				//Enregistrement de la forme découpé
				for (int k = 0; k < newForme.size(); ++k)
				{
					newVertices.push_back(newForme[k]);
				}

				//Update idForme
				if (newIdForme.size() == 0)
					newIdForme.push_back(0);
				else
					newIdForme.push_back(shapesSizes.back() + newIdForme.back());

				shapesSizes.push_back(newForme.size());

				currentForme++;
			}

			currentFenetre++;
		}

		//Remplassement des anciens vertices
		vertices = newVertices;
		tabMenuFormeVertices = newVertices;
		idFisrtVertexForme = newIdForme;

		//Clear fenetres
		tabMenuFenetreVertices.clear();
		idFisrtVertexFenetre.clear();

		for (int i = 0; i < vertices.size(); i++)
			std::cerr << vertices[i] << std::endl;
	}
}

void Input::drawCircle(Vertex center, Vertex FirstPoint, int nbPoints)
{
	float radius = sqrt(pow(FirstPoint.x - center.x, 2) + pow(FirstPoint.y - center.y, 2));

	vertices.pop_back();
	vertices.pop_back();
	
	tabMenuFormeVertices.pop_back();
	tabMenuFormeVertices.pop_back();

	for (int i = 0; i < nbPoints; ++i)
	{
		Vertex newPoint(0, 0, choosedColor.x, choosedColor.y, choosedColor.z);

		float theta = 2.0f * M_PI * float(i) / float(nbPoints);
		float x = radius * cosf(theta);//calculate the x component 
		float y = radius * sinf(theta);//calculate the y component 

		newPoint.x = x + center.x;
		newPoint.y = y + center.y;

		tabMenuFormeVertices.push_back(newPoint);
		vertices.push_back(newPoint);
	}

	if (idFisrtVertexForme.size() == 0)
		idFisrtVertexForme.push_back(0);
	else
		idFisrtVertexForme.push_back(shapesSizes.back() + idFisrtVertexForme.back());

	shapesSizes.push_back(nbPoints);
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

				if (clickMenuForme == true || clickCercle == true)
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
}

void Input::keyboard_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && canCreatePoint)
	{
		if (clickMenuForme)
		{
			if (idFisrtVertexForme.size() == 0)
				idFisrtVertexForme.push_back(0);
			else
				idFisrtVertexForme.push_back(shapesSizes.back() + idFisrtVertexForme.back());

			int sumVerticesInShapes = 0;
			for (int i = 0; i < shapesSizes.size(); ++i)
				sumVerticesInShapes += shapesSizes[i];

			shapesSizes.push_back(vertices.size() - sumVerticesInShapes);
		}
		else if (clickMenuFenetre)
		{
			if (idFisrtVertexFenetre.size() == 0)
				idFisrtVertexFenetre.push_back(0);
			else
				idFisrtVertexFenetre.push_back(shapesSizes.back() + idFisrtVertexFenetre.back());

			int sumVerticesInShapes = 0;
			for (int i = 0; i < shapesSizes.size(); ++i)
				sumVerticesInShapes += shapesSizes[i];

			shapesSizes.push_back(vertices.size() - sumVerticesInShapes);
		}
		else if (clickCercle)
		{
			int sumVerticesInShapes = 0;
			for (int i = 0; i < shapesSizes.size(); ++i)
				sumVerticesInShapes += shapesSizes[i];

			if (vertices.size() - sumVerticesInShapes == 2);
			{
				drawCircle(vertices[vertices.size() - 2], vertices.back(), 45);
			}

		}

		canCreatePoint = false;
		clickMenuForme = false;
		clickMenuFenetre = false;
		clickMenuRemplissage = false;
		clickMenuDecoupe = false;
		clickDelete = false;
		clickCercle = false;
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		int sumVerticesInShapes = 0;
		for (int i = 0; i < shapesSizes.size(); ++i)
			sumVerticesInShapes += shapesSizes[i];

		if(vertices.size() - sumVerticesInShapes == 2);
		{
			drawCircle(vertices[vertices.size() - 2], vertices.back(), 45);

			canCreatePoint = false;
			clickMenuForme = false;
			clickMenuFenetre = false;
			clickMenuRemplissage = false;
			clickMenuDecoupe = false;
			//clickDelete = false;
		}
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		deleteVertex();
	}

	//if (key == GLFW_KEY_F && action == GLFW_PRESS)
	//{
	//	std::cerr << "Press F To pay respect" << std::endl;

	//	vertices.clear();
	//	vertices = Fenetrage(tabMenuFormeVertices, tabMenuFenetreVertices);
	//	shapesSizes.clear();
	//	shapesSizes.push_back(vertices.size());
	//	idFisrtVertexFenetre.clear();

	//	for(int i = 0; i < vertices.size(); i++)
	//		std::cerr << vertices[i] << std::endl;
	//}

	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		Vertex v = intersection(vertices[0], vertices[1], vertices[2], vertices[3]);
		vertices.push_back(v);
	}

	//if (key == GLFW_KEY_C && action == GLFW_PRESS)
	//{
	//	/*Vertex a(0, 0, 1, 1, 1);
	//	Vertex b(0, 1, 1, 1, 1);
	//	Vertex c(1, 0, 1, 1, 1);
	//	Vertex d(1, 1, 1, 1, 1);*/
	//	std::cout << coupe(vertices[0], vertices[1], vertices[2], vertices[3]);
	//}
}



