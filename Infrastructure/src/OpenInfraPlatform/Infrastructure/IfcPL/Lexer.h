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
#ifndef OpenInfraPlatform_Infrastructure_Lexer_e79afd2d_748d_4cb3_a4f3_e9a7202770c4_h
#define OpenInfraPlatform_Infrastructure_Lexer_e79afd2d_748d_4cb3_a4f3_e9a7202770c4_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
//#include <BlueFramework/Engine/Lexer/SimpleLexer.h>
#include <cassert>
#include <boost/noncopyable.hpp>
#include "token.h"
#include <vector>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API Lexer
		{
		public:
			Lexer(const std::string& filename) :
				frontIndex(0)
			{
				/*
				buw::SimpleLexer sl(filename.c_str());
				sl.SetIgnoreWhitespace(true);
				buw::Token token;

				int tokenCount = 0;

				// while (sl.ReadToken(token))
				// {
				//	std::cout << token.GetStringValue() << std::endl;
				// }

				// read tokens
				while(sl.ReadToken(token))
				{
					//  IDENTIFIER
					if ( token.GetType() == buw::eTokenType::Identifier )
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();
						t.type = eTokenType::IDENTIFIER;

						if (t.word == std::string("if"))
						{
							t.type = eTokenType::IF;
						} 
						else if (t.word == std::string("else"))
						{
							t.type = eTokenType::ELSE;
						}
						else if (t.word == std::string("<="))
						{
							t.type = eTokenType::LEQ;
						}
						else if (t.word == std::string(">="))
						{
							t.type = eTokenType::GEQ;
						}
						else if (t.word == std::string("true"))
						{
							t.type = eTokenType::BOOL;
						}
						else if (t.word == std::string("false"))
						{
							t.type = eTokenType::BOOL;
						}

						tokens_.push_back(t);
						continue;
					}

					// NUMERIC
					if ( token.GetType() == buw::eTokenType::Integer )
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();
						t.type = eTokenType::NUMERIC;

						if (t.word == std::string("-"))
						{
							t.type = eTokenType::SUB;
						}

						tokens_.push_back(t);
						continue;
					}

					if ( token.GetType() == buw::eTokenType::Float )
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();
						t.type = eTokenType::NUMERIC;

						tokens_.push_back(t);
						continue;
					}

					if ( token.GetType() == buw::eTokenType::Left_Parenthesis)
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();
						t.type = eTokenType::BRACKET_OPEN;

						tokens_.push_back(t);
						continue;
					}

					if ( token.GetType() == buw::eTokenType::Right_Parenthesis)
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();
						t.type = eTokenType::BRACKET_CLOSE;

						tokens_.push_back(t);
						continue;
					}

					if ( token.GetType() == buw::eTokenType::Left_Brace)
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();
						t.type = eTokenType::BRACE_OPEN;

						tokens_.push_back(t);
						continue;
					}

					if ( token.GetType() == buw::eTokenType::Right_Brace)
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();
						t.type = eTokenType::BRACE_CLOSE;

						tokens_.push_back(t);
						continue;
					}

					if ( token.GetType() == buw::eTokenType::Unknown )
					{
						OpenInfraPlatform::Infrastructure::token t;

						t.line = token.GetRow();
						t.pos = token.GetColumn();
						t.word = token.GetStringValue().toStdString();

						if (t.word == std::string("="))
						{
							t.type = eTokenType::ASSIGN;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("("))
						{
							t.type = eTokenType::BRACKET_OPEN;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string(")"))
						{
							t.type = eTokenType::BRACKET_CLOSE;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string(";"))
						{
							t.type = eTokenType::SEMICOLON;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("+"))
						{
							t.type = eTokenType::ADD;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("-"))
						{
							t.type = eTokenType::SUB;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("*"))
						{
							t.type = eTokenType::MUL;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("/"))
						{
							t.type = eTokenType::DIV;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("{"))
						{
							t.type = eTokenType::BRACE_OPEN;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("<"))
						{
							t.type = eTokenType::LT;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string(">"))
						{
							t.type = eTokenType::GT;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("}"))
						{
							t.type = eTokenType::BRACE_CLOSE;
							tokens_.push_back(t);
							continue;
						}

						if (t.word == std::string("\""))
						{
							// extract string
							std::stringstream ss;

							// Lesen bis wieder " kommt
							bool firstRun = true;

							sl.SetIgnoreWhitespace(false); // whitespace are important now

							bool canRead = sl.ReadToken(token);
							assert(canRead);

							while (firstRun || token.GetStringValue() != "\"")
							{
								ss << token.GetStringValue();

								firstRun = false;

								bool canRead = sl.ReadToken(token);
								assert(canRead);
							} 

							t.type = eTokenType::STRING;
							t.word = ss.str();
							t.line = token.GetRow();
							t.pos = token.GetColumn();

							sl.SetIgnoreWhitespace(true); // whitespace are important now

							tokens_.push_back(t);
							continue;
						}

						assert(false);
					}
				}
				*/
			}

			void addToken(const std::string& word, 
				const eTokenType::Enum type, 
				const int line, 
				const int position)
			{
				OpenInfraPlatform::Infrastructure::token t;

				t.line = line;
				t.pos = position;
				t.word = word;
				t.type = type;

				tokens_.push_back(t);
			}

			std::vector<token> getTokens()
			{
				return tokens_;
			}

			int getTokenCount() const
			{
				return static_cast<int>(tokens_.size());
			}

			bool hasMoreTokens() const
			{
				if (frontIndex < tokens_.size())
				{
					return true;
				}
				else
					return false;
			}

			token peekToken() const
			{
				assert(tokens_.size() > 0);

				if (frontIndex < tokens_.size())
				{
					auto t = tokens_[frontIndex];
					return t;
				}
				else
				{
					token t;
					t.line = -1;
					t.pos = -1;
					t.word = "";
					t.type = eTokenType::END;

					return t;
				}
			}

			token peekNextToken()
			{
				assert(tokens_.size() > 1);

				auto t = tokens_[frontIndex+1];
				return t;
			}

			token nextToken()
			{
				assert(tokens_.size() > 0);
				token t = tokens_[frontIndex];
				frontIndex++;
				return t;
			}

		private:			
			int frontIndex;
			std::vector<token> tokens_;
		}; // end class Lexer
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Lexer;
}

#endif // end define OpenInfraPlatform_Infrastructure_Lexer_e79afd2d_748d_4cb3_a4f3_e9a7202770c4_h
