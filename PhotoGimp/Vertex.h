#pragma once
#include <iostream>

struct Vertex
{
	double x, y;
	float r, g, b;
	int x_int, y_int;
	Vertex();
	Vertex(double x, double y, float r, float g, float b);
	Vertex(double x, double y, float r, float g, float b, int x_int, int y_int);
	void CastToDouble(Vertex& v,int int_x, int int_y);
	friend std::ostream& operator <<(std::ostream&, const Vertex& obj);
};