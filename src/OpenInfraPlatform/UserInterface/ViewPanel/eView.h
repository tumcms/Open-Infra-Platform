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

#pragma once
#ifndef OpenInfraPlatform_UserInterface_eView_b7fc0b5d_e69a_43ab_9197_79a8301f2c49_h
#define OpenInfraPlatform_UserInterface_eView_b7fc0b5d_e69a_43ab_9197_79a8301f2c49_h

#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		enum class eView
		{
			HorizontalAlignment,
			VerticalAlignment,
			ThreeDimensional
		};
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	//using OpenInfraPlatform::UserInterface::eView;
}

#endif // end define OpenInfraPlatform_UserInterface_eView_b7fc0b5d_e69a_43ab_9197_79a8301f2c49_h
