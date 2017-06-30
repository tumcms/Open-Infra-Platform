// Copied and modified code from "IfcPlusPlus" library.
// This library is available under the OpenSceneGraph Public License. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and / or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* OpenSceneGraph Public License for more details.
*/

/* This file has been automatically generated using the TUM Open Infra Platform
Early Binding EXPRESS Generator. Any changes to this file my be lost in the future. */

#include <set>
#include <vector>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>
#include <locale.h>
#include <time.h>
#ifdef IfcAlignment_OPENMP
#include <omp.h>
#endif

#include <unordered_map>

#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Model.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Object.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "OpenInfraPlatform/IfcAlignment/model/UnknownEntityException.h"
#include "OpenInfraPlatform/IfcAlignment/IfcAlignmentP6EntitiesMap.h"
#include "OpenInfraPlatform/IfcAlignment/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment/reader/IfcStepReader.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		static std::tr1::unordered_map<std::string, IfcAlignmentP6EntityEnum> map_string2entity_enum(initializers_IfcAlignmentP6_entity, initializers_IfcAlignmentP6_entity + sizeof(initializers_IfcAlignmentP6_entity) / sizeof(initializers_IfcAlignmentP6_entity[0]));
		void applyBackwardCompatibility( IfcAlignmentModel::IfcVersion backward_version, IfcAlignmentP6EntityEnum type_enum, std::vector<std::string>& args );
		void applyBackwardCompatibility( std::string& keyword, std::string& step_line );
		IfcAlignmentP6Entity* createIfcAlignmentP6Entity( const IfcAlignmentP6EntityEnum entity_enum );

		void readStepLine( const std::string& line, shared_ptr<IfcAlignmentP6Entity>& entity )
		{
			char* stream_pos = (char*)line.c_str();
			if( *stream_pos != '#' )
			{
				return;
			}

			// need at least one integer here
			++stream_pos;
			if( *stream_pos == '\0' )
			{
				return;
			}

			if( !isdigit( *stream_pos ) )
			{
				return;
			}
			char* begin_id = stream_pos;

			// proceed until end of integer
			++stream_pos;
			while( *stream_pos != '\0' )
			{
				if( isdigit( *stream_pos ) )
				{
					++stream_pos;
				}
				else
				{
					break;
				}
			}

			const int id = atoi( std::string( begin_id, stream_pos-begin_id ).c_str() );

			// skip whitespace
			while( isspace( *stream_pos ) )
			{
				++stream_pos;
			}

			// next char after whitespace needs to be an "="
			if( *stream_pos != '=' )
			{
				// print error
				return;
			}
			++stream_pos;

			// skip whitespaces
			while( isspace( *stream_pos ) )
			{
				++stream_pos;
			}

			// extract keyword
			const char* keyword_begin = stream_pos;
			while( isalnum( *stream_pos ) )
			{
				++stream_pos;
			}

			std::string keyword( keyword_begin, stream_pos-keyword_begin );
			std::transform(keyword.begin(), keyword.end(), keyword.begin(), toupper);

			// proceed to '('
			if( *stream_pos != '(' )
			{
				while( *stream_pos != '\0' )
				{
					if( *stream_pos == '(' )
					{
						break;
					}
					++stream_pos;
				}
			}

			if( keyword.size() > 0 )
			{
				//std::map<std::string,IfcAlignmentP6EntityEnum>::iterator it_entity_enum = map_string2entity_enum.find( keyword );
				std::tr1::unordered_map<std::string,IfcAlignmentP6EntityEnum>::iterator it_entity_enum = map_string2entity_enum.find( keyword );
				if( it_entity_enum == map_string2entity_enum.end() )
				{
					throw UnknownEntityException( keyword );
				}
				else
				{
					IfcAlignmentP6EntityEnum entity_enum = it_entity_enum->second;

					shared_ptr<IfcAlignmentP6Entity> obj( createIfcAlignmentP6Entity( entity_enum ) );
					if( obj )
					{
						obj->setId( id );
						entity = obj;
						entity->m_entity_enum = entity_enum;

						size_t sub_length = line.size() -(stream_pos-line.c_str());
						entity->m_arguments.assign( stream_pos, sub_length );
					}
				}
			}
		}

		void copyToEndOfStepString( char*& stream_pos, char*& stream_pos_source )
		{
			// string can have escaped ticks: \' and also other escaped characters: \\  \S
			*(stream_pos++) = *(stream_pos_source++);
			bool escaped = false;
			while( *stream_pos_source != '\0' )
			{
				escaped = false;
				if( *stream_pos_source == '\\' )
				{
					if( *(stream_pos_source+1) == '\\' )
					{
						// we have a double backslash, so copy and continue
						*(stream_pos++) = *(stream_pos_source++);
						*(stream_pos++) = *(stream_pos_source++);
						continue;
					}
					*(stream_pos++) = *(stream_pos_source++);
					escaped = true;
				}

				if( *stream_pos_source == '\'' )
				{
					*(stream_pos++) = *(stream_pos_source++);
					if( escaped )
					{
						continue;
					}
					// end of string
					break;
				}
				// copy
				*(stream_pos++) = *(stream_pos_source++);
			}
		}

		IfcStepReader::IfcStepReader()
		{
		}

		IfcStepReader::~IfcStepReader()
		{
		}

		void IfcStepReader::readStreamHeader( std::string& read_in, shared_ptr<IfcAlignmentModel> model )
		{
			m_ifc_version = IfcAlignmentModel::UNDEFINED;
			m_file_schema = "";


			size_t file_header_end = read_in.find("DATA;");

			if( file_header_end != std::string::npos )
			{
				std::string file_header = read_in.substr(0,file_header_end);
				model->setFileHeader( file_header );
			}

			size_t file_schema_begin = read_in.find("FILE_SCHEMA") + 11;
			if( file_schema_begin != std::string::npos )
			{
				size_t file_schema_end = read_in.find(";",file_schema_begin);
				if( file_schema_end != std::string::npos )
				{

					m_file_schema = read_in.substr(file_schema_begin,file_schema_end-file_schema_begin);

					size_t find_whitespace = m_file_schema.find(" ");
					while(find_whitespace != std::string::npos)
					{
						m_file_schema.erase(find_whitespace,1);
						find_whitespace = m_file_schema.find(" ");
					}

					if( m_file_schema.at(0) =='(' && m_file_schema.at(m_file_schema.size()-1) ==')' )
					{
						m_file_schema = m_file_schema.substr( 1, m_file_schema.size()-2 );
					}
					if( m_file_schema.at(0) =='(' && m_file_schema.at(m_file_schema.size()-1) ==')' )
					{
						m_file_schema = m_file_schema.substr( 1, m_file_schema.size()-2 );
					}

					if (m_file_schema.size() != 0)	// modfied by Vertexwahn
					{
						if( m_file_schema.at(0) =='\'' && 
							m_file_schema.at(m_file_schema.size()-1) =='\'' )
						{
							m_file_schema = m_file_schema.substr( 1, m_file_schema.size()-2 );
						}
					}
					else
					{
						// hack: assume IFC4
						m_file_schema = "IFC4";
					}

					model->setFileSchema( m_file_schema );
					if( m_file_schema.substr(0,6).compare("IFC2X2") == 0 )
					{
						m_ifc_version = IfcAlignmentModel::IFC2X2;
					}
					else if( m_file_schema.substr(0,6).compare("IFC2X3") == 0 )
					{
						m_ifc_version = IfcAlignmentModel::IFC2X3;
					}
					else if( m_file_schema.substr(0,6).compare("IFC2X4") == 0 )
					{
						m_ifc_version = IfcAlignmentModel::IFC2X4;
					}
					else if( m_file_schema.substr(0,5).compare("IFC2X") == 0 )
					{
						m_ifc_version = IfcAlignmentModel::IFC2X;
					}
					else if( m_file_schema.compare("IFC4") == 0 )
					{
						m_ifc_version = IfcAlignmentModel::IFC4;
					}
					else if (m_file_schema.compare("IFC4x1") == 0)
					{
						m_ifc_version = IfcAlignmentModel::IFC4;
					}
					else if (m_file_schema.compare("IFC4X1") == 0)
					{
						m_ifc_version = IfcAlignmentModel::IFC4;
					}
					else if( m_file_schema.compare("IFC4RC4") == 0 )
					{
						m_ifc_version = IfcAlignmentModel::IFC4;
					}
					else
					{
						m_ifc_version = IfcAlignmentModel::UNKNOWN;
					}
				}
			}
		}

		void IfcStepReader::splitIntoStepLines( std::string& read_in, std::vector<std::string>& target_vec )
		{
			// set progress to 0
			double progress = 0.0;
			progressCallback( progress );
			const int length = (int)read_in.length();

			// sort out comments like /* ... */
			std::string buffer( read_in );
			char* stream_pos_source = &read_in[0];
			char* stream_pos = &buffer[0];

			while( *stream_pos_source != '\0' )
			{
				if( *stream_pos_source == '*' )
				{
					if( *(stream_pos_source-1) == '/' )
					{
						--stream_pos;
						// we are inside comment now, proceed to end of comment
						++stream_pos_source;
						while( *stream_pos_source != '\0' )
						{
							if( *stream_pos_source == '/' )
							{
								if( *(stream_pos_source-1) == '*' )
								{
									break;
								}
							}
							++stream_pos_source;
						}
						++stream_pos_source;
						continue;
					}
				}
				else if( *stream_pos_source == '\'' )
				{
					copyToEndOfStepString( stream_pos, stream_pos_source );
				}

				if( *stream_pos_source == '\n' )
				{
					// omit newlines
					++stream_pos_source;
					continue;
				}
				*(stream_pos++) = *(stream_pos_source++);
			}
			// copy end of string
			*(stream_pos) = *(stream_pos_source);

			// find beginning of data lines
			stream_pos = &buffer[0];
			stream_pos = strstr( stream_pos, "DATA;" );
			if( stream_pos != NULL )
			{
				stream_pos += 5;
				while(isspace(*stream_pos))
				{
					++stream_pos;
				}
			}
			else
			{
				// try to find the first data line another way
				stream_pos = &buffer[0];
				while( *stream_pos != '\0' )
				{
					if( *stream_pos == '#' )
					{
						break;
					}
					++stream_pos;
				}
			}

			// split into data lines: #1234=IFCOBJECTNAME(...,...,(...,...),...);
			char* last_token = stream_pos;
			char* progress_anchor = stream_pos;
			bool escaped = false;
			while( *stream_pos != '\0' )
			{
				if( *stream_pos == '\'' )
				{
					++stream_pos;
					// beginning of string, continue to end
					while( *stream_pos != '\0' )
					{
						escaped = false;
						if( *stream_pos == '\\' )
						{
							if( *(stream_pos+1) == '\\' )
							{
								// we have a double backslash, so just continue
								++stream_pos;
								++stream_pos;
								continue;
							}
							escaped = true;
						}
						else if( *stream_pos == '\'' )
						{
							if( escaped )
							{
								++stream_pos;
								continue;
							}
							// end of string
							break;
						}
						++stream_pos;
					}
					++stream_pos;
					continue;
				}

				if( *stream_pos == ';' )
				{
					char* begin_line = last_token;
					if( *begin_line == '#' )
					{
						std::string single_step_line( begin_line, stream_pos-last_token );
						target_vec.push_back( single_step_line );
					}

					++stream_pos;
					while(isspace(*stream_pos))
					{
						++stream_pos;
					}
					last_token = stream_pos;

					if( target_vec.size() % 100 == 0 )
					{
						double progress_since_anchor = (double)(stream_pos-progress_anchor)/double(length);
						if( progress_since_anchor > 0.01 )
						{
							progress = 0.1*(double)(stream_pos-&buffer[0])/double(length);
							progressCallback( progress );
							progress_anchor = stream_pos;
						}
					}
					continue;
				}
				++stream_pos;
			}
		}

		void IfcStepReader::readStepLines( const std::vector<std::string>& step_lines, std::vector<shared_ptr<IfcAlignmentP6Entity> >& target_entity_vec )
		{
			std::set<std::string> unkown_entities;
			std::stringstream err_unknown_entity;

			double progress = 0.1;
			double last_progress = 0.1;
			int num_lines = (int)step_lines.size();

#ifdef IfcAlignment_OPENMP
			std::vector<shared_ptr<IfcAlignmentP6Entity> >* target_vec_ptr = &target_entity_vec;
			std::set<std::string>* unkown_entities_ptr = &unkown_entities;

			#pragma omp parallel firstprivate(num_lines) shared(target_vec_ptr,unkown_entities_ptr)
			{
				// time for reading a step line does not differ much, so schedule many per thread
				#pragma omp for schedule(dynamic,100)
				for( int i=0; i<num_lines; ++i )
				{
					const std::string& step_line = step_lines[i];

					// read lines: #1234=IFCOBJECTNAME(...,...,(...,...),...)
					try
					{
						shared_ptr<IfcAlignmentP6Entity> entity;
						readStepLine( step_line,  entity );

						if( !entity )
						{
							continue;
						}

						#pragma omp critical
						{
							target_vec_ptr->push_back( entity );
						}
					}
					catch(UnknownEntityException& e)
					{
						std::string unknown_keyword = e.m_keyword;
						std::string step_line = step_lines[i];
						applyBackwardCompatibility( unknown_keyword, step_line );
						try
						{
							shared_ptr<IfcAlignmentP6Entity> entity;
							readStepLine( step_line, entity );

							if( entity )
							{
								#pragma omp critical
								target_vec_ptr->push_back( entity );
							}
						}
						catch( UnknownEntityException& )
						{
							if( unkown_entities.find( unknown_keyword ) == unkown_entities.end() )
							{
								#pragma omp critical
								{
									unkown_entities.insert( unknown_keyword );
									err_unknown_entity << "unknown IFC entity: " << unknown_keyword << std::endl;
								}
							}
						}
					}

					if( i%10 == 0)
					{
						progress = 0.1 + 0.1*(double)i/num_lines;
						if( progress - last_progress > 0.01 )
						{
							if( omp_get_thread_num() == 0 )
							{
								progressCallback( progress );
								last_progress = progress;
							}
						}
					}
				}
			}

#else // IfcAlignment_OPENMP

			for( int i=0; i<num_lines; ++i )
			{
				const std::string& step_line = step_lines[i];

				// read lines: #1234=IFCOBJECTNAME(...,...,(...,...),...)
				try
				{
					shared_ptr<IfcAlignmentP6Entity> entity;
					readStepLine( step_line, entity );

					if( !entity )
					{
						continue;
					}

					target_entity_vec.push_back( entity );

				}
				catch( UnknownEntityException& e )
				{
					std::string unknown_keyword = e.m_keyword;
					std::string step_line = step_lines[i];
					applyBackwardCompatibility( unknown_keyword, step_line );
					try
					{
						shared_ptr<IfcAlignmentP6Entity> entity;
						readStepLine( step_line, entity );

						if( !entity )
						{
							continue;
						}
						target_entity_vec.push_back( entity );
					}
					catch( UnknownEntityException& )
					{
						if( unkown_entities.find( unknown_keyword ) == unkown_entities.end() )
						{
							unkown_entities.insert( unknown_keyword );
							err_unknown_entity << "unknown IFC entity: " << unknown_keyword << std::endl;
						}
					}
				}

				progress = 0.1 + 0.1*(double)i/num_lines;
				if( progress - last_progress > 0.01 )
				{
					progressCallback( progress );
					last_progress = progress;
				}
			}
#endif

			if( err_unknown_entity.tellp() > 0 )
			{
				throw UnknownEntityException( err_unknown_entity.str() );
			}
		}

		void IfcStepReader::readEntityArguments( const std::vector<shared_ptr<IfcAlignmentP6Entity> >& vec_entities, const std::map<int,shared_ptr<IfcAlignmentP6Entity> > map_entities )
		{
			// second pass, now read arguments
			// every object can be initialized independently in parallel
			int num_objects = (int)vec_entities.size();
			std::stringstream err;

			// set progress
			double progress = 0.2;
			progressCallback( progress );

#ifdef IfcAlignment_OPENMP
			double last_progress = 0.2;
			const std::map<int,shared_ptr<IfcAlignmentP6Entity> >* map_ptr = &map_entities;
			const std::vector<shared_ptr<IfcAlignmentP6Entity> >* vec_entities_ptr = &vec_entities;

			#pragma omp parallel firstprivate(num_objects) shared(map_ptr,vec_entities_ptr)
			{
				const std::map<int,shared_ptr<IfcAlignmentP6Entity> > &map_loc = *map_ptr;
				std::stringstream thread_err;

				#pragma omp for schedule(dynamic, 100)
				for( int i=0; i<num_objects; ++i )
				{
					shared_ptr<IfcAlignmentP6Entity> entity = vec_entities_ptr->at(i);
					std::string& argument_str = entity->m_arguments;
					std::vector<std::string> arguments;
					tokenizeEntityArguments( argument_str, arguments );

					if( m_ifc_version != IfcAlignmentModel::IFC4 )
					{
						if( m_ifc_version != IfcAlignmentModel::UNDEFINED && m_ifc_version != IfcAlignmentModel::UNKNOWN )
						{
							IfcAlignmentP6EntityEnum entity_enum = entity->m_entity_enum;
							applyBackwardCompatibility( m_ifc_version, entity_enum, arguments );
						}
					}

					try
					{
						entity->readStepData( arguments, map_loc );
					}
					catch( std::exception& e )
					{
						#pragma omp critical
						err << "#" << entity->getId() << "=" << typeid(*entity).name() << ": " << e.what();
					}
					catch( std::exception* e )
					{
						#pragma omp critical
						err << "#" << entity->getId() << "=" << typeid(*entity).name() << ": " << e->what();
					}
					catch(...)
					{
						#pragma omp critical
						err << "#" << entity->getId() << "=" << typeid(*entity).name() << " readStepData: error occurred" << std::endl;
					}

					if( i%10 == 0 )
					{
						progress = 0.3 + 0.7*(double)i/num_objects;
						if( progress - last_progress > 0.01 )
						{
							if( omp_get_thread_num() == 0 )
							{
								progressCallback( progress );
								last_progress = progress;
							}
						}
					}
				}
			}

#else // IfcAlignment_OPENMP

			std::vector<shared_ptr<IfcAlignmentP6Entity> >::const_iterator it_entity_vec = vec_entities.begin();
			int i=0;
			for( ; it_entity_vec!=vec_entities.end(); ++it_entity_vec )
			{
				shared_ptr<IfcAlignmentP6Entity> entity = (*it_entity_vec);
				std::string& argument_str = entity->m_arguments;
				std::vector<std::string> arguments;
				tokenizeEntityArguments( argument_str, arguments );

				if( m_ifc_version != IfcAlignmentModel::IFC4 )
				{
					if( m_ifc_version != IfcAlignmentModel::UNDEFINED && m_ifc_version != IfcAlignmentModel::UNKNOWN )
					{
						IfcAlignmentP6EntityEnum entity_enum = entity->m_entity_enum;
						applyBackwardCompatibility( m_ifc_version, entity_enum, arguments );
					}
				}

				try
				{
					entity->readStepData( arguments, map_entities );
				}
				catch( std::exception& e )
				{
					err << "#" << entity->getId() << "=" << typeid(*entity).name() << ": " << e.what();
				}
				catch( std::exception* e )
				{
					err << "#" << entity->getId() << "=" << typeid(*entity).name() << ": " << e->what();
				}
				if( i%100 == 0 )
				{
					progress = 0.2 + 0.7*(double)i/num_objects;
					progressCallback( progress );
				}
				++i;
			}
#endif // IfcAlignment_OPENMP

			if( err.tellp() > 0 )
			{
				throw IfcAlignmentP6Exception( err.str() );
			}
		}

		void IfcStepReader::readStreamData(	std::string& read_in, std::map<int,shared_ptr<IfcAlignmentP6Entity> >& target_map )
		{
			char* current_numeric_locale = setlocale(LC_NUMERIC, NULL);
			setlocale(LC_NUMERIC,"C");

			if( m_ifc_version == IfcAlignmentModel::UNDEFINED || m_ifc_version == IfcAlignmentModel::UNKNOWN )
			{

				std::string error_message;
				error_message.append( "Unsupported IFC version: " );
				error_message.append( m_file_schema );
				errorCallback( error_message );
				progressCallback(0.0);
				return;
			}

			std::string message( "Detected IFC version: " );
			message.append( m_file_schema );

			if( m_ifc_version < IfcAlignmentModel::IFC4 )
			{
				message.append( "\nTrying to apply backward compatibility" );
			}
			messageCallback( message );

			std::stringstream err;
			std::vector<std::string> step_lines;
			try
			{
				splitIntoStepLines( read_in, step_lines );
			}
			catch(std::exception& e)
			{
				err << e.what();
			}

			std::vector<shared_ptr<IfcAlignmentP6Entity> > vec_entities;
			try
			{
				readStepLines( step_lines, vec_entities );
			}
			catch( UnknownEntityException& e )
			{
				std::string unknown_keyword = e.m_keyword;
				err << "unknown entity: " << unknown_keyword.c_str() << std::endl;
			}
			catch( IfcAlignmentP6Exception& e )
			{
				err << e.what();
			}
			catch(std::exception& e)
			{
				err << e.what();
			}
			catch(...)
			{
				err << "readStepLines: error occurred" << std::endl;
			}

			// copy entities into map so that they can be found during entity attribute initialization
			std::vector<shared_ptr<IfcAlignmentP6Entity> >::const_iterator it_entity_vec = vec_entities.begin();
			for( ; it_entity_vec!=vec_entities.end(); ++it_entity_vec )
			{
				shared_ptr<IfcAlignmentP6Entity> entity = (*it_entity_vec);
				target_map.insert( std::make_pair(entity->getId(), entity ) );
			}

			try
			{
				readEntityArguments( vec_entities, target_map );
			}
			catch( IfcAlignmentP6Exception& e )
			{
				err << e.what();
			}
			catch(std::exception& e)
			{
				err << e.what();
			}
			catch(...)
			{
				err << "readStepLines: error occurred" << std::endl;
			}

			setlocale(LC_NUMERIC,current_numeric_locale);
			if( err.tellp() > 0 )
			{
				throw IfcAlignmentP6Exception( err.str() );
			}
		}

		void applyBackwardCompatibility( std::string& keyword, std::string& step_line )
		{
			// TODO: systematic backward compatibility, possibly generated from schema diff
			if( keyword.compare("IFC2DCOMPOSITECURVE") == 0 )
			{
				size_t pos_find = step_line.find("IFC2DCOMPOSITECURVE");
				step_line = step_line.erase(pos_find+3,2);
			}
		}

		void applyBackwardCompatibility( IfcAlignmentModel::IfcVersion version, IfcAlignmentP6EntityEnum type_enum, std::vector<std::string>& args )
		{
			// TODO: replace this workaround with a systematic backward compatibility, possibly generated from schema diff
			if( version < IfcAlignmentModel::IFC2X )
			{
				throw IfcAlignmentP6Exception( "Unsupported IFC version" );
			}
			if( version <= IfcAlignmentModel::IFC2X )
			{

			}

			if( version <= IfcAlignmentModel::IFC2X2 )
			{
				switch( type_enum )
				{
				case IFCCOLOURRGB:
					//#315= IFCCOLOURRGB($,0.65882353,0.6627451,0.61960784);
					if( args.size() == 3 )
					{
						args.insert( args.begin(), "$" );
					}
					break;

				case IFCPROPERTYSINGLEVALUE:
					while( args.size() < 4 )
					{
						args.push_back( "$" );
					}
					break;
				case IFCPROJECT:
					while( args.size() < 9 )
					{
						args.push_back( "$" );
					}
					break;
				}
			}

			if( version <= IfcAlignmentModel::IFC2X3 )
			{
				switch( type_enum )
				{
				// B
				case IFCBEAM:
					args.push_back( "$" );
					break;
				case IFCBUILDINGELEMENTPART:
					args.push_back( "$" );
					break;
				// C
				case IFCCLASSIFICATION:
					args.push_back( "$" );
					args.push_back( "$" );
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCCLASSIFICATIONREFERENCE:
					args.push_back( "$" );
					break;
				case IFCCOLUMN:
					args.push_back( "$" );
					break;
				case IFCCURTAINWALL:
					args.push_back( "$" );
					break;
				case IFCCURVESTYLE:
					if( args.size() == 4 )
					{
						args.insert( args.begin()+1, "$" );
					}
					break;
				//D
				case IFCDISCRETEACCESSORY:
					args.push_back( "$" );
					break;
				case IFCDISCRETEACCESSORYTYPE:
					args.push_back( "$" );
					break;
				case IFCDISTRIBUTIONPORT:
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCDOOR:
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCDOORLININGPROPERTIES:
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				// F
				case IFCFILLAREASTYLE:
					args.push_back( "$" );
					break;
				case IFCFURNITURETYPE:
					args.push_back( "$" );
					break;

				// I
				case IFCISHAPEPROFILEDEF:
					args.push_back( "$" );
					args.push_back( "$" );
					break;

				// L
				case IFCLIBRARYREFERENCE:
					args.push_back( "$" );
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCLSHAPEPROFILEDEF:
					if( args.size() == 11 )
					{
						args.pop_back();
						args.pop_back();
					}
					break;
				// M
				case IFCMATERIAL:
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCMATERIALLAYER:
					args.push_back( "$" );
					args.push_back( "$" );
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCMATERIALLAYERSET:
					args.push_back( "$" );
					break;
				case IFCMATERIALLAYERSETUSAGE:
					args.push_back( "$" );
					break;
				case IFCMEMBER:
					args.push_back( "$" );
					break;

				// O
				case IFCOPENINGELEMENT:
					args.push_back( "$" );
					break;

				// P
				case IFCPLATE:
					args.push_back( "$" );
					break;
				case IFCPROPERTYBOUNDEDVALUE:
					args.push_back( "$" );
					break;

				// Q
				case IFCQUANTITYAREA:
					args.push_back( "$" );
					break;
				case IFCQUANTITYCOUNT:
					args.push_back( "$" );
					break;
				case IFCQUANTITYLENGTH:
					args.push_back( "$" );
					break;
				case IFCQUANTITYVOLUME:
					args.push_back( "$" );
					break;
				case IFCQUANTITYWEIGHT:
					args.push_back( "$" );
					break;

				// R
				case IFCRAMPFLIGHT:
					args.push_back( "$" );
					break;

				// S
				case IFCSIMPLEPROPERTYTEMPLATE:
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCSTAIRFLIGHT:
					args.push_back( "$" );
					break;
				case IFCSTRUCTURALANALYSISMODEL:
					args.push_back( "$" );
					break;
				case IFCSTRUCTURALPOINTCONNECTION:
					args.push_back( "$" );
					break;
				case IFCSTRUCTURALCURVEMEMBER:
					args.push_back( "$" );
					break;
				case IFCSURFACESTYLE:
					if( args.size() == 3 )
					{
						args.insert( args.begin()+1, "$" );
					}
					break;
				case IFCSYSTEMFURNITUREELEMENTTYPE:
					args.push_back( "$" );
					break;

				// T
				case IFCTSHAPEPROFILEDEF:
					if( args.size() == 13 )
					{
						args.pop_back();
					}
					break;

				// U
				case IFCUSHAPEPROFILEDEF:
					if( args.size() == 11 )
					{
						args.pop_back();
					}
					break;
				// W
				case IFCWALL:
					args.push_back( "$" );
					break;
				case IFCWALLSTANDARDCASE:
					args.push_back( "$" );
					break;
				case IFCWINDOW:
					args.push_back( "$" );
					args.push_back( "$" );
					break;
				case IFCWINDOWLININGPROPERTIES:
					args.push_back( "$" );
					args.push_back( "$" );
					args.push_back( "$" );
					break;

				case IFCZONE:
					args.push_back( "$" );
					break;



				}
			}

			if( version <= IfcAlignmentModel::IFC4 )
			{
				switch( type_enum )
				{
				// I
				case IFCISHAPEPROFILEDEF:
					args.push_back( "$" );
					args.push_back( "$" );
					break;

				// M
				case IFCMATERIALPROFILESETUSAGE:
					if( args.size() == 2 )
						args.push_back( "$" );
					break;
				}
			}

			//IfcRelDecomposes -> IfcRelAggregates
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform