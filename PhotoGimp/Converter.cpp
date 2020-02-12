//#include "Converter.h"
//#include "Color.h"
//#include <iostream>
//
//extern int width, height;
//extern Color choosedColor;
//
//std::vector<int> ConvertCoordToInt(Vertex v)
//{
//	std::vector<int> point;
//
//	int new_x = ((v.x / 2) * width) + 1.0f;
//	int new_y = ((v.y / 2) * height) + 1.0f;
//
//	std::cout << "Conversion du vertex" << v << " en point : (" << new_x << ", " << new_y << ")" << std::endl;
//
//	point.push_back(new_x);
//	point.push_back(new_y);
//
//	return point;
//}
//
//Vertex ConvertCoordToVertex(std::vector<int> p)
//{
//	Vertex v = Vertex(-1.0f + 2 * (double)p[0] / width, 1.0f - 2 * (double)p[1] / height, choosedColor.x, choosedColor.y, choosedColor.z);
//	
//	std::cout << "Conversion du point (" << p[0] << ", " << p[1] << ") en vertex : " << v << std::endl;
//
//	return v;
//}
