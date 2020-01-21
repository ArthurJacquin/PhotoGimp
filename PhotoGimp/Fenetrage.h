#pragma once
#include "Vertex.h"
#include <vector>

Vertex intersection(Vertex FormePoint, Vertex FormePointNext, Vertex FenetrePoint, Vertex FenetreNextPoint);
bool coupe(Vertex PointToTest, Vertex FormePointNext, Vertex FenetrePoint, Vertex FenetreNextPoint);
bool visible(Vertex PointToTest, Vertex FenetrePoint, Vertex FenetreNextPoint);
std::vector<Vertex> Fenetrage(std::vector<Vertex> PL_Forme, std::vector<Vertex> PW_Fenetre);