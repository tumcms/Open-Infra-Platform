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
					std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
					TreeItem* child = new TreeItem(ptr, thisPtr);
					QList<QVariant> itemData;
					itemData << QVariant(name) << QVariant(value) << QVariant("bool");
					child->setItemData(itemData);
					thisPtr->appendChild(child);
				}

				void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> value)
				{
					TreeItem* child = new TreeItem(std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object>(value), thisPtr);
					QList<QVariant> itemData;
					itemData << QVariant(name) << QVariant(value ? value->getId() : -1) << QVariant(value ? value->classname() : "nullptr");
					child->setItemData(itemData);
					thisPtr->appendChild(child);
				}

				template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractEnum, T>::value && std::is_default_constructible<T>::value, void>::type
					operator()(const char* name, std::shared_ptr<T> value) {
				TreeItem* child = new TreeItem(std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object>(value), thisPtr);
				QList<QVariant> itemData;
				if (value && typeid(value->m_value).name() == "std::string") {
					void* data = &(value->m_value);
					itemData << QVariant(name) << QVariant(static_cast<std::string*>(data)->data()) << QVariant(value ? value->classname() : "nullptr");
				}
				else
					itemData << QVariant(name) << QVariant(value ? value->m_value : "empty" ) << QVariant(value ? value->classname() : "nullptr");

				child->setItemData(itemData);
				thisPtr->appendChild(child);
				}

		
				//TODO: Get value stored in type
				void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type> value)
				{
					TreeItem* child = new TreeItem(std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object>(value), thisPtr);
					QList<QVariant> itemData;
					
					std::stringstream ss;
					if(value)
						//readStepData(std::string& arg)
						value->getStepData(ss);
					

					//auto classname = value->classname(); //Gibt z.B. IfcLabel o.ä. zurück
					//static_cast<classname>(value);
					//auto castedValue = value.m_value; //gibt m_value zurück aus IfcLabel, also den eigentlichen Wert, der als String o.ö. gespeichert ist
					//auto castedType = typeid(castedValue).name(); //gibt den Typ von m_value zurück, also z.B. String
					//
					//if (castedType == "string" || "char")
					//	QVariant value2 = QVariant(castedValue.data());
					//	return value2;
					//if (castedType == "bool" || "int" || "float" || "double")
					//	QVariant value2 = QVariant(castedValue);
					//	return value2;
					
					//itemData << QVariant(name) << QVariant(ss.str().data()) << QVariant(value ? value->classname() : "nullptr");
					itemData << QVariant(name) << QVariant("type") << QVariant(value ? value->classname() : "nullptr");
					//itemData << QVariant(name) << QVariant("m_type") << QVariant(value ? value->classname() : "nullptr");

					child->setItemData(itemData);
					thisPtr->appendChild(child);
				}

				//template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractSelect, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
				//operator()(const char* name, std::shared_ptr<T> value)
				//{
				//	std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
				//	TreeItem* child = new TreeItem(ptr, thisPtr);
				//	QList<QVariant> itemData;
				//	itemData << QVariant(name) << QVariant("m_select") << QVariant(typeid(T).name());
				//	child->setItemData(itemData);
				//	thisPtr->appendChild(child);
				//}

				template <class T> typename std::enable_if<std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractSelect, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value && !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
					operator()(const char* name, std::shared_ptr<T> value)
				{
					std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
					TreeItem* child = new TreeItem(ptr, thisPtr);
					QList<QVariant> itemData;
				
					//if !std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Type, T>::value, void>::type
					//{ 
					//std::stringstream ss;
					//if(value)
					//	value->getStepData(ss);
					//return ss;
					//}
				
					//itemData << QVariant(name) << QVariant(ss.str().data()) << QVariant(typeid(T).name());
					itemData << QVariant(name) << QVariant("m_select") << QVariant(typeid(T).name());
					child->setItemData(itemData);
					thisPtr->appendChild(child);
				}

				//void operator()(const char* name, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1AbstractEnum> value)
				//{
				//	std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
				//	TreeItem* child = new TreeItem(ptr, thisPtr);
				//	QList<QVariant> itemData;
				//	itemData << QVariant(name) << QVariant("m_enum") << QVariant(value->classname());
				//	child->setItemData(itemData);
				//	thisPtr->appendChild(child);
				//}

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
				//template <typename T>
				//void operator()(const char* name, std::shared_ptr<T> &ptr)
				//{
				//}

				//Function operator() which covers std::vector<T>.
				template <typename T>
				void operator()(const char* name, std::vector<T> vector)
				{
					std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
					TreeItem* child = new TreeItem(ptr, thisPtr);
					QList<QVariant> itemData;
					itemData << QVariant(name) << QVariant("vector") << QVariant(typeid(T).name());
					child->setItemData(itemData);
					thisPtr->appendChild(child);

					int i = 0;
					for(T it : vector) {
						TreeItem* vectorChild = new TreeItem(ptr, child);
						QList<QVariant> vectorData;
						//doesn't work yet since it is of type T and that requires the parser again (rekusiver aufruf)
						//T value = it;
						//
						//auto parse = [&](auto item) {
						//	visit_struct::for_each(item, parser_);
						//};
						//
						//if(ptr && ptr.get() != nullptr) {
						//	if(std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(ptr))
						//		OpenInfraPlatform::IfcAlignment1x1::castToVisitableAndCall<decltype(parse), void>(std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(ptr), parse);
						//}
						//vectorData << QVariant(i++) << QVariant(value) << QVariant(typeid(value).name());
						vectorData << QVariant(i++) << QVariant("") << QVariant("");
						vectorChild->setItemData(vectorData);
						child->appendChild(vectorChild);
					}
				}

				//Function operator() which covers everything that is not an int, float/double, string, boolean, pointer or vector.
				//This function also takes enums, since alot of classes derived from IfcAlignment1x1Type have a corresponding enum class, which is derived from it.
				//template <class T> typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, int>::value, void>::type
				//	operator()(const char* name, T t)
				//{
				//
				//}

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
		//	
		//	T m_managedData;
		//};		
	}
}

#endif // TREEITEM_H