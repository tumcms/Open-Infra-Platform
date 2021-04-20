/*
	Copyright (c) 2021 Technical University of Munich
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

#ifndef IFCTREEITEM_H
#define IFCTREEITEM_H

#include "EXPRESS/EXPRESSReference.h"
#include <QVariant>


namespace OpenInfraPlatform {
	namespace UserInterface {

		class IfcTreeItem
		{
		public:
			IfcTreeItem(std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity> data, std::shared_ptr<IfcTreeItem> parentItem = nullptr);
			~IfcTreeItem();

			void appendchild(std::shared_ptr<IfcTreeItem> child);

			std::shared_ptr<IfcTreeItem> child(int row);
			int childCount() const;
			int columnCount() const;
			QVariant data(int row, int column) const;
			int row() const;
			std::shared_ptr<IfcTreeItem> parentItem();
			QString getIfcClassName() const;

		private:
			QList<std::shared_ptr<IfcTreeItem>> childItems_;
			std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity> data_;
			std::shared_ptr<IfcTreeItem> parentItem_;

			struct getAttributeDescription;
		};
	}
}


#endif //IFCTREITEM_H

namespace oip
{
	using OpenInfraPlatform::UserInterface::IfcTreeItem;
}