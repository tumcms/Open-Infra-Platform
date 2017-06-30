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

#include "OpenInfraPlatform/Infrastructure/IfcPL/Parser.h"
#include "OpenInfraPlatform/Infrastructure/IfcPL/Interpreter.h"

using namespace OpenInfraPlatform::Infrastructure;

void compile()
{
	buw::ReferenceCounted<Lexer> lexer = std::make_shared<Lexer>(
		"C:/Users/no68koc/Desktop/code1.txt");

	std::cout << "##### Tokens: " << "#######################################" << std::endl;

	for (int i = 0; i < lexer->getTokenCount(); i++)
	{
		std::cout << lexer->getTokens()[i] << std::endl;
	}

	auto tokens = lexer->getTokens();

	buw::ReferenceCounted<Parser> parser = std::make_shared<Parser>(lexer);
	auto ast = parser->parse();

	std::cout << "##### Ast: " << "##########################################" << std::endl;

	std::cout << ast << std::endl;

	std::cout << "##### Program Output: " << "###############################" << std::endl;

	buw::ReferenceCounted<Interpreter> interpreter = std::make_shared<Interpreter>();
	interpreter->execute(ast);

	system("pause");
}