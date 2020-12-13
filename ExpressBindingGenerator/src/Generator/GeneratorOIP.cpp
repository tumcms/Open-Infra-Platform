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

#include "General/namespace.h"
//#include <Windows.h>
#include <algorithm>
#include <cassert>
#include <experimental/filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <chrono>

#include "General\graph.h"

//#include <boost/optional.hpp>
//#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

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
#    Copyright(c) 2020 Technical University of Munich\n\
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
Early Binding EXPRESS Generator. Any changes to this file may be lost in the future. */";

std::string notice_cmake =
"\
# This file has been automatically generated using the TUM Open Infra Platform\n\
# Early Binding EXPRESS Generator. Any changes to this file may be lost in the future.";

static size_t indentation = 0;

enum eKeepDelimCharacter {None, Left, Right, Standalone};
std::vector<std::string> split(const std::string& text, const char delim, const eKeepDelimCharacter value)
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

std::string join(const std::vector<std::string>& params, char sep) {
	std::string text;
	for (const auto val : params)
		text += val + sep;
	text.pop_back();
	return text;
}

std::string createIfElseStatement(const std::string& condition, const std::string& doThen, const std::string& doElse = "")
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
void writeBeginNamespace(std::ostream &out, const OpenInfraPlatform::ExpressBindingGenerator::Schema &schema)
{
	writeLine(out, "namespace OpenInfraPlatform");
	writeLine(out, "{");
	writeLine(out, "namespace " + schema.getName());
	writeLine(out, "{");
}

void writeEndNamespace(std::ostream &out, const OpenInfraPlatform::ExpressBindingGenerator::Schema &schema)
{
	writeLine(out, "} // end namespace " + schema.getName());
	writeLine(out, "} // end namespace OpenInfraPlatform");
}

void writeEndClass(std::ostream &out, const OpenInfraPlatform::ExpressBindingGenerator::Type &type)
{
	writeLine(out, "}; // end class " + type.getName());
}

void writeEndClass(std::ostream &out, const OpenInfraPlatform::ExpressBindingGenerator::Entity &entity)
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



/*!
* \brief Starts a doxygen comment.
* \note The function adds a new line at the end.
* \param out Output stream for the text.
*/
void writeDoxyCommentStart(std::ostream &out)
{
	writeLine(out, "/*!");
}
/*!
* \brief Ends a doxygen comment.
* \note The function adds a new line at the end.
* \param out Output stream for the text.
*/
void writeDoxyCommentEnd(std::ostream &out)
{
	writeLine(out, " */");
}
/*!
* \brief Writes a line of comment.
*
* The function prepends \c str with \code " * " \endcode and outputs it to the stream \c out.
* 
* \note The function adds a new line at the end.
* \note One must start and finish the doxy comment with ::writeDoxyCommentStart and ::writeDoxyCommentEnd before and after unsing this function.
*
* \param out Output stream for the text.
* \param str The string to be output.
*/
void writeDoxyLine(std::ostream &out, const std::string &str)
{
	writeLine(out, std::string(" * ") + str);
}

/*!
* \brief Writes a doxy-comment (\c brief).
*
* The function outputs the content of the doxy-comment to the stream \c out (\c desc).
*
* \param out		Output stream for the text (\c params).
* \param brief		The content of \c brief field.
* \param desc		The content of \c description field.
* \param params		The content(s) of \c params field. This field is a map of tuples, for details see \c notes.
* \param notes		The content(s) of \c note field. Each element is a separate note.
* \param returns	The content of \return field.
*
* \note Each field of this doxycomment has a note in "()" denoting what each input parameter fills (notes).
* \note \c params is a vector of tuples. The first field fills the optional parameters to \c \\param (empty / in / out / in,out). 
*	The second parameter is the param's name.
*	The third parameter is the param's description.
* \note At least \c brief or \c desc needs to be filled in.
*
* \return Nothing (\c returns).
*/
void writeDoxyComment(std::ostream &out,
	const std::string& brief = "",
	const std::string& desc = "",
	const std::vector<std::tuple<std::string, std::string, std::string>>* params = nullptr,
	const std::vector<std::string>* notes = nullptr,
	const std::string& returns = ""
)
{
	if (brief.empty() && desc.empty())
	{
		std::cerr << "At least brief or desc needs to be filled in!" << std::endl;
		return;
	}

	// If this is the first field, not need for a new empty line before.
	bool isFirst = true;

	// start comment
	writeDoxyCommentStart(out);
	// brief
	if( !brief.empty() )
	{
		if (!isFirst)
			writeDoxyLine(out, "");
		else
			isFirst = false;
		writeDoxyLine(out, "\\brief " + brief);
	}
	// description
	if (!desc.empty())
	{
		if (!isFirst)
			writeDoxyLine(out, "");
		else
			isFirst = false;
		writeDoxyLine(out, desc);
	}
	// parameters
	if( params )
	{
		if (!isFirst)
			writeDoxyLine(out, "");
		else
			isFirst = false;
		for (auto& it : *params)
		{
			if( !std::get<1>(it).empty() )
				writeDoxyLine(out, "\\param"
					+ (std::get<0>(it).empty() ? "" : "[" + std::get<0>(it) + "] ")
					+ std::get<1>(it) + " "
					+ std::get<2>(it));
		}
	}
	// notes
	if( notes )
	{
		if (!isFirst)
			writeDoxyLine(out, "");
		else
			isFirst = false;

		for (auto& it : *notes)
		{
			writeDoxyLine(out, "\\note " + it);
		}
	}
	// returns
	if (!returns.empty())
	{
		if (!isFirst)
			writeDoxyLine(out, "");
		else
			isFirst = false;
		writeDoxyLine(out, "\\return " + returns);
	}

	// end comment
	writeDoxyCommentEnd(out);
} // end WriteDoxyComment




void writeEntityDestructor(std::ostream &out, const OpenInfraPlatform::ExpressBindingGenerator::Entity &entity, std::string parameters = "", std::string implementation = "")
{
	//writeDoxyComment(out, "Destructor for " + entity.getName());

	std::string signature = entity.getName() + "::~" + entity.getName() + "(" + parameters + ") {" + implementation + "}";
	writeLine(out, signature);
}

void writeEntityFunction(std::ostream &out, const OpenInfraPlatform::ExpressBindingGenerator::Entity &entity, std::string returnType, std::string name, std::string parameters = "", std::string qualifiers = "", std::string implementation = "")
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
			auto tokens = split(it, ';', Left);
			statements.insert(statements.end(), tokens.begin(), tokens.end());
		}

		std::vector<std::string> textSplitByOpenBraces = std::vector<std::string>();
		for(auto statement : statements) {
			auto tokens = split(statement, '{', Left);
			textSplitByOpenBraces.insert(textSplitByOpenBraces.end(), tokens.begin(), tokens.end());
		}

		std::vector<std::string> lines = std::vector<std::string>();
		for(auto line : textSplitByOpenBraces) {
			auto tokens = split(line, '}', Standalone);
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

void writeEntityConstructor(std::ostream &out, const OpenInfraPlatform::ExpressBindingGenerator::Entity &entity, std::string parameters = "", std::string implementation = "")
{
	//std::string signature = entity.getName() + "::" + entity.getName() + "(" + parameters + ") {" + implementation + "}";
	//writeLine(out, signature);
	writeEntityFunction(out, entity, "", entity.getName(), parameters, "", implementation);
}

void writeValueTypeFile(const Type& type, std::ostream& out) {
	const std::string name = type.getName();
	const std::string basetype = type.getUnderlyingTypeName();
	
	
	writeDoxyComment(out, "Type, subtype of  " + basetype);
	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + name + " : public " + basetype + " {");
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
	
	linebreak(out);
	writeLine(out, name + "& operator=(const " + name + "& other) = default;");
	writeLine(out, "virtual " + name + "& operator=(const EXPRESSOptional<" + name + "> &other);");
	//writeLine(out, "virtual " + name + "& operator=(const EXPRESSOptional<" + name + "> &other) { this->m_value = other.get_value_or(" + name + "()); return *this; };");
	linebreak(out);
	writeLine(out, "virtual " + name + "* operator->() override;");
	//writeLine(out, "virtual " + name + "* operator->() override { return this; }");
	writeLine(out, "virtual const " + name + "* const operator->() const override;");
	//writeLine(out, "virtual const " + name + "* const operator->() const override { return this; }");
	linebreak(out);
	writeLine(out, "virtual const std::string classname() const override;");
	//writeLine(out, "virtual const std::string classname() const override { return \"" + name + "\"; }");
	writeLine(out, "};");
	return;
}

void writeContainerTypeFile(const Schema& schema, const Type& type, std::ostream& out) {
	/*
	#define DEFINE_CONTAINERTYPE(name, containertype, min, max, valuetype)\
	class name : public ExpressBindingGenerator::EXPRESSContainer<containertype<valuetype>,valuetype,min,max>, public ExpressBindingGenerator::EXPRESSType {\
	using base = ExpressBindingGenerator::EXPRESSContainer<containertype<valuetype>,valuetype,min,max>;\
	public:\
		typedef name type;\
		using base::base;\
		using base::operator=;\
		using base::operator containertype<valuetype>&;\
		name* operator->() { return this; }\
		const name* const operator->() const { return this; }\
		virtual name& operator=(const EXPRESSOptional<name> &other) { operator=(other.get_value_or(name())); return *this; };\
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
	const std::string basetype = "EarlyBinding::" + type.getContainerTypeName() + "<" + min + "," + max + "," + valuetype + ">";

	writeDoxyComment(out, "Container of " + type.getContainerType() + ", with cardinalities [" + min + "," + max + "]");
	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + name + " : public " + basetype + ", public EarlyBinding::EXPRESSType {");
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
	writeLine(out,  name + "* operator->();");
	//writeLine(out,  name + "* operator->() { return this; }");
	writeLine(out, "const " + name + "* const operator->() const;");
	//writeLine(out, "const " + name + "* const operator->() const { return this; }");
	linebreak(out);
	writeLine(out, name + "& operator=(" + name + "& other);");
	//writeLine(out, name + "& operator=(const " + name + "& other) = default;");
	//writeLine(out, name + "& operator=(const EXPRESSOptional<" + name + "> &other);");
	//writeLine(out, name + "& operator=(const EXPRESSOptional<" + name + "> &other) { operator=(other.get_value_or(" + name + "())); return *this; };");
	linebreak(out);
	writeLine(out, "virtual const std::string classname() const override;");
	//writeLine(out, "virtual const std::string classname() const override { return \"" + name + "\"; }");
	writeLine(out, "virtual const std::string getStepParameter() const override;");
	//writeLine(out, "virtual const std::string getStepParameter() const override { return this->base::getStepParameter(); }");
	linebreak(out);
	//writeLine(out, "static " + name + " readStepData(const std::string& args, const std::shared_ptr<ExpressBindingGenerator::EXPRESSModel>& model) {");
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

	writeLine(out, "enum class "+ enumName + " : int {");
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

	const std::string basetype = "ExpressBindingGenerator::ValueType<" + enumName + ">";
	
	/*
	#define DEFINE_ENUMTYPE(name, seq)\
	ENUM_W_STR(name##Values, int, seq);\
	class name : public OpenInfraPlatform::ExpressBindingGenerator::ValueType<name##Values> {\
		using base = OpenInfraPlatform::ExpressBindingGenerator::ValueType<name##Values>;\
		public:\
			typedef name type;\
			using base::base;\
			using base::operator=;\
			using base::operator->;\
			virtual name& operator=(const EXPRESSOptional<name> &other) { this->m_value = other.get_value_or(name()); return *this; };\
			virtual const std::string classname() const override { return #name; }\
			const std::string name::getStepParameter() const { return "." + to_string(OpenInfraPlatform::ExpressBindingGenerator::ValueType<name##Values>::m_value) + "."; };\
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

	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + name + " : public " + basetype + " {");
	writeLine(out, "using base = " + basetype + ";");
	writeLine(out, "public:");
	writeLine(out, "typedef " + enumName + " Enum;");
	linebreak(out);

	writeLine(out, "using base::base;");
	writeLine(out, "using base::operator=;");
	writeLine(out, "using base::operator->;");
	linebreak(out);
	
	writeLine(out, "virtual " + name + "& operator=(const EXPRESSOptional<" + name + "> &other) { this->m_value = other.get_value_or(" + name + "()); return *this; };");
	writeLine(out, "virtual const std::string classname() const override { return \"" + toUpper(name) + "\"; }");
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

	std::for_each(seq.begin(), seq.end(), [](auto& elem) {
		elem = "ENUM_" + elem;
	});

	writeLine(out, "enum class OIP_EARLYBINDING_EXPORT " + enumName + " : int {");
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
	writeLine(out, "OIP_EARLYBINDING_EXPORT const std::string to_string(const " + enumName + "& v);");
	linebreak(out);

	//writeLine(out, "inline const std::string to_string(const " + enumName + "& v) {");
	//writeLine(out, "switch(v) {");
	//for (auto elem : seq) {
	//	writeLine(out, "case " + enumName + "::" + elem + ": return \"." + elem + ".\";");
	//}
	//writeLine(out, "default: return \"unknown\";");
	//writeLine(out, "}");
	//writeLine(out, "};");
	//linebreak(out);

	const std::string basetype = "EarlyBinding::EnumType<" + enumName + "," + std::to_string(seq.size()) + ">";
	writeDoxyComment(out, "EnumType of " + std::to_string(seq.size()) + " elements");
	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + name + " : public " + basetype + " {");
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
	//writeLine(out, "virtual " + name + "& operator=(const EXPRESSOptional<" + name + "> &other) { this->m_value = other.get_value_or(" + name + "()); return *this; };");
	linebreak(out);
	writeLine(out, "virtual const std::string classname() const override;");
	//writeLine(out, "virtual const std::string classname() const override { return \"" + name + "\"; }");
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
	class select : public boost::make_recursive_variant<BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_TO_TUPLE(seq))>::type, public OpenInfraPlatform::ExpressBindingGenerator::EXPRESSType {\
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
	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + select + " : public " + basetype + ", public ExpressBindingGenerator::EXPRESSType {");
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

	writeLine(out, "virtual const std::string classname() const override { return \"" + toUpper(select) + "\"; };");
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

void writeSelectTypeFileREFACTORED(const Schema& schema, const Type& selectType, std::ostream& out) {
	//class IfcTimeOrRatioSelect : public OpenInfraPlatform::ExpressBindingGenerator::SelectType<IfcTimeOrRatioSelect, IfcDuration, IfcRatioMeasure> {
	//	using base = OpenInfraPlatform::ExpressBindingGenerator::SelectType<IfcTimeOrRatioSelect, IfcDuration, IfcRatioMeasure>;
	//public:
	//	using base::base;
	//	using base::operator=;		
	//
	//	virtual const std::string classname() const override { return "IfcTimeOrRatioSelect"; }
	//};

	const std::string select = selectType.getName();
	std::vector<std::string> seq = selectType.getTypes();
	//std::sort(seq.begin(), seq.end(), [](const std::string& lhs, const std::string& rhs) ->bool {return lhs < rhs; });

	writeDoxyComment(out, "SelectType of " + join(seq, ','));

	std::transform(seq.begin(), seq.end(), seq.begin(), [&schema](std::string elem)->std::string {return schema.hasEntity(elem) ? "EXPRESSReference<" + elem + ">" : elem; });

	const std::string basetype = "EarlyBinding::SelectType<" + join(seq, ',') + ">";

	//writeLine(out, "class " + select + " : public " + basetype +", public ExpressBindingGenerator::EXPRESSType {");
	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + select + " : public " + basetype + " {");
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
	writeLine(out, "virtual const std::string classname() const override;");
	//writeLine(out, "virtual const std::string classname() const override { return \"" + select + "\"; }");
	writeLine(out, "virtual const std::string getStepParameter() const;");
	//writeLine(out, "virtual const std::string getStepParameter() const { return base::getStepParameter(); }");
	writeLine(out, "};");
}

void writeSelectTypeFileMinimal(Schema& schema, Type& selectType, std::ostream& out) {
	const std::string select = selectType.getName();
	std::vector<std::string> seq = selectType.getTypes();
	std::transform(seq.begin(), seq.end(), seq.begin(), [&schema](std::string elem)->std::string {return schema.hasEntity(elem) ? "EXPRESSReference<" + elem + ">" : elem; });

	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + select + " {");
	writeLine(out, "public:");
	writeLine(out, select + "() = default;");
	writeLine(out, "~" + select + "() { };");
	writeLine(out, select + "& operator=(const " + select + "& other) = default;");
	linebreak(out);
	writeLine(out, select + "* operator->(){ return this; }");
	writeLine(out, "const std::string classname() const { return \"" + toUpper(select) + "\"; }");
	writeLine(out, "const std::string getStepParameter() const { return \"$\"; }");
	writeLine(out, "static " + select + " readStepData(const std::string arg, const std::shared_ptr<ExpressBindingGenerator::EXPRESSModel>& model) { return " + select + "(); }");
	writeLine(out, "};");
}

void GeneratorOIP::getCachedIncludes(const std::string& name, std::set<std::string>& types, std::set<std::string>& entities) const
{
	if (cacheIncludesTypes.find(name) != cacheIncludesTypes.end())
		types = cacheIncludesTypes.at(name);
	if (cacheIncludesEntities.find(name) != cacheIncludesEntities.end())
		entities = cacheIncludesEntities.at(name);
}

void GeneratorOIP::resolveSelectTypeIncludes(const Schema& schema, const Type& type, std::set<std::string>& includes, std::set<std::string>& resolved) {
	// if already checked -> skip
	if (resolved.find(type.getName()) != resolved.end())
		return;
	// check the cached stuff
	if (cacheIncludesEntities.find(type.getName()) != cacheIncludesEntities.end())
	{
		const auto& typeAttr = cacheIncludesEntities.at(type.getName());
		for( const auto& attr : typeAttr )
			if(includes.find(attr) == includes.end() )
				includes.insert(attr);
		resolved.insert(type.getName());
		return;
	}
	// add to resolved
	resolved.insert(type.getName());
	// otherwise check all types
	const auto& possibleSelectTypes = type.getTypes();
	for (const auto& value : possibleSelectTypes) {
		if (includes.find(value) == includes.end()) {
			if (schema.hasEntity(value)) {
				includes.insert(value);
			}
			else {
				if (schema.hasType(value) && schema.isSelectType(value)) {
					Type nextType = schema.getTypeByName(value);
					resolveSelectTypeIncludes(schema, nextType, includes, resolved);
				}
			}
		}
	}
}

void GeneratorOIP::resolveEntityIncludes(const Schema& schema, const Entity& entity, std::set<std::string>& includes, std::set<std::string>& resolved) {
	// if already checked -> skip
	if (resolved.find(entity.getName()) != resolved.end())
		return;
	// check the cached stuff
	if (cacheIncludesEntities.find(entity.getName()) != cacheIncludesEntities.end())
	{
		const auto& entAttr = cacheIncludesEntities.at(entity.getName());
		for (const auto& attr : entAttr)
			if (includes.find(attr) == includes.end())
				includes.insert(attr);
		resolved.insert(entity.getName());
		return;
	}

	resolved.insert(entity.getName());

	const auto attributes = schema.getAllEntityAttributes(entity, true);

	std::set<std::string> newEntityAttributes;
	std::string attrTypeName = "";
	for (const auto& attr : attributes) {
		if (attr.type->getType() == eEntityAttributeParameterType::TypeNamed) {
			attrTypeName = attr.type->toString();
		}
		else if (attr.type->getType() == eEntityAttributeParameterType::eGeneralizedType) {
			auto elementType = attr.type;
			while (elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
				elementType = std::static_pointer_cast<EntityAttributeGeneralizedType>(elementType)->elementType;
			}
			attrTypeName = elementType->toString();
		}

		if (   includes.find(attrTypeName) != includes.end()
			&& resolved.find(attrTypeName) != resolved.end())
			continue;
		if (schema.hasEntity(attrTypeName)) {
			newEntityAttributes.insert(attrTypeName);
		}
		if (schema.hasType(attrTypeName)) {
			const auto type = schema.getTypeByName(attrTypeName);
			if (type.isSelectType()) {
				resolveSelectTypeIncludes(schema, type, newEntityAttributes, resolved);
			}
		}
	}

	for (const auto& attributeEntityName : newEntityAttributes)
		if (includes.find(attributeEntityName) == includes.end())
			includes.insert(attributeEntityName);

	for (const auto& attributeEntityName : newEntityAttributes) {
		if (resolved.find(attributeEntityName) == resolved.end()) {
			auto attributeEntity = schema.getEntityByName(attributeEntityName);
			resolveEntityIncludes(schema, attributeEntity, includes, resolved);
		}
	}
}

void GeneratorOIP::resolveIncludes(const Schema& schema, const Type& type)
{
	std::set<std::string> typeAttributes, entityAttributes;

	if (type.isSelectType() || type.isContainerType()) {
		if (type.isSelectType())
		{
			for (auto select : type.getTypes()) {
				if (schema.hasEntity(select)) {
					entityAttributes.insert(select);
				}
				if (schema.hasType(select)) {
					typeAttributes.insert(select);
				}
			}
		}
		else if (type.isContainerType())
		{
			if (schema.hasEntity(type.getContainerType())) {
				entityAttributes.insert(type.getContainerType());
			}
			if (schema.hasType(type.getContainerType())) {
				typeAttributes.insert(type.getContainerType());
			}
		}

		std::set<std::string> resolvedClasses = { type.getName() };

		if (!typeAttributes.empty()) {
			for (const auto& val : typeAttributes) {
				if (schema.isSelectType(val)) {
					resolveSelectTypeIncludes(schema, schema.getTypeByName(val), entityAttributes, resolvedClasses);
				}
			}

			auto self = typeAttributes.find(type.getName());
			while (self != typeAttributes.end()) {
				typeAttributes.erase(self);
				self = typeAttributes.find(type.getName());
			}

			cacheIncludesTypes.insert(std::pair<std::string, std::set<std::string>>(type.getName(), typeAttributes));
		}

		if (!entityAttributes.empty()) {
			std::set<std::string> allEntitiesToInclude;
			for (const auto& entity : entityAttributes) {
				allEntitiesToInclude.insert(entity);
				resolveEntityIncludes(schema, schema.getEntityByName(entity), allEntitiesToInclude, resolvedClasses);
			}

			// remember for this type (saves time)
			cacheIncludesEntities.insert(std::pair<std::string, std::set<std::string>>(type.getName(), allEntitiesToInclude));
		}
	}
}

void GeneratorOIP::resolveIncludes(const Schema& schema, const Entity& entity)
{
	std::set<std::string> typeAttributes, entityAttributes;

	auto attributes = schema.getAllEntityAttributes(entity, true);

	for (const auto& attr : attributes) {
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

			while (elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
				elementType = std::static_pointer_cast<EntityAttributeGeneralizedType>(elementType)->elementType;
			}

			if (schema.hasEntity(elementType->toString())) {
				entityAttributes.insert(elementType->toString());
			}
			if (schema.hasType(elementType->toString())) {
				typeAttributes.insert(elementType->toString());
			}
		}
		if (attr.isInverse() || attr.hasInverseCounterpart()) {
			for (const auto& inverse : attr.getInverses())
			{
				if (schema.hasEntity(inverse.first)) {
					if (entityAttributes.find(inverse.first) == entityAttributes.end()) {
						entityAttributes.insert(inverse.first);
					}
				}
				if (schema.hasType(inverse.first)) {
					if (typeAttributes.find(inverse.first) == typeAttributes.end()) {
						typeAttributes.insert(inverse.first);
					}
				}
			}
		}
	}

	// Initialize set of resolved classes.
	std::set<std::string> resolvedClasses = {};

	for (const auto& typeName : typeAttributes) {
		auto type = schema.getTypeByName(typeName);
		if (type.isSelectType()) {
			resolveSelectTypeIncludes(schema, type, entityAttributes, resolvedClasses);
		}
	}

	for (const auto attributeEntityName : entityAttributes) {
		auto attributeEntity = schema.getEntityByName(attributeEntityName);
		resolveEntityIncludes(schema, attributeEntity, entityAttributes, resolvedClasses);
	}

	auto self = entityAttributes.find(entity.getName());
	while (self != entityAttributes.end()) {
		entityAttributes.erase(self);
		self = entityAttributes.find(entity.getName());
	}

	if( !typeAttributes.empty() )
		cacheIncludesTypes.insert(std::pair<std::string, std::set<std::string>>(entity.getName(), typeAttributes));
	if (!entityAttributes.empty())
		cacheIncludesEntities.insert(std::pair<std::string, std::set<std::string>>(entity.getName(), entityAttributes));

}

OpenInfraPlatform::ExpressBindingGenerator::GeneratorOIP::GeneratorOIP(const std::string &outputDirectory) : outputDirectory_(outputDirectory) {
}



GeneratorOIP::~GeneratorOIP() {
}

void GeneratorOIP::prepareGeneration(const Schema& schema)
{
	preparePaths(schema);
	prepareIncludes(schema);
	prepareSplits(schema);
}

void GeneratorOIP::prepareIncludes(const Schema& schema)
{
	// prepare the includes
	for (const auto& type : schema.types_)
		resolveIncludes(schema, type);
	for (const auto& entity : schema.entities_)
		resolveIncludes(schema, entity);
}

void GeneratorOIP::preparePaths(const Schema& schema)
{
	// lambda for easier notation
	std::function<std::string(std::string, std::string)> prepareFolder = []
	(const std::string& basepath, const std::string& newfolder) -> std::string
	{
		std::string fullpath = basepath + "/" + newfolder;
		if (!fs::exists(fullpath)) {
			fs::create_directory(fullpath);
		}
		return fullpath;
	};

	rootDirectory_ = prepareFolder(outputDirectory_, schema.getName());
	sourceDirectory_ = prepareFolder(rootDirectory_, "src");
	prepareFolder(sourceDirectory_, "zero");
	prepareFolder(sourceDirectory_, "bot");
	prepareFolder(sourceDirectory_, "mid");
	prepareFolder(sourceDirectory_, "top");
	readerPath_ = prepareFolder(sourceDirectory_, "reader");
}

void GeneratorOIP::prepareSplits(const Schema& schema)
{
	// build up the directed graph of entities/types
	// ignoring EXPRESS types as possible nodes (no REAL, NUMBER, etc.)
	std::map<std::string, size_t> mapNameToIndex;
	std::map<size_t, std::string> mapIndexToName;

	size_t counter = 0;
	for (const auto& type : schema.types_)
	{
		mapIndexToName.insert(std::pair<size_t, std::string>(counter, type.getName()));
		mapNameToIndex.insert(std::pair<std::string, size_t>(type.getName(), counter++));
	}

	size_t entityOffset = counter;
	for (const auto& entity : schema.entities_)
	{
		mapIndexToName.insert(std::pair<size_t, std::string>(counter, entity.getName()));
		mapNameToIndex.insert(std::pair<std::string, size_t>(entity.getName(), counter++));
	}

	//**************************************************
	// allocate adjacency matrix
	Graph adjacencyGraph(mapNameToIndex.size());

	// ease-of-access function
	std::function<void(std::string, std::string)> connect = [&adjacencyGraph, &mapNameToIndex]
	(const std::string& from, const std::string& to)
	{
		adjacencyGraph.addEdge(mapNameToIndex[from], mapNameToIndex[to]);
	};

	// determine the edges in the adjacency matrix
	// 1. supertypes
	for (const auto& type : schema.types_)
		if (type.isDerivedType())
			connect(type.getName(), type.getUnderlyingTypeName());
	for (const auto& entity : schema.entities_)
		if (entity.hasSupertype())
			connect(entity.getName(), entity.getSupertype());

	// 2. selects
	for (const auto& type : schema.types_)
		if (type.isSelectType())
			for (const auto& select : type.getTypes())
				connect(type.getName(), select); // doesn't matter if it is a type or an entity

	// 3. containers
	for (const auto& type : schema.types_)
		if (type.isContainerType())
			connect(type.getName(), type.getContainerType()); // doesn't matter if it is a type or an entity

	// 4. attributes
	std::function<std::vector<std::string>(std::string)> getAttributes = [&schema](const std::string& name) -> std::vector<std::string> {
		std::vector<std::string> attributes;
		for (const auto& attr : schema.getEntityByName(name).getAttributes()) // only own attributes, but inverses as well
			if (attr.type->getType() == eEntityAttributeParameterType::TypeNamed)
				attributes.push_back(attr.type->toString()); // doesn't matter if it is a type or an entity
			else if (attr.type->getType() == eEntityAttributeParameterType::eGeneralizedType) {
				auto elementType = attr.type;
				while (elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
					elementType = std::static_pointer_cast<EntityAttributeGeneralizedType>(elementType)->elementType;
				}
				attributes.push_back(elementType->toString()); // doesn't matter if it is a type or an entity
			}
		return attributes;
	};
	for (const auto& entity : schema.entities_)
		for (const auto& attr : getAttributes(entity.getName())) // only own attributes, but inverses as well
			connect(entity.getName(), attr); // doesn't matter if it is a type or an entity

	std::string name = sourceDirectory_ + "/graph.txt";
	std::ofstream out(name);
	adjacencyGraph.print(out, [&mapIndexToName](size_t i) -> std::string { 
		if (mapIndexToName.find(i) != mapIndexToName.end())
			return mapIndexToName.at(i);
		return "unknown";
	});

	//**************************************************
	// find the strongly connected components
	auto scc = adjacencyGraph.SCC();
	// print
	name = sourceDirectory_ + "/scc.txt";
	std::ofstream out2(name);
	for (const auto& lst : scc)
	{
		for (const auto& el : lst)
			out2 << mapIndexToName.at(el) + (el != *lst.rbegin() ? " -> " : "");
		out2 << std::endl;
	}			

	// mark those components that are connected with IfcProduct
	std::vector<bool> connected(mapNameToIndex.size(), false);
	for (const auto& lst : scc)
		//if (std::find_if(lst.begin(), lst.end(), [&IfcProductIndex](auto el) {return el == IfcProductIndex; }) != lst.end())
			for (const auto& el : lst)
				connected.at(el) = true;

	//**************************************************
	// find the biggest elementary circuit in the directed graph
	// see https://www.cs.tufts.edu/comp/150GA/homeworks/hw1/Johnson%2075.PDF
	// and http://normalisiert.de/code/java/elementaryCycles.zip

	// does one inherit from one that is connected?
	std::function<bool(std::vector<std::string>)> inheritsFromConnected = 
		[&mapNameToIndex, &connected, &schema, &inheritsFromConnected]
		(std::vector<std::string>& names) -> bool
	{
		for (const auto& name : names)
			if (schema.hasEntity(name))
			{
				// check the boollean array
				if( connected.at(mapNameToIndex.at(name)))
					return true;
			}
			else if (schema.hasType(name) && schema.isSelectType(name))
			{
				// call recursively
				if (inheritsFromConnected(schema.getTypeByName(name).getTypes()))
					return true;
			}
		return false;
	};

	// does it have any includes?
	std::function<bool(std::string)> hasIncludes = [this](const std::string& name) -> bool
	{
		std::set<std::string> types, entities;
		getCachedIncludes(name, types, entities);
		return !types.empty() || !entities.empty();
	};

	// does any of the attributes point to a connected?
	std::function<bool(std::vector<std::string>)> pointsToConnected = [&mapNameToIndex, &connected](std::vector<std::string>& names) -> bool
	{
		for (const auto& el : names)
			if (connected.at(mapNameToIndex.at(el)))
				return true;
		return false;
	};

	// does it have any connected includes?
	std::function<bool(std::string)> hasConnectedIncludes = [&pointsToConnected, this](const std::string& name) -> bool
	{
		std::set<std::string> types, entities;
		getCachedIncludes(name, types, entities);

		std::vector<std::string> allNames;
		allNames.reserve(types.size() + entities.size());
		for (const auto& el : types)
			allNames.push_back(el);
		for (const auto& el : entities)
			allNames.push_back(el);
		return pointsToConnected(allNames);
	};

	// determine the path for schemas' entities & types
	std::function<void(std::string)> determinePath = 
		[&mapNameToIndex, &connected, &schema, &inheritsFromConnected, &pointsToConnected, &hasConnectedIncludes, &hasIncludes, &getAttributes, this]
		(const std::string& name)
	{
		// if in the loop with ifcproduct -> mid
		if (connected.at(mapNameToIndex.at(name)))
		{
			mapFolderInSrc_.insert(std::pair<std::string, std::string>(name, "mid"));
			return;
		}
		else
		{
			// if it is a type
			if( schema.hasType(name) )
				if( !schema.isSelectType(name)) // but not a select type -> type
				{
					mapFolderInSrc_.insert(std::pair<std::string, std::string>(name, hasIncludes(name) ? "bot" : "zero"));
					return;
				}
				else // otherwise determine the selects
				{
					// look up if an entity within the select would be in top
					if(inheritsFromConnected(schema.getTypeByName(name).getTypes())
						|| pointsToConnected(schema.getTypeByName(name).getTypes())
						|| hasConnectedIncludes(name))
						mapFolderInSrc_.insert(std::pair<std::string, std::string>(name, "top"));
					else
						mapFolderInSrc_.insert(std::pair<std::string, std::string>(name, hasIncludes(name) ? "bot" : "zero"));
					return;
				}

			// if it inherits from one within the loop with ifcproduct -> top
			if( schema.hasEntity(name) )
			{
				auto parents = schema.getSuperTypes(schema.getEntityByName(name));
				if( inheritsFromConnected(parents)
					|| pointsToConnected(getAttributes(name))
					|| hasConnectedIncludes(name))
					mapFolderInSrc_.insert(std::pair<std::string, std::string>(name, "top"));
				else
					mapFolderInSrc_.insert(std::pair<std::string, std::string>(name, hasIncludes(name) ? "bot" : "zero"));
				return;
			}
			throw std::exception("This should never ever happen");
		}
	};

	for (const auto& type : schema.types_)
		determinePath(type.getName());
	for (const auto& entity : schema.entities_)
		determinePath(entity.getName());

	// print
	name = sourceDirectory_ + "/paths.txt";
	std::ofstream out3(name);
	for (const auto& pair : mapFolderInSrc_)
	{
		out3 << pair.second << ": " << pair.first << std::endl;
	}

	/*
	for (const auto& type : schema.types_)
		if (type.isSelectType())
			mapFolderInSrc_.insert(std::pair<std::string, std::string>(type.getName(), "mid"));
		else
			mapFolderInSrc_.insert(std::pair<std::string, std::string>(type.getName(), "bot"));

	for (const auto& entity : schema.entities_)
		mapFolderInSrc_.insert(std::pair<std::string, std::string>(entity.getName(), "top"));
	*/
}

void GeneratorOIP::generateREFACTORED( const Schema & schema)
{
	std::cout << "Preparing for generation ... ";
	prepareGeneration(schema);
	std::cout << "done." << std::endl;
	
	std::cout << "Generating CMakeLists ... ";
	generateCMakeListsFileREFACTORED(schema);
	std::cout << "done." << std::endl;

	std::cout << "Generating headers ... ";
	generateSchemaHeader(schema);
	generateEMTFiles(schema);
	generateNamespaceHeader(schema);
	std::cout << "done." << std::endl;

	std::cout << "Generating readers ... ";
	generateReaderFiles(schema);
	std::cout << "done." << std::endl;

	// Types.h
	createTypesHeaderFileREFACTORED(schema);

	// Entities.h
	std::cout << "Generating common headers ... ";
	createEntitiesHeaderFileREFACTORED(schema);
	std::cout << "done." << std::endl;

	std::cout << "Generating types:" << std::endl;
	//#pragma omp parallel for
	size_t typeCount = schema.getTypeCount();
	for (size_t i = 0; i < typeCount; i++) {
		const auto type = schema.getTypeByIndex(i);
		generateTypeHeaderFileREFACTORED(schema, type);
		generateTypeSourceFileREFACTORED(schema, type);
		std::cout << std::to_string(i+1) + "/" + std::to_string(typeCount) + ": " + type.getName() << std::endl;
	}

//#pragma omp parallel for
	std::cout << "Generating entities:" << std::endl;
	size_t entityCount = schema.getEntityCount();
	for (size_t i = 0; i < entityCount; i++) {
		const auto entity = schema.getEntityByIndex(i);
		generateEntityHeaderFileREFACTORED(schema, entity);
		generateEntitySourceFileREFACTORED(schema, entity);
		std::cout << std::to_string(i+1) + "/" + std::to_string(entityCount) + ": " + entity.getName() << std::endl;
	}
}

std::string GeneratorOIP::getFolder(const std::string& name) const
{
	if (mapFolderInSrc_.find(name) != mapFolderInSrc_.end())
	{
		return mapFolderInSrc_.at(name);
	}
	return outputDirectory_;
}

void GeneratorOIP::createEntitiesMapHeaderFile(const Schema &schema) {
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
		const auto entity = schema.getEntityByIndex(i);

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

void GeneratorOIP::createTypesHeaderFileREFACTORED(const Schema & schema)
{
	std::string folder = sourceDirectory_ + "/";
	std::string filename = schema.getName() + "Types.h";
	std::ofstream out(folder + filename);

	out << license;
	out << std::endl;
	
	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), "Types", guid, "h" }, '_');

	writeLine(out, "#pragma once");
	writeLine(out, "#ifndef " + define);
	writeLine(out, "#define " + define);
	linebreak(out);

	for ( const auto& type : schema.types_ ) {
		writeInclude(out, getFolder(type.getName()) + "/" + type.getName() + ".h");
	}

	linebreak(out);
	writeLine(out, "#endif // end define " + define);
	out.close();
}

void GeneratorOIP::createEntitiesHeaderFileREFACTORED(const Schema &schema) {
	std::string folder = sourceDirectory_ + "/";
	std::string filename = schema.getName() + "Entities.h";
	std::ofstream out(folder + filename);

	out << license << std::endl;
	out << std::endl;
	
	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), "Entities", guid, "h" }, '_');

	writeLine(out, "#pragma once");
	writeLine(out, "#ifndef " + define);
	writeLine(out, "#define " + define);
	linebreak(out);

	for (const auto& entity : schema.entities_) {
		writeInclude(out, getFolder(entity.getName()) + "/" + entity.getName() + ".h");
	}

	linebreak(out);
	writeLine(out, "#endif // end define " + define);
	out.close();
}

void GeneratorOIP::generateTypeHeaderFileREFACTORED(const Schema & schema, const Type & type) const
{
	std::string path = sourceDirectory_ + "/" + getFolder(type.getName()) + "/" + type.getName() + ".h";
	std::ofstream out(path);

	indentation = 0;

	writeLicenseAndNotice(out);

	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), type.getName(), guid, "h" }, '_');
	
	writeLine(out, "#pragma once");
	writeLine(out, "#ifndef " + define);
	writeLine(out, "#define " + define);

	linebreak(out);

	//writeInclude(out, "OpenInfraPlatform/../EarlyBinding/src/EXPRESS/EXPRESS.h");

	if (type.isSimpleType() || type.isDerivedType()) {
		writeInclude(out, "EXPRESS/ValueType.h");
	}
	else if (type.isEnumeration()) {
		writeInclude(out, "EXPRESS/EnumType.h");
	}
	else if (type.isContainerType()) {
		writeInclude(out, "EXPRESS/EXPRESSContainer.h");
		//writeInclude(out, "../EarlyBinding/src/EXPRESS/EXPRESSOptional.h");

		if (schema.hasType(type.getContainerType())) {
			writeInclude(out, "../" + getFolder(type.getContainerType()) + "/" + type.getContainerType() + ".h");
		}
	}
	else if (type.isSelectType()) {
		writeInclude(out, "EXPRESS/EXPRESSReference.h");
		writeInclude(out, "EXPRESS/SelectType.h");
	}

	writeInclude(out, "../" + schema.getName() + "Namespace.h");
	linebreak(out);


	if (type.isDerivedType()) {
		writeInclude(out, "../" + getFolder(type.getUnderlyingTypeName()) + "/" + type.getUnderlyingTypeName() + ".h");
		linebreak(out);
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

		if (!types.empty()) {
			for (const auto& val : types) {
				writeInclude(out, "../" + getFolder(val) + "/" + val + ".h");
			}
			linebreak(out);
		}
	}
	
	linebreak(out);

	writeBeginNamespace(out, schema);
	linebreak(out);

	if (type.isSelectType()) {
		if (!entities.empty()) {
			for (auto entity : entities) {
				writeLine(out, "class " + entity + ";");
			}
			linebreak(out);
		}
	}

	if (type.isSimpleType() || type.isDerivedType()) {
		writeValueTypeFile(type, out);
	}
	else if (type.isEnumeration()) {
		writeEnumTypeFileRefactored(type.getName(), type.getTypes(), out);
	}
	else if (type.isContainerType()) {
		if (schema.hasEntity(type.getContainerType())) {
			writeLine(out, "class " + type.getContainerType() + ";");
		}
		writeContainerTypeFile(schema, type, out);
	}
	else if (type.isSelectType()) {	
		writeSelectTypeFileREFACTORED(schema, type, out);
	}
	else {
		std::cerr << "UNKNOWN TYPE ENCOUNTERED!" << std::endl;
		//Unknown Type!
	}	

	writeEndNamespace(out, schema);
	writeLine(out, "#endif // end define " + define);
	out.close();
}

void GeneratorOIP::generateTypeSourceFileREFACTORED(const Schema & schema, const Type & type) const
{
	std::string path = sourceDirectory_ + "/" + getFolder(type.getName()) + "/" + type.getName() + ".cpp";
	std::ofstream out(path);

	indentation = 0;

	writeLicenseAndNotice(out);
		
	writeInclude(out, type.getName() + ".h");
	writeInclude(out, "EXPRESS/EXPRESSOptional.h");
	if (!type.isSelectType()) {
		writeInclude(out, "EXPRESS/EXPRESSOptionalImpl.h");
	}
	linebreak(out);

	if (type.isSelectType() || type.isContainerType()) {

		std::set<std::string> types, entities;
		getCachedIncludes(type.getName(), types, entities);

		if (!entities.empty()) {
			for (const auto& entity : entities) {
				writeInclude(out, "../" + getFolder(entity) + "/" + entity + ".h");
			}
			linebreak(out);
		}
		
		if (!types.empty()) {
			for (const auto& val : types) {
				writeInclude(out, "../" + getFolder(val) + "/" + val + ".h");
			}
			linebreak(out);
		}

		writeInclude(out, "EXPRESS/EXPRESSOptionalImpl.h");
		writeInclude(out, "EXPRESS/EXPRESSReferenceImpl.h");
		linebreak(out);
	}
	   	
	writeBeginNamespace(out, schema);
	
	std::string name = type.getName();

	if (type.isSimpleType() || type.isDerivedType()) {
		writeLine(out, name + "& " + name + "::operator=(const EXPRESSOptional<" + name + "> &other) { this->m_value = other.get_value_or(" + name + "()); return *this; };");
		linebreak(out);
		writeLine(out, name + "* " + name + "::operator->() { return this; }");
		writeLine(out, "const " + name + "* const " + name + "::operator->() const { return this; };");
		linebreak(out);
		writeLine(out, "const std::string " + name + "::classname() const { return \"" + toUpper(name) + "\"; };");
	}
	else if (type.isEnumeration()) {
		writeLine(out, "const std::string " + name + "::classname() const { return \"" + toUpper(name) + "\"; };");
		linebreak(out);
		writeLine(out, "const std::string to_string(const e" + type.getName() + "& v) {");
		writeLine(out, "switch(v) {");
		for (auto elem : type.getTypes()) {
			writeLine(out, "case e" + type.getName() + "::ENUM_" + elem + ": return \"." + elem + ".\";");
		}
		writeLine(out, "default: return \"unknown\";");
		writeLine(out, "}");
		writeLine(out, "};");
	}
	else if (type.isContainerType()) {
		writeLine(out, name + "* " + name + "::operator->() { return this; };");
		writeLine(out, "const " + name + "* const " + name + "::operator->() const { return this; };");
		linebreak(out);
		writeLine(out, name + "& " + name + "::operator=(" + name + "& other) { this->base::swap(other); return *this; };");
		//writeLine(out, name + "& " + name + "::operator=(const EXPRESSOptional<" + name + "> &other) { this->operator=(other.get_value_or(" + name + "())); return *this; };");
		linebreak(out);
		writeLine(out, "const std::string " + name + "::classname() const { return \"" + toUpper(name) + "\"; };");
		writeLine(out, "const std::string " + name + "::getStepParameter() const { return this->base::getStepParameter(); };");
	}
	else if (type.isSelectType()) {
		writeLine(out, "const std::string " + name + "::classname() const { return \"" + toUpper(name) + "\"; };");
		writeLine(out, "const std::string " + name + "::getStepParameter() const { return base::getStepParameter(); };");
	}
	else {
		std::cerr << "UNKNOWN TYPE ENCOUNTERED!" << std::endl;
		//Unknown Type!
	}

	writeEndNamespace(out, schema);

	writeLine(out, "template class OpenInfraPlatform::EarlyBinding::EXPRESSOptional<OpenInfraPlatform::" + schema.getName() + "::" + type.getName() + ">;");

	out.close();
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

void GeneratorOIP::generateReaderFiles(const Schema & schema)
{
	std::ofstream file(readerPath_  + "/" + schema.getName().append("Reader.h"));

	writeLicenseAndNotice(file);

	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), schema.getName() + "Reader", guid, "h" }, '_');

	writeLine(file, "#pragma once");
	writeLine(file, "#ifndef " + define);
	writeLine(file, "#define " + define);

	writeInclude(file, "../EarlyBinding/src/EXPRESS/EXPRESS.h");
	writeInclude(file, "string", true);
	linebreak(file);

	// Write begin namespace OpenInfraPlatform::Schema
	writeBeginNamespace(file, schema);	

	writeLine(file, "class OIP_EARLYBINDING_EXPORT " + schema.getName() + "Reader {"); // begin class
	writeLine(file, "public:");
	
	writeLine(file, "static std::shared_ptr<EarlyBinding::EXPRESSModel> FromFile(const std::string &filename);"); 
	writeLine(file, "};"); // end class

	writeEndNamespace(file, schema);

	writeLine(file, "#endif // end define " + define);

	file.close();

	file.open(readerPath_ + "/" + schema.getName().append("Reader.cpp"));
	writeLicenseAndNotice(file);
	writeInclude(file, schema.getName().append("Reader.h"));
	writeInclude(file, "../" + schema.getName() + "Entities.h");
	writeInclude(file, "fstream", true);
	writeInclude(file, "exception", true);
	linebreak(file);

	writeBeginNamespace(file, schema);
	linebreak(file);
	/*
	std::vector<std::string> parseArgs(const std::string &line) {
	std::vector<std::string> args;
	auto paramvalue = line.substr(line.find_first_of('(') + 1, line.find_last_of(')') - line.find_first_of('(') - 1);
	std::cout << paramvalue << std::endl;
	while (!paramvalue.empty()) {
	auto end = paramvalue.size() - 1;
	auto pos = paramvalue.find_first_of(',');
	if (pos < end) {
	if (paramvalue.find_first_of('(') < pos) {
	auto isOpenBrace = [](char c) -> bool {return c == '('; };

	while (std::count(paramvalue.begin(), paramvalue.begin() + pos, '(') != std::count(paramvalue.begin(), paramvalue.begin() + pos, ')'))
	pos++;

	args.push_back(paramvalue.substr(0, pos));
	paramvalue.erase(0, pos + 1);
	}
	else {
	args.push_back(paramvalue.substr(0, pos));
	paramvalue.erase(0, pos + 1);
	}
	}
	else {
	args.push_back(paramvalue.substr(0, pos));
	paramvalue.clear();
	}
	}
	return args;
	};
	*/

	writeLine(file, "std::vector<std::string> parseArgs(const std::string &line) {");
	writeLine(file, "std::vector<std::string> args;");
	writeLine(file, "args.push_back(line.substr(1, line.find_first_of('=') - 1));");
	writeLine(file, "auto paramvalue = line.substr(line.find_first_of('(') + 1, line.find_last_of(')') - line.find_first_of('(') - 1);");
	writeLine(file, "while(!paramvalue.empty()) {");
	writeLine(file, "auto end = paramvalue.size() - 1;");
	writeLine(file, "auto pos = paramvalue.find_first_of(',');");
	writeLine(file, "if (pos < end) {"); // begin if
	writeLine(file, "auto textStart = paramvalue.find_first_of('\\\'');");
	writeLine(file, "if (textStart < pos) {"); // begin if
	writeLine(file, "auto textEnd = paramvalue.substr(textStart + 1, paramvalue.size() - textStart - 1).find_first_of('\\\'') + textStart + 1;");
	writeLine(file, "pos = paramvalue.substr(textEnd, paramvalue.size() - textEnd).find_first_of(',') + textEnd;");
	writeLine(file, "} else if(paramvalue.find_first_of('(') < pos) {"); //end if begin else if
	writeLine(file, "while (std::count(paramvalue.begin(), paramvalue.begin() + pos, '(') != std::count(paramvalue.begin(), paramvalue.begin() + pos, ')')) pos++;");
	writeLine(file, "}"); // end else if
	writeLine(file, "args.push_back(paramvalue.substr(0, pos));");
	writeLine(file, "paramvalue.erase(0, pos + 1);");
	writeLine(file, "}"); // end if
	writeLine(file, "else {"); // begin else
	writeLine(file, "args.push_back(paramvalue.substr(0, pos));");
	writeLine(file, "paramvalue.clear();");
	writeLine(file, "}"); // end else
	writeLine(file, "}"); // end while !paramvalue.empty()
	writeLine(file, "return args;");
	writeLine(file, "};"); // end function parseArgs
	linebreak(file);


	writeLine(file, "std::shared_ptr<EarlyBinding::EXPRESSModel> " + schema.getName().append("Reader") + "::FromFile(const std::string &filename) {"); // begin function FromFile

	writeLine(file, "std::ifstream file(filename, std::ifstream::in);");
	writeLine(file, "if(file.is_open()) {"); // begin if(file.is_open())
	writeLine(file, "std::shared_ptr<EarlyBinding::EXPRESSModel> model = std::make_shared<EarlyBinding::EXPRESSModel>(\"" + schema.getName() + "\");");
	writeLine(file, "std::string lineInFile = \"\";");
	writeLine(file, "std::vector<std::string> lines;");
	writeLine(file, "try {");
	writeLine(file, "while (!std::getline(file, lineInFile).eof()) lines.push_back(lineInFile);");
	
	// begin for read file
	linebreak(file);
	writeLine(file, "// begin for read file");
	writeLine(file, "for(long i = 0; i < lines.size(); i++) {"); 
	writeLine(file, "auto line = lines[i];");
	writeLine(file, "if(line == \"\") continue;");
	writeLine(file, "line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());");
	writeLine(file, "if(line[0] == '#') {");
	writeLine(file, "const size_t id = std::stoull(line.substr(1, line.find_first_of('=') - 1));");
	writeLine(file, "const std::string entityType = line.substr(line.find_first_of('=') + 1, line.find_first_of('(') - line.find_first_of('=') - 1);");
	writeLine(file, "std::string parameters = line.substr(line.find_first_of('('), line.find_last_of(')') - line.find_first_of('(') + 1);");
	for (size_t idx = 0; idx < schema.getEntityCount(); idx++) {
		auto entity = schema.getEntityByIndex(idx);
		if (!schema.isAbstract(entity)) {
			writeLine(file, "if(entityType == \"" + toUpper(entity.getName()) + "\") {");
			//writeLine(file, "std::shared_ptr<" + entity.getName() + "> entity = std::make_shared<" + entity.getName() + ">(" + entity.getName() + "::readStepData(parseArgs(line), model));"); //TODO
			writeLine(file, "model->entities.insert({id, std::make_shared<" + entity.getName() + ">()});");
			writeLine(file, "continue;");
			writeLine(file, "}");
		}
	}
	writeLine(file, "}"); //end if line[0] == '#'
	writeLine(file, "}"); //end for read file

	linebreak(file);
	writeLine(file, "// initialize cross-references");
	writeLine(file, "#pragma omp parallel for");
	writeLine(file, "for(long i = 0; i < lines.size(); i++) {"); // begin for read file
	writeLine(file, "auto line = lines[i];");
	writeLine(file, "if(line == \"\") continue;");
	writeLine(file, "line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());");
	writeLine(file, "if(line[0] == '#') {");
	writeLine(file, "const size_t id = std::stoull(line.substr(1, line.find_first_of('=') - 1));");
	writeLine(file, "const std::string entityType = line.substr(line.find_first_of('=') + 1, line.find_first_of('(') - line.find_first_of('=') - 1);");
	writeLine(file, "std::string parameters = line.substr(line.find_first_of('('), line.find_last_of(')') - line.find_first_of('(') + 1);");
	for (size_t idx = 0; idx < schema.getEntityCount(); idx++) {
		auto entity = schema.getEntityByIndex(idx);
		if (!schema.isAbstract(entity)) {
			writeLine(file, "if(entityType == \"" + toUpper(entity.getName()) + "\") {");
            //writeLine(file, "*(model->entities.find(id)->second) = " + entity.getName() + "::readStepData(parseArgs(line), model);");
			writeLine(file, "(std::dynamic_pointer_cast<" + entity.getName() + ">(model->entities.find(id)->second))->operator=(" + entity.getName() + "::readStepData(parseArgs(line), model));");
			writeLine(file, "continue;");
			writeLine(file, "}");
		}
	}
	writeLine(file, "}"); //end if line[0] == '#'
	writeLine(file, "}"); //end for read file
	linebreak(file);
	writeLine(file, "// Initialize inverse parameters");
	writeLine(file, "size_t numEntities = model->entities.size();");
	writeLine(file, "#pragma omp parallel for");
	writeLine(file, "for(long i = 0; i < numEntities; i++) {"); // begin for each entity
	writeLine(file, "model->entities[i]->linkInverse(model);");
	writeLine(file, "}"); // end for each entity
	linebreak(file);
	writeLine(file, "return model;");
	writeLine(file, "}"); //end try 
	writeLine(file, "catch(std::exception e) {"); // begin catch
	writeLine(file, "std::cout << e.what() << std::endl;");
	writeLine(file, "}"); //end catch 
	writeLine(file, "}");
	writeLine(file, "else {");
	writeLine(file, "throw std::exception(\"Could not open file.\");");
	writeLine(file, "}"); // end else if(file.is_open())
	writeLine(file, "return nullptr;");
	writeLine(file, "};"); // end function FromFile
	writeEndNamespace(file, schema);

	file.close();
	return;
}

void GeneratorOIP::generateEMTFiles(const Schema & schema)
{
	std::ofstream file(sourceDirectory_ + "/EMTBasic" + schema.getName().append("EntityTypes.h"));

	writeLicenseAndNotice(file);
	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), "EMTBasic" + schema.getName() + "EntityTypes", guid, "h" }, '_');

	writeLine(file, "#pragma once");
	writeLine(file, "#ifndef " + define);
	writeLine(file, "#define " + define);
	
	writeLine(file, "namespace emt {"); // begin namespace emt
	writeLine(file, "template <");
	for (size_t idx = 0; idx < schema.getEntityCount(); idx++) {
		writeLine(file, "typename " + schema.getEntityByIndex(idx).getName() + "T,");
	}
	for (size_t idx = 0; idx < schema.getTypeCount(); idx++) {
		bool isLast = idx == schema.getTypeCount() - 1;
		writeLine(file, "typename " + schema.getTypeByIndex(idx).getName() + "T" + (isLast ? "": ","));
	}
	writeLine(file, ">");
	writeLine(file, "struct Basic" + schema.getName() + "EntityTypes {"); // begin struct
	for (size_t idx = 0; idx < schema.getEntityCount(); idx++) {
		writeLine(file, "typedef " + schema.getEntityByIndex(idx).getName() + "T " + schema.getEntityByIndex(idx).getName() + ";");
	}
	for (size_t idx = 0; idx < schema.getTypeCount(); idx++) {
		writeLine(file, "typedef " + schema.getTypeByIndex(idx).getName() + "T " + schema.getTypeByIndex(idx).getName() + ";");
	}
	writeLine(file, "};"); // end struct
		
	writeLine(file, "}"); // end namespace emt
	
	writeLine(file, "#endif // end define " + define);
	file.close();

	file.open(sourceDirectory_ + "/EMT" + schema.getName().append("EntityTypes.h"));

	guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), "EMT" + schema.getName() + "EntityTypes", guid, "h" }, '_');
	writeLicenseAndNotice(file);

	writeLine(file, "#pragma once");
	writeLine(file, "#ifndef " + define);
	writeLine(file, "#define " + define);

	writeInclude(file, "EMTBasic" + schema.getName().append("EntityTypes.h"));
	//writeInclude(file, schema.getName() + "Entities.h");
	//writeInclude(file, schema.getName() + "Types.h");

	writeBeginNamespace(file, schema);

	for (size_t idx = 0; idx < schema.getEntityCount(); idx++) {
		writeLine(file, "class " + schema.getEntityByIndex(idx).getName() + ";");
	}
	for (size_t idx = 0; idx < schema.getTypeCount(); idx++) {
		writeLine(file, "class " + schema.getTypeByIndex(idx).getName() + ";");
	}

	writeEndNamespace(file, schema);
	linebreak(file);

	writeLine(file, "namespace emt {"); // begin namespace emt

	writeLine(file, "typedef Basic" + schema.getName() + "EntityTypes <"); // begin typedef

	for (size_t idx = 0; idx < schema.getEntityCount(); idx++) {
		writeLine(file, "OpenInfraPlatform::" + schema.getName() + "::" + schema.getEntityByIndex(idx).getName() + ",");
	}
	for (size_t idx = 0; idx < schema.getTypeCount(); idx++) {
		bool isLast = idx == schema.getTypeCount() - 1;
		writeLine(file, "OpenInfraPlatform::" + schema.getName() + "::" + schema.getTypeByIndex(idx).getName() + (isLast ? "" : ","));
	}

	writeLine(file, "> " + schema.getName() + "EntityTypes;");

	writeLine(file, "}"); // end namespace emt
	writeLine(file, "#endif // end define " + define);

	file.close();
}

std::string GeneratorOIP::convertSimpleTypeToCPPType(const Schema &schema, std::string simpleType) const {
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

	file << "project(OpenInfraPlatform." << schema.getName() << ".Top CXX)" << std::endl;
	file << "" << std::endl;
	file << "set(CMAKE_DEBUG_POSTFIX \"d\")" << std::endl << std::endl;	
	file << "" << std::endl;
	file << "include_directories(" << std::endl;
	file << "  src" << std::endl;
	file << "  ${CMAKE_SOURCE_DIR}/EarlyBinding/src" << std::endl;
	file << "  ${visit_struct_INCLUDE_DIR}" << std::endl;
	file << "  ${Boost_INCLUDE_DIR}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_Source              "
		"src/*.*)" << std::endl;	
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_top_Source         "
		"src/top/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_mid_Source         "
		"src/mid/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_bot_Source         "
		"src/bot/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_zero_Source         "
		"src/zero/*.*)" << std::endl;
	file << "file(GLOB OpenInfraPlatform_" << schema.getName()
		<< "_reader_Source         "
		"src/reader/*.*)" << std::endl;

	file << "" << std::endl;

	file << "set_property(SOURCE ${OpenInfraPlatform_" << schema.getName() << "_Source} PROPERTY GENERATED ON)" << std::endl;
	file << "set_property(SOURCE ${OpenInfraPlatform_" << schema.getName() << "_top_Source} PROPERTY GENERATED ON)" << std::endl;
	file << "set_property(SOURCE ${OpenInfraPlatform_" << schema.getName() << "_mid_Source} PROPERTY GENERATED ON)" << std::endl;
	file << "set_property(SOURCE ${OpenInfraPlatform_" << schema.getName() << "_bot_Source} PROPERTY GENERATED ON)" << std::endl;
	file << "set_property(SOURCE ${OpenInfraPlatform_" << schema.getName() << "_zero_Source} PROPERTY GENERATED ON)" << std::endl;
	file << "set_property(SOURCE ${OpenInfraPlatform_" << schema.getName() << "_reader_Source} PROPERTY GENERATED ON)" << std::endl;

	file << "" << std::endl;

	file << "file(GLOB OpenInfraPlatform_EarlyBinding_EXPRESS_Source ${CMAKE_SOURCE_DIR}/EarlyBinding/src/EXPRESS/*.*)" << std::endl;

	file << "" << std::endl;

	file << "source_group(OpenInfraPlatform\\\\EXPRESS FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "                FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_Source})" << std::endl;	
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "\\\\top        FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_top_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "\\\\reader        FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_reader_Source})" << std::endl;
	
	file << "" << std::endl;

	file << "add_library(OpenInfraPlatform." << schema.getName() << ".Top SHARED" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_Source}" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_top_Source}" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_reader_Source}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "target_link_libraries(OpenInfraPlatform." + schema.getName() + ".Top PUBLIC" << std::endl;
	file << "\t"
		<< "OpenInfraPlatform." + schema.getName() + ".Mid" << std::endl;
	file << "\t"
		<< "OpenInfraPlatform." + schema.getName() + ".Bot" << std::endl;
	file << "\t"
		<< "OpenInfraPlatform." + schema.getName() + ".Zero" << std::endl;
	file << ")" << std::endl;
  file << "add_definitions(-DOIP_EARLYBINDING_EXPORT_ASEXPORT)" << std::endl;
	
	file << "" << std::endl;

	file << "target_include_directories(OpenInfraPlatform." + schema.getName() + ".Top INTERFACE src)" << std::endl;
	file << "set_target_properties(OpenInfraPlatform." + schema.getName() + ".Top PROPERTIES LINKER_LANGUAGE CXX)" << std::endl;

	file << "" << std::endl;

	file << "Install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include" << std::endl;
	file << "\t" << "COMPONENT " << schema.getName() << std::endl;
	file << "\t" << "FILES_MATCHING PATTERN \"*.h\"" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;
	file << "" << std::endl;

	file << "project(OpenInfraPlatform." << schema.getName() << ".Mid CXX)" << std::endl;
	file << "" << std::endl;
	file << "set(CMAKE_DEBUG_POSTFIX \"d\")" << std::endl << std::endl;
	file << "" << std::endl;
	file << "include_directories(" << std::endl;
	file << "  src" << std::endl;
	file << "  ${CMAKE_SOURCE_DIR}/EarlyBinding/src" << std::endl;
	file << "  ${visit_struct_INCLUDE_DIR}" << std::endl;
	file << "  ${Boost_INCLUDE_DIR}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "source_group(OpenInfraPlatform\\\\EXPRESS FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "\\\\mid          FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_mid_Source})" << std::endl;

	file << "" << std::endl;

	file << "add_library(OpenInfraPlatform." << schema.getName() << ".Mid SHARED" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_mid_Source}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "target_link_libraries(OpenInfraPlatform." + schema.getName() + ".Mid PUBLIC" << std::endl;
	file << "\t"
		<< "OpenInfraPlatform." + schema.getName() + ".Bot" << std::endl;
	file << "\t"
		<< "OpenInfraPlatform." + schema.getName() + ".Zero" << std::endl;
	file << ")" << std::endl;

	file << "target_include_directories(OpenInfraPlatform." + schema.getName() + ".Mid INTERFACE src)" << std::endl;
  file << "add_definitions(-DOIP_EARLYBINDING_EXPORT_ASEXPORT)" << std::endl;
	
	file << "" << std::endl;

	file << "" << std::endl;

	file << "project(OpenInfraPlatform." << schema.getName() << ".Bot CXX)" << std::endl;
	file << "" << std::endl;
	file << "set(CMAKE_DEBUG_POSTFIX \"d\")" << std::endl << std::endl;
	file << "" << std::endl;
	file << "include_directories(" << std::endl;
	file << "  src" << std::endl;
	file << "  ${CMAKE_SOURCE_DIR}/EarlyBinding/src" << std::endl;
	file << "  ${visit_struct_INCLUDE_DIR}" << std::endl;
	file << "  ${Boost_INCLUDE_DIR}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "source_group(OpenInfraPlatform\\\\EXPRESS FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "\\\\bot        FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_bot_Source})" << std::endl;

	file << "" << std::endl;

	file << "add_library(OpenInfraPlatform." << schema.getName() << ".Bot SHARED" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_bot_Source}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "target_link_libraries(OpenInfraPlatform." + schema.getName() + ".Bot PUBLIC" << std::endl;
	file << "\t"
		<< "OpenInfraPlatform." + schema.getName() + ".Zero" << std::endl;
	file << ")" << std::endl;

	file << "target_include_directories(OpenInfraPlatform." + schema.getName() + ".Bot INTERFACE src)" << std::endl;
	file << "add_definitions(-DOIP_EARLYBINDING_EXPORT_ASEXPORT)" << std::endl;

	file << "" << std::endl;

	file << "" << std::endl;

	file << "project(OpenInfraPlatform." << schema.getName() << ".Zero CXX)" << std::endl;
	file << "" << std::endl;
	file << "set(CMAKE_DEBUG_POSTFIX \"d\")" << std::endl << std::endl;
	file << "" << std::endl;
	file << "include_directories(" << std::endl;
	file << "  src" << std::endl;
	file << "  ${CMAKE_SOURCE_DIR}/EarlyBinding/src" << std::endl;
	file << "  ${visit_struct_INCLUDE_DIR}" << std::endl;
	file << "  ${Boost_INCLUDE_DIR}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "source_group(OpenInfraPlatform\\\\EXPRESS FILES ${OpenInfraPlatform_EarlyBinding_EXPRESS_Source})" << std::endl;
	file << "source_group(OpenInfraPlatform\\\\" << schema.getName()
		<< "\\\\zero        FILES "
		"${OpenInfraPlatform_"
		<< schema.getName() << "_zero_Source})" << std::endl;

	file << "" << std::endl;

	file << "add_library(OpenInfraPlatform." << schema.getName() << ".Zero SHARED" << std::endl;
	file << "\t"
		<< "${OpenInfraPlatform_" << schema.getName() << "_zero_Source}" << std::endl;
	file << ")" << std::endl;

	file << "" << std::endl;

	file << "target_include_directories(OpenInfraPlatform." + schema.getName() + ".Zero INTERFACE src)" << std::endl;
	file << "add_definitions(-DOIP_EARLYBINDING_EXPORT_ASEXPORT)" << std::endl;

	file << "" << std::endl;
	file.close();
}

void GeneratorOIP::generateEntityHeaderFileREFACTORED(const Schema & schema, const Entity & entity) const
{
	std::string path = sourceDirectory_ + "/" + getFolder(entity.getName()) + "/" + entity.getName() + ".h";
	std::ofstream out(path);

	writeLicenseAndNotice(out);

	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), entity.getName(), guid, "h" }, '_');

	writeLine(out, "#pragma once");
	writeLine(out, "#ifndef " + define);
	writeLine(out, "#define " + define);
	linebreak(out);
	writeInclude(out, "EXPRESS/EXPRESS.h");
	linebreak(out);
	writeInclude(out, "visit_struct/visit_struct.hpp", true);
	linebreak(out);
	writeInclude(out, "../" + schema.getName() + "Namespace.h");
	linebreak(out);
	writeInclude(out, "utility", true);
	linebreak(out);

	// Write include for supertype.
	if (entity.hasSupertype()) {
		writeInclude(out, "../" + getFolder(entity.getSupertype()) + "/" + entity.getSupertype() + ".h");
		linebreak(out);
	}


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

			while (elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
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
	if (self != entityAttributes.end()) {
		entityAttributes.erase(self);
	}
		
	if (!typeAttributes.empty()) {
		for (const auto& type : typeAttributes) {
			writeInclude(out, "../" + getFolder(type) + "/" + type + ".h");
		}
		linebreak(out);
	}
		

	std::string supertype = entity.hasSupertype() ? entity.getSupertype() : "EarlyBinding::EXPRESSEntity";
	
	writeBeginNamespace(out, schema);
	
	if (!entityAttributes.empty()) {
		for (const auto& entityAttribute : entityAttributes) {
			if( entityAttribute != supertype) // skip supertype when forward declaring
				writeLine(out,"class " + entityAttribute + ";");
		}
		linebreak(out);
	}

	writeDoxyComment(out, "Entity" + entity.hasSupertype() ? " subtype of " + supertype : "");

	writeLine(out, "class OIP_EARLYBINDING_EXPORT " + entity.getName() + " : public " + supertype + " {");
	writeLine(out, "private:");
	writeLine(out, "using base = " + supertype + ";");
	writeLine(out, "public:");
	
	//writeLine(out, "typedef " + entity.getName() + " UnderlyingType;");
	
	if (!schema.isAbstract(entity)) {
		// Default constructor.
		writeLine(out, entity.getName() + "();");

		// Copy constructor.
		writeLine(out, entity.getName() + "(const " + entity.getName() + "& other);");

		// Move constructor.
		writeLine(out, entity.getName() + "(" + entity.getName() + "&& other);");
		linebreak(out);

		// Destructor.
		writeLine(out, "virtual ~" + entity.getName() + "();");
		linebreak(out);

		// Swap function.
		writeLine(out, "friend void swap(" + entity.getName() + "& first, " + entity.getName() + "& second);");
		linebreak(out);

		// Assignment operator.
		writeLine(out, "virtual " + entity.getName() + "& operator=(const " + entity.getName() + "& other);");
		linebreak(out);

		// Classname function.
		writeLine(out, "virtual const std::string classname() const override;");
		linebreak(out); 

		//Interpret STEP data
		writeLine(out, "static " + entity.getName() + " readStepData(const std::vector<std::string>& args, const std::shared_ptr<EarlyBinding::EXPRESSModel>& model);");
		linebreak(out);

		//Get STEP data
		writeLine(out, "virtual const std::string getStepLine() const override;");
		linebreak(out);

		// Initialize INVERSE parameters
		writeLine(out, "virtual void linkInverse(const std::shared_ptr<EarlyBinding::EXPRESSModel>& model) override;");
		linebreak(out);

		writeLine(out, "using base::getStepParameter;");		
	}
	else {
		//writeLine(out, "virtual " + entity.getName() + "& operator=(" + entity.getName() + " other) = 0;");
		writeLine(out, "virtual const std::string classname() const = 0;");
		writeLine(out, "virtual const std::string getStepLine() const = 0;");
		writeLine(out, "virtual void linkInverse(const std::shared_ptr<EarlyBinding::EXPRESSModel>& model) = 0;");
	}

	//GetAttributes
	if (!attributes.empty()) {
		linebreak(out);
		for (auto attr : attributes) {
			writeLine(out, attr.toString(schema) + " " + attr.getName() + ";");
		}
	}

	writeLine(out, "};");
	writeEndNamespace(out, schema);

	//Make structure visitable
	auto attributeNames = schema.getAllEntityAttributesNames(entity, true);
	if (!attributeNames.empty())
	{
		linebreak(out);
		out << "\n";
		out << "VISITABLE_STRUCT(OpenInfraPlatform::" << schema.getName() << "::" << entity.getName();
		for (auto item : attributeNames) {
			out << "," << item;
		}
		out << ");" << std::endl;
		linebreak(out);
	}

	writeLine(out, "#endif // end define " + define);
	out.close();
}

void GeneratorOIP::generateSchemaHeader(const Schema & schema)
{
	std::ofstream file(sourceDirectory_ + "/"+ schema.getName().append(".h"));

	writeLicenseAndNotice(file);
	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), schema.getName(), guid, "h" }, '_');

	writeLine(file, "#pragma once");
	writeLine(file, "#ifndef " + define);
	writeLine(file, "#define " + define);
	linebreak(file);

	writeInclude(file, schema.getName() + "Namespace.h");
	writeInclude(file, schema.getName() + "Entities.h");
	writeInclude(file, schema.getName() + "Types.h");
	writeInclude(file, "reader/" + schema.getName() + "Reader.h");

	linebreak(file);
	writeLine(file, "#endif // end define " + define);

	file.close();	
}

void GeneratorOIP::generateNamespaceHeader(const Schema & schema)
{
	std::ofstream file(sourceDirectory_ + "/" + schema.getName().append("Namespace.h"));

	writeLicenseAndNotice(file);
	auto guid = getRandomGUID();
	std::replace(guid.begin(), guid.end(), '-', '_');
	std::string define = join(std::vector<std::string>{ "OpenInfraPlatform", schema.getName(), "Namespace", guid, "h" }, '_');

	writeLine(file, "#pragma once");
	writeLine(file, "#ifndef " + define);
	writeLine(file, "#define " + define);
	linebreak(file);
	writeInclude(file, "EXPRESS/EXPRESS.h");
	linebreak(file);

	writeBeginNamespace(file, schema);

	writeLine(file, "using REAL = OpenInfraPlatform::EarlyBinding::REAL;");
	writeLine(file, "using STRING = OpenInfraPlatform::EarlyBinding::STRING;");
	writeLine(file, "using BOOLEAN = OpenInfraPlatform::EarlyBinding::BOOLEAN;");
	writeLine(file, "using NUMBER = OpenInfraPlatform::EarlyBinding::NUMBER;");
	writeLine(file, "using INTEGER = OpenInfraPlatform::EarlyBinding::INTEGER;");
	writeLine(file, "using BINARY = OpenInfraPlatform::EarlyBinding::BINARY;");
	writeLine(file, "using LOGICAL = OpenInfraPlatform::EarlyBinding::LOGICAL;");
	linebreak(file);
	writeLine(file, "template <size_t MinCardinality, size_t MaxCardinality, typename T> using LIST = OpenInfraPlatform::EarlyBinding::EXPRESSContainer<T, MinCardinality, MaxCardinality>;");
	writeLine(file, "template <size_t MinCardinality, size_t MaxCardinality, typename T> using SET = OpenInfraPlatform::EarlyBinding::EXPRESSContainer<T, MinCardinality, MaxCardinality>;");
	writeLine(file, "template <size_t MinCardinality, size_t MaxCardinality, typename T> using BAG = OpenInfraPlatform::EarlyBinding::EXPRESSContainer<T, MinCardinality, MaxCardinality>;");
	writeLine(file, "template <size_t MinCardinality, size_t MaxCardinality, typename T> using ARRAY = OpenInfraPlatform::EarlyBinding::EXPRESSContainer<T, MinCardinality, MaxCardinality>;");

	writeEndNamespace(file, schema);

	writeLine(file, "#endif // end define " + define);

	file.close();
}

void GeneratorOIP::generateEntitySourceFileREFACTORED(const Schema & schema, const Entity & entity) const
{
	std::string path = sourceDirectory_ + "/" + getFolder(entity.getName()) + "/" + entity.getName() + ".cpp";
	std::ofstream out(path);

	writeLicenseAndNotice(out);	
	writeInclude(out, entity.getName() + ".h");
	linebreak(out);

	std::set<std::string> typeAttributes, entityAttributes;
	getCachedIncludes(entity.getName(), typeAttributes, entityAttributes);

	if (!entityAttributes.empty()) {
		for (const auto& entityAttribute : entityAttributes) {
			writeInclude(out, "../" + getFolder(entityAttribute) + "/" + entityAttribute + ".h");
		}
		linebreak(out);
	}

	writeInclude(out, "EXPRESS/EXPRESSOptionalImpl.h");
	writeInclude(out, "EXPRESS/EXPRESSReferenceImpl.h");
	linebreak(out);

	writeBeginNamespace(out, schema);
	

	auto initClassAsDefault = [&out, &entity, &schema]() {

		// Default constructor
		writeDoxyComment(out, "Default constructor");
		writeLine(out, entity.getName() + "::" + entity.getName() + "() { }");
		linebreak(out);

		// Copy constructor
		writeDoxyComment(out, "Copy constructor");
		writeLine(out, entity.getName() + "::" + entity.getName() + "(const " + entity.getName() + "& other) {");
		writeLine(out, "operator=(other);");
		writeLine(out, "}");
		linebreak(out);

		// Move constructor.
		writeDoxyComment(out, "Move constructor");
		writeLine(out, entity.getName() + "::" + entity.getName() + "(" + entity.getName() + "&& other) : " + entity.getName() + "() {");
		writeLine(out, "swap(*this, other);");
		writeLine(out, "}");
		linebreak(out);

		// Destructor
		writeDoxyComment(out, "Destructor.");
		writeLine(out, entity.getName() + "::~" + entity.getName() + "() {};");
		linebreak(out);

		// Copy Assignment Operator
		writeDoxyComment(out, "Assigns the content of \\c other to \\c this.");
		writeLine(out, entity.getName() + "& " + entity.getName() + "::operator=(const " + entity.getName() + "& other) {");
		writeLine(out, "this->m_id = other.m_id;");
		auto allAttributes = schema.getAllEntityAttributes(entity, true);
		for (auto& attr : allAttributes) {
			writeLine(out, "this->" + attr.getName() + " = other." + attr.getName() + ";");
		}
		writeLine(out, "return *this;");
		writeLine(out, "}");
		linebreak(out);

		// Classname function
		writeDoxyComment(out, "Returns the class name.", "", nullptr, nullptr, "\"" + toUpper(entity.getName()) + "\"");
		writeLine(out, "const std::string " + entity.getName() + "::classname() const { return \"" + toUpper(entity.getName()) + "\";} ");
		linebreak(out);

		// Interpret STEP data
		writeDoxyComment(out, "Interprets the STEP serialization.", "", nullptr, nullptr, "An instance of \\c " + entity.getName());
		writeLine(out, entity.getName() + " " + entity.getName() +"::readStepData(const std::vector<std::string>& args, const std::shared_ptr<EarlyBinding::EXPRESSModel>& model) {");
		writeLine(out, entity.getName() + " entity;");
		writeLine(out, "entity.setId(stoull(args[0]));");
		auto attributes = schema.getAllEntityAttributes(entity, false);
		for (int i = 0; i < attributes.size(); i++) {
			auto attr = attributes[i];
			writeLine(out, "entity." + attr.getName() + " = decltype(" + attr.getName() + ")::readStepData(args[" + std::to_string(i + 1) + "], model);");
		}
		writeLine(out, "return entity;");
		writeLine(out, "}");
		linebreak(out);

		// Get STEP data
		writeDoxyComment(out, "Returns the STEP serialization.", "", nullptr, nullptr, "#ID=" + entity.getName() + "(<attributes>);");
		writeLine(out, "const std::string " + entity.getName() + "::getStepLine() const {");
		writeLine(out, "std::string classname = this->classname();");
		writeLine(out, "boost::to_upper(classname);");
		writeLine(out, "std::string stepLine = this->getStepParameter() + \"=\" + classname + \"(\";");
		for (int i = 0; i < attributes.size() - 1; i++) {
			writeLine(out, "stepLine += " + attributes[i].getName() + ".getStepParameter() + \",\";");
		}
		writeLine(out, "stepLine += " + attributes.back().getName() + ".getStepParameter() + \");\";");
		writeLine(out, "return stepLine;");
		writeLine(out, "}");
		linebreak(out);
				
		// Set inverse attributes
		writeDoxyComment(out, "Sets the inverse attributes.", "", nullptr, nullptr, "");
		writeLine(out, "void " + entity.getName() + "::linkInverse(const std::shared_ptr<EarlyBinding::EXPRESSModel>& model) {");
		for (auto attr : schema.getAllEntityAttributes(entity, true))
		{
			if (attr.hasInverseCounterpart())
			{
				int dim = 0;
				auto elementType = attr.type;
				std::string get = "";
				if (attr.isOptional())
				{
					writeLine(out, "if( this->" + attr.getName() + " ) {");
					get = ".get()";
				}
				writeLine(out, "auto " + attr.getName() + "_0 = " + attr.getName() + get + ";");

				// if the attribute is a container, we need to get to the inner most entity
				while (elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
					dim++;
					writeLine(out, "for( auto " + attr.getName() + "_" + std::to_string(dim) + " : " + attr.getName() + "_" + std::to_string(dim - 1) + " ) {");
					elementType = std::static_pointer_cast<EntityAttributeGeneralizedType>(elementType)->elementType;
				}

				// treat differently for reference-to-entity and selecttype attributes
				if (schema.hasEntity(elementType->toString())) {
					for( auto inverse : attr.getInverses() )
					{
						writeLine(out, "if( " + attr.getName() + "_" + std::to_string(dim) + ".isOfType<" + inverse.first + ">() ) {");
						writeLine(out, attr.getName() + "_" + std::to_string(dim) + ".as<" + inverse.first + ">()->" + inverse.second + ".push_back(EXPRESSReference<" + entity.getName() + ">::constructInstance(this->getId(), model));");
						writeLine(out, "}");
					}
				}
				else if (schema.hasType(elementType->toString()) && schema.getTypeByName(elementType->toString()).isSelectType()) {
					Type t = schema.getTypeByName(elementType->toString());

					writeLine(out, "switch( " + attr.getName() + "_" + std::to_string(dim) + ".which() ) {");
					for (int k = 0; k < t.getTypeCount(); ++k) {
						auto inverses = attr.getInverses();

						// only write if there is also an inverse for this select type
						auto inverse = std::find_if(inverses.begin(), inverses.end(), [&t, &k](const auto &el) { return el.first == t.getType(k); });

						if ( inverse != inverses.end())
						{
							writeLine(out, "case " + std::to_string(k) + ":");
							writeLine(out, "{\t// " + t.getType(k));
							writeLine(out, attr.getName() + "_" + std::to_string(dim) + ".get<" + std::to_string(k) + ">()->" + inverse->second + ".push_back(EXPRESSReference<" + entity.getName() + ">::constructInstance(this->getId(), model));");
							writeLine(out, "break;");
							writeLine(out, "}");
						}
					}
					writeLine(out, "}"); // end switch
				}

				// close the for loops from above
				while (dim --> 0) // while dim goes to zero
					writeLine(out, "}");
				// close the if( this->" + attr.getName() + " )
				if (attr.isOptional())
					writeLine(out, "}");
			}
		}
		writeLine(out, "}");
		linebreak(out);
	};

	if (!schema.isAbstract(entity)) {

		initClassAsDefault();

		// Write swap function implementation
		writeDoxyComment(out, "Swaps the content between the \\c first and \\c second.");
		writeLine(out, "void swap(" + entity.getName() + "& first, " + entity.getName() + "& second) {");
		writeLine(out, "using std::swap;");
		writeLine(out, "swap(first.m_id, second.m_id);");
		for (auto attr : schema.getAllEntityAttributes(entity, true)) {
			writeLine(out, "swap(first." + attr.getName() + ", second." + attr.getName() + ");");
		}
		writeLine(out, "};");
		linebreak(out);		
	}
		
	writeEndNamespace(out, schema);

	writeLine(out, "template class OpenInfraPlatform::EarlyBinding::EXPRESSReference<OpenInfraPlatform::" + schema.getName() + "::" + entity.getName() + ">;");
	writeLine(out, "template class OpenInfraPlatform::EarlyBinding::EXPRESSOptional<OpenInfraPlatform::EarlyBinding::EXPRESSReference<OpenInfraPlatform::" + schema.getName() + "::" + entity.getName() + ">" + ">;");
	out.close();
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END
