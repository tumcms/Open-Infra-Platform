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

//#include <iostream>
//#include <boost/python.hpp>
//#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
//#include <string>
//#include <functional>
//
//
//#include <QtXml>
//#include <QtXmlPatterns>
//
//#include <BlueFramework/Core/Math/vector.h>
//#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
//
//#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignment2D.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
//
//#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignment2D.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DArc.h"
//#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"
//
//#include "OpenInfraPlatform/Infrastructure/Import/LandXmlImport.h"
//#include "OpenInfraPlatform/Infrastructure/Import/OSMImport.h"
//#include "OpenInfraPlatform/Infrastructure/Import/IfcAlignmentImport.h"
//#include "OpenInfraPlatform/Infrastructure/Import/IfcRoadImport.h"
//#include "OpenInfraPlatform/Infrastructure/Import/OkstraImport.h"
//#include "OpenInfraPlatform/Infrastructure/Import/RoadXMLImport.h"
//
//
//template<typename T, int size>
//void setX(buw::Vector<T, size>& vector, T value)
//{
//	vector.x() = value;
//}
//
//template<typename T, int size>
//double getX(const buw::Vector<T, size>& vector)
//{
//	return vector.x();
//}
//
//template<typename T, int size>
//void setY(buw::Vector<T, size>& vector, T value)
//{
//	vector.y() = value;
//}
//
//template<typename T, int size>
//double getY(const buw::Vector<T, size>& vector)
//{
//	return vector.y();
//}
//
//template<typename T, int size>
//void setZ(buw::Vector<T, size>& vector, T value)
//{
//	vector.z() = value;
//}
//
//template<typename T, int size>
//double getZ(const buw::Vector<T, size>& vector)
//{
//	return vector.z();
//}
//
//template<typename T, int size>
//void setW(buw::Vector<T, size>& vector, T value)
//{
//	vector.w() = value;
//}
//
//template<typename T, int size>
//double getW(const buw::Vector<T, size>& vector)
//{
//	return vector.w();
//}
//
//template<typename T, int size>
//std::string Str(const buw::Vector<T, size>& vector)
//{
//	std::stringstream ss;
//	ss << vector;
//	return ss.str();
//}
//
//template<typename T, int size>
//std::string Repr(const buw::Vector<T, size>& vector)
//{
//	std::stringstream ss;
//	ss << "Vector" << size << " " << vector;
//	return ss.str();
//}
//
//template<typename T>
//T copy(const T& t)
//{
//	return t;
//}
//
//template<typename T>
//T& vectorGet(std::vector<T>& v, int i)
//{
//	return v[i];
//}
//
//template<typename T>
//void vectorSet(std::vector<T>& v, int i, T& t)
//{
//	v[i] = t;
//}
//
//
//buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> getAlignmentElementByStationing(const buw::HorizontalAlignment2D& ha, const buw::Stationing station)
//{
//	return ha.getAlignmentElementByStationing(station);
//}
//
//boost::shared_ptr<buw::OSMImport> OSMImportConstr(const std::string& filename, boost::python::list& list, int mode)
//{
//	boost::shared_ptr<buw::OSMImport> obj;
//	std::vector<std::string> filter;
//	for (int i = 0; i < boost::python::len(list); i++)
//	{
//		filter.push_back(boost::python::extract<std::string>(list[i]));
//	}
//
//	obj.reset(new buw::OSMImport(filename, filter, mode));
//	return obj;
//}
//
//boost::python::list getOSMDefaultFilter()
//{
//	boost::python::list list;
//	for (const std::string& str : buw::OSMImport::getDefaultFilter())
//	{
//		list.append(str);
//	}
//
//	return list;
//}
//
//buw::Vector3d getMinimum(const buw::AxisAlignedBoundingBox3d& bb)
//{
//	return bb.getMinimum();
//}
//
//buw::Vector3d getMaximum(const buw::AxisAlignedBoundingBox3d& bb)
//{
//	return bb.getMaximum();
//}
//
//buw::ReferenceCounted<buw::AlignmentModel> simplifiedImport(const std::string& filename)
//{
//	buw::ReferenceCounted<buw::AlignmentModel> alignmentModel = std::make_shared<buw::AlignmentModel>();
//
//	buw::String buwstrFilename = filename.c_str();
//	if (buwstrFilename.toLower().endsWith(".xml"))
//	{
//		QDomDocument xmlBOM;
//		QFile f(filename.c_str());
//		if (!f.open(QIODevice::ReadOnly))
//		{
//			std::cerr << "Error while loading file" << std::endl;
//			throw std::runtime_error("Error while loading file");
//		}
//
//		xmlBOM.setContent(&f);
//		f.close();
//		QDomElement root = xmlBOM.documentElement();
//		std::string type = root.tagName().toStdString();
//		if (buw::String(type).startsWith("Land"))
//		{
//			buw::LandXmlImport import(filename);
//			alignmentModel = import.getAlignmentModel();
//		}
//		else
//		{
//			buw::OkstraImport import(filename);
//			alignmentModel = import.getAlignmentModel();
//		}
//	}
//	else if (buwstrFilename.toLower().endsWith(".cte"))
//	{
//		buw::OkstraImport import(filename);
//		alignmentModel = import.getAlignmentModel();
//	}
//	else if (buwstrFilename.toLower().endsWith(".rnd"))
//	{
//		buw::IfcRoadImport import(filename);
//		alignmentModel = import.getAlignmentModel();
//	}
//	else if (buwstrFilename.toLower().endsWith(".ifc"))
//	{
//		buw::IfcAlignmentImport import(filename);
//		alignmentModel = import.getAlignmentModel();
//	}
//	else if (buwstrFilename.toLower().endsWith(".osm"))
//	{
//		buw::OSMImport import(filename);
//		alignmentModel = import.getAlignmentModel();
//	}
//
//
//	return alignmentModel;
//}
//
//namespace boost
//{
//	namespace python
//	{
//		//template<typename T, int size>
//		//class_<buw::Vector<T, size>> defineVector(char const* classname)
//		//{
//		//	return class_<buw::Vector<T, size>>(classname)
//		//		.def(init<T>())
//		//		.def(init<const buw::Vector<T, size>&>())
//		//		.def("__copy__", copy<buw::Vector<T, size>>)
//		//		.def("__str__", &Str<T, size>)
//		//		.def("__repr__", &Repr<T, size>)
//		//		.def("zero", &buw::Vector<T, size>::zero, return_value_policy<copy_non_const_reference>())
//		//		.def("normalize", &buw::Vector<T, size>::normalize, return_value_policy<copy_non_const_reference>())
//		//		.def("clamp", &buw::Vector<T, size>::clamp, return_value_policy<copy_non_const_reference>())
//		//		.def("saturate", &buw::Vector<T, size>::saturate, return_value_policy<copy_non_const_reference>())
//		//		.def("getMaxElement", &buw::Vector<T, size>::getMaxElement)
//		//		.def("getMinElement", &buw::Vector<T, size>::getMinElement)
//		//		.def("length", &buw::Vector<T, size>::length)
//		//		.def("cwiseInverse", &buw::Vector<T, size>::cwiseInverse)
//		//		.def("cwiseProduct", &buw::Vector<T, size>::cwiseProduct)
//		//		.def("lengthSquared", &buw::Vector<T, size>::lengthSquared)
//		//		//.def("squaredLength", &buw::Vector<T, size>::squaredLength) does not work ?
//		//		.def(self + self)
//		//		.def(self - self)
//		//		.def(self += self)
//		//		.def(self -= self)
//		//		.def(self *= T())
//		//		.def(self /= T())
//		//		.def(self == self)
//		//		.def(self != self)
//		//		;
//		//}
//
//		template<typename T, int size>
//		class_<buw::Vector<T, size>> defineVector(char const* classname)
//		{
//			return class_<buw::Vector<T, size>>(classname)
//				.def(init<T>())
//				.def(init<const buw::Vector<T, size>&>())
//				.def("__copy__", &copy<buw::Vector<T, size>>)
//				.def("__str__",		&Str<T, size>)
//				.def("__repr__", &Repr<T, size>)
//				.def("normalize", &buw::Vector<T, size>::normalized, return_value_policy<copy_non_const_reference>())
//				.def("norm", &buw::Vector<T, size>::norm)
//				.def("cwiseInverse", &buw::Vector<T, size>::cwiseInverse)
//				.def("squaredNorm", &buw::Vector<T, size>::squaredNorm)
//				//.def("squaredLength", &buw::Vector<T, size>::squaredLength) does not work ?
//				.def(self + self)
//				.def(self - self)
//				.def(self += self)
//				.def(self -= self)
//				.def(self *= T())
//				.def(self /= T())
//				.def(self == self)
//				.def(self != self)
//				;
//		}
//	}
//}
//
//BOOST_PYTHON_MODULE(Infrastructure)
//{
//	using namespace boost::python;
//
//	defineVector<double, 2>("vector2d")
//		.def(init<double, double>())
//		.add_property("x", &getX<double, 2>, &setX<double, 2>)
//		.add_property("y", &getY<double, 2>, &setY<double, 2>)
//		;
//
//	defineVector<double, 3>("Vector3d")
//		.def(init<double, double, double>())
//		.add_property("x", &getX<double, 3>, &setX<double, 3>)
//		.add_property("y", &getY<double, 3>, &setY<double, 3>)
//		.add_property("z", &getZ<double, 3>, &setZ<double, 3>)
//		;
//
//	defineVector<double, 4>("vector4d")
//		.def(init<double, double, double, double>())
//		.add_property("x", &getX<double, 4>, &setX<double, 4>)
//		.add_property("y", &getY<double, 4>, &setY<double, 4>)
//		.add_property("z", &getZ<double, 4>, &setZ<double, 4>)
//		.add_property("w", &getW<double, 4>, &setW<double, 4>)
//		;
//
//	/*def("distance", buw::distance<double, 2>);
//	def("distance", buw::distance<double, 3>);
//	def("distance", buw::distance<double, 4>);
//	*/
//
//	/*
//	def("normalize", buw::normalize<double, 2>);
//	def("normalize", buw::normalize<double, 3>);
//	def("normalize", buw::normalize<double, 4>);
//	*/
//
//	/*
//	def("length", BlueFramework::Core::Math::length<double, 2>);
//	def("length", BlueFramework::Core::Math::length<double, 3>);
//	def("length", BlueFramework::Core::Math::length<double, 4>);
//
//	def("dot", buw::dot<double, 2>);
//	def("dot", buw::dot<double, 3>);
//	def("dot", buw::dot<double, 4>);
//	*/
//
//	//def("cross", BlueFramework::Core::Math::cross<double, 2>);
//	//def("cross", BlueFramework::Core::Math::cross<double, 3>);
//	//def("cross", BlueFramework::Core::Math::cross<double, 4>);
//
//	class_<buw::AxisAlignedBoundingBox3d>("AxisAlignedBoundingBox3d")
//		.def(init<const buw::Vector3d&, const buw::Vector3d&>())
//		.def("getMinimum", getMinimum)
//		.def("getMaximum", getMaximum)
//		.def("getCenter", &buw::AxisAlignedBoundingBox3d::getCenter);
//
//	class_<buw::AlignmentModel,
//		buw::ReferenceCounted<buw::AlignmentModel>>
//		("AlignmentModel")
//		.def("addAlignment", &buw::AlignmentModel::addAlignment)
//		.def("deleteAlignment", &buw::AlignmentModel::deleteAlignment)
//		.def("getAlignmentCount", &buw::AlignmentModel::getAlignmentCount)
//		.def("getAlignment", &buw::AlignmentModel::getAlignment)
//		.def("getAlignments", &buw::AlignmentModel::getAlignments)
//		.def("getExtends", &buw::AlignmentModel::getExtends);
//
//	typedef std::vector<buw::ReferenceCounted<buw::IAlignment3D>> AlignmentList;
//
//	class_<AlignmentList>("AlignmentList")
//		.def("__len__", &AlignmentList::size)
//		.def("__getItem__", vectorGet<buw::ReferenceCounted<buw::IAlignment3D>>, return_value_policy<copy_non_const_reference>())
//		.def("__setItem__", vectorSet<buw::ReferenceCounted<buw::IAlignment3D>>)
//		.def("__iter__", iterator<AlignmentList>())
//		;
//
//
//	class_<buw::IAlignment3D,
//		buw::ReferenceCounted<buw::IAlignment3D>,
//		boost::noncopyable>
//		("IAlignment3D", no_init)
//		.def("getPosition", &buw::IAlignment3D::getPosition)
//		.def("getStartStation", &buw::IAlignment3D::getStartStation)
//		.def("getEndStation", &buw::IAlignment3D::getEndStation)
//		.def("getLength", &buw::IAlignment3D::getLength)
//		.def("getName", &buw::IAlignment3D::getName)
//		.def("setName", static_cast<void (buw::IAlignment3D::*)(const std::string&)>(&buw::IAlignment3D::setName))
//		.def("getType", &buw::IAlignment3D::getType);
//
//
//	enum_<buw::e3DAlignmentType>("e3DAlignmentType")
//		.value("e2DBased", buw::e3DAlignmentType::e2DBased)
//		.value("e3DBased", buw::e3DAlignmentType::e3DBased)
//		.value("Unknown", buw::e3DAlignmentType::Unknown)
//		;
//
//	class_<buw::Alignment3DBased3D,
//		buw::ReferenceCounted<buw::Alignment3DBased3D>,
//		bases<buw::IAlignment3D>>
//		("Alignment3DBased3D", init<double, OpenInfraPlatform::Infrastructure::Alignment3DBased3DType>())
//		.def("addPoint", &buw::Alignment3DBased3D::addPoint);
//
//	enum_<buw::Alignment3DBased3DType>("Alignment3DBased3DType")
//		.value("Spline", buw::Alignment3DBased3DType::Spline)
//		.value("Polyline", buw::Alignment3DBased3DType::Polyline)
//		;
//
//	class_<buw::Alignment2DBased3D,
//		buw::ReferenceCounted<buw::Alignment2DBased3D>,
//		bases<buw::IAlignment3D >>
//		("Alignment2DBased3D", init<buw::ReferenceCounted<buw::HorizontalAlignment2D>, buw::ReferenceCounted<buw::VerticalAlignment2D>>())
//		.def("hasHorizontalAlignment", &buw::Alignment2DBased3D::hasHorizontalAlignment)
//		.def("getHorizontalAlignmentElementCount", &buw::Alignment2DBased3D::getHorizontalAlignmentElementCount)
//		.def("getHorizontalAlignmentLength", &buw::Alignment2DBased3D::getHorizontalAlignmentLength)
//		.def("getHorizontalAlignmentElementCount", &buw::Alignment2DBased3D::getHorizontalAlignmentElementCount)
//		.def("getHorizontalPosition", &buw::Alignment2DBased3D::getHorizontalPosition)
//		.def("getHorizontalAlignment", &buw::Alignment2DBased3D::getHorizontalAlignment)
//		.def("setHorizontalAlignment", &buw::Alignment2DBased3D::setHorizontalAlignment)
//		.def("hasVerticalAlignment", &buw::Alignment2DBased3D::hasVerticalAlignment)
//		.def("getVerticalPosition", &buw::Alignment2DBased3D::getVerticalPosition)
//		.def("getVerticalAlignment", &buw::Alignment2DBased3D::getVerticalAlignment)
//		.def("setVerticalAlignment", &buw::Alignment2DBased3D::setVerticalAlignment)
//		;
//
//	implicitly_convertible<buw::ReferenceCounted<buw::Alignment2DBased3D>, buw::ReferenceCounted<buw::IAlignment3D>>();
//	implicitly_convertible<buw::ReferenceCounted<buw::Alignment3DBased3D>, buw::ReferenceCounted<buw::IAlignment3D>>();
//
//	// Horizontal Alignment
//	class_<buw::HorizontalAlignment2D,
//		buw::ReferenceCounted<buw::HorizontalAlignment2D>>
//		("HorizontalAlignment2D", init<double>())
//		.def("getStartStation", &buw::HorizontalAlignment2D::getStartStation)
//		.def("getEndStation", &buw::HorizontalAlignment2D::getEndStation)
//		.def("getPosition", &buw::HorizontalAlignment2D::getPosition)
//		.def("addElement", &buw::HorizontalAlignment2D::addElement)
//		.def("getAlignmentElementByStationing", getAlignmentElementByStationing)
//		.def("getAlignmentElementCount", &buw::HorizontalAlignment2D::getAlignmentElementCount)
//		.def("getAlignmentElementByIndex", &buw::HorizontalAlignment2D::getAlignmentElementByIndex);
//
//
//	class_<buw::HorizontalAlignmentElement2D,
//		buw::ReferenceCounted<buw::HorizontalAlignmentElement2D>,
//		boost::noncopyable>
//		("HorizontalAlignmentElement2D", no_init)
//		.def("getPosition", &buw::HorizontalAlignmentElement2D::getPosition)
//		.def("getStartPosition", &buw::HorizontalAlignmentElement2D::getStartPosition)
//		.def("getEndPosition", &buw::HorizontalAlignmentElement2D::getEndPosition)
//		.def("getLength", &buw::HorizontalAlignmentElement2D::getLength)
//		.def("getAlignmentType", &buw::HorizontalAlignmentElement2D::getAlignmentType)
//		;
//
//	enum_<buw::eHorizontalAlignmentType>("eHorizontalAlignmentType")
//		.value("Line", buw::eHorizontalAlignmentType::Line)
//		.value("Arc", buw::eHorizontalAlignmentType::Arc)
//		.value("Clothoid", buw::eHorizontalAlignmentType::Clothoid)
//		.value("Unknown", buw::eHorizontalAlignmentType::Unknown)
//		;
//
//	class_<buw::HorizontalAlignmentElement2DLine,
//		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine>,
//		bases<buw::HorizontalAlignmentElement2D>>
//		("HorizontalAlignmentElement2DLine", init<buw::Vector2d, buw::Vector2d>());
//
//	class_<buw::HorizontalAlignmentElement2DArc,
//		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc>,
//		bases<buw::HorizontalAlignmentElement2D>>
//		("HorizontalAlignmentElement2DArc", init<buw::Vector2d, buw::Vector2d, buw::Vector2d, bool>());
//
//	class_<buw::clothoidDescription>
//		("clothoidDescription", init<buw::Vector2d, double, double, bool, double, bool, double>());
//
//	class_<buw::HorizontalAlignmentElement2DClothoid,
//		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>,
//		bases<buw::HorizontalAlignmentElement2D>>
//		("HorizontalAlignmentElement2DClothoid", init<buw::clothoidDescription>());
//
//	implicitly_convertible<buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine>, buw::ReferenceCounted<buw::HorizontalAlignmentElement2D>>();
//	implicitly_convertible<buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc>, buw::ReferenceCounted<buw::HorizontalAlignmentElement2D>> ();
//	implicitly_convertible<buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>, buw::ReferenceCounted<buw::HorizontalAlignmentElement2D>>();
//
//
//	// Vertical Alignment
//	class_<buw::VerticalAlignment2D,
//		buw::ReferenceCounted<buw::VerticalAlignment2D>,
//		boost::noncopyable>
//		("VerticalAlignment2D")
//		.def("getStartStation", &buw::VerticalAlignment2D::getStartStation)
//		.def("getEndStation", &buw::VerticalAlignment2D::getEndStation)
//		.def("getPosition", &buw::VerticalAlignment2D::getPosition)
//		.def("addElement", &buw::VerticalAlignment2D::addElement);
//
//
//	class_<buw::VerticalAlignmentElement2D,
//		buw::ReferenceCounted<buw::VerticalAlignmentElement2D>,
//		boost::noncopyable>
//		("VerticalAlignmentElement2D", no_init)
//		.def("getPosition", &buw::VerticalAlignmentElement2D::getPosition)
//		.def("getStartPosition", &buw::VerticalAlignmentElement2D::getStartPosition)
//		.def("getEndPosition", &buw::VerticalAlignmentElement2D::getEndPosition)
//		;
//
//	class_<buw::VerticalAlignmentElement2DLine,
//		buw::ReferenceCounted<buw::VerticalAlignmentElement2DLine>,
//		bases<buw::VerticalAlignmentElement2D >>
//		("VerticalAlignmentElement2DLine", init<buw::Vector2d, buw::Vector2d>());
//
//	class_<buw::VerticalAlignmentElement2DArc,
//		buw::ReferenceCounted<buw::VerticalAlignmentElement2DArc>,
//		bases <buw::VerticalAlignmentElement2D >>
//		("VerticalAlignmentElement2DArc", init<buw::Vector2d, buw::Vector2d, double, double, bool>());
//
//	class_<buw::VerticalAlignmentElement2DParabola,
//		buw::ReferenceCounted<buw::VerticalAlignmentElement2DParabola>,
//		bases<buw::VerticalAlignmentElement2D >>
//		("VerticalAlignmentElement2DParabola", init<buw::Vector2d, buw::Vector2d, double, double>());
//
//	implicitly_convertible<buw::ReferenceCounted<buw::VerticalAlignmentElement2DLine>, buw::ReferenceCounted<buw::VerticalAlignmentElement2D>>();
//	implicitly_convertible<buw::ReferenceCounted<buw::VerticalAlignmentElement2DArc>, buw::ReferenceCounted<buw::VerticalAlignmentElement2D>>();
//	implicitly_convertible<buw::ReferenceCounted<buw::VerticalAlignmentElement2DParabola>, buw::ReferenceCounted<buw::VerticalAlignmentElement2D>>();
//
//	// Importer
//	class_<buw::Import, boost::noncopyable>("Import", init<const std::string&>())
//		.def("getAlignmentModel", &buw::LandXmlImport::getAlignmentModel);
//
//	class_<buw::LandXmlImport, boost::noncopyable, bases<buw::Import>>("LandXmlImport", init<const std::string&>());
//
//	class_<buw::IfcAlignmentImport, boost::noncopyable, bases<buw::Import>>("IfcAlignmentImport", init<const std::string&>());
//
//	class_<buw::IfcRoadImport, boost::noncopyable, bases<buw::Import>>("IfcRoadImport", init<const std::string&>());
//
//	class_<buw::OkstraImport, boost::noncopyable, bases<buw::Import>>("OkstraImport", init<const std::string&>());
//
//	class_<buw::RoadXMLImport, boost::noncopyable, bases<buw::Import>>("RoadXMLImport", init<const std::string&>());
//
//	class_<buw::OSMImport, boost::noncopyable, bases<buw::Import>>("OSMImport", no_init)
//		.def("__init__", make_constructor(OSMImportConstr));
//
//	def("getOSMDefaultFilter", getOSMDefaultFilter);
//
//	def("simplifiedImport", simplifiedImport);
//
//
//	register_ptr_to_python<buw::ReferenceCounted<buw::AlignmentModel>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::IAlignment3D>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::Alignment3DBased3D>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::Alignment2DBased3D>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::HorizontalAlignment2D>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::HorizontalAlignmentElement2D>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::VerticalAlignment2D>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::VerticalAlignmentElement2D>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::VerticalAlignmentElement2DLine>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::VerticalAlignmentElement2DArc>>();
//	register_ptr_to_python<buw::ReferenceCounted<buw::VerticalAlignmentElement2DParabola>>();
//
//
//}