/*
  This file is part of TUM Open Infra Platform Early Binding EXPRESS
  Generator, a simple early binding generator for EXPRESS.
  Copyright (c) 2016-2017 Technical University of Munich
  Chair of Computational Modeling and Simulation.

  TUM Open Infra Platform Early Binding EXPRESS Generator is free
  software; you can redistribute it and/or modify it under the terms
  of the GNU General Public License Version 3 as published by the Free
  Software Foundation.

  TUM Open Infra Platform Early Binding EXPRESS Generator is
  distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
  for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "GeneratorOIP.h"

#include "OpenInfraPlatform/ExpressBinding/namespace.h"
//#include <Windows.h>
#include <algorithm>
#include <cassert>
#include <experimental/filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>

#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

namespace fs = std::experimental::filesystem;


std::string license =
  "\
\
// Copied and modified code from \"IfcPlusPlus\" library.\n\
// This library is available under the OpenSceneGraph Public License. Original copyright notice:\n\
\n\
/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold\n\
*\n\
* This library is open source and may be redistributed and / or modified under\n\
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or\n\
* (at your option) any later version.The full license is in LICENSE file\n\
* included with this distribution, and on the openscenegraph.org website.\n\
*\n\
* This library is distributed in the hope that it will be useful,\n\
* but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the\n\
* OpenSceneGraph Public License for more details.\n\
*/\
";

std::string license_cmake =
"#\n\
#    Copyright(c) 2018 Technical University of Munich\n\
#    Chair of Computational Modeling and Simulation.\n\
#\n\
#    TUM Open Infra Platform is free software; you can redistribute it and/or modify\n\
#    it under the terms of the GNU General Public License Version 3\n\
#    as published by the Free Software Foundation.\n\
#\n\
#    TUM Open Infra Platform is distributed in the hope that it will be useful,\n\
#    but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the\n\
#    GNU General Public License for more details.\n\
#\n\
#    You should have received a copy of the GNU General Public License\n\
#    along with this program.If not, see <http://www.gnu.org/licenses/>.\n\
#\n\
";

std::string notice =
  "\
/* This file has been automatically generated using the TUM Open Infra Platform\n\
Early Binding EXPRESS Generator. Any changes to this file my be lost in the future. */";

std::string notice_cmake =
"\
# This file has been automatically generated using the TUM Open Infra Platform\n\
# Early Binding EXPRESS Generator. Any changes to this file my be lost in the future.";

static size_t indentation = 0;

enum eKeepDelimCharacter {None, Left, Right, Standalone};
std::vector<std::string> split(std::string text, char delim, eKeepDelimCharacter value)
{
	if(text.find(delim) == std::string::npos) {
		return { text };
	}
	else {
		// Initialize the stringlist in which we want to store the tokenized string.
		std::vector<std::string> stringlist = std::vector<std::string>();
		std::string line;
		bool isString = false;

		// Iterate over all characters in the text.
		for(int i = 0; i < text.size(); i++) {
			char character = text[i];

			// If we find the string delimiters and are not in string, we are in string, otherwise we're not, so it's a simple toggle.
			if(character == '\"')
				isString = !isString;

			// If the character is the delim character and we're not in string mode, process it, otherwise skip it.
			if(character == delim && !isString) {				

				switch(value) {
					// If we don't want to keep it, add the current line if it is not empty.
				case None:
					if(!line.empty()) {
						stringlist.push_back(line);
						line.clear();
					}
					continue;
					// If we want to add it to the left side, we add it and push back the line and then clear it.
				case Left:
					line += character;
					stringlist.push_back(line);
					line.clear();
					continue;
					// If we want to add it to the right side, we push back the line - if not empty - and then add the char to the new line.
				case Right:
					if(!line.empty()) {
						stringlist.push_back(line);
						line.clear();
					}
					line += character;
					continue;
					// If we want it to be standalone, we push back the current line if not empty, clear it and add the char to the line, push it back and clear it again.
				case Standalone:
					if(!line.empty()) {
						stringlist.push_back(line);
						line.clear();
					}
					line += character;
					stringlist.push_back(line);
					line.clear();
					continue;

				default: break;
				}
			}
			else {
				line += character;
			}
		}

		// Add the last element if it is not empty.
		if(!line.empty())
			stringlist.push_back(line);
		
		return stringlist;
	}
}

std::string join(std::vector<std::string>& params, char sep) {
	std::string text;
	for (auto val : params)
		text += val + sep;
	text.pop_back();
	return text;
}
std::string createIfElseStatement(std::string condition, std::string doThen, std::string doElse = "")
{
	std::string statement = "if(" + condition + ") {" + doThen + "}";

	if(!doElse.empty())
		statement += "else {" + doElse + "}";

	return statement;
};

std::string toUpper(const std::string &inputString) {
	std::string str = inputString;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

std::string replaceAll(std::string str, const std::string &from, const std::string &to) {
	// replace this using boost!
	// copied from
	// http://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

void copyTemplate(const std::string &templateFilename, const std::string &outFilename, const Schema &schema) {
	std::ofstream out(outFilename);
	
	std::ifstream in(templateFilename);
	std::string line;
	while (std::getline(in, line)) {
		out << replaceAll(line, "Ifc2x3", schema.getName()) << std::endl;
	}
}

void copyFile(const std::string &filename, const std::string &outFilename) {
	std::ofstream out(outFilename);
		
	std::ifstream in(filename);
	std::string line;
	while (std::getline(in, line)) {
		out << line << std::endl;
	}
}


void indent(std::ostream &out, size_t level = indentation)
{
	for(size_t i = 0; i < level; i++)
		out << "\t";
}

void linebreak(std::ostream &out)
{
	out << std::endl;
}

void write(std::ostream &out, std::string text)
{
	for(char character : text) {
		if(character == '}')
			indentation--;
	}

	out << text;

	for(char character : text) {
		if(character == '{')
			indentation++;
	}
}

void writeLine(std::ostream &out, std::string text)
{
	// If we have a line with { and } we remain at the same indentation and simply ignore it.
	if(text.find('{') != std::string::npos && text.find('}') != std::string::npos) {
		indent(out);
		write(out, text);
		out << std::endl;
	}
	else {
		for(char character : text) {
			if(character == '}')
				indentation--;
		}

		indent(out);
		out << text;
		out << std::endl;

		for(char character : text) {
			if(character == '{')
				indentation++;
		}
	}
}
void writeBeginNamespace(std::ostream &out, const OpenInfraPlatform::ExpressBinding::Schema &schema)
{
	writeLine(out, "namespace OpenInfraPlatform");
	writeLine(out, "{");
	writeLine(out, "namespace " + schema.getName());
	writeLine(out, "{");
}

void writeEndNamespace(std::ostream &out, const OpenInfraPlatform::ExpressBinding::Schema &schema)
{
	writeLine(out, "} // end namespace " + schema.getName());
	writeLine(out, "} // end namespace OpenInfraPlatform");
}

void writeEndClass(std::ostream &out, OpenInfraPlatform::ExpressBinding::Type &type)
{
	writeLine(out, "}; // end class " + type.getName());
}

void writeEndClass(std::ostream &out, OpenInfraPlatform::ExpressBinding::Entity &entity)
{
	writeLine(out, "}; // end class " + entity.getName());
}

void writeLicenseAndNotice(std::ostream &out)
{
	out << license << std::endl;
	out << std::endl;
	out << notice << std::endl;
	out << std::endl;
}

void writeInclude(std::ostream &out, std::string filename, bool useAngleBrackets = false)
{
	if(useAngleBrackets)
		writeLine(out ,"#include <" + filename + ">");
	else
		writeLine(out, "#include \"" + filename + "\"");
}



void writeEntityDestructor(std::ostream &out, const OpenInfraPlatform::ExpressBinding::Entity &entity, std::string parameters = "", std::string implementation = "")
{
	std::string signature = entity.getName() + "::~" + entity.getName() + "(" + parameters + ") {" + implementation + "}";
	writeLine(out, signature);
}

void writeEntityFunction(std::ostream &out, const OpenInfraPlatform::ExpressBinding::Entity &entity, std::string returnType, std::string name, std::string parameters = "", std::string qualifiers = "", std::string implementation = "")
{
	std::string signature = "";

	if(!returnType.empty())
		signature = returnType + " ";

	signature += entity.getName() + "::" + name + "(" + parameters + ")";

	if(!qualifiers.empty())
		signature += " " + qualifiers;

	if(!implementation.empty()) {
		signature += " {";
		writeLine(out, signature);

		auto linebreaks = split(implementation, '\n', None);

		std::vector<std::string> statements = std::vector<std::string>();
		for(auto it : linebreaks) {
			auto &tokens = split(it, ';', Left);
			statements.insert(statements.end(), tokens.begin(), tokens.end());
		}

		std::vector<std::string> textSplitByOpenBraces = std::vector<std::string>();
		for(auto statement : statements) {
			auto &tokens = split(statement, '{', Left);
			textSplitByOpenBraces.insert(textSplitByOpenBraces.end(), tokens.begin(), tokens.end());
		}

		std::vector<std::string> lines = std::vector<std::string>();
		for(auto line : textSplitByOpenBraces) {
			auto &tokens = split(line, '}', Standalone);
			lines.insert(lines.end(), tokens.begin(), tokens.end());
		}
				

		auto end = std::remove_if(lines.begin(), lines.end(), [](const std::string &str)->bool {return str == " " || str == ""; });
		lines.erase(end, lines.end());

		std::for_each(lines.begin(), lines.end(), [](std::string &str) {
			if(str.front() == ' ')
				str = str.substr(1, str.size() - 1);
			if(str.back() == ' ')
				str = str.substr(0, str.size() - 1);
		});

		for(auto elem : lines)
			writeLine(out, elem);

		writeLine(out, "}");
	}
	else {
		signature += "{ }";
		writeLine(out, signature);
	}
}

void writeEntityConstructor(std::ostream &out, const OpenInfraPlatform::ExpressBinding::Entity &entity, std::string parameters = "", std::string implementation = "")
{
	//std::string signature = entity.getName() + "::" + entity.getName() + "(" + parameters + ") {" + implementation + "}";
	//writeLine(out, signature);
	writeEntityFunction(out, entity, "", entity.getName(), parameters, "", implementation);
}

void writeValueTypeFile(const Type& type, std::ostream& out) {
	const std::string name = type.getName();
	const std::string basetype = type.getUnderlyingTypeName();
	
	/*
	class name : public basetype {\
	using base = basetype;\
	public:\
	typedef name type;\
	using base::base;\
	using base::operator=;\
	virtual name* operator->() override { return this; }\
	virtual const name* const operator->() const override { return this; }\
	virtual name& operator=(const Optional<name> &other) { this->m_value = other.get_value_or(name()); return *this; };\
	virtual const std::string classname() const override { return #name; }\
	};
	*/

	writeLine(out, "class " + name + " : public " + basetype + "{");
	writeLine(out, "using base = " + basetype + ";");
	writeLine(out, "public:");
	writeLine(out, "typedef " + name + " type;");
	linebreak(out);
	writeLine(out, name + "() = default;");
	writeLine(out, name + "(const " + name + "& other) = default;");
	writeLine(out, "virtual ~" + name + "() { };");
	linebreak(out);
	writeLine(out, "using base::base;");
	writeLine(out, "using base::operator=;");
	//writeLine(out, "using base::operator>>;");
	//writeLine(out, "using base::operator<<;");
	linebreak(out);
	writeLine(out, name + "& operator=(const " + name + "& other) = default;");
	writeLine(out, "virtual " + name + "& operator=(const Optional<" + name + "> &other) { this->m_value = other.get_value_or(" + name + "()); return *this; };");
	linebreak(out);
	writeLine(out, "virtual " + name + "* operator->() override { return this; }");
	writeLine(out, "virtual const " + name + "* const operator->() const override { return this; }");
	linebreak(out);
	writeLine(out, "virtual const std::string classname() const override { return \"" + name + "\"; }");
	writeLine(out, "};");
	return;
}

void writeContainerTypeFile(Schema& schema, Type& type, std::ostream& out) {
	/*
	#define DEFINE_CONTAINERTYPE(name, containertype, min, max, valuetype)\
	class name : public ExpressBinding::EXPRESSContainer<containertype<valuetype>,valuetype,min,max>, public ExpressBinding::EXPRESSType {\
	using base = ExpressBinding::EXPRESSContainer<containertype<valuetype>,valuetype,min,max>;\
	public:\
		typedef name type;\
		using base::base;\
		using base::operator=;\
		using base::operator containertype<valuetype>&;\
		name* operator->() { return this; }\
		const name* const operator->() const { return this; }\
		virtual name& operator=(const Optional<name> &other) { operator=(other.get_value_or(name())); return *this; };\
		virtual const std::string classname() const override { return #name; }\
		virtual const std::string getStepParameter() const override {return base::getStepParameter(); }\
	};
	*/

	const std::string name = type.getName();
	const std::string min = std::to_string(type.getContainerCardinalityMin());
	const std::string max = std::to_string(type.getContainerCardinalityMax());
	const std::string containertype = type.getContainerTypeName() + "TYPE";
	std::string valuetype = type.getContainerType();
	if (schema.hasEntity(valuetype)) {
		valuetype = "EXPRESSReference<" + valuetype + ">";
	}
	const std::string basetype = "ExpressBinding::" + type.getContainerTypeName() + "<" + min + "," + max + "," + valuetype + ">";

	writeLine(out, "class " + name + ": public " + basetype + ", public ExpressBinding::EXPRESSType {");
	writeLine(out, "using base = " + basetype + ";");
	writeLine(out, "public:");
	writeLine(out, name + "() = default;");
	writeLine(out, name + "(const "+ name + "& other) = default;");
	//writeLine(out, name + "(const base& other) : base(other) { };");

	writeLine(out, "~" + name + "() { };");
	linebreak(out);
	writeLine(out, "using base::base;");
	writeLine(out, "using base::operator=;");
	//writeLine(out, "using base::operator " + containertype + "<" + valuetype + ">&;");
	linebreak(out);	
	writeLine(out,  name + "* operator->() { return this; }");
	writeLine(out, "const " + name + "* const operator->() const { return this; }");
	linebreak(out);
	writeLine(out, name + "& operator=(const " + name + "& other) = default;");
	writeLine(out, name + "& operator=(const Optional<" + name + "> &other) { operator=(other.get_value_or(" + name + "())); return *this; };");
	linebreak(out);
	writeLine(out, "virtual const std::string classname() const override { return \"" + name + "\"; }");
	writeLine(out, "virtual const std::string getStepParameter() const override { return this->base::getStepParameter(); }");
	linebreak(out);
	//writeLine(out, "static " + name + " readStepData(const std::string& args, const std::shared_ptr<ExpressBinding::EXPRESSModel>& model) {");
	//writeLine(out, "return base::readStepData(args, model);");
	//writeLine(out, "}");
	writeLine(out, "};");
}

void writeEnumTypeFile(std::string name, std::vector<std::string> seq, std::ostream& out) {

	/*
	#define ENUM_W_STR(name, type, seq)\
        enum class name : type {\
            BOOST_PP_SEQ_ENUM(seq)\
        };\
        inline const std::string to_string(name v)\
        {\
            switch (v)\
            {\
                BOOST_PP_SEQ_FOR_EACH(\
                        ENUMUTLS_STR_SWITCH_CASE,\
                        name,\
                        seq)\
                default: return "unknown " BOOST_PP_STRINGIZE(name);\
            }\
        }
	*/
	const std::string enumName = "e" + name;

	writeLine(out, "enum class "+ enumName + ": int {");
	for (int i = 0; i < seq.size(); i++) {
		if (i != seq.size() - 1) {
			writeLine(out, seq[i] + " = " + std::to_string(i) + ",");
		}
		else {
			writeLine(out, seq[i] + " = " + std::to_string(i));
		}

	}
	writeLine(out, "};");
	linebreak(out);
	writeLine(out, "inline const std::string to_string(const " + enumName + "& v) {");
	writeLine(out, "switch(v) {");
	for (auto elem: seq) {
		writeLine(out, "case "+ enumName + "::" + elem + ": return \"." + elem + ".\";");
	}
	writeLine(out, "default: return \"unknown\";");
	writeLine(out, "}");
	writeLine(out, "}");
	linebreak(out);

	const std::string basetype = "ExpressBinding::ValueType<" + enumName + ">";
	
	/*
	#define DEFINE_ENUMTYPE(name, seq)\
	ENUM_W_STR(name##Values, int, seq);\
	class name : public OpenInfraPlatform::ExpressBinding::ValueType<name##Values> {\
		using base = OpenInfraPlatform::ExpressBinding::ValueType<name##Values>;\
		public:\
			typedef name type;\
			using base::base;\
			using base::operator=;\
			using base::operator->;\
			virtual name& operator=(const Optional<name> &other) { this->m_value = other.get_value_or(name()); return *this; };\
			virtual const std::string classname() const override { return #name; }\
			const std::string name::getStepParameter() const { return "." + to_string(OpenInfraPlatform::ExpressBinding::ValueType<name##Values>::m_value) + "."; };\
			static name##Values name::readStepData(const std::string &value) {\
				auto from_string = [](const std::string &value)-> name##Values {\
					BOOST_PP_SEQ_FOR_EACH(\
						ENUMUTLS_FROM_STR_SWITCH_CASE,\
						name##Values,\
						seq)\
					return name##Values::BOOST_PP_SEQ_HEAD(seq);\
				};\
		return from_string(value.substr(1, value.size() - 2));\
		};\
	};
	*/

	writeLine(out, "class " + name + " : public " + basetype + " {");
	writeLine(out, "using base = " + basetype + ";");
	writeLine(out, "public:");
	writeLine(out, "typedef " + enumName + " Enum;");
	linebreak(out);

	writeLine(out, "using base::base;");
	writeLine(out, "using base::operator=;");
	writeLine(out, "using base::operator->;");
	linebreak(out);
	
	writeLine(out, "virtual " + name + "& operator=(const Optional<" + name + "> &other) { this->m_value = other.get_value_or(" + name + "()); return *this; };");
	writeLine(out, "virtual const std::string classname() const override { return \"" + name + "\"; }");
	writeLine(out, "const std::string getStepParameter() const { return to_string(" + basetype + "::m_value); };");
	writeLine(out, "static " + enumName + " readStepData(const std::string &value) {");
	writeLine(out, "const std::string name = value.substr(1, value.size() - 2);");
	for (auto elem : seq) {
		writeLine(out, "if(name == \"" + elem + "\") return Enum::" + elem + ";");
	}
	writeLine(out, "return Enum::" + seq[0] + ";");
	writeLine(out, "};");
	writeLine(out, "};");
	return;
}

void writeEnumTypeFileRefactored(std::string name, std::vector<std::string> seq, std::ostream& out) {
	const std::string enumName = "e" + name;

	writeLine(out, "enum class " + enumName + ": int {");
	for (int i = 0; i < seq.size(); i++) {
		if (i != seq.size() - 1) {
			writeLine(out, seq[i] + " = " + std::to_string(i) + ",");
		}
		else {
			writeLine(out, seq[i] + " = " + std::to_string(i));
		}

	}
	writeLine(out, "};");
	linebreak(out);
	writeLine(out, "inline const std::string to_string(const " + enumName + "& v) {");
	writeLine(out, "switch(v) {");
	for (auto elem : seq) {
		writeLine(out, "case " + enumName + "::" + elem + ": return \"." + elem + ".\";");
	}
	writeLine(out, "default: return \"unknown\";");
	writeLine(out, "}");
	writeLine(out, "}");
	linebreak(out);

	const std::string basetype = "ExpressBinding::EnumType<" + enumName + "," + std::to_string(seq.size()) + ">";
	writeLine(out, "class " + name + " : public " + basetype + " {");
	writeLine(out, "using base = " + basetype + ";");
	writeLine(out, "public:");
	writeLine(out, name + "() = default;");
	writeLine(out, name + "(const " + name + "& other) = default;");
	writeLine(out, "virtual ~" + name + "() { };");
	linebreak(out);
	writeLine(out, "using base::base;");
	writeLine(out, "using base::operator=;");
	writeLine(out, "using base::operator->;");
	linebreak(out);
	writeLine(out, name + "& operator=(const " + name + "& other) = default;");
	//writeLine(out, "virtual " + name + "& operator=(const Optional<" + name + "> &other) { this->m_value = other.get_value_or(" + name + "()); return *this; };");
	linebreak(out);
	writeLine(out, "virtual const std::string classname() const override { return \"" + name + "\"; }");
	writeLine(out, "};");
	return;
}
void resolveEntity(Schema& schema, const Entity& entity, std::ostream& out) {
	if (schema.isAbstract(entity)) {
		for (int sub = 0; sub < entity.getSubtypeCount(); sub++) {
			auto subtype = schema.getEntityByName(entity.getSubtypeByIndex(sub));
			resolveEntity(schema, subtype, out);
		}
	}
	else {
		std::string rawType = entity.getName();
		std::string upper;
		upper.resize(rawType.size());
		std::transform(rawType.begin(), rawType.end(), upper.begin(), ::toupper);
		/*if(name == BOOST_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(elem))) return select(elem::type::readStepData(value.substr( value.find_first_of('(') + 1,  value.find_first_of(')') )));*/
		writeLine(out, "if(name == \"" + upper + "\") return this->model.lock()->[strtoull(arg)];");
	}
}

void writeSelectTypeFile(Schema & schema, Type& selectType, std::ostream& out) {
	/*
	#define DEFINE_SELECTTYPE(select, seq)\
	class select : public boost::make_recursive_variant<BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_TO_TUPLE(seq))>::type, public OpenInfraPlatform::ExpressBinding::EXPRESSType {\
	using base = boost::make_recursive_variant<BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_TO_TUPLE(seq))>::type;\
	public:\
	select() = default;\
	using base::base;\
	BOOST_PP_SEQ_FOR_EACH_I(\
	SELECT_CAST_REF_OPERATOR,\
	,\
	seq\
	)\
	BOOST_PP_SEQ_FOR_EACH_I(\
	SELECT_CAST_CONST_OPERATOR,\
	,\
	seq\
	)\
	template <typename V> operator V&() {\
	switch(this->base::which()) {\
	BOOST_PP_SEQ_FOR_EACH_I(\
	CASE, \
	, \
	seq\
	)\
	default: return (V&) boost::get<BOOST_PP_SEQ_ELEM(0,seq)>(*this);\
	}\
	};\
	virtual const std::string getStepParameter() const override {\
	std::string param;\
	switch(this->base::which()) {\
	BOOST_PP_SEQ_FOR_EACH_I(\
	GET_STEP_PARAMETER, \
	, \
	seq\
	)\
	default: break;\
	}\
	return param;\
	}\
	virtual const std::string classname() const override { return #select; };\
	static select readStepData(const std::string& value) {\
	auto name = value.substr(0, value.find_first_of('('));\
	BOOST_PP_SEQ_FOR_EACH_I(\
	READ_STEP_DATA, \
	select, \
	seq\
	)\
	return select();\
	}\
	select* operator->() { return this; };\
	const select* const operator->() const { return this; };\
	typedef select type;\
	};
	*/

	const std::string select = selectType.getName();
	std::vector<std::string> seq = selectType.getTypes();
	std::transform(seq.begin(), seq.end(), seq.begin(), [&schema](std::string elem)->std::string {return schema.hasEntity(elem) ? "EXPRESSReference<" + elem + ">" : elem; });

	const std::string basetype = "boost::make_recursive_variant<" + join(seq, ',') + ">::type";
	writeLine(out, "class " + select + " : public " + basetype + ", public ExpressBinding::EXPRESSType {");
	writeLine(out, "using base = " + basetype + ";");
	writeLine(out, "public:");
	writeLine(out, select + "() = default;");
	writeLine(out, "using base::base;");
	linebreak(out);

	writeLine(out, select + "* operator->() { return this; };");
	writeLine(out, "const " + select + "* const operator->() const { return this; };");
	writeLine(out, "typedef " + select + " type;");
	linebreak(out);

	/*
	#define SELECT_CAST_REF_OPERATOR(r, data, i, elem)\
	operator elem&() { return boost::get<elem>(*this); };

	#define SELECT_CAST_CONST_OPERATOR(r, data, i, elem)\
	operator const elem() const { return boost::get<elem>(*this); };
	*/
	for (auto elem : seq) {
		writeLine(out, "operator " + elem + "&() { return boost::get<" + elem + ">(*this); };");
		writeLine(out, "operator const " + elem + "() const { return boost::get<" + elem + ">(*this); };");
	}

	/*
	template <typename V> operator V&() {\
	switch(this->base::which()) {\
	BOOST_PP_SEQ_FOR_EACH_I(\
	CASE, \
	, \
	seq\
	)\
	default: return (V&) boost::get<BOOST_PP_SEQ_ELEM(0,seq)>(*this);\
	}\
	};\
	*/

	writeLine(out, "template <typename V> operator V&() {");
	writeLine(out, "switch(this->base::which()) {");
	for (int i = 0; i < seq.size(); i++) {
		/*case i: return (V&) boost::get<elem>(*this);*/
		writeLine(out, "case " + std::to_string(i) + ": return (V&) boost::get<" + seq[i] + ">(*this);");
	}
	writeLine(out, "default: return (V&) boost::get<" + seq[0] + ">(*this);");
	writeLine(out, "};");
	writeLine(out, "};");
	linebreak(out);

	/*
	virtual const std::string getStepParameter() const override {\
	std::string param;\
	switch(this->base::which()) {\
	BOOST_PP_SEQ_FOR_EACH_I(\
	GET_STEP_PARAMETER, \
	, \
	seq\
	)\
	default: break;\
	}\
	return param;\
	}\
	*/
	writeLine(out, "virtual const std::string getStepParameter() const override {");
	writeLine(out, "switch(this->base::which()) {");
	for (int i = 0; i < seq.size(); i++) {
		/*case i: param.append(boost::get<elem>(*this)->classname()).append("(").append(boost::get<elem>(*this)->getStepParameter()).append(")");*/
		writeLine(out, "case " + std::to_string(i) + ": return boost::get<" + seq[i] + ">(*this)->classname() + \"(\" + boost::get<" + seq[i] + ">(*this)->getStepParameter() + \")\";");
	}
	writeLine(out, "default: return \"unknown\";");
	writeLine(out, "};");
	writeLine(out, "};");
	linebreak(out);

	writeLine(out, "virtual const std::string classname() const override { return \"" + select + "\"; };");
	linebreak(out);

	/*
	static select readStepData(const std::string& value) {\
	auto name = value.substr(0, value.find_first_of('('));\
	BOOST_PP_SEQ_FOR_EACH_I(\
	READ_STEP_DATA, \
	select, \
	seq\
	)\
	return select();\
	}\
	*/
	writeLine(out, "static " + select + " readStepData(const std::string& value) {");
	writeLine(out, "auto name = value.substr(0, value.find_first_of('('));");
	writeLine(out, "auto arg = value.substr( value.find_first_of('(') + 1,  value.find_first_of(')') );");
	for (std::string rawType : selectType.getTypes()) {
		if (schema.hasEntity(rawType)) {
			resolveEntity(schema, schema.getEntityByName(rawType), out);
		}
		else {
			std::string upper;
			upper.resize(rawType.size());
			std::transform(rawType.begin(), rawType.end(), upper.begin(), ::toupper);
			/*if(name == BOOST_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(elem))) return select(elem::type::readStepData(value.substr( value.find_first_of('(') + 1,  value.find_first_of(')') )));*/
			writeLine(out, "if(name == \"" + upper + "\") return " + rawType + "(" + rawType + "::readStepData(arg));");
		}
	}
	writeLine(out, "return " + select + "();");
	writeLine(out, "};");

	writeLine(out, "};");
	return;
}

void writeSelectTypeFileREFACTORED(Schema& schema, Type& selectType, std::ostream& out) {
	//class IfcTimeOrRatioSelect : public OpenInfraPlatform::ExpressBinding::SelectType<IfcTimeOrRatioSelect, IfcDuration, IfcRatioMeasure> {
	//	using base = OpenInfraPlatform::ExpressBinding::SelectType<IfcTimeOrRatioSelect, IfcDuration, IfcRatioMeasure>;
	//public:
	//	using base::base;
	//	using base::operator=;		
	//
	//	virtual const std::string classname() const override { return "IfcTimeOrRatioSelect"; }
	//};

	const std::string select = selectType.getName();
	std::vector<std::string> seq = selectType.getTypes();
	std::transform(seq.begin(), seq.end(), seq.begin(), [&schema](std::string elem)->std::string {return schema.hasEntity(elem) ? "EXPRESSReference<" + elem + ">" : elem; });

	const std::string basetype = "ExpressBinding::SelectType<" + join(seq, ',') + ">";
	//writeLine(out, "class " + select + " : public " + basetype +", public ExpressBinding::EXPRESSType {");
	writeLine(out, "class " + select + " : public " + basetype + " {");
	writeLine(out, "using base = " + basetype + ";");
	writeLine(out, "public:");
	writeLine(out, select + "() = default;");
	//writeLine(out, select + "(const base& other) : base(other) { };");
	writeLine(out, select + "(const "+ select + "& other) = default;");
	//writeLine(out, "~" + select + "() { };");
	writeLine(out, select + "& operator=(const " + select + "& other) = default;");
	linebreak(out);
	writeLine(out, "using base::base;");
	writeLine(out, "using base::operator=;");
	linebreak(out);
	writeLine(out, "virtual const std::string classname() const override { return \"" + select + "\"; }");
	writeLine(out, "virtual const std::string getStepParameter() const { return base::getStepParameter(); }");
	writeLine(out, "};");
}

void writeSelectTypeFileMinimal(Schema& schema, Type& selectType, std::ostream& out) {
	const std::string select = selectType.getName();
	std::vector<std::string> seq = selectType.getTypes();
	std::transform(seq.begin(), seq.end(), seq.begin(), [&schema](std::string elem)->std::string {return schema.hasEntity(elem) ? "EXPRESSReference<" + elem + ">" : elem; });

	writeLine(out, "class " + select + " {");
	writeLine(out, "public:");
	writeLine(out, select + "() = default;");
	writeLine(out, "~" + select + "() { };");
	writeLine(out, select + "& operator=(const " + select + "& other) = default;");
	linebreak(out);
	writeLine(out, select + "* operator->(){ return this; }");
	writeLine(out, "const std::string classname() const { return \"" + select + "\"; }");
	writeLine(out, "const std::string getStepParameter() const { return \"$\"; }");
	writeLine(out, "static " + select + " readStepData(const std::string arg, const std::shared_ptr<ExpressBinding::EXPRESSModel>& model) { return " + select + "(); }");
	writeLine(out, "};");
}

OpenInfraPlatform::ExpressBinding::GeneratorOIP::GeneratorOIP(const std::string &outputDirectory) : outputDirectory_(outputDirectory) {
}



GeneratorOIP::~GeneratorOIP() {
}

void GeneratorOIP::generate(std::ostream &out, OpenInfraPlatform::ExpressBinding::Schema &schema) {
	rootDirectory_ = outputDirectory_ + "/" + schema.getName();

	std::string schemaDirectory = rootDirectory_ + "/schema";
	sourceDirectory_ = rootDirectory_ + "/src";
	entityPath_ = sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName() + "/entity";
	typePath_ = sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName() + "/type";
	guidPath_ = sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName() + "/guid";
	readerPath_ = sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName() + "/reader";
	modelPath_ = sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName() + "/model";
	writerPath_ = sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName() + "/writer";
	xmlPath_ = sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName() + "/xml";

	if (!fs::exists(rootDirectory_)) {
		fs::create_directory(rootDirectory_);
	}

	if (!fs::exists(schemaDirectory)) {
		fs::create_directory(schemaDirectory);
	}

	if (!fs::exists(sourceDirectory_)) {
		fs::create_directory(sourceDirectory_);
	}

	if (!fs::exists(sourceDirectory_ + "/OpenInfraPlatform")) {
		fs::create_directory(sourceDirectory_ + "/OpenInfraPlatform");
	}

	if (!fs::exists(sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName())) {
		fs::create_directory(sourceDirectory_ + "/OpenInfraPlatform/" + schema.getName());
	}

	if (!fs::exists(guidPath_)) {
		fs::create_directory(guidPath_);
	}

	if (!fs::exists(entityPath_)) {
		fs::create_directory(entityPath_);
	}

	if (!fs::exists(readerPath_)) {
		fs::create_directory(readerPath_);
	}

	if (!fs::exists(modelPath_)) {
		fs::create_directory(modelPath_);
	}

	if (!fs::exists(writerPath_)) {
		fs::create_directory(writerPath_);
	}

	if (!fs::exists(xmlPath_)) {
		fs::create_directory(xmlPath_);
	}

	// guid
	copyTemplate("Template/guid/CreateGuid_64.h", guidPath_ + "/CreateGuid_64.h", schema);
	copyTemplate("Template/guid/CreateGuid_64.cpp", guidPath_ + "/CreateGuid_64.cpp", schema);
	// model
	copyTemplate("Template/model/Exception.cpp", modelPath_ + "/Exception.cpp", schema);
	copyTemplate("Template/model/Exception.h", modelPath_ + "/Exception.h", schema);
	copyTemplate("Template/model/Model.cpp", modelPath_ + "/Model.cpp", schema);
	copyTemplate("Template/model/Model.h", modelPath_ + "/Model.h", schema);
	copyTemplate("Template/model/Object.cpp", modelPath_ + "/Object.cpp", schema);
	copyTemplate("Template/model/Object.h", modelPath_ + "/Object.h", schema);
	copyTemplate("Template/model/shared_ptr.h", modelPath_ + "/shared_ptr.h", schema);
	copyTemplate("Template/model/StatusObservable.cpp", modelPath_ + "/StatusObservable.cpp", schema);
	copyTemplate("Template/model/StatusObservable.h", modelPath_ + "/StatusObservable.h", schema);
	copyTemplate("Template/model/UnitConverter.cpp", modelPath_ + "/UnitConverter.cpp", schema);
	copyTemplate("Template/model/UnitConverter.h", modelPath_ + "/UnitConverter.h", schema);
	copyTemplate("Template/model/UnknownEntityException.h", modelPath_ + "/UnknownEntityException.h", schema);
	copyTemplate("Template/model/Util.h", modelPath_ + "/Util.h", schema);
	// reader
	copyTemplate("Template/reader/IfcStepReader.cpp", readerPath_ + "/IfcStepReader.cpp", schema);
	copyTemplate("Template/reader/IfcStepReader.h", readerPath_ + "/IfcStepReader.h", schema);
	copyTemplate("Template/reader/IfcXmlReader.cpp", readerPath_ + "/IfcXmlReader.cpp", schema);
	copyTemplate("Template/reader/IfcXmlReader.h", readerPath_ + "/IfcXmlReader.h", schema);
	copyTemplate("Template/reader/Reader.cpp", readerPath_ + "/Reader.cpp", schema);
	copyTemplate("Template/reader/Reader.h", readerPath_ + "/Reader.h", schema);
	copyTemplate("Template/reader/ReaderUtil.cpp", readerPath_ + "/ReaderUtil.cpp", schema);
	copyTemplate("Template/reader/ReaderUtil.h", readerPath_ + "/ReaderUtil.h", schema);
	// writer
	copyTemplate("Template/writer/IfcStepWriter.cpp", writerPath_ + "/IfcStepWriter.cpp", schema);
	copyTemplate("Template/writer/IfcStepWriter.h", writerPath_ + "/IfcStepWriter.h", schema);
	copyTemplate("Template/writer/IfcWriter.h", writerPath_ + "/IfcWriter.h", schema);
	copyTemplate("Template/writer/IfcXmlWriter.cpp", writerPath_ + "/IfcXmlWriter.cpp", schema);
	copyTemplate("Template/writer/IfcXmlWriter.h", writerPath_ + "/IfcXmlWriter.h", schema);
	copyTemplate("Template/writer/WriterUtil.cpp", writerPath_ + "/WriterUtil.cpp", schema);
	copyTemplate("Template/writer/WriterUtil.h", writerPath_ + "/WriterUtil.h", schema);
	// xml
	copyTemplate("Template/xml/XmlTools.cpp", xmlPath_ + "/XmlTools.cpp", schema);
	copyTemplate("Template/xml/XmlTools.h", xmlPath_ + "/XmlTools.h", schema);

	generateCMakeListsFile(schema);

	// Types.h
	createTypesHeaderFile(schema);

	// Entities.h
	createEntitiesHeaderFile(schema);
	createEntitiesMapHeaderFile(schema);

	// EntityBroker.cpp
	createEntityBrokerCPPFile(schema);

	generateEntityEnumsHeaderFile(schema);

	for (int i = 0; i < schema.getTypeCount(); i++) {
		auto &type = schema.getTypeByIndex(i);

		generateTypeHeaderFile(schema, type);
		generateTypeSourceFile(schema, type);
	}

	for (int i = 0; i < schema.getEntityCount(); i++) {
		auto &entity = schema.getEntityByIndex(i);

		generateEntityHeaderFile(schema, entity);
		generateEntitySourceFile(schema, entity);
	}

	//Added 16.01.2019
	generateSchemaHeader(schema);
}

void GeneratorOIP::generateREFACTORED(std::ostream & out, Schema & schema)
{
	rootDirectory_ = outputDirectory_ + "/" + schema.getName();

	std::string schemaDirectory = rootDirectory_ + "/schema";
	std::string earlyBindingDirectory = outputDirectory_ + "/";
	std::string expressDirectory = earlyBindingDirectory + "EXPRESS/";
	sourceDirectory_ = rootDirectory_ + "/src";
	entityPath_ = sourceDirectory_ + "/entity";
	typePath_ = sourceDirectory_ + "/type";
	

	if (!fs::exists(rootDirectory_)) {
		fs::create_directory(rootDirectory_);
	}

	if (!fs::exists(schemaDirectory)) {
		fs::create_directory(schemaDirectory);
	}

	if (!fs::exists(sourceDirectory_)) {
		fs::create_directory(sourceDirectory_);
	}
		

	if (!fs::exists(entityPath_)) {
		fs::create_directory(entityPath_);
	}

	if (!fs::exists(typePath_)) {
		fs::create_directory(typePath_);
	}

	generateCMakeListsFileREFACTORED(schema);

	generateSchemaHeader(schema);

	// Types.h
	createTypesHeaderFileREFACTORED(schema);

	// Entities.h
	createEntitiesHeaderFileREFACTORED(schema);

//#pragma omp parallel for
	for (int i = 0; i < schema.getTypeCount(); i++) {
		auto &type = schema.getTypeByIndex(i);
		generateTypeHeaderFileREFACTORED(schema, type);
	}

//#pragma omp parallel for
	for (int i = 0; i < schema.getEntityCount(); i++) {
		auto &entity = schema.getEntityByIndex(i);
		generateEntityHeaderFileREFACTORED(schema, entity);
	}
}

void GeneratorOIP::createEntitiesMapHeaderFile(Schema &schema) {
	// EntitiesMap.h
	std::stringstream ssFilename;
	ssFilename << sourceDirectory_ << "/OpenInfraPlatform/" << schema.getName() << "/" << schema.getName() << "EntitiesMap.h";
	std::ofstream out(ssFilename.str());

	out << license << std::endl;
	out << std::endl;
	out << "#pragma once" << std::endl;

	out << "#include <map>" << std::endl;
	out << "#include \"OpenInfraPlatform/" << schema.getName() << "/" << schema.getName() << "EntityEnums.h\" " << std::endl;

	out << "namespace OpenInfraPlatform" << std::endl;
	out << "{" << std::endl;
	out << "	namespace " << schema.getName() << std::endl;
	out << "\t"
	    << "{" << std::endl;

	out << "\t"
	    << "\t"
	    << "\t"
	    << "static const std::pair<std::string, " << schema.getName() << "EntityEnum> initializers_" << schema.getName() << "_entity[] = {" << std::endl;

	for (int i = 0; i < schema.getEntityCount(); i++) {
		auto &entity = schema.getEntityByIndex(i);

		out << "\t"
		    << "\t"
		    << "\t"
		    << "std::pair<std::string, " << schema.getName() << "EntityEnum>(\"" << toUpper(entity.getName()) << "\", " << toUpper(entity.getName()) << ")";

		if (i < schema.getEntityCount() - 1) {
			out << ",";
		}

		out << std::endl;
	}

	out << "\t"
	    << "\t"
	    << "};" << std::endl;
	out << "\t"
	    << "}" << std::endl;
	out << "}" << std::endl;
}

void GeneratorOIP::createTypesHeaderFile(Schema &schema) {
	std::stringstream ssFilename;

	ssFilename << sourceDirectory_ << "/OpenInfraPlatform/" << schema.getName() << "/" << schema.getName() << "Types.h";
	std::ofstream out(ssFilename.str());

	out << license;
	out << std::endl;
	out << "#pragma once" << std::endl;

	for (int i = 0; i < schema.getTypeCount(); i++) {
		auto &type = schema.getTypeByIndex(i);

		out << "#include \"OpenInfraPlatform/" + schema.getName() + "/entity/" << type.getName() << ".h\"" << std::endl;
	}
}

void GeneratorOIP::createTypesHeaderFileREFACTORED(Schema & schema)
{
	std::stringstream ssFilename;

	ssFilename << sourceDirectory_ <<  "/" << schema.getName() << "Types.h";
	std::ofstream out(ssFilename.str());

	out << license;
	out << std::endl;
	out << "#pragma once" << std::endl;

	for (int i = 0; i < schema.getTypeCount(); i++) {
		auto &type = schema.getTypeByIndex(i);

		out << "#include \"type/" << type.getName() << ".h\"" << std::endl;
	}
}

void GeneratorOIP::createEntitiesHeaderFile(Schema &schema) {
	std::stringstream ssFilename;
	ssFilename << sourceDirectory_ << "/OpenInfraPlatform/" << schema.getName() << "/" << schema.getName() << "Entities.h";
	std::ofstream out(ssFilename.str());

	out << license << std::endl;
	out << std::endl;
	out << "#pragma once" << std::endl;

	for (int i = 0; i < schema.getEntityCount(); i++) {
		auto &entity = schema.getEntityByIndex(i);

		out << "#include \"OpenInfraPlatform/" + schema.getName() + "/entity/" << entity.getName() << ".h\"" << std::endl;
	}
}

void GeneratorOIP::createEntitiesHeaderFileREFACTORED(Schema &schema) {
	std::stringstream ssFilename;
	ssFilename << sourceDirectory_ <<  "/" << schema.getName() << "Entities.h";
	std::ofstream out(ssFilename.str());

	out << license << std::endl;
	out << std::endl;
	out << "#pragma once" << std::endl;

	for (int i = 0; i < schema.getEntityCount(); i++) {
		auto &entity = schema.getEntityByIndex(i);

		out << "#include \"entity/" << entity.getName() << ".h\"" << std::endl;
	}
}

void GeneratorOIP::generateTypeHeaderFile(Schema &schema, Type &type)
{
	std::stringstream ssHeaderFilename;
	ssHeaderFilename << entityPath_ << "/" << type.getName() << ".h";
	std::cout << ssHeaderFilename.str() << std::endl;
	std::ofstream out(ssHeaderFilename.str());

	indentation = 0;

	writeLicenseAndNotice(out);

	out << "#pragma once" << std::endl;
	out << std::endl;

	// Includes
	for(auto name : { "vector", "map", "memory", "sstream", "string", "visit_struct/visit_struct.hpp" })
		writeInclude(out, name, true);

	writeInclude(out, "OpenInfraPlatform/" + schema.getName() + "/model/Object.h");	

	if(!type.isSimpleType() && !type.isEnumeration() && !type.isList() && !type.isArray() && !type.isSet() && !type.isSelectType()) {
		writeInclude(out, "OpenInfraPlatform/" + schema.getName() + "/entity/" + type.getUnderlyingTypeName() + ".h");
	}
		

	// collect the class from which this object should derive from
	std::vector<std::string> baseClasses;

	if(true) {
		// very stupid and slow select types lookup...
		for(int i = 0; i < schema.getTypeCount(); ++i) {
			Type t = schema.getTypeByIndex(i);

			if(t.isSelectType()) {
				for(int k = 0; k < t.getTypeCount(); ++k) {
					if(t.getType(k) == type.getName()) {
						writeInclude(out, t.getName() + ".h");
						baseClasses.push_back(t.getName());
					}
				}
			}
		}
	}

	linebreak(out);
	writeBeginNamespace(out, schema);

	writeLine(out, "// TYPE " + type.getName() + " = " + type.getUnderlyingTypeName() + ";");

	indent(out);
	write(out, "class " + type.getName());

	if(type.isSimpleType() || type.isArray() || type.isSet() || type.isEnumeration()) {
		baseClasses.push_back(schema.getName() + "Type");
	}

	if(type.isEnumeration()) {
		baseClasses.push_back(schema.getName() + "AbstractEnum");
	}

	if(type.isSelectType()) {
		bool usedInAnotherSelect = false;

		// very stupid and slow select types lookup...
		for(int i = 0; i < schema.getTypeCount(); ++i) {
			Type t = schema.getTypeByIndex(i);

			if(t.isSelectType()) {
				for(int k = 0; k < t.getTypeCount(); ++k) {
					if(t.getType(k) == type.getName()) {
						usedInAnotherSelect = true;
					}
				}
			}
		}

		if(!usedInAnotherSelect) {
			baseClasses.push_back(schema.getName() + "AbstractSelect");
		}
	}

	if(!type.isSimpleType() && !type.isEnumeration() && !type.isList() && !type.isArray() && !type.isSet() && !type.isSelectType()) {
		baseClasses.push_back(type.getUnderlyingTypeName());
	}

	// inherit form base classes
	for(int j = 0; j < baseClasses.size(); j++) {
		if(j == 0) {
			write(out, " : ");
		}

		write(out, "public " + baseClasses[j]);

		if(baseClasses.size() > j + 1) {
			write(out, ", ");
		}
	}

	linebreak(out);

	writeLine(out, "{");

	indent(out, indentation - 1);
	write(out, "public:");
	linebreak(out);	

	if(type.isEnumeration()) {
		out << "\t"
			<< "\t"
			<< "\t"
			<< "enum " << type.getName() << "Enum" << std::endl;
		out << "\t"
			<< "\t"
			<< "\t"
			<< "{" << std::endl;

		for(int i = 0; i < type.getTypeCount(); ++i) {
			out << "\t"
				<< "\t"
				<< "\t"
				<< "\t ENUM_" << type.getTypes()[i]; // add _ENUM to avoid collisions with C++
													 // identifiers, e.g. "NULL"

			if(i != type.getTypeCount() - 1) {
				out << "," << std::endl;
			}
		}
		out << std::endl;
		out << "\t"
			<< "\t"
			<< "\t"
			<< "};" << std::endl;
		out << std::endl;
	}

	// ctor

	out << "\t"
		<< "\t"
		<< "\t" << type.getName() << "();" << std::endl;

	// ctor2

	if(type.isEnumeration()) {
		out << "\t"
			<< "\t"
			<< "\t" << type.getName() << "(" << type.getName() << "Enum"
			<< " value);" << std::endl;
	}
	else if(type.isSimpleType()) {
		out << "\t"
			<< "\t"
			<< "\t" << type.getName() << "(" << convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName()) << " value);" << std::endl;
	}
	else if(type.getType() == eType::Unknown) {
		if(schema.isIntegerType(type.getName())) {
			out << "\t"
				<< "\t"
				<< "\t" << type.getName() << "(" << convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName()) << " value);" << std::endl;
		}
	}
	else if(type.isList()) {
		std::cout << "skip it" << std::endl;
		// skip it!
	}
	else {
		std::cout << "mu" << std::endl;
	}

	// dtor
	out << "\t"
		<< "\t"
		<< "\t"
		<< "virtual ~" << type.getName() << "();" << std::endl;

	// classname
	out << "\t"
		<< "\t"
		<< "\t"
		<< "virtual const char* classname() const { return \"" << type.getName() << "\"; }" << std::endl;

	// getStepParamter
	if(type.isSelectType()) {
		out << "\t"
			<< "\t"
			<< "\t"
			<< "virtual void getStepParameter(std::stringstream& stream, bool "
			"is_select_type = false) const = 0; // abstract class"
			<< std::endl;
	}
	else {
		out << "\t"
			<< "\t"
			<< "\t"
			<< "virtual void getStepParameter(std::stringstream& stream, bool "
			"is_select_type = false) const;"
			<< std::endl;
	}

	// readStepData
	if(type.isSelectType()) {
		out << "\t"
			<< "\t"
			<< "\t"
			<< "static std::shared_ptr<" << type.getName() << "> readStepData(const std::string& arg, const std::map<int,shared_ptr<" << schema.getName() << "Entity> >& map);"
			<< std::endl;
	}
	else {
		out << "\t"
			<< "\t"
			<< "\t"
			<< "static std::shared_ptr<" << type.getName() << "> readStepData(const std::string& arg);" << std::endl;
	}

	// attributes
	if(type.isSimpleType()) {
		out << "\t"
			<< "\t"
			<< "\t" << convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName()) << " m_value;" << std::endl;
	}

	if(type.isList() || type.isArray()) {
		std::string typeName = convertSimpleTypeToCPPType(schema, type.getContainerType());

		if(typeName.empty())
			typeName = convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName());

		if(typeName.empty())
			typeName = type.getName();

		out << "\t"
			<< "\t"
			<< "\t"
			<< "std::vector<" << typeName << "> m_vec;" << std::endl;
	}

	

	if(type.isEnumeration()) {
		out << "\t"
			<< "\t"
			<< "\t" << type.getName() << "Enum"
			<< " m_enum;" << std::endl;
	}

	// operators

	if(type.isSimpleType()) {
		out << "\t"
			<< "\t"
			<< "\t" << "operator " << convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName()) << "() { return m_value; }" << std::endl;
	}

	if(type.isList()) {
		// No operators for lists.
	}

	if(type.isArray()) {
		out << "\t"
			<< "\t"
			<< "\t" << convertSimpleTypeToCPPType(schema, type.getContainerType()) << " operator[](size_t idx) { return m_vec[idx]; }" << std::endl;
	}

	if(type.isEnumeration()) {
		// No operators for enums.
	}

	writeEndClass(out, type);
	writeEndNamespace(out, schema);

	if(type.isSimpleType() || type.isList() || type.isArray() || type.isEnumeration()) {
		out << "\n";
		out << "VISITABLE_STRUCT(OpenInfraPlatform::" << schema.getName() << "::" << type.getName() << ",";

		if(type.isSimpleType()) {
			out << " m_value);" << std::endl;
		}
		else if(type.isList() || type.isArray()) {
			out << " m_vec);" << std::endl;
		}
		else if(type.isEnumeration()) {
			out << " m_enum);" << std::endl;
		}
	}
}

void GeneratorOIP::generateTypeHeaderFileREFACTORED(Schema & schema, Type & type)
{
	std::stringstream ssHeaderFilename;
	ssHeaderFilename << typePath_ << "/" << type.getName() << ".h";
	//std::cout << ssHeaderFilename.str() << std::endl;
	std::ofstream out(ssHeaderFilename.str());

	indentation = 0;

	writeLicenseAndNotice(out);

	boost::mt19937 ran;
	ran.seed(time(NULL)); // one should likely seed in a better way
	boost::uuids::basic_random_generator<boost::mt19937> gen(&ran);
	auto guid = boost::uuids::to_string(gen());
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), type.getName(), guid, "h" }, '_');
	
	writeLine(out, "#pragma once");
	writeLine(out, "#ifndef " + define);
	writeLine(out, "#define " + define);

	linebreak(out);

	writeInclude(out, "EXPRESS.h", true);
	

	if (type.isDerivedType()) {
		writeInclude(out, type.getUnderlyingTypeName() + ".h");
	}	

	std::set<std::string> types, entities;

	if (type.isSelectType()) {
		for (auto select : type.getTypes()) {
			if (schema.hasEntity(select)) {
				entities.insert(select);
			}
			if (schema.hasType(select)) {
				types.insert(select);
			}			
		}

		// Disabled for minimal working example
		for (auto val : types)
			writeInclude(out,  val + ".h");

		// Disabled due to recursive code generation
		//for (auto entity : entities)
		//	writeInclude(out, "../entity/" + entity + ".h");
	}

	linebreak(out);
	writeBeginNamespace(out, schema);
	
	if (type.isSelectType()) {
		// Disabled for minimal working example
		for (auto entity : entities) {
			writeLine(out, "class " + entity + ";");
		}
	}

	if (type.isSimpleType() || type.isDerivedType()) {
		//writeLine(out, "DEFINE_TYPE(" + type.getName() + ","  + type.getUnderlyingTypeName() + ")");
		writeValueTypeFile(type, out);
	}
	else if (type.isEnumeration()) {
		//std::string values;
		//for (auto value : type.getTypes())
		//	values.append("(" + value + ")");
		//
		//writeLine(out, "DEFINE_ENUMTYPE(" + type.getName() + "," + values + ")");
		//writeEnumTypeFile(type.getName(), type.getTypes(), out);
		writeLine(out, "#ifdef NULL");
		writeLine(out, "#undef NULL");
		writeLine(out, "#endif");
		writeEnumTypeFileRefactored(type.getName(), type.getTypes(), out);
		writeLine(out, "#define NULL 0");
	}
	else if (type.isContainerType()) {
		//writeLine(out, "DEFINE_CONTAINERTYPE(" + type.getName() + "," + type.getContainerTypeIdentifier() + ")");
		writeContainerTypeFile(schema, type, out);
	}
	else if (type.isSelectType()) {
		//std::string values;
		//
		//if (type.getTypeCount() >= 20) {
		//	int offset = 0;
		//	auto params = type.getTypes();
		//	int i = 0;
		//	for (; i < type.getTypeCount(); i++) {
		//		if (schema.hasEntity(params[i])) {
		//			values.append("(EXPRESSReference<" + params[i] + ">)");
		//		}
		//		else {
		//			values.append("(" + params[i] + ")");
		//		}
		//		if (i != 0 && i % 19 == 0) {
		//			writeLine(out, "DEFINE_SELECTTYPE(" + type.getName() + std::to_string(offset) + "," + values + ")");
		//			offset++;
		//			values.clear();
		//		}
		//		if (i == type.getTypeCount() - 1) {
		//			writeLine(out, "DEFINE_SELECTTYPE(" + type.getName() + std::to_string(offset) + "," + values + ")");
		//			offset++;
		//			values.clear();
		//		}
		//	}
		//	for (int c = 0; c < offset; c++) {
		//		values.append("(" + type.getName() + std::to_string(c) + ")");
		//	}
		//	writeLine(out, "DEFINE_SELECTTYPE(" + type.getName() + "," + values + ")");
		//}
		//else {
		//	for (auto value : type.getTypes()) {
		//		if (schema.hasEntity(value)) {
		//			values.append("(EXPRESSReference<" + value + ">)");
		//		}
		//		else {
		//			values.append("(" + value + ")");
		//		}
		//	}
		//	writeLine(out, "DEFINE_SELECTTYPE(" + type.getName() + "," + values + ")");
		//}
		writeSelectTypeFileREFACTORED(schema, type, out);
		//writeSelectTypeFileMinimal(schema, type, out);
	}
	else {
		std::cerr << "UNKNOWN TYPE ENCOUNTERED!" << std::endl;
		//Unknown Type!
	}	

	writeEndNamespace(out, schema);
	writeLine(out, "#endif // end define " + define);
	out.close();
}

void GeneratorOIP::generateTypeSourceFile(Schema &schema, Type &type) {
	std::string name = type.getName();

	std::stringstream ssFilename;
	ssFilename << entityPath_ << "/" << name << ".cpp";
	std::ofstream out(ssFilename.str());

	indentation = 0;
	writeLicenseAndNotice(out);

	writeInclude(out, type.getName() + ".h");

	writeInclude(out, "OpenInfraPlatform/" + schema.getName() + "/reader/ReaderUtil.h");
	writeInclude(out, "OpenInfraPlatform/" + schema.getName() + "/writer/WriterUtil.h");

	writeBeginNamespace(out, schema);

	// ctor
	out << "\t"
	    << "\t" << type.getName() << "::" << type.getName() << "() {}" << std::endl;

	// ctor2
	if (type.isEnumeration()) {
		out << "\t"
		    << "\t" << type.getName() << "::" << type.getName() << "(" << type.getName() << "::" << type.getName() << "Enum"
		    << " value) { m_enum = value; }" << std::endl;
	} else if (type.isList()) {
		// skip it
	} else if (type.isSimpleType()) {
		out << "\t"
		    << "\t" << type.getName() << "::" << type.getName() << "(" << convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName()) << " value) { m_value = value; }"
		    << std::endl;
	} else if (type.getType() == eType::Unknown) {
		if (schema.isIntegerType(type.getName())) {
			out << "\t"
			    << "\t" << type.getName() << "::" << type.getName() << "(" << convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName()) << " value) { m_value = value; }"
			    << std::endl;
		}
	} else {
	}

	// dtor
	out << "\t"
	    << "\t" << type.getName() << "::~" << type.getName() << "() {}" << std::endl;

	// getStepParameter
	generateTypeSourceFileGetStepParameter(type, out, schema);

	// readStepData
	if (type.isSelectType()) {
		out << "\t"
		    << "\t"
		    << "std::shared_ptr<" << type.getName() << "> " << type.getName() << "::readStepData(const std::string& arg, const std::map<int,shared_ptr<" << schema.getName()
		    << "Entity> >& map)" << std::endl;
		out << "\t"
		    << "\t"
		    << "{" << std::endl;

		out << "\t"
		    << "\t"
		    << "\t"
		    << "// Read SELECT TYPE" << std::endl;

		out << "\t"
		    << "\t"
		    << "\t"
		    << "if( arg.size() == 0 ) { return std::shared_ptr<" << type.getName() << ">(); }" << std::endl;

		out << "\t"
		    << "\t"
		    << "\t"
		    << "if( arg[0] == '#' )" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "int id=atoi( arg.substr(1,arg.length()-1).c_str() );" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "std::map<int,shared_ptr<" << schema.getName() << "Entity> >::const_iterator it_entity = map.find( id );" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "if( it_entity != map.end() )" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t\t\t\t\t"
		    << "shared_ptr<" << type.getName() << "> type_object = dynamic_pointer_cast<" << type.getName() << ">(it_entity->second);" << std::endl;
		out << "\t\t\t\t\t"
		    << "return type_object;" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "}" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "else" << std::endl;
		out << "\t\t\t\t"
		    << "{" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "std::stringstream strs;" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "strs << \"Object width id \" << id << \" not found\";" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "throw " << schema.getName() << "Exception( strs.str() );" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "}" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "}" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "else if( arg.compare(\"$\")==0 )" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t\t"
		    << "\t\t"
		    << "return shared_ptr<" << type.getName() << ">();" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "}" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "else if( arg.compare(\"*\")==0 )" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t\t"
		    << "\t\t"
		    << "return shared_ptr<" << type.getName() << ">();" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "}" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "else" << std::endl;
		out << "\t\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t\t"
		    << "\t\t"
		    << "// inline arguments" << std::endl;

		out << "\t\t"
		    << "\t\t"
		    << "std::string keyword;" << std::endl;
		out << "\t\t"
		    << "\t\t"
		    << "std::string inline_arg;" << std::endl;
		out << "\t\t"
		    << "\t\t"
		    << "tokenizeInlineArgument( arg, keyword, inline_arg );" << std::endl;
		out << "\t\t"
		    << "\t\t"
		    << "std::stringstream strs;" << std::endl;
		out << "\t\t"
		    << "\t\t"
		    << "strs << \"unhandled inline argument: \" << arg << \" in function " << schema.getName() << "::" << type.getName() << "::readStepData\" << std::endl;" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "throw " << schema.getName() << "Exception( strs.str() );" << std::endl;

		out << "\t\t"
		    << "\t"
		    << "}" << std::endl;

		out << "\t"
		    << "\t\t"
		    << "return shared_ptr<" << type.getName() << ">();" << std::endl;

		out << "\t"
		    << "\t"
		    << "}" << std::endl;
	} else if (type.isEnumeration()) {
		out << "\t"
		    << "\t"
		    << "\t"
		    << "std::shared_ptr<" << type.getName() << "> " << type.getName() << "::readStepData(const std::string& arg)" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "if( arg.compare( \"$\" ) == 0 ) { return std::shared_ptr<" << type.getName() << ">(); }" << std::endl;

		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "std::shared_ptr<" << type.getName() << "> type_object(new " << type.getName() << "() );" << std::endl;

		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "if ( _stricmp( arg.c_str(), \"." << type.getTypes()[0] << ".\") == 0)" << std::endl;

		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "type_object->m_enum = " << type.getName() << "::" << type.getName() << "Enum::ENUM_" << type.getTypes()[0] << ";" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "}" << std::endl;

		for (int i = 1; i < type.getTypes().size(); i++) {
			out << "\t"
			    << "\t"
			    << "\t"
			    << "\t"
			    << "else if ( _stricmp( arg.c_str(), \"." << type.getTypes()[i] << ".\") == 0)" << std::endl;
			out << "\t"
			    << "\t"
			    << "\t"
			    << "\t"
			    << "{" << std::endl;
			out << "\t"
			    << "\t"
			    << "\t"
			    << "\t"
			    << "\t"
			    << "type_object->m_enum = " << type.getName() << "::" << type.getName() << "Enum::ENUM_" << type.getTypes()[i] << ";" << std::endl;
			out << "\t"
			    << "\t"
			    << "\t"
			    << "\t"
			    << "}" << std::endl;
		}

		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "return type_object;" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "}" << std::endl;
	} else {
		out << "\t"
		    << "\t"
		    << "std::shared_ptr<" << type.getName() << "> " << type.getName() << "::readStepData(const std::string& arg)" << std::endl;
		out << "\t"
		    << "\t"
		    << "{" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "if( arg.compare( \"$\" ) == 0 ) { return std::shared_ptr<" << type.getName() << ">(); }" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "else if( arg.compare( \"*\" ) == 0 ) { return std::shared_ptr<" << type.getName() << ">(); }" << std::endl;
		out << "\t"
		    << "\t"
		    << "\t"
		    << "std::shared_ptr<" << type.getName() << "> type_object(new " << type.getName() << "() );" << std::endl;

		if (type.isList()) {
			if (type.getContainerType() == "IfcPositiveInteger") {
				out << "\t"
				    << "\t"
				    << "\t"
				    << "    readIntList(  arg, type_object->m_vec );" << std::endl;
			}
		} else if (type.isSimpleType()) {
			if (type.getType() == eType::Real) {
				out << "\t"
				    << "\t"
				    << "\t"
				    << "\t"
				    << "type_object->m_value = atof(arg.c_str());" << std::endl;
			} else if (type.getType() == eType::Boolean) {
				out << "\t\t\t\t"
				    << "if (_stricmp(arg.c_str(), \".F.\") == 0)" << std::endl;
				out << "\t\t\t\t"
				    << "{" << std::endl;
				out << "\t\t\t\t"
				    << "	type_object->m_value = false;" << std::endl;
				out << "\t\t\t\t"
				    << "}" << std::endl;
				out << "\t\t\t\t"
				    << "else if (_stricmp(arg.c_str(), \".T.\") == 0)" << std::endl;
				out << "\t\t\t\t"
				    << "{" << std::endl;
				out << "\t\t\t\t"
				    << "	type_object->m_value = true;" << std::endl;
				out << "\t\t\t\t"
				    << "}" << std::endl;
			} else if (type.getType() == eType::Binary) {
				// ignore it...
			} else if (type.getType() == eType::Integer || type.getType() == eType::Number) {
				out << "\t\t\t"
				    << "type_object->m_value = atoi(arg.c_str());" << std::endl;
			} else if (type.getType() == eType::String) {
				out << "\t\t\t"
				    << "type_object->m_value = arg;" << std::endl;
			}

		} else if (type.isArray()) {
			out << "\t"
			    << "\t"
			    << "\t"
			    << "\t"
			    << "readDoubleList( arg, type_object->m_vec );" << std::endl;
		} else {
			if (schema.isRealType(type.getName())) {
				out << "\t"
				    << "\t"
				    << "\t"
				    << "type_object->m_value = atof(arg.c_str());" << std::endl;
			}
		}
		out << "\t"
		    << "\t"
		    << "\t"
		    << "return type_object;" << std::endl;
		out << "\t"
		    << "\t"
		    << "}" << std::endl;
	}

	writeEndNamespace(out, schema);
}

bool isSimpleType(std::string name) {
	if (name == "REAL")
		return true;
	if (name == "BINARY")
		return true;
	if (name == "BOOLEAN")
		return true;
	if (name == "INTEGER")
		return true;
	if (name == "STRING")
		return true;
	if (name == "LOGICAL")
		return true;
	if (name == "NUMBER")
		return true;

	return false;
}

void OpenInfraPlatform::ExpressBinding::GeneratorOIP::generateTypeSourceFileGetStepParameter(const Type &type, std::ofstream &out, Schema &schema) {
	if (type.isSelectType()) {
		return;
	}

	out << "\t\t"
	    << "void " << type.getName()
	    << "::getStepParameter(std::stringstream&"
	       " stream, bool is_select_type) const"
	    << std::endl;

	if (type.isEnumeration()) {
		out << "\t\t\t"
		    << "{" << std::endl;

		out << "\t\t\t\t"
		    << "if ( m_enum == " << type.getName() << "Enum::ENUM_" << type.getTypes()[0] << ")" << std::endl;

		out << "\t\t\t\t"
		    << "{" << std::endl;
		out << "\t\t\t\t\t"
		    << "stream << \"." << type.getTypes()[0] << ".\";" << std::endl;
		out << "\t\t\t"
		    << "\t"
		    << "}" << std::endl;

		for (int i = 1; i < type.getTypes().size(); i++) {
			out << "\t\t\t\t"
			    << "else if ( m_enum == " << type.getName() << "Enum::ENUM_" << type.getTypes()[i] << ")" << std::endl;
			out << "\t\t\t\t"
			    << "{" << std::endl;
			out << "\t\t\t\t\t"
			    << "stream << \"." << type.getTypes()[i] << ".\";" << std::endl;
			out << "\t\t\t\t"
			    << "}" << std::endl;
		}

		out << "\t\t\t\t"
		    << "if (is_select_type) { stream << \")\"; }" << std::endl;
		out << "\t\t\t"
		    << "}" << std::endl;

		return;
	}

	out << "\t\t"
	    << "{" << std::endl;
	out << "\t\t\t"
	    << "if (is_select_type) { stream << \"" << toUpper(type.getName()) << "(\"; }" << std::endl;

	if (type.isList()) {
		if (type.getContainerType() == "IfcPositiveInteger") {
			out << "\t"
			    << "\t"
			    << "\t"
			    << "writeIntList( stream, m_vec );" << std::endl;
		}
	}

	if (!type.isSimpleType() && !type.isList() && !type.isEnumeration() && !type.isArray() && !type.isSet() && !type.isSelectType()) {
		Type currentType = schema.getTypeByName(type.getUnderlyingTypeName());

		while (!currentType.isSimpleType()) {
			currentType = schema.getTypeByName(currentType.getUnderlyingTypeName());
		}

		if (currentType.getUnderlyingTypeName() == "STRING") {
			out << "\t"
			    << "\t"
			    << "stream << \"'\" << encodeStepString( m_value ) << "
			       "\"'\";"
			    << std::endl;
		}
	}

	if (type.getType() == eType::Unknown) {
		// must be derived form some simple type
		std::string underlyingType = type.getUnderlyingTypeName();

		while (!isSimpleType(underlyingType)) {
			const Type &ut = schema.getTypeByName(underlyingType);
			underlyingType = ut.getUnderlyingTypeName();
		}

		if (underlyingType == "REAL") {
			out << "\t\t\t"
			    << "stream << m_value;" << std::endl;
		} else if (underlyingType == "STRING") {
			out << "\t\t\t"
			    << "stream << \"'\" << encodeStepString( m_value ) << \"'\";" << std::endl;
		} else if (underlyingType == "INTEGER") {
			out << "\t\t\t"
			    << "stream << m_value;" << std::endl;
		} else {
			std::cout << "mu" << std::endl;
		}
	}

	if (type.isSimpleType()) {
		if (type.getType() == eType::Integer) {
			out << "\t"
			    << "\t"
			    << "\t"
			    << "  stream << m_value;" << std::endl;
		} else if (type.getType() == eType::Boolean) {
			out << "\t\t\t"
			    << "if (m_value == false)" << std::endl;
			out << "\t\t\t"
			    << "{" << std::endl;
			out << "\t\t\t"
			    << "	stream << \".F.\";" << std::endl;
			out << "\t\t\t"
			    << "}" << std::endl;
			out << "\t\t\t"
			    << "else if (m_value == true)" << std::endl;
			out << "\t\t\t"
			    << "{" << std::endl;
			out << "\t\t\t"
			    << "	stream << \".T.\";" << std::endl;
			out << "\t\t\t"
			    << "}" << std::endl;
		} else if (type.getType() == eType::String) {
			out << "\t\t\t"
			    << "stream << \"'\" << encodeStepString( m_value ) << \"'\";" << std::endl;
		} else if (type.getType() == eType::Real) {
			out << "\t\t\t"
			    << "stream << m_value;" << std::endl;
		} else {
			std::cout << "muh" << std::endl;
		}
	}

	if (type.isArray()) {
		if (type.getContainerType() == "REAL") {
			out << "\t\t\t  "
			    << "writeDoubleList( stream, m_vec );" << std::endl;
		}
	}

	out << "\t\t\t"
	    << "if (is_select_type) { stream << \")\"; }" << std::endl;
	out << "\t\t"
	    << "}" << std::endl;
}

std::string GeneratorOIP::convertSimpleTypeToCPPType(Schema &schema, std::string simpleType) const {
	std::map<std::string, std::string> simpleTypeMapping;
	simpleTypeMapping.insert(std::make_pair("INTEGER", "int"));
	simpleTypeMapping.insert(std::make_pair("REAL", "double"));
	simpleTypeMapping.insert(std::make_pair("NUMBER", "int"));
	simpleTypeMapping.insert(std::make_pair("STRING", "std::string"));
	simpleTypeMapping.insert(std::make_pair("BOOLEAN", "bool"));
	simpleTypeMapping.insert(std::make_pair("LOGICAL", "bool"));
	simpleTypeMapping.insert(std::make_pair("BINARY", "const char*"));
	// simpleTypeMapping.insert(std::make_pair("IfcPositiveInteger", "int"));

	if (!simpleTypeMapping.count(simpleType)) {
		std::cout << simpleType << std::endl;

		Type underlyingType = schema.getTypeByName(simpleType);
		while (!underlyingType.isSimpleType()) {
			underlyingType = schema.getUnderlyingType(underlyingType.getName());
		}

		return convertSimpleTypeToCPPType(schema, underlyingType.getUnderlyingTypeName());
	}

	assert(simpleTypeMapping.count(simpleType));

	return simpleTypeMapping[simpleType];
}

void GeneratorOIP::includeFile(const std::string &filename, std::ofstream &file) {
	std::ifstream in(filename);
	std::string line;
	while (std::getline(in, line)) {
		file << line << std::endl;
	}
}

void GeneratorOIP::generateCMakeListsFile(const Schema &schema) {
	std::string name = "CMakeLists.txt";

	std::stringstream ssFilename;
	ssFilename << rootDirectory_ << "/" << name;
	std::ofstream file(ssFilename.str());

	file << license_cmake << std::endl;
	file << std::endl;
	file << notice_cmake << std::endl;
	file << std::endl;

	// file << "cmake_minimum_required(VERSION 3.5)" << std::endl;

	file << "project(OpenInfraPlatform." << schema.getName() << ")" << std::endl;
	file << "" << std::endl;
	file << "set(CMAKE_DEBUG_POSTFIX \"d\")" << std::endl << std::endl;

	file << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../Debug)" << std::endl;
	file << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../Release)" << std::endl;
	file << "set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../Debug)" << std::endl;
	file << "set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../Release)" << std::endl;

	// file << "find_package(Boost 1.61.0 REQUIRED)" << std::endl;

	// file << "# Compiler settings" << std::endl;
	// file << "if (WIN32)" << std::endl;
	// file << "# Standard: / DWIN32 / D_WINDOWS / W3 / Zm1000 / EHsc / GR"
	//     << std::endl;
	// file << "	set(CMAKE_CXX_FLAGS \"/DWIN32 /D_WINDOWS /W4 /Zi /EHsc /GR /MP "
	//        "/openmp /bigobj\")"
	//     << std::endl;
	// file << "	endif(WIN32)" << std::endl;
	file << "" << std::endl;
	file << "add_definitions(-D_VARIADIC_MAX=128)" << std::endl;
	file << "set(CMAKE_CXX_STANDARD 14)" << std::endl;
	file << "" << std::endl;
	file << "include_directories(" << std::endl;
	file << "  src/OpenInfraPlatform/" << schema.getName() << std::endl;
	file << "  src" << std::endl;
	file << "  ${Boost_INCLUDE_DIR}" << std::endl;
	file << ")" << std::endl;
	file << "" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_Source              "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_guid_Source         "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/guid/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_entity_Source         "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/entity/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_include_Source "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/entity/include/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_model_Source        "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/model/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_reader_Source       "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/reader/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_writer_Source       "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/writer/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
	     << "_xml_Source          "
	        "src/OpenInfraPlatform/"
	     << schema.getName() << "/xml/*.*)" << std::endl;
	file << "" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "                FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "\\\\guid            FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_guid_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "\\\\entity          FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_entity_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "\\\\entity\\\\include FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_include_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "\\\\model           FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_model_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "\\\\reader          FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_reader_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "\\\\writer          FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_writer_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
	     << "\\\\xml             FILES "
	        "${OpenInfraPlatform_"
	     << schema.getName() << "_xml_Source})" << std::endl;
	file << "" << std::endl;
	file << "add_library(OpenInfraPlatform." << schema.getName() << " STATIC" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_Source}" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_guid_Source}" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_entity_Source}" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_include_Source}" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_model_Source}" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_reader_Source}" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_writer_Source}" << std::endl;
	file << "\t"
	     << "${OpenInfraPlatform_" << schema.getName() << "_xml_Source}" << std::endl;
	file << ")" << std::endl;
	file << "" << std::endl;
	file << "if (WIN32)" << std::endl;
	file << "\t"
	     << "target_link_libraries(OpenInfraPlatform." << schema.getName() << std::endl;
	file << "\t"
	     << "Rpcrt4.lib)" << std::endl;
	file << "endif (WIN32)" << std::endl;
	
	//Provide install instructions
	file << std::endl;
	file << "Install(DIRECTORY ${PROJECT_SOURCE_DIR}/build/${MSVC_VERSION_STRING}/Debug DESTINATION lib/${MSVC_VERSION_STRING}/x64" << std::endl;
	file << "\t" << "COMPONENT " << schema.getName() << std::endl;
	file << "\t" << "FILES_MATCHING PATTERN \"*.lib\" PATTERN \"*.pdb\"" << std::endl;
	file << ")" << std::endl;
	file << std::endl;

	file << std::endl;
	file << "Install(DIRECTORY ${PROJECT_SOURCE_DIR}/build/${MSVC_VERSION_STRING}/Release DESTINATION lib/${MSVC_VERSION_STRING}/x64" << std::endl;
	file << "\t" << "COMPONENT " << schema.getName() << std::endl;
	file << "\t" << "FILES_MATCHING PATTERN \"*.lib\"" << std::endl;
	file << ")" << std::endl;
	file << std::endl;

	file << "Install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include" << std::endl;
	file << "\t" << "COMPONENT " << schema.getName() << std::endl;
	file << "\t" << "FILES_MATCHING PATTERN \"*.h\"" << std::endl;
	file << ")" << std::endl;
}

void GeneratorOIP::generateCMakeListsFileREFACTORED(const Schema & schema)
{
	std::string name = "CMakeLists.txt";

	std::stringstream ssFilename;
	ssFilename << rootDirectory_ << "/" << name;
	std::ofstream file(ssFilename.str());

	file << license_cmake << std::endl;
	file << std::endl;
	file << notice_cmake << std::endl;
	file << std::endl;

	// file << "cmake_minimum_required(VERSION 3.5)" << std::endl;

	file << "project(OpenInfraPlatform." << schema.getName() << " CXX)" << std::endl;
	file << "" << std::endl;
	file << "set(CMAKE_DEBUG_POSTFIX \"d\")" << std::endl << std::endl;	
	file << "" << std::endl;
	file << "include_directories(" << std::endl;
	file << "  src" << std::endl;
	file << "  ${Boost_INCLUDE_DIR}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_Source              "
		"src/*.*)" << std::endl;	
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_entity_Source         "
		"src/entity/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_type_Source         "
		"src/type/*.*)" << std::endl;	

	file << "" << std::endl;

	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "                FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_Source})" << std::endl;	
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "\\\\entity          FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_entity_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "\\\\type          FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_type_Source})" << std::endl;
	
	file << "" << std::endl;

	file << "add_library(OpenInfraPlatform." << schema.getName() << " STATIC" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_Source}" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_entity_Source}" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_type_Source}" << std::endl;	
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "target_include_directories(OpenInfraPlatform." + schema.getName() + " INTERFACE src)" << std::endl;
	file << "set_target_properties(OpenInfraPlatform." + schema.getName() + " PROPERTIES LINKER_LANGUAGE CXX)" << std::endl;

	file << "" << std::endl;

	file << "Install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include" << std::endl;
	file << "\t" << "COMPONENT " << schema.getName() << std::endl;
	file << "\t" << "FILES_MATCHING PATTERN \"*.h\"" << std::endl;
	file << ")" << std::endl;

	file.close();

	
	/*
	file.open(outputDirectory_ + "/" + name);

	file << license_cmake << std::endl;
	file << std::endl;
	file << notice_cmake << std::endl;
	file << std::endl;

	// file << "cmake_minimum_required(VERSION 3.5)" << std::endl;

	file << "project(OpenInfraPlatform.EarlyBinding CXX)" << std::endl;
	file << "" << std::endl;
	file << "include_directories(" << std::endl;
	//file << "  EXPRESS" << std::endl;
	file << "  ${CMAKE_SOURCE_DIR}/ExpressBinding/src/OpenInfraPlatform/ExpressBinding/EXPRESS" << std::endl;
	file << "  ${Boost_INCLUDE_DIR}" << std::endl;
	file << "  ${visit_struct_INCLUDE_DIR}" << std::endl;
	file << ")" << std::endl;

	file << "add_subdirectory(" << schema.getName() << ")" << std::endl;

	file << "" << std::endl;

	file << "get_target_property(" << schema.getName() << "_INCLUDE_DIRS OpenInfraPlatform." << schema.getName() << " INTERFACE_INCLUDE_DIRECTORIES)" << std::endl;
	file << "add_library(OpenInfraPlatform.EarlyBinding INTERFACE)" << std::endl;
	//file << "target_link_libraries(OpenInfraPlatform.EarlyBinding OpenInfraPlatform." << schema.getName() << ")" << std::endl;

	file << "target_include_directories(OpenInfraPlatform.EarlyBinding" << std::endl;;
	//file << "\t INTERFACE EXPRESS" << std::endl;;
	file << "\t INTERFACE ${visit_struct_INCLUDE_DIR}" << std::endl;;
	file << "\t INTERFACE ${Boost_INCLUDE_DIR}" << std::endl;;
	file << "\t INTERFACE ${" << schema.getName() << "_INCLUDE_DIRS}" << std::endl;;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "Install(DIRECTORY ${PROJECT_SOURCE_DIR} DESTINATION include" << std::endl;
	file << "\t" << "COMPONENT EarlyBinding" << std::endl;
	file << "\t" << "FILES_MATCHING PATTERN \"*.h\"" << std::endl;
	file << ")" << std::endl;
	file.close();
	*/
}

void GeneratorOIP::createEntityBrokerCPPFile(Schema &schema) {
	std::stringstream ssFilename;
	ssFilename << sourceDirectory_ << "/OpenInfraPlatform/" << schema.getName() << "/" << schema.getName() << "EntityBroker.cpp";
	std::ofstream out(ssFilename.str());

	out << license << std::endl;
	out << std::endl;

	out << "#include <vector>" << std::endl;
	out << "#include <map>" << std::endl;
	out << "#include <string>" << std::endl;
	out << "#include \"" << schema.getName() << "Entities.h\"" << std::endl;
	out << "#include \"OpenInfraPlatform/" << schema.getName() << "/" << schema.getName() << "EntityEnums.h\" " << std::endl;
	out << "#include \"OpenInfraPlatform/" << schema.getName() << "/model/Exception.h\" " << std::endl;
	out << "#include \"OpenInfraPlatform/" << schema.getName() << "/model/Object.h\" " << std::endl;

	out << std::endl;

	out << "namespace OpenInfraPlatform" << std::endl;
	out << "{" << std::endl;
	out << "	namespace " << schema.getName() << std::endl;
	out << "\t"
	    << "{" << std::endl;

	out << "\t"
	    << "\t" << schema.getName() << "Entity* create" << schema.getName() << "Entity( const " << schema.getName()
	    << "EntityEnum entity_enum "
	       ")"
	    << std::endl;

	out << "\t"
	    << "\t"
	    << "{" << std::endl;
	out << "\t"
	    << "\t"
	    << "\t"
	    << "switch( entity_enum )" << std::endl;
	out << "\t"
	    << "\t"
	    << "\t"
	    << "{" << std::endl;

	for (int i = 0; i < schema.getEntityCount(); i++) {
		auto &entity = schema.getEntityByIndex(i);

		out << "\t"
		    << "\t"
		    << "\t"
		    << "\t"
		    << "case " << toUpper(entity.getName()) << ": return new " << entity.getName() << "();" << std::endl;
	}

	out << "\t"
	    << "\t"
	    << "\t"
	    << "\t"
	    << "default: throw " << schema.getName() << "Exception(\"given " << schema.getName() << "EntityEnum not valid\"); " << std::endl;
	out << "\t"
	    << "\t"
	    << "\t"
	    << "}" << std::endl;
	out << "\t"
	    << "\t"
	    << "\t"
	    << "return 0;" << std::endl;

	out << "\t"
	    << "\t"
	    << "}" << std::endl;
	out << "\t"
	    << "}" << std::endl;
	out << "}" << std::endl;
}

void GeneratorOIP::generateEntityHeaderFile(OpenInfraPlatform::ExpressBinding::Schema &schema, Entity &entity) {
	std::stringstream ssHeaderFilename;
	ssHeaderFilename << entityPath_ << "/" << entity.getName() << ".h";
	std::cout << ssHeaderFilename.str() << std::endl;
	std::ofstream out(ssHeaderFilename.str());

	indentation = 0;

	writeLicenseAndNotice(out);

	writeLine(out, "#pragma once");
	linebreak(out);

	// Includes
	for(auto name : { "vector", "map", "memory", "sstream", "string", "visit_struct/visit_struct.hpp" })
		writeInclude(out, name, true);

	writeInclude(out, "OpenInfraPlatform/" + schema.getName() + "/model/Object.h");

	// very stupid and slow select types lookup...
	for (int i = 0; i < schema.getTypeCount(); ++i) {
		Type t = schema.getTypeByIndex(i);

		if (t.isSelectType()) {
			for (int k = 0; k < t.getTypeCount(); ++k) {
				if (t.getType(k) == entity.getName()) {
					writeInclude(out, t.getName() + ".h");
				}
			}
		}
	}

	if (entity.hasSupertype()) {
		writeInclude(out, entity.getSupertype() + ".h");
	}

	std::set<std::string> includeTypes = std::set<std::string>();
	std::set<std::string> forwardDeclarations = std::set<std::string>();

	for(int i = 0; i < entity.getAttributeCount(); i++) {
		auto type = entity.getAttribute(i).type;

		// Get type from container until we end up with a TypeNamed or Simple.
		while(type->getType() == eEntityAttributeParameterType::eGeneralizedType) {
			type = std::dynamic_pointer_cast<EntityAttributeGeneralizedType>(type)->elementType;
		}
				
		if(type->getType() == eEntityAttributeParameterType::TypeNamed) {
			auto name = type->toString();

			// Check if the attribute is a TYPE
			if(schema.hasType(name)) {
				name = schema.getTypeByName(name).getName();

				// If the TYPE is REAL or INTEGER type, we add it as include since we need to have knowledge of it. Otherwíse forward declare it.
				if(schema.isIntegerType(name) || schema.isRealType(name) || schema.getTypeByName(name).isEnumeration())
					includeTypes.insert(name);
				else
					forwardDeclarations.insert(name);
			}
			// If it is a ENTITY, we add the class to forward declarations.
			else if(schema.hasEntity(name)) {				
				forwardDeclarations.insert(schema.getEntityByName(name).getName());				
			}
		}
	}

	// Write the includes for Types which are used as members.
	for(auto incl : includeTypes)
		writeInclude(out, incl + ".h");

	linebreak(out);
	writeBeginNamespace(out, schema);
	
	// Write forward declarations.
	for(auto decl : forwardDeclarations)
		writeLine(out, "class " + decl + ";");

	writeLine(out, "// ENTITY " + entity.getName());

	indent(out, indentation);
	write(out, "class " + entity.getName());
	
	if (entity.hasSupertype()) {
		write(out, " : public " + entity.getSupertype());
	} else {
		write(out, " : public " + schema.getName() + "Entity");
	}

	// very stupid and slow select types lookup...
	for (int i = 0; i < schema.getTypeCount(); ++i) {
		Type t = schema.getTypeByIndex(i);

		if (t.isSelectType()) {
			for (int k = 0; k < t.getTypeCount(); ++k) {
				if (t.getType(k) == entity.getName()) {
					write(out, ", public " + t.getName());
				}
			}
		}
	}

	linebreak(out);
	linebreak(out);

	writeLine(out, "{");

	indent(out, indentation - 1);
	write(out, "public:");
	linebreak(out);
	

	// ctors
	writeLine(out, entity.getName() + "();");
	writeLine(out, entity.getName() + "(int id);");

	// dtor
	writeLine(out, "~" + entity.getName() + "();");
	
	linebreak(out);

	writeLine(out, "// method setEntity takes over all attributes from another instance of the class");	
	writeLine(out, "virtual void setEntity(std::shared_ptr<" + schema.getName() + "Entity> other);");
	writeLine(out, "virtual void getStepLine(std::stringstream& stream) const;");
	writeLine(out, "virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;");
	writeLine(out, "virtual void readStepData(std::vector<std::string>& args, const std::map<int, shared_ptr<" + schema.getName() + "Entity> >& map);");
	writeLine(out, "virtual void setInverseCounterparts(shared_ptr<" + schema.getName() + "Entity> ptr_self);");
	writeLine(out, "virtual void unlinkSelf();");
	writeLine(out, "virtual const char* classname() const { return \"" + entity.getName() + "\"; }");
	
	linebreak(out);

	// current class
	writeLine(out, "// " + entity.getName() + " -----------------------");	
	writeLine(out, "// attributes:");

	for (int i = 0; i < entity.getAttributeCount(); i++) {
		const EntityAttribute &att = entity.getAttribute(i);

		if (att.getParameterType() == eEntityAttributeParameterType::TypeNamed) {
			if(schema.hasType(att.type->toString())) {
				std::string name = schema.getTypeByName(att.type->toString()).getName();

				if(schema.isRealType(name) || schema.isIntegerType(name)) {
					writeLine(out, name + " m_" + att.getName() + ";");					
				}
				else {
					writeLine(out, "std::shared_ptr<" + att.type->toString() + "> m_" + att.getName() + ";");
				}				
			}
			else {
				writeLine(out, "std::shared_ptr<" + att.type->toString() + "> m_" + att.getName() + ";");
			}

		} else if (att.getParameterType() == eEntityAttributeParameterType::eGeneralizedType) {
			auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(att.type);

			if (p->containerType == eEntityAttributeContainerType::List) {
				out << "\t"
				    << "\t"
				    << "\t"
				    << "std::vector<";

				auto iterator = p->elementType;

				while (iterator->getType() == eEntityAttributeParameterType::eGeneralizedType) {
					auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
					out << "std::vector<";

					iterator = p->elementType;
				}

				if (iterator->getType() == eEntityAttributeParameterType::TypeNamed) {
					out << "std::shared_ptr<" << iterator->toString() << ">";
				}

				iterator = p->elementType;

				while (iterator->getType() == eEntityAttributeParameterType::eGeneralizedType) {
					auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
					out << ">";

					iterator = p->elementType;
				}

				out << "> "
				    << " m_" << att.getName() << ";" << std::endl;
			} else if (p->containerType == eEntityAttributeContainerType::Set) {
				out << "\t"
				    << "\t"
				    << "\t"
				    << "std::vector<";

				if (p->elementType->getType() == eEntityAttributeParameterType::TypeNamed) {
					out << "std::shared_ptr<" << p->elementType->toString() << ">";
				}

				out << "> "
				    << " m_" << att.getName() << ";" << std::endl;
			} else if (p->containerType == eEntityAttributeContainerType::Array) {
				out << "\t"
				    << "\t"
				    << "\t"
				    << "std::vector<";

				if (p->elementType->getType() == eEntityAttributeParameterType::TypeNamed) {
					out << "std::shared_ptr<" << p->elementType->toString() << ">";
				}

				out << "> "
				    << " m_" << att.getName() << ";" << std::endl;
			} else {
				std::cout << "\t"
				          << "\t"
				          << "\t" << att.type->toString() << " m_" << att.getName() << ";" << std::endl;
				out << "\t"
				    << "\t"
				    << "\t" << att.type->toString() << " m_" << att.getName() << ";" << std::endl;
			}

		} else {
			out << "\t"
			    << "\t"
			    << "\t" << convertSimpleTypeToCPPType(schema, att.type->toString()) << " m_" << att.getName() << ";" << std::endl;
		}
	}

	writeEndClass(out, entity);
	writeEndNamespace(out, schema);
	
	//Make structure visitable
	auto attributes = schema.getAllEntityAttributesNames(entity);
	if(!attributes.empty())
	{
		out << "\n";
		out << "VISITABLE_STRUCT(OpenInfraPlatform::" << schema.getName() << "::" << entity.getName();
		for(auto item : attributes) {
			out << ", m_" << item;
		}
		out << ");" << std::endl;
	}
	
}

void GeneratorOIP::generateEntityHeaderFileREFACTORED(Schema & schema, Entity & entity)
{
	std::stringstream ssHeaderFilename;
	ssHeaderFilename << entityPath_ << "/" << entity.getName() << ".h";
	//std::cout << ssHeaderFilename.str() << std::endl;
	std::ofstream out(ssHeaderFilename.str());

	indentation = 0;

	writeLicenseAndNotice(out);

	boost::mt19937 ran;
	ran.seed(time(NULL)); // one should likely seed in a better way
	boost::uuids::basic_random_generator<boost::mt19937> gen(&ran);
	auto guid = boost::uuids::to_string(gen());
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), entity.getName(), guid, "h" }, '_');

	writeLine(out, "#pragma once");
	writeLine(out, "#ifndef " + define);
	writeLine(out, "#define " + define);
	linebreak(out);

	// Write include for supertype.
	if (entity.hasSupertype())
		writeInclude(out, entity.getSupertype() + ".h");
	
	writeInclude(out, "EXPRESS.h", true);
	writeInclude(out, "visit_struct/visit_struct.hpp", true);
	linebreak(out);


	auto attributes = entity.getAttributes();

	std::set<std::string> typeAttributes, entityAttributes;

	for (auto attr : attributes) {
		if (attr.type->getType() == eEntityAttributeParameterType::TypeNamed) {
			if (schema.hasEntity(attr.type->toString())) {
				entityAttributes.insert(attr.type->toString());
			}
			if (schema.hasType(attr.type->toString())) {
				typeAttributes.insert(attr.type->toString());
			}
		}
		else if (attr.type->getType() == eEntityAttributeParameterType::eGeneralizedType) {
			auto elementType = attr.type;
			int dim = 0;

			while (elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
				dim++;
				elementType = std::static_pointer_cast<EntityAttributeGeneralizedType>(elementType)->elementType;
			}

			if (schema.hasEntity(elementType->toString())) {
				entityAttributes.insert(elementType->toString());
			}
			if (schema.hasType(elementType->toString())) {
				typeAttributes.insert(elementType->toString());
			}
		}
	}

	auto self = entityAttributes.find(entity.getName());
	if (self != entityAttributes.end())
		entityAttributes.erase(self);
		

	for (auto type : typeAttributes)
		writeInclude(out, "../type/" + type + ".h");

	for (auto entityAttribute : entityAttributes)
		writeInclude(out, entityAttribute + ".h");

	std::string supertype = entity.hasSupertype() ? entity.getSupertype() : "ExpressBinding::EXPRESSEntity";
	
	linebreak(out);
	writeBeginNamespace(out, schema);

	writeLine(out, "class " + entity.getName() + " : public " + supertype + " {");
	writeLine(out, "public:");
	
	auto initClassAsDefault = [&out, &entity, &schema]() {
		// Default constructor.
		writeLine(out, entity.getName() + "() = default;");

		// Copy constructor.
		writeLine(out, entity.getName() + "(const " + entity.getName() + "& other) = default;");

		// Destructor.
		writeLine(out, "virtual ~" + entity.getName() + "() {};");

		// Assignment operator.
		writeLine(out, "virtual " + entity.getName() + "& operator=(const " + entity.getName() + "& other) = default;");
		linebreak(out);

		//Classname function
		writeLine(out, "virtual const std::string classname() const override { return \"" + entity.getName() + "\";} ");
		linebreak(out);

		auto attributes = schema.getAllEntityAttributes(entity);

		writeLine(out, "static " + entity.getName() + " readStepData(const std::vector<std::string>& args, const std::shared_ptr<ExpressBinding::EXPRESSModel>& model) {");
		writeLine(out, entity.getName() + " entity;");
		writeLine(out, "entity.setId(stoull(args[0]));");
		for (int i = 0; i < attributes.size(); i++) {
			auto attr = attributes[i];
			writeLine(out, "entity." + attr.getName() + " = decltype(" + attr.getName() + ")::readStepData(args[" + std::to_string(i + 1) + "], model);");
		}
		writeLine(out, "return entity;");
		writeLine(out, "}");
		linebreak(out);

		writeLine(out, "virtual const std::string getStepLine() const override {");
		writeLine(out, "std::string stepLine = this->getStepParameter() + \"=\" + this->classname() + \"(\";");
		for (int i = 0; i < attributes.size() - 1; i++) {
			writeLine(out, "stepLine += " + attributes[i].getName() + ".getStepParameter() + \",\";");
		}
		writeLine(out, "stepLine += " + attributes.back().getName() + ".getStepParameter() + \")\";");
		writeLine(out, "return stepLine;");
		writeLine(out, "}");
	};

	if (!schema.isAbstract(entity)) {
		initClassAsDefault();
	}
	else {
		writeLine(out, "virtual const std::string classname() const = 0;");
		writeLine(out, "virtual const std::string getStepLine() const = 0;");
	}
	linebreak(out);

	//GetAttributes	
	if (!attributes.empty()) {
		for (auto attr : attributes) {
			writeLine(out, attr.toString(schema) + " " + attr.getName() + ";");
		}
		linebreak(out);
	}

	writeLine(out, "};");
	writeEndNamespace(out, schema);

	//Make structure visitable
	auto attributeNames = schema.getAllEntityAttributesNames(entity);
	if (!attributeNames.empty())
	{
		out << "\n";
		out << "VISITABLE_STRUCT(OpenInfraPlatform::" << schema.getName() << "::" << entity.getName();
		for (auto item : attributeNames) {
			out << "," << item;
		}
		out << ");" << std::endl;
	}

	writeLine(out, "#endif // end define " + define);
	out.close();
}

void GeneratorOIP::generateEntityEnumsHeaderFile(Schema &schema) {
	std::stringstream ssHeaderFilename;
	ssHeaderFilename << sourceDirectory_ << "/OpenInfraPlatform/" << schema.getName() << "/" << schema.getName() << "EntityEnums.h";
	std::cout << ssHeaderFilename.str() << std::endl;
	std::ofstream out(ssHeaderFilename.str());

	out << license << std::endl;
	out << std::endl;
	out << notice << std::endl;
	out << std::endl;

	out << "#pragma once" << std::endl;
	out << std::endl;

	writeBeginNamespace(out, schema);	

	out << "\t"
	    << "\t"
	    << "enum " << schema.getName() << "EntityEnum" << std::endl;
	out << "\t"
	    << "\t"
	    << "{" << std::endl;

	for (int i = 0; i < schema.getEntityCount(); i++) {
		out << "\t"
		    << "\t"
		    << "\t" << toUpper(schema.getEntityByIndex(i).getName());
		if (i < schema.getEntityCount() - 1) {
			out << ",";
		}

		out << std::endl;
	}

	out << "\t"
	    << "\t"
	    << "};" << std::endl;

	writeEndNamespace(out, schema);
}

void GeneratorOIP::generateSchemaHeader(Schema & schema)
{
	std::ofstream file(sourceDirectory_ + "/"+ schema.getName().append(".h"));

	writeInclude(file, schema.getName() + "Entities.h");
	writeInclude(file, schema.getName() + "Types.h");
	
	file.close();	
}

void GeneratorOIP::generateEntitySourceFile(Schema &schema, const Entity &entity) {
	std::stringstream ssHeaderFilename;
	ssHeaderFilename << entityPath_ << "/" << entity.getName() << ".cpp";
	std::cout << ssHeaderFilename.str() << std::endl;
	std::ofstream out(ssHeaderFilename.str());

	auto superTypes = schema.getSuperTypes(entity);
	auto attributes = schema.getAllEntityAttributesNames(entity);

	indentation = 0;
	writeLicenseAndNotice(out);
	linebreak(out);

	// Includes
	for(auto header : { "sstream", "limits" })
		writeInclude(out, header, true);
	linebreak(out);

	for(auto header : { "model/Exception.h", "reader/ReaderUtil.h", "writer/WriterUtil.h" })
		writeInclude(out, "OpenInfraPlatform/" + schema.getName() + "/" + header);
	linebreak(out);

	writeInclude(out, "OpenInfraPlatform/" + schema.getName() + "/" + schema.getName() + "EntityEnums.h");
	writeInclude(out, entity.getName() + ".h");

	// Include all types forward declared in header.
	std::set<std::string> includes = std::set<std::string>();

	for(auto att : schema.getAllEntityAttributes(entity)) {
		auto type = att.type;

		// Get type from container until we end up with a TypeNamed or Simple.
		while(type->getType() == eEntityAttributeParameterType::eGeneralizedType) {
			type = std::dynamic_pointer_cast<EntityAttributeGeneralizedType>(type)->elementType;
		}

		if(type->getType() == eEntityAttributeParameterType::TypeNamed) {
			auto name = type->toString();

			//// Check if the attribute is a TYPE
			if(schema.hasType(name)) {
				name = schema.getTypeByName(name).getName();
				// If the TYPE is REAL or INTEGER type, we add it as include since we need to have knowledge of it. Otherwíse forward declare it.
				if(!schema.isIntegerType(name) && !schema.isRealType(name))
					includes.insert(name);
			}
			// If it is a ENTITY, we add the class to forward declarations.
			else if(schema.hasEntity(name)) {
				includes.insert(schema.getEntityByName(name).getName());
			}
		}
	}

	// Write the includes for Types which are used as members.
	for(auto incl : includes)
		writeInclude(out, incl + ".h");

	linebreak(out);

	writeBeginNamespace(out, schema);
	writeLine(out, "// ENTITY " + entity.getName());

	// ctor impl
	writeEntityConstructor(out, entity, "", "m_entity_enum = " + toUpper(entity.getName()) + ";");
	linebreak(out);
	
	writeEntityConstructor(out, entity, "int id", "m_id = id; m_entity_enum = " + toUpper(entity.getName()) + ";");
	linebreak(out);

	// dtor impl
	writeEntityDestructor(out, entity);
	linebreak(out);

	// setEntity	
	writeLine(out, "// method setEntity takes over all attributes from another instance of the class");

	std::string statements = "std::shared_ptr<" + entity.getName() + "> other = std::dynamic_pointer_cast<" + entity.getName() + ">(other_entity);" + "if(!other) { return; }";		
	for(auto att : attributes) {
		statements += "m_" + att + " = other->m_" + att + ";";
	}

	writeEntityFunction(out, entity, "void", "setEntity", "std::shared_ptr<" + schema.getName() + "Entity> other_entity", "", statements);
	linebreak(out);
	statements.clear();
	
	// getStepLine	
	statements += "stream << \"#\" << m_id << \"=" + toUpper(entity.getName()) + "\" << \"(\";";
	
	auto attributeVector = schema.getAllEntityAttributes(entity);
	for (int i = 0; i < attributeVector.size(); i++) {
		const EntityAttribute &att = attributeVector[i];

		if (att.getParameterType() == eEntityAttributeParameterType::eGeneralizedType) {
			auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(att.type);

			std::cout << entity.getName() << "." << att.getName() << std::endl;

			if (p->containerType == eEntityAttributeContainerType::List || p->containerType == eEntityAttributeContainerType::Set
			    || p->containerType == eEntityAttributeContainerType::Array) {
				if (p->elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
					// 2D for example List of List
					auto q = std::static_pointer_cast<EntityAttributeGeneralizedType>(p->elementType);

					if (schema.hasType(q->elementType->toString())) {
						if (schema.isIntegerType(q->elementType->toString())) {							
							statements += "writeTypeOfIntList2D( stream, m_" + attributeVector[i].getName() + " );";
						} else {							
							statements += "writeTypeOfRealList2D( stream, m_" + attributeVector[i].getName() + " );";
						}

					} else {
						statements += "writeEntityList2D( stream, m_" + attributeVector[i].getName() + " );";
					}
				} else {
					if (schema.hasType(p->elementType->toString())) {
						// is type a Real Type?
						if (schema.isRealType(p->elementType->toString())) {
							statements += "writeTypeOfRealList( stream, m_" + attributeVector[i].getName() + " );";
						} else {							
							statements += "writeTypeList( stream, m_" + attributeVector[i].getName() + " );";
						}
					} else {					
						statements += "writeEntityList( stream, m_" + attributeVector[i].getName() + " );";
					}
				}
			} 
		}
		else if (att.getParameterType() == eEntityAttributeParameterType::Simple) {			
			statements += "if( m_" + attributeVector[i].getName() + " == m_" + attributeVector[i].getName() + " ) { stream << m_" + attributeVector[i].getName() + "; }" + "else { stream << \"$\"; }";
		}
		else if (att.getParameterType() == eEntityAttributeParameterType::TypeNamed) {
			if(schema.hasType(att.type->toString())) {
				if(schema.isIntegerType(att.type->toString()) || schema.isRealType(att.type->toString())) {
					if (schema.isSelectType(att.type->toString())) {
						statements += "m_" + attributeVector[i].getName() + ".getStepParameter(stream, true);";
					}
					else {
						statements += "m_" + attributeVector[i].getName() + ".getStepParameter(stream);";
					}
				}
				else {
					if (schema.isSelectType(att.type->toString())) {
						statements += "m_" + attributeVector[i].getName() + " ? m_" + attributeVector[i].getName() + "->getStepParameter(stream, true) : stream << \"$\";";
					}
					else {
						statements += "m_" + attributeVector[i].getName() + " ? m_" + attributeVector[i].getName() + "->getStepParameter(stream) : stream << \"$\";";
					}
				}
			}
			else {
				std::string condition = "m_" + attributeVector[i].getName();

				std::string doThen = schema.hasEntity(att.type->toString()) ?
					"stream << \"#\" << m_" + attributeVector[i].getName() + "->getId();" :
					"m_" + attributeVector[i].getName() + "->getStepParameter( stream );";

				std::string doElse = entity.hasQualifiedAttribute(attributeVector[i].getName()) ?
					"stream << \"*\";" :
					"stream << \"$\";";

				statements += createIfElseStatement(condition, doThen, doElse);
			}			
		} else {
			if (entity.hasQualifiedAttribute(attributeVector[i].getName())) {
				statements += createIfElseStatement("m_" + attributeVector[i].getName(), "m_" + attributeVector[i].getName() + "->getStepParameter(stream);", "stream << \"*\";");
			} else {				
				statements += "if( m_" + attributeVector[i].getName() + ") { m_" + attributeVector[i].getName() + "->getStepParameter( stream ); } else { stream << \"$\"; }";
			}
		}

		if (i != attributeVector.size() - 1) {			
			statements += "stream << \",\";";
		}
	}
	
	statements += "stream << \");\";";	
	writeEntityFunction(out, entity, "void", "getStepLine", "std::stringstream& stream", "const", statements);
	linebreak(out);
	statements.clear();

	// getStepParameter	
	writeEntityFunction(out, entity, "void", "getStepParameter", "std::stringstream &stream, bool", "const", "stream << \"#\" << m_id;");
	linebreak(out);

	// readStepData
	statements += "const int num_args = (int)args.size();";
	
	std::string vectorSize = std::to_string(attributeVector.size());
	std::string condition = "num_args < " + vectorSize;
	std::string doThen = "std::stringstream strserr;";
	doThen += "strserr << \"Wrong parameter count for entity " + entity.getName() + ", expecting " + vectorSize + ", having \" << num_args << \". Object id: \" << getId() << std::endl;";
	doThen += "throw " + schema.getName() + "Exception( strserr.str().c_str() );";
	statements += createIfElseStatement(condition, doThen);
	
	statements += "#ifdef _DEBUG\n";
	doThen = "std::cout << \"Wrong parameter count for entity " + entity.getName() + ", expecting " + vectorSize + ", having \" << num_args << \". Object id: \" << getId() << std::endl;";
	statements += createIfElseStatement(condition, doThen);
	statements += "#endif\n";

	for (int i = 0; i < attributeVector.size(); i++) {
		const EntityAttribute &att = attributeVector[i];
		std::string i_str = std::to_string(i);

		if (att.getParameterType() == eEntityAttributeParameterType::TypeNamed) {
			if (schema.hasType(att.type->toString())) {
				if (schema.isIntegerType(att.type->toString()) || schema.isRealType(att.type->toString()))
					statements += "m_" + att.getName() + " = " + att.type->toString() + "::readStepData(args[" + i_str + "]) ? *" + att.type->toString() + "::readStepData(args[" + i_str + "]) : " + att.type->toString() + "();";
				else {
					statements += "m_" + att.getName() + " = " + att.type->toString() + "::readStepData";

					if (schema.isSelectType(att.type->toString())) {
						statements += "(args[" + i_str + "], map );";

					}
					else {
						statements += "(args[" + i_str + "]);";
					}
				}
			} else {
				statements += "readEntityReference(args[" + i_str + "], m_" + att.getName() + ", map);";
			}
		} else if (att.getParameterType() == eEntityAttributeParameterType::eGeneralizedType) {
			auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(att.type);
	
			if (p->containerType == eEntityAttributeContainerType::List 
				|| p->containerType == eEntityAttributeContainerType::Set
			    || p->containerType == eEntityAttributeContainerType::Array) {
				if (schema.hasType(p->elementType->toString())) {
					// is type a Real Type?
					if (schema.isRealType(p->elementType->toString())) {						
						statements += "readTypeOfRealList(args[" + i_str + "], m_" + att.getName() + ");";
					} else {
						if (schema.isSelectType(p->elementType->toString())) {							
							statements += "readSelectList(args[" + i_str + "], m_" + att.getName() + ", map);";
						} else {							
							statements += "readTypeList(args[" + i_str + "], m_" + att.getName() + ");";
						}
					}
				} else {
					auto isGeneralizedType = (p->elementType->getType() == eEntityAttributeParameterType::eGeneralizedType);
					if (isGeneralizedType) {
						auto q = std::static_pointer_cast<EntityAttributeGeneralizedType>(p->elementType);

						auto isEntity = schema.hasEntity(q->elementType->toString());
						auto isType = schema.hasType(q->elementType->toString());
						auto isIntegerType = isType && schema.isIntegerType(schema.getTypeByName(q->elementType->toString()).getName());
						auto isRealType = isType && schema.getTypeByName(q->elementType->toString()).getUnderlyingTypeName() == "REAL";
						
						if(isIntegerType)
							statements += "readTypeOfIntList2D(args[" + i_str + "], m_" + att.getName() + ");";
						else if(isRealType)
							statements += "readTypeOfRealList2D(args[" + i_str + "], m_" + att.getName() + ");";
						else if(isEntity)
							statements += "readEntityReferenceList2D(args[" + i_str + "], m_" + att.getName() + " , map);";
					}
					else {						
						statements += "readEntityReferenceList(args[" + i_str + "], m_" + att.getName() + " , map);";
					}
				}
			}
		}
	}
	
	
	writeEntityFunction(out, entity, "void", "readStepData", "std::vector<std::string>& args, const std::map<int,shared_ptr<" + schema.getName() + "Entity> >& map", "", statements);
	linebreak(out);
	statements.clear();

	// setInverseCounterparts	
	std::string impl = "";
	if(entity.hasSupertype())
		impl = entity.getSupertype() + "::setInverseCounterparts(ptr_self_entity);";
	writeEntityFunction(out, entity, "void", "setInverseCounterparts", "shared_ptr<" + schema.getName() + "Entity> ptr_self_entity", "", impl);
	linebreak(out);

	// unlinkSelf
	impl = "";
	if(entity.hasSupertype())
		impl = entity.getSupertype() + "::unlinkSelf();";
	writeEntityFunction(out, entity, "void", "unlinkSelf", "", "", impl);

	writeEndNamespace(out, schema);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
