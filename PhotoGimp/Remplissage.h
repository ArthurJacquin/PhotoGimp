#pragma once
#include "Fenetrage.h"

std::vector<Vertex> RectEG(std::vector<Vertex> Poly); //retourne les coordonn�es du rectangle englobant 
std::vector<Vertex> GetCurrentLineFromRect(std::vector<Vertex> rect, int y); //retourne les coordonn�es de la ligne du rectangle englobant � Y = y
std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> Line, std::vector<Vertex> Poly); //retourne les intersections pour chaque ligne du rectangle englobant
std::vector<Vertex> Remplissage(std::vector<Vertex> Poly);