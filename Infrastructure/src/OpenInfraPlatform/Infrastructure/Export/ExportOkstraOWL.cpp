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
		raptor_uri* okstra_uri = raptor_new_uri(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#");
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
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Achse");

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
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Achselement");

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Anfangsstation_rechnerisch___Achselement");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(station).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Laenge___Achselement");
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
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Richtung___Achselement");
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
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Radius_zu_Beginn___Achselement");
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
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Radius_am_Ende___Achselement");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(radius).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisElementUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Elementtyp___Achselement");

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
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Bezeichnung");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)axisName.toCString());

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Art_Achse.1");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"Hauptachse");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			// add all "Achselement" to "Achse"
			for (const std::string& axisElementName : collectedAxisElementUniqueBlankTermNames) {
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#hat_Achselement___Achse");
				triple->object = raptor_new_term_from_blank(world, (const unsigned char*)axisElementName.c_str());

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Achse");

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
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Gradiente");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}


			// hat_Gradiente
			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)axisUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#hat_Gradiente___Achse");
				triple->object = raptor_new_term_from_blank(world, (const unsigned char*)gradientUniqueBlankTermName.str().c_str());

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}


			enum class OKSTRA_PVI_Type { Start, Line, Parabola };

			struct OKSTRA_PVI {
				OKSTRA_PVI_Type pvi_type;
				buw::Vector2d Position;

				// pvi_type : Parabola
				double Ausrundung;
			};

			std::vector<OKSTRA_PVI> pvis;

			/*double*/ station = verticalAlignment->getStartStation();
			for (int i = 0; i < verticalAlignment->getAlignmentElementCount(); i++) {
				buw::ReferenceCounted<buw::VerticalAlignmentElement2D> element = verticalAlignment->getAlignmentElementByIndex(i);

				if (i == 0) {
					OKSTRA_PVI pvi;
					pvi.pvi_type = OKSTRA_PVI_Type::Start;
					pvi.Position = element->getStartPosition();
					pvis.push_back(pvi);
				}

				if (i == verticalAlignment->getAlignmentElementCount() - 1
					|| (element->getAlignmentType() == buw::eVerticalAlignmentType::Line
						&& verticalAlignment->getAlignmentElementByIndex(i + 1)->getAlignmentType() != buw::eVerticalAlignmentType::Parabola)) {
					OKSTRA_PVI pvi;
					pvi.pvi_type = OKSTRA_PVI_Type::Line;
					pvi.Position = element->getEndPosition();
					pvis.push_back(pvi);
				}

				if (element->getAlignmentType() == buw::eVerticalAlignmentType::Parabola) {
					OKSTRA_PVI pvi;
					pvi.pvi_type = OKSTRA_PVI_Type::Parabola;
					element->genericQuery(buw::eAlignmentElementQueryId::PVI, &pvi.Position);

					double T, startGradient, endGradient;
					element->genericQuery(buw::eAlignmentElementQueryId::IntersectionPointDistance, &T);
					element->genericQuery(buw::eAlignmentElementQueryId::StartGradient, &startGradient);
					element->genericQuery(buw::eAlignmentElementQueryId::EndGradient, &endGradient);

					pvi.Ausrundung = abs(T / (endGradient - startGradient));

					pvis.push_back(pvi);
				}
			}

			for (int ki = 0; ki < pvis.size(); ki++) {

				std::stringstream gradKoorUniqueBlankTermName;
				gradKoorUniqueBlankTermName << "axis" << i << "_gradKoor_" << ki;

				// Add "Grad_Koor"
				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)gradKoorUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Grad_Koor");

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}
			

				//Oklabi::Fachobjekt* gradKoor = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Grad_Koor", version));
				//gradiente->FuegeHinzu("hat_Grad_Koor", Oklabi::AnyType::Erzeuge(gradKoor));
		
				//gradKoor->Setze("Station", Oklabi::AnyType::Erzeuge(pvis[i].Position.x()));
				//gradKoor->Setze("Hoehe", Oklabi::AnyType::Erzeuge(pvis[i].Position.y()));

				// create okstra:Station___Grad_Koor 
				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)gradKoorUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Station___Grad_Koor");
					double station = pvis[i].Position.x();
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(station).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)gradKoorUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Hoehe___Grad_Koor");
					double hoehe = pvis[i].Position.y();
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(hoehe).c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				// hat_Grad_Koor

				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)gradientUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#hat_Grad_Koor___Gradiente");
					triple->object = raptor_new_term_from_blank(world, (const unsigned char*)gradKoorUniqueBlankTermName.str().c_str());

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				if (pvis[i].pvi_type == OKSTRA_PVI_Type::Parabola) {




					std::stringstream ausrundungUniqueBlankTermName;
					ausrundungUniqueBlankTermName << "axis" << i << "_gradKoor_" << ki << "_ausrundung";

					
					//Oklabi::Fachobjekt* ausrundung = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Ausrundung", version));
					// Add "Ausrundung"
					{
						raptor_statement* triple = NULL;
						triple = raptor_new_statement(world);

						triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)ausrundungUniqueBlankTermName.str().c_str());
						triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
						triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Ausrundung");

						raptor_serializer_serialize_statement(rdf_serializer, triple);
						raptor_free_statement(triple);
					}

					//gradKoor->FuegeHinzu("hat_Ausrundung", Oklabi::AnyType::Erzeuge(ausrundung));
					// Add "hat_Ausrundung___Grad_Koor"
					{
						raptor_statement* triple = NULL;
						triple = raptor_new_statement(world);

						triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)gradKoorUniqueBlankTermName.str().c_str());
						triple->predicate = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#hat_Ausrundung___Grad_Koor");
						triple->object = raptor_new_term_from_blank(world, (const unsigned char*)ausrundungUniqueBlankTermName.str().c_str());

						raptor_serializer_serialize_statement(rdf_serializer, triple);
						raptor_free_statement(triple);
					}

					//ausrundung->Setze("Scheitelradius", Oklabi::AnyType::Erzeuge(pvis[i].Ausrundung));


					{
						raptor_statement* triple = NULL;
						triple = raptor_new_statement(world);

						triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)ausrundungUniqueBlankTermName.str().c_str());
						triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Scheitelradius___Ausrundung");
						double Ausrundung = pvis[i].Ausrundung;
						triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)std::to_string(Ausrundung).c_str());

						raptor_serializer_serialize_statement(rdf_serializer, triple);
						raptor_free_statement(triple);
					}
				}
			}
		}
		

		// Create "Trasse"
		{
			raptor_statement* triple = NULL;
			triple = raptor_new_statement(world);

			triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)"trasse1");
			triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
			triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Trasse");

			raptor_serializer_serialize_statement(rdf_serializer, triple);
			raptor_free_statement(triple);
		}

		// add all elements of "Achse" to "Trasse"
		for (const std::string& axisElementName : collectedAxisUniqueBlankTermNames) {
			raptor_statement* triple = NULL;
			triple = raptor_new_statement(world);

			triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)"trasse1");
			triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#hat_Achse___Trasse");
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
				triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#DGM");

				raptor_serializer_serialize_statement(rdf_serializer, triple);
				raptor_free_statement(triple);
			}

			{
				raptor_statement* triple = NULL;
				triple = raptor_new_statement(world);

				triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dgmUniqueBlankTermName.str().c_str());
				triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Bezeichnung");
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
					triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Dreieck");

					raptor_serializer_serialize_statement(rdf_serializer, triple);
					raptor_free_statement(triple);
				}

				// add "Dreieck to DGM"
				{
					raptor_statement* triple = NULL;
					triple = raptor_new_statement(world);

					triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dgmUniqueBlankTermName.str().c_str());
					triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#hat_Dreiecke___DGM");
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
						triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)"http://okstraowl.org/model/2017/okstraowl#allgemeines_Punktobjekt");

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
						triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#Punktgeometrie___allgemeines_Punktobjekt");
						triple->object = raptor_new_term_from_uri_string(world, (unsigned char*)ss.str().c_str());

						raptor_serializer_serialize_statement(rdf_serializer, triple);
						raptor_free_statement(triple);
					}

					// Dreieck -> okstra:hat_Punkte
					{
						raptor_statement* triple = NULL;
						triple = raptor_new_statement(world);

						triple->subject = raptor_new_term_from_blank(world, (const unsigned char*)dreieckUniqueBlankTermName.str().c_str());
						triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#hat_Punkte___Dreieck");
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
				    triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://okstraowl.org/model/2017/okstraowl#allgemeines_Punktobjekt");
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
