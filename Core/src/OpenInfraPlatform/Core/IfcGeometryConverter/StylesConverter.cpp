// Copied and modified code from "IfcPlusPlus".
// This code is available under the OSGPL license. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and/or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* OpenSceneGraph Public License for more details.
*/

// More details can be found in README.md file in the root directory.

//! deprecated

#include <cstring>


#include "StylesConverter.h"

//#ifdef IFC4_READER
//
//#include "BlueFramework/Ifc4/entity/include/IfcSpecularHighlightSelect.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSpecularExponent.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSpecularRoughness.h"
//#include "BlueFramework/Ifc4/entity/include/IfcColourOrFactor.h"
//#include "BlueFramework/Ifc4/entity/include/IfcColourRgb.h"
//#include "BlueFramework/Ifc4/entity/include/IfcNormalisedRatioMeasure.h"
//#include "BlueFramework/Ifc4/entity/include/IfcDraughtingPreDefinedColour.h"
//#include "BlueFramework/Ifc4/entity/include/IfcLabel.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSurfaceStyleElementSelect.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSurfaceStyle.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSurfaceStyleShading.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSurfaceStyleRendering.h"
//#include "BlueFramework/Ifc4/entity/include/IfcStyledItem.h"
//#include "BlueFramework/Ifc4/entity/include/IfcPresentationStyleAssignment.h"
//#include "BlueFramework/Ifc4/entity/include/IfcPresentationStyleSelect.h"
//#include "BlueFramework/Ifc4/entity/include/IfcPresentationStyle.h"
//#include "BlueFramework/Ifc4/entity/include/IfcCartesianPoint.h"
//#include "BlueFramework/Ifc4/entity/include/IfcProperty.h"
//#include "BlueFramework/Ifc4/entity/include/IfcComplexProperty.h"
//#include "BlueFramework/Ifc4/entity/include/IfcIdentifier.h"
//#include "BlueFramework/Ifc4/entity/include/IfcPropertySingleValue.h"
//#include "BlueFramework/Ifc4/entity/include/IfcInteger.h"
//#include "BlueFramework/Ifc4/entity/include/IfcCurveStyle.h"
//#include "BlueFramework/Ifc4/entity/include/IfcFillAreaStyle.h"
//#include "BlueFramework/Ifc4/entity/include/IfcTextStyle.h"
//#include "BlueFramework/Ifc4/entity/include/IfcNullStyle.h"
//#include "BlueFramework/Ifc4/entity/include/IfcExternallyDefinedSurfaceStyle.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSurfaceStyleLighting.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSurfaceStyleRefraction.h"
//#include "BlueFramework/Ifc4/entity/include/IfcSurfaceStyleWithTextures.h"
//
//using namespace BlueFramework::Ifc4;
//#endif
//
//#ifdef IFC2X3_READER
//
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSpecularHighlightSelect.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSpecularExponent.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSpecularRoughness.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcColourOrFactor.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcColourRgb.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcNormalisedRatioMeasure.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcDraughtingPreDefinedColour.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcLabel.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSurfaceStyleElementSelect.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSurfaceStyle.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSurfaceStyleShading.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSurfaceStyleRendering.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcStyledItem.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcPresentationStyleAssignment.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcPresentationStyleSelect.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcPresentationStyle.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcCartesianPoint.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcProperty.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcComplexProperty.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcIdentifier.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcPropertySingleValue.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcInteger.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcCurveStyle.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcFillAreaStyle.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcTextStyle.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcNullStyle.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcExternallyDefinedSurfaceStyle.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSurfaceStyleLighting.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSurfaceStyleRefraction.h"
//#include "OpenInfraPlatform/Ifc2x3/entity/include/IfcSurfaceStyleWithTextures.h"
//
//using namespace OpenInfraPlatform::Ifc2x3;

//#endif

using namespace OpenInfraPlatform::IfcGeometryConverter;

/**********************************************************************************************/

StylesConverter::StylesConverter()
{
}

/**********************************************************************************************/

StylesConverter::~StylesConverter()
{
}

/**********************************************************************************************/

//float convertIfcSpecularHighlightSelect(shared_ptr<IfcSpecularHighlightSelect> highlight_select )
//{
//	float shininess = 64;
//
//	if( dynamic_pointer_cast<IfcSpecularExponent>(highlight_select) )
//	{
//		shared_ptr<IfcSpecularExponent> spec = dynamic_pointer_cast<IfcSpecularExponent>(highlight_select);
//		osg::ref_ptr<osgFX::SpecularHighlights> spec_highlights = new osgFX::SpecularHighlights();
//		spec_highlights->setSpecularExponent( spec->m_value );
//		// todo: add to scenegraph
//
//	}
//	else if( dynamic_pointer_cast<IfcSpecularRoughness>(highlight_select) )
//	{
//		shared_ptr<IfcSpecularRoughness> specRough = dynamic_pointer_cast<IfcSpecularRoughness>(highlight_select);
//		shininess = (float) specRough->m_value*128;
//		if (shininess<=1.0) shininess=1.0;
//	}
//	return shininess;
//}
//
//void convertIfcColourRgb( shared_ptr<IfcColourRgb> color_rgb, osg::Vec4f& color )
//{
//	if( color_rgb->m_Red )
//	{
//		color._v[0] = (float)color_rgb->m_Red->m_value;
//	}
//	if( color_rgb->m_Green)
//	{
//		color._v[1] = (float)color_rgb->m_Green->m_value;
//	}
//	if( color_rgb->m_Blue)
//	{
//		color._v[2] = (float)color_rgb->m_Blue->m_value;
//	}
//}
//
//void convertIfcColourOrFactor( shared_ptr<IfcColourOrFactor> colorOrFactor, osg::Vec4f& src_color, osg::Vec4f& target_color)
//{
//	// TYPE IfcColourOrFactor = SELECT ( IfcNormalisedRatioMeasure, IfcColourRgb);
//	shared_ptr<IfcColourRgb> color_rgb = dynamic_pointer_cast<IfcColourRgb>(colorOrFactor);
//	if( color_rgb )
//	{
//		convertIfcColourRgb( color_rgb, target_color );
//		return;
//	}
//
//	shared_ptr<IfcNormalisedRatioMeasure> ratio_measure = dynamic_pointer_cast<IfcNormalisedRatioMeasure>(colorOrFactor);
//	if( ratio_measure )
//	{
//		float factor = ratio_measure->m_value;
//		target_color.set( src_color.r()*factor, src_color.g()*factor, src_color.b()*factor, src_color.a() );
//		return;
//	}
//}
//
//void convertIfcColour( shared_ptr<IfcColour> ifc_color, osg::Vec4f& color )
//{
//	// IfcColour = SELECT ( IfcColourSpecification, IfcPreDefinedColour );
//	shared_ptr<IfcColourSpecification> color_spec = dynamic_pointer_cast<IfcColourSpecification>(ifc_color);
//	if( color_spec )
//	{
//		// ENTITY IfcColourSpecification ABSTRACT SUPERTYPE OF(IfcColourRgb);
//		shared_ptr<IfcColourRgb> color_rgb = dynamic_pointer_cast<IfcColourRgb>(color_spec);
//		if( color_rgb )
//		{
//			convertIfcColourRgb( color_rgb, color );
//		}
//		return;
//	}
//
//	shared_ptr<IfcPreDefinedColour> predefined_color = dynamic_pointer_cast<IfcPreDefinedColour>(ifc_color);
//	if( predefined_color )
//	{
//		// ENTITY IfcPreDefinedColour ABSTRACT SUPERTYPE OF(IfcDraughtingPreDefinedColour)
//		shared_ptr<IfcDraughtingPreDefinedColour> draughting_predefined_color = dynamic_pointer_cast<IfcDraughtingPreDefinedColour>(predefined_color);
//		if( draughting_predefined_color )
//		{
//			if( draughting_predefined_color->m_Name )
//			{
//				std::string predefined_name = draughting_predefined_color->m_Name->m_value;
//				if( _stricmp( predefined_name.c_str(), "black")==0 )		color.set(0.0f,0.0f,0.0f, 1.f);		
//				else if( _stricmp( predefined_name.c_str(), "red")==0 )		color.set(1.0f,0.0f,0.0f, 1.f);
//				else if( _stricmp( predefined_name.c_str(), "green")==0 )	color.set(0.0f,1.0f,0.0f, 1.f);
//				else if( _stricmp( predefined_name.c_str(), "blue")==0 )	color.set(0.0f,0.0f,1.0f, 1.f);
//				else if( _stricmp( predefined_name.c_str(), "yellow")==0 )	color.set(1.0f,1.0f,0.0f, 1.f);
//				else if( _stricmp( predefined_name.c_str(), "magenta")==0 )	color.set(1.0f,0.0f,1.0f, 1.f);
//				else if( _stricmp( predefined_name.c_str(), "cyan")==0 )	color.set(0.0f,1.0f,1.0f, 1.f);
//				else if( _stricmp( predefined_name.c_str(), "white")==0 )	color.set(1.0f,1.0f,1.0f, 1.f);
//			}
//		}
//		return;
//	}
//}
//
//
//osg::StateSet* StylesConverter::convertIfcSurfaceStyle( shared_ptr<IfcSurfaceStyle> surface_style )
//{
//	const int style_id = surface_style->getId();
//	std::map<int,osg::ref_ptr<osg::StateSet> >::iterator it_styles = m_map_ifc_styles.find(style_id);
//	if( it_styles != m_map_ifc_styles.end() ){	return it_styles->second; }
//
//	std::vector<shared_ptr<IfcSurfaceStyleElementSelect> >& vec_styles = surface_style->m_Styles;
//	if( vec_styles.size() == 0 )
//	{
//		return NULL;
//	}
//
//	osg::StateSet* stateset = NULL;
//	for( std::vector<shared_ptr<IfcSurfaceStyleElementSelect> >::iterator it=vec_styles.begin(); it!=vec_styles.end(); ++it )
//	{
//		shared_ptr<IfcSurfaceStyleElementSelect> surf_style_element_select = (*it);
//		if( !surf_style_element_select )
//		{
//			continue;
//		}
//		// TYPE IfcSurfaceStyleElementSelect = SELECT	(IfcExternallyDefinedSurfaceStyle	,IfcSurfaceStyleLighting	,IfcSurfaceStyleRefraction	,IfcSurfaceStyleShading	,IfcSurfaceStyleWithTextures);
//
//		shared_ptr<IfcExternallyDefinedSurfaceStyle> ext_surf_style = dynamic_pointer_cast<IfcExternallyDefinedSurfaceStyle>(surf_style_element_select);
//		if( ext_surf_style )
//		{
//			std::cout << "IfcExternallyDefinedSurfaceStyle not implemented" << std::endl;
//			continue;
//		}
//
//		shared_ptr<IfcSurfaceStyleLighting> style_lighting = dynamic_pointer_cast<IfcSurfaceStyleLighting>(surf_style_element_select);
//		if( style_lighting )
//		{
//			std::cout << "IfcSurfaceStyleLighting not implemented" << std::endl;
//			continue;
//		}
//
//		shared_ptr<IfcSurfaceStyleRefraction> style_refraction = dynamic_pointer_cast<IfcSurfaceStyleRefraction>(surf_style_element_select);
//		if( style_refraction )
//		{
//			std::cout << "IfcSurfaceStyleRefraction not implemented" << std::endl;
//			continue;
//		}
//
//		shared_ptr<IfcSurfaceStyleShading> surface_style_shading = dynamic_pointer_cast<IfcSurfaceStyleShading>(surf_style_element_select);
//		if( surface_style_shading )
//		{
//			osg::Vec4f color( 0.8f, 0.8f, 0.8f, 1.f );
//			if( surface_style_shading->m_SurfaceColour)
//			{
//				shared_ptr<IfcColourRgb> surf_color = surface_style_shading->m_SurfaceColour;
//				convertIfcColourRgb( surf_color, color );
//			}
//
//			if( color.r() < 0.05 && color.g() < 0.05 && color.b() < 0.05 )
//			{
//				color.set( 0.9f, 0.9f, 0.9f, color.a() );
//			}
//
//			osg::Vec4f ambientColor( color );
//			osg::Vec4f emissiveColor( 0.0f, 0.0f, 0.0f, 1.f );
//			osg::Vec4f diffuseColor( color );
//			osg::Vec4f specularColor( color );
//			float shininess = 35.f;
//			float transparency = 0.7f;
//			bool set_transparent = false;
//
//			shared_ptr<IfcSurfaceStyleRendering> surf_style_rendering = dynamic_pointer_cast<IfcSurfaceStyleRendering>(surf_style_element_select);
//			if( surf_style_rendering )
//			{
//				if( surf_style_rendering->m_DiffuseColour)
//				{
//					shared_ptr<IfcColourOrFactor> color_or_factor = surf_style_rendering->m_DiffuseColour;
//					convertIfcColourOrFactor(color_or_factor, color, diffuseColor);
//
//				}
//
//				if( surf_style_rendering->m_SpecularColour)
//				{
//					shared_ptr<IfcColourOrFactor> color_or_factor = surf_style_rendering->m_SpecularColour;
//					//convertIfcColourOrFactor(color_or_factor, color, specularColor);
//				}
//
//				if( surf_style_rendering->m_Transparency)
//				{
//					// in IFC 1 is transparent, 0 is opaque. if not given, the value 0 (opaque) is assumed
//					// in osg, 1 is opaque, 0 is transparent
//					transparency = 1.f - (float)surf_style_rendering->m_Transparency->m_value;
//					if( transparency < 0.08f )
//					{
//						transparency = 0.08f;
//					}
//					
//					if( transparency > 1.f )
//					{
//						transparency = 1.f;
//					}
//
//					if( transparency < 0.99f )
//					{
//						set_transparent = true;
//					}
//				}
//
//				if( surf_style_rendering->m_SpecularHighlight)
//				{
//					shared_ptr<IfcSpecularHighlightSelect> spec_highlight = surf_style_rendering->m_SpecularHighlight;
//					shininess = convertIfcSpecularHighlightSelect( spec_highlight );
//				}
//			}
//			ambientColor *= 0.8f;
//
//			ambientColor._v[3] = transparency;
//			diffuseColor._v[3] = transparency;
//			specularColor._v[3] = transparency;
//			emissiveColor._v[3] = transparency;
//			
//			osg::ref_ptr<osg::Material> mat = new osg::Material();
//			mat->setAmbient( osg::Material::FRONT_AND_BACK, ambientColor );
//			mat->setDiffuse( osg::Material::FRONT_AND_BACK, diffuseColor );
//			mat->setSpecular( osg::Material::FRONT_AND_BACK, specularColor );
//			mat->setShininess( osg::Material::FRONT_AND_BACK, shininess );
//			mat->setColorMode( osg::Material::SPECULAR );
//			mat->setEmission( osg::Material::FRONT_AND_BACK, emissiveColor );
//
//			if( stateset == NULL )
//			{
//				stateset = new osg::StateSet();
//				m_map_ifc_styles[style_id] = stateset;
//			}
//			stateset->setAttribute( mat, osg::StateAttribute::ON );
//			
//			if( set_transparent )
//			{
//				mat->setTransparency( osg::Material::FRONT_AND_BACK, transparency );	
//				stateset->setMode( GL_BLEND, osg::StateAttribute::ON );
//				stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
//			}
//			else
//			{
//				// blending is disabled in this case, so set transparency in case blending is enabled at the root node
//				mat->setTransparency( osg::Material::FRONT_AND_BACK, 0.7f );
//			}
//			continue;
//		}
//
//		shared_ptr<IfcSurfaceStyleWithTextures> style_texture = dynamic_pointer_cast<IfcSurfaceStyleWithTextures>(surf_style_element_select);
//		if( style_texture )
//		{
//			std::cout << "IfcSurfaceStyleWithTextures not implemented" << std::endl;
//			continue;
//		}
//		
//	}
//	return stateset;
//}
//
//osg::StateSet* StylesConverter::convertIfcStyledItem( weak_ptr<IfcStyledItem> styled_item_weak )
//{
//	shared_ptr<IfcStyledItem> styled_item( styled_item_weak );
//	const int style_id = styled_item->getId();
//
//	std::map<int,osg::ref_ptr<osg::StateSet> >::iterator it_styles = m_map_ifc_styles.find(style_id);
//	if( it_styles != m_map_ifc_styles.end() ){	return m_map_ifc_styles[style_id]; }
//
//	osg::StateSet* resulting_stateset = NULL;
//
//	std::vector<shared_ptr<IfcStyleAssignmentSelect> >& vec_style_assigns = styled_item->m_Styles;
//	std::vector<shared_ptr<IfcStyleAssignmentSelect> >::iterator it_style_assigns;
//	
//	for( it_style_assigns=vec_style_assigns.begin(); it_style_assigns!=vec_style_assigns.end(); ++it_style_assigns )
//	{
//		// TYPE IfcStyleAssignmentSelect = SELECT	(IfcPresentationStyle	,IfcPresentationStyleAssignment);
//		shared_ptr<IfcStyleAssignmentSelect> style_assign_select = (*it_style_assigns);
//		shared_ptr<IfcPresentationStyleAssignment> style_assign = dynamic_pointer_cast<IfcPresentationStyleAssignment>(style_assign_select);    
//		if( style_assign )
//		{
//			std::vector<shared_ptr<IfcPresentationStyleSelect> >& vec_styles = style_assign->m_Styles;
//		
//			std::vector<shared_ptr<IfcPresentationStyleSelect> >::iterator it_presentation_styles;
//			for( it_presentation_styles=vec_styles.begin(); it_presentation_styles!=vec_styles.end(); ++it_presentation_styles )
//			{
//				// TYPE IfcPresentationStyleSelect = SELECT	(IfcCurveStyle	,IfcFillAreaStyle	,IfcNullStyle	,IfcSurfaceStyle	,IfcSymbolStyle	,IfcTextStyle);
//				shared_ptr<IfcPresentationStyleSelect> pres_style_select = (*it_presentation_styles);
//				osg::StateSet* presentation_style_stateset = convertIfcPresentationStyleSelect( pres_style_select );
//				if( presentation_style_stateset != NULL )
//				{
//					if( resulting_stateset == NULL )
//					{
//						resulting_stateset = presentation_style_stateset;
//					}
//					else
//					{
//						resulting_stateset->merge( *presentation_style_stateset );
//					}
//				}
//			}
//			continue;
//		}
//		
//
//		// ENTITY IfcPresentationStyle ABSTRACT SUPERTYPE OF(ONEOF(IfcCurveStyle, IfcFillAreaStyle, IfcSurfaceStyle, IfcSymbolStyle, IfcTextStyle));
//		shared_ptr<IfcPresentationStyle> presentation_style = dynamic_pointer_cast<IfcPresentationStyle>(style_assign_select);
//		if( presentation_style )
//		{
//			osg::StateSet* presentation_style_stateset = convertIfcPresentationStyle( presentation_style );
//			if( presentation_style_stateset != NULL )
//			{
//				if( resulting_stateset == NULL )
//				{
//					resulting_stateset = presentation_style_stateset;
//				}
//				else
//				{
//					resulting_stateset->merge( *presentation_style_stateset );
//				}
//			}
//			continue;
//		}
//
//		continue;
//	}
//	return resulting_stateset;
//}
//
//osg::StateSet* StylesConverter::convertIfcComplexPropertyColor( shared_ptr<IfcComplexProperty> complex_property )
//{
//	std::vector<shared_ptr<IfcProperty> >& vec_HasProperties = complex_property->m_HasProperties;
//	if( !complex_property->m_UsageName ) return NULL;
//	if( vec_HasProperties.size() < 3 ) return NULL;
//	std::string usage_name = complex_property->m_UsageName->m_value;
//	if( _stricmp( usage_name.c_str(), "Color" ) != 0 ) return NULL;
//	
//	int complex_property_id = complex_property->getId();
//	std::map<int,osg::ref_ptr<osg::StateSet> >::iterator it_styles = m_map_ifc_styles.find(complex_property_id);
//	if( it_styles != m_map_ifc_styles.end() )
//	{
//		// use existing stateset
//		return it_styles->second;
//	}
//
//	shared_ptr<IfcPropertySingleValue> prop1 = dynamic_pointer_cast<IfcPropertySingleValue>(complex_property->m_HasProperties[0]);
//	shared_ptr<IfcPropertySingleValue> prop2 = dynamic_pointer_cast<IfcPropertySingleValue>(complex_property->m_HasProperties[1]);
//	shared_ptr<IfcPropertySingleValue> prop3 = dynamic_pointer_cast<IfcPropertySingleValue>(complex_property->m_HasProperties[2]);
//	if( prop1 && prop2 && prop3 )
//	{
//		if( prop1->m_NominalValue && prop2->m_NominalValue && prop3->m_NominalValue )
//		{
//			shared_ptr<IfcInteger> prop1v = dynamic_pointer_cast<IfcInteger>(prop1->m_NominalValue);
//			shared_ptr<IfcInteger> prop2v = dynamic_pointer_cast<IfcInteger>(prop2->m_NominalValue);
//			shared_ptr<IfcInteger> prop3v = dynamic_pointer_cast<IfcInteger>(prop3->m_NominalValue);
//
//			if( prop1v && prop2v && prop3v )
//			{
//				double r = prop1v->m_value/255.0;
//				double g = prop2v->m_value/255.0;
//				double b = prop3v->m_value/255.0;
//
//#ifdef REUSE_EXISTING_STATESETS_SAME_COLOR
//				// if there is a stateset with the same colors, use that one
//				std::map<int,osg::ref_ptr<osg::StateSet> >::iterator it = m_map_ifc_complex_property_color.begin();
//				for( ; it!=m_map_ifc_complex_property_color.end(); ++it )
//				{
//					osg::StateSet* existing_stateset = it->second.get();
//					osg::StateAttribute* state_att = existing_stateset->getAttribute( osg::StateAttribute::MATERIAL );
//					osg::Material* existing_material = dynamic_cast<osg::Material*>(state_att);
//					if( existing_material )
//					{
//						osg::Vec4f color = existing_material->getDiffuse( osg::Material::FRONT );
//						if( fabs(color.r()-r) > 0.04 )
//						{
//							continue;
//						}
//						if( fabs(color.g()-g) > 0.04 )
//						{
//							continue;
//						}
//						if( fabs(color.b()-b) > 0.04 )
//						{
//							continue;
//						}
//
//						return existing_stateset;
//					}
//				}
//#endif
//
//				if( r < 0.05 && g < 0.05 && b < 0.05 )
//				{
//					r = 0.9;
//					g = 0.9;
//					b = 0.9;
//				}
//
//				osg::Vec4f color( r, g, b, 1.f );
//				osg::ref_ptr<osg::Material> mat = new osg::Material();
//				mat->setAmbient( osg::Material::FRONT_AND_BACK, color );
//				mat->setDiffuse( osg::Material::FRONT_AND_BACK, color );
//				mat->setSpecular( osg::Material::FRONT_AND_BACK, color );
//				mat->setShininess( osg::Material::FRONT_AND_BACK, 35.f );
//				mat->setTransparency( osg::Material::FRONT_AND_BACK, 0.7f );
//				mat->setColorMode( osg::Material::SPECULAR );
//
//				osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
//				stateset->setAttribute( mat, osg::StateAttribute::ON );
//
//				m_map_ifc_styles[complex_property_id] = stateset;
//
//				return stateset;
//			}
//		}
//	}
//	return NULL;
//}
//
//osg::StateSet* StylesConverter::convertIfcPresentationStyle( shared_ptr<IfcPresentationStyle> presentation_style )
//{
//	// ENTITY IfcPresentationStyle	ABSTRACT SUPERTYPE OF(ONEOF(IfcCurveStyle, IfcFillAreaStyle, IfcSurfaceStyle, IfcSymbolStyle, IfcTextStyle));
//	osg::StateSet* stateset = NULL;
//	shared_ptr<IfcCurveStyle> curve_style = dynamic_pointer_cast<IfcCurveStyle>( presentation_style );
//	if( curve_style )
//	{
//		return convertIfcCurveStyle( curve_style );
//		return stateset;
//	}
//
//	shared_ptr<IfcFillAreaStyle> fill_area_style = dynamic_pointer_cast<IfcFillAreaStyle>( presentation_style );
//	if( fill_area_style )
//	{
//
//		std::cout << "IfcFillAreaStyle not implemented" << std::endl;
//		return stateset;
//	}
//
//
//	shared_ptr<IfcSurfaceStyle> surface_style = dynamic_pointer_cast<IfcSurfaceStyle>( presentation_style );
//	if( surface_style )
//	{
//		return convertIfcSurfaceStyle( surface_style );
//	}
//
//	shared_ptr<IfcTextStyle> text_style = dynamic_pointer_cast<IfcTextStyle>( presentation_style );
//	if( text_style )
//	{
//		std::cout << "IfcTextStyle not implemented" << std::endl;
//
//		return stateset;
//	}
//
//
//	return stateset;
//}
//
//osg::StateSet* StylesConverter::convertIfcPresentationStyleSelect( shared_ptr<IfcPresentationStyleSelect> presentation_style )
//{
//	// TYPE IfcPresentationStyleSelect = SELECT	(IfcCurveStyle	,IfcFillAreaStyle	,IfcNullStyle	,IfcSurfaceStyle	,IfcSymbolStyle	,IfcTextStyle);
//	osg::StateSet* stateset = NULL;
//	shared_ptr<IfcCurveStyle> curve_style = dynamic_pointer_cast<IfcCurveStyle>( presentation_style );
//	if( curve_style )
//	{
//		return convertIfcCurveStyle( curve_style );
//		return stateset;
//	}
//
//	shared_ptr<IfcFillAreaStyle> fill_area_style = dynamic_pointer_cast<IfcFillAreaStyle>( presentation_style );
//	if( fill_area_style )
//	{
//
//		std::cout << "IfcFillAreaStyle not implemented" << std::endl;
//		return stateset;
//	}
//
//	shared_ptr<IfcNullStyle> null_style = dynamic_pointer_cast<IfcNullStyle>( presentation_style );
//	if( null_style )
//	{
//
//		std::cout << "IfcNullStyle not implemented" << std::endl;
//		return stateset;
//	}
//
//
//	shared_ptr<IfcSurfaceStyle> surface_style = dynamic_pointer_cast<IfcSurfaceStyle>( presentation_style );
//	if( surface_style )
//	{
//		return convertIfcSurfaceStyle( surface_style );
//	}
//
//	shared_ptr<IfcTextStyle> text_style = dynamic_pointer_cast<IfcTextStyle>( presentation_style );
//	if( text_style )
//	{
//
//		std::cout << "IfcTextStyle not implemented" << std::endl;
//		return stateset;
//	}
//
//
//	return stateset;
//}
//
//
//osg::StateSet* StylesConverter::convertIfcCurveStyle( shared_ptr<IfcCurveStyle> curve_style )
//{
//	int style_id = curve_style->getId();
//	std::map<int,osg::ref_ptr<osg::StateSet> >::iterator it_styles = m_map_ifc_styles.find(style_id);
//	if( it_styles != m_map_ifc_styles.end() ){	return m_map_ifc_styles[style_id]; }
//
//	//CurveFont	 : OPTIONAL IfcCurveFontOrScaledCurveFontSelect;
//	//CurveWidth	 : OPTIONAL IfcSizeSelect;
//	//CurveColour	 : OPTIONAL IfcColour;
//
//	osg::StateSet* stateset = NULL;
//
//	shared_ptr<IfcColour> curve_color = curve_style->m_CurveColour;
//	if( curve_color )
//	{
//		osg::Vec4f color( 0.8f, 0.8f, 0.8f, 1.f );
//		convertIfcColour( curve_color, color );
//
//		if( color.r() < 0.05 && color.g() < 0.05 && color.b() < 0.05 )
//		{
//			color.set( 0.9f, 0.9f, 0.9f, color.a() );
//		}
//
//		osg::Vec4f ambientColor( color );
//		osg::Vec4f emissiveColor( 0.0f, 0.0f, 0.0f, 1.f );
//		osg::Vec4f diffuseColor( color );
//		osg::Vec4f specularColor( color );
//		float shininess = 35.f;
//		float transparency = 0.7f;
//		bool set_transparent = false;
//
//		ambientColor *= 0.8f;
//
//		ambientColor._v[3] = transparency;
//		diffuseColor._v[3] = transparency;
//		specularColor._v[3] = transparency;
//		emissiveColor._v[3] = transparency;
//
//		osg::ref_ptr<osg::Material> mat = new osg::Material();
//		mat->setAmbient( osg::Material::FRONT_AND_BACK, ambientColor );
//		mat->setDiffuse( osg::Material::FRONT_AND_BACK, diffuseColor );
//		mat->setSpecular( osg::Material::FRONT_AND_BACK, specularColor );
//		mat->setShininess( osg::Material::FRONT_AND_BACK, shininess );
//		mat->setColorMode( osg::Material::SPECULAR );
//		mat->setEmission( osg::Material::FRONT_AND_BACK, emissiveColor );
//
//		stateset = new osg::StateSet();
//		m_map_ifc_styles[style_id] = stateset;
//
//		stateset->setAttribute( mat, osg::StateAttribute::ON );
//
//		if( set_transparent )
//		{
//			mat->setTransparency( osg::Material::FRONT_AND_BACK, transparency );	
//			stateset->setMode( GL_BLEND, osg::StateAttribute::ON );
//			stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
//		}
//		else
//		{
//			// blending is disabled in this case, so set transparency in case blending is enabled at the root node
//			mat->setTransparency( osg::Material::FRONT_AND_BACK, 0.7f );
//		}
//	}
//	return stateset;
//}
