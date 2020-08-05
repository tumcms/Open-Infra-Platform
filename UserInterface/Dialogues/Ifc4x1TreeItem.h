/*
Copyright (c) 2018 Technical University of Munich
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

#ifndef Ifc4X1TREEITEM_H
#define Ifc4X1TREEITEM_H

#include <QList>
#include <QVariant>

namespace OpenInfraPlatform {
	namespace UserInterface {

		class Ifc4x1TreeItem
		{
		public:
			explicit Ifc4x1TreeItem(std::map<size_t, std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>> data, std::shared_ptr<Ifc4x1TreeItem> parentItem = nullptr);
			~Ifc4x1TreeItem();

			void appendChild(shared_ptr<Ifc4x1TreeItem> child);

			shared_ptr<Ifc4x1TreeItem> child(int row);
			int childCount() const;
			int columnCount() const;
			QVariant data(int column, int row) const;
			int row() const;
			shared_ptr<Ifc4x1TreeItem> parentItem();
			std::string getIfcClassName();

		private:
			QList<shared_ptr<Ifc4x1TreeItem>> childItems_;
			std::map<size_t, std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>> data_;
			shared_ptr<Ifc4x1TreeItem> parentItem_;

			struct getAttributeDescription;
		};

	}
}
#endif  // TREEITEM_H

namespace buw
{
	using OpenInfraPlatform::UserInterface::Ifc4x1TreeItem;
}
