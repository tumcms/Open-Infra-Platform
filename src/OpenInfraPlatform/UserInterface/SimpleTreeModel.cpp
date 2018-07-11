#include "SimpleTreeItem.h"
#include "SimpleTreeModel.h"

#include <QStringList>
#include <sstream>

//OpenInfraPlatform::UserInterface::TreeModel::TreeModel(const QString &data, QObject *parent)
//	: QAbstractItemModel(parent)

OpenInfraPlatform::UserInterface::TreeModel::TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> &data, QObject *parent)
	: QAbstractItemModel(parent) 
{
	QList<QVariant> rootData;
	//std::pair<int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> rootData;
	rootData << "Title" << "Summary";
	//rootData = std::pair<int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>>(-1, );
	rootItem = new TreeItem<QList<QVariant>>(rootData);
	//setupModelData(data.split(QString("\n")), rootItem);
}

OpenInfraPlatform::UserInterface::TreeModel::~TreeModel()
{
	delete rootItem;
}

Qt::ItemFlags OpenInfraPlatform::UserInterface::TreeModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
		return 0;

	return QAbstractItemModel::flags(index);
}

QVariant OpenInfraPlatform::UserInterface::TreeModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->data(section);

	return QVariant();
}

//void OpenInfraPlatform::UserInterface::TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
//{
//	QList<TreeItem*> parents;
//	QList<int> indentations;
//	parents << parent;
//	indentations << 0;
//
//	int number = 0;
//
//	while(number < lines.count()) {
//		int position = 0;
//		while(position < lines[number].length()) {
//			if(lines[number].at(position) != ' ')
//				break;
//			position++;
//		}
//
//		QString lineData = lines[number].mid(position).trimmed();
//
//		if(!lineData.isEmpty()) {
//			// Read the column data from the rest of the line.
//			QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
//			QList<QVariant> columnData;
//			for(int column = 0; column < columnStrings.count(); ++column)
//				columnData << columnStrings[column];
//
//			if(position > indentations.last()) {
//				// The last child of the current parent is now the new parent
//				// unless the current parent has no children.
//
//				if(parents.last()->childCount() > 0) {
//					parents << parents.last()->child(parents.last()->childCount() - 1);
//					indentations << position;
//				}
//			}
//			else {
//				while(position < indentations.last() && parents.count() > 0) {
//					parents.pop_back();
//					indentations.pop_back();
//				}
//			}
//
//			// Append a new item to the current parent's list of children.
//			parents.last()->appendChild(new TreeItem(columnData, parents.last()));
//		}
//
//		++number;
//	}
//}