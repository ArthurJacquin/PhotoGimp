#pragma once
#include "Vertex.h"
#include <vector>

Vertex intersection(Vertex FormePoint, Vertex FormePointNext, Vertex FenetrePoint, Vertex FenetreNextPoint);
bool coupe(Vertex PointToTest, Vertex FormePointNext, Vertex FenetrePoint, Vertex FenetreNextPoint);
bool visible(Vertex PointToTest, Vertex FenetrePoint, Vertex FenetreNextPoint, bool cw);
std::vector<Vertex> Fenetrage(std::vector<Vertex> PL_Forme, std::vector<Vertex> PW_Fenetre);
bool CheckIfClockwise(std::vector<Vertex> v);
std::vector<Vertex> isConcave(std::vector<Vertex> PW_Fenetre);