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
#ifndef OSMDATAMODEL_H
#define OSMDATAMODEL_H

#include <BBox.h>
#include <GeorefMetadata.h>
#include <IModel.h>
#include <string>
#include <vector>
#include <mutex>

#include "namespace.h"

// typedefs
using PointLayout_t = buw::VertexPosition3Color3Normal3;

namespace OpenInfraPlatform
{
	namespace Core
	{
		/**
		* @namespace OsmDataConverter
		* @brief Namepsce containing structs and OsmModel class for storing all OpenStreetMap data
		*/
		namespace OsmDataConverter
		{
			/**
			* @struct IndexedMeshDescription
			* @brief Struct containing the description of indexed mesh.
			*/
			struct IndexedMeshDescription {
				std::vector<int>						indices;
				std::vector<PointLayout_t>				points;		// BlueFramework/Rasterizer/src/vertex.h

				/**
				* @brief Method to check if indices and points vector is empty.
				* @return Boolean indicating if the indices and points vector is empty.
				*/
				bool isEmpty() const { return (indices.size() == 0 && points.size() == 0); }

				/**
				* @brief Method to reset the indices and points vector.
				*/
				void reset() { indices.clear(); points.clear(); }
			};

			/**
			*@struct GeometryDescription
			* @brief Struct containing the description of geometry, with the bounding box information
			*/
			struct GeometryDescription {
				IndexedMeshDescription					meshDescription;
				oip::BBox								bb;
				/**
				* @brief Method to check if meshDescription is empty.
				* @return Boolean indicating if meshDescription is empty.
				*/
				bool isEmpty() const { return meshDescription.isEmpty(); }

				/**
				* @brief Method to reset the meshDescription and bounding box.
				*/
				void reset() { meshDescription.reset(); bb.reset(); }

				/**
				* @brief Method to add indices to meshDescription.
				* @param indices Vector of integers representing indices to be added.
				*/
				void addIndices(const std::vector<int>& indices)
				{
					meshDescription.indices.reserve(indices.size());
					for (const auto& index : indices)
						meshDescription.indices.push_back(index);
				}

				/**
				* @brief Method to add points to meshDescription.
				* @param points Vector of PointLayout_t representing points to be added.
				*/
				void addPoints(const std::vector<PointLayout_t>& points)
				{
					meshDescription.points.reserve(points.size());
					for (const auto& point : points)
						meshDescription.points.push_back(point);
				}

				/**
				* @brief Method to update the bounding box of geometry.
				*/
				void updateBBox()
				{
					for (const auto& point : meshDescription.points)
						bb.update(point.position[0], point.position[1], point.position[2]);
				}
			};

			/**
			* @brief OsmModel is a class that represents a 3D model created from OpenStreetMap data.
			* This class is derived from oip::IModel.
			*/
			class OsmModel : public oip::IModel
			{
			private:
				/**
				* @brief A vector of GeometryDescription shared pointers.
				*/
				std::vector<std::shared_ptr<GeometryDescription>>					geometries_;

				/**
				* @brief A mutex to protect the geometries vector from concurrent access.
				*/
				std::mutex															geometryMutex_;

				std::string															filename_;

			public:
				/**
				* @brief Resets the model by clearing the geometries vector.
				*/
				void reset();

				/**
				* @brief Adds a GeometryDescription shared pointer to the geometries vector.
				* @param geometry The GeometryDescription shared pointer to be added.
				*/
				void addGeometry(std::shared_ptr<GeometryDescription> geometry);

				/**
				* @brief Returns a reference to the geometries vector.
				* @return std::vector<std::shared_ptr<GeometryDescription>> const& A reference to the geometries vector.
				*/
				std::vector<std::shared_ptr<GeometryDescription>> const& geometries() const { return geometries_; }

				/**
				* @brief Sets the filename of the OSM file from which the model was created.
				* @param filename The filename of the OSM file.
				*/
				void setFilename(const std::string& filename) { filename_ = filename; }

				// ************************************************************************************************************************************************************
				// Interface IModel implementation
				// ************************************************************************************************************************************************************

				virtual bool isEmpty() const override;
				virtual std::string getSource() const override;
				virtual oip::BBox getExtent() override;
				virtual oip::GeorefMetadata getGeorefMetadata() const override;
				virtual void transformAllPoints(const oip::GeorefMetadata& newGeorefMetadata, std::function<std::tuple<double, double, double> const(double, double, double)>& transf) override;

				// ************************************************************************************************************************************************************
			};
		}
	}
}

EMBED_CORE_OSMDATACONVERTER_INTO_OIP_NAMESPACE(OsmModel)

#endif //OSMDATAMODEL_H