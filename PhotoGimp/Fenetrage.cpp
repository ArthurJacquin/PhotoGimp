#pragma once
#include "Vertex.h"
#include <vector>

bool coupe(Vertex PointToTest, std::vector<Vertex> tabFormeVertices, std::vector<Vertex> tabFenetreVertices)
{

	return false;
}

Vertex intersection(Vertex FormePoint, Vertex FormePointNext, Vertex FenetrePoint, Vertex FenetreNextPoint)
{
	Vertex Pa = { FormePoint.x - FormePointNext.x, FormePoint.y - FormePointNext.y, 1.f, 1.f, 1.f };
	Vertex Pb = { FenetrePoint.x - FenetreNextPoint.x, FenetrePoint.y - FenetreNextPoint.y, 1.f, 0.f, 0.f };
	Vertex IntersectionPoint = { 0.f, 0.f, 0.f, 0.f, 0.f };

	float denom = (Pa.x * Pb.y) - (Pa.y * Pb.x);

	float equationx = (FormePoint.x * FormePointNext.y) - (FormePoint.y * FormePointNext.x);
	float equationy = (FenetrePoint.x * FenetreNextPoint.y) - (FenetrePoint.y * FenetreNextPoint.x);
	//std::cerr << "equationx :" << equationx << std::endl;

	IntersectionPoint.x = (equationx * Pb.x - equationy * Pa.x) * 1 / denom;
	IntersectionPoint.y = (equationx * Pb.y - equationy * Pa.y) * 1 / denom;
	//std::cerr << "IntersectionPoint : " << IntersectionPoint << std::endl;

	return IntersectionPoint;
}


bool visible(Vertex PointToTest, Vertex FenetrePoint, Vertex FenetreNextPoint)
{
	//détermine l'orientation des triangles avec normes des vecteurs FiPk et FiFi+1
	float leftSide = abs(((PointToTest.x - FenetrePoint.x) * (FenetreNextPoint.x - FenetrePoint.x)) - ((PointToTest.y - FenetrePoint.y) * (FenetreNextPoint.y - FenetrePoint.y)));
	if (leftSide < 0)
		return true;
	else
		return false;
}

//REMARQUE : Ps est la liste des vertex tabMenuFormeVertices