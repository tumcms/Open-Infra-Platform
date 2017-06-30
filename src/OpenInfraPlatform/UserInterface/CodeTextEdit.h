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
#ifndef OpenInfraPlatform_UserInterface_CodeTextEdit_5a1d54d3_7a91_40dc_8452_7bc0041964da_h
#define OpenInfraPlatform_UserInterface_CodeTextEdit_5a1d54d3_7a91_40dc_8452_7bc0041964da_h

#include <boost/noncopyable.hpp>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QUrl>
#include <QTextStream>
#include <QDropEvent>
#include <QMimeData>
#include "highlighter.h"
#include <iostream>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class CodeTextEdit : public QTextEdit
		{
			Q_OBJECT;

		public:
			CodeTextEdit();

			void wheelEvent(QWheelEvent *e);

		public Q_SLOTS:
			void makeDrag();

		protected:
			void dropEvent(QDropEvent *de);
		};
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::CodeTextEdit;
}

#endif // end define OpenInfraPlatform_UserInterface_CodeTextEdit_5a1d54d3_7a91_40dc_8452_7bc0041964da_h