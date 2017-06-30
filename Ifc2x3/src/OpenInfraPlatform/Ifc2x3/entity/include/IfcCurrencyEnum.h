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
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "../../model/shared_ptr.h"
#include "../../model/Ifc2x3Object.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcCurrencyEnum = ENUMERATION OF	(AED	,AES	,ATS	,AUD	,BBD	,BEG	,BGL	,BHD	,BMD	,BND	,BRL	,BSD	,BWP	,BZD	,CAD	,CBD	,CHF	,CLP	,CNY	,CYS	,CZK	,DDP	,DEM	,DKK	,EGL	,EST	,EUR	,FAK	,FIM	,FJD	,FKP	,FRF	,GBP	,GIP	,GMD	,GRX	,HKD	,HUF	,ICK	,IDR	,ILS	,INR	,IRP	,ITL	,JMD	,JOD	,JPY	,KES	,KRW	,KWD	,KYD	,LKR	,LUF	,MTL	,MUR	,MXN	,MYR	,NLG	,NZD	,OMR	,PGK	,PHP	,PKR	,PLN	,PTN	,QAR	,RUR	,SAR	,SCR	,SEK	,SGD	,SKP	,THB	,TRL	,TTD	,TWD	,USD	,VEB	,VND	,XEU	,ZAR	,ZWD	,NOK);
		class IfcCurrencyEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcCurrencyEnumEnum
			{
				ENUM_AED,
				ENUM_AES,
				ENUM_ATS,
				ENUM_AUD,
				ENUM_BBD,
				ENUM_BEG,
				ENUM_BGL,
				ENUM_BHD,
				ENUM_BMD,
				ENUM_BND,
				ENUM_BRL,
				ENUM_BSD,
				ENUM_BWP,
				ENUM_BZD,
				ENUM_CAD,
				ENUM_CBD,
				ENUM_CHF,
				ENUM_CLP,
				ENUM_CNY,
				ENUM_CYS,
				ENUM_CZK,
				ENUM_DDP,
				ENUM_DEM,
				ENUM_DKK,
				ENUM_EGL,
				ENUM_EST,
				ENUM_EUR,
				ENUM_FAK,
				ENUM_FIM,
				ENUM_FJD,
				ENUM_FKP,
				ENUM_FRF,
				ENUM_GBP,
				ENUM_GIP,
				ENUM_GMD,
				ENUM_GRX,
				ENUM_HKD,
				ENUM_HUF,
				ENUM_ICK,
				ENUM_IDR,
				ENUM_ILS,
				ENUM_INR,
				ENUM_IRP,
				ENUM_ITL,
				ENUM_JMD,
				ENUM_JOD,
				ENUM_JPY,
				ENUM_KES,
				ENUM_KRW,
				ENUM_KWD,
				ENUM_KYD,
				ENUM_LKR,
				ENUM_LUF,
				ENUM_MTL,
				ENUM_MUR,
				ENUM_MXN,
				ENUM_MYR,
				ENUM_NLG,
				ENUM_NZD,
				ENUM_OMR,
				ENUM_PGK,
				ENUM_PHP,
				ENUM_PKR,
				ENUM_PLN,
				ENUM_PTN,
				ENUM_QAR,
				ENUM_RUR,
				ENUM_SAR,
				ENUM_SCR,
				ENUM_SEK,
				ENUM_SGD,
				ENUM_SKP,
				ENUM_THB,
				ENUM_TRL,
				ENUM_TTD,
				ENUM_TWD,
				ENUM_USD,
				ENUM_VEB,
				ENUM_VND,
				ENUM_XEU,
				ENUM_ZAR,
				ENUM_ZWD,
				ENUM_NOK
			};

			IfcCurrencyEnum();
			IfcCurrencyEnum( IfcCurrencyEnumEnum e ) { m_enum = e; }
			~IfcCurrencyEnum();
			virtual const char* classname() const { return "IfcCurrencyEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcCurrencyEnum> readStepData( std::string& arg );
			IfcCurrencyEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

