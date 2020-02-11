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

bool visible(Vertex p, Vertex p1, Vertex p2, bool cw)
{
	if (cw)
	{
		return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + (p2.x * p1.y - p1.x * p2.y) > 0;
	}
	else
	{
	//détermine l'orientation des triangles avec normes des vecteurs FiPk et FiFi+1
	return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + (p2.x * p1.y - p1.x * p2.y) < 0;
	}


}

//REMARQUE : Ps est la liste des vertex tabMenuFormeVertices
std::vector<Vertex> Fenetrage(std::vector<Vertex> PL_Forme, std::vector<Vertex> PW_Fenetre)
{
	/*
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
			//if (!visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw) ^ !visible(F, PW_Fenetre[i], PW_Fenetre[i + 1], cw))
			//{
				if (coupe(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]))
				{
					//visible si ses deux extrémités sont visibles 
					if (visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw) && visible(F, PW_Fenetre[i], PW_Fenetre[i + 1], cw))
					{
						PS.push_back(F);
						PS.push_back(S);
					}
					//Premier vertex est à l'extérieur, le second à l'intérieur
					if (!visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw) && visible(F, PW_Fenetre[i], PW_Fenetre[i + 1], cw))
					{
						I = intersection(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]);
						std::cerr << "intersection entre :" << S << "-> " << F << "et " << PW_Fenetre[i] << "-> " << PW_Fenetre[i + 1] << "= " << I << std::endl;
						PS.push_back(I);
						N2++;
					}
					//Premier intérieur, deuxieme extérieur
					else if (visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw) && !visible(F, PW_Fenetre[i], PW_Fenetre[i + 1], cw))
					{
						I = intersection(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]);
						std::cerr << "intersection entre :" << S << "-> " << F << "et " << PW_Fenetre[i] << "-> " << PW_Fenetre[i + 1] << "= " << I << std::endl;
						PS.push_back(I);
					}
					// invisible si ses deux extrémités sont invisibles
					else if (!visible(S, PW_Fenetre[i], PW_Fenetre[i + 1], cw) && !visible(F, PW_Fenetre[i], PW_Fenetre[i + 1], cw))
					{
						std::cerr << "la je fais rien lol" << std::endl;
					}
					/*
					I = intersection(S, F, PW_Fenetre[i], PW_Fenetre[i + 1]);
					std::cerr << "intersection entre :" << S << "-> " << F << "et " << PW_Fenetre[i] << "-> " << PW_Fenetre[i + 1] << "= " << I << std::endl;
					PS.push_back(I);
					N2++;
				}
			//}

			PL_Forme = PS;
			N1 = N2;
		}
	}
	*/

	bool clockWise = CheckIfClockwise(PW_Fenetre);

	Vertex s = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex e = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex I = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex cp1 = { 0.0, 0.0, 0.0, 1.0, 0.0 };
	Vertex cp2 = { 0.0, 0.0, 0.0, 1.0, 0.0 };

	std::vector<Vertex> inputPolygon;
	inputPolygon.resize(99);

	std::vector<Vertex> newPolygon;
	newPolygon.resize(99);

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
		std::cerr << "newPolygonSize : " << newPolygonSize << std::endl;

		for (int i = 0; i < newPolygonSize; i++)
		{
			s = inputPolygon[i];
			e = inputPolygon[(i + 1) % newPolygonSize];
			std::cerr << "inputPolygon : " << inputPolygon.size() << std::endl;
			//visible si ses deux extrémités sont visibles 
			if (visible(s, cp1, cp2, clockWise) && visible(e, cp1, cp2, clockWise))
			{
				std::cerr << "visible si ses deux extremites sont visibles " << std::endl;
				newPolygon[counter++] = e;
			}
			//Premier vertex est à l'extérieur, le second à l'intérieur
			else if (!visible(s, cp1, cp2, clockWise) && visible(e, cp1, cp2, clockWise))
			{
				std::cerr << "Premier vertex est a l'exterieur, le second à l'interieur " << std::endl;
				newPolygon[counter++] = intersection(s, e, cp1, cp2);
				newPolygon[counter++] = e;
			}
			//Premier intérieur, deuxieme extérieur
			else if (visible(s, cp1, cp2, clockWise) && !visible(e, cp1, cp2, clockWise))
			{
				std::cerr << "Premier interieur, deuxieme exterieur" << std::endl;
				newPolygon[counter++] = intersection(s, e, cp1, cp2);
			}
			// invisible si ses deux extrémités sont invisibles
			else if (!visible(s, cp1, cp2, clockWise) && !visible(e, cp1, cp2, clockWise))
			{
				std::cerr << "la je fais rien lol" << std::endl;
			}
		}
		newPolygonSize = counter;
		std::cerr << "counter : " << counter << std::endl;
		//newPolygon.resize(counter);
	}
	newPolygon.resize(newPolygonSize);
	return newPolygon;
}