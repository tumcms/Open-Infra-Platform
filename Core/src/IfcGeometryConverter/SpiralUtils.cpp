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

#include	"../stdafx.h"

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<assert.h>
#include	<cmath>


#include	"spiral.h"


void	RecursiveMultiplication(
	double	value,
	double	* polynomialConstants,
	uint_t	polynomialConstantCnt,
	double	* myArray,
	uint_t	myArrayParentIndex,
	uint_t	i_n,
	uint_t	n
)
{
	assert(value);
	if (i_n < n - 1) {
		assert(polynomialConstantCnt && polynomialConstants[0] == 0.);
		for (uint_t i = 1; i < polynomialConstantCnt; i++) {
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
		assert(i_n == n - 1);
		for (uint_t i = 1; i < polynomialConstantCnt; i++) {
			if (polynomialConstants[i]) {
				assert(myArrayParentIndex + i >= n && myArrayParentIndex + i < polynomialConstantCnt* n + 1);
				myArray[myArrayParentIndex + i] += value * polynomialConstants[i];
			}
		}
	}
}

double	IntegralTaylorSeriesExpansionElement(
	uint_t	n,
	double	* polynomialConstants,
	uint_t	polynomialConstantCnt,
	double	s
)
{
	//
	//	pC = polynomialConstants
	//	c = polynomialConstantCnt
	// 	x =  indeterminate
	// 	   =>	pC[c-1] * x^(c-1) + pC[c-2] * x^(c-2) + ... + pC[1] * x^(1) + pC[0] * x^(0) where pC[0] == 0
	//
	assert(polynomialConstantCnt && polynomialConstants[0] == 0.);

	if (n) {
#ifdef _ALLOC
		double	* myArray = (double*)calloc(polynomialConstantCnt * n + 1, sizeof(double));
#else
		double	* myArray = new double[polynomialConstantCnt * n + 1]();
#endif

		RecursiveMultiplication(
			1.,
			polynomialConstants, polynomialConstantCnt,
			myArray, 0,
			0, n
		);

		double	value = 0., factor = 1.;
		for (uint_t k = 0; k < polynomialConstantCnt * n + 1; k++) {
			factor *= s;
			value += myArray[k] * factor / (k + 1);
		}

		uint_t	tB = n;
		while (tB > 1) {
			value /= (double)tB;
			tB--;
		}

#ifdef _ALLOC
		free(myArray);
#else
		delete[] myArray;
#endif

		return	value;
	}
	else {
		return	s;
	}
}

double	IntegralTaylorSeriesCosExpansion(
	uint_t	i,
	double	* polynomialConstants,
	uint_t	polynomialConstantCnt,
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
	uint_t	i,
	double	* polynomialConstants,
	uint_t	polynomialConstantCnt,
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

double	IntegralTaylorSeriesCos(
	double	* polynomialConstants,
	uint_t	polynomialConstantCnt,
	double	s
)
{
	uint_t	minSteps = (polynomialConstantCnt > 7) ? 4 : 6, maxSteps = 8;
	double	borderValue = 0.000001;

	//
	// SUM [0 .. inf]
	//
	double value = 0.;

	uint_t i = 0;
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

	assert(i == maxSteps);
	return value;
}

double	IntegralTaylorSeriesSin(
	double	* polynomialConstants,
	uint_t	polynomialConstantCnt,
	double	s
)
{
	uint_t	minSteps = (polynomialConstantCnt > 7) ? 4 : 6, maxSteps = 8;
	double	borderValue = 0.0000001;

	//
	// SUM [0 .. inf]
	//
	double value = 0.;

	uint_t i = 0;
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

	assert(i == maxSteps);
	return value;
}


//
//	Numerical Integration
//


double	NumericalIntegrationCos(
	double		length,
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt
)
{
	double	factor = 1.,
		value = polynomialConstants[0];
	for (uint_t i = 1; i < polynomialConstantCnt; i++) {
		factor *= length;
		value += polynomialConstants[i] * factor;
	}

	return	std::cos(value);
}

double	NumericalIntegrationSin(
	double		length,
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt
)
{
	double	factor = 1.,
		value = polynomialConstants[0];
	for (uint_t i = 1; i < polynomialConstantCnt; i++) {
		factor *= length;
		value += polynomialConstants[i] * factor;
	}

	return	std::sin(value);
}

double	NumericalIntegrationCos(
	double		offset,
	double		length,
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt,
	double		minWidth,
	double		angle
)
{
	double	P1y = NumericalIntegrationCos(offset + length / 6., polynomialConstants, polynomialConstantCnt);
	double	P2y = NumericalIntegrationCos(offset + length / 2., polynomialConstants, polynomialConstantCnt);
	double	P3y = NumericalIntegrationCos(offset + length - length / 6., polynomialConstants, polynomialConstantCnt);

	double	distance = 2. * (P2y - P1y) - (P3y - P1y);

	if ((length / 6. > minWidth) &&
		(distance > angle * length)) {
		double	a = NumericalIntegrationCos(offset, length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			b = NumericalIntegrationCos(offset + length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			c = NumericalIntegrationCos(offset + 2. * length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle);

		assert(a * 3. <= length);
		assert(b * 3. <= length);
		assert(c * 3. <= length);
		return	a + b + c;
	}

	return	(P1y + P2y + P3y) * length / 3.;
}

double	NumericalIntegrationSin(
	double		offset,
	double		length,
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt,
	double		minWidth,
	double		angle
)
{
	double	P1y = NumericalIntegrationSin(offset + length / 6., polynomialConstants, polynomialConstantCnt);
	double	P2y = NumericalIntegrationSin(offset + length / 2., polynomialConstants, polynomialConstantCnt);
	double	P3y = NumericalIntegrationSin(offset + length - length / 6., polynomialConstants, polynomialConstantCnt);

	double	distance = 2. * (P2y - P1y) - (P3y - P1y);

	if ((length / 6. > minWidth) &&
		(distance > angle * length)) {
		double	a = NumericalIntegrationSin(offset, length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			b = NumericalIntegrationSin(offset + length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle),
			c = NumericalIntegrationSin(offset + 2. * length / 3., length / 3., polynomialConstants, polynomialConstantCnt, minWidth, angle);

		assert(a * 3. < length);
		assert(b * 3. < length);
		assert(c * 3. < length);
		return	a + b + c;
	}

	return	(P1y + P2y + P3y) * length / 3.;
}

double	NumericalIntegrationCos__(
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt,
	double		s
)
{
	int_t	initialPartCnt = 10;
	double	minWidth = 0.0000001, angle = 0.0000001;

	double	partSize = s / initialPartCnt, value = 0.;
	for (int_t i = 0; i < initialPartCnt; i++) {
		value +=
			NumericalIntegrationCos(
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
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt,
	double		s
)
{
	int_t	initialPartCnt = 1000;
	double	minWidth = 0.0000001, angle = 0.0000001;

	double	partSize = s / initialPartCnt, value = 0.;
	for (int_t i = 0; i < initialPartCnt; i++) {
		value +=
			NumericalIntegrationSin(
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

double	NumericalIntegrationCos(
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt,
	double		s
)
{
	if (s) {
#ifdef _DEBUG
		double A;

		{
#ifdef _ALLOC
			double	* localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
#else
			double	* localPolynomialConstants = new double[polynomialConstantCnt];
#endif

			for (uint_t i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i];
			}

			double	value = NumericalIntegrationCos__(localPolynomialConstants, polynomialConstantCnt, s);

#ifdef _ALLOC
			free(localPolynomialConstants);
#else
			delete[] localPolynomialConstants;
#endif

			A = value;
		}
#endif // _DEBUG

		double B;

		{
#ifdef _ALLOC
			double	* localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
#else
			double	* localPolynomialConstants = new double[polynomialConstantCnt];
#endif

			double	factor = 1.;
			for (uint_t i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i] * factor;
				factor *= s;
			}

			double	value = NumericalIntegrationCos__(localPolynomialConstants, polynomialConstantCnt, 1.);

#ifdef _ALLOC
			free(localPolynomialConstants);
#else
			delete[] localPolynomialConstants;
#endif

			B = s * value;
		}

		assert(std::fabs(A - B) < 0.00001 * _max_(std::fabs(A), 1.));

		return	B;
	}

	return	0.;
}

double	NumericalIntegrationSin(
	double		* polynomialConstants,
	uint_t		polynomialConstantCnt,
	double		s
)
{
	if (s) {
#ifdef _DEBUG
		double A;

		{
#ifdef _ALLOC
			double	* localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
#else
			double	* localPolynomialConstants = new double[polynomialConstantCnt];
#endif

			for (uint_t i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i];
			}

			double	value = NumericalIntegrationSin__(localPolynomialConstants, polynomialConstantCnt, s);

#ifdef _ALLOC
			free(localPolynomialConstants);
#else
			delete[] localPolynomialConstants;
#endif

			A = value;
		}
#endif // _DEBUG

		double B;

		{
#ifdef _ALLOC
			double	* localPolynomialConstants = (double*)malloc(polynomialConstantCnt * sizeof(double));
#else
			double	* localPolynomialConstants = new double[polynomialConstantCnt];
#endif

			double	factor = 1.;
			for (uint_t i = 0; i < polynomialConstantCnt; i++) {
				localPolynomialConstants[i] = polynomialConstants[i] * factor;
				factor *= s;
			}

			double	value = NumericalIntegrationSin__(localPolynomialConstants, polynomialConstantCnt, 1.);

#ifdef _ALLOC
			free(localPolynomialConstants);
#else
			delete[] localPolynomialConstants;
#endif

			B = s * value;
		}

		assert(std::fabs(A - B) < 0.000001 * _max_(std::fabs(A), 1.));

		return	B;
	}

	return	0.;
}
