#include "Remplissage.h"

CoteList GetLCFromPoly(std::vector<Vertex> Poly)
{
	std::cout << "Hello from GetLCFromPoly" << std::endl;
	
	//CoteActif currCote;
	CoteList LC; //Liste des côtés du Poly
	/*int nbCote = 0;
	int j = 0;
	CoteActif previous;

	for (int i = Poly.size() - 1; i >= 0; --i) //On remonte les côtés en partant "à l'envers" pour les ajouter à la liste
	{
		j = i == (Poly.size() - 1) ? 0 : i + 1;

		float yMax = Poly[j].y > Poly[i].y ? Poly[j].y : Poly[i].y; //trouver le y max
		float coeff = (Poly[i].y - Poly[j].y) / (Poly[i].x - Poly[j].x); //calcul du coeff directeur
		float x = 0.0f; //pour l'instant on laisse à 0.0f
		//stocker le côté qu'on vient de créer pour le donner en "next" au côté qu'on va créer ensuite
		currCote = CoteActif(yMax, x, coeff);
		std::cout << u8"Création d'un CoteActif : " << currCote << std::endl;

		LC.AddBeginList(currCote);
		//LC = CoteList(currCote); //initialisation de la liste avec le dernier côté

		if (i != Poly.size() - 1)
		{
			currCote.SetNextCote(previous);
		}
		previous = currCote;
		++nbCote;//incrémenter nbCote
	}

	if (nbCote != Poly.size())
	{
		std::cout << u8"Erreur dans la création de la liste des côtés" << std::endl;
		std::cout << u8"Nombre de côtés comptés : " << nbCote << " et nombre de sommets du poly : " << Poly.size() << std::endl;
	}

	//boucler la boucle des côtés en mettant le dernier côté stocké en premier de la listes
	*/
	return LC;
}

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

	Vertex P1 = { xMin, yMin, 0.f, 1.f, 1.f };
	Vertex P2 = { xMin, yMax, 0.f, 1.f, 1.f };
	Vertex P3 = { xMax, yMax, 0.f, 1.f, 1.f };
	Vertex P4 = { xMax, yMin, 0.f, 1.f, 1.f };

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
	std::cout << "Hello from GetCurrentLineFromRect" << std::endl;

	std::vector<Vertex> line;
	
	Vertex P1 = { rect[0].x, y, 0.f, 1.f, 1.f };
	Vertex P2 = { rect[2].x, y, 0.f, 1.f, 1.f };

	line.push_back(P1);
	line.push_back(P2);

	std::cout << "Point 1 de la ligne courante : " << P1 << std::endl;
	std::cout << "Point 2 de la ligne courante : " << P2 << std::endl;

	return line;
}

std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> Line, std::vector<Vertex> Poly)
{
	std::cout << "Hello from FindIntersectionWithLine" << std::endl;

	std::vector<Vertex> intersections;
	/*
	CoteList LC = GetLCFromPoly(Poly);
	CoteActif* currCote = LC.GetFirst();
	CoteActif* last = LC.GetLast();
	*/
	Vertex P1 = Line[0]; //premier point de la ligne de balayage 
	Vertex P2 = Line[1]; //deuxième point de la ligne de balayage
	Vertex P3 = { 0.f, 0.f, 0.f, 1.f, 1.f }; //premier point du côté 
	Vertex P4 = { 0.f, 0.f, 0.f, 1.f, 1.f }; //deuxième point du côté

	/*std::vector<int> P1int = ConvertCoordToInt(P1);
	std::vector<int> P2int = ConvertCoordToInt(P2);
	std::vector<int> P3int = ConvertCoordToInt(P3);
	std::vector<int> P4int = ConvertCoordToInt(P4);*/

	int j = 0;
	double currY = Line[0].y;
	//int currY = P1int[1];

	/*while (currCote != last) //itérer sur la liste des côtés du poly 
	{
		//mettre à jour P3 et P4 et recalculer les coord en int
		currCote = currCote->GetNextCote();
		intersections.push_back(intersection(P1, P2, P3, P4)); //ajouter l'intersection à la liste des intersections
	}*/

	for (int i = 0; i < Poly.size(); ++i)
	{
		j = i + 1;
		if (i == Poly.size() - 1)
		{
			j = 0;
		}

		P3.x = Poly[i].x;
		P3.y = Poly[i].y;
		P4.x = Poly[j].x;
		P4.y = Poly[j].y;

		Vertex intersectionPoint = intersection(P1, P2, P3, P4); //intersection entre la ligne et le côté du poly
		intersections.push_back(intersectionPoint); //ajouter l'intersection à la liste des intersections
		std::cout << "Intersection en y : " << currY << " => " << intersectionPoint.x << std::endl;
	}

	return intersections;
}

std::vector<Vertex> Remplissage(std::vector<Vertex> Poly)
{
	//std::cout << "Hello from Remplissage" << std::endl;

	std::vector<Vertex> polyFilled;

	//std::vector<Vertex> rect = RectEG(Poly);
	////std::vector<int> rectInt;

	////for (int i = 0; i < rect.size(); ++i)
	////{
	////	//rectInt.push_back(ConvertCoordToInt(rect[i]);)
	////}
	//std::vector<Vertex> currLine;
	//std::vector<Vertex> intersections;
	//Vertex P = { 0.f, 0.f, 0.f, 1.f, 1.f };
	//int nbIntersections = 0;
	//int currIntersection = 0;

	//double xMin, xMax, currX, currY;
	//int xMinInt, xMaxInt, currXInt, currYInt;

	//for (currYInt = rect[0].y; currY < rect[2].y; currY += 0.001f)
	//{
	//	currLine = GetCurrentLineFromRect(rect, currY); //récupère la ligne courante
	//	intersections = FindIntersectionWithLine(currLine, Poly); //récupère les intersections entre la ligne et le poly
	//	nbIntersections = intersections.size(); //nombre d'intersections
	//	currIntersection = 0; //id de l'intersection courante

	//	while (currIntersection < nbIntersections) //tant qu'on a pas parcouru toutes les intersections
	//	{
	//		xMin = intersections[currIntersection].x; //on récupère le x min de la zone entre les deux intersections
	//		++currIntersection; //on passe à l'intersection suivante

	//		if (currIntersection != nbIntersections) //si on est pas dans la dernière zone
	//		{
	//			xMax = intersections[currIntersection].x; //on récupère le x max de la zone entre les deux intersections

	//			for (currX = xMin; currX < xMax; ++currX) //on parcoure tous les points à l'ordonnée currY qui sont dans la zone
	//			{
	//				P.x = currX;
	//				P.y = currY;
	//				polyFilled.push_back(P); //on ajoute ce point à la liste finale des points à dessiner
	//			}
	//			++currIntersection; //on passe à l'intersection suivante
	//		}
	//	}
	//	intersections.clear();
	//	currLine.clear();
	//}

	//for (int i = 0; i < polyFilled.size(); ++i)
	//{
	//	std::cout << "Points à remplir : " << std::endl;
	//	std::cout << polyFilled[i] << std::endl;
	//}

	return polyFilled;
}

std::vector<CoteList> CreateSI(std::vector<Vertex> Poly, std::vector<Vertex> rect)
{
	std::cout << "Hello from CreateSI" << std::endl;

	std::vector<CoteList> SI;

	return SI;
}

CoteList InitLCA(std::vector<CoteList> SI, double y)
{
	std::cout << "Hello from InitLCA" << std::endl;

	CoteList LCA;

	//récupérer le coeff a et le mettr dans curr_x => à renommer ?? (Rappel : a = point2.x - point1.x)
	//curr_x est censé contenir l'abscisse de l'intersection


	return LCA;
}

std::vector<Vertex> RemplissageLCA(std::vector<Vertex> Poly)
{
	std::cout << "Hello from RemplissageLCA" << std::endl;

	std::vector<Vertex> polyFilled;

	std::vector<Vertex> rect = RectEG(Poly);
	//Création SI =>			SI = CreateSI(Poly);
	std::vector<CoteList> SI = CreateSI(Poly, rect);
	//Initialisation LCA =>		LCA = InitLCA();
	CoteList currLCA;
	int xMin, xMax, currX, currY;

	for (currY = rect[0].y; currY < rect[2].y; ++currY)
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
