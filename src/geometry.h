#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "nurbs.h"

using Point = glm::vec<3, double>;
using Mat = std::vector<std::vector<Point>>;
using Curve = nurbs::Curve3d;
using Surface = nurbs::Surface3d;

namespace Geometry
{
	// The total chord length
	double GetTotalChordLength(const std::vector<Point>& points);

	// The chord length parameterization
	std::vector<double> GetChordParameterization(const std::vector<Point>& points);

	// The chord length parameterization for several groups of points
	std::vector<double> GetChordParameterization(const Mat& points);

	// Technique of averaging
	std::vector<double> AverageKnotVector(unsigned int degree, const std::vector<double>& params);

	// Determine the knot span index
	int GetKnotSpanIndex(unsigned int degree, const std::vector<double>& knotVector, double paramT);

	// Compute the nonvanishing basis functions
	std::vector<double> BasisFunctions(int spanIndex, unsigned int degree, const std::vector<double>& knotVector, double paramT);

}