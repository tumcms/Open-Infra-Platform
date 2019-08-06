/*! \verbatim
 *  \copyright	Copyright (c) 2015 Julian Amann. All rights reserved.
 *	\author		Julian Amann <julian.amann@tum.de> (https://www.cms.bgu.tum.de/en/team/amann)
 *	\brief		This file is part of the BlueFramework.
 *	\endverbatim
 */

#pragma once
#ifndef OpenInfraPlatform_UserInterface_OpenInfraMap_fb3c8e89_70ea_4bd7_8393_1d1b86e58faa_h
#define OpenInfraPlatform_UserInterface_OpenInfraMap_fb3c8e89_70ea_4bd7_8393_1d1b86e58faa_h

#include <buw.h>
#include <QWidget>
#include <QQuickView>
#include <QGeoCoordinate>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		enum class GeoCoordinateSystem
		{
			WGS84,
			GaussKrueger,
		};

		class OpenInfraMap
		{
		public:			
			explicit OpenInfraMap(QWidget* parent);

			virtual ~OpenInfraMap();
			
			QWidget* widget();
			void show();
			void hide();

			QGeoCoordinate position() const;
			void position(const QGeoCoordinate& value);
			int zoom() const;
			void zoom(int value);
			int minimalZoom() const;
			int maximalZoom() const;

			void reposition(const buw::Vector3d& vector, GeoCoordinateSystem coordinateSystem);

		private:
			QQuickView* view_;
			QWidget* container_;
		}; // end class OpenInfraMap
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform


#endif // end define OpenInfraPlatform_UserInterface_OpenInfraMap_fb3c8e89_70ea_4bd7_8393_1d1b86e58faa_h