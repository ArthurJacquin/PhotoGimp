#include "Remplissage.h"

std::vector<Vertex> RectEG(std::vector<Vertex> Poly)
{
	std::cout << "Hello from RectEG" << std::endl;

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

	Vertex P1 = Vertex(xMin, yMin, 0.f, 1.f, 1.f);
	Vertex P2 = Vertex(xMin, yMax, 0.f, 1.f, 1.f);
	Vertex P3 = Vertex(xMax, yMax, 0.f, 1.f, 1.f);
	Vertex P4 = Vertex(xMax, yMin, 0.f, 1.f, 1.f);

	rect.push_back(P1);
	rect.push_back(P2);
	rect.push_back(P3);
	rect.push_back(P4);

	std::cout << "Point 1 du rectangle englobant : " << P1 << std::endl;
	std::cout << "Point 2 du rectangle englobant : " << P2 << std::endl;
	std::cout << "Point 3 du rectangle englobant : " << P3 << std::endl;
	std::cout << "Point 4 du rectangle englobant : " << P4 << std::endl;

	return rect;
}

std::vector<Vertex> GetCurrentLineFromRect(std::vector<Vertex> rect, double y)
{
	std::cout << "Find current line at : " << y << std::endl;

	std::vector<Vertex> line;
	
	Vertex P1 = Vertex(rect[0].x, y, 0.f, 1.f, 1.f);
	Vertex P2 = Vertex(rect[2].x, y, 0.f, 1.f, 1.f);

	line.push_back(P1);
	line.push_back(P2);

	std::cout << "Point 1 de la ligne courante : " << P1 << std::endl;
	std::cout << "Point 2 de la ligne courante : " << P2 << std::endl;

	return line;
}

std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> rect, std::vector<Vertex> Line, std::vector<Vertex> Poly)
{
	std::cout << "Hello from FindIntersectionWithLine" << std::endl;

	std::vector<Vertex> intersections;

	Vertex P1 = Line[0]; //premier point de la ligne de balayage 
	Vertex P2 = Line[1]; //deuxi�me point de la ligne de balayage
	Vertex P3 = Vertex(0.f, 0.f, 0.f, 1.f, 1.f); //premier point du c�t� 
	Vertex P4 = Vertex(0.f, 0.f, 0.f, 1.f, 1.f); //deuxi�me point du c�t�

	int j = 0;
	for (int i = 0; i < Poly.size(); ++i)
	{
		j = i + 1;
		if (i == Poly.size() - 1)
		{
			j = 0;
		}

		//mettre � jour P3 et P4
		P3.x = Poly[i].x;
		P3.y = Poly[i].y;
		P3.CastToInt(P3);
		P4.x = Poly[j].x;
		P4.y = Poly[j].y;
		P4.CastToInt(P4);
		Vertex intersectionPoint = intersection(P1, P2, P3, P4); //intersection entre la ligne et le c�t� du poly

		std::cout << "Intersection en y : " << Line[0].y << " => " << intersectionPoint << std::endl;

		if(intersectionPoint.x < rect[0].x 
		|| intersectionPoint.x > rect[2].x
		|| intersectionPoint.y < rect[0].y
		|| intersectionPoint.y > rect[2].y) 
		{
			continue;
		}

		intersections.push_back(intersectionPoint); //ajouter l'intersection � la liste des intersections
		std::cout << "Intersection valid������e" << std::endl;
	}

	return intersections;
}

std::vector<Vertex> DebugRemplissage(std::vector<Vertex> Poly)
{
	std::cout << "Hello from Debug Remplissage" << std::endl;

	std::vector<Vertex> verticesToDraw; //stockage des vertices � draw

	std::vector<Vertex> rect = RectEG(Poly); //r�cup�ration du rectangle englobant
	std::vector<Vertex> currLine; //stockage de la ligne actuelle
	std::vector<Vertex> intersections; //stockage des intersections par ligne
	int nbIntersections = 0; //nombre d'intersections par ligne

	double currY;

	for (currY = rect[0].y; currY < rect[2].y; currY += 0.01f) //it�ration de ligne en ligne
	{
		currLine = GetCurrentLineFromRect(rect, currY); //r�cup�re la ligne courante via la coordonn�e en double
		intersections = FindIntersectionWithLine(rect, currLine, Poly); //r�cup�re les intersections entre la ligne et le poly
		nbIntersections = intersections.size(); //nombre d'intersections
		for (int i = 0; i < nbIntersections; ++i)
		{
			verticesToDraw.push_back(intersections[i]);
		}
	}

	return verticesToDraw;
}
