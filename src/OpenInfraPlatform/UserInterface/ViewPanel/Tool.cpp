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

#include "Tool.h"

//namespace OpenInfraPlatform
//{
//	namespace UserInterface
//	{
//		class SketchBasedAlignment : public Tool
//		{
//		public:
//			SketchBasedAlignment(buw::ReferenceCounted<buw::VertexCachePoint> vcp) :
//				vertexCachePoint_(vcp)
//			{
//
//			}
//
//			void mousePressEvent(QMouseEvent *event) override
//			{
//				if (event->button() & Qt::LeftButton)
//				{
//					if (event->modifiers() & Qt::SHIFT)
//					{
//						m_ConstructionPoints.clear();
//
//						vertexCachePoint_->clear();
//					}
//				}
//			}
//
//			void mouseMoveEvent(QMouseEvent *event) override
//			{
//				if (event->buttons())
//				{
//					if (event->modifiers() & Qt::SHIFT)
//					{
//						buw::Vector3f lastTargetPoint = targetPoint_;
//
//						vertexCachePoint_->drawPoint(targetPoint_);
//
//						m_ConstructionPoints.push_back(lastTargetPoint);
//					}
//				}
//			}
//
//			void setTargetPoint(const buw::Vector3f& targetPoint) override
//			{
//				targetPoint_ = targetPoint;
//			}
//
//		private:
//			buw::Vector3f targetPoint_;
//
//			std::vector<buw::Vector3f> m_ConstructionPoints;
//
//			// Drawing
//			buw::ReferenceCounted<buw::VertexCachePoint>	vertexCachePoint_;
//		};
//	}
//}
//
//void OpenInfraPlatform::UserInterface::ToolManager::setTargetPoint(buw::Vector3f targetPoint_)
//{
//	tool_->setTargetPoint(targetPoint_);
//}
//
//void OpenInfraPlatform::UserInterface::ToolManager::mouseMoveEvent(QMouseEvent *event)
//{
//	tool_->mouseMoveEvent(event);
//}
//
//void OpenInfraPlatform::UserInterface::ToolManager::mousePressEvent(QMouseEvent *event)
//{
//	tool_->mousePressEvent(event);
//}
//
//void OpenInfraPlatform::UserInterface::ToolManager::setCurrentTool(buw::ReferenceCounted<Tool> tool)
//{
//	tool_ = tool;
//}
//
//OpenInfraPlatform::UserInterface::ToolManager::ToolManager(buw::ReferenceCounted<buw::VertexCachePoint> vcp)
//{
//	tool_ = std::make_shared<SketchBasedAlignment>(vcp);
//}
//
