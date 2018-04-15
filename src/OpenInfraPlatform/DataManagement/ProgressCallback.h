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

#pragma once
#ifndef OpenInfraPlatform_DataManagement_ProgressCallback_D84F130D_FBD7_45E0_93AF_9CA3EC9CB915_h
#define OpenInfraPlatform_DataManagement_ProgressCallback_D84F130D_FBD7_45E0_93AF_9CA3EC9CB915_h

#include <GenericProgressCallback.h>

namespace OpenInfraPlatform {
	namespace DataManagement {
		template <typename Function> class ProgressCallback :  public CCLib::GenericProgressCallback
		{
		public:

		ProgressCallback(const Function &f): CCLib::GenericProgressCallback(), func_(f) {}
	
		virtual void update(float percent) override
		{
			func_(percent);
		}
	
		virtual void setMethodTitle(const char* methodTitle)
		{
	
		}
		
		virtual void setInfo(const char* infoStr)
		{
	
		}
	
		virtual void start()
		{
	
		}
	
		virtual void stop()
		{
	
		}	
		virtual bool isCancelRequested()
		{
			return false;
		}

		private:
			Function func_;
		};
	}
}

#endif





