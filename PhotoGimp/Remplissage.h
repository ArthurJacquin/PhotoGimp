#pragma once
#include "Fenetrage.h"
#include "CoteList.h"

CoteList GetLCFromPoly(std::vector<Vertex> Poly);
std::vector<Vertex> RectEG(std::vector<Vertex> Poly); //retourne les coordonnées du rectangle englobant 
std::vector<Vertex> GetCurrentLineFromRect(std::vector<Vertex> rect, int y); //retourne les coordonnées de la ligne du rectangle englobant à Y = y
std::vector<Vertex> FindIntersectionWithLine(std::vector<Vertex> Line, std::vector<Vertex> Poly); //retourne les intersections pour chaque ligne du rectangle englobant
std::vector<Vertex> Remplissage(std::vector<Vertex> Poly); //retourne la liste des Vertex à dessiner
std::vector<CoteList> CreateSI(std::vector<Vertex> Poly, std::vector<Vertex> rect); //créer la liste SI du Poly
CoteList InitLCA(std::vector<CoteList> SI, int y); //Initialise la liste LCA en fonction du y passé en paramètre et à partir de la SI
std::vector<Vertex> RemplissageLCA(std::vector<Vertex> Poly); //retourne la liste des Vertex à dessiner en appliquant l'algo LCA