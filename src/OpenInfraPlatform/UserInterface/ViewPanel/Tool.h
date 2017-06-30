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

#pragma once

//#include "buw.BlueEngine.h"
//#include <QMouseEvent>
//
//namespace OpenInfraPlatform
//{
//	namespace UserInterface
//	{
//		class Tool
//		{
//		public:
//			virtual void mousePressEvent(QMouseEvent *event) = 0;
//			virtual void mouseMoveEvent(QMouseEvent *event) = 0;
//			virtual void setTargetPoint(const buw::Vector3f& targetPoint) = 0;
//		};
//
//		class ToolManager
//		{
//		public:
//			ToolManager(buw::ReferenceCounted<buw::VertexCachePoint> vcp);
//
//			void setCurrentTool(buw::ReferenceCounted<Tool> tool);
//
//			void mousePressEvent(QMouseEvent *event);
//
//			void mouseMoveEvent(QMouseEvent *event);
//
//			void setTargetPoint(buw::Vector3f targetPoint_);
//
//		private:
//			buw::ReferenceCounted<Tool>			tool_;
//			buw::Vector3f		targetPoint_;
//		};
//	}
//}