#pragma once
#include "Fenetrage.h"

std::vector<Vertex> RectEG(std::vector<Vertex> Poly); //retourne les coordonnées du rectangle englobant 
std::vector<Vertex> GetCurrentLineFromRect(std::vector<Vertex> rect, int y); //retourne les coordonnées de la ligne du rectangle englobant à Y = y
std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> Line, std::vector<Vertex> Poly); //retourne les intersections pour chaque ligne du rectangle englobant
std::vector<Vertex> Remplissage(std::vector<Vertex> Poly);