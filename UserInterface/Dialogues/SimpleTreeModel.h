#pragma once
#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
#include "reader/IFC2X3Reader.h"
#include "EMTIFC2X3EntityTypes.h"
#include "IFC2X3.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4
#include "reader/IFC4Reader.h"
#include "EMTIFC4EntityTypes.h"
#include "IFC4.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
#include "reader/IFC4X1Reader.h"
#include "EMTIFC4X1EntityTypes.h"
#include "IFC4X1.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
#include "reader/IFC4X3_RC1Reader.h"
#include "EMTIFC4X3_RC1EntityTypes.h"
#include "IFC4X3_RC1.h"
#include "EXPRESS/EXPRESSReference.h"
#endif

#include <QAbstractItemModel>
#include <QString>
#include <QModelIndex>
#include <QVariant>


namespace OpenInfraPlatform {
	namespace UserInterface {
		class TreeItem;

		class TreeModel : public QAbstractItemModel {
			Q_OBJECT;

		public:
			TreeModel(std::map<size_t, std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>>& data, QObject *parent = 0);
			//explicit TreeModel(const QString &data, QObject *parent = 0);
			~TreeModel();

			QVariant data(const QModelIndex &index, int role) const override;

			Qt::ItemFlags flags(const QModelIndex &index) const override;

			QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

			QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

			QModelIndex parent(const QModelIndex &index) const override;

			int rowCount(const QModelIndex &parent = QModelIndex()) const override;

			int columnCount(const QModelIndex &parent = QModelIndex()) const override;

		private:
			//void setupModelData(const QStringList &lines, TreeItem *parent);

			TreeItem *rootItem;
			//std::vector<shared_ptr<TreeItem>> data_;
		};
	}
}
