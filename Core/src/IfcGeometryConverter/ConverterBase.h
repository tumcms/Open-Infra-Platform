/*
    Copyright (c) 2018 Technical University of Munich
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

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
 *
 * - modified by Michael Kern, September 2014
*/
// visual studio
#pragma once
// unix
#ifndef CONVERTERBASE_H
#define CONVERTERBASE_H

#include "CarveHeaders.h"

#include "GeometrySettings.h"
#include "UnitConverter.h"

namespace OpenInfraPlatform
{
	namespace Core 
	{
		namespace IfcGeometryConverter {

			/*!	\brief Base class for converter templates

			This template provides the base for all converter classes.
			It includes the geometry settings and the unit conversion factors.

			\sa GeometrySettings
			\sa UnitConverterT
			*/
			template <
				class IfcEntityTypesT
			>
			class ConverterBaseT {
			public:
				//! Default constructor
				ConverterBaseT(
					std::shared_ptr<GeometrySettings> geomSettings,
					std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter
				) :
					geomSettings_(geomSettings),
					unitConverter_(unitConverter)
				{}
				//! Default destructor
				~ConverterBaseT() {}

				//! Getter for geometry settings
				std::shared_ptr<GeometrySettings>&				 GeomSettings()		  { return geomSettings_; }
				std::shared_ptr<GeometrySettings> 				 GeomSettings() const { return geomSettings_; }
				//! Getter for unit conversion
				std::shared_ptr<UnitConverter<IfcEntityTypesT>>& UnitConvert()		  { return unitConverter_; }
				std::shared_ptr<UnitConverter<IfcEntityTypesT>>  UnitConvert()	const { return unitConverter_; }

			private:

				std::shared_ptr<GeometrySettings> geomSettings_; //< Geometry settings for conversion
				std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter_; //< Unit conversion factors

			};
		}
	}
}

#endif

