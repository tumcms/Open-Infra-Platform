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

#include <buw.Rasterizer.h>

#include "..\namespace.h"


OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

/**
\brief Base class for all effects used in OIP.

The geometry is moved to the (0,0,0) in the viewport before rendering.
This class provides an interface for the offset needed.

\note The offset is to be applied with summation "+". I.e. the value of offset tells how far away the (0,0,0) lies from the mid-point of all loaded models.
*/
class EffectBase : public buw::Effect {
public:
	//! Constructor
    EffectBase(buw::IRenderSystem* renderSytem);
	//! Destructor
	~EffectBase() {}

	/** 
	\brief Sets the offset to the new value.

	\note Calls changeOffset.

	\param[in] offsetNew The new value of offset.
	*/
    void setOffset( const buw::Vector3d& offsetNew );

	/**
	\brief Gets the current offset.

	\return The currently applied offset.
	*/
    buw::Vector3d getOffset() const { return offset_; }

protected:

	/**
	\brief The interface function that every deriving class must override.
	*/
    virtual void changeOffset( const buw::Vector3d& offsetOld, const buw::Vector3d& offsetNew ) = 0;

private:

	//! the applied offset
    buw::Vector3d offset_;
	//! was the offset set already
	bool offsetValid_;

};

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END

EMBED_RENDERING_INTO_OIP_NAMESPACE(EffectBase)
