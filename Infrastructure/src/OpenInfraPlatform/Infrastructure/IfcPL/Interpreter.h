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
#ifndef OpenInfraPlatform_Infrastructure_Interpreter_477027e7_a49f_4552_83bf_6a4b700adf11_h
#define OpenInfraPlatform_Infrastructure_Interpreter_477027e7_a49f_4552_83bf_6a4b700adf11_h

#include <boost/noncopyable.hpp>
#include <iostream>
#include <sstream>
#include <map>

#undef TRUE
#undef FALSE

#include "token.h"
#include "Lexer.h"
#include "AbstractSyntaxTree.h"
#include "variant.h"

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct symbol
		{
			std::string name;
		};

		class Interpreter
		{
		public:
			void execute(buw::ReferenceCounted<AbstractSyntaxTree> ast)
			{
				walk(ast->getRoot());
			}

		private:
			std::map<std::string, VariantType> variables;

			double parseDouble(const std::string& str) const
			{
				std::stringstream ss;
				ss << str;
				double value;
				ss >> value;
				return value;
			}

			double parseDouble(const VariantType& vari) const
			{
				int index = vari.which();

				if (index == 3)
				{
					return boost::get<double>(vari);
				}
				else if (index == 4) /*string*/
				{
					std::string str = boost::get<std::string>(vari);
					return parseDouble(str);
				}

				assert(false);
				return 0;
			}

			void walk(buw::ReferenceCounted<AbstractSyntaxTreeNode> node)
			{
				if (node == nullptr)
				{
					return;
				}

				switch (node->getTokenType())
				{
				case eTokenType::PROGRAM:
				case eTokenType::STMNT:
					walk(node->right);
					walk(node->left);
					break;

				case eTokenType::ASSIGN:
					// Zuzuweisender Ausdruck befindet sich zur Rechten:
					walk(node->right);
					// Zur Linken ist die Variable:
					variables[node->left->token_.word] = node->right->value;
					// Die Zuweisung trägt selbst den zugewiesenen Wert:
					node->value = node->right->value;
					break;
				
				case eTokenType::IDENTIFIER:
					node->value = variables[node->token_.word];
					break;				
					
				case eTokenType::BOOL:
				case eTokenType::STRING:
				case eTokenType::NUMERIC:
					node->value = node->token_.word;
					break;

				case eTokenType::ADD:
					walk(node->right);
					walk(node->left);
					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x + y;
					}
					break;

				case eTokenType::SUB:
					walk(node->right);
					walk(node->left);
					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x - y;
					}
					break;

				case eTokenType::MUL:
					walk(node->right);
					walk(node->left);
					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x * y;
					}
					break;

				case eTokenType::DIV:
					walk(node->right);
					walk(node->left);
					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x / y;
					}
					break;

				case eTokenType::LT:
					walk(node->right);
					walk(node->left);
					node->left->value = parseDouble(node->left->value);
					node->right->value = parseDouble(node->right->value);

					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x < y;
					}
					break;

				case eTokenType::GT:
					walk(node->right);
					walk(node->left);
					node->left->value = parseDouble(node->left->value);
					node->right->value = parseDouble(node->right->value);

					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x > y;
					}
					break;

				case eTokenType::LEQ:
					walk(node->right);
					walk(node->left);
					node->left->value = parseDouble(node->left->value);
					node->right->value = parseDouble(node->right->value);

					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x <= y;
					}
					break;

				case eTokenType::GEQ:
					walk(node->right);
					walk(node->left);
					node->left->value = parseDouble(node->left->value);
					node->right->value = parseDouble(node->right->value);

					{
						double x = parseDouble(node->left->value);
						double y = parseDouble(node->right->value);

						node->value = x >= y;
					}
					break;

				case eTokenType::IF:
					// Der rechte Knoten ist der "COND"-Teilbaum:
					walk(node->right);
					// Wenn der COND-Knoten false zurückgibt, dann else ausführen:
					{
						bool condition = boost::get<bool>(node->right->value);
						if(!condition)  walk(node->left);
					}
					
					break;

				case eTokenType::COND:
					// Bedingungsausdruck berechnen:
					walk(node->right);
					node->value = node->right->value;

					// Wenn Bedingung erfüllt, dann Anweisung ausführen:
					{
						bool condition = boost::get<bool>(node->value);
						if(condition)  walk(node->left);
					}
					break;

				case eTokenType::FCALL:
					// Argumentenliste evaluieren:
					walk(node->right);
					if (node->left == nullptr)
					{
						std::cout << "null" << std::endl;
					}
					node->value = callFunction(node->left->token_, node->right->value);
					break;
				
				default:
					std::cout << tokenToString(node->getTokenType()) << std::endl;
					assert(false);
					break;
				}
			}

			VariantType callFunction(const token& t, VariantType arg)
			{
				if (t.word == std::string("print"))
				{
					std::cout << arg << std::endl;
				}
				else if (t.word == std::string("input"))
				{
					std::cout << arg << " ";
					double value = 0;
					std::cin >> value;
					return value;
				}
				else if (t.word == std::string("sqrt"))
				{
					double value = parseDouble(arg);
					return sqrt(value);
				}

				return 0;
			}

		private:
			std::map<std::string,int> symbolTable;
		};
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Interpreter;
}

#endif // end define OpenInfraPlatform_Infrastructure_Interpreter_477027e7_a49f_4552_83bf_6a4b700adf11_h
