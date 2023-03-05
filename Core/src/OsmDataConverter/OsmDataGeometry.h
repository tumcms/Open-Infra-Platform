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
#ifndef OSMDATAGEOMETRY_H
#define OSMDATAGEOMETRY_H

// Qt5 includes
#include <QtXml>
#include <QDebug>
#include <QString>
#include <QColor>

// external libraries
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <BlueFramework/Core/Math/vector.h>

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <array>
#include <tuple>
#include <string>
#include <algorithm>
#include <thread>
#define _USE_MATH_DEFINES

#include "namespace.h"

// typedefs
using FeatureBBox_t = std::tuple<double, double, double, double>;
using Node_t = Eigen::Vector3d;
using Way_t = std::vector<Node_t, Eigen::aligned_allocator<Node_t > >;
using Polygon_t = std::pair<QString, std::vector<Way_t>>;
using OsmFeature_t = std::pair<QString, std::vector<Polygon_t>>;


namespace OpenInfraPlatform
{
	namespace Core
	{
		namespace OsmDataConverter
		{
			struct OsmGeometryContainer {
				std::vector<QDomElement>												wayList;
				std::vector<QDomElement>												relationList;
				std::vector<QString>													miscTypes;
				std::array<std::pair<QString, double>, 4>								highwayWidth;
				std::unordered_map<QString, FeatureBBox_t>								idBBox;
				std::unordered_map<QString, int>										wayIdPosition;
				std::unordered_map<QString, QColor>										hexRGBScheme;
			};

			enum class Direction : unsigned int {
				X = 0,
				Y = 1,
				Z = 2
			};

			/**
			* @class OsmGeometry
			* @brief Class to generate geometry data from OpenStreetMap (OSM) XML files.
			*/
			class OsmGeometry
			{
			private:
				// container for OSM geometry data
				OsmGeometryContainer                                osmGeometryContainer_;
				// direction oif extrusion
				Direction											extrusionDirection_;

			public:
				/**
				* @brief Default constructor for OsmGeometry.
				*/
				explicit OsmGeometry();

				/**
				* @brief Destructor for OsmGeometry.
				*/
				virtual ~OsmGeometry();

				/**
				* @brief Initializes member variables with mappers and all OSM data types.
				* @param root The QDomElement root node of the OSM file.
				* @param attr The attribute to initialize.
				*/
				void initializeContainer(const QDomElement& root, const QString attr);

				/**
				* @brief Generates a stl vector container from QDomNodeList using std::generate and lambda function.
				* @param nodeList The QDomNodeList to generate the container from.
				* @return The stl vector container generated from the QDomNodeList.
				*/
				std::vector<QDomElement> toQDomElementVector(const QDomNodeList nodeList);

				/**
				* @brief Sets all sub-features obtainable from OpenStreetMap.
				* @return A vector of all sub-features.
				*/
				std::vector<QString> setSubFeatures();

				//! [references from https://www.openstreetmap.org/#map]
				/**
				* @brief Sets the coloring scheme for respective sub - features.
				* @return A vector of colors for each sub - feature.
				*/
				std::vector<QColor> setSubFeatureColor();

				/**
				* @brief Appends bounding box (bbox) information obtained from the osm element via the tag '<bounds>'.
				* @param featureID The ID of the feature to append the bbox information to.
				* @param boundsElement The QDomElement bounds information.
				*/
				void addToFeatureBBox(const QString featureID, const QDomElement& boundsElement);

				/**
				* @brief Adds OsmFeature_t data to the final output stl vector<OsmElemenet_t>.
				* @param finalOutput The final output stl vector<OsmElemenet_t>.
				* @param osmElement The OsmFeature_t data to add to the final output.
				*/
				void addToOutput(std::vector<OsmFeature_t>& finalOutput, const OsmFeature_t& osmElement) { if (osmElement.second.size()) finalOutput.push_back(osmElement); }

				/**
				* @brief Retrieves all tags of an element.
				* @param element The QDomElement to retrieve the tags from.
				* @param tagName The name of the tag to retrieve.
				* @return A QDomNodeList containing all tags with the given name.
				*/
				QDomNodeList getTags(const QDomElement element, const QString tagName) { return element.elementsByTagName(tagName); }

				/**
				* @brief Sets the OsmFeature_t.first value to the given name.
				* @param polygon The Polygon_t data structure to set the name for.
				* @param name The name to set.
				*/
				void setPolygonName(Polygon_t& polygon, const QString name) { polygon.first = name; }

				/**
				* @brief Resets the Polygon name and data std::vector<QString, std::vector<Way_t>>.
				* @param polygon The Polygon_t data structure to reset.
				*/
				void resetPolygonData(Polygon_t& polygon) { polygon.first.clear(); polygon.second.clear(); }

				/**
				* @brief Retrieves the terrain bounds information.
				* @param root The QDomElement root node of the OSM file.
				* @param tag The tag to retrieve the bounds information for.
				* @param padding The padding value to apply to the terrain.
				* @return The Polygon_t
				* This function retrieves the terrain bounds information from the OSM file using the provided tag,
				* applies the padding value to the terrain, and returns the terrain bounds in the form of a Polygon_t object.
				*/
				Polygon_t createTerrain(const QDomElement& root, const QString tag, const double padding = 0.0025);

				/**
				* @brief Retrieves the color for a sub-feature.
				* @param subFeaName The name of the sub-feature to retrieve the color for.
				* @return The color of the sub-feature.
				*/
				buw::Vector3f getColor(const QString subFeaName);

				/**
				* @brief Converts a HexRgb color to a floating point value.
				* @param hexRGBColor The color to convert.
				* @return The converted color.
				*/
				buw::Vector3f hexRGBToFloat(const QColor hexRGBColor);

				/**
				* @brief Applies padding to the terrain coordinates.
				* @param minGeodeticCoord The minimum geodetic coordinate.
				* @param maxGeodeticCoord The maximum geodetic coordinate.
				* @param paddingValue The amount of padding to apply.
				*/
				void applyPadding(double& minGeodeticCoord, double& maxGeodeticCoord, const double paddingValue);

				/**
				* @brief Rounds off a value to a specified precision.
				* @param value The value to round off.
				* @param roundDown If true, round down. Otherwise, round up.
				* @param precision The precision to round off to.
				* @return The rounded value.
				*/
				double roundOff(const double value, const bool roundDown = false, const double precision = 0.001);

				/**
				* @brief Assembles the geodetic coordinates for the terrain.
				* @param minlat The minimum latitude coordinate.
				* @param maxlat The maximum latitude coordinate.
				* @param minlon The minimum longitude coordinate.
				* @param maxlon The maximum longitude coordinate.
				* @return The geodetic coordinates for the terrain.
				*/
				std::vector<std::vector<double>> assembleGeodeticCoords(double& minlat, double& maxlat, double& minlon, double& maxlon);

				/**
				* @brief Retrieve the height of a building element in an OSM file.
				* @param element The building element to retrieve the height from.
				* @return The height of the building element as a double.
				*/
				double retrieveBuildingHeight(const QDomElement element);

				/**
				* @brief Retrieve the value of the specified attribute(s) of a QDomElement.
				*
				* This function retrieves the value of the specified attribute(s) of a QDomElement, which is typically an element in an XML file.
				* The attribute(s) to retrieve are specified as a QString or a std::vector<QString>.
				* The function searches through all tags of the given element to find the specified attribute(s),
				* and returns the value of the 'v' attribute of the first tag that matches the specified key(s).
				*
				* @tparam T The type of the attribute(s) to retrieve. Can be either a QString or a std::vector<QString>.
				* @param element The QDomElement to search for the specified attribute(s).
				* @param attributes The attribute(s) to retrieve. Can be a single QString or a std::vector<QString>.
				* @param values (optional) The value(s) of the attribute(s) to retrieve. Can be a single QString or a std::vector<QString>. If this parameter is not specified, all tags with the specified key(s) will be returned.
				* @return The value of the first tag that matches the specified key(s) and (optionally) value(s), or an empty QString if no such tag is found.
				*
				* @note The attribute(s) must be specified as exact matches for the 'k' attribute of the tag element.
				* @note The tag(s) are searched in order, so if multiple tags with the same key(s) are present, the function will return the value of the first one it encounters.
				* @note The function returns an empty QString if no tag with the specified key(s) is found.
				*/
				//QString retrieveFeatureAttribute(const QDomElement& element, const T& attributes)
				template <typename T>
				QString retrieveFeatureAttribute(const QDomElement& element, const T& attributes, const T& values = T())
				{
					// get all tags
					QDomNodeList tags = getTags(element, "tag");
					for (int i = 0; i < tags.count(); i++) {
						QDomElement tag = tags.at(i).toElement();

						// single attribute
						// checks if values is empty or not, and also checks if the v attribute of the tag is equal to the values input parameter, 
						// and returns the attribute v value if the condition is true
						if constexpr (std::is_same_v<T, QString>) {
							if (tag.attribute("k") == attributes && (values.isEmpty() || tag.attribute("v") == values))
								//if (tag.attribute("k") == attributes)
								return tag.attribute("v");
						}
						// multiple attributes
						// checks if values is empty or not, and also checks if the v attribute of the tag is equal to any of the values input parameter,
						// using std::find function, and returns the attribute v value if the condition is true
						else if constexpr (std::is_same_v<T, std::vector<QString>>) {
							for (const auto& attr : attributes) {
								// special case: building [if it finds this attribute key, returns the attribute directly; can't name all building 'way' as arguments]
								if (tag.attribute("k") == attr && !values.empty())
									return tag.attribute("v");

								if (tag.attribute("k") == attr && (values.empty() || std::find(values.begin(), values.end(), tag.attribute("v")) != values.end()))
									//if (tag.attribute("k") == attr)
									return tag.attribute("v");
							}
						}
					}
					return QString();
				}

				/**
				* @brief Check if 'relation' member exists within 'relation' element.
				* @param parentRelation The parent 'relation' element.
				* @return True if 'relation' member exists, false otherwise.
				*/
				bool isValidMemberRelation(const QDomElement parentRelation);

				/**
				* @brief Templated function to find mapper value.
				* @tparam T The type of the container value.
				* @param key The key to search for in the container.
				* @param container The container to search for the key.
				* @return The value associated with the key if it exists, or a default value if not.
				*/
				template <typename T>
				T findValue(const QString& key, const std::unordered_map<QString, T>& container)
				{
					auto it = container.find(key);
					if (it != container.end())
						return it->second;
					return T(-1);
				}

				/**
				* @brief Templated function to find array container value with the same signature as the one above.
				* @tparam T The type of the container value.
				* @tparam N The size of the container array.
				* @param key The key to search for in the container.
				* @param container The container to search for the key.
				* @return The value associated with the key if it exists, or a default value if not.
				*/
				template <typename T, size_t N>
				T findValue(const QString& key, const std::array<std::pair<QString, T>, N>& container)
				{
					for (const auto& p : container) {
						if (p.first == key)
							return p.second;
					}
					return T(-1);
				}

				/**
				* @brief Offset point perpendicular to line formed by corresponding line end points.
				* @param elementNodes The set of nodes for the line.
				* @param offsetDistance The distance to offset the point.
				* @return The offset point.
				*/
				Way_t offsetPoints(const Way_t elementNodes, const double& offsetDistance);

				/**
				* @brief Add offset point perpendicular to line formed by corresponding line end points.
				* @param node The node to offset.
				* @param normVec The normal vector for the line.
				* @param offsetDistance The distance to offset the point.
				* @param offsetNodes The set of nodes for the line with the offset point added.
				*/
				void addOffsetPoint(const Node_t node, const Node_t normVec, const double offsetDistance, Way_t& offsetNodes);

				/**
				* @brief Retrieve OSM feature by mapping id to index.
				* @param id The id of the feature to retrieve.
				* @return The element with the matching id.
				*/
				QDomElement mapIdToIndex(const QString id);

				/**
				* @brief Extract latitude and longitude information from node.
				* @param nodeElement The node element.
				* @return The latitude and longitude of the node.
				*/
				Node_t extractLatLon(const QDomElement& nodeElement);

				/**
				* @brief Convert nodes from WGS-84 CRS to Cartesian geocentric CRS.
				* @param latitude The latitude of the node.
				* @param longitude The longitude of the node.
				* @param elevation The elevation of the node.
				* @return The converted node.
				*/
				Node_t projectWGS84(double latitude, double longitude, double elevation);

				/**
				* @brief Remove way from wayListContainer and mapper.
				* @param wayId The id of the way to be deleted.
				*/
				void deleteWayFromMap(const QString wayId) { osmGeometryContainer_.wayIdPosition.erase(wayId); }

				/**
				* @brief Check if 'way' is "closed".
				* @param wayNodes The element nodes of the way.
				* @return Whether or not the way is "closed".
				*/
				bool isRing(const Way_t& wayNodes);

				/**
				* @brief Check if geometry incomplete.
				* @param wayElement The QDomElement of the way.
				* @return Whether or not the geometry is incomplete.
				*/
				bool isIncompleteGeometry(const QDomElement& wayElement);

				/**
				* @brief Check if latitude and longitude info. given.
				* @param nodeElement The QDomElement of the node.
				* @return Whether or not the latitude and longitude information is given.
				*/
				bool hasLatLon(const QDomElement& nodeElement) { return (nodeElement.hasAttribute("lat") && nodeElement.hasAttribute("lon")); }

				/**
				* @brief Extrude the provided 'wayNodes' in the X, Y, or Z direction by a factor of 'extrusionFactor'
				* @param wayNodes The Way_t nodes to extrude
				* @param extrusionFactor The factor to extrude the nodes by
				*/
				void extrude(Way_t& wayNodes, const double& extrusionFactor);


				/**
				* @brief Given a 3D 'polygon3D', return a 2D Polygon_t
				* @param polygon3D The 3D polygon to get a 2D polygon from
				* @param featureType The feature type of the polygon
				* @return The 2D Polygon_t
				*/
				Polygon_t getSurfacePlane(Polygon_t polygon3D, const QString featureType);

				/**
				* @brief Combine all the polygon nodes and indices to form a Polygon_t
				* @param polygon The Polygon_t to update with the combined nodes and indices
				* @param polygonNodes The polygon nodes to combine
				* @param polygonIndices The polygon indices to combine
				*/
				void combineWayArbitrary(Polygon_t& polygon, Way_t& polygonNodes, std::vector<std::vector<int>>& polygonIndices);

				/**
				* @brief Combine all highway nodes and indices to form a Polygon_t and order the indices
				* @param highwayPolygon The highway Polygon_t to update with the combined nodes and indices
				* @param highway The highway nodes to combine
				* @param highwayIndices The highway indices to combine
				*/
				void combineHighway(Polygon_t& highwayPolygon, Way_t& highway, std::vector<std::vector<int>>& highwayIndices);

				/**
				* @brief Map the provided STL containers to the corresponding Eigen containers
				* @param inputWays The input STL container of ways to map
				* @param inputIndices The input STL container of indices to map
				* @param polyWays The output Eigen container of ways
				* @param polyIndices The output Eigen container of indices
				*/
				void mapStlToEigen(Eigen::MatrixXd& inputWays, Eigen::MatrixXi& inputIndices, Way_t& polyWays, std::vector<std::vector<int>>& polyIndices);

				/**
				* @brief Cast the provided Eigen matrix of doubles to an Eigen matrix of floats
				* @param doubleMatrix The input Eigen matrix of doubles
				* @return The output Eigen matrix of floats
				*/
				Eigen::MatrixXf castDoubleToFloat(Eigen::MatrixXd& doubleMatrix);

				/**
				* @brief Given a set of 'innerPolygon' nodes, compute the midpoint of the nodes to form 'holePoints'
				* @param innerPolygon The set of nodes to compute the midpoint of
				* @param holePoints The output midpoint of the nodes
				*/
				void getHoles(std::vector<Way_t>& innerPolygon, Eigen::MatrixXd& holePoints);

				/**
				* @brief Given a set of relation 'way' elements and a 'role', return all 'outer' and 'inner' polygon ways
				* @param relationWaysList The relation 'way' elements to retrieve the polygon ways from
				* @param role The role of the 'way' element to retrieve the polygon ways for
				* @return The list of all 'outer' and 'inner' polygon ways
				*/
				QDomNodeList getPolygonList(QDomNodeList& relationWaysList, const QString& role);

				/**
				* @brief Modify the attributes of the provided relation 'way' elements
				* @param relationWaysList The list of relation 'way' elements to modify
				* @param attribute The attribute to modify
				* @param value The value to set the attribute to
				*/
				void modifyRelationElements(std::vector<QDomElement>& relationWaysList, const QString attribute, const QString value);

				/**
				* @brief Check if a 'way' element is contained inside another 'way' element by using bbox information.
				* If contained, increment the height for miscellaneous features to avoid 'mesh flickering' phenomenon.
				* @param miscID The id of the miscellaneous feature to check.
				* @param bboxContainer The unordered map of feature id to their bounding boxes.
				* @return The increment value of the height.
				*/
				double isWayContained(const QString miscID, const std::unordered_map<QString, FeatureBBox_t>& bboxContainer);

				/**
				* @brief Read all OpenStreetMap features from the given root node.
				* @param root The root node of the OpenStreetMap data.
				* @return A vector of OpenStreetMap features.
				*/
				std::vector<OsmFeature_t> readOsmGeometry(QDomElement& root);

				/**
				* @brief Read the 'relation' element of the given OpenStreetMap feature.
				* @param baseElement The base OpenStreetMap feature to update.
				* @param relationElement The 'relation' element to read.
				* @param tag The tag for the relation.
				*/
				void readRelation(OsmFeature_t& baseElement, QDomElement& relationElement, QString tag);

				/**
				* @brief Read the 'building' multipolygon from the given list of 'way' elements.
				* @param buildingList The list of 'way' elements that make up the building.
				* @param building The OpenStreetMap building feature to update.
				* @param height The height of the building.
				*/
				void readBuildingMultipolygon(std::vector<QDomElement>& buildingList, OsmFeature_t& building, double height);

				/**
				* @brief Read the 'outer' boundary of the 'multipolygon' relation for miscellaneous features.
				* @param miscList The list of 'relation' elements.
				* @param miscellaneous The miscellaneous OpenStreetMap feature to update.
				* @param miscType The type of the miscellaneous feature.
				*/
				void readMiscellaneousMultipolygon(std::vector<QDomElement>& miscList, OsmFeature_t& miscellaneous, const QString miscType);

				/**
				* @brief Read the 'building' relation element.
				*
				* @param outlineElement The 'way' element that outlines the building.
				* @param height The height of the building.
				* @return The polygon that represents the building.
				*/
				Polygon_t readBuildingTypeRelation(QDomElement& outlineElement, double height);

				/**
				* @brief Read the 'site' relation element.
				* @param siteList The list of 'way' elements that make up the site.
				* @param element The OpenStreetMap feature to update.
				* @param height The height of the site.
				*/
				void readSiteTypeRelation(std::vector<QDomElement>& siteList, OsmFeature_t& element, double height);

				/**
				* @brief Read the 'way' element of the OpenStreetMap feature.
				*
				* @param feature The 'way' element to read.
				* @param featureType The type of the OpenStreetMap feature.
				* @param physicalProperty The physical property of the OpenStreetMap feature.
				* @return The nodes that make up the 'way' element.
				*/
				Way_t readFeature(const QDomElement& feature, const QString featureType, double physicalProperty);

				/**
				* @brief Reads OSM element 'node' for all OSM elements.
				* @param featureType The type of feature being read.
				* @param nodeList The list of nodes to be read.
				* @param propertyValue The value of the physical property to be assigned to the feature.
				* @return The list of nodes read.
				* This function reads the nodes of an OSM feature and returns them as a list of nodes. The physical property
				* of the feature can also be assigned using the propertyValue parameter. If no propertyValue is provided, it is
				* assumed to be zero.
				*/
				Way_t readNodes(QString featureType, QDomNodeList& nodeList, double propertyValue = 0.0);
			};

		}
	}
}

EMBED_CORE_OSMDATACONVERTER_INTO_OIP_NAMESPACE(OsmGeometry)

#endif // !OSMDATAGEOMETRY_H
