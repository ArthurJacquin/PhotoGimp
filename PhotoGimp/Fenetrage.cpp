#pragma once
#include "Vertex.h"
#include <vector>
#include "Fenetrage.h"

Vertex intersection(Vertex P1, Vertex P2, Vertex P3, Vertex P4)
{
	Vertex IntersectionPoint = { 0.f, 0.f, 0.f, 1.f, 0.f };

	//Coefs directeurs
	double mP1P2 = (P2.y - P1.y) / (P2.x - P1.x);
	double mP3P4 = (P4.y - P3.y) / (P4.x - P3.x);

	//Ordonnée à l'origine
	double pP1P2 = P2.y - (mP1P2 * P2.x);
	double pP3P4 = P4.y - (mP3P4 * P4.x);
	
	double Vco = -mP3P4 + mP1P2;
	double Vcob = -pP3P4 + pP1P2;

	float Xi = -(Vcob / Vco);
	float Yi = mP3P4 * Xi + pP3P4;

	IntersectionPoint.x = Xi;
	IntersectionPoint.y = Yi;

	return IntersectionPoint;
}

bool coupe(Vertex P1, Vertex P2, Vertex P3, Vertex P4)
{
	//Coefs directeurs
	double mP1P2 = (P2.y - P1.y) / (P2.x - P1.x);
	double mP3P4 = (P4.y - P3.y) / (P4.x - P3.x);

	return mP1P2 != mP3P4;
}

bool CheckIfClockwise(std::vector<Vertex> v)
{
	v.push_back(v[0]);
	float som = 0;

	for (int i = 0; i < v.size() - 1; ++i)
	{
		som += (v[i + 1].x - v[i].x) * (v[i + 1].y + v[i].y);
	}

	std::cout << (som >= 0.f);
	return som >= 0.f;
}

bool visible(Vertex PointToTest, Vertex FenetrePoint, Vertex FenetreNextPoint, bool clockwise)
{
	//détermine l'orientation des triangles avec normes des vecteurs FiPk et FiFi+1
	float leftSide = ((FenetreNextPoint.y - FenetrePoint.y) * PointToTest.x + (FenetrePoint.x - FenetreNextPoint.x)) * PointToTest.y
		+ ((FenetreNextPoint.x * FenetrePoint.y) - (FenetreNextPoint.y * FenetrePoint.x));
	
	if(clockwise)
	{
		return leftSide > 0.0f;
	}
	else
	{
		return leftSide < 0.0f;
	}
}

//REMARQUE : Ps est la liste des vertex tabMenuFormeVertices
std::vector<Vertex> Fenetrage(std::vector<Vertex> PL_Forme, std::vector<Vertex> PW_Fenetre)
{
	bool cw = CheckIfClockwise(PW_Fenetre);
	PW_Fenetre.push_back(PW_Fenetre[0]);

	int N1 = PL_Forme.size();
	int N3 = PW_Fenetre.size();
	int N2 = 0;
	
	Vertex S = { 0.0, 0.0, 0.0, 1.0, 0.0 }; 
	Vertex F = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex I = { 0.0, 0.0, 0.0, 1.0, 0.0 };

	std::vector<Vertex> PS;
	
	for (int i = 0; i < N3 - 1; ++i)
	{
		N2 = 0;
		PS.clear();

		for (int j = 0; j < N1; ++j)
		{
			if (j == 0)
			{
				F = PL_Forme[j];
			}
			else
			{
				if (!visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw) ^ !visible(PL_Forme[j], PW_Fenetre[i], PW_Fenetre[i + 1], cw))
				{
					if (coupe(S, PL_Forme[j], PW_Fenetre[i], PW_Fenetre[i + 1]))
					{
						I = intersection(S, PL_Forme[j], PW_Fenetre[i], PW_Fenetre[i + 1]);
						std::cerr << "intersection entre :" << S << "-> " << PL_Forme[j] << "et " << PW_Fenetre[i] << "-> " << PW_Fenetre[i + 1] << "= " << I << std::endl;
						PS.push_back(I);
						N2++;
					}
				}
			}

			S = PL_Forme[j];
			if (visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw))
			{
				PS.push_back(S);
				N2++;
			}
		}
		if (N2 > 0)
		{
			if (!visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw) ^ !visible(F, PW_Fenetre[i], PW_Fenetre[i + 1], cw))
			{
				if (coupe(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]))
				{
					I = intersection(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]);
					std::cerr << "intersection entre :" << S << "-> " << F << "et " << PW_Fenetre[i] << "-> " << PW_Fenetre[i + 1] << "= " << I << std::endl;
					PS.push_back(I);
					N2++;
				}
			}

			PL_Forme = PS;
			N1 = N2;
		}
	}

	return PL_Forme;
}