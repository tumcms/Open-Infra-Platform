/*
    Copyright (c) 2021 Technical University of Munich
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

#pragma once
#ifndef IFCGEOMETRYMODELRENDERER_H
#define IFCGEOMETRYMODELRENDERER_H

#include <buw.Engine.h>

#include "GeometryModelRenderer.h"
#include "IfcGeometryConverter/ConverterBuw.h"

#include <Effects/IfcGeometryEffect.h>



/*!
 * \brief Utility class to render \c IfcGeometryModel data without UI for automated unit tests.
 * 
 */
class IfcGeometryModelRenderer : public GeometryModelRenderer
{
public:
    /*!
     * \brief Constructs the renderer by injecting the rendering system. 
     * \param renderSystem
     */
	IfcGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem);

	/*!
	 * \brief Releases all resources.
	 */
	virtual ~IfcGeometryModelRenderer();

    /*!
     * \brief Set the model to be rendered. 
     * \param model
     * \note This also moves the camera to it's default position.
     */
    void setModel(const std::shared_ptr<oip::IfcModel>& model);

protected:
	/*!
	* \brief Returns extent of the ifc model in form of a bounding box.
	*/
	virtual oip::BBox getExtent() const override;

    /*!
     * \brief Renders the IfcGeometryEffect.
     */
	virtual void render() override;

private:
	buw::ReferenceCounted<oip::IfcModel> model_ = nullptr;
    buw::ReferenceCounted<OpenInfraPlatform::Rendering::IfcGeometryEffect> ifcGeometryEffect_ = nullptr;
};

#endif // IFCGEOMETRYMODELRENDERER_H
