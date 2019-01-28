#pragma once
#ifndef IfcTreeItem_H
#define IfcTreeItem_H


#include <QList>
#include <QVariant>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include "OpenInfraPlatform\IfcAlignment1x1\model\Model.h"

#include <visit_struct/visit_struct.hpp>
#include <type_traits>

namespace OpenInfraPlatform {
	namespace UserInterface {

		class IfcTreeItemBase
		{
		protected:
			QList<IfcTreeItemBase*> m_childItems;
			QList<QVariant> m_itemData;
			IfcTreeItemBase *m_parentItem = nullptr;

		public:

			IfcTreeItemBase() = default;

			void appendChild(IfcTreeItemBase *child)
			{
				m_childItems.append(child);
			}

			IfcTreeItemBase *child(int row)
			{
				return m_childItems.value(row);
			}

			int childCount() const
			{
				return m_childItems.count();
			}

			int columnCount() const
			{
				return 3;
			}

			//QVariant OpenInfraPlatform::UserInterface::IfcTreeItem::data(int column) const
			QVariant data(int column) const
			{
				return m_itemData.value(column);
			}

			int row() const
			{
				if (m_parentItem)
					return m_parentItem->m_childItems.indexOf(const_cast<IfcTreeItemBase*>(this));

				return 0;
			}

			IfcTreeItemBase *parentItem()
			{
				return m_parentItem;
			}

			void setItemData(QList<QVariant> itemData)
			{
				m_itemData = itemData;
			}

			virtual ~IfcTreeItemBase() {
				qDeleteAll(m_childItems);
			}

			template<class T> const T& getValue() const; //to be implimented after Parameter
			template<class T, class U> void setValue(const U& rhs); //to be implimented after Parameter

			virtual void createChildren()
			{

			}

		};
		
		template <typename T> class IfcTreeItem : public IfcTreeItemBase {
		public:
			IfcTreeItem(T &data, IfcTreeItemBase* parent = nullptr)
				: m_managedData(data)
			{
				m_parentItem = parent;
			}
			virtual ~IfcTreeItem()
			{
				qDeleteAll(m_childItems);
			}

			const T& getValue() const { return value; }

			void setValue(const T& rhs) { value = rhs; }

			typedef struct {
				template <typename T>
				void operator()(const char * name, const std::shared_ptr<T> & value) {
					std::cerr << name << ": " << *value << std::endl;
				}

				template <typename T>
				void operator()(const char * name, const std::vector<T> & value) {
					std::cerr << name << ": " << "vector" << std::endl;
				}

				template <typename T>
				void operator()(const char * name, const T & value) {
					std::cerr << name << ": " << value << std::endl;
				}

			} visitor_;
			
			virtual void createChildren() override
			{
				visit_struct::for_each(*m_managedData, visitor_{});
			}
			
			T m_managedData;			
		};
			

		//Here's the trick: dynamic_cast rather than virtual
		template<class T> const T& IfcTreeItemBase::getValue() const
		{
			return dynamic_cast<const IfcTreeItem<T>&>(*this).getValue();
		}
		template<class T, class U> void IfcTreeItemBase::setValue(const U& rhs)
		{
			return dynamic_cast<IfcTreeItem<T>&>(*this).setValue(rhs);
		}
	}
}

#endif // IfcTreeItem_H