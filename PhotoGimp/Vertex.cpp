#include "Vertex.h"

Vertex::Vertex(double x, double y, float r, float g, float b)
	:x(x), y(y), r(r), g(g), b(b)
{
}

std::ostream& operator<<(std::ostream& os, const Vertex& obj)
{
	os << "(" << obj.x << "," << obj.y;
	return os;
}
