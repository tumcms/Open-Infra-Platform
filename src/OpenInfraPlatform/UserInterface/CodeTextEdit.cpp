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

#include "CodeTextEdit.h"

OpenInfraPlatform::UserInterface::CodeTextEdit::CodeTextEdit()
{
	//setStyleSheet("font: 12pt \"Times New Roman\";");
}

void OpenInfraPlatform::UserInterface::CodeTextEdit::wheelEvent(QWheelEvent *e)
{
	if (e->modifiers() & Qt::ControlModifier)
	{
		const int delta = e->delta();
		if (delta < 0)
			zoomOut();
		else if (delta > 0)
		{
			zoomIn();
		}

		return;
	}

	QTextEdit::wheelEvent(e);
}

void OpenInfraPlatform::UserInterface::CodeTextEdit::makeDrag()
{

}

void OpenInfraPlatform::UserInterface::CodeTextEdit::dropEvent(QDropEvent *de)
{
	if (de->mimeData()->hasUrls())
	{
		QString url = de->mimeData()->urls()[0].toString();
		url = url.right(url.length() - 8);

		std::cout << url.toLatin1().data() << std::endl;

		QFile file(url.toLatin1().data());
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			throw std::runtime_error("Could not open file.");

		QTextStream in(&file);
		QString line = in.readLine();
		while (!line.isNull())
		{
			this->append(line);
			line = in.readLine();
		}
	}
}
