#pragma once
#include "Vertex.h"
#include <vector>
#include "Fenetrage.h"

Vertex intersection(Vertex FormePoint, Vertex FormePointNext, Vertex FenetrePoint, Vertex FenetreNextPoint)
{
	Vertex Pa = { FormePoint.x - FormePointNext.x, FormePoint.y - FormePointNext.y, 1.f, 1.f, 1.f };
	Vertex Pb = { FenetrePoint.x - FenetreNextPoint.x, FenetrePoint.y - FenetreNextPoint.y, 1.f, 0.f, 0.f };
	Vertex IntersectionPoint = { 0.f, 0.f, 0.f, 1.f, 0.f };

	float denom = (Pa.x * Pb.y) - (Pa.y * Pb.x);

	float equationx = (FormePoint.x * FormePointNext.y) - (FormePoint.y * FormePointNext.x);
	float equationy = (FenetrePoint.x * FenetreNextPoint.y) - (FenetrePoint.y * FenetreNextPoint.x);

	IntersectionPoint.x = (equationx * Pb.x - equationy * Pa.x) * 1 / denom;
	IntersectionPoint.y = (equationx * Pb.y - equationy * Pa.y) * 1 / denom;

	return IntersectionPoint;
}

bool coupe(Vertex PointToTest, Vertex FormePointNext, Vertex FenetrePoint, Vertex FenetreNextPoint)
{
	Vertex Pa = { PointToTest.x - FormePointNext.x, PointToTest.y - FormePointNext.y, 1.f, 1.f, 1.f };
	Vertex Pb = { FenetrePoint.x - FenetreNextPoint.x, FenetrePoint.y - FenetreNextPoint.y, 1.f, 0.f, 0.f };

	float denom = (Pa.x * Pb.y) - (Pa.y * Pb.x);

	if (denom == 0.0)
	{
		return false;
	}

	return true;
}


bool visible(Vertex PointToTest, Vertex FenetrePoint, Vertex FenetreNextPoint)
{
	//détermine l'orientation des triangles avec normes des vecteurs FiPk et FiFi+1
	float leftSide = ((FenetreNextPoint.y - FenetrePoint.y) * PointToTest.x + (FenetrePoint.x - FenetreNextPoint.x)) * PointToTest.y
		+ ((FenetreNextPoint.x * FenetrePoint.y) - (FenetreNextPoint.y * FenetrePoint.x));

	if (leftSide < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//REMARQUE : Ps est la liste des vertex tabMenuFormeVertices

std::vector<Vertex> Fenetrage(std::vector<Vertex> PL_Forme, std::vector<Vertex> PW_Fenetre)
{
	int N2 = 0;
	int N1 = PL_Forme.size();
	Vertex S = { 0.0, 0.0, 0.0, 1.0, 0.0 }; 
	Vertex F = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex I = { 0.0, 0.0, 0.0, 1.0, 0.0 };

	std::vector<Vertex> PS;

	for (int i = 1; i < PW_Fenetre.size() - 1; ++i )
	{
		N2 = 0;
		PS.clear();

		for (int j = 1; j < PL_Forme.size(); ++j )
		{
			if (j == 1)
			{
				F = PL_Forme[j];
			}
			else
			{
				if (coupe(S, PL_Forme[j], PW_Fenetre[i], PW_Fenetre[i + 1]))
				{
					I = intersection(S, PL_Forme[j], PW_Fenetre[i], PW_Fenetre[i + 1]);
					PS.push_back(I);
					N2++;
				}
			}

			S = PL_Forme[j];
			if (visible(S, PW_Fenetre[i], PW_Fenetre[i + 1]))
			{
				PS.push_back(S);
				N2++;
			}
		}

		if (N2 > 0)
		{
			if (coupe(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]))
			{
				I = intersection(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]);
				PS.push_back(I);
				N2++;
			}

			PL_Forme = PS;
			N1 = N2;
		}
	}
	return PL_Forme;
}