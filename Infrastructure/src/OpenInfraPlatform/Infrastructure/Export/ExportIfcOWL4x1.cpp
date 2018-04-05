/*
Copyright (c) 2018 Technical University of Munich
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

#include "OpenInfraPlatform/Infrastructure/Export/ExportIfcOWL4x1.h"
#include "OpenInfraPlatform/Infrastructure/Export/ExportIfcAlignment1x1.h"

#include "raptor2/raptor2.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include <QString>
#include <QStringList>
#include <QRegExp>
#include <type_traits>

#include "IfcAlignment1x1Caster.h"
#include "IfcAlignment1x1EnumStrings.h"

std::string sanitize(const char* name){
	auto reg0 = QRegExp("class ", Qt::CaseSensitive, QRegExp::Wildcard);
	auto reg1 = QRegExp("OpenInfraPlatform::IfcAlignment1x1::", Qt::CaseSensitive, QRegExp::Wildcard);
	auto reg2 = QRegExp("enum ", Qt::CaseSensitive, QRegExp::Wildcard);
	return (QString(name).remove(reg0).remove(reg1).remove(reg2)).toStdString();
};

static std::vector<raptor_term*> subjectStack = std::vector<raptor_term*>();
static std::vector<raptor_term*> predicateStack = std::vector<raptor_term*>();
static std::vector<raptor_term*> objectStack = std::vector<raptor_term*>();
static std::vector<std::string> typenameStack = std::vector<std::string>();
static std::map<int, raptor_term*> subjectMap = std::map<int, raptor_term*>();

class OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl {
private:
	FILE * outfile;
	static raptor_world* world_;
	static raptor_serializer* serializer_;

private:
	static void createStatementFromLiteral(std::string literal)
	{
		raptor_statement* triple = nullptr;
		triple = raptor_new_statement(world_);

		triple->subject = raptor_term_copy(subjectStack.back());
		triple->predicate = raptor_term_copy(predicateStack.back());
		triple->object = raptor_new_term_from_literal(world_, (unsigned char*)literal.c_str(), nullptr, nullptr);

		raptor_serializer_serialize_statement(serializer_, triple);
		raptor_free_statement(triple);
	}

	static void createPropertyStatementFromMap(const char* name, int id)
	{
		if(subjectMap.count(id)) {

			QString predicate = QString(name).split('_')[1];
			predicate[0] = predicate[0].toLower();
			predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");


			raptor_statement* triple = nullptr;
			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subjectStack.back());
			triple->predicate = raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str()));
			triple->object = raptor_term_copy(subjectMap.find(id)->second);

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);
		}
	}

	struct parseVector {
		template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
		operator()(const char* name, std::vector<std::shared_ptr<T>> vector)
		{
			if(!vector.empty()) {
				QStringList text = QStringList();
				for(auto it : vector) {
					text.append(QString::number(visit_struct::get<0>(*it)));
				}

				createStatementFromLiteral(text.join(", ").toStdString());
			}
		}
				

		void operator()(const char* name, std::vector<std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPositiveInteger>> vector)
		{
			if(!vector.empty()) {
				QStringList text = QStringList();
				for(auto it : vector) {
					text.append(QString::number(visit_struct::get<0>((OpenInfraPlatform::IfcAlignment1x1::IfcInteger)*it)));
				}

				createStatementFromLiteral(text.join(", ").toStdString());
			}
		}

		template <class T> 
		void operator()(const char* name, T t)
		{
			BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
		}
	};

	struct parseType {		

		void operator()(const char* name, std::string string)
		{			
			createStatementFromLiteral(string);
		}

		template <class T> typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, int>::value, void>::type
		operator()(const char* name, T value)
		{
			std::string string = QString::number((T) value).toStdString();
			createStatementFromLiteral(string);
		}
				
		void operator()(const char* name, bool value)
		{
			value ? createStatementFromLiteral("true") : createStatementFromLiteral("false");
		}

		template <typename T>
		void operator()(const char* name, std::shared_ptr<T> &ptr)
		{
			std::string message = "Invalid function call. " + sanitize(typeid(ptr).name()) + " can't be a member of IfcAlignment1x1Type.";
			throw buw::Exception(message.data());
		}

		template <typename T>
		void operator()(const char* name, std::vector<T> vector)
		{
			std::string message = "Invalid function call. " + sanitize(typeid(vector).name()) + " can't be a member of IfcAlignment1x1Type.";
			throw buw::Exception(message.data());
		}

		template <class T> typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, int>::value, void>::type
		operator()(const char* name, T t)
		{
			if(std::is_enum<T>::value) {
				QString enumName = QString(sanitize(typeid(T).name()).data());
				enumName = enumName.split("::")[1];
				createStatementFromLiteral(getStringFromEnum(enumName.toStdString(), (int) t));
			}
			else {
				BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
			}
		}

	};

	struct parseAttribute {

		template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
		operator()(const char* name, std::shared_ptr<T> &ptr)
		{
			if(ptr) {					
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));

				visit_struct::for_each(*ptr, parseType {});

				predicateStack.pop_back();				
			}
			else {
				BLUE_LOG(trace) << "Class " << typenameStack.back() << ", attribute " << name << ". Empty pointer.";
			}
		}		
		
		template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(const char* name, std::shared_ptr<T> &ptr){
			if(ptr) {
				auto id = std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(ptr)->getId();
				createPropertyStatementFromMap(name, id);				
			}
		}

		template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractSelect, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
		operator()(const char* name, std::shared_ptr<T> &base_ptr)
		{
			if(base_ptr.get()) {
				QString classname = QString(typeid(*base_ptr).name());
				if(classname.endsWith("IfcSIUnit"))
					createPropertyStatementFromMap(name, std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcSIUnit>(base_ptr)->getId());
				else if(classname.endsWith("IfcAxis2Placement3D"))
					createPropertyStatementFromMap(name, std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAxis2Placement3D>(base_ptr)->getId());
				else if(classname.endsWith("IfcGeometricRepresentationContext"))
					createPropertyStatementFromMap(name, std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationContext>(base_ptr)->getId());
				else {
					BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
				}
			}
			else {
				BLUE_LOG(trace) << "Class " << typenameStack.back() << ", attribute " << name << ". Empty pointer.";
			}
		}
		
		void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPositiveInteger> ptr)
		{
			QString predicate = QString(name).split('_')[1];
			predicate[0] = predicate[0].toLower();
			predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
			predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));

			parseType {}(name, ((OpenInfraPlatform::IfcAlignment1x1::IfcInteger)*ptr).m_value);

			predicateStack.pop_back();
		}

		void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPositiveLengthMeasure> ptr)
		{
			QString predicate = QString(name).split('_')[1];
			predicate[0] = predicate[0].toLower();
			predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
			predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));

			parseType {}(name, ((OpenInfraPlatform::IfcAlignment1x1::IfcLengthMeasure)*ptr).m_value);

			predicateStack.pop_back();
		}

		
		template < class T>
		void operator()(const char* name, std::vector<std::vector<std::shared_ptr<T>>> vector)
		{
			if(!vector.empty()) {
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));

				for(auto it : vector) {
					parseVector {}(name, it);
				}

				predicateStack.pop_back();
			}
		}

		void operator()(const char* name, std::vector<std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcLengthMeasure>> vector)
		{
			if(!vector.empty()) {
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));

				parseVector {}(name, vector);		

				predicateStack.pop_back();
			}
		}
		
		template < class T>
		void operator()(const char* name, std::vector<std::shared_ptr<T>> vector)
		{
			if(!vector.empty()) {				
				for(auto it : vector) {
					this->operator()(name, it);
				}
			}
		}
				
		template <typename T>
		void operator()(const char* name, T t)
		{
			if(std::is_integral<T>::value || std::is_floating_point<T>::value) {
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));

				parseType {}(name, t);

				predicateStack.pop_back();
			}			
			else {
				BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
			}
		}
	};


	struct DerivedIfcEntityParser {

		template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T& entity) const
		{
			auto type = sanitize(typeid(T).name());
			auto id = QString::number(((OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity) entity).getId()).toStdString();
			std::string subjectString = QString(sanitize(typeid(T).name()).data()).toLower().toStdString() + "_" + id;

			auto subject = raptor_new_term_from_blank(world_, (const unsigned char*)(subjectString.c_str()));
			auto predicate = raptor_new_term_from_uri_string(world_, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
			auto object = raptor_new_term_from_uri_string(world_, (unsigned char*)((std::string("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#").append(type)).c_str()));

			raptor_statement* triple = nullptr;
			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subject);
			triple->predicate = raptor_term_copy(predicate);
			triple->object = raptor_term_copy(object);

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);

			subjectStack.push_back(subject);
			typenameStack.push_back(type);
			
			visit_struct::for_each(entity, parseAttribute {});

			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subject);
			triple->predicate = predicate;
			triple->object = object;

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);


			subjectStack.pop_back();
			typenameStack.pop_back();
		}

		template <class T> typename std::enable_if<!std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T& entity) const
		{
			std::string message = "Invalid function call. " + sanitize(typeid(entity).name()) + " isn't a member of IfcAlignment1x1Entity.";
			throw buw::Exception(message.data());
		}

		void operator()(OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity& entity) const
		{
			std::string message = "Invalid function call.";
			throw buw::Exception(message.data());
		}
	};


	struct MapIfcObjectsParser {
		void operator()(std::pair<const int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> pair)
		{
			OpenInfraPlatform::IfcAlignment1x1::castAndCall(pair.second, DerivedIfcEntityParser {});
		}
	};

	struct CreateSubjectMap {
		void operator()(std::pair<const int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> pair)
		{
			auto type = sanitize(typeid(*pair.second).name());
			auto id = QString::number(pair.first).toStdString();
			std::string subjectString = QString(type.data()).toLower().toStdString() + "_" + id;

			auto subject = raptor_new_term_from_blank(world_, (const unsigned char*)(subjectString.c_str()));
			subjectMap.insert(std::pair<int, raptor_term*>(pair.first, subject));
		}
	};

public:
	ExportIfcOWL4x1Impl(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) {
		
		auto uuid = boost::uuids::uuid();
		std::string temp = "./";
		temp.append(boost::uuids::to_string(uuid));
		temp.append(".ifc");

		auto ifcExporter = buw::makeReferenceCounted<buw::ExportIfcAlignment1x1>(ifcAlignmentExportDescription(),am, dem, temp);
		boost::filesystem::remove(temp);
		
		auto model = ifcExporter->getIfcAlignment1x1Model();

		//Write header to file
		outfile = fopen(filename.c_str(), "w");

		world_ = raptor_new_world();

		if(boost::ends_with(filename, "rdf"))
			serializer_ = raptor_new_serializer(world_, "rdfxml-abbrev");
		else
			serializer_ = raptor_new_serializer(world_, "turtle");

		raptor_serializer_start_to_file_handle(serializer_, nullptr, outfile);

		const unsigned char* okstra_prefix = (const unsigned char*)"ifc";
		raptor_uri* okstra_uri = raptor_new_uri(world_, (const unsigned char*)"http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
		raptor_serializer_set_namespace(serializer_, okstra_uri, okstra_prefix);

		const unsigned char* rdf_prefix = (const unsigned char*)"rdf";
		raptor_uri* rdf_uri = raptor_new_uri(world_, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#");
		raptor_serializer_set_namespace(serializer_, rdf_uri, rdf_prefix);
		
		std::for_each(model->getMapIfcObjects().begin(), model->getMapIfcObjects().end(), CreateSubjectMap {});
		std::for_each(model->getMapIfcObjects().begin(), model->getMapIfcObjects().end(), MapIfcObjectsParser {});		
	}

	virtual ~ExportIfcOWL4x1Impl() {
		raptor_serializer_serialize_end(serializer_);
		raptor_free_serializer(serializer_);

		raptor_free_world(world_);

		for(auto it : subjectStack)
			raptor_free_term(it);

		for(auto it : predicateStack)
			raptor_free_term(it);

		for(auto it : objectStack)
			raptor_free_term(it);

		for(auto it : subjectMap)
			raptor_free_term(it.second);

		subjectStack.clear();
		predicateStack.clear();
		objectStack.clear();
		subjectMap.clear();

		fclose(outfile);
	}
};

OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) : 
	Export(am, dem, filename), impl_(new ExportIfcOWL4x1Impl(am, dem, filename))
{

}

OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::~ExportIfcOWL4x1()
{

}

raptor_world* OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl::world_ = raptor_new_world();
raptor_serializer* OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl::serializer_ = raptor_new_serializer(world_, "turtle");