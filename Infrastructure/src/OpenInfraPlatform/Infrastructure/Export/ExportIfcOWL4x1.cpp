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
#include "OpenInfraPlatform/ExpressBinding/Meta/Schema.h"
#include "raptor2/raptor2.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include <OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntitiesMap.h>
#include <OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityTypes.h>

#include <BlueFramework/Engine/ResourceManagment/download.h>

#include <QString>
#include <QStringList>
#include <QRegExp>
#include <type_traits>

//#include <boost/preprocessor/iteration/local.hpp>
//#include <boost/preprocessor/iteration/iterate.hpp>

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>


std::string sanitize(const char* name){
	auto reg0 = QRegExp("class ", Qt::CaseSensitive, QRegExp::Wildcard);
	auto reg1 = QRegExp("OpenInfraPlatform::IfcAlignment1x1::", Qt::CaseSensitive, QRegExp::Wildcard);
	auto reg2 = QRegExp("enum ", Qt::CaseSensitive, QRegExp::Wildcard);
	return (QString(name).remove(reg0).remove(reg1).remove(reg2)).toStdString();
};


#include <../Tools/test1.h>

static unsigned level = 0;
static std::vector<raptor_term*> subjectStack = std::vector<raptor_term*>();
static std::vector<raptor_term*> predicateStack = std::vector<raptor_term*>();
static std::vector<raptor_term*> objectStack = std::vector<raptor_term*>();
static std::vector<std::string> typenameStack = std::vector<std::string>();
static std::map<int, raptor_term*> subjectMap = std::map<int, raptor_term*>();

static void printIndented(int count, ...)
{
	for(int i = 0; i < level; i++) {
		std::cout << "\t";
	}
	va_list args;
	va_start(args, count);
	for(int i = 0; i < count; ++i) {
		std::cout << va_arg(args, char*);
	}
	va_end(args);
	std::cout << std::endl;
}



class OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl {
private:
	FILE * outfile;
	static raptor_world* world_;
	static raptor_serializer* serializer_;

private:

	struct parseType {

		void createStatementFromLiteral(std::string literal)
		{
			raptor_statement* triple = nullptr;
			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subjectStack.back());
			triple->predicate = raptor_term_copy(predicateStack.back());
			triple->object = raptor_new_term_from_literal(world_, (unsigned char*)literal.c_str(), nullptr, nullptr);

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);
		}

		void operator()(const char* name, std::string string)
		{
			//std::cout << name << ": string" << std::endl;
			printIndented(3, name, ": ", string.data());
			createStatementFromLiteral(string);
		}

		void operator()(const char* name, double value)
		{
			//std::cout << name << ": string" << std::endl;
			std::string string = QString::number(value).toStdString();
			printIndented(3, name, ": ", string.data());

			createStatementFromLiteral(string);
		}

		void operator()(const char* name, float value)
		{
			std::string string = QString::number(value).toStdString();
			//std::cout << name << ": string" << std::endl;
			printIndented(3, name, ": ", string.data());

			createStatementFromLiteral(string);
		}

		void operator()(const char* name, int value)
		{
			std::string string = QString::number(value).toStdString();
			//std::cout << name << ": string" << std::endl;
			printIndented(3, name, ": ", string.data());

			createStatementFromLiteral(string);
		}

		template <typename T>
		void operator()(const char* name, T t)
		{
			//DUMMY
		}
	};

	struct parseAttribute {
		template < class T, class = typename std::enable_if<visit_struct::traits::is_visitable<T>::value>::type>
		void operator()(const char* name, std::shared_ptr<T> ptr)
		{
			if(ptr) {
				if(std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value) {
					
					QString predicate = QString(name).split('_')[1];
					predicate[0] = predicate[0].toLower();
					predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
					predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));

					level++;
					visit_struct::for_each(*ptr, parseType {});
					level--;

					predicateStack.pop_back();
				}					
				else {
					parse(name, ptr);
				}
			}
			else {
				//std::cout << name << ": pointer(empty)" << std::endl;
				printIndented(2, name, ": pointer(empty)");
			}

		}

		template < class T, class = typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value>::type>
		void parse(const char* name, std::shared_ptr<T> ptr)
		{
			auto id = std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(ptr)->getId();
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

		template < class T, class = typename std::enable_if<!std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value>::type>
		void parse(const char* name, T ptr)
		{
			//DUMMY
		}


		template < class T, class = typename std::enable_if<visit_struct::traits::is_visitable<T>::value>::type>
		void operator()(const char* name, std::vector<std::shared_ptr<T>> vector)
		{
			if(!vector.empty()) {
				//std::cout << name << ": vector(" << vector.size() << ")" << std::endl;
				printIndented(4, name, ": vector(", QString::number(vector.size()).data(), ")");

				//if(std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value) {
				//	QString predicate = QString(name).split('_')[1];
				//	predicate[0] = predicate[0].toLower();
				//	predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
				//	predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));
				//
				//	//TODO
				//	parseType parser;
				//	for(auto it : vector) {
				//		level++;
				//		parser(name, *it);
				//		level--;
				//	}
				//
				//	predicateStack.pop_back();
				//}
				//else {
					for(auto it : vector) {
						level++;
						parseAttribute()(name, it);
						level--;
					}
				//}
			}
		}

		
		template <typename T>
		void operator()(const char* name, T t)
		{
			//std::cout << name << ": "<< typeid(t).name() << std::endl;
			printIndented(3, name, ": ", sanitize(typeid(t).name()).data());
		}
	};

	struct DerivedIfcEntityParser {

		template < class T, class = typename std::enable_if<visit_struct::traits::is_visitable<T>::value>::type>
		void operator()(T& entity) const
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
			
			level++;
			visit_struct::for_each(entity, parseAttribute {});
			level--;

			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subject);
			triple->predicate = predicate;
			triple->object = object;

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);


			subjectStack.pop_back();
			typenameStack.pop_back();
		}


		void operator()(OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity& entity) const
		{
		}
	};


	struct MapIfcObjectsParser {

		void operator()(std::pair<const int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> pair)
		{
			castAndCall(pair.second, DerivedIfcEntityParser {});
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