#include "Remplissage.h"

CoteList GetLCFromPoly(std::vector<Vertex> Poly)
{
	CoteList LC; //Liste des c�t�s du Poly
	int nbCote = 0;
	CoteActif previous;
	//TODO : conversion du poly en liste de CoteActif

	for (int i = 0; i < Poly.size(); ++i) //Faire la boucle � l'envers
	{
		CoteActif currCote = CoteActif();
		//Prendre deux � deux les points du poly et en d�duire les valeurs du CoteActif correspondants
		//Pour N sommets il y N CoteActif
		//calculer le coeff directeur (Rappel : coeff = (y2 - y1)/(x2 - x1))
		//r�cup�rer le y max // facile !
		//r�cup�rer le coeff a et le mettr dans curr_x => � renommer ?? (Rappel : a = point2.x - point1.x)
		//stocker le c�t� qu'on vient de cr�er pour le donner en "next" au c�t� qu'on va cr�er ensuite
		previous = currCote;
		if (nbCote == 0) //si c'est le premier c�t�, on le stock � la fin de la liste
		{
			LC.AddEndList(currCote);
		}
		++nbCote;//incr�menter nbCote
	}

	//boucler la boucle des c�t�s en mettant le dernier c�t� stock� en premier de la listes

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
	Vertex P2 = Line[1]; //deuxi�me point de la ligne de balayage
	Vertex P3 = { 0.f, 0.f, 0.f, 1.f, 1.f }; //premier point du c�t� 
	Vertex P4 = { 0.f, 0.f, 0.f, 1.f, 1.f }; //deuxi�me point du c�t�
	
	while (currCote != last) //it�rer sur la liste des c�t�s du poly 
	{
		//mettre � jour P3 et P4
		currCote = currCote->GetNextCote();
		intersections.push_back(intersection(P1, P2, P3, P4)); //ajouter l'intersection � la liste des intersections
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
		currLine = GetCurrentLineFromRect(rect, currY); //r�cup�re la ligne courante
		intersections = FindIntersectionWithLine(currLine, Poly); //r�cup�re les intersections entre la ligne et le poly
		nbIntersections = intersections.size(); //nombre d'intersections
		currIntersection = 0; //id de l'intersection courante

		while (currIntersection < nbIntersections) //tant qu'on a pas parcouru toutes les intersections
		{
			xMin = intersections[currIntersection].x; //on r�cup�re le x min de la zone entre les deux intersections
			++currIntersection; //on passe � l'intersection suivante

			if (currIntersection != nbIntersections) //si on est pas dans la derni�re zone
			{
				xMax = intersections[currIntersection].x; //on r�cup�re le x max de la zone entre les deux intersections

				for (currX = xMin; currX < xMax; ++currX) //on parcoure tous les points � l'ordonn�e currY qui sont dans la zone
				{
					P.x = currX;
					P.y = currY;
					polyFilled.push_back(P); //on ajoute ce point � la liste finale des points � dessiner
				}
				++currIntersection; //on passe � l'intersection suivante
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
	//Cr�ation SI =>			SI = CreateSI(Poly);
	std::vector<CoteList> SI = CreateSI(Poly, rect);
	//Initialisation LCA =>		LCA = InitLCA();
	CoteList currLCA;
	int xMin, xMax, currX, currY;

	for (currY = rect[0].y; currY < rect[1].y; ++currY)
	{
		currLCA = InitLCA(SI, currY);
	}

	//Pour chaque ligne Y :
		//G�rer les entr�es dans LCA � partir de SI =>			LCA.push_back(GetSIEntries(SI, Y);
		//G�rer les sorties dans LCA � partir de SI =>			LCA.pop_back(GETSIEntries(Si, Y);
		//Afficher les morceaux de la ligne d�crits dans LCA (voir explications ci-apr�s)
	//LCA contient tous les c�t�s intersectionn�s
	//On commence avec le bit pair
	//A chaque fois qu'on passe�  un autre c�t� on change la parit� du bit
	//Les c�t�s contenus dans LCA nous donne les xMin et xMax des morceaux de ligne � dessiner
	//On dessine seulement si le bit est impair
	//Cas particulier � g�rer : si l'intersection est double au m�me point


	return polyFilled;
}
