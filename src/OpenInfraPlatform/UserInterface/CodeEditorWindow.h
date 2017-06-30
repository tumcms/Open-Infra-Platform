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
#ifndef OpenInfraPlatform_UserInterface_CodeEditorWindow_5f48a20a_6127_4e9c_b8b9_01b44ac3c30a_h
#define OpenInfraPlatform_UserInterface_CodeEditorWindow_5f48a20a_6127_4e9c_b8b9_01b44ac3c30a_h

#include "ui_CodeEditorWindow.h"
#include <boost/noncopyable.hpp>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QUrl>
#include <QTextStream>
#include <QDropEvent>
#include <QMimeData>
#include "highlighter.h"
#include "OpenInfraPlatform/UserInterface/CodeTextEdit.h"
#include <iostream>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class CodeEditorWindow : public QMainWindow
		{
			Q_OBJECT

		public:
			CodeEditorWindow(QWidget *parent = nullptr);

			virtual ~CodeEditorWindow()	{}

		public Q_SLOTS:
			void on_actionExit_triggered();
			void on_actionExample1_triggered();
			void on_pushButtonExecute_clicked();
			void on_actionHello_World_triggered();
			void on_actionEuclidean_triggered();

		protected:
			virtual void changeEvent(QEvent* evt) override;

		private:
			void setupEditor();

		private:
			Ui::CodeEditorWindow*	ui_;
			CodeTextEdit*			editor_;
			Highlighter*			highlighter_;
		private:
		}; // end class CodeEditorWindow
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::CodeEditorWindow;
}

#endif // end define OpenInfraPlatform_UserInterface_CodeEditorWindow_5f48a20a_6127_4e9c_b8b9_01b44ac3c30a_h
