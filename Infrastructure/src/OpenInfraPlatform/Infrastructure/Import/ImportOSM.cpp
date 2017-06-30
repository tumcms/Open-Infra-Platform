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

#include "ImportOSM.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"

#include <qxml.h>

#include <set>


template<typename DataType>
struct hasID : public std::unary_function < size_t, bool >
{
	explicit hasID(const size_t& cmp) : cmp_(cmp) {}
	bool operator() (const DataType &arg)
	{
		return arg.id == cmp_;
	}
	size_t cmp_;
};

class OSMXmlDoc;

template<typename T>
struct OSMRef
{
	size_t id;
	OSMXmlDoc* doc;

	OSMRef() :
		doc(nullptr)
	{}

	OSMRef(OSMXmlDoc* d) :
		doc(d)
	{}

	T* get()
	{
		std::vector<T>::iterator it = std::find_if(doc->get<T>().begin(), doc->get<T>().end(), hasID<T>(id));
		if (it != doc->get<T>().end())
			return &(*it);

		return nullptr;
	}
};

struct OSMNode
{
	size_t id;
	double lat;
	double lon;
};

struct OSMWay
{
	size_t id;
	std::string name;
	std::string highway;
	std::vector<OSMRef<OSMNode>> nodeRefs;
};

template<typename T>
struct OSMMember
{
	OSMRef<T> ref;
	std::string role;
};

struct OSMRelation
{
	size_t id;
	std::string name;
	std::string type;
	std::vector<OSMMember<OSMNode>> nodeMembers;
	std::vector<OSMMember<OSMWay>> wayMembers;
	std::vector<OSMMember<OSMRelation>> relationMembers;
};

class OSMXmlDoc : public QXmlDefaultHandler
{
	struct Element
	{
		std::string type;
		union { void* ptr; int index; } ref;
	};

	bool startElement(const QString & namespaceURI, const QString & localName,
		const QString & qName, const QXmlAttributes & atts)
	{
		Element element;
		element.type = localName.toStdString();
		element.ref.ptr = nullptr;

		if (localName == "bounds")
		{
			boundsMin_.x() = atts.value("minlat").toDouble();
			boundsMin_.y() = atts.value("maxlat").toDouble();
			boundsMax_.x() = atts.value("minlon").toDouble();
			boundsMax_.y() = atts.value("maxlon").toDouble();
		}
		else if (localName == "node")
		{
			OSMNode node;
			node.lat = atts.value("lat").toDouble();
			node.lon = atts.value("lon").toDouble();
			node.id = atts.value("id").toULongLong();

			nodes_.push_back(node);

			element.ref.index = nodes_.size() - 1;
		}
		else if (localName == "way")
		{
			OSMWay way;
			way.id = atts.value("id").toULongLong();
			ways_.push_back(way);

			element.ref.index = ways_.size() - 1;
		}
		else if (localName == "nd")
		{
			Element e = path_.back();
			if (e.type == "way")
			{
				OSMRef<OSMNode> ref(this);
				ref.id = atts.value("ref").toULongLong();
				ways_[e.ref.index].nodeRefs.push_back(ref);
			}
		}
		else if (localName == "relation")
		{
			OSMRelation relation;
			relation.id = atts.value("id").toULongLong();
			relation.type = atts.value("type").toStdString();

			relations_.push_back(relation);

			element.ref.index = relations_.size() - 1;
		}
		else if (localName == "member")
		{
			Element e = path_.back();
			if (e.type == "relation")
			{
				size_t id = atts.value("ref").toULongLong();
				std::string role = atts.value("role").toStdString();
				if (atts.value("type") == "node")
				{
					OSMMember<OSMNode> member;
					OSMRef<OSMNode> ref(this);
					ref.id = id;
					member.ref = ref;
					member.role = role;
					relations_[e.ref.index].nodeMembers.push_back(member);
				}
				else if (atts.value("type") == "way")
				{
					OSMMember<OSMWay> member;
					OSMRef<OSMWay> ref(this);
					ref.id = id;
					member.ref = ref;
					member.role = role;
					relations_[e.ref.index].wayMembers.push_back(member);
				}
				else if (atts.value("type") == "relation")
				{
					OSMMember<OSMRelation> member;
					OSMRef<OSMRelation> ref(this);
					ref.id = id;
					member.ref = ref;
					member.role = role;
					relations_[e.ref.index].relationMembers.push_back(member);
				}
			}

		}
		else if (localName == "tag")
		{
			Element e = path_.back();
			if (e.type == "relation")
			{
				if (atts.value("k") == "type")
					relations_[e.ref.index].type = atts.value("v").toStdString();
				else if (atts.value("k") == "name")
					relations_[e.ref.index].name = atts.value("v").toStdString();
			}
			else if (e.type == "way")
			{
				if (atts.value("k") == "highway")
					ways_[e.ref.index].highway = atts.value("v").toStdString();
				else if (atts.value("k") == "name")
					ways_[e.ref.index].name = atts.value("v").toStdString();
			}
		}

		path_.push_back(element);
		return true;

	}

	bool endElement(const QString & namespaceURI, const QString & localName, const QString & qName)
	{
		path_.pop_back();

		return true;
	}



public:
	template<typename T>
	std::vector<T>& get()
	{
		assert(false);
	}

	template<>
	std::vector<OSMNode>& get()
	{
		return nodes_;
	}

	template<>
	std::vector<OSMWay>& get()
	{
		return ways_;
	}

	template<>
	std::vector<OSMRelation>& get()
	{
		return relations_;
	}

	std::vector<OSMNode>& nodes()
	{
		return nodes_;
	}

	std::vector<OSMWay>& ways()
	{
		return ways_;
	}

	std::vector<OSMRelation>& relations()
	{
		return relations_;
	}

	buw::Vector2d& boundsMin()
	{
		return boundsMin_;
	}

	buw::Vector2d& boundsMax()
	{
		return boundsMax_;
	}
private:
	buw::Vector2d boundsMin_;
	buw::Vector2d boundsMax_;

	std::vector<OSMNode> nodes_;
	std::vector<OSMWay> ways_;
	std::vector<OSMRelation> relations_;

	std::vector<Element> path_;

};

#define deg2rad(d) (((d)*M_PI)/180)
#define rad2deg(d) (((d)*180)/M_PI)
#define earth_radius 6378137

class OSMMercator
{
public:
	/* The following functions take or return there results in degrees */

	static double y2lat_d(double y) { return rad2deg(2 * atan(exp(deg2rad(y))) - M_PI / 2); }
	static double x2lon_d(double x) { return x; }
	static double lat2y_d(double lat) { return rad2deg(log(tan(M_PI / 4 + deg2rad(lat) / 2))); }
	static double lon2x_d(double lon) { return lon; }

	/* The following functions take or return there results in something close to meters, along the equator */

	static double y2lat_m(double y) { return rad2deg(2 * atan(exp((y / earth_radius))) - M_PI / 2); }
	static double x2lon_m(double x) { return rad2deg(x / earth_radius); }
	static double lat2y_m(double lat) { return earth_radius * log(tan(M_PI / 4 + deg2rad(lat) / 2)); }
	static double lon2x_m(double lon) { return deg2rad(lon) * earth_radius; }

	static buw::Vector2d lonlat2xy_m(double lon, double lat) { return buw::Vector2d(lon2x_m(lon), lat2y_m(lat)); }
	static buw::Vector2d lonlat2xy_d(double lon, double lat) { return buw::Vector2d(lon2x_d(lon), lat2y_d(lat)); }
};


OSMNode* findFirst(OSMWay* wayPtr)
{
	OSMNode* firstPtr = nullptr;
	for (auto it = wayPtr->nodeRefs.begin(); it != wayPtr->nodeRefs.end(); it++)
	{
		firstPtr = it->get();
		if (firstPtr)
			break;
	}

	return firstPtr;
}

OSMNode* findSecond(OSMWay* wayPtr)
{
	OSMNode* nodePtr = nullptr;
	bool foundFirst = false;
	for (auto it = wayPtr->nodeRefs.begin(); it != wayPtr->nodeRefs.end(); it++)
	{
		OSMNode* ptr = it->get();
		if (ptr)
		{
			if (!foundFirst)
				foundFirst = true;
			else
			{
				nodePtr = ptr;
				break;
			}
		}
	}

	return nodePtr;
}

OSMNode* findLast(OSMWay* wayPtr)
{
	OSMNode* lastPtr = nullptr;
	for (auto it = wayPtr->nodeRefs.rbegin(); it != wayPtr->nodeRefs.rend(); it++)
	{
		lastPtr = it->get();
		if (lastPtr)
			break;
	}

	return lastPtr;
}

OSMNode* findSecondLast(OSMWay* wayPtr)
{
	OSMNode* nodePtr = nullptr;
	bool foundLast = false;
	for (auto it = wayPtr->nodeRefs.rbegin(); it != wayPtr->nodeRefs.rend(); it++)
	{
		OSMNode* ptr = it->get();
		if (ptr)
		{
			if (!foundLast)
				foundLast = true;
			else
			{
				nodePtr = ptr;
				break;
			}
		}
	}

	return nodePtr;
}

bool contains(OSMWay* wayPtr1, OSMWay* wayPtr2)
{
	bool found;
	for (OSMRef<OSMNode> ref2 : wayPtr2->nodeRefs)
	{
		for (OSMRef<OSMNode> ref1 : wayPtr1->nodeRefs)
		{
			found = ref1.id = ref2.id;
			if (found)
				break;
		}
		if (!found)
			break;
	}

	return found;
}

std::vector<std::string> OpenInfraPlatform::Infrastructure::ImportOSM::getDefaultFilter()
{
	return{ "motorway", "trunk", "primary", "secondary", "tertiary", "unclassified", "residential", "service", "motorway_link", "trunk_link", "primary_link", "secondary_link", "tertiary_link" };
}
std::vector<std::string> OpenInfraPlatform::Infrastructure::ImportOSM::getModeNames()
{
	return{ "None", "BasedOnAngle", "BasedOnStreetName", "Combined" };
}

template<typename T, typename Comp>
struct Matrix
{
	Matrix(int n)
	{
		assert(n > 0);

		n_ = n;
		matrix_ = new T[size()];
	}
	~Matrix()
	{
		delete matrix_;
	}

	int size() const
	{
		return (n_ * (n_ - 1)) / 2;
	}

	int index(int i1, int i2)
	{
		assert(i1 != i2);
		int j1 = std::min(i1, i2);
		int j2 = std::max(i1, i2);
		assert(j2 < n_);

		return j1 * (2 * n_ - j1 - 1) / 2 + j2 - j1 - 1;
	}

	T& operator()(int i1, int i2)
	{
		return matrix_[index(i1, i2)];
	}

	void set(int i1, T value)
	{
		for (int i = 0; i < n_; i++)
		{
			if (i != i1)
				matrix_[index(i1, i)] = value;
		}
	}

	T findBest(int* pI1, int* pI2)
	{
		assert(n_ > 1);

		Comp comp;

		int i1 = 0;
		int i2 = 1;
		T m = matrix_[0];

		for (int i = 0; i < n_; i++)
		{
			for (int j = i + 1; j < n_; j++)
			{
				T v = matrix_[index(i, j)];
				if (comp(v, m))
				{
					m = v;
					i1 = i;
					i2 = j;
				}
			}
		}

		*pI1 = i1;
		*pI2 = i2;

		return m;
	}

	int n_;
	T* matrix_;
};

struct DirectionalWay
{
	OSMWay* wayPtr;
	bool reverse;
};

typedef std::vector<DirectionalWay> Intersection;
typedef std::vector<DirectionalWay> AggregatedWay;

struct Connection
{
	DirectionalWay way1;
	DirectionalWay way2;
};

struct Helper
{
	std::vector<Connection> connections;
	std::vector<DirectionalWay> deadEnds;
};

std::map<OSMNode*, Intersection> findIntersections(const std::vector<OSMWay*>& ways)
{
	std::map<OSMNode*, Intersection> intersections;
	for (OSMWay* wayPtr : ways)
	{
		OSMNode* firstPtr = findFirst(wayPtr);
		OSMNode* lastPtr = findLast(wayPtr);

		intersections[firstPtr].push_back({ wayPtr, false });
		intersections[lastPtr].push_back({ wayPtr, true });
	}

	return intersections;
}

float compareAngle(const DirectionalWay& way1, const DirectionalWay& way2)
{
	OSMNode* n1, *m1;
	if (!way1.reverse)
	{
		n1 = findFirst(way1.wayPtr);
		m1 = findSecond(way1.wayPtr);
	}
	else
	{
		n1 = findLast(way1.wayPtr);
		m1 = findSecondLast(way1.wayPtr);
	}
	buw::Vector2d dir1 = OSMMercator::lonlat2xy_m(m1->lon, m1->lat) - OSMMercator::lonlat2xy_m(n1->lon, n1->lat);
	dir1.normalize();

	OSMNode* n2, *m2;
	if (!way2.reverse)
	{
		n2 = findFirst(way2.wayPtr);
		m2 = findSecond(way2.wayPtr);
	}
	else
	{
		n2 = findLast(way2.wayPtr);
		m2 = findSecondLast(way2.wayPtr);
	}
	buw::Vector2d dir2 = OSMMercator::lonlat2xy_m(m2->lon, m2->lat) - OSMMercator::lonlat2xy_m(n2->lon, n2->lat);
	dir2.normalize();

	buw::Vector2d mid = dir1 + dir2;
	return 1 - (mid.norm() / 2.0);
}

float compareNames(const DirectionalWay& way1, const DirectionalWay& way2)
{
	if(way1.wayPtr->name == way2.wayPtr->name)
		return 1;
	return -1;
}

Helper findConnections(const std::map<OSMNode*, Intersection>& intersections, int mode)
{
	std::vector<Connection> connections;
	std::vector<DirectionalWay> deadEnds;

	for (auto& intersection : intersections)
	{
		auto& elements = std::get<1>(intersection);
		int numElements = elements.size();

		std::list<int> indices;
		Matrix<float, std::greater<float>> matrix(numElements);

		for (int i = 0; i < numElements; i++)
		{
			indices.push_back(i);

			for (int j = i + 1; j < numElements; j++)
			{
				float value = -1;
				if (mode == 1)
					value = compareAngle(elements[i], elements[j]);
				else if (mode == 2)
					value = compareNames(elements[i], elements[j]);
				else if (mode == 3)
					value = compareAngle(elements[i], elements[j]) + 0.7 * compareNames(elements[i], elements[j]);

				matrix(i, j) = value;
			}
		}

		for (int i = 0; i < std::floor(numElements / 2.0); i++)
		{
			int i1, i2;
			float best = matrix.findBest(&i1, &i2);
			if (best < 0)
				break;

			connections.push_back({ elements[i1], elements[i2] });

			matrix.set(i1, -1);
			matrix.set(i2, -1);

			indices.remove(i1);
			indices.remove(i2);
		}

		if (indices.size() != 0)
		{
			for (int i : indices)
			{
				deadEnds.push_back(elements[i]);
			}
		}
	}

	return{ connections, deadEnds };
}

std::vector<AggregatedWay> findHalves(const std::vector<Connection>& connections, const std::vector<DirectionalWay>& deadEnds)
{
	std::vector<AggregatedWay> halves;

	// DeadEnds are starting points
	for (auto& end : deadEnds)
	{
		AggregatedWay aWay;
		aWay.push_back(end);
		halves.push_back(aWay);
	}

	int numRemaining = std::numeric_limits<int>::max();
	std::vector<Connection> remainingConnections = connections;
	while (numRemaining > 0)
	{
		std::vector<Connection> tempConnections;
		for (auto& con : remainingConnections)
		{
			bool found = false;
			for (AggregatedWay& aWay : halves)
			{
				if (aWay.back().wayPtr == con.way1.wayPtr)
				{
					assert(aWay.back().reverse != con.way1.reverse);
					aWay.push_back(con.way2);
				}
				else if (aWay.back().wayPtr == con.way2.wayPtr)
				{
					assert(aWay.back().reverse != con.way2.reverse);
					aWay.push_back(con.way1);
				}
				else
					continue;

				found = true;
				break;
			}

			if (!found)
				tempConnections.push_back(con);
		}

		// resolve loops
		if (tempConnections.size() == numRemaining)
		{
			AggregatedWay aWay1;
			aWay1.push_back(tempConnections.back().way1);

			AggregatedWay aWay2;
			aWay2.push_back(tempConnections.back().way2);

			halves.push_back(aWay1);
			halves.push_back(aWay2);

			tempConnections.pop_back();
		}

		remainingConnections = tempConnections;
		numRemaining = remainingConnections.size();
	}

	return halves;
}

std::vector<AggregatedWay> stitchHalves(const std::vector<AggregatedWay>& halves)
{
	std::vector<AggregatedWay> aggregatedWays;
	for (int i = 0; i < halves.size(); i++)
	{
		const AggregatedWay& aWay1 = halves[i];
		for (int j = i + 1; j < halves.size(); j++)
		{
			const AggregatedWay& aWay2 = halves[j];

			if (aWay1.back().wayPtr == aWay2.back().wayPtr)
			{
				assert(aWay1.back().reverse != aWay2.back().reverse);

				AggregatedWay stiched = aWay1;
				for (auto it = aWay2.rbegin() + 1; it != aWay2.rend(); it++)
				{
					stiched.push_back(*it);
					stiched.back().reverse = !stiched.back().reverse;
				}

				aggregatedWays.push_back(stiched);
				break;
			}
		}
	}

	return aggregatedWays;
}

OpenInfraPlatform::Infrastructure::ImportOSM::ImportOSM(const std::string& filename)
	:ImportOSM(filename, getDefaultFilter(), 2)
{
}

OpenInfraPlatform::Infrastructure::ImportOSM::ImportOSM(const std::string& filename, const std::vector<std::string>& filter, int mode)
	: Import(filename)
{
	alignmentModel_ = std::make_shared<buw::AlignmentModel>();
	digitalElevationModel_ = std::make_shared<buw::DigitalElevationModel>();


	QFile file(filename.c_str());
	if (!file.open(QIODevice::ReadOnly))
		assert(false);

	QXmlInputSource source(&file);

	OSMXmlDoc doc;

	QXmlSimpleReader reader;
	reader.setContentHandler(&doc);

	if (!reader.parse(source))
		assert(false);

	/*buw::Vector3d point(dlon * 40075160 * cos(n->lat * M_PI / 180) / 360, dlat * 40008000 / 360, 0); */
	buw::Vector2d centerOffset = (doc.boundsMax() - doc.boundsMin()) * 0.5 + doc.boundsMin();
	centerOffset = OSMMercator::lonlat2xy_m(centerOffset.x(), centerOffset.y());


	std::vector<OSMWay*> filtered;
	for (OSMWay& way : doc.ways())
	{
		if (std::find(filter.begin(), filter.end(), way.highway) != filter.end())
		{
			filtered.push_back(&way);
		}
	}

	std::map<OSMNode*, Intersection> intersections = findIntersections(filtered);

	Helper h = findConnections(intersections, mode);
	std::vector<Connection>& connections = h.connections;
	std::vector<DirectionalWay>& deadEnds = h.deadEnds;

	std::vector<AggregatedWay> halves = findHalves(connections, deadEnds);

	std::vector<AggregatedWay> aggregatedWays = stitchHalves(halves);

	int i = 0;
	for (const AggregatedWay& aWay : aggregatedWays)
	{
		buw::ReferenceCounted<buw::Alignment3DBased3D> alignment = std::make_shared<buw::Alignment3DBased3D>(0, Alignment3DBased3DType::Polyline);
		alignmentModel_->addAlignment(alignment);

		std::set<std::string> names;

		int offset = 0;
		for (const DirectionalWay& way : aWay)
		{

			if (way.wayPtr->name != "")
			{
				names.insert(way.wayPtr->name);
			}


			OSMNode* nodePtr = nullptr;
			if (!way.reverse)
			{
				for (auto it = way.wayPtr->nodeRefs.begin() + offset; it != way.wayPtr->nodeRefs.end(); it++)
				{
					nodePtr = it->get();
					if (nodePtr)
					{
						buw::Vector2d p = OSMMercator::lonlat2xy_m(nodePtr->lon, nodePtr->lat);
						p = p - centerOffset;
						alignment->addPoint(buw::Vector3d(p.x(), p.y(), 0));
					}
				}
			}
			else
			{
				for (auto it = way.wayPtr->nodeRefs.rbegin() + offset; it != way.wayPtr->nodeRefs.rend(); it++)
				{
					nodePtr = it->get();
					if (nodePtr)
					{
						buw::Vector2d p = OSMMercator::lonlat2xy_m(nodePtr->lon, nodePtr->lat);
						p = p - centerOffset;
						alignment->addPoint(buw::Vector3d(p.x(), p.y(), 0));
					}
				}
			}

			if (offset == 0)
				offset = 1;
		}

		if (names.empty())
		{
			alignment->setName("Alignment " + std::to_string(i));
			i++;
		}
		else
		{
			std::string alignmentName = "";
			for (const std::string& name : names)
			{
				if (alignmentName != "")
					alignmentName += " / ";
				alignmentName += name;
			}
			alignment->setName(alignmentName);
		}
	}
}