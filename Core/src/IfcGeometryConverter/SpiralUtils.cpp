/*
	Copyright (c) 2021 Technical University of Munich
	Chair of Computational Modeling and Simulation.

	TUM Open Infra Platform is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License Version 3
	as published by the Free Software Foundation.

	TUM Open Infra Platform is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

//
//  Author:  Peter Bonsma
//  $Date: 1999-12-31 23:59:59 +0000 (Wed, 31 Jan 1999) $
//  $Revision: 3999 $
//  Project: Geometry Kernel
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:  peter.bonsma@rdf.bg
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <utility>
#include <sstream>

#include "CarveHeaders.h"

#include "GeometrySettings.h"
#include "ProfileConverter.h"
#include "CurveConverter.h"

#include "SpiralUtils.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_BEGIN

/**********************************************************************************************/
/*!Calculate recursive multiplication for calculation Taylor series
* \param[in]  value                  value of Taylor series
* \param[in]  polynomialConstants    polynomial constants for a polynomial term - a,b,c,d
* \param[in]  myArray                matrix with 1xn number of iteration points
* \param[in]  i_n                    actual iteration point
* \param[in]  n                      number of iteration points
*
* \return
*/
void	RecursiveMultiplication(
	const double	value,
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	std::vector<double>&  myArray,
	const int myArrayParentIndex,
	const int i_n,
	const int n
)
{
	if (!value) throw oip::InconsistentGeometryException("Invalid polynomial constants!");
	if (i_n < n - 1) {
		if(polynomialConstantCnt && polynomialConstants[0] != 0.)throw oip::InconsistentGeometryException("Invalid polynomial constants!");
		for (int i = 1; i < polynomialConstantCnt; i++) {
			if (polynomialConstants[i]) {
				RecursiveMultiplication(
					value * polynomialConstants[i],
					polynomialConstants, polynomialConstantCnt,
					myArray, myArrayParentIndex + i,
					i_n + 1, n
				);
			}
		}
	}
	else {
		if (i_n != n - 1) throw oip::InconsistentGeometryException("Invalid polynomial constants!");
		for (int i = 1; i < polynomialConstantCnt; i++) {
			if (polynomialConstants[i]) {
				if (myArrayParentIndex + i < n && myArrayParentIndex + i >= polynomialConstantCnt* n + 1)throw oip::InconsistentGeometryException("Invalid polynomial constants!");
				myArray[myArrayParentIndex + i] += value * polynomialConstants[i];
			}
		}
	}
}
/**********************************************************************************************/

/*!Calculate the Taylor series
* \param[in]  n                      number of iteration points
* \param[in]  polynomialConstants    polynomial constants for a polynomial term - a,b,c,d
* \param[in]  s                      the length of the curve between two points
*
* \return
*/
double	IntegralTaylorSeriesExpansionElement(
	const int n,
	const std::vector<double>& polynomialConstants,
	int polynomialConstantCnt,
	const double	s
)
{
	//
	//	pC = polynomialConstants
	//	c = polynomialConstantCnt
	// 	x =  indeterminate
	// 	   =>	pC[c-1] * x^(c-1) + pC[c-2] * x^(c-2) + ... + pC[1] * x^(1) + pC[0] * x^(0) where pC[0] == 0
	//
	if (polynomialConstantCnt && polynomialConstants[0] != 0.)throw oip::InconsistentGeometryException("Invalid polynomial constants!");

	if (n) {
//#ifdef _ALLOC
		std::vector<double> myArray(polynomialConstantCnt*n + 1);
//#else
		//std::vector<double> myArray = new double* [polynomialConstantCnt*n + 1]();
		//std::vector<double>  myArray = new double[polynomialConstantCnt * n + 1]();
//#endif

		RecursiveMultiplication(
			1.,
			polynomialConstants, polynomialConstantCnt,
			myArray, 0,
			0, n
		);

		double	value = 0., factor = 1.;
		for (int k = 0; k < polynomialConstantCnt * n + 1; k++) {
			factor *= s;
			value += myArray[k] * factor / (k + 1);
		}

		int	tB = n;
		while (tB > 1) {
			value /= (double)tB;
			tB--;
		}
/*
#ifdef _ALLOC
		free(myArray);
#else
		delete[] & myArray;
#endif
*/
		return	value;
	}
	else {
		return	s;
	}
}

double IntegralTaylorSeriesCosExpansion(
	const int i,
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	double	s
)
{
	double	value =
		IntegralTaylorSeriesExpansionElement(
			i * 2,
			polynomialConstants, polynomialConstantCnt,
			s
		);

	if (i % 2) {
		return	-value;
	}
	else {
		return	value;
	}
}

double	IntegralTaylorSeriesSinExpansion(
	const int i,
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	double	s
)
{
	double	value =
		IntegralTaylorSeriesExpansionElement(
			i * 2 + 1,
			polynomialConstants, polynomialConstantCnt,
			s
		);

	if (i % 2) {
		return	-value;
	}
	else {
		return	value;
	}
}

double	SpiralUtils::IntegralTaylorSeriesCos(
	const std::vector<double>& polynomialConstants,
	const int	polynomialConstantCnt,
	double	s
)
{
	int	minSteps = (polynomialConstantCnt > 7) ? 4 : 6, maxSteps = 8;
	double	borderValue = 0.000001;

	//
	// SUM [0 .. inf]
	//
	double value = 0.;

	int i = 0;
	for (; i < minSteps; i++) {
		value +=
			IntegralTaylorSeriesCosExpansion(
				i,
				polynomialConstants, polynomialConstantCnt,
				s
			);
	}

	if (polynomialConstantCnt > 7) {
		return	value;
	}

	for (; i < maxSteps; i++) {
		double	deviation =
			IntegralTaylorSeriesCosExpansion(
				i,
				polynomialConstants, polynomialConstantCnt,
				s
			);
		value += deviation;

		if (std::fabs(deviation) < borderValue) {
			return value;
		}
	}

	value +=
		IntegralTaylorSeriesCosExpansion(
			i,
			polynomialConstants, polynomialConstantCnt,
			s
		);

	if (i != maxSteps) throw oip::InconsistentGeometryException("Incorrect integral implementation");
	return value;
}

double	SpiralUtils::IntegralTaylorSeriesSin(
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	const double	s
)
{
	int	minSteps = (polynomialConstantCnt > 7) ? 4 : 6, maxSteps = 8;
	double	borderValue = 0.0000001;

	//
	// SUM [0 .. inf]
	//
	double value = 0.;

	int i = 0;
	for (; i < minSteps; i++) {
		value +=
			IntegralTaylorSeriesSinExpansion(
				i,
				polynomialConstants, polynomialConstantCnt,
				s
			);
	}

	if (polynomialConstantCnt > 7) {
		return	value;
	}

	for (; i < maxSteps; i++) {
		double	deviation =
			IntegralTaylorSeriesSinExpansion(
				i,
				polynomialConstants, polynomialConstantCnt,
				s
			);
		value += deviation;

		if (std::fabs(deviation) < borderValue) {
			return value;
		}
	}

	value +=
		IntegralTaylorSeriesSinExpansion(
			i,
			polynomialConstants, polynomialConstantCnt,
			s
		);

	if (i != maxSteps) throw oip::InconsistentGeometryException("Incorrect integral implementation");
	return value;
}


//
//	Numerical Integration
//


double	SpiralUtils::NumericalIntegrationCos(
	const double length,
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt
)
{
	double	factor = 1.,
		value = polynomialConstants[0];
	for (int i = 1; i < polynomialConstantCnt; i++) {
		factor *= length;
		value += polynomialConstants[i] * factor;
	}

	return	std::cos(value);
}

double	SpiralUtils::NumericalIntegrationSin(
	const double length,
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt
)
{
	double	factor = 1.,
		value = polynomialConstants[0];
	for (int i = 1; i < polynomialConstantCnt; i++) {
		factor *= length;
		value += polynomialConstants[i] * factor;
	}

	return	std::sin(value);
}

double	SpiralUtils::NumericalIntegrationCos(
	const double offset,
	const double length,
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	const double minWidth,
	const double angle
)
{
	double	P1y = SpiralUtils::NumericalIntegrationCos(offset + length / 6., polynomialConstants, polynomialConstantCnt);
	double	P2y = SpiralUtils::NumericalIntegrationCos(offset + length / 2., polynomialConstants, polynomialConstantCnt);
	double	P3y = SpiralUtils::NumericalIntegrationCos(offset + length - length / 6., polynomialConstants, polynomialConstantCnt);

	double	distance = 2. * (P2y - P1y) - (P3y - P1y);

	if ((length / 6. > minWidth) &&
		(distance > angle * length)) {
		double	a = SpiralUtils::NumericalIntegrationCos(offset, length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			b = SpiralUtils::NumericalIntegrationCos(offset + length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			c = SpiralUtils::NumericalIntegrationCos(offset + 2. * length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle);

		if (a * 3. > length) throw oip::InconsistentGeometryException("Incorrect length implementation");
		if (b * 3. > length) throw oip::InconsistentGeometryException("Incorrect length implementation");
		if (c * 3. > length) throw oip::InconsistentGeometryException("Incorrect length implementation");
		return	a + b + c;
	}

	return	(P1y + P2y + P3y) * length / 3.;
}

double	SpiralUtils::NumericalIntegrationSin(
	const double		offset,
	const double		length,
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	const double minWidth,
	const double angle
)
{
	double	P1y = SpiralUtils::NumericalIntegrationSin(offset + length / 6., polynomialConstants, polynomialConstantCnt);
	double	P2y = SpiralUtils::NumericalIntegrationSin(offset + length / 2., polynomialConstants, polynomialConstantCnt);
	double	P3y = SpiralUtils::NumericalIntegrationSin(offset + length - length / 6., polynomialConstants, polynomialConstantCnt);

	double	distance = 2. * (P2y - P1y) - (P3y - P1y);

	if ((length / 6. > minWidth) &&
		(distance > angle * length)) {
		double	a = SpiralUtils::NumericalIntegrationSin(offset, length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			b = SpiralUtils::NumericalIntegrationSin(offset + length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			c = SpiralUtils::NumericalIntegrationSin(offset + 2. * length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle);

		if (a * 3. > length) throw oip::InconsistentGeometryException("Incorrect length implementation");
		if (b * 3. > length) throw oip::InconsistentGeometryException("Incorrect length implementation");
		if (c * 3. > length) throw oip::InconsistentGeometryException("Incorrect length implementation");
		return	a + b + c;
	}

	return	(P1y + P2y + P3y) * length / 3.;
}

double	NumericalIntegrationCos__(
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	const double s
)
{
	int	initialPartCnt = 10;
	double	minWidth = 0.0000001, angle = 0.0000001;

	double	partSize = s / initialPartCnt, value = 0.;
	for (int i = 0; i < initialPartCnt; i++) {
		value +=
			SpiralUtils::NumericalIntegrationCos(
				i * partSize,
				partSize,
				polynomialConstants,
				polynomialConstantCnt,
				minWidth * s,
				angle * s
			);
	}

	return	value;
}

double	NumericalIntegrationSin__(
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	const double s
)
{
	int	initialPartCnt = 1000;
	double	minWidth = 0.0000001, angle = 0.0000001;

	double	partSize = s / initialPartCnt, value = 0.;
	for (int i = 0; i < initialPartCnt; i++) {
		value +=
			SpiralUtils::NumericalIntegrationSin(
				i * partSize,
				partSize,
				polynomialConstants,
				polynomialConstantCnt,
				minWidth * s,
				angle * s
			);
	}

	return	value;
}

double	SpiralUtils::NumericalIntegrationCos(
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	const double s
)
{
	if (s) {
//#ifdef _DEBUG
		double A;

		{
//#ifdef _ALLOC
			std::vector<double>localPolynomialConstants(polynomialConstantCnt);
			//double	* localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
//#else
//			std::vector<double>& localPolynomialConstants = new double [polynomialConstantCnt];
			//std::vector<double>& localPolynomialConstants = new double[polynomialConstantCnt];
//#endif

			for (int i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i];
			}

			double	value = NumericalIntegrationCos__(localPolynomialConstants, polynomialConstantCnt, s);
//
//#ifdef _ALLOC
//			free(localPolynomialConstants);
//#else
//			delete[] & localPolynomialConstants;
//#endif

			A = value;
		}
//#endif // _DEBUG

		double B;

		{
//#ifdef _ALLOC
			//std::vector<double>& localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
			std::vector<double>localPolynomialConstants(polynomialConstantCnt);
//#else
//			//std::vector<double>& localPolynomialConstants = new double[polynomialConstantCnt];
//			std::vector<double> localPolynomialConstants(polynomialConstantCnt);
//#endif

			double	factor = 1.;
			for (int i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i] * factor;
				factor *= s;
			}

			double	value = NumericalIntegrationCos__(localPolynomialConstants, polynomialConstantCnt, 1.);
//
//#ifdef _ALLOC
//			free(localPolynomialConstants);
//#else
//			delete[] & localPolynomialConstants;
//#endif

			B = s * value;
		}

		if (std::fabs(A - B) > 0.00001 * std::max(std::fabs(A), 1.)) throw oip::InconsistentGeometryException("Incorrect geometry implementation");

		return	B;
	}

	return	0.;
}

double	SpiralUtils::NumericalIntegrationSin(
	const std::vector<double>& polynomialConstants,
	const int polynomialConstantCnt,
	const double s
)
{
	if (s) {
//#ifdef _DEBUG
		double A;

		{
//#ifdef _ALLOC
			//std::vector<double>& localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
			std::vector<double>localPolynomialConstants(polynomialConstantCnt);
//#else
//			//std::vector<double>& localPolynomialConstants = new double[polynomialConstantCnt];
//			std::vector<double> localPolynomialConstants(polynomialConstantCnt);
//#endif

			for (int i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i];
			}

			double	value = NumericalIntegrationSin__(localPolynomialConstants, polynomialConstantCnt, s);

//#ifdef _ALLOC
//			free(localPolynomialConstants);
//#else
//			delete[] &localPolynomialConstants;
//#endif

			A = value;
		}
//#endif // _DEBUG

		double B;

		{
//#ifdef _ALLOC
			//const std::vector<double>& localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
			std::vector<double>localPolynomialConstants(polynomialConstantCnt);
//#else
//			//std::vector<double>& localPolynomialConstants = new double[polynomialConstantCnt];
//			std::vector<double> localPolynomialConstants(polynomialConstantCnt);
//#endif

			double	factor = 1.;
			for (int i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i] * factor;
				factor *= s;
			}

			double	value = NumericalIntegrationSin__(localPolynomialConstants, polynomialConstantCnt, 1.);
//
//#ifdef _ALLOC
//			free(localPolynomialConstants);
//#else
//			delete[] &localPolynomialConstants;
//#endif

			B = s * value;
		}

		if (std::fabs(A - B) > 0.000001 * std::max(std::fabs(A), 1.)) throw oip::InconsistentGeometryException("Incorrect integral implementation");

		return	B;
	}

	return	0.;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_END