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

#include "OpenInfraPlatform/Infrastructure/Export/ExportOkstraOWL.h"
#include "raptor2/raptor2.h"
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>
#include <iomanip>

OpenInfraPlatform::Infrastructure::ExportOkstraOWL::ExportOkstraOWL(buw::ReferenceCounted<buw::AlignmentModel> am,
                                                                    buw::ReferenceCounted<buw::DigitalElevationModel> dem,
                                                                    const std::string& filename)
    : Export(am, dem, filename) {
	if (true) // foaf test
	{
		FILE* outfile = fopen(filename.c_str(), "w");

		raptor_world* world = raptor_new_world();

		raptor_serializer* rdf_serializer = nullptr;

		if (boost::ends_with(filename, "rdf"))
			rdf_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
		else
			rdf_serializer = raptor_new_serializer(world, "turtle");

		raptor_serializer_start_to_file_handle(rdf_serializer, nullptr, outfile);

		const unsigned char* okstra_prefix = (const unsigned char*)"okstra";
		raptor_uri* okstra_uri = raptor_new_uri(world, (const unsigned char*)"http://okstraowl.org/0.1/");
		raptor_serializer_set_namespace(rdf_serializer, okstra_uri, okstra_prefix);

		const unsigned char* rdf_prefix = (const unsigned char*)"rdf";
		raptor_uri* rdf_uri = raptor_new_uri(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#");
		raptor_serializer_set_namespace(rdf_serializer, rdf_uri, rdf_prefix);

		std::vector<std::string> collectedAxisUniqueBlankTermNames;

		for (int i = 0; i < am->getAlignmentCount(); i++) {
			buw::ReferenceCounted<buw::IAlignment3D> alignment = am->getAlignment(i);
			buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);
			buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = alignment2D->getHorizontalAlignment();
			buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment = alignment2D->getVerticalAlignment();

			buw::String axisName = am->getAlignments()[i]->getName();

			std::stringstream axisUniqueBlankTermName;
			axisUniqueBlankTermName << "axis_" << i;

			collectedAxisUniqueBlankTermNames.push_back(axisUniqueBlankTermName.str());

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/Achse");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			// Export "Achselement" instances of current horizontal alignment
			std::vector<std::string> collectedAxisElementUniqueBlankTermNames;
			double station = horizontalAlignment->getStartStation();

			// write horizontal alignment
			for (int k = 0; k < horizontalAlignment->getAlignmentElementCount(); k++) {
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> element = horizontalAlignment->getAlignmentElementByIndex(k);

				std::stringstream axisElementUniqueBlankTermName;
				axisElementUniqueBlankTermName << "axis_" << i << "_element_" << k;

				collectedAxisElementUniqueBlankTermNames.push_back(axisElementUniqueBlankTermName.str());

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/Achselement");

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Anfangsstation_rechnerisch___Achselement");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(station).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Laenge___Achselement");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(element->getLength()).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					buw::Vector2d direction = (element->getEndPosition() - element->getStartPosition());
					direction.normalize();

					double angle = acos(direction.x());

					if (direction.y() < 0)
						angle = (2 * M_PI) - angle;

					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Richtung___Achselement");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(angle).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				if (element->getAlignmentType() == eHorizontalAlignmentType::Arc || element->getAlignmentType() == eHorizontalAlignmentType::Clothoid) {
					double radius = 0;
					element->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart, &radius);

					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Radius_zu_Beginn___Achselement");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(radius).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				if (element->getAlignmentType() == eHorizontalAlignmentType::Arc || element->getAlignmentType() == eHorizontalAlignmentType::Clothoid) {
					double radius = 0;
					element->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd, &radius);

					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Radius_am_Ende___Achselement");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(radius).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Elementtyp___Achselement");

					std::string langtext = std::to_string(1);
					if (element->getAlignmentType() == eHorizontalAlignmentType::Arc)
						langtext = std::to_string(2);
					if (element->getAlignmentType() == eHorizontalAlignmentType::Clothoid)
						langtext = std::to_string(12);

					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)langtext.c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				station += element->getLength();
			}

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Bezeichnung");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)axisName.toCString());

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Art_Achse.1");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"Hauptachse");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			// add all "Achselement" to "Achse"
			for (const std::string& axisElementName : collectedAxisElementUniqueBlankTermNames) {
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/hat_Achselement___Achse");
				triple->object = raptor_new_term_from_blank(world, (const unsigned char*)axisElementName.c_str());

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/Achse");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			// write vertical alignment

			std::stringstream gradientUniqueBlankTermName;
			gradientUniqueBlankTermName << "gradient_axis_" << i;

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)gradientUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/Gradiente");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}


			// hat_Gradiente
			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/hat_Gradiente___Achse");
				triple->object = raptor_new_term_from_blank(world, (const unsigned char*)gradientUniqueBlankTermName.str().c_str());

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

		}
		

		// Create "Trasse"
		{
			raptor_statement* triple = NULL;
			triple = raptor_new_statement(world);

			triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)"trasse1");
			triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
			triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/Trasse");

			raptor_serializer_serialize_statement(rdf_serializer, triple);
			raptor_free_statement(triple);
		}

		// add all elements of "Achse" to "Trasse"
		for (const std::string& axisElementName : collectedAxisUniqueBlankTermNames) {
			raptor_statement* triple = NULL;
			triple = raptor_new_statement(world);

			triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)"trasse1");
			triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/hat_Achse___Trasse");
			triple->object = raptor_new_term_from_blank(world, (const unsigned char*)axisElementName.c_str());

			raptor_serializer_serialize_statement(rdf_serializer, triple);
			raptor_free_statement(triple);
		}

		for (int i = 0; i < dem->getSurfaceCount(); i++) {
			buw::String name = dem->getSurface(i)->getName();

			std::stringstream dgmUniqueBlankTermName;
			dgmUniqueBlankTermName << "dgm_" << i << "_element_" << i;

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dgmUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/DGM");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dgmUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Bezeichnung");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)name.toCString());

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			// out << "\t" << "okstra:hat_Dreiecke [" << std::endl;

			buw::ReferenceCounted<buw::Surface> surface = dem->getSurface(i);

			const std::vector<buw::Vector3d>& points = surface->getPoints();

			const std::vector<buw::Vector3i>& faces = surface->getTriangeFaces();

			for (size_t k = 0; k < faces.size(); ++k) { // t buw::Vector3i& face : faces) {
				const buw::Vector3i& face = faces[i];

				std::stringstream dreieckUniqueBlankTermName;
				dreieckUniqueBlankTermName << "dgm_" << i << "_dreieck_" << k;

				// out << "\t\t" << "okstra:Dreieck [" << std::endl;

				// create "Dreieck"
				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dreieckUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/Dreieck");

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				// add "Dreieck to DGM"
				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dgmUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/hat_Dreiecke___DGM");
					triple->object = raptor_new_term_from_blank(world, (unsigned char*)dreieckUniqueBlankTermName.str().c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				// allgemeines Punktobjekt

				for (int p = 0; p < 3; p++) {
					std::stringstream allgemeinesPunktobjektUniqueBlankTermName;
					allgemeinesPunktobjektUniqueBlankTermName << "dgm_" << i << "_dreieck_" << k << "_allgPunkt_" << p;

					{
						raptor_statement* triple = NULL;
						triple = raptor_new_statement(world);

						triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)allgemeinesPunktobjektUniqueBlankTermName.str().c_str());
						triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
						triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/0.1/allgemeines_Punktobjekt");

						raptor_serializer_serialize_statement(rdf_serializer, triple);
						raptor_free_statement(triple);
					}

					{
						std::stringstream ss;
						const buw::Vector3d& p0 = points[face[p]];
						ss << std::setprecision(9) << "Point(" << p0.x() << "," << p0.y() << "," << p0.z() << ")";

						raptor_statement* triple = NULL;
						triple = raptor_new_statement(world);

						triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)allgemeinesPunktobjektUniqueBlankTermName.str().c_str());
						triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/Punktgeometrie___allgemeines_Punktobjekt");
						triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)ss.str().c_str());

						raptor_serializer_serialize_statement(rdf_serializer, triple);
						raptor_free_statement(triple);
					}

					// Dreieck -> okstra:hat_Punkte
					{
						raptor_statement* triple = NULL;
						triple = raptor_new_statement(world);

						triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dreieckUniqueBlankTermName.str().c_str());
						triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/hat_Punkte___Dreieck");
						triple->object = raptor_new_term_from_blank(world, (unsigned char*)allgemeinesPunktobjektUniqueBlankTermName.str().c_str());

						raptor_serializer_serialize_statement(rdf_serializer, triple);
						raptor_free_statement(triple);
					}
				}

				/*
				{
				    std::stringstream ss;
				    ss << "\"Point(" << p0.x() << " " << p0.y() << " " << p0.z() << ")\"";
				    
				    raptor_statement* triple = NULL; triple = raptor_new_statement(world);

				    triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dgmUniqueBlankTermName.str().c_str());
				    triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/0.1/allgemeines_Punktobjekt");
				    triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)ss.str().c_str());

				    raptor_serializer_serialize_statement(rdf_serializer, triple); raptor_free_statement(triple);
				}
*/
				// out << "\t\t\t" << "okstra:allgemeines_Punktobjekt " << "\"Point(" << p0.x() << " " << p0.y() << " " << p0.z() << ")\" ;" << std::endl;
				// out << "\t\t\t" << "okstra:allgemeines_Punktobjekt " << "\"Point(" << p1.x() << " " << p1.y() << " " << p1.z() << ")\" ;" << std::endl;
				// out << "\t\t\t" << "okstra:allgemeines_Punktobjekt " << "\"Point(" << p2.x() << " " << p2.y() << " " << p2.z() << ")\"" << std::endl;

				// out << "\t\t" << "]";

				if (i != faces.size() - 1) {
					// out << " ;";
				}

				// out << std::endl;
			}

			// out << "\t" << "] ." << std::endl << std::endl;
		}

		raptor_serializer_serialize_end(rdf_serializer);
		raptor_free_serializer(rdf_serializer);

		raptor_free_world(world);

		fclose(outfile);

		return;
	}
}

OpenInfraPlatform::Infrastructure::ExportOkstraOWL::~ExportOkstraOWL() {
}

void OpenInfraPlatform::Infrastructure::ExportOkstraOWL::fallbackTerainOutput(buw::ReferenceCounted<buw::AlignmentModel> am,
                                                                              buw::ReferenceCounted<buw::DigitalElevationModel> dem,
                                                                              const std::string& filename) {
	std::ofstream out(filename.c_str());

	out << std::setprecision(9) << std::showpoint << std::fixed;

	out << "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> ." << std::endl;
	out << "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> ." << std::endl;
	out << "@prefix okstra: <http://okstraowl.org/def/2017/okstraowl#> ." << std::endl;
	out << std::endl;

	for (int i = 0; i < am->getAlignmentCount(); i++) {
		buw::String name = am->getAlignments()[i]->getName();

		out << "<#" << name.toCString() << ">" << std::endl;
		out << "\t"
		    << "a okstra:Trasse ;" << std::endl;
		out << "\t"
		    << "okstra:Bezeichnung \"" << name.toCString() << "\"" << std::endl;

		out << "\t"
		    << "okstra:hat_Achse [" << std::endl;

		buw::ReferenceCounted<buw::IAlignment3D> alignment = alignmentModel_->getAlignment(i);
		buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);
		buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = alignment2D->getHorizontalAlignment();
		buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment = alignment2D->getVerticalAlignment();

		for (int i = 0; i < horizontalAlignment->getAlignmentElementCount(); i++) {
		}
		out << "\t\t"
		    << "okstra:Achse [" << std::endl;

		out << "\t\t"
		    << "] ;" << std::endl;

		out << "\t"
		    << "] ;" << std::endl;

		out << " ." << std::endl << std::endl;
	}

	for (int i = 0; i < dem->getSurfaceCount(); i++) {
		buw::String name = dem->getSurface(i)->getName();

		out << "<#" << name.toCString() << ">" << std::endl;
		out << "\t"
		    << "a okstra:DGM ;" << std::endl;
		out << "\t"
		    << "okstra:Bezeichnung \"" << name.toCString() << "\""
		    << " ;" << std::endl;

		out << "\t"
		    << "okstra:hat_Dreiecke [" << std::endl;

		buw::ReferenceCounted<buw::Surface> surface = dem->getSurface(i);

		const std::vector<buw::Vector3d>& points = surface->getPoints();

		const std::vector<buw::Vector3i>& faces = surface->getTriangeFaces();
		for (size_t i = 0; i < faces.size(); ++i) { // t buw::Vector3i& face : faces) {
			const buw::Vector3i& face = faces[i];

			out << "\t\t"
			    << "okstra:Dreieck [" << std::endl;

			const buw::Vector3d& p0 = points[face[0]];
			const buw::Vector3d& p1 = points[face[1]];
			const buw::Vector3d& p2 = points[face[2]];

			out << "\t\t\t"
			    << "okstra:allgemeines_Punktobjekt "
			    << "\"Point(" << p0.x() << " " << p0.y() << " " << p0.z() << ")\" ;" << std::endl;
			out << "\t\t\t"
			    << "okstra:allgemeines_Punktobjekt "
			    << "\"Point(" << p1.x() << " " << p1.y() << " " << p1.z() << ")\" ;" << std::endl;
			out << "\t\t\t"
			    << "okstra:allgemeines_Punktobjekt "
			    << "\"Point(" << p2.x() << " " << p2.y() << " " << p2.z() << ")\"" << std::endl;

			out << "\t\t"
			    << "]";

			if (i != faces.size() - 1) {
				out << " ;";
			}

			out << std::endl;
		}

		out << "\t"
		    << "] ." << std::endl
		    << std::endl;
	}

	out.close();
}
