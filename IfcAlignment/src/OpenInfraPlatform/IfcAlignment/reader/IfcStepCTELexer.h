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

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <memory>

namespace IfcStepCTE
{
	struct eTokenTypes
	{
		enum Enum
		{
			OpenBracket,
			CloseBracket,
			Integer,
			Comma,
			Minus,
			Dollar,
			Invalid
		};
	};

	struct token
	{
		eTokenTypes::Enum type;
		int value;
	};

	class Lexer
	{
	public:
		typedef std::shared_ptr<Lexer> Ptr;

		std::vector<token> getTokens(const std::string& str);

	private:
		void createOpenBracketToken();

		void createCloseBracketToken();

		void createCommaToken();

		void createMinusToken();

		void createDollarToken();

		void createInvalidToken();

		void createIntegerToken(const int value);

	private:
		std::vector<token> tokenList;
	};

	/*
	Terminals:
	<OpenBracket>
	<CloseBracket>
	<Integer>
	<Comma>
	<Minus>

	<ListOfListOfIntegers>			::= <OpenBracket> <ListOfListOfIntegersIntern> <CloseBracket>
	<ListOfListOfIntegersIntern>	::= "" | <OpenBracket> <ListOfIntegers> <CloseBracket>
	<ListOfIntegers>                ::= <Integer> | <Integer> <Comma> <ListOfIntegers>
	
	class Parser
	{
	public:
		Parser(Lexer::Ptr lexer) :
			lexer_(lexer)
		{

		}

		~Parser()
		{

		}

		void parse(const std::string& str)
		{

			const std::vector<token> tokens = lexer_->getTokens(str);

		}

	private:
		ReferenceCounted<Lexer> lexer_;
	};*/

	void readListOfListOfIntegers(const std::string& str, std::vector<std::vector<int>>& vec);
}
