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

// visual studio
#pragma once
// unix
#ifndef IFCGEOMETRYMODEL_H
#define IFCGEOMETRYMODEL_H

#include <unordered_map>
#include <thread>
#include <mutex>

#include <BBox.h>
#include <IModel.h>

#include "namespace.h"

typedef buw::VertexPosition3Color3Normal3 VertexLayout;

namespace OpenInfraPlatform
{
	namespace Core 
	{
		namespace IfcGeometryConverter 
		{
			struct IndexedMeshDescription {
				std::vector<uint32_t>		indices;
				std::vector<VertexLayout>	vertices;
				bool isEmpty() { return (indices.size() == 0 && vertices.size() == 0); };
				void reset() { indices.clear(); vertices.clear(); }
			};

			struct PolylineDescription {
				std::vector<uint32_t>		indices;
				std::vector<buw::Vector3f>	vertices;
				bool isEmpty() { return (indices.size() == 0 && vertices.size() == 0); };
				void reset() { indices.clear(); vertices.clear(); }
			};

			class IfcGeometryModel : public oip::IModel {
			public:

				oip::BBox              bb_;
				IndexedMeshDescription meshDescription_;
				PolylineDescription    polylineDescription_;
				bool isEmpty();
				void reset();

				// ---------------------------------------------------------------------------------------------------------------------------------------------------
				// Interface IModel implementation
				// ---------------------------------------------------------------------------------------------------------------------------------------------------

				virtual oip::BBox getExtent() override;

				virtual std::string getEPSGcode() const override;
				virtual void transformAllPoints(const std::string& newEPSGcode, std::function<std::tuple<double, double, double> const(double, double, double)>& transf) override;

				// ---------------------------------------------------------------------------------------------------------------------------------------------------

			};

		}
	}
}

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(IfcGeometryModel)

#endif // IFCGEOMETRYMODEL_H
