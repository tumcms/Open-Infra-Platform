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

#include <sstream>
#include <limits>
#include <map>
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "../model/shared_ptr.h"
#include "../model/Ifc2x3Exception.h"
#include "include/IfcCurrencyEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcCurrencyEnum 
		IfcCurrencyEnum::IfcCurrencyEnum() {}
		IfcCurrencyEnum::~IfcCurrencyEnum() {}
		void IfcCurrencyEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCCURRENCYENUM("; }
			if( m_enum == ENUM_AED )
			{
				stream << ".AED.";
			}
			else if( m_enum == ENUM_AES )
			{
				stream << ".AES.";
			}
			else if( m_enum == ENUM_ATS )
			{
				stream << ".ATS.";
			}
			else if( m_enum == ENUM_AUD )
			{
				stream << ".AUD.";
			}
			else if( m_enum == ENUM_BBD )
			{
				stream << ".BBD.";
			}
			else if( m_enum == ENUM_BEG )
			{
				stream << ".BEG.";
			}
			else if( m_enum == ENUM_BGL )
			{
				stream << ".BGL.";
			}
			else if( m_enum == ENUM_BHD )
			{
				stream << ".BHD.";
			}
			else if( m_enum == ENUM_BMD )
			{
				stream << ".BMD.";
			}
			else if( m_enum == ENUM_BND )
			{
				stream << ".BND.";
			}
			else if( m_enum == ENUM_BRL )
			{
				stream << ".BRL.";
			}
			else if( m_enum == ENUM_BSD )
			{
				stream << ".BSD.";
			}
			else if( m_enum == ENUM_BWP )
			{
				stream << ".BWP.";
			}
			else if( m_enum == ENUM_BZD )
			{
				stream << ".BZD.";
			}
			else if( m_enum == ENUM_CAD )
			{
				stream << ".CAD.";
			}
			else if( m_enum == ENUM_CBD )
			{
				stream << ".CBD.";
			}
			else if( m_enum == ENUM_CHF )
			{
				stream << ".CHF.";
			}
			else if( m_enum == ENUM_CLP )
			{
				stream << ".CLP.";
			}
			else if( m_enum == ENUM_CNY )
			{
				stream << ".CNY.";
			}
			else if( m_enum == ENUM_CYS )
			{
				stream << ".CYS.";
			}
			else if( m_enum == ENUM_CZK )
			{
				stream << ".CZK.";
			}
			else if( m_enum == ENUM_DDP )
			{
				stream << ".DDP.";
			}
			else if( m_enum == ENUM_DEM )
			{
				stream << ".DEM.";
			}
			else if( m_enum == ENUM_DKK )
			{
				stream << ".DKK.";
			}
			else if( m_enum == ENUM_EGL )
			{
				stream << ".EGL.";
			}
			else if( m_enum == ENUM_EST )
			{
				stream << ".EST.";
			}
			else if( m_enum == ENUM_EUR )
			{
				stream << ".EUR.";
			}
			else if( m_enum == ENUM_FAK )
			{
				stream << ".FAK.";
			}
			else if( m_enum == ENUM_FIM )
			{
				stream << ".FIM.";
			}
			else if( m_enum == ENUM_FJD )
			{
				stream << ".FJD.";
			}
			else if( m_enum == ENUM_FKP )
			{
				stream << ".FKP.";
			}
			else if( m_enum == ENUM_FRF )
			{
				stream << ".FRF.";
			}
			else if( m_enum == ENUM_GBP )
			{
				stream << ".GBP.";
			}
			else if( m_enum == ENUM_GIP )
			{
				stream << ".GIP.";
			}
			else if( m_enum == ENUM_GMD )
			{
				stream << ".GMD.";
			}
			else if( m_enum == ENUM_GRX )
			{
				stream << ".GRX.";
			}
			else if( m_enum == ENUM_HKD )
			{
				stream << ".HKD.";
			}
			else if( m_enum == ENUM_HUF )
			{
				stream << ".HUF.";
			}
			else if( m_enum == ENUM_ICK )
			{
				stream << ".ICK.";
			}
			else if( m_enum == ENUM_IDR )
			{
				stream << ".IDR.";
			}
			else if( m_enum == ENUM_ILS )
			{
				stream << ".ILS.";
			}
			else if( m_enum == ENUM_INR )
			{
				stream << ".INR.";
			}
			else if( m_enum == ENUM_IRP )
			{
				stream << ".IRP.";
			}
			else if( m_enum == ENUM_ITL )
			{
				stream << ".ITL.";
			}
			else if( m_enum == ENUM_JMD )
			{
				stream << ".JMD.";
			}
			else if( m_enum == ENUM_JOD )
			{
				stream << ".JOD.";
			}
			else if( m_enum == ENUM_JPY )
			{
				stream << ".JPY.";
			}
			else if( m_enum == ENUM_KES )
			{
				stream << ".KES.";
			}
			else if( m_enum == ENUM_KRW )
			{
				stream << ".KRW.";
			}
			else if( m_enum == ENUM_KWD )
			{
				stream << ".KWD.";
			}
			else if( m_enum == ENUM_KYD )
			{
				stream << ".KYD.";
			}
			else if( m_enum == ENUM_LKR )
			{
				stream << ".LKR.";
			}
			else if( m_enum == ENUM_LUF )
			{
				stream << ".LUF.";
			}
			else if( m_enum == ENUM_MTL )
			{
				stream << ".MTL.";
			}
			else if( m_enum == ENUM_MUR )
			{
				stream << ".MUR.";
			}
			else if( m_enum == ENUM_MXN )
			{
				stream << ".MXN.";
			}
			else if( m_enum == ENUM_MYR )
			{
				stream << ".MYR.";
			}
			else if( m_enum == ENUM_NLG )
			{
				stream << ".NLG.";
			}
			else if( m_enum == ENUM_NZD )
			{
				stream << ".NZD.";
			}
			else if( m_enum == ENUM_OMR )
			{
				stream << ".OMR.";
			}
			else if( m_enum == ENUM_PGK )
			{
				stream << ".PGK.";
			}
			else if( m_enum == ENUM_PHP )
			{
				stream << ".PHP.";
			}
			else if( m_enum == ENUM_PKR )
			{
				stream << ".PKR.";
			}
			else if( m_enum == ENUM_PLN )
			{
				stream << ".PLN.";
			}
			else if( m_enum == ENUM_PTN )
			{
				stream << ".PTN.";
			}
			else if( m_enum == ENUM_QAR )
			{
				stream << ".QAR.";
			}
			else if( m_enum == ENUM_RUR )
			{
				stream << ".RUR.";
			}
			else if( m_enum == ENUM_SAR )
			{
				stream << ".SAR.";
			}
			else if( m_enum == ENUM_SCR )
			{
				stream << ".SCR.";
			}
			else if( m_enum == ENUM_SEK )
			{
				stream << ".SEK.";
			}
			else if( m_enum == ENUM_SGD )
			{
				stream << ".SGD.";
			}
			else if( m_enum == ENUM_SKP )
			{
				stream << ".SKP.";
			}
			else if( m_enum == ENUM_THB )
			{
				stream << ".THB.";
			}
			else if( m_enum == ENUM_TRL )
			{
				stream << ".TRL.";
			}
			else if( m_enum == ENUM_TTD )
			{
				stream << ".TTD.";
			}
			else if( m_enum == ENUM_TWD )
			{
				stream << ".TWD.";
			}
			else if( m_enum == ENUM_USD )
			{
				stream << ".USD.";
			}
			else if( m_enum == ENUM_VEB )
			{
				stream << ".VEB.";
			}
			else if( m_enum == ENUM_VND )
			{
				stream << ".VND.";
			}
			else if( m_enum == ENUM_XEU )
			{
				stream << ".XEU.";
			}
			else if( m_enum == ENUM_ZAR )
			{
				stream << ".ZAR.";
			}
			else if( m_enum == ENUM_ZWD )
			{
				stream << ".ZWD.";
			}
			else if( m_enum == ENUM_NOK )
			{
				stream << ".NOK.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcCurrencyEnum> IfcCurrencyEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcCurrencyEnum>(); }
			shared_ptr<IfcCurrencyEnum> type_object( new IfcCurrencyEnum() );
			if( _stricmp( arg.c_str(), ".AED." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_AED;
			}
			else if( _stricmp( arg.c_str(), ".AES." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_AES;
			}
			else if( _stricmp( arg.c_str(), ".ATS." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_ATS;
			}
			else if( _stricmp( arg.c_str(), ".AUD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_AUD;
			}
			else if( _stricmp( arg.c_str(), ".BBD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BBD;
			}
			else if( _stricmp( arg.c_str(), ".BEG." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BEG;
			}
			else if( _stricmp( arg.c_str(), ".BGL." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BGL;
			}
			else if( _stricmp( arg.c_str(), ".BHD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BHD;
			}
			else if( _stricmp( arg.c_str(), ".BMD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BMD;
			}
			else if( _stricmp( arg.c_str(), ".BND." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BND;
			}
			else if( _stricmp( arg.c_str(), ".BRL." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BRL;
			}
			else if( _stricmp( arg.c_str(), ".BSD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BSD;
			}
			else if( _stricmp( arg.c_str(), ".BWP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BWP;
			}
			else if( _stricmp( arg.c_str(), ".BZD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_BZD;
			}
			else if( _stricmp( arg.c_str(), ".CAD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_CAD;
			}
			else if( _stricmp( arg.c_str(), ".CBD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_CBD;
			}
			else if( _stricmp( arg.c_str(), ".CHF." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_CHF;
			}
			else if( _stricmp( arg.c_str(), ".CLP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_CLP;
			}
			else if( _stricmp( arg.c_str(), ".CNY." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_CNY;
			}
			else if( _stricmp( arg.c_str(), ".CYS." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_CYS;
			}
			else if( _stricmp( arg.c_str(), ".CZK." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_CZK;
			}
			else if( _stricmp( arg.c_str(), ".DDP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_DDP;
			}
			else if( _stricmp( arg.c_str(), ".DEM." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_DEM;
			}
			else if( _stricmp( arg.c_str(), ".DKK." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_DKK;
			}
			else if( _stricmp( arg.c_str(), ".EGL." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_EGL;
			}
			else if( _stricmp( arg.c_str(), ".EST." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_EST;
			}
			else if( _stricmp( arg.c_str(), ".EUR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_EUR;
			}
			else if( _stricmp( arg.c_str(), ".FAK." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_FAK;
			}
			else if( _stricmp( arg.c_str(), ".FIM." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_FIM;
			}
			else if( _stricmp( arg.c_str(), ".FJD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_FJD;
			}
			else if( _stricmp( arg.c_str(), ".FKP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_FKP;
			}
			else if( _stricmp( arg.c_str(), ".FRF." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_FRF;
			}
			else if( _stricmp( arg.c_str(), ".GBP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_GBP;
			}
			else if( _stricmp( arg.c_str(), ".GIP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_GIP;
			}
			else if( _stricmp( arg.c_str(), ".GMD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_GMD;
			}
			else if( _stricmp( arg.c_str(), ".GRX." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_GRX;
			}
			else if( _stricmp( arg.c_str(), ".HKD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_HKD;
			}
			else if( _stricmp( arg.c_str(), ".HUF." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_HUF;
			}
			else if( _stricmp( arg.c_str(), ".ICK." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_ICK;
			}
			else if( _stricmp( arg.c_str(), ".IDR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_IDR;
			}
			else if( _stricmp( arg.c_str(), ".ILS." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_ILS;
			}
			else if( _stricmp( arg.c_str(), ".INR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_INR;
			}
			else if( _stricmp( arg.c_str(), ".IRP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_IRP;
			}
			else if( _stricmp( arg.c_str(), ".ITL." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_ITL;
			}
			else if( _stricmp( arg.c_str(), ".JMD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_JMD;
			}
			else if( _stricmp( arg.c_str(), ".JOD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_JOD;
			}
			else if( _stricmp( arg.c_str(), ".JPY." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_JPY;
			}
			else if( _stricmp( arg.c_str(), ".KES." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_KES;
			}
			else if( _stricmp( arg.c_str(), ".KRW." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_KRW;
			}
			else if( _stricmp( arg.c_str(), ".KWD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_KWD;
			}
			else if( _stricmp( arg.c_str(), ".KYD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_KYD;
			}
			else if( _stricmp( arg.c_str(), ".LKR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_LKR;
			}
			else if( _stricmp( arg.c_str(), ".LUF." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_LUF;
			}
			else if( _stricmp( arg.c_str(), ".MTL." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_MTL;
			}
			else if( _stricmp( arg.c_str(), ".MUR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_MUR;
			}
			else if( _stricmp( arg.c_str(), ".MXN." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_MXN;
			}
			else if( _stricmp( arg.c_str(), ".MYR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_MYR;
			}
			else if( _stricmp( arg.c_str(), ".NLG." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_NLG;
			}
			else if( _stricmp( arg.c_str(), ".NZD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_NZD;
			}
			else if( _stricmp( arg.c_str(), ".OMR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_OMR;
			}
			else if( _stricmp( arg.c_str(), ".PGK." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_PGK;
			}
			else if( _stricmp( arg.c_str(), ".PHP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_PHP;
			}
			else if( _stricmp( arg.c_str(), ".PKR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_PKR;
			}
			else if( _stricmp( arg.c_str(), ".PLN." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_PLN;
			}
			else if( _stricmp( arg.c_str(), ".PTN." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_PTN;
			}
			else if( _stricmp( arg.c_str(), ".QAR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_QAR;
			}
			else if( _stricmp( arg.c_str(), ".RUR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_RUR;
			}
			else if( _stricmp( arg.c_str(), ".SAR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_SAR;
			}
			else if( _stricmp( arg.c_str(), ".SCR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_SCR;
			}
			else if( _stricmp( arg.c_str(), ".SEK." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_SEK;
			}
			else if( _stricmp( arg.c_str(), ".SGD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_SGD;
			}
			else if( _stricmp( arg.c_str(), ".SKP." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_SKP;
			}
			else if( _stricmp( arg.c_str(), ".THB." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_THB;
			}
			else if( _stricmp( arg.c_str(), ".TRL." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_TRL;
			}
			else if( _stricmp( arg.c_str(), ".TTD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_TTD;
			}
			else if( _stricmp( arg.c_str(), ".TWD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_TWD;
			}
			else if( _stricmp( arg.c_str(), ".USD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_USD;
			}
			else if( _stricmp( arg.c_str(), ".VEB." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_VEB;
			}
			else if( _stricmp( arg.c_str(), ".VND." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_VND;
			}
			else if( _stricmp( arg.c_str(), ".XEU." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_XEU;
			}
			else if( _stricmp( arg.c_str(), ".ZAR." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_ZAR;
			}
			else if( _stricmp( arg.c_str(), ".ZWD." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_ZWD;
			}
			else if( _stricmp( arg.c_str(), ".NOK." ) == 0 )
			{
				type_object->m_enum = IfcCurrencyEnum::ENUM_NOK;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
