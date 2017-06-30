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

// visual studio
#pragma once
// unix
#ifndef PROFILECACHE_H
#define PROFILECACHE_H

#include <map>

#include "CarveHeaders.h"

#include "ProfileConverter.h"

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		template<
			class IfcEntityTypesT,
			class IfcUnitConverterT
		>
		class ProfileCacheT
		{
		public:
			ProfileCacheT(std::shared_ptr<GeometrySettings> geomSettings,
				std::shared_ptr<IfcUnitConverterT> unitConverter)
				: m_geomSettings(geomSettings), m_unitConverter(unitConverter)
			{

			}

			~ProfileCacheT()
			{

			}

			std::shared_ptr<ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>> getProfileConverter(
				std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef>& ifcProfile)
			{
				const int profile_id = ifcProfile->getId();

				typename std::map<int, shared_ptr<ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>>>::iterator 
					it_profile_cache = m_profileCache.find(profile_id);
				if (it_profile_cache != m_profileCache.end())
				{
					return it_profile_cache->second;
				}

				shared_ptr<ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>> profile_converter =
					std::make_shared<ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>>(m_geomSettings, m_unitConverter);

				profile_converter->computeProfile(ifcProfile);

				m_profileCache[profile_id] = profile_converter;


				return profile_converter;
			}

			void clearProfileCache()
			{
				m_profileCache.clear();
			}

		protected:
			std::shared_ptr<GeometrySettings>	m_geomSettings;
			std::shared_ptr<IfcUnitConverterT>	m_unitConverter;
			std::map<int, std::shared_ptr<ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>>> m_profileCache;
		};
	}
}

#endif
