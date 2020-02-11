#pragma once
#include <iostream>

struct Vertex
{
	double x, y;
	float r, g, b;
	Vertex();
	Vertex(double x, double y, float r, float g, float b);
	friend std::ostream& operator <<(std::ostream&, const Vertex& obj);
};