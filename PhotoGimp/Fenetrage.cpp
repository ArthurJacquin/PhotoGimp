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

	//Ordonn�e � l'origine
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

	return som >= 0.f;
}

bool visible(Vertex p, Vertex p1, Vertex p2, bool cw)
{
	if (cw)
	{
		return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + (p2.x * p1.y - p1.x * p2.y) > 0;
	}
	else
	{
	//d�termine l'orientation des triangles avec normes des vecteurs FiPk et FiFi+1
	return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + (p2.x * p1.y - p1.x * p2.y) < 0;
	}
}

std::vector<Vertex> isConcave(std::vector<Vertex> PW_Fenetre)
{
	bool cw = CheckIfClockwise(PW_Fenetre);
	std::vector<float> distance;
	Vertex avant = { 0, 0, 0, 0, 0 };
	Vertex apres = { 0, 0, 0, 0, 0 };

	for (int i = 0; i < PW_Fenetre.size() - 1; i++)
	{
		if (!visible(PW_Fenetre[i + 1], PW_Fenetre[(i - 1) % PW_Fenetre.size()], PW_Fenetre[i], cw))
		{
			std::cerr << "je suis un polygon concave" << std::endl;
			std::cerr << "je suis le point qui est concave :" << PW_Fenetre[i] << std::endl;
			avant = PW_Fenetre[(i - 1) % PW_Fenetre.size()];
			apres = PW_Fenetre[i + 1];

			//calcul distance euclidienne des points autres que (i + 1) et (i - 1)
			for (int j = 0; j < PW_Fenetre.size() - 1; j ++)
			{
				float dist = sqrt(pow((PW_Fenetre[(j + 1) % PW_Fenetre.size()].x) - PW_Fenetre[j].x, 2) + pow(PW_Fenetre[j + 1].y - PW_Fenetre[j].y, 2));
				if (dist == 0 || PW_Fenetre[j] == avant || PW_Fenetre[j] == apres)
					continue;
				else
				{
					distance.push_back(dist);
				}

				std::cerr << "distance euclidienne entre :" << PW_Fenetre[(j + 1) % PW_Fenetre.size()] << "et" << PW_Fenetre[j] << " = " << dist << std::endl;
			}
		}
	}
	return PW_Fenetre;
}


//REMARQUE : Ps est la liste des vertex tabMenuFormeVertices
std::vector<Vertex> Fenetrage(std::vector<Vertex> PL_Forme, std::vector<Vertex> PW_Fenetre)
{
	bool clockWise = CheckIfClockwise(PW_Fenetre);

	Vertex s = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex e = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex I = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex cp1 = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex cp2 = { 0.0, 0.0, 0.0, 1.0, 0.0 };

	std::vector<Vertex> inputPolygon;
	inputPolygon.resize(9999);

	std::vector<Vertex> newPolygon;
	newPolygon.resize(9999);

	for (int i = 0; i < PL_Forme.size(); i++)
	{
		newPolygon[i] = PL_Forme[i];
	}
	int newPolygonSize = PL_Forme.size();

	for (int j = 0; j < PW_Fenetre.size(); j++)
	{
		for (int k = 0; k < newPolygonSize; k++)
		{
			inputPolygon[k] = newPolygon[k];
		}

		int counter = 0;
		cp1 = PW_Fenetre[j];
		cp2 = PW_Fenetre[(j + 1) % PW_Fenetre.size()];

		for (int i = 0; i < newPolygonSize; i++)
		{
			s = inputPolygon[i];
			e = inputPolygon[(i + 1) % newPolygonSize];

			//visible si ses deux extr�mit�s sont visibles 
			if (visible(s, cp1, cp2, clockWise) && visible(e, cp1, cp2, clockWise))
			{
				newPolygon[counter++] = e;
			}
			//Premier vertex est � l'ext�rieur, le second � l'int�rieur
			else if (!visible(s, cp1, cp2, clockWise) && visible(e, cp1, cp2, clockWise))
			{
				newPolygon[counter++] = intersection(s, e, cp1, cp2);
				newPolygon[counter++] = e;
			}
			//Premier int�rieur, deuxieme ext�rieur
			else if (visible(s, cp1, cp2, clockWise) && !visible(e, cp1, cp2, clockWise))
			{
				newPolygon[counter++] = intersection(s, e, cp1, cp2);
			}
		}
		newPolygonSize = counter;
	}
	newPolygon.resize(newPolygonSize);

	return newPolygon;
}