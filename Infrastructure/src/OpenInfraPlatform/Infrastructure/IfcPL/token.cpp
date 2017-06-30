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

#include "token.h"

#include <iostream>

std::string OpenInfraPlatform::Infrastructure::tokenToString(const eTokenType::Enum type)
{
	std::string tokenTypes[] = {
		"UNKNOWN" /* = 0*/,
		"IDENTIFIER" /* = 1*/,
		"NUMERIC" /* = 2*/,
		"BOOL" /* = 3*/,
		"STRING" /* = 4*/,
		"IF" /* = 5*/,
		"ELSE" /* = 6*/,
		"BRACKET_OPEN" /* = 7*/,
		"BRACKET_CLOSE" /* = 8*/,
		"SEMICOLON" /* = 9*/,
		"ADD" /* = 10*/,
		"SUB" /* = 11*/,
		"MUL" /* = 12*/,
		"DIV" /* = 13*/,
		"AND" /* = 14*/,
		"OR" /* = 15*/,
		"NOT" /* = 16*/,
		"ASSIGN" /* = 17*/,
		"EQUAL" /* = 18*/,
		"UNEQUAL" /* = 19*/,
		"LT" /* = 20*/,
		"GT" /* = 21*/,
		"LEQ" /* = 22*/,
		"GEQ" /* = 23*/,
		"FCALL" /* = 24*/,
		"TRUE" /* = 25*/,
		"FALSE" /* = 26*/,
		"BRACE_OPEN" /* = 27*/,
		"BRACE_CLOSE" /* = 28*/,
		"COMMA" /* = 29*/,
		"SIGN" /* = 30*/,
		"STMNT" /* = 31*/,
		"PROGRAM" /* = 32*/,
		"COND" /* = 33*/,
		"END" /* = 34*/
	};

	return tokenTypes[type];
}

std::ostream& OpenInfraPlatform::Infrastructure::operator << (std::ostream& os, token& t)
{
	os << t.word.c_str() << "\t [" << tokenToString(t.type).c_str() << ",\t " << t.line << ",\t " << t.pos << "]";
	return os;
}