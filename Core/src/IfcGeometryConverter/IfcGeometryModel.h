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
// unix
#ifndef IFCGEOMETRYMODEL_H
#define IFCGEOMETRYMODEL_H

#include <unordered_map>
#include <thread>
#include <mutex>

#include <BBox.h>
#include <GeorefMetadata.h>
#include <IModel.h>

#include "namespace.h"
#include "EXPRESS/EXPRESSModel.h"

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
				bool isEmpty() const { return (indices.size() == 0 && vertices.size() == 0); };
				void reset() { indices.clear(); vertices.clear(); }
			};

			struct PolylineDescription {
				std::vector<uint32_t>		indices;
				std::vector<buw::Vector3f>	vertices;
				bool isEmpty() const { return (indices.size() == 0 && vertices.size() == 0); };
				void reset() { indices.clear(); vertices.clear(); }
			};

			struct GeometryDescription {
				IndexedMeshDescription  meshDescription;
				PolylineDescription		polylineDescription;
				oip::BBox				bb;
				bool isEmpty() const { return meshDescription.isEmpty() && polylineDescription.isEmpty(); }
				void reset() { meshDescription.reset(); polylineDescription.reset(); bb.reset(); }
				void UpdateBBox( const carve::geom::aabb<3>& bbox )
				{
					bb.update(bbox.min());
					bb.update(bbox.max());
					//for (const auto& vertex : meshDescription.vertices)
					//	bb.update(vertex.position[0], vertex.position[1], vertex.position[2]);
					//for (const auto& vertex : polylineDescription.vertices)
					//	bb.update(vertex[0], vertex[1], vertex[2]);
				}
				void UpdateBBox(const carve::geom3d::Vector& pt)
				{
					bb.update(pt.x, pt.y, pt.z);
				}
			};

			class IfcModel : public oip::IModel 
			{
			private:
				std::vector<std::shared_ptr<GeometryDescription>>	geometries_;
				std::mutex											geometryMutex_;

				std::string											filename_;
				oip::GeorefMetadata									georefMeta_;

				std::shared_ptr<oip::EXPRESSModel>					expressModel_;

			public:
				void reset();

				void addGeometry(std::shared_ptr<GeometryDescription> geometry);
				std::vector<std::shared_ptr<GeometryDescription>> const &geometries() const { return geometries_; }

				void addExpressModel(std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSModel> expressModel);
				std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSModel> const getExpressModel() const { return expressModel_; }

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

				void setGeoref(const oip::GeorefMetadata& georefMeta) {
					georefMeta_ = georefMeta;
				}


			};

		}
	}
}

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(IfcModel)

#endif // IFCGEOMETRYMODEL_H
