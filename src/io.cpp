#include "io.h"
#include "nurbs.h"

void IO::writeObj(const std::string& filename, const Surface& srf, int u_resolution, int v_resolution)
{
	std::ofstream file(filename);
	writeObj(file, srf, u_resolution, v_resolution);
}

void IO::writeObj(std::ostream& os, const Surface& srf, int u_resolution, int v_resolution)
{
	// step size
	double h1 = 1.0 / u_resolution;
	double h2 = 1.0 / v_resolution;
	// number of sampled points at each direction
	int number1 = u_resolution + 1;	
	int number2 = v_resolution + 1;

	// vertex positions
	for (int i = 0; i < number1; ++i)
	{
		for(int j = 0; j < number2; ++j)
		{ 
			Point point = nurbs::surfacePoint(srf, i * h1, j * h2);
			os << "v" << " " << point[0] << " " << point[1] << " " << point[2] << std::endl;
		}
	}

	// vertex normals
	for (int i = 0; i < number1; ++i)
	{
		for (int j = 0; j < number2; ++j)
		{
			Point normal = nurbs::surfaceNormal(srf, i * h1, j * h2);
			os << "vn" << " " << normal[0] << " " << normal[1] << " " << normal[2] << std::endl;
		}
	}

	// faces
	for (int i = 0; i < u_resolution; ++i)
	{
		for (int j = 0; j < v_resolution; ++j)
		{
			int a = i * number2 + j;
			int b = i * number2 + j + 1;
			int c = (i + 1) * number2 + j;
			int d = (i + 1) * number2 + j + 1;

			os << "f" << " " << a + 1 << " " << c + 1 << " " << b + 1 << std::endl;
			os << "f" << " " << b + 1 << " " << c + 1 << " " << d + 1 << std::endl;
		}
	}
}