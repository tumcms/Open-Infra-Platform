/*
    Copyright (c) 2017 Technical University of Munich
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

#include "gtest/gtest.h"

#include "buw.OIPInfrastructure.h"

#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/Math/quaternion.h>
#include <BlueFramework/Core/Math/util.h>
#include <BlueFramework/Core/Math/matrix.h>

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

namespace
{
	// TestClothoide Kreisbogen - Klothoide - Kreisbogen 
	TEST(HorizontalAlignmentElement2DClothoid, getPosition)
	{
		using namespace buw;

		Vector2d start = buw::Vector2d(861.369007, 537.722476);
		Vector2d end = buw::Vector2d(930.775243, 503.483954);
		Vector2d pi = buw::Vector2d(896.290146, 516.54507);

		double length = 77.500241;
		double radiusStart = 500;
		double radiusEnd = 367;
		bool clockwise = false;

		/*<Spiral length="77.500241" radiusEnd="367.000000" radiusStart="500.000000" rot="ccw" spiType="clothoid" constant="326.996979" dirEnd="4.3503375925" dirStart="4.1672511921" theta="0.1830864004" totalY="7.435685" totalX="-77.033840" staStart="628.971429" tanLong="40.840770" tanShort="36.875665">
		<Start>5333537.722476 4467861.369007</Start>
		<PI>5333516.54507 4467896.290146</PI>
		<End>5333503.483954 </End>
		</Spiral>*/

		buw::ReferenceCounted<HorizontalAlignmentElement2DClothoid_old> c =
			std::make_shared<HorizontalAlignmentElement2DClothoid_old>(start, end, pi, length, radiusStart, radiusEnd, clockwise);

		Vector2d calculatedStartPoint = c->getPosition(0);
		Vector2d test1 = c->getPosition(0.3);
		Vector2d test2 = c->getPosition(0.5);
		Vector2d test3 = c->getPosition(0.7);
		Vector2d calculatedEndPoint = c->getPosition(1);

		// std::cout << calculatedStartPoint.x() << " " << calculatedStartPoint.y() << std::endl;
		// std::cout << test1.x() << " " << test1.y() << std::endl;
		// std::cout << test2.x() << " " << test2.y() << std::endl;
		// std::cout << test3.x() << " " << test3.y() << std::endl;
		// std::cout << calculatedEndPoint.x() << " " << calculatedEndPoint.y() << std::endl;

		EXPECT_NEAR(buw::distance(calculatedStartPoint, start), 0.0, 0.001);
		EXPECT_NEAR(buw::distance(calculatedEndPoint, end), 0.0, 0.001);
	}

	// TestClothoide Kreisbogen - Klothoide - Kreisbogen | ccw | endCurvature<startCurvature
	TEST(HorizontalAlignmentElement2DClothoid, getPosition2)
	{
		using namespace buw;

		Vector2d start = Vector2d(4468141.633883, 5333462.303922);
		Vector2d end = Vector2d(4468161.038359, 5333457.490118);
		Vector2d pi = Vector2d(4468151.242887, 5333460.115737);
		double length = 19.993861;
		double radiusStart = 504.7;
		double radiusEnd = 550;
		bool clockwise = true;

		/*<Spiral length="19.993861" radiusEnd="550.000000" radiusStart="504.700000" rot="cw" spiType="clothoid" constant="350.023522" dirEnd="4.4505010013" dirStart="4.4884849075" theta="0.0379839062" totalY="0.374242" totalX="-19.989156" staStart="921.745754" tanLong="10.141260" tanShort="9.855004">
		<Start>5333462.303922 4468141.633883</Start>
		<PI>5333460.115737 4468151.242887</PI>
		<End>5333457.490118 4468161.038359</End>
		</Spiral>*/

		buw::ReferenceCounted<HorizontalAlignmentElement2DClothoid_old> c =
			std::make_shared<HorizontalAlignmentElement2DClothoid_old>(start, end, pi, length, radiusStart, radiusEnd, clockwise);

		Vector2d calculatedEndPoint = c->getPosition(1);
		Vector2d vec = end - calculatedEndPoint;
		double dist = (vec).norm();

		EXPECT_NEAR(dist, 0, 0.01);
	}

	// TestClothoide Kreisbogen - Klothoide - Kreisbogen | cw | endCurvature<startCurvature
	TEST(HorizontalAlignmentElement2DClothoid, getPosition3)
	{
		buw::Vector2d start = buw::Vector2d(4468892.91057, 5333153.356899);
		buw::Vector2d end = buw::Vector2d(4468943.390419, 5333121.729338);
		buw::Vector2d pi = buw::Vector2d(4468916.250799, 5333140.660668);
		double length = 59.600185;
		double radiusStart = 404.7;
		double radiusEnd = 800;
		bool clockwise = true;

		/*<Spiral length="59.600185" radiusEnd="800.000000" radiusStart="404.700000" rot="cw" spiType="clothoid" constant="220.938801" dirEnd="4.1033070374" dirStart="4.2141921728" theta="0.1108851354" totalY="2.940175" totalX="-59.496833" staStart="1736.556752" tanLong="33.090093" tanShort="26.569919">
		<Start>5333153.356899 4468892.91057</Start>
		<PI>5333140.660668 4468916.250799</PI>
		<End>5333121.729338 4468943.390419</End>
		</Spiral>*/

		double startCurvature = 0;
		if (radiusStart != 0 && radiusStart != std::numeric_limits<double>::infinity())
			startCurvature = 1 / radiusStart;

		double endCurvature = 0;
		if (radiusEnd != 0 && radiusEnd != std::numeric_limits<double>::infinity())
			endCurvature = 1 / radiusEnd;

		double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
		double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
		bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

		buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> c =
			std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		buw::Vector2d calculatedEndPoint = c->getPosition(1);
		buw::Vector2d vec = end - calculatedEndPoint;
		double dist = (vec).norm();

		EXPECT_NEAR(dist, 0, 0.01);
	}

	// TestClothoide Gerade - Klothoide - Kreisbogen | cw | startCurvature<endCurvature
	TEST(HorizontalAlignmentElement2DClothoid, getPosition4)
	{
		buw::Vector2d start = buw::Vector2d(4467579.352923, 5333698.667465);
		buw::Vector2d end = buw::Vector2d(4467669.348813, 5333655.171404);
		buw::Vector2d pi = buw::Vector2d(4467640.34223, 5333671.659422);

		double length = 100.000266;
		double radiusStart = std::numeric_limits<double>::infinity();
		double radiusEnd = 500;
		bool clockwise = true;

		/*<Spiral length="100.000266" radiusEnd="500.000000" radiusStart="INF" rot="cw" spiType="clothoid" constant="223.607095" dirEnd="4.1955113073" dirStart="4.2955115733" theta="0.1000002660" totalY="3.330971" totalX="99.900311" staStart="302.319042" tanLong="66.701798" tanShort="33.365201">
		<Start>5333698.667465 4467579.352923</Start>
		<PI>5333671.659422 4467640.34223</PI>
		<End>5333655.171404 4467669.348813</End>
		</Spiral>*/

		double startCurvature = 0;
		if (radiusStart != 0 && radiusStart != std::numeric_limits<double>::infinity())
			startCurvature = 1 / radiusStart;

		double endCurvature = 0;
		if (radiusEnd != 0 && radiusEnd != std::numeric_limits<double>::infinity())
			endCurvature = 1 / radiusEnd;

		double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
		double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
		bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

		buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> c =
			std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		buw::Vector2d calculatedStartPoint = c->getPosition(0);
		buw::Vector2d test1 = c->getPosition(0.3);
		buw::Vector2d test2 = c->getPosition(0.5);
		buw::Vector2d test3 = c->getPosition(0.7);
		buw::Vector2d calculatedEndPoint = c->getPosition(1);

		// std::cout << calculatedStartPoint.x() << " " << calculatedStartPoint.y() << std::endl;
		// std::cout << test1.x() << " " << test1.y() << std::endl;
		// std::cout << test2.x() << " " << test2.y() << std::endl;
		// std::cout << test3.x() << " " << test3.y() << std::endl;
		// std::cout << calculatedEndPoint.x() << " " << calculatedEndPoint.y() << std::endl;

		buw::Vector2d vec = end - calculatedEndPoint;
		double dist = (vec).norm();

		EXPECT_NEAR(dist, 0, 0.01);
	}


	// TestClothoide Gerade - Klothoide - Kreisbogen | ccw | startCurvature<endCurvature
	TEST(HorizontalAlignmentElement2DClothoid, getPosition5)
	{
		buw::Vector2d start = buw::Vector2d(4467794.606875, 5333585.591109);
		buw::Vector2d end = buw::Vector2d(4467823.174087, 5333563.360072);
		buw::Vector2d pi = buw::Vector2d(4467813.473859, 5333570.539786);

		double length = 36.200238;
		double radiusStart = std::numeric_limits<double>::infinity();
		double radiusEnd = 500;
		bool clockwise = false;

		/*<Spiral length="36.200238" radiusEnd="500.000000" radiusStart="INF" rot="ccw" spiType="clothoid" constant="134.536683" dirEnd="4.0752157061" dirStart="4.0390154681" theta="0.0362002380" totalY="0.436778" totalX="36.195494" staStart="546.753448" tanLong="24.135149" tanShort="12.068252">
		<Start>5333585.591109 4467794.606875</Start>
		<PI>5333570.539786 4467813.473859</PI>
		<End>5333563.360072 4467823.174087</End>
		</Spiral>*/

		double startCurvature = 0;
		if (radiusStart != 0 && radiusStart != std::numeric_limits<double>::infinity())
			startCurvature = 1 / radiusStart;

		double endCurvature = 0;
		if (radiusEnd != 0 && radiusEnd != std::numeric_limits<double>::infinity())
			endCurvature = 1 / radiusEnd;

		double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
		double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
		bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

		buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> c =
			std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		buw::Vector2d calculatedStartPoint = c->getPosition(0);
		buw::Vector2d test1 = c->getPosition(0.3);
		buw::Vector2d test2 = c->getPosition(0.5);
		buw::Vector2d test3 = c->getPosition(0.7);
		buw::Vector2d calculatedEndPoint = c->getPosition(1);

		// std::cout << calculatedStartPoint.x() << " " << calculatedStartPoint.y() << std::endl;
		// std::cout << test1.x() << " " << test1.y() << std::endl;
		// std::cout << test2.x() << " " << test2.y() << std::endl;
		// std::cout << test3.x() << " " << test3.y() << std::endl;
		// std::cout << calculatedEndPoint.x() << " " << calculatedEndPoint.y() << std::endl;

		buw::Vector2d vec = end - calculatedEndPoint;
		double dist = (vec).norm();

		EXPECT_NEAR(dist, 0, 0.01);
	}

	// TestClothoide Kreisbogen - Klothoide - Gerade  | ccw | endCurvature<startCurvature
	TEST(HorizontalAlignmentElement2DClothoid, getPosition6)
	{
		buw::Vector2d start = buw::Vector2d(4467972.527169, 5333490.457365);
		buw::Vector2d end = buw::Vector2d(4468049.83656, 5333477.066945);
		buw::Vector2d pi = buw::Vector2d(4467997.954109, 5333484.159277);

		double length = 78.500368;
		double radiusStart = 367;
		double radiusEnd = std::numeric_limits<double>::infinity();
		bool clockwise = false;

		/*	<Spiral length="78.500368" radiusEnd="INF" radiusStart="367.000000" rot="ccw" spiType="clothoid" constant="169.734013" dirEnd="4.5765310421" dirStart="4.4695823119" theta="0.1069487302" totalY="2.796219" totalX="-78.410627" staStart="750.234482" tanLong="52.364968" tanShort="26.195327">
		<Start>5333490.457365 4467972.527169</Start>
		<PI>5333484.159277 4467997.954109</PI>
		<End>5333477.066945 4468049.83656</End>
		</Spiral>*/

		double startCurvature = 0;
		if (radiusStart != 0 && radiusStart != std::numeric_limits<double>::infinity())
			startCurvature = 1 / radiusStart;

		double endCurvature = 0;
		if (radiusEnd != 0 && radiusEnd != std::numeric_limits<double>::infinity())
			endCurvature = 1 / radiusEnd;

		double startDirection = buw::HorizontalAlignmentElement2DClothoid::computeStartDirection(start, pi);
		double clothoidConstant = buw::HorizontalAlignmentElement2DClothoid::computeClothoidConstant(length, startCurvature, endCurvature);
		bool entry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);

		buw::clothoidDescription desc(start, startDirection, startCurvature, !clockwise, clothoidConstant, entry, length);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> c =
			std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

		buw::Vector2d calculatedStartPoint = c->getPosition(0);
		buw::Vector2d test1 = c->getPosition(0.3);
		buw::Vector2d test2 = c->getPosition(0.5);
		buw::Vector2d test3 = c->getPosition(0.7);
		buw::Vector2d calculatedEndPoint = c->getPosition(1);

		// std::cout << calculatedStartPoint.x() << " " << calculatedStartPoint.y() << std::endl;
		// std::cout << test1.x() << " " << test1.y() << std::endl;
		// std::cout << test2.x() << " " << test2.y() << std::endl;
		// std::cout << test3.x() << " " << test3.y() << std::endl;
		// std::cout << calculatedEndPoint.x() << " " << calculatedEndPoint.y() << std::endl;

		buw::Vector2d vec = end - calculatedEndPoint;
		double dist = (vec).norm();

		EXPECT_NEAR(dist, 0, 0.01);
	}

	void checkComputeClothidEndPoint(const std::string &filename)
	{
		buw::ImportLandXml parser(filename.c_str());

		std::vector<buw::ReferenceCounted<buw::IAlignment3D>> alignments = parser.getAlignmentModel()->getAlignments();

		buw::Vector3d offset = alignments[0]->getPosition(alignments[0]->getStartStation());

		for (int k = 0; k < alignments.size(); k++)
		{
			buw::ReferenceCounted<buw::IAlignment3D> a3 = alignments[k];

			if (a3->getType() == buw::e3DAlignmentType::e2DBased)
			{
				buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(a3);

				for (int i = 0; i < a->getHorizontalAlignment()->getAlignmentElementCount(); i++)
				{
					auto he = a->getHorizontalAlignment()->getAlignmentElementByIndex(i);

					if (he->getAlignmentType() == buw::eHorizontalAlignmentType::Clothoid)
					{
						// Start point
						buw::Vector2d startPoint = he->getStartPosition();
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &startPoint);

						// End point
						buw::Vector2d endPoint = he->getEndPosition();

						//std::cout << "End point: " << std::setprecision(10) << endPoint << std::endl;

						// PI
						buw::Vector2d piPoint;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI, &piPoint);

						//std::cout << "Point of intersection: " << std::setprecision(10) << piPoint << std::endl;

						// Radius Start
						double RadiusStart = 0;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart, &RadiusStart);
						//std::cout << "Start radius: " << RadiusStart << std::endl;

						// Radius End
						double RadiusEnd = 0;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd, &RadiusEnd);
						//std::cout << "End radius: " << RadiusEnd << std::endl;

						double A = 0;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::ClothoidConstant, &A);
						//std::cout << "A: " << A << std::endl;

						double L = 0;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Length, &L);
						//std::cout << "L: " << L << std::endl;

						double startCurvature = 0;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureStart, &startCurvature);

						double endCurvature = 0;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureEnd, &endCurvature);

						bool clockwise = 0;
						he->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise, &clockwise);
						//std::cout << "Clockwise: " << clockwise << std::endl;
												

						double computedEndRadius = buw::HorizontalAlignmentElement2DClothoid_old::computeEndRadius(A, L, RadiusStart, startCurvature < endCurvature);

						//std::cout << "Computed end radius: " << computedEndRadius << std::endl;

						if (computedEndRadius != std::numeric_limits<double>::infinity())
						{
							BLUE_ASSERT(std::abs(computedEndRadius - RadiusEnd) < 0.001, "Invalid end radius");
							EXPECT_NEAR(std::abs(computedEndRadius - RadiusEnd), 0.0, 0.001);
						}

						buw::Vector2d tmsl = piPoint - startPoint;

						auto computedEndPoint = buw::HorizontalAlignmentElement2DClothoid_old::computeEndPoint(
							startPoint,
							buw::calculateAngleBetweenVectors(buw::Vector2d(1.0, 0.0), tmsl),
							L,
							RadiusStart,
							!clockwise,
							startCurvature < endCurvature,
							A);

						//std::cout << "Computed end point: " << computedEndPoint << std::endl;
						//std::cout << std::setprecision(10) << "Difference: " << (computedEndPoint - endPoint) << std::endl;

						if (startCurvature != 0 && endCurvature != 0)
						{
							EXPECT_NEAR(buw::distance(computedEndPoint, endPoint), 0.0, 0.1);
						}
						else
						{
							EXPECT_NEAR(buw::distance(computedEndPoint, endPoint), 0.0, 0.001);
						}

						//std::cout << "---------------------------------------------------------------------" << std::endl;
					}
				}
			}
		}
	}

	struct HughClothoidData
	{
		double easting;
		double northing;
		double startDirection;
		double startRadius;
		bool isCcw;
		double spiralA;
		bool isEntry;
		double segmentLength;
	};

	std::ostream& operator<<(std::ostream& out, const HughClothoidData& clothoid)
	{
		out << clothoid.easting << std::endl;
		out << clothoid.northing << std::endl;
		out << clothoid.startDirection << std::endl;
		out << clothoid.startRadius << std::endl;
		out << clothoid.isCcw << std::endl;
		out << clothoid.spiralA << std::endl;
		out << clothoid.isEntry << std::endl;
		out << clothoid.segmentLength << std::endl;

		const double& A = clothoid.spiralA;
		const double& L = clothoid.segmentLength;
		const bool isCcw = clothoid.isCcw;

		double fullSpiralLength = buw::HorizontalAlignmentElement2DClothoid_old::computeFulllLength(clothoid.isEntry, A, clothoid.startRadius, L);
		double turnedAngle = buw::HorizontalAlignmentElement2DClothoid_old::computeTurnedAngle(clothoid.segmentLength, fullSpiralLength, A);
		double endDirection = buw::HorizontalAlignmentElement2DClothoid_old::computeEndDirection(clothoid.startDirection, isCcw, turnedAngle);
		double spiralOriginProjection = buw::HorizontalAlignmentElement2DClothoid_old::computeOriginProjection(clothoid.isEntry, clothoid.segmentLength, clothoid.spiralA, fullSpiralLength);
		double spiralOriginOffset = buw::HorizontalAlignmentElement2DClothoid_old::computeOriginOffset(clothoid.isEntry, clothoid.segmentLength, clothoid.spiralA, fullSpiralLength, isCcw);
		double endPointProjection = buw::HorizontalAlignmentElement2DClothoid_old::computeEndPointProjection(clothoid.isEntry, clothoid.segmentLength, clothoid.spiralA, fullSpiralLength);

		//std::cout << "FullSpiralLength: " << fullSpiralLength << std::endl;
		//std::cout << "turnedAngle: " << turnedAngle << std::endl;
		//std::cout << "endDirection: " << endDirection << std::endl;
		//std::cout << "spiralOriginProjection: " << spiralOriginProjection << std::endl;
		//std::cout << "spiralOriginOffset: " << spiralOriginOffset << std::endl;
		//std::cout << "endPointProjection: " << endPointProjection << std::endl;
		
		double endPoint_x = clothoid.easting + endPointProjection * std::cos(clothoid.startDirection) - spiralOriginOffset * std::sin(clothoid.startDirection);

		//std::cout << "endPoint_x = " << endPoint_x << std::endl;

		return out;
	}

	TEST(HorizontalAlignmentElement2DClothoid, ComputeClothoidEndPoint)
	{
		/*
		{
			HughClothoidData d1;
			d1.easting = 74490.3706;
			d1.northing = 631959.4274;
			d1.startDirection = -2.6100066732051;
			d1.startRadius = 0.0;
			d1.isCcw = false;
			d1.spiralA = 351.198661728657;
			d1.isEntry = true;
			d1.segmentLength = 27.4090000000001;

			std::cout << d1 << std::endl;

			HughClothoidData d2;
			d2.easting = 72735.5756;
			d2.northing = 631358.4488;
			d2.startDirection = -2.9888566732051;
			d2.startRadius = 0;
			d2.isCcw = true;
			d2.spiralA = 353.624094201738;
			d2.isEntry = true;
			d2.segmentLength = 61.0;

			std::cout << d2 << std::endl;
		}
		*/
		
		std::vector<std::string> filenames;
		filenames.push_back("../testdata/LandXML/AutoCAD Civil 3D/debug2.xml");
		filenames.push_back("../testdata/LandXML/AutoCAD Civil 3D/debug.xml");
		filenames.push_back("../testdata/LandXML/B15n_Data/B15n_Trasse.xml");
		filenames.push_back("../testdata/LandXML/Mainbruecke_Klingenberg.xml");
		filenames.push_back("../testdata/LandXML/AutoCAD Civil 3D/LandXMLDemo.xml");
		filenames.push_back("../testdata/LandXML/Bilbao/Bilbao.xml");
	
		for (int i = 0; i < filenames.size(); i++)
		{
			checkComputeClothidEndPoint(filenames[i]);
		}
	}
}