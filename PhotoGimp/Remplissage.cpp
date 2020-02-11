#include "Remplissage.h"

CoteList GetLCFromPoly(std::vector<Vertex> Poly)
{
	CoteList LC; //Liste des côtés du Poly
	int nbCote = 0;
	CoteActif previous;
	//TODO : conversion du poly en liste de CoteActif

	for (int i = 0; i < Poly.size(); ++i) //Faire la boucle à l'envers
	{
		CoteActif currCote = CoteActif();
		//Prendre deux à deux les points du poly et en déduire les valeurs du CoteActif correspondants
		//Pour N sommets il y N CoteActif
		//calculer le coeff directeur (Rappel : coeff = (y2 - y1)/(x2 - x1))
		//récupérer le y max // facile !
		//récupérer le coeff a et le mettr dans curr_x => à renommer ?? (Rappel : a = point2.x - point1.x)
		//stocker le côté qu'on vient de créer pour le donner en "next" au côté qu'on va créer ensuite
		previous = currCote;
		if (nbCote == 0) //si c'est le premier côté, on le stock à la fin de la liste
		{
			LC.AddEndList(currCote);
		}
		++nbCote;//incrémenter nbCote
	}

	//boucler la boucle des côtés en mettant le dernier côté stocké en premier de la listes

	return LC;
}

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
	
	Vertex P1 = { rect[0].x, (double)y, 0.f, 1.f, 1.f };
	Vertex P2 = { rect[1].x, (double)y, 0.f, 1.f, 1.f };

	line.push_back(P1);
	line.push_back(P2);

	return line;
}

std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> Line, std::vector<Vertex> Poly)
{
	std::vector<Vertex> intersections;

	CoteList LC = GetLCFromPoly(Poly);
	CoteActif* currCote = LC.GetFirst();
	CoteActif* last = LC.GetLast();

	Vertex P1 = Line[0]; //premier point de la ligne de balayage 
	Vertex P2 = Line[1]; //deuxième point de la ligne de balayage
	Vertex P3 = { 0.f, 0.f, 0.f, 1.f, 1.f }; //premier point du côté 
	Vertex P4 = { 0.f, 0.f, 0.f, 1.f, 1.f }; //deuxième point du côté
	
	while (currCote != last) //itérer sur la liste des côtés du poly 
	{
		//mettre à jour P3 et P4
		currCote = currCote->GetNextCote();
		intersections.push_back(intersection(P1, P2, P3, P4)); //ajouter l'intersection à la liste des intersections
	}
	
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

std::vector<CoteList> CreateSI(std::vector<Vertex> Poly, std::vector<Vertex> rect)
{
	std::vector<CoteList> SI;

	return SI;
}

CoteList InitLCA(std::vector<CoteList> SI, int y)
{
	CoteList LCA;

	return LCA;
}

std::vector<Vertex> RemplissageLCA(std::vector<Vertex> Poly)
{
	std::vector<Vertex> polyFilled;

	std::vector<Vertex> rect = RectEG(Poly);
	//Création SI =>			SI = CreateSI(Poly);
	std::vector<CoteList> SI = CreateSI(Poly, rect);
	//Initialisation LCA =>		LCA = InitLCA();
	CoteList currLCA;
	int xMin, xMax, currX, currY;

	for (currY = rect[0].y; currY < rect[1].y; ++currY)
	{
		currLCA = InitLCA(SI, currY);
	}

	//Pour chaque ligne Y :
		//Gérer les entrées dans LCA à partir de SI =>			LCA.push_back(GetSIEntries(SI, Y);
		//Gérer les sorties dans LCA à partir de SI =>			LCA.pop_back(GETSIEntries(Si, Y);
		//Afficher les morceaux de la ligne décrits dans LCA (voir explications ci-après)
	//LCA contient tous les côtés intersectionnés
	//On commence avec le bit pair
	//A chaque fois qu'on passeà  un autre côté on change la parité du bit
	//Les côtés contenus dans LCA nous donne les xMin et xMax des morceaux de ligne à dessiner
	//On dessine seulement si le bit est impair
	//Cas particulier à gérer : si l'intersection est double au même point


	return polyFilled;
}
