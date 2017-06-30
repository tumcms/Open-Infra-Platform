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

#pragma once

#include <algorithm>
#include <locale>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include "../model/shared_ptr.h"
#include "../model/Exception.h"
#include "../model/Object.h"

#ifndef WIN32
#include <cstdio>
#include <cstring>
#endif

#pragma warning(disable : 4996)

namespace OpenInfraPlatform
{
    namespace IfcAlignment1x1
    {
        void readBoolList( const std::string& str, std::vector<bool>& vec );
        void readIntList( const std::string& str, std::vector<int>& vec );
        void readIntList2D( const std::string& str, std::vector<std::vector<int> >& vec );
        void readIntList3D( const std::string& str, std::vector<std::vector<std::vector<int> > >& vec );
        void readDoubleList( const std::string& str, std::vector<double>& vec );
        void readDoubleList2D( const std::string& str, std::vector<std::vector<double> >& vec );
        void readDoubleList3D( const std::string& str, std::vector<std::vector<std::vector<double> > >& vec );
        void readConstCharList( const std::string& str, std::vector<const char*>& vec );
        void readStringList( const std::string& str, std::vector<std::string>& vec );

        void checkOpeningClosingParenthesis( const char* ch_check );
        void tokenizeEntityArguments( std::string& argument_str, std::vector<std::string>& entity_arguments );
        void tokenizeInlineArgument( std::string input, std::string& keyword, std::string& inner_argument );
        void findLeadingTrailingParanthesis( char* ch, char*& pos_opening, char*& pos_closing );
        void tokenizeList( std::string& list_str, std::vector<std::string>& list_items );
        void tokenizeEntityList( std::string& list_str, std::vector<int>& list_items );

        void readIntValue( std::string& str, int& value );
        void readRealValue( std::string& str, double& value );

        template<class T>
        void readTypeOfIntList( std::string& str, std::vector<shared_ptr<T> >& vec )
        {
            //(38,12,4)
            char* ch = (char*)str.c_str();

            // ignore leading space or opening parenthesis
            while( *ch != '\0' )
            {
                if( *ch == '(' )
                {
                    checkOpeningClosingParenthesis( ch );
                    ++ch;
                    break;
                }
                else if( isspace( *ch ) )
                {
                    ++ch;
                }
                else
                {
                    break;
                }
            }

            while( *ch != '\0' )
            {
                vec.push_back( shared_ptr<T>(new T( atoi( ch ) ) ) );
                ch = strchr( ch, ',' );
                if( ch == NULL )
                {
                    break;
                }
                ++ch;
            }
        }

        template<class T>
        void readTypeOfRealList( const char* str, std::vector<shared_ptr<T> >& vec )
        {
            //(.38,12.0,.04)
            char* ch = (char*)str;

            // ignore leading space or opening parenthesis
            while( *ch != '\0' )
            {
                if( *ch == '(' )
                {
                    checkOpeningClosingParenthesis( ch );
                    ++ch;
                    break;
                }
                else if( isspace( *ch ) )
                {
                    ++ch;
                }
                else
                {
                    break;
                }
            }

            while( *ch != '\0' )
            {
#ifdef _DEBUG
                if( strchr(ch, '$') != NULL )
                {
                    throw IfcAlignment1x1Exception("unexpected $");
                }
#endif
                vec.push_back( shared_ptr<T>(new T( atof( ch ) ) ) );
                ch = strchr( ch, ',' );
                if( ch == NULL )
                {
                    break;
                }
                ++ch;
            }
        }

        template<class T>
        void readTypeOfRealList( std::string& str, std::vector<shared_ptr<T> >& vec )
        {
            //(.38,12.0,.04)
            char* ch = (char*)str.c_str();
            readTypeOfRealList( ch, vec );
        }

		
		template<class T>
        void readTypeOfIntList2D( std::string& str, std::vector<std::vector<shared_ptr<T> > >& vec )
        {
			if(str == "$")
				return;
			
            //((.38,12.0,.04),(.38,1.0,346.0),(1.8,1.0,.04))
            char* ch = (char*)str.c_str();

            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }

            if( ch[0] != '(' )
            {
                throw IfcAlignment1x1Exception( "readTypeOfRealList2D: string does not start with (" );
            }
            unsigned int i=0;
            unsigned int last_token = 1;
            int num_par_open = 0;
            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    if( num_par_open == 1 )
                    {
                        vec.resize(vec.size()+1);
                        std::string s = str.substr( last_token, i-last_token );
                        readTypeOfIntList( s, vec.back() );
                        last_token = i+1;
                    }
                }
                else if( ch[i] == '(' )
                {
                    ++num_par_open;
                }
                else if( ch[i] == ')' )
                {
                    --num_par_open;
                    if( num_par_open == 0 )
                    {
                        // closing paranthesis found
                        vec.resize(vec.size()+1);
                        std::string s = str.substr( last_token, i-last_token );
                        readTypeOfIntList( s, vec.back() );
                        return;
                    }
                }
                ++i;
            }

            // no closing paranthesis found
            std::stringstream err;
            err << "readTypeOfRealList2D: no closing paranthesis found: " << str << std::endl;
            throw IfcAlignment1x1Exception( err.str() );
        }

        template<class T>
        void readTypeOfRealList2D( std::string& str, std::vector<std::vector<shared_ptr<T> > >& vec )
        {
			if(str == "$")
				return;
			
            //((.38,12.0,.04),(.38,1.0,346.0),(1.8,1.0,.04))
            char* ch = (char*)str.c_str();

            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }

            if( ch[0] != '(' )
            {
                throw IfcAlignment1x1Exception( "readTypeOfRealList2D: string does not start with (" );
            }
            unsigned int i=0;
            unsigned int last_token = 1;
            int num_par_open = 0;
            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    if( num_par_open == 1 )
                    {
                        vec.resize(vec.size()+1);
                        std::string s = str.substr( last_token, i-last_token );
                        readTypeOfRealList( s, vec.back() );
                        last_token = i+1;
                    }
                }
                else if( ch[i] == '(' )
                {
                    ++num_par_open;
                }
                else if( ch[i] == ')' )
                {
                    --num_par_open;
                    if( num_par_open == 0 )
                    {
                        // closing paranthesis found
                        vec.resize(vec.size()+1);
                        std::string s = str.substr( last_token, i-last_token );
                        readTypeOfRealList( s, vec.back() );
                        return;
                    }
                }
                ++i;
            }

            // no closing paranthesis found
            std::stringstream err;
            err << "readTypeOfRealList2D: no closing paranthesis found: " << str << std::endl;
            throw IfcAlignment1x1Exception( err.str() );
        }

        template<class T>
        void readEntityReference(  std::string& str, shared_ptr<T>& smart, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map_entities )
        {
            if( str.length() == 0)
            {
                std::stringstream err;
                err << "readEntityReference: empty argument. should be $" << std::endl;
                return;
            }
            if( str.at(0) == '#' )
            {
                int entity_id = atoi( str.erase( 0, 1 ).c_str() );
                std::map<int,shared_ptr<IfcAlignment1x1Entity> >::const_iterator it_entity = map_entities.find( entity_id );
                if( it_entity != map_entities.end() )
                {
                    shared_ptr<IfcAlignment1x1Entity> found_obj = it_entity->second;
                    smart = dynamic_pointer_cast<T>(found_obj);
                }
                else
                {
                    std::stringstream err;
                    err << "readEntityReference: object with id " << entity_id << " not found" << std::endl;
                    throw IfcAlignment1x1Exception( err.str() );
                }
            }
            else if( str.compare("$")==0 )
            {

            }
            else if( str.compare("*")==0 )
            {

            }
            else
            {
                throw IfcAlignment1x1Exception( "readEntityReference: unexpected argument\n" );
            }
        }

        template<class T>
        void readTypeList( std::string arg_complete, std::vector<shared_ptr<T> >& vec )
        {
            //(IfcLabel('label'),'',IfcLengthMeasure(2.0),#299)
            char* pos_opening = NULL;
            char* pos_closing = NULL;
            char* ch = (char*)arg_complete.c_str();
            findLeadingTrailingParanthesis( ch, pos_opening, pos_closing );
            if( pos_opening == NULL || pos_closing == NULL )
            {
                if( arg_complete.compare("$") == 0 )
                {
                    // empty list
                    return;
                }
                std::stringstream err;
                err << "readTypeList: num_opening != num_closing : " << arg_complete.c_str() << std::endl;
                throw IfcAlignment1x1Exception( err.str() );
            }
            std::string arg( pos_opening+1, pos_closing-pos_opening-1 );
            std::vector<std::string> list_items;
            tokenizeList( arg, list_items );

            for( unsigned int i=0; i<list_items.size(); ++i )
            {
                std::string& item = list_items[i];
                vec.push_back( T::readStepData( item ) );
            }
        }

        template<class T>
        void readSelectList( std::string& arg_complete, std::vector<shared_ptr<T> >& vec, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map_entities )
        {
            //(#287,#291,#295,#299)
            char* pos_opening = NULL;
            char* pos_closing = NULL;
            char* ch = (char*)arg_complete.c_str();
            findLeadingTrailingParanthesis( ch, pos_opening, pos_closing );
            if( pos_opening == NULL || pos_closing == NULL )
            {
                if( arg_complete.compare("$") == 0 )
                {
                    // empty list
                    return;
                }
                std::stringstream err;
                err << "readTypeList: num_opening != num_closing : " << arg_complete.c_str() << std::endl;
                throw IfcAlignment1x1Exception( err.str() );
            }
            std::string arg( pos_opening+1, pos_closing-pos_opening-1 );
            std::vector<std::string> list_items;
            tokenizeList( arg, list_items );

            std::map<int,shared_ptr<IfcAlignment1x1Entity> >::const_iterator it_entity;
            for( unsigned int i=0; i<list_items.size(); ++i )
            {
                std::string& item = list_items[i];
                char* ch = (char*)item.c_str();
                if( *ch == '#' )
                {
                    ++ch;
                    const int id = atoi( ch );
                    it_entity = map_entities.find( id );
                    if( it_entity != map_entities.end() )
                    {
                        shared_ptr<IfcAlignment1x1Entity> found_obj = it_entity->second;
                        vec.push_back( dynamic_pointer_cast<T>(found_obj) );
                    }
                }
                else
                {
                    // could be type like IFCPARAMETERVALUE(90)
                    vec.push_back( T::readStepData( item, map_entities ) );
                }
            }
            return;
        }

        template<class T>
        void readEntityReferenceList( const char* arg_complete, std::vector<shared_ptr<T> >& vec, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map_entities )
        {
            //(#287,#291,#295,#299)
            char* pos_opening = NULL;
            char* pos_closing = NULL;
            char* ch = (char*)arg_complete;
            findLeadingTrailingParanthesis( ch, pos_opening, pos_closing );
            if( pos_opening == NULL || pos_closing == NULL )
            {
                if( arg_complete != NULL )
                {
                    if( *arg_complete == '$' )
                    {
                        // empty list
                        return;
                    }
                }
                std::stringstream err;
                err << "readEntityReferenceList: num_opening != num_closing : " << arg_complete << std::endl;
                throw IfcAlignment1x1Exception( err.str() );
            }
            std::string arg( pos_opening+1, pos_closing-pos_opening-1 );
            std::vector<int> list_items;
            tokenizeEntityList( arg, list_items );
            std::map<int,shared_ptr<IfcAlignment1x1Entity> >::const_iterator it_entity;
            for( unsigned int i=0; i<list_items.size(); ++i )
            {
                const int id = list_items[i];
                it_entity = map_entities.find( id );
                if( it_entity != map_entities.end() )
                {
                    shared_ptr<IfcAlignment1x1Entity> found_obj = it_entity->second;
                    vec.push_back( dynamic_pointer_cast<T>(found_obj) );
                }
            }
        }

        template<class T>
        void readEntityReferenceList( const std::string& str, std::vector<shared_ptr<T> >& vec, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map_entities )
        {
            //(#287,#291,#295,#299)
            char* ch = (char*)str.c_str();
            readEntityReferenceList( ch, vec, map_entities );
        }

        template<class T>
        void readEntityReferenceList2D( std::string& str, std::vector<std::vector<shared_ptr<T> > >& vec, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map_entities )
        {
            //((#287,#291,#295,#299),(#287,#291,#295,#299))
            char* ch = (char*)str.c_str();

            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }

            char* last_token = ch;
            int num_par_open = 0;
            while( *ch != '\0' )
            {
                if( *ch == ')' )
                {
                    --num_par_open;
                    if( num_par_open == 0 )
                    {
                        // last list
                        vec.resize(vec.size()+1);
                        readEntityReferenceList( std::string( last_token, ch-last_token ), vec.back(), map_entities );
                        return;
                    }
                }
                else if( *ch == '(' )
                {
                    ++num_par_open;
                    if( num_par_open == 1 )
                    {
                        last_token = ch+1;
                    }
                }
                else if( *ch == ',' )
                {
                    if( num_par_open == 1 )
                    {
                        vec.resize(vec.size()+1);
                        readEntityReferenceList( std::string( last_token, ch-last_token ), vec.back(), map_entities );
                        last_token = ch+1;
                    }
                }
                ++ch;
            }
            // no closing paranthesis found
            std::stringstream err;
            err << "readEntityReferenceList2D: no closing paranthesis found: " << str << std::endl;
            throw IfcAlignment1x1Exception( err.str() );
        }

        template<class T>
        void readEntityReferenceList3D( std::string& str, std::vector<std::vector<std::vector<shared_ptr<T> > > >& vec, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map_entities )
        {
            //(((#287,#291,#295,#299),(#287,#291,#295,#299)),((#287,#291,#295,#299),(#287,#291,#295,#299)))
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize < 8 )
            {
                return;
            }

            int num_par_open = 0;
            char* ch = (char*)str.c_str();
            char* last_token = ch;

            while( *ch != '\0' )
            {
                if( *ch == ')' )
                {
                    --num_par_open;
                    if( num_par_open == 0 )
                    {
                        // last list
                        vec.resize(vec.size()+1);
                        std::string inner_argument( last_token, ch-last_token );
                        readEntityReferenceList2D( inner_argument, vec.back(), map_entities );
                        return;
                    }
                }
                else if( *ch == '(' )
                {
                    ++num_par_open;
                    if( num_par_open == 1 )
                    {
                        last_token = ch+1;
                    }
                }
                else if( *ch == ',' )
                {
                    if( num_par_open == 1 )
                    {
                        vec.resize(vec.size()+1);
                        std::string inner_argument( last_token, ch-last_token );
                        readEntityReferenceList2D( inner_argument, vec.back(), map_entities );
                        last_token = ch+1;
                    }
                }
                ++ch;
            }
            // no closing paranthesis found
            std::stringstream err;
            err << "readEntityReferenceList3D: no closing paranthesis found: " << str << std::endl;
            throw IfcAlignment1x1Exception( err.str() );
        }
    } // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
