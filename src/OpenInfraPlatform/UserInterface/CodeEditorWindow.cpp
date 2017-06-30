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

#include "CodeEditorWindow.h"

#include "OpenInfraPlatform/Infrastructure/IfcPL/Parser.h"
#include "OpenInfraPlatform/Infrastructure/IfcPL/Interpreter.h"

OpenInfraPlatform::UserInterface::CodeEditorWindow::CodeEditorWindow( QWidget *parent /*= nullptr*/ ) :
	ui_(new Ui::CodeEditorWindow)
{
	ui_->setupUi(this);

	setupEditor();
	ui_->verticalLayout->addWidget(editor_);
}

void OpenInfraPlatform::UserInterface::CodeEditorWindow::changeEvent(QEvent* evt)
{
	if (evt->type() == QEvent::LanguageChange)
	{
		ui_->retranslateUi(this);
	}
	else
	{
		QWidget::changeEvent(evt);
	}
}

void OpenInfraPlatform::UserInterface::CodeEditorWindow::setupEditor()
{
	QFont font;
	//font.setFamily("Consolas");
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(10);

	editor_ = new CodeTextEdit;
	editor_->setFont(font);

	highlighter_ = new Highlighter(editor_->document());

	editor_->setPlainText(
		"print(\"Hello World!\");"
	);
}

void OpenInfraPlatform::UserInterface::CodeEditorWindow::on_actionExit_triggered()
{
	close();
}

void OpenInfraPlatform::UserInterface::CodeEditorWindow::on_actionExample1_triggered()
{
	editor_->setPlainText(
		"A = input(\"Geben Sie eine Zahl ein: \");"
	);
}

void OpenInfraPlatform::UserInterface::CodeEditorWindow::on_pushButtonExecute_clicked()
{
	system("cls");

	using namespace OpenInfraPlatform::Infrastructure;

	QFile file("code1.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out << editor_->toPlainText().toStdString().c_str();
	file.close(); 
	
	buw::ReferenceCounted<Lexer> lexer = std::make_shared<Lexer>("code1.txt");

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
}

void OpenInfraPlatform::UserInterface::CodeEditorWindow::on_actionHello_World_triggered()
{
	editor_->setPlainText(
		"print(\"Hello World!\");"
	);
}

void OpenInfraPlatform::UserInterface::CodeEditorWindow::on_actionEuclidean_triggered()
{
	editor_->setPlainText(
		"print(\"Euclidean\");"								"\n"
		"a = input(\"Type a number (a): \");"				"\n"
		"b = input(\"Type a number (b): \");"				"\n"
		"print(a + b);"										"\n"
		);
}
