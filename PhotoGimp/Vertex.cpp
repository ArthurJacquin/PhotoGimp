#include "Vertex.h"

extern int width, height;

Vertex::Vertex()
{
	x = 0;
	y = 0;
	r = 0;
	g = 0;
	b = 0;
	x_int = 0;
	y_int = 0;
}

Vertex::Vertex(double x, double y, float r, float g, float b)
	:x(x), y(y), r(r), g(g), b(b)
{
	x_int = ((x / 2) * width) + 1.0f;
	y_int = ((y / 2) * height) + 1.0f;
}

Vertex::Vertex(double x, double y, float r, float g, float b, int x_int, int y_int)
	:x(x), y(y), r(r), g(g), b(b), x_int(x_int), y_int(y_int)
{
}

void Vertex::CastToDouble(Vertex& v, int int_x, int int_y)
{
	v.x = (double)(-1.0f + 2 * int_x / width);
	v.y = (double)(1.0f - 2 * int_y / height);
}

std::ostream& operator<<(std::ostream& os, const Vertex& obj)
{
	os << "(" << obj.x << "," << obj.y << "," << obj.r << "," << obj.g << "," << obj.b << "," << obj.x_int << "," << obj.y_int << ")" << std::endl;
	return os;
}
