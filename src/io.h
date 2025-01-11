#ifndef IO_H
#define IO_H

#include "geometry.h"
#include <ostream>
#include <fstream>
#include <string>
#include <vector>

namespace IO
{
	// discreate the B-spline surface to triangle meshes
	void writeObj(const std::string& filename, const Surface& srf, int u_resolution = 100, int v_resolution = 100);	// interface
	void writeObj(std::ostream& os, const Surface& srf, int u_resolution, int v_resolution);	// internal

} // namespace IO

#endif