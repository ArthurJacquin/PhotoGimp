#include "Remplissage.h"
#include <algorithm> 

bool sortVertex(Vertex i, Vertex j) { return (i.x < j.x); }

std::vector<Vertex> RectEG(std::vector<Vertex> Poly)
{
	std::vector<Vertex> rect;
	double yMax = 0.f;
	double yMin = 1000.0f;
	double xMax = 0.f;
	double xMin = 1000.0f;

	for (int i = 0; i < Poly.size(); ++i)
	{
		if (Poly[i].x > xMax)
			xMax = Poly[i].x;
		if (Poly[i].x < xMin)
			xMin = Poly[i].x;
		if (Poly[i].y > yMax)
			yMax = Poly[i].y;
		if (Poly[i].y < yMin)
			yMin = Poly[i].y;
	}

	Vertex P1 = Vertex(xMin - 0.05f, yMin - 0.05f, 0.f, 1.f, 1.f);
	Vertex P2 = Vertex(xMin - 0.05f, yMax + 0.05f, 0.f, 1.f, 1.f);
	Vertex P3 = Vertex(xMax + 0.05f, yMax + 0.05f, 0.f, 1.f, 1.f);
	Vertex P4 = Vertex(xMax + 0.05f, yMin - 0.05f, 0.f, 1.f, 1.f);
	 
	rect.push_back(P1);
	rect.push_back(P2);
	rect.push_back(P3);
	rect.push_back(P4);

	return rect;
}

std::vector<Vertex> GetCurrentLineFromRect(std::vector<Vertex> rect, double y)
{
	std::vector<Vertex> line;
	
	Vertex P1 = Vertex(rect[0].x, y, 0.f, 1.f, 1.f);
	Vertex P2 = Vertex(rect[2].x, y, 0.f, 1.f, 1.f);

	line.push_back(P1);
	line.push_back(P2);

	return line;
}

std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> rect, std::vector<Vertex> Line, std::vector<Vertex> Poly)
{
	std::vector<Vertex> intersections;

	Vertex P1 = Line[0]; //premier point de la ligne de balayage 
	Vertex P2 = Line[1]; //deuxième point de la ligne de balayage
	Vertex P3 = Vertex(0.f, 0.f, 0.f, 1.f, 1.f); //premier point du côté 
	Vertex P4 = Vertex(0.f, 0.f, 0.f, 1.f, 1.f); //deuxième point du côté

	int j = 0;
	for (int i = 0; i < Poly.size(); ++i)
	{
		j = i + 1;
		if (i == Poly.size() - 1)
		{
			j = 0;
		}

		//mettre à jour P3 et P4
		P3.x = Poly[i].x;
		P3.y = Poly[i].y;
		P4.x = Poly[j].x;
		P4.y = Poly[j].y;

		Vertex intersectionPoint = intersection(P1, P2, P3, P4); //intersection entre la ligne et le côté du poly

		double yMax = P3.y > P4.y ? P3.y : P4.y;
		double yMin = P3.y < P4.y ? P3.y : P4.y;

		if(intersectionPoint.x < rect[0].x 
		|| intersectionPoint.x > rect[2].x
		|| intersectionPoint.y < rect[0].y
		|| intersectionPoint.y > rect[2].y
		|| intersectionPoint.y <= yMin
		|| intersectionPoint.y >= yMax)
		{
			continue;
		}

		intersections.push_back(intersectionPoint); //ajouter l'intersection à la liste des intersections
	}
	
	std::sort(intersections.begin(), intersections.end(), sortVertex);
	return intersections;
}

std::vector<Vertex> Remplissage(std::vector<Vertex> Poly)
{
	std::cout << "Hello from Remplissage" << std::endl;

	std::vector<Vertex> verticesToDraw; //stockage des vertices à draw

	std::vector<Vertex> rect = RectEG(Poly); //récupération du rectangle englobant
	std::vector<Vertex> currLine; //stockage de la ligne actuelle
	std::vector<Vertex> intersections; //stockage des intersections par ligne
	int nbIntersections = 0; //nombre d'intersections par ligne

	double currY;

	for (currY = rect[0].y; currY < rect[2].y; currY += 0.006f) //itération de ligne en ligne
	{
		currLine = GetCurrentLineFromRect(rect, currY); //récupère la ligne courante via la coordonnée en double
		intersections = FindIntersectionWithLine(rect, currLine, Poly); //récupère les intersections entre la ligne et le poly
		nbIntersections = intersections.size(); //nombre d'intersections

		if (nbIntersections == 1 || nbIntersections % 2 != 0)
			continue;

		for (int i = 0; i < nbIntersections; ++i)
		{
			verticesToDraw.push_back(intersections[i]);
		}
	}

	return verticesToDraw;
}


