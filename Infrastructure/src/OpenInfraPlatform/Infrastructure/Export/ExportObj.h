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
#ifndef OpenInfraPlatform_Infrastructure_ObjExport_b64d487c_2700_4abb_8aab_fc866636400a_h
#define OpenInfraPlatform_Infrastructure_ObjExport_b64d487c_2700_4abb_8aab_fc866636400a_h

#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class ExportObj : private boost::noncopyable
		{
		public:
			ExportObj();

			virtual ~ExportObj()
			{
			}

		private:
		}; // end class ObjExport
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ExportObj;
}

#endif // end define OpenInfraPlatform_Infrastructure_ObjExport_b64d487c_2700_4abb_8aab_fc866636400a_h
