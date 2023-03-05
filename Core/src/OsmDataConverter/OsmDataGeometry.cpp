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

#include "OsmDataGeometry.h"

OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::OsmGeometry()
{

}


OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::~OsmGeometry()
{

}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::initializeContainer(const QDomElement& root, const QString attr)
{
	// store all 'relation' data type
	osmGeometryContainer_.relationList = toQDomElementVector(root.elementsByTagName("relation"));
	// store all 'way' data type
	osmGeometryContainer_.wayList = toQDomElementVector(root.elementsByTagName("way"));

	// store bbox information for relations of 'miscellaneous' types
	for (const auto& relationelement : osmGeometryContainer_.relationList) {
		//																			keys					values
		if (retrieveFeatureAttribute<std::vector<QString>>(relationelement, { "type", "building" }, { "site", "building" }).isEmpty())
			addToFeatureBBox(relationelement.attribute(attr), relationelement.firstChildElement());
	}

	// map id to position ['way']
	// store bbox information for ways of 'miscellaneous' types
	for (unsigned int i = 0; i < osmGeometryContainer_.wayList.size(); i++) {

		QDomElement wayElement = osmGeometryContainer_.wayList.at(i).toElement();

		// map id to index
		QString id = wayElement.attribute(attr);
		osmGeometryContainer_.wayIdPosition[id] = i;

		// add bbox information; only if 'miscellaneous' element
		//																		keys
		if (retrieveFeatureAttribute<std::vector<QString>>(wayElement, { "building", "highway" }).isEmpty())
			addToFeatureBBox(id, wayElement.firstChildElement());
	}


	// initalize highway width mapper
	std::vector<QString> highwayType = { "residential", "tertiary", "secondary", "primary" };
	for (int highwayIt = 0; highwayIt < highwayType.size(); highwayIt++) {

		//double width = (highwayIt * 2.0) + 4.0;
		double width = highwayIt + 4.0;
		osmGeometryContainer_.highwayWidth[highwayIt] = std::make_pair(highwayType.at(highwayIt), width);
	}

	// store all miscellaneous types
	osmGeometryContainer_.miscTypes = { "amenity", "leisure", "landuse", "natural" };

	// store all sub-feature colors (as HexRgb) in mapper
	std::vector<QString> subFeature = setSubFeatures();
	std::vector<QColor> subFeaColor = setSubFeatureColor();

	for (unsigned int i = 0; i < subFeature.size(); i++)
		osmGeometryContainer_.hexRGBScheme[subFeature[i]] = subFeaColor[i];
}


std::vector<QDomElement> OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::toQDomElementVector(const QDomNodeList nodeList)
{
	std::vector<QDomElement> elementList(nodeList.size());
	std::generate(elementList.begin(), elementList.end(), [nodeList, i = 0]() mutable {return nodeList.item(i++).toElement(); });

	return elementList;
}


std::vector<QString> OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::setSubFeatures()
{
	return std::vector<QString> { "grass", "forest", "wood", "park", "hospital", "farm", "cemetery", "playground", "pitch", "water", "school", "university",
		"parking", "residential", "tertiary", "secondary", "primary", "building", "construction", "site" };
}


std::vector<QColor> OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::setSubFeatureColor()
{
	//									grass				forest			wood				park				hospital		farm
	return std::vector<QColor> { QColor("#16300d"), QColor("#8dc56c"), QColor("#aed1a0"), QColor("#b6fdb6"), QColor("#ffffc0"), QColor("#ead8bd"),
		//		cemetery			playground		pitch				  water				 school				university			parking
		QColor("#aacbaf"), QColor("#dffce2"), QColor("#8ad3af"), QColor("#aad3df"), QColor("#f0f0d8"), QColor("#292828"), QColor("#0f0f0d"),
		//		residential			tertiary			secondary		primary				building			construction		site
		QColor("#0d0d0d"), QColor("#0d0d0d"), QColor("#16180d"), QColor("#4a280d"), QColor("#f5f5dc"), QColor("#40402f"), QColor("#f5f5dc") };
}


//void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::addToFeatureBBox(const QString featureID, const QString elementType, const QDomElement& boundsElement)
void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::addToFeatureBBox(const QString featureID, const QDomElement& boundsElement)
{
	// get bbox infromation from bounds element
	double minlat = boundsElement.attribute("minlat").toDouble();
	double minlon = boundsElement.attribute("minlon").toDouble();
	double maxlat = boundsElement.attribute("maxlat").toDouble();
	double maxlon = boundsElement.attribute("maxlon").toDouble();

	// store the bbox infromation
	osmGeometryContainer_.idBBox[featureID] = std::make_tuple(minlat, minlon, maxlat, maxlon);
}


double OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::roundOff(const double value, const bool roundDown, const double precision)
{
	if (roundDown)
		return std::floor(value / precision) * precision;
	return std::ceil(value / precision) * precision;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::applyPadding(double& minGeodeticCoord, double& maxGeodeticCoord, const double paddingValue)
{
	//minGeodeticCoord = roundOff(minGeodeticCoord, true);
	//maxGeodeticCoord = roundOff(maxGeodeticCoord);

	// more control over the exact location of the bounding box corners
	minGeodeticCoord -= paddingValue;
	maxGeodeticCoord += paddingValue;
}


std::vector<std::vector<double>> OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::assembleGeodeticCoords(double& minlat, double& maxlat, double& minlon, double& maxlon)
{
	// padding value (obtained after trial & error)
	const double paddingValue = 0.0010;
	// latitude
	applyPadding(minlat, maxlat, paddingValue);
	// longitude
	applyPadding(minlon, maxlon, paddingValue);
	//												S-W					S-E					N-E					N-W
	return std::vector<std::vector<double>>{ { minlat, minlon }, { minlat, maxlon }, { maxlat, maxlon }, { maxlat, minlon } };
}


Polygon_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::createTerrain(const QDomElement& root, const QString tag, const double padding)
{
	// container
	Polygon_t terrainGeo;
	terrainGeo.first = "terrain";

	// terrain bbox i.e. S-W & N-E coordinates
	QDomElement terrainElement = root.namedItem(tag).toElement();

	// retrieve min, max lat./long. & apply padding
	double minlat = terrainElement.attribute("minlat").toDouble();
	double minlon = terrainElement.attribute("minlon").toDouble();
	double maxlat = terrainElement.attribute("maxlat").toDouble();
	double maxlon = terrainElement.attribute("maxlon").toDouble();


	// assemble geodetic coords & apply padding to make sure terrain always contains OSM features
	std::vector<std::vector<double>> assembledGeoCoords = assembleGeodeticCoords(minlat, maxlat, minlon, maxlon);

	// elevation properties
	unsigned int direction = static_cast<int>(Direction::Z);
	const double elevation = -0.5;

	// create terrain corner points (3D)
	//					N-W       N-E (maxlat, maxlon)
	//					 x ------- x
	//					 |         |		-- z = 0
	//					 x ------- x
	//(minlat, minlon)	S-W       S-E
	//						  |
	//					 x ------- x
	//					 |         |		-- z = -z
	//					 x ------- x

	Way_t terrainNodes; terrainNodes.reserve(8);
	for (const auto& geoCoord : assembledGeoCoords)
	{
		Node_t n1 = projectWGS84(geoCoord[0], geoCoord[1], 0.0);
		Node_t n2 = n1;
		n2(direction) = n1(direction) + elevation;
		terrainNodes.insert(terrainNodes.end(), { n1, n2 });
	}
	terrainGeo.second.push_back(terrainNodes);
	return terrainGeo;
}


buw::Vector3f OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::getColor(const QString subFeaName)
{
	if (osmGeometryContainer_.hexRGBScheme.count(subFeaName) > 0)
		return hexRGBToFloat(osmGeometryContainer_.hexRGBScheme[subFeaName]);

	// default sub-feature color
	return hexRGBToFloat(QColor("#ffffff"));
}


buw::Vector3f OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::hexRGBToFloat(const QColor hexRGBColor)
{
	buw::Vector3f floatColor;
	floatColor.x() = hexRGBColor.redF();
	floatColor.y() = hexRGBColor.greenF();
	floatColor.z() = hexRGBColor.blueF();
	return floatColor;
}


double OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::retrieveBuildingHeight(const QDomElement element)
{
	// get all tags
	QDomNodeList tags = getTags(element, "tag");

	for (int i = 0; i < tags.count(); i++) {
		QDomElement tag = tags.at(i).toElement();

		// building:levels
		if (tag.attribute("k") == "building:levels")
			return ((tag.attribute("v").toDouble() * 6.0) + 6.0);
		// height
		else if (tag.attribute("k") == "height")
			return tag.attribute("v").toDouble();
	}
	// reference height (per floor in a building)
	return 6.0;
}


bool OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::isValidMemberRelation(const QDomElement parentRelation)
{
	QDomNodeList members = getTags(parentRelation, "member");

	for (unsigned int i = 0; i < members.count(); i++) {
		QDomElement member = members.at(i).toElement();

		if (member.attribute("type") == "relation")
			return true;

		else if (isIncompleteGeometry(member))
			return true;
	}
	return false;
}


// https://stackoverflow.com/questions/71627443/calculate-offset-coordinate-in-a-cartesian-space
Way_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::offsetPoints(const Way_t elementNodes, const double& offsetDistance)
{
	Way_t offsetNodes;
	offsetNodes.reserve(elementNodes.size() * 2);

	// start from 1 and get the previous line end point
	for (unsigned int pointIt = 1; pointIt < elementNodes.size(); pointIt++)
	{
		// get start & end points of the line
		const Node_t endNode = elementNodes.at(pointIt);
		const Node_t startNode = elementNodes.at(pointIt - 1);

		// calculate the distance and direction vector
		const Node_t dirVec = endNode - startNode;
		const double dirLength = dirVec.norm();

		Node_t normVec = { -dirVec.y(), dirVec.x(), 0.0 };
		normVec.normalize();

		if (pointIt == 1)
			addOffsetPoint(startNode, normVec, offsetDistance, offsetNodes);

		addOffsetPoint(endNode, normVec, offsetDistance, offsetNodes);
	}
	return offsetNodes;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::addOffsetPoint(const Node_t node, const Node_t normVec, const double offsetDistance, Way_t& offsetNodes)
{
	const Node_t offPos = node + normVec * offsetDistance;
	const Node_t offNeg = node - normVec * offsetDistance;
	offsetNodes.insert(offsetNodes.end(), { offPos, offNeg });
}


QDomElement OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::mapIdToIndex(const QString id)
{
	// find index value
	int index = findValue<int>(id, osmGeometryContainer_.wayIdPosition);

	// if no reference of way found; return empty QDomElement
	if (index == -1)
		return QDomElement();

	return osmGeometryContainer_.wayList.at(index).toElement();
}


Node_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::extractLatLon(const QDomElement& nodeElement)
{
	// extract node information
	double latitude = nodeElement.attribute("lat").toDouble();
	double longitude = nodeElement.attribute("lon").toDouble();

	// convert from WGS-84 to Cartesian ECEF
	return projectWGS84(latitude, longitude, 0.0);
}


// #TODO: this is approx. close but still not accurate (implement an accurate solution, if necessary)
Node_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::projectWGS84(double latitude, double longitude, double elevation)
{
	// convert latitude and longitude to radians
	latitude = latitude * (M_PI / 180.0);
	longitude = longitude * (M_PI / 180.0);

	// set radius of the Earth
	const double earthRad = 6371000.0;

	// get Cartesian X,Y,Z
	double x = earthRad * std::sin(latitude) * std::cos(longitude);
	double y = earthRad * std::sin(latitude) * std::sin(longitude);
	double z = elevation;

	return Node_t(-x, y, z);
}


bool OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::isRing(const Way_t& wayNodes)
{
	// 'building' and 'miscellaneous' features have 2 repition nodes to signify closed geo.
	int repNode = 2;
	// check first and last node
	// only if size is greater than repition node
	return wayNodes.size() >= repNode && wayNodes.front().isApprox(wayNodes[wayNodes.size() - repNode]);
}


bool OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::isIncompleteGeometry(const QDomElement& wayElement)
{
	QDomNodeList allNodes = getTags(wayElement, "nd");

	for (unsigned int i = 0; i < allNodes.count(); i++) {
		QDomElement nodeElement = allNodes.at(i).toElement();
		if (!hasLatLon(nodeElement))
			return true;
	}
	return false;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::extrude(Way_t& wayNodes, const double& extrusionFactor)
{
	// get the index (axis) to extrude
	unsigned int direction = static_cast<unsigned int>(extrusionDirection_);

	Way_t tmp = wayNodes;
	unsigned int position = 1;

	for (auto it = tmp.begin(); it != tmp.end(); ++it) {

		if (extrusionFactor != 0.0) {
			(*it)(direction) += extrusionFactor;
		}
		// append
		wayNodes.insert(wayNodes.begin() + position, *it);

		// increment iterator
		position += 2;
	}
}


Polygon_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::getSurfacePlane(Polygon_t polygon3D, const QString featureType)
{
	Polygon_t polygon2D;
	polygon2D.first = polygon3D.first;

	// 'building' and 'miscellaneous' features have repition nodes at the end to signify they're closed geo.
	const unsigned int repNodes = (featureType == "building" || featureType == "miscellaneous") ? 2 : 0;
	const unsigned int advance = 2;

	for (const auto& way3D : polygon3D.second) {

		Way_t way2D;
		for (auto it = way3D.begin(); it != way3D.end() - repNodes; std::advance(it, advance)) {
			way2D.push_back(*it);
		}
		polygon2D.second.push_back(way2D);
	}

	return polygon2D;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::combineWayArbitrary(Polygon_t& polygon, Way_t& polygonNodes, std::vector<std::vector<int>>& polygonIndices)
{
	int start = 0, nextInd = 0, end = 0;

	for (auto it = polygon.second.begin(); it != polygon.second.end(); ++it) {

		// arrange polygon nodes
		polygonNodes.insert(polygonNodes.end(), it->begin(), it->end());

		// arrange indices
		// example: count = 6
		// 5	 4	   3
		// x --- x --- x
		// |		   |
		// x --- x --- x
		// 0	 1     2

		start = end;
		end = polygonNodes.size();

		for (int index = start; index < end; index++) {
			nextInd = (index + 1) % end;
			if (nextInd == 0)
				nextInd = start;

			// append
			polygonIndices.push_back(std::vector<int>({ index, nextInd }));
		}
	}
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::combineHighway(Polygon_t& highwayPolygon, Way_t& highway, std::vector<std::vector<int>>& highwayIndices)
{
	int start = 0, count = highwayPolygon.second[0].size(), end = count - 1, nextInd = 0;

	for (auto it = highwayPolygon.second.begin(); it != highwayPolygon.second.end(); it++)
	{
		// append highway nodes
		highway.insert(highway.end(), it->begin(), it->end());

		// order highway indices
		// example: count = 6
		// 0     2     4
		// x --- x --- x 
		// |		   |
		// x --- x --- x
		// 1     3     5

		// even indices 
		for (int evenInd = start; evenInd < end; evenInd += 2)
		{
			nextInd = evenInd + 2;
			if (evenInd == count - 2)
				nextInd = end;

			// append 
			highwayIndices.push_back(std::vector<int>({ evenInd, nextInd }));
		}

		// odd indices
		for (int oddInd = end; oddInd > start; oddInd -= 2)
		{
			nextInd = oddInd - 2;
			if (oddInd == start + 1)
				nextInd = start;

			// append
			highwayIndices.push_back(std::vector<int>({ oddInd, nextInd }));
		}
	}
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::mapStlToEigen(Eigen::MatrixXd& inputWays, Eigen::MatrixXi& inputIndices, Way_t& polyWays, std::vector<std::vector<int>>& polyIndices)
{
	// 3D to 2D
	for (unsigned int i = 0; i < inputWays.rows(); i++)
	{
		inputWays.row(i) = Eigen::Vector2d::Map(&polyWays[i][0], polyWays[i].size() - 1);
		inputIndices.row(i) = Eigen::Vector2i::Map(&polyIndices[i][0], polyIndices[i].size());
	}
}


Eigen::MatrixXf OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::castDoubleToFloat(Eigen::MatrixXd& doubleMatrix)
{
	Eigen::MatrixXf floatMatrix = doubleMatrix.cast<float>();
	return floatMatrix;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::getHoles(std::vector<Way_t>& innerPolygon, Eigen::MatrixXd& holePoints)
{
	// midpoints container
	QVector<double> holeMidpoints;

	//for (int i = 0; i < innerPolygon.second.size(); i++)
	for (auto& way : innerPolygon)
	{
		// hole mid-point
		double x = 0, y = 0;
		for (auto& node : way)
		{
			x += node.x();
			y += node.y();
		}
		holeMidpoints.append(x / way.size());
		holeMidpoints.append(y / way.size());
	}

	// setup holePoints
	int holeCount = holeMidpoints.size() / 2;
	if (holeCount) {
		holePoints.resize(holeCount, 2);
		// stl vector<double> to Eigen::MatrixXd
		// special case: holeCount = 1
		if (holeCount == 1) {
			holePoints(0, 0) = holeMidpoints[0];
			holePoints(0, 1) = holeMidpoints[1];
		}
		else {	// holeCount > 1
			for (unsigned int i = 0; i < holeCount; i++) {
				int index = i * 2;
				holePoints(i, 0) = holeMidpoints[index];
				holePoints(i, 1) = holeMidpoints[index + 1];
			}
			//holePoints.row(i) = Eigen::Vector2d::Map(holeMidpoints.data(), holeMidpoints.size());
		}

	}
}


QDomNodeList OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::getPolygonList(QDomNodeList& relationWaysList, const QString& role)
{
	QDomNodeList polyList;
	int polyIter = 0;

	for (int i = 0; i < relationWaysList.count(); i++) {
		QDomNode relationWay = relationWaysList.at(i);
		if (relationWay.toElement().attribute("role") == role) {
			polyList.at(polyIter).appendChild(relationWay);
			polyIter += 1;
		}
	}
	return polyList;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::modifyRelationElements(std::vector<QDomElement>& relationWaysList, const QString attribute, const QString value)
{
	// use std::remove_if to remove elements without the desired attribute
	auto it = std::remove_if(relationWaysList.begin(), relationWaysList.end(),
		[&](const QDomElement& element) {
			return element.attribute(attribute) != value;
		});

	// erase the removed elements from the vector
	relationWaysList.erase(it, relationWaysList.end());
}


double OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::isWayContained(const QString miscID, const std::unordered_map<QString, FeatureBBox_t>& bboxContainer)
{
	// get bounds of the current way
	auto it = bboxContainer.find(miscID);
	// if not found
	if (it == bboxContainer.end())
		return 0.5;

	// get the coordinates
	auto currentBounds = it->second;
	// south-west-north-east
	double wayMinLat = std::get<0>(currentBounds);
	double wayMinLon = std::get<1>(currentBounds);
	double wayMaxLat = std::get<2>(currentBounds);
	double wayMaxLon = std::get<3>(currentBounds);

	// count num. ways containing the current way within
	double height = 0.5;
	for (const auto& container : bboxContainer) {

		// check if id is not the same
		if (it->first == container.first)
			continue;

		// get bounds of all ways
		double minlat = std::get<0>(container.second);
		double minlon = std::get<1>(container.second);
		double maxlat = std::get<2>(container.second);
		double maxlon = std::get<3>(container.second);

		// check if within
		if (wayMinLat >= minlat && wayMinLon >= minlon && wayMaxLat <= maxlat && wayMaxLon <= maxlon)
			// increment the height
			height += 0.5;
	}
	return height;
}


std::vector<OsmFeature_t> OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readOsmGeometry(QDomElement& root)
{
	// containers
	// final output
	std::vector<OsmFeature_t> osmData;
	// osm features
	OsmFeature_t			highways;			highways.first = "highway";
	OsmFeature_t			buildings;			buildings.first = "building";
	OsmFeature_t			miscellaneous;		miscellaneous.first = "miscellaneous";

	// read OSM data 'relation' (building or miscellanous types)
	unsigned int numRelation = osmGeometryContainer_.relationList.size();
	//if (!root.namedItem("relation").isNull())
	if (numRelation > 0)
	{
		//for (unsigned int relIt = 0; relIt < relationsList.count(); relIt++)
		for (unsigned int relIt = 0; relIt < numRelation; relIt++)
		{
			//QDomElement relationElement = relationsList.at(relIt).toElement();
			QDomElement relationElement = osmGeometryContainer_.relationList.at(relIt);

			// invalid -> relation within relation OR incomplete geometry
			if (isValidMemberRelation(relationElement))
				continue;

			QString miscInfo;

			// find if 'building' or 'misc.' relation
			if (retrieveFeatureAttribute<std::vector<QString>>(relationElement, { "type", "building" }, { "site", "building" }).isEmpty()) {
				miscInfo = retrieveFeatureAttribute<std::vector<QString>>(relationElement, osmGeometryContainer_.miscTypes);
			}


			if (!miscInfo.isEmpty())
				readRelation(miscellaneous, relationElement, "member");
			else
				readRelation(buildings, relationElement, "member");
		}
	}

	// read osm element 'way' (can be of type 'building', 'highway' or 'miscellaneous')
	// #TODO: modify implementation of osmGeometryContainer_.wayList to delete 'way' elements read in 'relation'
	unsigned int numWays = osmGeometryContainer_.wayList.size();
	bool ringCheck;

	for (unsigned int wayIt = 0; wayIt < numWays; wayIt++) {

		QDomElement wayElement = osmGeometryContainer_.wayList.at(wayIt).toElement();
		QString elementId = wayElement.attribute("id");
		int elementIndex = findValue<int>(elementId, osmGeometryContainer_.wayIdPosition);

		// don't read in 'way' elements read already in 'relation' as 'member'
		if (elementIndex != -1 && !(isIncompleteGeometry(wayElement))) {

			Polygon_t wayPolygon;
			double physicalPropertyVal;

			// type "building"
			if (!retrieveFeatureAttribute<QString>(wayElement, "building").isEmpty()) {

				// set building name
				setPolygonName(wayPolygon, "building");

				// get building height
				physicalPropertyVal = retrieveBuildingHeight(wayElement);

				// read building
				Way_t building = readFeature(wayElement, "building", physicalPropertyVal);

				// only accept "closed" building structure
				if (isRing(building)) {
					wayPolygon.second.push_back(building);
					buildings.second.push_back(wayPolygon);
				}
			}
			// type "highway"
			else if (!retrieveFeatureAttribute<QString>(wayElement, "highway").isEmpty()) {

				// get highway info
				QString highwayType = retrieveFeatureAttribute<QString>(wayElement, "highway");
				setPolygonName(wayPolygon, highwayType);

				// get highway width
				physicalPropertyVal = findValue<double>(highwayType, osmGeometryContainer_.highwayWidth);
				if (physicalPropertyVal == -1)
					physicalPropertyVal = 4.0;

				// read highway
				Way_t highway = readFeature(wayElement, "highway", physicalPropertyVal);

				wayPolygon.second.push_back(highway);
				highways.second.push_back(wayPolygon);
			}
			else {	// type "miscellaneous"

				// get misc sub-feature
				QString miscInfo = retrieveFeatureAttribute<std::vector<QString>>(wayElement, osmGeometryContainer_.miscTypes);
				setPolygonName(wayPolygon, miscInfo);

				// get height
				physicalPropertyVal = isWayContained(elementId, osmGeometryContainer_.idBBox);

				// read miscellaneous sub-feature
				Way_t miscWay = readFeature(wayElement, "miscellaneous", physicalPropertyVal);

				// only accept if "closed"
				if (isRing(miscWay)) {
					wayPolygon.second.push_back(miscWay);
					miscellaneous.second.push_back(wayPolygon);
				}
			}
			resetPolygonData(wayPolygon);
		}
	}
	// append to final output
	addToOutput(osmData, highways);
	addToOutput(osmData, buildings);
	addToOutput(osmData, miscellaneous);

	return osmData;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readRelation(OsmFeature_t& baseElement, QDomElement& relationElement, QString tag)
{
	// get all sub-elements 'member's of relationElement
	QDomNodeList relationWaysList = getTags(relationElement, tag);
	std::vector<QDomElement> relationWayElements = toQDomElementVector(relationWaysList);

	// misc. relation
	if (baseElement.first == "miscellaneous") {

		// get misc. type
		QString miscType = retrieveFeatureAttribute<std::vector<QString>>(relationElement, osmGeometryContainer_.miscTypes);

		// only obtain members with `role="outer"` attribute 
		modifyRelationElements(relationWayElements, "role", "inner");
		readMiscellaneousMultipolygon(relationWayElements, baseElement, miscType);
	}

	else {	// building relation

		// get relation type
		QString relationType = retrieveFeatureAttribute<QString>(relationElement, "type");

		// get height from "building:levels" attribute
		double height = retrieveBuildingHeight(relationElement);

		// could be either 'building' or 'miscellaneous' structure (miscellaneous exists only as multipolygon)
		if (relationType == "multipolygon") {

			// check if all the 'way' members of the 'relation' element in the correct order
			if (relationWayElements.front().attribute("role") != "outer")
				std::reverse(relationWayElements.begin(), relationWayElements.end());

			readBuildingMultipolygon(relationWayElements, baseElement, height);
		}
		else if (relationType == "building") {

			// check if 'role="outline"' or 'role="outer"'
			if (relationWayElements.front().attribute("role") != "outline" && relationWayElements.front().attribute("role") != "part") {

				// get first element which should be of 'role="outline"'
				std::reverse(relationWayElements.begin(), relationWayElements.end());

				QDomElement outlineElement = relationWayElements.front().toElement();

				Polygon_t buildingPolygon = readBuildingTypeRelation(outlineElement, height);
				setPolygonName(buildingPolygon, "building");

				baseElement.second.push_back(buildingPolygon);
			}
			else {	// treat it as a multipolygon

				// check if all the 'way' members of the 'relation' element in the correct order
				if (relationWayElements.front().attribute("role") != "outer")
					std::reverse(relationWayElements.begin(), relationWayElements.end());

				readBuildingMultipolygon(relationWayElements, baseElement, height);
			}
		}
		else if (relationType == "site")	// type = 'site'
			readSiteTypeRelation(relationWayElements, baseElement, height);
	}
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readBuildingMultipolygon(std::vector<QDomElement>& buildingList, OsmFeature_t& building, double height)
{
	// initialization
	QString lastRole = "outer";
	bool lastWayClosed = false;
	int distinctPoly = 0;

	// container
	Polygon_t poly;
	Way_t openWay;

	// set name
	setPolygonName(poly, "multipolygon");

	for (const QDomElement& polyWayElement : buildingList) {

		// initialization of variables for each loop
		bool currentWayClosed;
		QString currentRole = polyWayElement.attribute("role");
		QString polyWayId = polyWayElement.attribute("ref");

		QDomElement wayElement = mapIdToIndex(polyWayId);

		// way doesn't exist independantly (i.e. only within relation element)
		if (wayElement.isNull())
			wayElement = polyWayElement;

		Way_t currentWay = readFeature(wayElement, building.first, height);

		// check if the current way is closed (ring) or open
		currentWayClosed = isRing(currentWay);

		// check for mulitpolygon cases -> https://wiki.openstreetmap.org/wiki/Relation:multipolygon#Multiple_ways_forming_a_ring
		if (currentRole == "outer") {

			if (currentRole == lastRole) {
				// "outer" followed by "outer" role
				if (lastWayClosed == currentWayClosed && lastWayClosed) {
					building.second.push_back(poly);
					// clear all polygon data
					resetPolygonData(poly);
					distinctPoly = 0;
				}
			}
			else {	// lastRole != currentRole

			 // reset polygon when distinctPolygon = 1
				if (distinctPoly == 1) {
					building.second.push_back(poly);
					resetPolygonData(poly);
					distinctPoly = 0;
				}
			}

			// polygon boundary
			if (currentWayClosed) {		// polygon boundary closed

				poly.second.insert(poly.second.begin(), currentWay);
				distinctPoly += 1;

			}
			else {	// polygon boundary not closed

			 // add way to polygon list
				openWay.insert(openWay.end(), currentWay.begin(), currentWay.end());

				// check way "closed" after insertion of another way
				currentWayClosed = isRing(currentWay);
				if (currentWayClosed) {

					poly.second.insert(poly.second.begin(), openWay);
					openWay.clear();
				}
			}

		}
		else {	// currentRole = "inner"

		 // polygon boundary closed
			if (currentWayClosed) {
				poly.second.insert(poly.second.end(), currentWay);

			}
			else {	// polygon boundary not closed

			 // add way to polygon list
				openWay.insert(openWay.end(), currentWay.begin(), currentWay.end());

				// check if way "closed" after insertion of another way
				currentWayClosed = isRing(openWay);
				if (currentWayClosed) {

					poly.second.insert(poly.second.end(), openWay);
					openWay.clear();
				}
			}
		}
		// set last role & check
		lastRole = currentRole;
		lastWayClosed = currentWayClosed;

		deleteWayFromMap(polyWayId);
	}

	// append remaining polygon data
	if (poly.second.size() != 0)
		building.second.push_back(poly);
}

void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readMiscellaneousMultipolygon(std::vector<QDomElement>& miscList, OsmFeature_t& miscellaneous, const QString miscType)
{
	// container
	Polygon_t poly;
	Way_t openWay;

	// set name
	setPolygonName(poly, miscType);

	for (const QDomElement& miscElement : miscList) {

		// get height
		double height = isWayContained(miscElement.attribute("id"), osmGeometryContainer_.idBBox);

		Way_t currentWay = readFeature(miscElement, "miscellaneous", height);

		// check closed
		bool currentWayClosed = isRing(currentWay);

		// polygon boundary
		if (currentWayClosed) {	 // polygon boundary closed
			poly.second.insert(poly.second.begin(), currentWay);
		}
		else {	// polygon boundary not closed

		 // add way to polygon list
			openWay.insert(openWay.end(), currentWay.begin(), currentWay.end());

			// check way "closed" after insertion of another way
			currentWayClosed = isRing(currentWay);
			if (currentWayClosed) {
				poly.second.insert(poly.second.begin(), openWay);
			}
		}
	}
	miscellaneous.second.push_back(poly);
}

// #TODO: include support of 'role="part"'; for now only supports 'role="outline"'
Polygon_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readBuildingTypeRelation(QDomElement& outlineElement, double height)
{
	Polygon_t building;

	// get reference
	QString outlineId = outlineElement.attribute("ref");
	QDomElement wayElement = mapIdToIndex(outlineId);

	if (wayElement.isNull())
		wayElement = outlineElement;

	// get the way nodes
	Way_t outlineWay = readFeature(wayElement, "building", height);

	// only return closed ways
	if (isRing(outlineWay))
		building.second.push_back(outlineWay);

	deleteWayFromMap(outlineId);

	return building;
}


void OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readSiteTypeRelation(std::vector<QDomElement>& siteList, OsmFeature_t& feature, double height)
{
	Polygon_t sitePoly;
	setPolygonName(sitePoly, "site");

	for (int siteIt = 0; siteIt < siteList.size(); siteIt++) {

		// individual site way member
		QDomElement siteMember = siteList.at(siteIt).toElement();

		// get reference to 'way'
		QString siteElementId = siteMember.attribute("ref");
		QDomElement siteElement = mapIdToIndex(siteElementId);
		if (siteElement.isNull())
			siteElement = siteMember;

		// get height for individual site element
		height = retrieveBuildingHeight(siteElement);

		Way_t siteWay = readFeature(siteElement, "building", height);

		// only return closed ways
		if (isRing(siteWay))
			sitePoly.second.push_back(siteWay);

		deleteWayFromMap(siteElementId);
	}

	feature.second.push_back(sitePoly);
}


Way_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readFeature(const QDomElement& feature, const QString featureType, double physicalProperty)
{
	if (physicalProperty == 4.0 && featureType == "building") {
		if (!feature.namedItem("tag").isNull())
			physicalProperty = retrieveBuildingHeight(feature);
	}

	QDomNodeList nodes = getTags(feature, "nd");
	return readNodes(featureType, nodes, physicalProperty);
}


Way_t OpenInfraPlatform::Core::OsmDataConverter::OsmGeometry::readNodes(QString featureType, QDomNodeList& nodeList, double propertyValue)
{
	Way_t nodes;

	// get all nodes
	for (unsigned int nodeIt = 0; nodeIt < nodeList.count(); nodeIt++) {
		QDomElement nodeElement = nodeList.at(nodeIt).toElement();
		Node_t node = extractLatLon(nodeElement);
		nodes.push_back(node);
	}

	// specify extrusion direction
	extrusionDirection_ = Direction::Z;

	if (featureType == "highway") {
		nodes = offsetPoints(nodes, propertyValue);
		// change propertyValue now to extrude in z-direction
		propertyValue = 2.0;
	}
	extrude(nodes, propertyValue);

	return nodes;
}