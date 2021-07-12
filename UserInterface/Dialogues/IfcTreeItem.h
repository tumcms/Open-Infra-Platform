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
#include <QList>


namespace OpenInfraPlatform {
	namespace UserInterface {

		class IfcTreeItem
		{
		public:
			explicit IfcTreeItem(OpenInfraPlatform::EarlyBinding::EXPRESSEntity *data, IfcTreeItem *parentItem);
			explicit IfcTreeItem(const QList<QVariant> &data, IfcTreeItem *parentItem = 0);
			~IfcTreeItem();

			void appendChild(IfcTreeItem *child);

			IfcTreeItem *child(int row);
			int childCount() const;
			int columnCount() const;
			QVariant data(int column) const;
			int row() const;
			IfcTreeItem *parentItem();
			QString getIfcClassName() const;

			//void setItemData(QList<QVariant> itemData);
			//void createChildren();

		private:
			QList<IfcTreeItem*> childItems_;
			OpenInfraPlatform::EarlyBinding::EXPRESSEntity *data_;
			QList<QVariant> itemData_;
			IfcTreeItem *parentItem_;

			//struct getAttributeDescription;

			//std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSObject> m_managedData = nullptr;

			////Helper struct which parses the attributes of a derived entity which are IfcAlignment1x1Types and hold flat values.
			//struct parseType {

			//	void operator()(const char* name, std::string string)
			//	{
			//		std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSObject> ptr = nullptr;
			//		TreeItem* child = new TreeItem(ptr, thisPtr);
			//		QList<QVariant> itemData;
			//		itemData << QVariant(name) << QVariant(string.data()) << QVariant("std::string");
			//		child->setItemData(itemData);
			//		thisPtr->appendChild(child);
			//	}

			//	//Function operator() which creates a statement from a boolean value.
			//	void operator()(const char* name, bool value)
			//	{
			//		std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSObject> ptr = nullptr;
			//		TreeItem* child = new TreeItem(ptr, thisPtr);
			//		QList<QVariant> itemData;
			//		itemData << QVariant(name) << QVariant(value) << QVariant("bool");
			//		child->setItemData(itemData);
			//		thisPtr->appendChild(child);
			//	}

			//	void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity> value)
			//	{
			//		TreeItem* child = new TreeItem(std::static_pointer_cast<OpenInfraPlatform::EarlyBinding::EXPRESSObject>(value), thisPtr);
			//		QList<QVariant> itemData;
			//		itemData << QVariant(name) << QVariant(value ? value->getId() : -1); //<< QVariant(value ? value->classname() : "nullptr");
			//		child->setItemData(itemData);
			//		thisPtr->appendChild(child);
			//	}

			//	//TODO: Get value stored in type
			//	void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSType> value)
			//	{
			//		TreeItem* child = new TreeItem(std::static_pointer_cast<OpenInfraPlatform::EarlyBinding::EXPRESSObject>(value), thisPtr);
			//		QList<QVariant> itemData;

			//		//std::stringstream ss;
			//		if (value)
			//			//readStepData(std::string& arg)
			//			//value->getStepData(ss);


			//		//auto classname = value->classname(); //Gibt z.B. IfcLabel o.ä. zurück
			//		//static_cast<classname>(value);
			//		//auto castedValue = value.m_value; //gibt m_value zurück aus IfcLabel, also den eigentlichen Wert, der als String o.ö. gespeichert ist
			//		//auto castedType = typeid(castedValue).name(); //gibt den Typ von m_value zurück, also z.B. String
			//		//
			//		//if (castedType == "string" || "char")
			//		//	QVariant value2 = QVariant(castedValue.data());
			//		//	return value2;
			//		//if (castedType == "bool" || "int" || "float" || "double")
			//		//	QVariant value2 = QVariant(castedValue);
			//		//	return value2;

			//		//itemData << QVariant(name) << QVariant(ss.str().data()) << QVariant(value ? value->classname() : "nullptr");
			//			itemData << QVariant(name) << QVariant("m_type"); //<< QVariant(value ? value->classname() : "nullptr");
			//			//itemData << QVariant(name) << QVariant("m_type") << QVariant(value ? value->classname() : "nullptr");

			//		child->setItemData(itemData);
			//		thisPtr->appendChild(child);
			//	}

			//	//template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractSelect, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
			//	//operator()(const char* name, std::shared_ptr<T> value)
			//	//{
			//	//	std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
			//	//	TreeItem* child = new TreeItem(ptr, thisPtr);
			//	//	QList<QVariant> itemData;
			//	//	itemData << QVariant(name) << QVariant("m_select") << QVariant(typeid(T).name());
			//	//	child->setItemData(itemData);
			//	//	thisPtr->appendChild(child);
			//	//}

			//	//template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::EarlyBinding::IfcAlignment1x1AbstractSelect, T>::value && !std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSType, T>::value && !std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSEntity, T>::value, void>::type
			//	//	operator()(const char* name, std::shared_ptr<T> value)
			//	template <class T> typename std::enable_if<!std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSType, T>::value && !std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSEntity, T>::value, void>::type
			//		operator()(const char* name, std::shared_ptr<T> value)
			//	{
			//		std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSObject> ptr = nullptr;
			//		TreeItem* child = new TreeItem(ptr, thisPtr);
			//		QList<QVariant> itemData;

			//		//if !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
			//		//{ 
			//		//std::stringstream ss;
			//		//if(value)
			//		//	value->getStepData(ss);
			//		//return ss;
			//		//}

			//		//itemData << QVariant(name) << QVariant(ss.str().data()) << QVariant(typeid(T).name());
			//		itemData << QVariant(name) << QVariant("m_select") << QVariant(typeid(T).name());
			//		child->setItemData(itemData);
			//		thisPtr->appendChild(child);
			//	}

			//	//void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractEnum> value)
			//	//{
			//	//	std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
			//	//	TreeItem* child = new TreeItem(ptr, thisPtr);
			//	//	QList<QVariant> itemData;
			//	//	itemData << QVariant(name) << QVariant("m_enum") << QVariant(value->classname());
			//	//	child->setItemData(itemData);
			//	//	thisPtr->appendChild(child);
			//	//}

			//	template <class T> typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, int>::value, void>::type
			//		operator()(const char* name, T value)
			//	{
			//		std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
			//		TreeItem* child = new TreeItem(ptr, thisPtr);
			//		QList<QVariant> itemData;
			//		itemData << QVariant(name) << QVariant(value) << QVariant(typeid(value).name());
			//		child->setItemData(itemData);
			//		thisPtr->appendChild(child);
			//	}


			//	//Function operator() which covers std::shared_ptr<T>.
			//	//template <typename T>
			//	//void operator()(const char* name, std::shared_ptr<T> &ptr)
			//	//{
			//	//}

			//	//Function operator() which covers std::vector<T>.
			//	template <typename T>
			//	void operator()(const char* name, std::vector<T> vector)
			//	{
			//		std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSObject> ptr = nullptr;
			//		TreeItem* child = new TreeItem(ptr, thisPtr);
			//		QList<QVariant> itemData;
			//		itemData << QVariant(name) << QVariant("vector") << QVariant(typeid(T).name());
			//		child->setItemData(itemData);
			//		thisPtr->appendChild(child);

			//		int i = 0;
			//		for (T it : vector) {
			//			TreeItem* vectorChild = new TreeItem(ptr, child);
			//			QList<QVariant> vectorData;
			//			//doesn't work yet since it is of type T and that requires the parser again (rekusiver aufruf)
			//			//T value = it;
			//			//
			//			//auto parse = [&](auto item) {
			//			//	visit_struct::for_each(item, parser_);
			//			//};
			//			//
			//			//if(ptr && ptr.get() != nullptr) {
			//			//	if(std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(ptr))
			//			//		OpenInfraPlatform::IfcAlignment1x1::castToVisitableAndCall<decltype(parse), void>(std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(ptr), parse);
			//			//}
			//			//vectorData << QVariant(i++) << QVariant(value) << QVariant(typeid(value).name());
			//			vectorData << QVariant(i++) << QVariant("") << QVariant("");
			//			vectorChild->setItemData(vectorData);
			//			child->appendChild(vectorChild);
			//		}
			//	}

			//	//Function operator() which covers everything that is not an int, float/double, string, boolean, pointer or vector.
			//	//This function also takes enums, since alot of classes derived from IfcAlignment1x1Type have a corresponding enum class, which is derived from it.
			//	//template <class T> typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, int>::value, void>::type
			//	//	operator()(const char* name, T t)
			//	//{
			//	//
			//	//}

			//	TreeItem* thisPtr = nullptr;

			//} parser_;
		  
		};
	}
}

#endif //IFCTREEITEM_H

namespace oip
{
	using OpenInfraPlatform::UserInterface::IfcTreeItem;
}