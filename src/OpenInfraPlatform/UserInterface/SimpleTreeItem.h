#pragma once
#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include "OpenInfraPlatform\IfcAlignment1x1\model\Model.h"

#include <visit_struct/visit_struct.hpp>

namespace OpenInfraPlatform {

	namespace UserInterface {

			class TreeItem {
			public:
				TreeItem(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> &data, TreeItem* parent = nullptr);
				virtual ~TreeItem();

				void appendChild(TreeItem *child);
				TreeItem *child(int row);
				int childCount() const;
				int columnCount() const;
				QVariant data(int column) const;
				int row() const;
				TreeItem *parentItem();

				void setItemData(QList<QVariant> itemData);

				void createChildren();

					private:

						QList<TreeItem*> m_childItems;
						QList<QVariant> m_itemData;
						TreeItem *m_parentItem;

						std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> m_managedData = nullptr;

						//Helper struct which parses the attributes of a derived entity which are IfcAlignment1x1Types and hold flat values.
						struct parseType {

							void operator()(const char* name, std::string string)
							{
							std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
							TreeItem* child = new TreeItem(ptr, thisPtr);
							QList<QVariant> itemData;
							itemData << QVariant(name) << QVariant(string.data()) << QVariant("std::string");
							child->setItemData(itemData);
							thisPtr->appendChild(child);
							}

							//Function operator() which creates a statement from a boolean value.
							void operator()(const char* name, bool value)
							{

							}

							void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> value)
							{
								TreeItem* child = new TreeItem(std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object>(value), thisPtr);
								QList<QVariant> itemData;
								itemData << QVariant(name) << QVariant(value->getId()) << QVariant(value->classname());
								child->setItemData(itemData);
								thisPtr->appendChild(child);
							}

							template <class T> typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, int>::value, void>::type
									operator()(const char* name, T value)
							 {
							std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
							TreeItem* child = new TreeItem(ptr, thisPtr);
							QList<QVariant> itemData;
							itemData << QVariant(name) << QVariant(value) << QVariant(typeid(value).name());
							child->setItemData(itemData);
							thisPtr->appendChild(child);
							}

							//Function operator() which covers std::shared_ptr<T>.
							//This is a dummy function required by the compiler but which mustn't be called. Throws an exception.
							template <typename T>
							void operator()(const char* name, std::shared_ptr<T> &ptr)
							{

							}

							//Function operator() which covers std::vector<T>.
							//This is a function required by the compiler but is not implemented and mustn't be called. Throws an exception.
							template <typename T>
							void operator()(const char* name, std::vector<T> vector)
							{

							}
						
							//Function operator() which covers everything that is not an int, float/double, string, boolean, pointer or vector.
							//This function also takes enums, since alot of classes derived from IfcAlignment1x1Type have a corresponding enum class, which is derived from it.
							template <class T> typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, int>::value, void>::type
								operator()(const char* name, T t)
							{

							}

							TreeItem* thisPtr = nullptr;

						} parser_;

		};


					//template <typename T> class TreeItemT : public TreeItem {
					//public:
					//	TreeItemT(T &data, TreeItem* parent) : TreeItem(parent), m_managedData(data)
					//	{
					//		auto func = [&](auto item)->void {
					//			visit_struct::for_each(item, [&](const char* name, auto &value) {
					//				TreeItemT<decltype(value)>* child = new TreeItemT<decltype(value)>(value, this);
					//				QList<QVariant> itemData;
					//				itemData << QVariant(name) << QVariant("") << QVariant(typeid(value).name());
					//				child->setItemData(itemData);
					//				this->appendChild(child);
					//			});
					//		};
					//		
					//		if(visit_struct::traits::is_visitable<T>::value) {
					//			OpenInfraPlatform::IfcAlignment1x1::castToVisitableAndCall<decltype(func),void>(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(&m_managedData), func);
					//		} else {
					//		
					//		}
					//	}
					//			
					//	void createChildren()
					//	{
					//		visit_struct::for_each(m_managedData, [&](const char* name, auto &value) {
					//			TreeItemT<decltype(value)>* child = new TreeItemT<decltype(value)>(value, this);
					//			QList<QVariant> itemData;
					//			itemData << QVariant(name) << QVariant("") << QVariant(typeid(value).name());
					//			child->setItemData(itemData);
					//			this->appendChild(child);
					//		});
					//	}
					//	
					//	T m_managedData;
					//};		

	}

}

#endif // TREEITEM_H