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

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_token_803980f8_efd8_456e_ab24_78a84ad1c496_h
#define OpenInfraPlatform_Infrastructure_token_803980f8_efd8_456e_ab24_78a84ad1c496_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include <boost/noncopyable.hpp>
#include <string>

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct eTokenType
		{
			enum Enum
			{
				UNKNOWN = 0,
				IDENTIFIER = 1,
				NUMERIC = 2,
				BOOL = 3,
				STRING = 4,
				IF = 5,
				ELSE = 6,
				BRACKET_OPEN = 7,
				BRACKET_CLOSE = 8,
				SEMICOLON = 9,
				ADD = 10,
				SUB = 11,
				MUL = 12,
				DIV = 13,
				AND = 14,
				OR = 15,
				NOT = 16,
				ASSIGN = 17,
				EQUAL = 18,
				UNEQUAL = 19,
				LT = 20,
				GT = 21,
				LEQ = 22,
				GEQ = 23,
				FCALL = 24,
				TRUE = 25,
				FALSE = 26,
				BRACE_OPEN = 27,
				BRACE_CLOSE = 28,
				COMMA = 29,
				SIGN = 30,
				STMNT = 31,
				PROGRAM = 32,
				COND = 33,
				END = 34
			};
		}; // end struct eTokenType

		//! Converts a token to a human readable string
		BLUEINFRASTRUCTURE_API std::string tokenToString(const eTokenType::Enum type);

		struct token
		{
			token()
			{
				word = "";
				type = eTokenType::UNKNOWN;
				line = -1;
				pos = -1;
			}

			std::string word;
			eTokenType::Enum type;
			int line;
			int pos;
		};

		BLUEINFRASTRUCTURE_API std::ostream& operator << (std::ostream& os, token& t);
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::token;
}

#endif // end define OpenInfraPlatform_Infrastructure_token_803980f8_efd8_456e_ab24_78a84ad1c496_h
