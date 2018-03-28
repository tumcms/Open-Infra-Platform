/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016 Technical University of Munich
    Chair of Computational Modeling and Simulation.
    
    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.
    
    BlueFramework is distributed in the hope that it will be useful,
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

#include <BlueFramework/Engine/ResourceManagment/download.h>

#include <QString>
#include <QRegExp>
#include <type_traits>

std::string sanitize(const char* name){
	auto reg0 = QRegExp("class ", Qt::CaseSensitive, QRegExp::Wildcard);
	auto reg1 = QRegExp("OpenInfraPlatform::IfcAlignment1x1::", Qt::CaseSensitive, QRegExp::Wildcard);
	return (QString(name).remove(reg0).remove(reg1)).toStdString();
};

template<template<typename...> class TT, typename T>
struct is_instantiation_of : std::false_type {};

template<template<typename...> class TT, typename... Ts>
struct is_instantiation_of<TT, TT<Ts...>> : std::true_type {};

struct func {	
	template <typename T>
	void operator()(const char* name, std::shared_ptr<T> ptr)
	{
		if(ptr) {
			std::cout << name << ": pointer" << std::endl;
			if(visit_struct::traits::is_visitable<T>::value) {
				visit_struct::for_each(*ptr, func {});
			}
		}
		else {
			std::cout << name << ": pointer(empty)" << std::endl;
		}

	}

	template <typename T>
	void operator()(const char* name, std::vector<std::shared_ptr<T>> vector)
	{
		std::cout << name << ": vector" << std::endl;
		if(visit_struct::traits::is_visitable<T>::value) {
			for(auto it : vector) {
				visit_struct::for_each(*it, func {});
			}
		}
	}

	template <typename T>
	void operator()(const char* name, T t)
	{
		std::cout << name << ": T" << std::endl;
	}

	void operator()(const char* name, std::string string)
	{
		std::cout << "\t" << name << ": " << string << std::endl;
	}
};

struct process {
	template <typename K, class V, class T>
	void operator()(std::pair<const K, std::shared_ptr<V>> pair)
	{
		if(visit_struct::traits::is_visitable<V>::value) {
			auto& entity = *pair.second;
			std::cout << sanitize(typeid(entity).name()) << std::endl;
			visit_struct::for_each(entity, func {});
		}
	}
};

class OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl {
public:
	ExportIfcOWL4x1Impl(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) {
		
		//OpenInfraPlatform::ExpressBinding::Schema schema = OpenInfraPlatform::ExpressBinding::Schema::read("IFC4x1_RC3.exp");
		
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
		
		
		std::for_each(model->getMapIfcObjects().begin(), model->getMapIfcObjects().end(), process {});

		for(auto& entry : model->getMapIfcObjects()) {
			auto& entity = *(entry.second);
			std::string type = sanitize(typeid(entity).name());
			std::cout << entity.getId() << "=" << entity.m_entity_enum << ": " << type << std::endl;

			const std::type_info& t = (typeid(entity));

			visit_struct::for_each(entity, func {});

			//if(entity.m_entity_enum == OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1EntityEnum::IFCPERSON) {
			//	auto person = *(std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcPerson>(entry.second));
			//	visit_struct::for_each(person, func {});
			//}
		}


		
		/*
		std::vector<std::string> collectedAxisUniqueBlankTermNames;

		for (int i = 0; i < am->getAlignmentCount(); i++) {
			buw::ReferenceCounted<buw::IAlignment3D> alignment = am->getAlignment(i);
			buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);
			buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = alignment2D->getHorizontalAlignment();
			buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment = alignment2D->getVerticalAlignment();

			buw::String axisName = am->getAlignments()[i]->getName();

			std::stringstream ifcAlignmentUniqueBlankTermName;
			ifcAlignmentUniqueBlankTermName << "axis_" << i;

			collectedAxisUniqueBlankTermNames.push_back(ifcAlignmentUniqueBlankTermName.str());

			{
				raptor_statement* triple = nullptr;
				triple = raptor_new_statement(world_);

				triple->subject = raptor_new_term_from_blank(world_, (const unsigned char*)ifcAlignmentUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world_, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
				triple->object = raptor_new_term_from_uri_string(world_, (unsigned char*)"http://www.buildingsmart-tech.org/ifcowl/IFC4x1#IfcAlignment");

				raptor_serializer_serialize_statement(serializer_, triple);
				raptor_free_statement(triple);
			}

			{
				raptor_statement* triple = nullptr;
				triple = raptor_new_statement(world_);

				triple->subject = raptor_new_term_from_blank(world_, (const unsigned char*)ifcAlignmentUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world_, (const unsigned char*)"http://www.buildingsmart-tech.org/ifcowl/IFC4x1#name_IfcRoot");
				triple->object = raptor_new_term_from_literal(world_, (unsigned char*)axisName.toCString(), nullptr, nullptr);

				raptor_serializer_serialize_statement(serializer_, triple);
				raptor_free_statement(triple);
			}



		}*/
	}

	virtual ~ExportIfcOWL4x1Impl() {
		raptor_serializer_serialize_end(serializer_);
		raptor_free_serializer(serializer_);

		raptor_free_world(world_);

		fclose(outfile);
	}

private:
	FILE * outfile = nullptr;
	raptor_world* world_ = nullptr;
	raptor_serializer* serializer_ = nullptr;
};

OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) : 
	Export(am, dem, filename), impl_(new ExportIfcOWL4x1Impl(am, dem, filename))
{

}

OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::~ExportIfcOWL4x1()
{

}
