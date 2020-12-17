/*
Copyright (c) 2021 Technical University of Munich
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
//unix
#ifndef OFFMODEL_H
#define OFFMODEL_H

#include <BBox.h>
#include <GeorefMetadata.h>
#include <IModel.h>

#include "namespace.h"

namespace OpenInfraPlatform
{
	namespace Core
	{
		namespace OffConverter
		{
			struct IndexedMeshDescription {
				std::vector<uint32_t>							indices;
				std::vector<buw::Vector3d>						vertices;
				oip::BBox										bb;
				bool isEmpty() const { return (indices.size() == 0 && vertices.size() == 0); };
				void reset() { indices.clear(); vertices.clear(); }
				void UpdateBBox()
				{
					for (const auto& vertex : vertices)
						bb.update(vertex[0], vertex[1], vertex[2]);
				}
			};

			class OffModel : public oip::IModel
			{
			private:
				IndexedMeshDescription					geometry_;
				std::string								filename_;

			public:
				void reset(); 

				void addVertex(buw::Vector3d vertex);
				IndexedMeshDescription const &geometry() const { return geometry_; }

				// ---------------------------------------------------------------------------------------------------------------------------------------------------
				// Interface IModel implementation
				// ---------------------------------------------------------------------------------------------------------------------------------------------------

				virtual bool isEmpty() const override;
				virtual std::string getSource() const override;

				virtual oip::BBox getExtent() override;

				virtual oip::GeorefMetadata getGeorefMetadata() const override;
				virtual void transformAllPoints(const oip::GeorefMetadata& newGeorefMetadata, std::function<std::tuple<double, double, double> const(double, double, double)>& transf) override;

				// ---------------------------------------------------------------------------------------------------------------------------------------------------

				void setFilename(const std::string& filename) {
					filename_ = filename;
				}
			};
		}
	}
}

EMBED_CORE_OFFCONVERTER_INTO_OIP_NAMESPACE(OffModel)

#endif //OFFMODEL_H