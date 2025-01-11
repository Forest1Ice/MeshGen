#include "geometry.h"

double Geometry::GetTotalChordLength(const std::vector<Point>& points)
{
	int n = points.size() - 1;
	double length = 0.0;

	for (int i = 1; i <= n; ++i)
	{
		length += glm::distance(points[i], points[i - 1]);
	}

	return length;
}

std::vector<double> Geometry::GetChordParameterization(const std::vector<Point>& points)
{
	int size = points.size();
	int n = size - 1;
	double d = GetTotalChordLength(points);

	// initialization
	std::vector<double> uk(size, 0.0);
	uk[n] = 1.0;

	for (int i = 1; i <= n - 1; ++i)
	{
		uk[i] = uk[i - 1] + glm::distance(points[i], points[i - 1]) / d;
	}

	return uk;
}

std::vector<double> Geometry::GetChordParameterization(const Mat& points)
{
	int number = points.size(); // number of groups
	int size = points[0].size(); // number of points of each group

	std::vector<double> vk(size, 0.0), temp(size);
	for (int i = 0; i < number; ++i)
	{
		temp = GetChordParameterization(points[i]);
		for (int k = 0; k < size; ++k)
		{
			vk[k] += temp[k];
		}
	}

	for (int k = 0; k < size; ++k)
	{
		vk[k] /= number;
	}

	return vk;
}

std::vector<double> Geometry::AverageKnotVector(unsigned int degree, const std::vector<double>& params)
{
	int size = params.size();
	int n = size - 1;
	int m = n + degree + 1;

	std::vector<double> knotVector(m + 1, 0.0);
	for (int i = m - degree; i <= m; ++i)
	{
		knotVector[i] = 1.0;
	}

	for (int j = 1; j <= n - degree; ++j)
	{
		double sum = 0.0;
		for (int i = j; i <= j + degree - 1; ++i)
		{
			sum += params[i];
		}
		knotVector[j + degree] = (1.0 / degree) * sum;
	}

	return knotVector;
}

int Geometry::GetKnotSpanIndex(unsigned int degree, const std::vector<double>& knotVector, double paramT)
{
	int n = knotVector.size() - degree - 2;

	if (paramT >= knotVector[n + 1])
	{
		return n;
	}
	if (paramT <= knotVector[degree])
	{
		return degree;
	}

	int low = degree;
	int high = n + 1;
	int mid = static_cast<int>(floor((low + high) / 2.0));

	while (paramT < knotVector[mid] ||
		paramT >= knotVector[mid + 1])
	{
		if (paramT < knotVector[mid])
		{
			high = mid;
		}
		else
		{
			low = mid;
		}
		mid = static_cast<int>(floor((low + high) / 2.0));
	}
	
	return mid;
}

std::vector<double> Geometry::BasisFunctions(int spanIndex, unsigned int degree, const std::vector<double>& knotVector, double paramT)
{
	std::vector<double> basisFunctions(degree + 1);
	basisFunctions[0] = 1.0;

	std::vector<double> left(degree + 1);
	std::vector<double> right(degree + 1);

	for (int j = 1; j <= degree; ++j)
	{
		left[j] = paramT - knotVector[spanIndex + 1 - j];
		right[j] = knotVector[spanIndex + j] - paramT;

		double saved = 0.0;

		for (int r = 0; r < j; ++r)
		{
			double temp = basisFunctions[r] / (right[r + 1] + left[j - r]);
			basisFunctions[r] = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
		}
		basisFunctions[j] = saved;
	}

	return basisFunctions;
}