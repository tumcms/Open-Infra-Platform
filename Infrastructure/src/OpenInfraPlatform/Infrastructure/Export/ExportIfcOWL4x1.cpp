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
#include "OpenInfraPlatform/Infrastructure/Export/ExportIfc4x1.h"

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

//Helper function to remove unwanted stuff from the string returned by typeid(T).name() function.
std::string sanitize(const char* name){
	auto reg0 = QRegExp("class ", Qt::CaseSensitive, QRegExp::Wildcard);
	auto reg1 = QRegExp("OpenInfraPlatform::IfcAlignment1x1::", Qt::CaseSensitive, QRegExp::Wildcard);
	auto reg2 = QRegExp("enum ", Qt::CaseSensitive, QRegExp::Wildcard);
	return (QString(name).remove(reg0).remove(reg1).remove(reg2)).toStdString();
};

//Static stack variables which hold raptor terms so they don't have to be passed over all function calls.
static std::vector<raptor_term*> subjectStack = std::vector<raptor_term*>();
static std::vector<raptor_term*> predicateStack = std::vector<raptor_term*>();
static std::vector<raptor_term*> objectStack = std::vector<raptor_term*>();
static std::vector<std::string> typenameStack = std::vector<std::string>();

//Map holding subjects with their id as key.
static std::map<int, raptor_term*> subjectMap = std::map<int, raptor_term*>();

class OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl {
private:
	FILE * outfile;
	static raptor_world* world_;
	static raptor_serializer* serializer_;

private:
	//Function which takes a string and creates a statement with the subject and predicate on their stacks and the given literal.
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

	//This function creates a statement with the subject on the subjectStack and the predicate by the name and the typename on the typenameStack.
	//The object is identified by the id and received from the subjectMap.
	static void createPropertyStatementFromMap(const char* name, int id)
	{
		//If the object is contained in the map, create the statement as described.
		if(subjectMap.count(id)) {

			//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
			QString predicate = QString(name).split('_')[1];
			predicate[0] = predicate[0].toLower();
			predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

			//Create the raptor statement as described above and serialize it.
			raptor_statement* triple = nullptr;
			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subjectStack.back());
			triple->predicate = raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str()));
			triple->object = raptor_term_copy(subjectMap.find(id)->second);

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);
		}
		//If the subject is not contained in the map, write it to the log file as warning since this means we have either a false id or not yet parsed the object.
		else {
			//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
			QString predicate = QString(name).split('_')[1];
			predicate[0] = predicate[0].toLower();
			predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

			//Write warning to log file with id and property string.
			BLUE_LOG(warning) << "Subject with id " << QString::number(id).toStdString() << " and in property " << predicate.toStdString() << " not found in the map.";
		}
	}

	//Helper struct to parse attributes holding vectors of pointers which should not be sorted but in one statement.
	struct parseVector {

		//Function operator() that covers vectors of visitable IfcAlignment1x1Type instances.
		template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
		operator()(const char* name, std::vector<std::shared_ptr<T>> vector)
		{
			//If not empty, we construct a string list holding each value of the vector elements.
			if(!vector.empty()) {
				QStringList text = QStringList();
				for(auto it : vector) {
					text.append(QString::number(visit_struct::get<0>(*it)));
				}

				//We create our text by concatenating all entries, seperating them with ", " so that the list is written as one statement to avoid sorting.
				createStatementFromLiteral(text.join(", ").toStdString());
			}
		}
				
		//Function operator() that covers std::vector<std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPositiveInteger>>.
		//This is a special case since IfcPositiveInteger is not visitable, but is often used and the class holsing the value is IfcInteger.
		void operator()(const char* name, std::vector<std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPositiveInteger>> vector)
		{
			//If not empty, we construct a string list holding each value of the vector elements by casting those to IfcInteger.
			if(!vector.empty()) {
				QStringList text = QStringList();
				for(auto it : vector) {
					text.append(QString::number(visit_struct::get<0>((OpenInfraPlatform::IfcAlignment1x1::IfcInteger)*it)));
				}

				//We create our text by concatenating all entries, seperating them with ", " so that the list is written as one statement to avoid sorting.
				createStatementFromLiteral(text.join(", ").toStdString());
			}
		}

		//Function operator() which covers T.
		//This is a function required by the compiler and shouldn't be called since it means the type is not handled.
		//A warning is written to the log file.
		template <class T> 
		void operator()(const char* name, T t)
		{
			BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
		}
	};

	//Helper struct which parses the attributes of a derived entity which are IfcAlignment1x1Types and hold flat values.
	struct parseType {
		
		//Function operator() which creates a statement from a string value.
		void operator()(const char* name, std::string string)
		{			
			createStatementFromLiteral(string);
		}

		//Function operator() which creates a statement from a numeric value.
		template <class T> typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, int>::value, void>::type
		operator()(const char* name, T value)
		{
			std::string string = QString::number((T) value).toStdString();
			createStatementFromLiteral(string);
		}
				
		//Function operator() which creates a statement from a boolean value.
		void operator()(const char* name, bool value)
		{
			value ? createStatementFromLiteral("true") : createStatementFromLiteral("false");
		}

		//Function operator() which covers std::shared_ptr<T>.
		//This is a dummy function required by the compiler but which mustn't be called. Throws an exception.
		template <typename T>
		void operator()(const char* name, std::shared_ptr<T> &ptr)
		{
			std::string message = "Invalid function call. " + sanitize(typeid(ptr).name()) + " can't be a member of IfcAlignment1x1Type.";
			throw buw::Exception(message.data());
		}

		//Function operator() which covers std::vector<T>.
		//This is a function required by the compiler but is not implemented and mustn't be called. Throws an exception.
		template <typename T>
		void operator()(const char* name, std::vector<T> vector)
		{
			std::string message = "Invalid function call. " + sanitize(typeid(vector).name()) + "is a vector and vectors are not yet handled.";
			throw buw::Exception(message.data());
		}

		//Function operator() which covers everything that is not an int, float/double, string, boolean, pointer or vector.
		//This function also takes enums, since alot of classes derived from IfcAlignment1x1Type have a corresponding enum class, which is derived from it.
		template <class T> typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, int>::value, void>::type
		operator()(const char* name, T t)
		{
			//If T is an enum, we call a function which converts it to a string and write it as string value.
			if(std::is_enum<T>::value) {
				//We get the name of the enum from the typeid name.
				QString enumName = QString(sanitize(typeid(T).name()).data());
				enumName = enumName.split("::")[1];

				//Call to automatically generated function which takes the enum name and the value and returns a string representation of the enum, without the "ENUM_" prefix.
				//Then create the statement from the string representation.
				std::string text = getStringFromEnum(enumName.toStdString(), (int)t);
				createStatementFromLiteral(text);
			}
			//This is called for everything not covered so far. Write the type and attribute to the log file as a warning.
			else {
				BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
			}
		}

	};

	//Helper struct which parses the attributes of a derived entity.
	struct parseAttribute {

		//Function operator() which parses pointers to visitable objects derived from IfcAlignment1x1Type, so objects holding or representing flat values or vectors.
		template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
		operator()(const char* name, std::shared_ptr<T> &ptr)
		{
			if(ptr) {
				//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

				//Push the predicate on the stack and parse all attributes of the type - should always only be 1, but we still use another struct - and pop from stack when finished.
				//Dont know why but i probably had a reason not to use visit_struct::get<0>(*ptr) and pass only that to parseType.
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));
				visit_struct::for_each(*ptr, parseType {});
				predicateStack.pop_back();				
			}
			//Write it as trace to the log file if we have an empty pointer.
			else {
				BLUE_LOG(trace) << "Class " << typenameStack.back() << ", attribute " << name << ". Empty pointer.";
			}
		}		
		
		//Function operator() which parses pointers to entities, so objects that have an id and should be specified in the file and shouldn't be parsed but linked as properties.
		template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(const char* name, std::shared_ptr<T> &ptr){
			if(ptr) {
				//If the pointer is not empty, we get the id and search for the subject in the map and create the statement.
				//We use the attribute name, the typename on the stack and the subject on the stack.
				auto id = std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(ptr)->getId();
				createPropertyStatementFromMap(name, id);				
			}
		}

		//Function operator() which parses pointers to things which are neither IfcAlignment1x1Entity nor IfcAlignment1x1Type but IfcAlignment1x1AbstractSelect.
		//These pointers are declared to hold objects which can be abstract, so their dynamic type is either a IfcAlignment1x1Entity or IfcAlignment1x1Type.
		//These special cases are currently handled manually since it's only 3 classes currently, which are all derived from IfcAlignment1x1Entity in their derived form.
		template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractSelect, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
		operator()(const char* name, std::shared_ptr<T> &base_ptr)
		{
			if(base_ptr.get()) {
				//If the pointer is not empty we get the classname and perform the respective cast.
				QString classname = QString(typeid(*base_ptr).name());
				if(classname.endsWith("IfcSIUnit")) {
					createPropertyStatementFromMap(name, std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcSIUnit>(base_ptr)->getId());
				}
				else if(classname.endsWith("IfcAxis2Placement3D")) {
					createPropertyStatementFromMap(name, std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAxis2Placement3D>(base_ptr)->getId());
				}
				else if(classname.endsWith("IfcGeometricRepresentationContext")) {
					createPropertyStatementFromMap(name, std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationContext>(base_ptr)->getId());
				}
				//If we find a new type which falls in the same category but is not handled, we want to write a warning to the log file.
				else {
					BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
				}
			}
			//Write it as trace to the log file if we have an empty pointer.
			else {
				BLUE_LOG(trace) << "Class " << typenameStack.back() << ", attribute " << name << ". Empty pointer.";
			}
		}
		
		//Function operator() which covers a special case of the first, objects derived from IfcAlignment1x1Type.
		//The IfcPositiveInteger class does not hold a value, its parent class IfcInteger does and we have no general way of upcasting.
		//Same procedure as for IfcPositiveLengthMeasure.
		void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPositiveInteger> ptr)
		{
			//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
			QString predicate = QString(name).split('_')[1];
			predicate[0] = predicate[0].toLower();
			predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

			//Push the predicate on the stack and cast it to IfcInteger and call parseType directly with the name and the value. Pop the predicate from the stack when finished.
			predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));
			parseType {}(name, ((OpenInfraPlatform::IfcAlignment1x1::IfcInteger)*ptr).m_value);
			predicateStack.pop_back();
		}

		//Function operator() which covers a special case of the first, objects derived from IfcAlignment1x1Type.
		//The IfcPositiveLengthMeasure class does not hold a value, its parent class IfcLengthMeasure does and we have no general way of upcasting.
		//Same procedure as for IfcPositiveInteger.
		void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPositiveLengthMeasure> ptr)
		{
			//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
			QString predicate = QString(name).split('_')[1];
			predicate[0] = predicate[0].toLower();
			predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

			//Push the predicate on the stack and cast it to IfcLengthMeasure and call parseType directly with the name and the value. Pop the predicate from the stack when finished.
			predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));
			parseType {}(name, ((OpenInfraPlatform::IfcAlignment1x1::IfcLengthMeasure)*ptr).m_value);
			predicateStack.pop_back();
		}

		//Function operator() which covers std::vector<std::shared_ptr<T>>, so attributes which are vectors.
		//If the vector is not empty, parse every element simultaneously as if it was a single attribute. This results in a list of values as object of one statement.
		template < class T>
		void operator()(const char* name, std::vector<std::shared_ptr<T>> vector)
		{
			if(!vector.empty()) {
				for(auto it : vector) {
					this->operator()(name, it);
				}
			}
		}
		
		//Function operator() which covers std::vector<std::shared_ptr<IfcLengthMeasure>>, a special case of general vectors of pointers.
		//This is handled manually since these are mostly positions, so coordinates etc. which should not be sorted, since the serializer sorts lists.
		void operator()(const char* name, std::vector<std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcLengthMeasure>> vector)
		{
			if(!vector.empty()) {
				//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

				//Push the predicate on the stack and call parseVector for the vector and name. Pop the predicate from the stack when finished.
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));
				parseVector {}(name, vector);
				predicateStack.pop_back();
			}
		}
		
		//Function operator() which covers std::vector<std::vector<std::shared_ptr<T>>>, so vectors of vectors.
		//These are usually IfcCartesianPointList3D etc. so each subvector should be printed as it is, not sorted.
		//TODO: Make these large lists also not sorted since this destroys the index lists and coordinate lists.
		template < class T>
		void operator()(const char* name, std::vector<std::vector<std::shared_ptr<T>>> vector)
		{
			if(!vector.empty()) {
				//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

				//Push the predicate on the stack and call parseVector for each subvector (element in main vector) with the same attribute name and predicate so we get a sorted list.
				//Pop the predicate from the stack when finished.
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));
				for(auto it : vector) {
					parseVector {}(name, it);
				}
				predicateStack.pop_back();
			}
		}
		
		//Function operator() which covers everything else, but has special behaviour for flat base types which are not encapsulated in pointers or IfcTypes.
		//This is probably related to the EarlyBinding generator, but has to be handled.
		template <typename T>
		void operator()(const char* name, T t)
		{
			//If we have an integral or floating point type, we treat it as a IfcType, since the encapsulation doesn't show up in OWL anyway.
			//So something that is an IfcLabel like IfcPerson: m_GivenName shows up as 'ifc:givenName_IfcPerson "Peter";'.
			if(std::is_integral<T>::value || std::is_floating_point<T>::value) {

				//Create our predicate as <ifc_uri_prefix><attribute_name>_<parent_type> since this is the actual URI for the properties.
				QString predicate = QString(name).split('_')[1];
				predicate[0] = predicate[0].toLower();
				predicate = predicate.append("_").append(typenameStack.back().data()).prepend("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");

				//Push the predicate on the stack and call parseType directly with the name and the value. Pop the predicate from the stack when finished.
				predicateStack.push_back(raptor_new_term_from_uri_string(world_, (unsigned char*)(predicate.toStdString().c_str())));
				parseType {}(name, t);
				predicateStack.pop_back();
			}
			//This is if we find something which is not held in a pointer and is not a base type, so it is unhandled and is written to the Log file as a warning.
			else {
				BLUE_LOG(warning) << "Attribute " << name << ": " << sanitize(typeid(T).name()) << ". Type unhandled!";
			}
		}
	};

	//Helper struct to parse the derived ifc object.
	struct DerivedIfcEntityParser {

		//Creates an empty subject in the beginning and the same subject again after all attributes have been parsed to capture relationships etc. .
		template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T& entity) const
		{
			//Create the subject name as "<type>_<id>" to be unique in the file.
			auto type = sanitize(typeid(T).name());
			auto id = QString::number(((OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity) entity).getId()).toStdString();
			std::string subjectString = QString(sanitize(typeid(T).name()).data()).toLower().toStdString() + "_" + id;

			//Initialize subject, predicate and object for owl statement.
			auto subject = raptor_new_term_from_blank(world_, (const unsigned char*)(subjectString.c_str()));
			auto predicate = raptor_new_term_from_uri_string(world_, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
			auto object = raptor_new_term_from_uri_string(world_, (unsigned char*)((std::string("http://www.buildingsmart-tech.org/ifcowl/IFC4x1#").append(type)).c_str()));

			//Create the statement from copies of the initialized statement parts since we still need them later and pass it to the serializer.
			raptor_statement* triple = nullptr;
			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subject);
			triple->predicate = raptor_term_copy(predicate);
			triple->object = raptor_term_copy(object);

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);

			//Push the subject and the type of the parent object on the stack to make them accessible to the attributes and subtypes .
			subjectStack.push_back(subject);
			typenameStack.push_back(type);
			
			//Parse each attribute of the derivedentity and call parseAttribute::operator() for each pair of name and attribute value.
			visit_struct::for_each(entity, parseAttribute {});

			//Create the second statement now containing the "parsed" subject to capture all relationships.
			triple = raptor_new_statement(world_);

			triple->subject = raptor_term_copy(subject);
			triple->predicate = predicate;
			triple->object = object;

			raptor_serializer_serialize_statement(serializer_, triple);
			raptor_free_statement(triple);

			//Remove our subject and typename from teh stack again since we're done now.
			subjectStack.pop_back();
			typenameStack.pop_back();
		}
		
		//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
		template <class T> typename std::enable_if<!std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T& entity) const
		{
			std::string message = "Invalid function call. " + sanitize(typeid(entity).name()) + " isn't a member of IfcAlignment1x1Entity.";
			throw buw::Exception(message.data());
		}

		//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
		void operator()(OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity& entity) const
		{
			std::string message = "Invalid function call.";
			throw buw::Exception(message.data());
		}
	};

	//Helper struct to parse each object in the map.
	struct MapIfcObjectsParser {

		//Function operator which takes the IfcAlignment1x1Entity and calls a function that performs a cast to its runtime type and calls a struct that parses the derived object.
		void operator()(std::pair<const int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> pair)
		{
			OpenInfraPlatform::IfcAlignment1x1::castToDerivedAndCall<DerivedIfcEntityParser, void>(pair.second, DerivedIfcEntityParser {});
		}
	};

	//Helper struct to create an owl subject for neach object in the map.
	struct CreateSubjectMap {

		//Function operator() to iterate over the map and create a subject for each object to capture the relationships between objects.
		void operator()(std::pair<const int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> pair)
		{
			//Create the subject name as <typename>_<id> to be somewhat unique in the file and that it can be referenced.
			auto type = sanitize(typeid(*pair.second).name());
			auto id = QString::number(pair.first).toStdString();
			std::string subjectString = QString(type.data()).toLower().toStdString() + "_" + id;

			//Create the subject and insert it into the map.
			auto subject = raptor_new_term_from_blank(world_, (const unsigned char*)(subjectString.c_str()));
			subjectMap.insert(std::pair<int, raptor_term*>(pair.first, subject));
		}
	};

public:
	ExportIfcOWL4x1Impl(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) {
		
		//Generate UUID as filename for the temporary .ifc file from which we take the model.
		auto uuid = boost::uuids::uuid();
		std::string temp = "./";
		temp.append(boost::uuids::to_string(uuid));
		temp.append(".ifc");

		//Export the file temporarily as Ifc4x1 to get the model from the exporter.
		auto ifcExporter = buw::makeReferenceCounted<buw::ExportIfc4x1>(ifcAlignmentExportDescription(),am, dem, temp);
		boost::filesystem::remove(temp);		
		auto model = ifcExporter->getIfcAlignment1x1Model();

		//Initialize the raptor serializer, world and the file.
		outfile = fopen(filename.c_str(), "w");
		world_ = raptor_new_world();
		if(boost::ends_with(filename, "rdf"))
			serializer_ = raptor_new_serializer(world_, "rdfxml-abbrev");
		else
			serializer_ = raptor_new_serializer(world_, "turtle");

		raptor_serializer_start_to_file_handle(serializer_, nullptr, outfile);

		//Initialize the namespace and prefix for rdf and ifc
		const unsigned char* ifc_prefix = (const unsigned char*)"ifc";
		raptor_uri* ifc_uri = raptor_new_uri(world_, (const unsigned char*)"http://www.buildingsmart-tech.org/ifcowl/IFC4x1#");
		raptor_serializer_set_namespace(serializer_, ifc_uri, ifc_prefix);

		const unsigned char* rdf_prefix = (const unsigned char*)"rdf";
		raptor_uri* rdf_uri = raptor_new_uri(world_, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#");
		raptor_serializer_set_namespace(serializer_, rdf_uri, rdf_prefix);
		
		//Create a map of all subjects - objects in the map - to capture the relationships between the different ifc objects.
		std::for_each(model->getMapIfcObjects().begin(), model->getMapIfcObjects().end(), CreateSubjectMap {});

		//Parse each object in the map and write it to the owl file.
		std::for_each(model->getMapIfcObjects().begin(), model->getMapIfcObjects().end(), MapIfcObjectsParser {});		
	}

	virtual ~ExportIfcOWL4x1Impl() {

		//Free the raptor variables.
		raptor_serializer_serialize_end(serializer_);
		raptor_free_serializer(serializer_);
		raptor_free_world(world_);

		//Call the destructor functions for all objects in the stacks and map.
		for(auto it : subjectStack)
			raptor_free_term(it);

		for(auto it : predicateStack)
			raptor_free_term(it);

		for(auto it : objectStack)
			raptor_free_term(it);

		for(auto it : subjectMap)
			raptor_free_term(it.second);

		//Clear the stacks.
		subjectStack.clear();
		predicateStack.clear();
		objectStack.clear();
		subjectMap.clear();

		//Close the file we write to.
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

//Initialization for static variables, never remove those since the compiler wants them!
raptor_world* OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl::world_ = raptor_new_world();
raptor_serializer* OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1::ExportIfcOWL4x1Impl::serializer_ = raptor_new_serializer(world_, "turtle");