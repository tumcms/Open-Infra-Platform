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
#ifndef BlueFramework_GraphicsEngine_BlueMap_89d0ecd9_c7bb_42aa_87a1_f2b355d8cf2c_h
#define BlueFramework_GraphicsEngine_BlueMap_89d0ecd9_c7bb_42aa_87a1_f2b355d8cf2c_h

#include <BlueFramework/Core/PropertySet.h>
#include <boost/noncopyable.hpp>
#include <string>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QPointF>

namespace BlueFramework
{
	namespace Engine
	{
		enum class GeoCoordinateSystem
		{
			WGS84,
			GaussKrueger,
		};

		class OpenInfraMap : private boost::noncopyable
		{
		public:			
			explicit OpenInfraMap(QWidget* parent);

			virtual ~OpenInfraMap();
			
			QWidget* show();
			void hide();

			QGeoCoordinate position() const;
			void position(const QGeoCoordinate& value);
			int zoom() const;
			void zoom(int value);
			int minimalZoom() const;
			int maximalZoom() const;

			void reposition(const buw::Vector3d& vector, GeoCoordinateSystem coordinateSystem);

		private:
			QQuickView m_view;
			QWidget* m_container;
		}; // end class BlueMap
	} // end namespace GraphicsEngine
} // end namespace BlueFramework

namespace buw
{
	using BlueFramework::Engine::OpenInfraMap;
	using BlueFramework::Engine::GeoCoordinateSystem;
}

#endif // end define BlueFramework_GraphicsEngine_BlueMap_89d0ecd9_c7bb_42aa_87a1_f2b355d8cf2c_h