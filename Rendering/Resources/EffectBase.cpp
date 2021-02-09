/*
    Copyright (c) 2018 Technical University of Munich
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

#include "EffectBase.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

EffectBase::EffectBase(buw::IRenderSystem* renderSytem) 
    : buw::Effect(renderSytem),
      offset_(0.,0.,0.), offsetValid_(false)
{

}

void EffectBase::setOffset( const buw::Vector3d& offsetNew )
{
    if( offsetNew == offset_ && offsetValid_)
        return;

    changeOffset( offset_, offsetNew );

    offset_ = offsetNew;
	offsetValid_ = true;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END
