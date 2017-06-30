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

#include "CoordinateSystem.h"

void OpenInfraPlatform::UserInterface::drawCoordinateSystem(
	buw::ReferenceCounted<buw::VertexCacheLineT<buw::VertexPosition3Color3Size1>> vertexCacheLine,
	float scale/* = 1.0f*/, 
	eCoordinateSystemType type/* = eCoordinateSystemType::Autodesk*/)
{
	// draw axes
	
	/// X
	// draw x-Axis	
	buw::Vector3f redColor = { 153.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f };
	
	vertexCacheLine->drawLine(
		{ { buw::Vector3f(-0.4f,0.0f,0.0f) * 100.0f * scale }, redColor, 1.0f },
		{ { buw::Vector3f(0.4f,0.0f,0.0f) * 100.0f * scale }, redColor, 1.0f }
	);

	// draw arrowhead
	vertexCacheLine->drawLine( 
		{ { buw::Vector3f(0.4f,0.0f,0.0f) * 100.0f * scale }, redColor, 1.0f },
		{ { buw::Vector3f(0.375f,0.0f,0.025f) * 100.0f * scale }, redColor, 1.0f }
	);
	vertexCacheLine->drawLine( 
		{ { buw::Vector3f(0.4f,0.0f,0.0f) * 100.0f * scale }, redColor, 1.0f },
		{ { buw::Vector3f(0.375f,0.0f,-0.025f) * 100.0f * scale }, redColor, 1.0f }
	);

	// draw x character
	buw::Vector3f offsetX(3.5, 0.0f, 0.0f);
	offsetX *= scale;

	vertexCacheLine->drawLine( 
		{ { offsetX + buw::Vector3f(0.4f,0.0f,0.0f) * 100.0f * scale }, redColor, 1.0f },
		{ { offsetX + buw::Vector3f(0.375f,0.0f,0.025f) * 100.0f * scale }, redColor, 1.0f }
	);
/*
	vertexCacheLine->drawLine( offsetX + buw::Vector3f(0.4f,0.0f,0.0f) * 100.0f * scale, offsetX + buw::Vector3f(0.375f,0.0f,-0.025f) * 100.0f * scale);

	vertexCacheLine->drawLine( offsetX + buw::Vector3f(0.4f,0.0f,0.0f) * 100.0f * scale, offsetX + buw::Vector3f(2*(0.4f-0.375f) + 0.375f,0.0f,0.025f) * 100.0f * scale);
	vertexCacheLine->drawLine( offsetX + buw::Vector3f(0.4f,0.0f,0.0f) * 100.0f * scale, offsetX + buw::Vector3f(2*(0.4f-0.375f) + 0.375f,0.0f,-0.025f) * 100.0f * scale);

	/// Y

	// draw y-Axis
	vertexCacheLine->setColor(30.0f / 255.0f, 153.0f / 255.0f, 30.0f / 255.0f);  // green color
	vertexCacheLine->drawLine( buw::Vector3f(0.0f,-0.4f,0.0f) * 100.0f * scale, buw::Vector3f(0.0f,0.4f,0.0f) * 100.0f * scale);

	// draw arrowhead
	vertexCacheLine->drawLine( buw::Vector3f(0.0f,0.4f,0.0f) * 100.0f * scale, buw::Vector3f(0.0f,0.375f,0.025f) * 100.0f * scale);
	vertexCacheLine->drawLine( buw::Vector3f(0.0f,0.4f,0.0f) * 100.0f * scale, buw::Vector3f(0.0f,0.375f,-0.025f) * 100.0f * scale);

	buw::Vector3f offsetY(0.0, 3.5f, 0.0f);
	offsetY *= scale;
	
	if(type == eCoordinateSystemType::OpenGL)
	{
		// draw y character
		vertexCacheLine->drawLine(offsetY + buw::Vector3f(0.0f,0.375f,0.0f) * 100.0f * scale,offsetY + buw::Vector3f(0.0f,0.400f,0.0f) * 100.0f * scale);
		vertexCacheLine->drawLine(offsetY + buw::Vector3f(0.0f,0.400f,0.0f) * 100.0f * scale,offsetY + buw::Vector3f(0.0f,0.425f,0.025f) * 100.0f * scale);
		vertexCacheLine->drawLine(offsetY + buw::Vector3f(0.0f,0.400f,0.0f) * 100.0f * scale,offsetY + buw::Vector3f(0.0f,0.425f,-0.025f) * 100.0f * scale);
	}
	else // type == eCoordinateSystemType::Autodesk
	{
		// draw z character
		vertexCacheLine->drawLine(offsetY + buw::Vector3f(0.0f,0.375f,-0.025f) * 100.0f * scale,offsetY + buw::Vector3f(0.0f,0.375f,0.025f) * 100.0f * scale);
		vertexCacheLine->drawLine(offsetY + buw::Vector3f(0.0f,0.425f,-0.025f) * 100.0f * scale,offsetY + buw::Vector3f(0.0f,0.375f,0.025f) * 100.0f * scale);
		vertexCacheLine->drawLine(offsetY + buw::Vector3f(0.0f,0.425f,-0.025f) * 100.0f * scale,offsetY + buw::Vector3f(0.0f,0.425f,0.025f) * 100.0f * scale);
	}

	/// Z

	buw::Vector3f offsetZ(0.0, 0.0f, -3.5f);
	offsetZ *= scale;

	// draw z-Axis
	vertexCacheLine->setColor(30.0f / 255.0f, 30.0f / 255.0f, 153.0f / 255.0f); // blue color
	vertexCacheLine->drawLine( buw::Vector3f(0.0f,0.0f,-0.4f) * 100.0f * scale, buw::Vector3f(0.0f,0.0f,0.4f) * 100.0f * scale);

	// draw arrowhead
	vertexCacheLine->drawLine( buw::Vector3f(0.0f,0.0f,-0.4f) * 100.0f * scale, buw::Vector3f( 0.025f, 0.0f,-0.375f) * 100.0f * scale);
	vertexCacheLine->drawLine( buw::Vector3f(0.0f,0.0f,-0.4f) * 100.0f * scale, buw::Vector3f(-0.025f,0.0f,-0.375f) * 100.0f * scale);

	if(type == eCoordinateSystemType::OpenGL)
	{
		// draw z character
		vertexCacheLine->drawLine( offsetZ + buw::Vector3f(-0.025f,0.0f,-0.375f) * 100.0f * scale, offsetZ + buw::Vector3f(0.025f,0.0f,-0.425f) * 100.0f * scale);
		vertexCacheLine->drawLine( offsetZ + buw::Vector3f(-0.025f,0.0f,-0.425f) * 100.0f * scale, offsetZ + buw::Vector3f(0.025f,0.0f,-0.425f) * 100.0f * scale);
		vertexCacheLine->drawLine( offsetZ + buw::Vector3f(-0.025f,0.0f,-0.375f) * 100.0f * scale, offsetZ + buw::Vector3f(0.025f,0.0f,-0.375f) * 100.0f * scale);
	}
	else // type == eCoordinateSystemType::Autodesk
	{
		//	draw y character
		vertexCacheLine->drawLine( offsetZ + buw::Vector3f(0.0f,0.0f,-0.4f) * 100.0f * scale, offsetZ + buw::Vector3f( 0.025f,0.0f, -0.375f - 2*0.025) * 100.0f * scale);
		vertexCacheLine->drawLine( offsetZ + buw::Vector3f(0.0f,0.0f,-0.4f) * 100.0f * scale, offsetZ + buw::Vector3f(-0.025f,0.0f, -0.375f - 2*0.025) * 100.0f * scale);
		vertexCacheLine->drawLine( offsetZ + buw::Vector3f(0.0f,0.0f,-0.4f + 0.025) * 100.0f * scale, offsetZ + buw::Vector3f(0.0f,0.0f,-0.4f) * 100.0f * scale);
	}
	*/
}

//void OpenInfraPlatform::UserInterface::drawGrid( 
//	buw::ReferenceCounted<buw::VertexCacheLine> vertexCacheLine,
//	const buw::drawGridDescription& dgd )
//{
//	float fPGridRed = 61.0f/255.0f;
//	float fPGridGreen = 61.0f/255.0f;
//	float fPGridBlue = 61.0f/255.0f;
//
//	float fSGridRed = 99.0f/255.0f;
//	float fSGridGreen = 99.0f/255.0f;
//	float fSGridBlue = 99.0f/255.0f;
//	/*
//
//		TopLeft               TopRight
//		+---------+---------+
//		|         |         |
//		|         |         |
//		|         |         |
//		|         |         |
//		|---------+---------|
//		|         |         |
//		|         |         |
//		|         |         |
//		+---------+---------+
//		BottomLeft            BottomRight
//	*/
//
//	float segementWidth = dgd.width / dgd.widthSegments;
//	float segementHeight = dgd.height / dgd.widthSegments;
//
//	buw::Vector3f bottomLeft;
//	buw::Vector3f bottomRight;
//	buw::Vector3f topLeft;
//	buw::Vector3f topRight;
//				
//	buw::Vector3f incrementalWidthStep;
//	buw::Vector3f incrementalHeightStep;
//
//	switch (dgd.orientation)
//	{
//	case eGridOrientation::POSITIV_Z_ORIENTATION:
// 		topLeft = dgd.center + buw::Vector3f(-dgd.width/2.0f, dgd.height/2.0f, 0.0f);
//		bottomLeft = dgd.center + buw::Vector3f(-dgd.width/2.0f, -dgd.height/2.0f, 0.0f);
//		topRight = dgd.center + buw::Vector3f(dgd.width/2.0f, dgd.height/2.0f, 0.0f);
//		bottomRight = dgd.center + buw::Vector3f(dgd.width/2.0f, -dgd.height/2.0f, 0.0f);
//		incrementalWidthStep = buw::Vector3f(segementWidth, 0.0f, 0.0f);
//		incrementalHeightStep = buw::Vector3f(0.0f, -segementHeight, 0.0f);
//		break;
//
//	case eGridOrientation::POSITIV_Y_ORIENTATION:
//		topLeft = dgd.center + buw::Vector3f(-dgd.width/2.0f, 0.0f, dgd.height/2.0f);
//		bottomLeft = dgd.center + buw::Vector3f(-dgd.width/2.0f, 0.0f, -dgd.height/2.0f);
//		topRight = dgd.center + buw::Vector3f(dgd.width/2.0f, 0.0f,  dgd.height/2.0f);
//		bottomRight = dgd.center + buw::Vector3f(dgd.width/2.0f, 0.0f, -dgd.height/2.0f);
//		incrementalWidthStep = buw::Vector3f(segementWidth, 0.0f, 0.0f);
//		incrementalHeightStep = buw::Vector3f(0.0f, 0.0f, -segementHeight);
//		break;
//
//	case eGridOrientation::POSITIV_X_ORIENTATION:
//		topLeft = dgd.center + buw::Vector3f(0.0f, dgd.height/2.0f, -dgd.width/2.0f);
//		bottomLeft = dgd.center + buw::Vector3f(0.0f, -dgd.height/2.0f, -dgd.width/2.0f);
//		topRight = dgd.center + buw::Vector3f(0.0f,  dgd.height/2.0f, dgd.width/2.0f);
//		bottomRight = dgd.center + buw::Vector3f(0.0f, -dgd.height/2.0f, dgd.width/2.0f);
//		incrementalWidthStep = buw::Vector3f(0.0f, 0.0f, segementWidth);
//		incrementalHeightStep = buw::Vector3f(0.0f, -segementHeight, 0.0f);
//		break;
//
//	default:
//		break;
//	};
//
//					
//	// draw height/horizontal lines - run from leftTop to rightTop
//	buw::Vector3f currentPositionLeftTop = topLeft;
//	buw::Vector3f currentPositionRightTop = topRight;
//	for (int iRows = 0; iRows < dgd.widthSegments+1; iRows++)
//	{
//		if(iRows == 20 && dgd.leaveCoodinateSystemBlank) // special treatment for middle lines
//		{
//			vertexCacheLine->setColor(fPGridRed, fPGridGreen, fPGridBlue);
//
//			buw::Vector3f ir = currentPositionLeftTop + 0.4f * (currentPositionRightTop - currentPositionLeftTop);
//
//			vertexCacheLine->drawLine(
//				buw::Vector3f(currentPositionLeftTop.x(), currentPositionLeftTop.y(), currentPositionLeftTop.z()),
//				buw::Vector3f(ir .x(), ir.y(), ir.z())
//			);
//
//			ir = currentPositionLeftTop + 0.6f * (currentPositionRightTop - currentPositionLeftTop);
//
//			vertexCacheLine->drawLine(
//				buw::Vector3f(ir .x(), ir.y(), ir.z()),
//				buw::Vector3f(currentPositionRightTop.x(), currentPositionRightTop.y(), currentPositionRightTop.z())
//			);
//					
//			currentPositionLeftTop += incrementalHeightStep;
//			currentPositionRightTop += incrementalHeightStep;
//			continue;
//		}
//
//		if((iRows % 5) == 0)
//			vertexCacheLine->setColor(fPGridRed, fPGridGreen, fPGridBlue);
//		else
//			vertexCacheLine->setColor(fSGridRed, fSGridGreen, fSGridBlue);
//				
//		vertexCacheLine->drawLine(
//			buw::Vector3f(currentPositionLeftTop.x(), currentPositionLeftTop.y(), currentPositionLeftTop.z()),
//			buw::Vector3f(currentPositionRightTop.x(), currentPositionRightTop.y(), currentPositionRightTop.z())
//		);
//				
//		currentPositionLeftTop += incrementalHeightStep;
//		currentPositionRightTop += incrementalHeightStep;
//	}
//
//	// draw width/vertical lines - run from leftTop to leftBottom
//	buw::Vector3f currentPositionTop = topLeft;
//	buw::Vector3f currentPositionBottom = bottomLeft;
//	for (int iCols = 0; iCols < dgd.widthSegments+1; iCols++)
//	{
//		if(iCols == 20 && dgd.leaveCoodinateSystemBlank) // special treatment for middle lines
//		{
//			vertexCacheLine->setColor(fPGridRed, fPGridGreen, fPGridBlue);
//
//			buw::Vector3f ir = currentPositionTop + 0.4f * (currentPositionBottom - currentPositionTop);
//
//			vertexCacheLine->drawLine(
//				buw::Vector3f(currentPositionTop.x(), currentPositionTop.y(), currentPositionTop.z()),
//				buw::Vector3f(ir .x(), ir.y(), ir.z())
//			);
//
//			ir = currentPositionTop + 0.6f * (currentPositionBottom - currentPositionTop);
//
//			vertexCacheLine->drawLine(
//				buw::Vector3f(ir .x(), ir.y(), ir.z()),
//				buw::Vector3f(currentPositionBottom.x(), currentPositionBottom.y(), currentPositionBottom.z())
//			);
//						
//
//			currentPositionTop += incrementalWidthStep;
//			currentPositionBottom += incrementalWidthStep;
//			continue;
//		}
//
//		if((iCols % 5) == 0)
//			vertexCacheLine->setColor(fPGridRed, fPGridGreen, fPGridBlue);
//		else
//			vertexCacheLine->setColor(fSGridRed, fSGridGreen, fSGridBlue);
//					
//		vertexCacheLine->drawLine(
//			buw::Vector3f(currentPositionTop.x(), currentPositionTop.y(), currentPositionTop.z()),
//			buw::Vector3f(currentPositionBottom.x(), currentPositionBottom.y(), currentPositionBottom.z())
//		);
//
//		currentPositionTop += incrementalWidthStep;
//		currentPositionBottom += incrementalWidthStep;
//	}
//}