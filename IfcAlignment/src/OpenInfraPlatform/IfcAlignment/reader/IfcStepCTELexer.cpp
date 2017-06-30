// Copied and modified code from "IfcPlusPlus" library.
// This library is available under the OpenSceneGraph Public License. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and / or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* OpenSceneGraph Public License for more details.
*/

/* This file has been automatically generated using the TUM Open Infra Platform
Early Binding EXPRESS Generator. Any changes to this file my be lost in the future. */

#include "IfcStepCTELexer.h"

using namespace IfcStepCTE;

void IfcStepCTE::Lexer::createIntegerToken(const int value)
{
	token t;
	t.type = eTokenTypes::Integer;
	t.value = value;
	tokenList.push_back(t);
}

void IfcStepCTE::Lexer::createInvalidToken()
{
	token t;
	t.type = eTokenTypes::Invalid;
	t.value = 0;
	tokenList.push_back(t);
}

void IfcStepCTE::Lexer::createMinusToken()
{
	token t;
	t.type = eTokenTypes::Minus;
	t.value = 0;
	tokenList.push_back(t);
}

void IfcStepCTE::Lexer::createCommaToken()
{
	token t;
	t.type = eTokenTypes::Comma;
	t.value = 0;
	tokenList.push_back(t);
}

void IfcStepCTE::Lexer::createCloseBracketToken()
{
	token t;
	t.type = eTokenTypes::CloseBracket;
	t.value = 0;
	tokenList.push_back(t);
}

void IfcStepCTE::Lexer::createOpenBracketToken()
{
	token t;
	t.type = eTokenTypes::OpenBracket;
	t.value = 0;
	tokenList.push_back(t);
}

void IfcStepCTE::Lexer::createDollarToken()
{
	token t;
	t.type = eTokenTypes::Dollar;
	t.value = 0;
	tokenList.push_back(t);
}

std::vector<token> IfcStepCTE::Lexer::getTokens(const std::string& str)
{
	tokenList.clear();

	int stringLength = str.size();

	int tokenStartIndex = 0;	// index of first character of the current token
	int tokenEndIndex = 0;			// index of the last character that belongs to the character

	for (int i = 0; i < stringLength; i++)
	{
		tokenStartIndex = tokenEndIndex = i;

		if (str[i] == ' ' || str[i] == '\t') // skip blanks
		{
			continue;
		}

		if (isdigit(str[i]))
		{
			i++; // check next character

			while (isdigit(str[i])) // detect integers
			{
				tokenEndIndex = i;
				i++;
			}

			i--; // step one back - since last character was not a digit

			std::string sub = str.substr(tokenStartIndex, tokenEndIndex - tokenStartIndex + 1);
			//std::cout << sub << std::endl;
			int value = std::stoi(sub.c_str());
			//std::cout << value << std::endl;

			createIntegerToken(value);

			continue;
		}

		switch (str[i])
		{
		case '(':
			createOpenBracketToken();
			continue;
		case ')':
			createCloseBracketToken();
			continue;
		case ',':
			createCommaToken();
			continue;
		case '-':
			createMinusToken();
			continue;
		case  '$':
			createDollarToken();
			continue;
		default:
			createInvalidToken();
			std::cout << "error" << std::endl;
			break;
		}
	}

	return tokenList;
}

void IfcStepCTE::readListOfListOfIntegers(const std::string& str, std::vector<std::vector<int>>& vec)
{
	Lexer lex;
	const std::vector<token> tokens = lex.getTokens(str);

	assert(tokens[0].type == eTokenTypes::OpenBracket || tokens[0].type == eTokenTypes::Dollar);

	if (tokens[0].type == eTokenTypes::Dollar)
	{
		return;
	}

	assert(tokens[1].type == eTokenTypes::OpenBracket);

	int tokenIndex = 1;

	std::vector<int> internalList;

	while (tokenIndex < tokens.size())
	{
		internalList.clear();

		// read CloseBracket or OpenBracket
		const token* t = &tokens[tokenIndex];
		assert(t->type == eTokenTypes::CloseBracket | t->type == eTokenTypes::OpenBracket);

		if (t->type == eTokenTypes::CloseBracket)
		{
			t = &tokens[++tokenIndex];
			assert(t->type == eTokenTypes::Comma | t->type == eTokenTypes::CloseBracket);

			if (t->type == eTokenTypes::CloseBracket)
			{
				return;
			}

			t = &tokens[++tokenIndex];
			assert(t->type == eTokenTypes::OpenBracket);
		}

		do
		{
			// read Integer or read minus sign if available
			t = &tokens[++tokenIndex];
			assert(t->type == eTokenTypes::Integer || t->type == eTokenTypes::Minus);

			bool isNegative = false;

			if (t->type == eTokenTypes::Minus)
			{
				// Read integer now
				t = &tokens[++tokenIndex];
				assert(t->type == eTokenTypes::Integer);

				isNegative = true;
			}

			internalList.push_back(isNegative ? -t->value : t->value);

			// does list end here?
			t = &tokens[++tokenIndex];
			assert(t->type == eTokenTypes::Comma || t->type == eTokenTypes::CloseBracket);

		} while (t->type == eTokenTypes::Comma);

		vec.push_back(internalList);
	}
}

