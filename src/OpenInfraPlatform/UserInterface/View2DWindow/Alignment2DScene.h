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

#include <QDockWidget>

#include "OpenInfraPlatform/DataManagement/Data.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QGraphicsScene>
#include <boost/noncopyable.hpp>
#include <vector>
#include <map>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		// Scene
		class Alignment2DScene : public QGraphicsScene
		{
			Q_OBJECT;

		public:
			enum class A2D_DrawState
			{
				A2D_Print,
				A2D_Draw,
			};

		public:
			Alignment2DScene(QObject *parent = 0);
			
			void setAlignment(buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> alignment);

			void setSelectedAlignment(int index);
			int getSelectedAlignment();

			void setDifferentColorsForHorizontalAlignmentElements(const bool checked);
			void setDifferentColorsForVerticalAlignmentElements(const bool checked);

			void setScalingRatio(double x, double y);
			void fit(double width);

			void configureColors(const A2D_DrawState state);

			void exportToFile(QWidget* parent);

		private:
			void drawAlignmentScene();
			void drawDiagram(QPainterPath& diagPainter, QPainterPath& diagDashedPainter);

			void drawAxis(QPainterPath& diagPainter, double at, double begin, double end, double scaling, double desiredStepSize, bool doubleLine = true, bool vertical = false);
			void addPaths();
			
		protected:
			void scale();

			virtual void v_configureColors(A2D_DrawState state){};

			virtual void v_drawAlignment(buw::ReferenceCounted<buw::Alignment2DBased3D> a,
				std::map<buw::eHorizontalAlignmentType, QPainterPath>& horizontalPainter,
				std::map<buw::eVerticalAlignmentType, QPainterPath>& verticalPainter) 
			{};
			virtual void v_drawDiagram(QPainterPath& diagPainter, QPainterPath& diagDashedPainter)
			{};

			virtual QGraphicsTextItem* v_labelX(double value);
			virtual QGraphicsTextItem* v_labelY(double value);

			virtual void v_addPaths(){};
			
		protected:
			void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
			void wheelEvent(QGraphicsSceneWheelEvent* mouseEvent);

		protected:
			buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> alignment_;
			int					selectedAlignmentIndex_;
			bool				differentColorsForHorizontalAlignmentElements_;
			bool				differentColorsForVerticalAlignmentElements_;

			buw::Vector4d		bounds;

			std::map<buw::eHorizontalAlignmentType, QPen>			horizontalPens;
			std::map<buw::eVerticalAlignmentType, QPen>				verticalPens;
			std::map<buw::eHorizontalAlignmentType, QPainterPath>	horizontalPainter;
			std::map<buw::eVerticalAlignmentType, QPainterPath>		verticalPainter;

			QPen			diagramPen, 
							diagramDashedPen;
			QBrush			transparentBrush;
			QFont			diagramFont;
			QColor			diagramFontColor;

			double				scalingX, 
								scalingY;

			buw::Vector2d		ratio;

		public:
			static QPainterPath scaledPainterPath(QPainterPath* path, double sX, double sY);
		};
	} // end namespace UserInterface
} 

