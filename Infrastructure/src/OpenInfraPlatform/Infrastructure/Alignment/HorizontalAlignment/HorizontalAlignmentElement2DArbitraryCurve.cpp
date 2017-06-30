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

#include "HorizontalAlignmentElement2DArbitraryCurve.h"

#include "OpenInfraPlatform/Infrastructure/IfcPL/PythonInterpreter.h"
#include <BlueFramework/Core/Exception.h>
#include <windows.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class HorizontalAlignmentElement2DArbitraryCurve::HorizontalAlignmentElement2DArbitraryCurveImpl {
public:
	std::string strModulueName;

	HorizontalAlignmentElement2DArbitraryCurveImpl(const buw::Vector2d& start,
	                                               const buw::Vector2d& end,
	                                               const buw::Vector2d& pi,
	                                               const double length,
	                                               const double radiusStart,
	                                               const double radiusEnd,
	                                               const bool clockwise) {
		start_ = start;
		end_ = end;
		pi_ = pi;
		length_ = length;
		radiusStart_ = radiusStart;
		radiusEnd_ = radiusEnd;
		clockwise_ = clockwise;

		strModulueName = "clothoid";
		// strModulueName = "line";
	}

	virtual double getLength() const {
		//		PythonInterpreter& interperter = PythonInterpreter::getInstance();
		//
		//		pythonInterpreterDescription pyid;
		//		pyid.moduleName = strModulueName.c_str();
		//		pyid.functionName = "getLength";
		//		pyid.returnType = eType::Double;
		//		Vector2d start;
		//		start.x = start_.x();
		//		start.y = start_.y();
		//		Vector2d end;
		//		end.x = end_.x();
		//		end.y = end_.y();
		//		interperter.execute2(pyid, start, end, length_, radiusStart_, radiusEnd_, clockwise_ );
		//		return interperter.getDoubleValue();
		return 0.0;
	}

	buw::Vector2d getPosition(const double lerpParameter) const {
		//		PythonInterpreter& interperter = PythonInterpreter::getInstance();
		//		pythonInterpreterDescription pyid;
		//		pyid.moduleName = strModulueName.c_str();
		//		pyid.functionName = "getPosition";
		//
		//		std::stringstream ss;
		//		ss << lerpParameter;
		//
		//		pyid.arguments.push_back( argument(ss.str().c_str() , eType::Double) );
		//		pyid.returnType = eType::Vector2d;
		//		Vector2d start;
		//		start.x = start_.x();
		//		start.y = start_.y();
		//		Vector2d end;
		//		end.x = end_.x();
		//		end.y = end_.y();
		//		interperter.execute2(pyid, start, end, length_, radiusStart_, radiusEnd_, clockwise_ );
		//
		//		double x = interperter.getVector2dValue().x;
		//		double y = interperter.getVector2dValue().y;
		//
		//		return buw::Vector2d(x, y);

		return buw::Vector2d(0.0, 0.0);
	}

	bool genericQuery(const int id, void* result) const {
		return false;
	}

	eHorizontalAlignmentType getAlignmentType() const {
		return OpenInfraPlatform::Infrastructure::eHorizontalAlignmentType::Unknown;
	}

	buw::Vector2d getStartPosition() const {
		return start_;
	}

	buw::Vector2d getEndPosition() const {
		return end_;
	}

private:
	buw::Vector2d start_;
	buw::Vector2d end_;
	buw::Vector2d pi_;
	double length_;
	double radiusStart_;
	double radiusEnd_;
	bool clockwise_;
};

eHorizontalAlignmentType HorizontalAlignmentElement2DArbitraryCurve::getAlignmentType() const {
	return impl_->getAlignmentType();
}

bool HorizontalAlignmentElement2DArbitraryCurve::genericQuery(const int id, void* result) const {
	return impl_->genericQuery(id, result);
}

buw::Vector2d HorizontalAlignmentElement2DArbitraryCurve::getPosition(const double lerpParameter) const {
	return impl_->getPosition(lerpParameter);
}

buw::Vector2d HorizontalAlignmentElement2DArbitraryCurve::getTangent(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

buw::Vector2d HorizontalAlignmentElement2DArbitraryCurve::getNormal(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

double HorizontalAlignmentElement2DArbitraryCurve::getLength() const {
	return impl_->getLength();
}

HorizontalAlignmentElement2DArbitraryCurve::~HorizontalAlignmentElement2DArbitraryCurve() {
}

HorizontalAlignmentElement2DArbitraryCurve::HorizontalAlignmentElement2DArbitraryCurve(const buw::Vector2d& start,
                                                                                       const buw::Vector2d& end,
                                                                                       const buw::Vector2d& pi,
                                                                                       const double length,
                                                                                       const double radiusStart,
                                                                                       const double radiusEnd,
                                                                                       const bool clockwise)
    : impl_(new HorizontalAlignmentElement2DArbitraryCurveImpl(start, end, pi, length, radiusStart, radiusEnd, clockwise)) {
}

buw::Vector2d HorizontalAlignmentElement2DArbitraryCurve::getStartPosition() const {
	return impl_->getStartPosition();
}

buw::Vector2d HorizontalAlignmentElement2DArbitraryCurve::getEndPosition() const {
	return impl_->getEndPosition();
}

//----------------------------------------------------------------------------------------------

HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve(const buw::Vector2d startPosition,
                                                                                                                     const double startDirection,
                                                                                                                     const double startCurvature,
                                                                                                                     const bool counterClockwise,
                                                                                                                     const double clothoidConstant,
                                                                                                                     const bool entry,
                                                                                                                     const double length)
    : atc_(nullptr) {
	properties_.addVector2d("startPosition", startPosition);
	properties_.addDouble("startDirection", startDirection);
	properties_.addDouble("startCurvature", startCurvature);
	properties_.addBoolean("counterClockwise", counterClockwise);
	properties_.addDouble("clothoidConstant", clothoidConstant);
	properties_.addBoolean("entry", entry);
	properties_.addDouble("length", length);

	typedef IArbitraryTransitionCurve::IArbitraryTransitionCurve* (*LPcreateIArbitraryTransitionCurve)(buw::PropertySet & properties);

	wchar_t* filename = L"C:\\build\\vs2015\\IfcPL\\ExecutionEnvironment\\Debug\\Clothoid.dll";

	HMODULE hDLL = nullptr;
	hDLL = LoadLibraryEx(filename, nullptr, 0);

	if (!hDLL) {
		throw buw::Exception("DLL not found");
	}

	LPcreateIArbitraryTransitionCurve createIArbitraryTransitionCurve = nullptr;
	createIArbitraryTransitionCurve = (LPcreateIArbitraryTransitionCurve)GetProcAddress((HMODULE)hDLL, "createIArbitraryTransitionCurve");

	atc_ = createIArbitraryTransitionCurve(properties_);
}

buw::Vector2d HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::getPosition(const double lerpParameter) const {
	return atc_->getPostion(lerpParameter);
}

buw::Vector2d HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::getTangent(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

buw::Vector2d HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::getNormal(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

buw::Vector2d HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::getStartPosition() const {
	return atc_->getPostion(0.0);
}

buw::Vector2d HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::getEndPosition() const {
	return atc_->getPostion(1.0);
}

double HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::getLength() const {
	return atc_->getLength();
}

eHorizontalAlignmentType OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DIfcPLArbitraryTransitionCurve::getAlignmentType() const {
	return eHorizontalAlignmentType::Unknown;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END