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

#include "ExportOkstraOWL.h"
#include <fstream>

#include "raptor2/raptor2.h"

static raptor_serializer* rdf_serializer;

static void
serialize_triple(void* user_data, raptor_statement* triple)
{
	raptor_serializer_serialize_statement(rdf_serializer, triple);
}

static void
declare_namespace(void* user_data, raptor_namespace *nspace)
{
	raptor_serializer_set_namespace_from_namespace(rdf_serializer, nspace);
}



OpenInfraPlatform::Infrastructure::ExportOkstraOWL::ExportOkstraOWL(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) :
Export(am, dem, filename)
{
	FILE* outfile = fopen(filename.c_str(), "w");

	raptor_world *world = NULL;
	raptor_statement* triple;

	world = raptor_new_world();

	rdf_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	raptor_serializer_start_to_file_handle(rdf_serializer, nullptr, outfile);

	triple = raptor_new_statement(world);
	triple->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://example.org/subject");
	triple->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)"http://example.org/predicate");
	triple->object = raptor_new_term_from_literal(world, (const unsigned char*)"An example literal", NULL, (const unsigned char*)"en");

	raptor_serializer_serialize_statement(rdf_serializer, triple);

	raptor_free_statement(triple);

	raptor_serializer_serialize_end(rdf_serializer);

	raptor_free_serializer(rdf_serializer);
	raptor_free_world(world);

	fclose(outfile);
}

OpenInfraPlatform::Infrastructure::ExportOkstraOWL::~ExportOkstraOWL()
{

}