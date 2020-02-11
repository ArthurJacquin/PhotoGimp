#include "Remplissage.h"

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

	Vertex P1 = { xMin, yMin, 0.f, 1.f, 1.f };
	Vertex P2 = { xMax, yMax, 0.f, 1.f, 1.f };
	rect.push_back(P1);
	rect.push_back(P2);
	return rect;
}

std::vector<Vertex> GetCurrentLineFromRect(std::vector<Vertex> rect, int y)
{
	std::vector<Vertex> line;
	
	Vertex P1 = { rect[0].x, y, 0.f, 1.f, 1.f };
	Vertex P2 = { rect[1].x, y, 0.f, 1.f, 1.f };

	line.push_back(P1);
	line.push_back(P2);

	return line;
}

std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> Line, std::vector<Vertex> Poly)
{
	std::vector<Vertex> intersections;

	//TODO : conversion du poly en liste de CoteActif
	//récupérer ces côtés actifs et leur valeur pour trouver les intersection de la ligne
	//intersections.push_back(intersection(Line[0].x, Line[0].y, Poly));

	return intersections;
}

std::vector<Vertex> Remplissage(std::vector<Vertex> Poly)
{
	std::vector<Vertex> polyFilled;

	std::vector<Vertex> rect = RectEG(Poly);
	std::vector<Vertex> currLine;
	std::vector<Vertex> intersections;
	Vertex P = { 0.f, 0.f, 0.f, 1.f, 1.f };
	int nbIntersections = 0;
	int currIntersection = 0;

	int xMin, xMax, currX, currY;

	for (currY = rect[0].y; currY < rect[1].y; ++currY)
	{
		currLine = GetCurrentLineFromRect(rect, currY); //récupère la ligne courante
		intersections = FindIntersectionWithLine(currLine, Poly); //récupère les intersections entre la ligne et le poly
		nbIntersections = intersections.size(); //nombre d'intersections
		currIntersection = 0; //id de l'intersection courante

		while (currIntersection < nbIntersections) //tant qu'on a pas parcouru toutes les intersections
		{
			xMin = intersections[currIntersection].x; //on récupère le x min de la zone entre les deux intersections
			++currIntersection; //on passe à l'intersection suivante

			if (currIntersection != nbIntersections) //si on est pas dans la dernière zone
			{
				xMax = intersections[currIntersection].x; //on récupère le x max de la zone entre les deux intersections

				for (currX = xMin; currX < xMax; ++currX) //on parcoure tous les points à l'ordonnée currY qui sont dans la zone
				{
					P.x = currX;
					P.y = currY;
					polyFilled.push_back(P); //on ajoute ce point à la liste finale des points à dessiner
				}
				++currIntersection; //on passe à l'intersection suivante
			}
		}
		intersections.clear();
		currLine.clear();
	}

	return polyFilled;
}
