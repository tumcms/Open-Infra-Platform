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

#ifdef WIN32
#include <math.h>
#else
#include <cmath>
#endif
#include <limits>

#include "model/Ifc4Exception.h"
#include "ReaderUtil.h"

namespace OpenInfraPlatform
{
    namespace Ifc4
    {
        int hex2int(char c)
        {
            int first = c / 16 - 3;
            int second = c % 16;
            int result = first*10 + second;
            if(result > 9) result--;
            return result;
        }

        std::string decodeStepString( std::string arg_str )
        {
            char* stream_pos = (char*)arg_str.c_str();
            std::string result_str;

            while( *stream_pos != '\0' )
            {
                if( *stream_pos == '\\' )
                {
                    ++stream_pos;
                    if( *stream_pos == 'S' )
                    {
                        ++stream_pos;
                        if( *stream_pos == '\\' )
                        {
                            ++stream_pos;
                            char char_from_8859 = *(stream_pos)+128;
                            result_str.push_back( char_from_8859 );
                            ++stream_pos;
                            continue;
                        }
                    }
                    else if( *stream_pos == 'X' )
                    {
                        ++stream_pos;
                        if( *stream_pos == '\\' )
                        {
                            ++stream_pos;
                            char c = *stream_pos;
                            int result_ascii = hex2int( c );
                            char char_ascii = result_ascii;
                            result_str.push_back( char_ascii );
                            continue;
                        }
                        else if( *stream_pos == '0' )
                        {
                            ++stream_pos;
                            if( *stream_pos == '\\' )
                            {
                            }
                        }
                        else if( *stream_pos == '2' )
                        {
                            ++stream_pos;
                            if( *stream_pos == '\\' )
                            {
                                // the following sequence of multiples of four hexadecimal characters shall be interpreted as encoding the
                                // two-octet representation of characters from the BMP in ISO 10646
                            }
                        }
                    }
                }
                result_str.push_back( *stream_pos );
                ++stream_pos;

            }
            return result_str;
        }

        void checkOpeningClosingParenthesis( const char* ch_check )
        {
            int num_opening=0;
            int num_closing=0;
            while( *ch_check != '\0' )
            {
                if( *ch_check == '(' )
                {
                    ++num_opening;
                }
                else if( *ch_check == ')' )
                {
                    ++num_closing;
                }
                ++ch_check;
            }
            if( num_opening != num_closing )
            {
                std::stringstream err;
                err << "checkOpeningClosingParenthesis: num_opening != num_closing : " << ch_check << std::endl;
                throw Ifc4Exception( err.str().c_str(), __func__ );
            }
        }

        void findLeadingTrailingParanthesis( char* ch, char*& pos_opening, char*& pos_closing )
        {
            int num_opening = 0;
            while( *ch != '\0' )
            {
                if( *ch == '\'' )
                {
                    ++ch;
                    // beginning of string, continue to end
                    while( *ch != '\0' )
                    {
                        if( *ch == '\'' )
                        {
                            break;
                        }
                        ++ch;
                    }
                    ++ch;
                    continue;
                }

                if( *ch == '(' )
                {
                    if( num_opening == 0 )
                    {
                        pos_opening = ch;
                    }
                    ++num_opening;
                }
                else if( *ch == ')' )
                {
                    --num_opening;
                    if( num_opening == 0 )
                    {
                        pos_closing = ch;
                    }
                }
                ++ch;
            }
        }

        void tokenizeList( std::string& list_str, std::vector<std::string>& list_items )
        {
            if( list_str.size() == 0 )
            {
                return;
            }
            char* stream_pos = (char*)list_str.c_str();
            char* last_token = stream_pos;
            while( *stream_pos != '\0' )
            {
                if( *stream_pos == '\'' )
                {
                    ++stream_pos;
                    // beginning of string, continue to end
                    while( *stream_pos != '\0' )
                    {
                        if( *stream_pos == '\'' )
                        {
                            break;
                        }
                        ++stream_pos;
                    }
                    ++stream_pos;
                    continue;
                }

                if( *stream_pos == ',' )
                {
                    std::string item( last_token, stream_pos-last_token );
                    if( item.at(0) == '\'' && item.at(item.size()-1) == '\'' )
                    {
                        item.erase(item.size()-1);
                        item.erase(0);
                    }
                    list_items.push_back( item );

                    ++stream_pos;
                    while( isspace(*stream_pos) )
                    {
                        ++stream_pos;
                    }
                    last_token = stream_pos;
                    if( *stream_pos == '\0' )
                    {
                        throw Ifc4Exception( "tokenizeList: *stream_pos == '\0'", __func__ );
                    }
                    continue;
                }
                ++stream_pos;
            }
            // pick up last element
            if( last_token != NULL )
            {
                if( last_token != stream_pos )
                {
                    std::string item( last_token, stream_pos-last_token );
                    if( item.at(0) == '\'' && item.at(item.size()-1) == '\'' )
                    {
                        item.erase(item.size()-1);
                        item.erase(0);
                    }
                    list_items.push_back( item );
                }
            }
        }

        void tokenizeEntityList( std::string& list_str, std::vector<int>& list_items )
        {
            if( list_str.size() == 0 )
            {
                return;
            }
            char* stream_pos = (char*)list_str.c_str();
            while( *stream_pos != '\0' )
            {
                // skip whitespace
                while( isspace( *stream_pos ) )
                {
                    ++stream_pos;
                }

                if( *stream_pos == '#' )
                {
                    ++stream_pos;
                    // beginning of id
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
                    list_items.push_back( id );
                }
                else if( *stream_pos == '$' )
                {
                    // empty
                }
                else
                {
                    std::stringstream err;
                    err << "tokenizeEntityList: unexpected argument: " << list_str.c_str() << std::endl;
                    throw Ifc4Exception( err.str().c_str(), __func__ );
                }

                while( isspace( *stream_pos ) )
                {
                    ++stream_pos;
                }
                if( *stream_pos == ',' )
                {
                    ++stream_pos;
                    //last_token = stream_pos;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }

        void readIntValue( std::string& str, int& int_value )
        {
            if( str.compare("$") == 0 )
            {
                int_value = std::numeric_limits<int>::quiet_NaN();
            }
            else
            {
                int_value = atoi( str.c_str() );
            }
        }
        void readRealValue( std::string& str, double& real_value )
        {
            if( str.compare("$") == 0 )
            {
                real_value = std::numeric_limits<double>::quiet_NaN();
            }
            else
            {
                real_value = atof( str.c_str() );
            }
        }

        void readIntList( const std::string& str, std::vector<int>& vec )
        {
            const char* ch = str.c_str();
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }
            unsigned int i=0;
            unsigned int last_token = 0;
            while( i<argsize )
            {
                if( ch[i] == '(' )
                {
                    ++i;
                    last_token = i;
                    break;
                }
                ++i;
            }

            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    vec.push_back( atoi( str.substr( last_token, i-last_token ).c_str() ) );
                    last_token = i+1;
                }
                else if( ch[i] == ')' )
                {
                    vec.push_back( atoi( str.substr( last_token, i-last_token ).c_str() ) );
                    return;
                }
                ++i;
            }
        }
        void readIntList2D( const std::string& str, std::vector<std::vector<int> >& vec )
        {
            // ((1,2,4),(3,23,039),(938,3,-3,6))
            const char* ch = str.c_str();
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }
            unsigned int i=0;
            unsigned int num_par_open=0;
            int last_token = 1; // mk: CHANGED if we assume that string begins with ((, the last token should start with 1
            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    if( num_par_open == 1 )
                    {
                        std::vector<int> inner_vec;
                        readIntList( str.substr( last_token, i-last_token ), inner_vec );
						vec.push_back(inner_vec); // mk: CHANGED as inner_vec should be pushed after it is filled!
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
                        std::vector<int> inner_vec;
                        readIntList( str.substr( last_token, i-last_token ), inner_vec );
						vec.push_back(inner_vec); // mk: CHANGED as inner_vec should be pushed after it is filled!
                        return;
                    }
                }
                ++i;
            }
        }

        void readDoubleList( const std::string& str, std::vector<double>& vec )
        {
            const char* ch = str.c_str();
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }
            unsigned int i=0;
            unsigned int last_token = 0;
            while( i<argsize )
            {
                if( ch[i] == '(' )
                {
                    ++i;
                    last_token = i;
                    break;
                }
                ++i;
            }

            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    vec.push_back( atof( str.substr( last_token, i-last_token ).c_str() ) );
                    last_token = i+1;
                }
                else if( ch[i] == ')' )
                {
                    vec.push_back( atof( str.substr( last_token, i-last_token ).c_str() ) );
                    return;
                }
                ++i;
            }
        }

        void readDoubleList2D( const std::string& str, std::vector<std::vector<double> >& vec )
        {
            // ((1.6,2.0,4.9382),(3.78,23.34,039.938367),(938.034,3.0,-3.45,6.9182))
            const char* ch = str.c_str();
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }
            unsigned int i=0;
            unsigned int num_par_open=0;
            unsigned int last_token = 0;
            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    if( num_par_open == 1 )
                    {
                        std::vector<double> inner_vec;
                        readDoubleList( str.substr( last_token, i-last_token ), vec.back() );
						vec.push_back(inner_vec); // mk: CHANGED as inner_vec should be pushed after it is filled!
                        last_token = i;
                    }
                }
                else if( ch[i] == '(' )
                {
                    ++num_par_open;
                    last_token = i;
                }
                else if( ch[i] == ')' )
                {
                    --num_par_open;
                    if( num_par_open == 0 )
                    {
                        std::vector<double> inner_vec;
                        readDoubleList( str.substr( last_token, i-last_token ), vec.back() );
						vec.push_back(inner_vec); // mk: CHANGED as inner_vec should be pushed after it is filled!
                        return;
                    }
                }
                ++i;
            }
        }

        void readDoubleList3D( const std::string& str, std::vector<std::vector<std::vector<double> > >& vec )
        {
            // ((1.6,2.0,4.9382),(3.78,23.34,039.938367),(938.034,3.0,-3.45,6.9182))
            const char* ch = str.c_str();
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }
            unsigned int i=0;
            unsigned int num_par_open=0;
            unsigned int last_token = 0;
            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    if( num_par_open == 1 )
                    {
                        std::vector<std::vector<double> > inner_vec;
                        readDoubleList2D( str.substr( last_token, i-last_token ), vec.back() );
						vec.push_back(inner_vec); // mk: CHANGED as inner_vec should be pushed after it is filled!
                        last_token = i;
                    }
                }
                else if( ch[i] == '(' )
                {
                    ++num_par_open;
                    last_token = i;
                }
                else if( ch[i] == ')' )
                {
                    --num_par_open;
                    if( num_par_open == 0 )
                    {
                        std::vector<std::vector<double> > inner_vec;
                        readDoubleList2D( str.substr( last_token, i-last_token ), vec.back() );
						vec.push_back(inner_vec); // mk: CHANGED as inner_vec should be pushed after it is filled!
                        return;
                    }
                }
                ++i;
            }
        }

        void readConstCharList( const std::string& str, std::vector<const char*>& vec )
        {
            const char* ch = str.c_str();
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }
            unsigned int i=0;
            unsigned int last_token = 0;
            while( i<argsize )
            {
                if( ch[i] == '(' )
                {
                    ++i;
                    last_token = i;
                    break;
                }
                ++i;
            }
            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    vec.push_back( decodeStepString( str.substr( last_token, i-last_token ) ).c_str() );
                    last_token = i+1;
                }
                else if( ch[i] == ')' )
                {
                    vec.push_back( decodeStepString( str.substr( last_token, i-last_token ) ).c_str() );
                    return;
                }
                ++i;
            }
        }
        void readStringList( const std::string& str, std::vector<std::string>& vec )
        {
            const char* ch = str.c_str();
            const unsigned int argsize = (unsigned int)str.size();
            if( argsize == 0 )
            {
                return;
            }
            unsigned int i=0;
            unsigned int last_token = 0;
            while( i<argsize )
            {
                if( ch[i] == '(' )
                {
                    ++i;
                    last_token = i;
                    break;
                }
                ++i;
            }
            while( i<argsize )
            {
                if( ch[i] == ',' )
                {
                    vec.push_back( decodeStepString( str.substr( last_token, i-last_token ) ) );
                    last_token = i+1;
                }
                else if( ch[i] == ')' )
                {
                    vec.push_back( decodeStepString( str.substr( last_token, i-last_token ) ) );
                    return;
                }
                ++i;
            }
        }


        void tokenizeEntityArguments( std::string& argument_str, std::vector<std::string>& entity_arguments )
        {
            char* stream_pos = (char*)argument_str.c_str();
            if( *stream_pos != '(' )
            {
                return;
            }

            ++stream_pos;
            int num_open_braces = 1;
            char* last_token = stream_pos;

            while( *stream_pos != '\0' )
            {
                if( *stream_pos == '\'' )
                {
                    // go to end of string
                    ++stream_pos;
                    char look_back = ' ';
                    char look_back2 = ' ';
                    while( *stream_pos != '\0' )
                    {
                        if( *stream_pos == '\'' )
                        {
                            if( look_back == '\\' )
                            {
                                if( look_back2 != '\\' )
                                {
                                    // tick is escaped
                                    look_back = *stream_pos;
                                    ++stream_pos;
                                    continue;
                                }
                            }
                            // else tick marks the end of argument
                            ++stream_pos;
                            break;
                        }
                        look_back2 = look_back;
                        look_back = *stream_pos;
                        ++stream_pos;
                    }
                    continue;
                }

                if( *stream_pos == '(' )
                {
                    ++num_open_braces;
                }
                else if( *stream_pos == ',' )
                {
                    if( num_open_braces == 1 )
                    {
                        if( *last_token == ',' )
                        {
                            ++last_token;
                        }

                        char* begin_arg = last_token;

                        // skip whitespace
                        while( isspace( *begin_arg ) )
                        {
                            ++begin_arg;
                        }
                        char* end_arg = stream_pos-1;
                        if( *begin_arg == '\'' && *end_arg == '\'' )
                        {
                            // TODO:
                            std::string arg_str( begin_arg+1, end_arg-begin_arg-1 );
                            arg_str = decodeStepString( arg_str );
                            entity_arguments.push_back( arg_str );
                        }
                        else
                        {
                            entity_arguments.push_back( std::string( begin_arg, end_arg-begin_arg+1 ) );
                        }
                        last_token = stream_pos;
                    }
                }
                else if( *stream_pos == ')' )
                {
                    --num_open_braces;
                    if( num_open_braces == 0 )
                    {
                        if( *last_token == ',' )
                        {
                            ++last_token;
                        }

                        char* begin_arg = last_token;

                        // skip whitespace
                        while( isspace( *begin_arg ) )
                        {
                            ++begin_arg;
                        }

                        int remaining_size = (int)(stream_pos - begin_arg);
                        if( remaining_size > 0 )
                        {
                            char* end_arg = stream_pos-1;
                            if( *begin_arg == '\'' && *end_arg == '\'' )
                            {
                                entity_arguments.push_back( std::string( begin_arg+1, end_arg-begin_arg-1 ) );
                            }
                            else
                            {
                                entity_arguments.push_back( std::string( begin_arg, end_arg-begin_arg+1 ) );
                            }
                        }
                        break;
                    }
                }
                ++stream_pos;
            }
        }

        void tokenizeInlineArgument( std::string arg, std::string& keyword, std::string& inline_arg )
        {
            if( arg.size() == 0 )
            {
                throw Ifc4Exception( "tokenizeInlineArgument: arg.size() == 0", __func__ );
            }
            if( arg.compare("$") == 0 )
            {
                return;
            }
            if( arg.compare("*") == 0 )
            {
                return;
            }
            if( arg.at(0) == '#' )
            {
                throw Ifc4Exception( "tokenizeInlineArgument: argument begins with #, so it is not inline", __func__ );
            }

            char* stream_pos = (char*)arg.c_str();
            while(isspace(*stream_pos))
            {
                ++stream_pos;
            }

            char* begin_keyword = stream_pos;
            while(isalnum(*stream_pos))
            {
                ++stream_pos;
            }

            // get type name
            std::string key( begin_keyword, stream_pos-begin_keyword );

            if( key.size() == 0 )
            {
                // single argument, for example .T.
                inline_arg = arg;
                return;
            }

            // proceed to '('
            if( *stream_pos == '(' )
            {
                ++stream_pos;
            }
            else
            {
                while( *stream_pos != '\0' )
                {
                    if( *stream_pos == '(' )
                    {
                        ++stream_pos;
                        break;
                    }
                    ++stream_pos;
                }
            }

            // proceed to ')'
            std::string inline_argument;
            char* inline_argument_begin = stream_pos;

            while( *stream_pos != '\0' )
            {
                if( *stream_pos == '\'' )
                {
                    ++stream_pos;
                    // inside string
                    char look_back = ' ';
                    while( *stream_pos != '\0' )
                    {
                        if( *stream_pos == '\'' )
                        {
                            if( look_back == '\\' )
                            {
                                // tick is escaped
                                look_back = *stream_pos;
                                ++stream_pos;
                                continue;
                            }
                            // else tick marks the end of argument
                            break;
                        }
                        look_back = *stream_pos;
                        ++stream_pos;
                    }
                }

                if( *stream_pos == ')' )
                {
                    // skip whitespace
                    while( isspace( *inline_argument_begin ) )
                    {
                        ++inline_argument_begin;
                    }
                    char* end_arg = stream_pos-1;
                    if( *inline_argument_begin == '\'' && *end_arg == '\'' )
                    {
                        inline_argument = std::string( inline_argument_begin+1, end_arg-inline_argument_begin-1 );
                    }
                    else
                    {
                        inline_argument = std::string( inline_argument_begin, end_arg-inline_argument_begin+1 );
                    }

                    break;
                }
                ++stream_pos;
            }

            std::transform(key.begin(), key.end(), key.begin(), toupper);
            keyword = key;
            inline_arg = inline_argument;
        }
    } // end namespace Ifc4
} // end namespace OpenInfraPlatform
