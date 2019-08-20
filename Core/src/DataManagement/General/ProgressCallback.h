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

//#include <GenericProgressCallback.h>
#include <QObject>

namespace OpenInfraPlatform {
namespace Core {
	namespace DataManagement {
		class ProgressCallback : public QObject,  public CCLib::GenericProgressCallback
		{
		Q_OBJECT;
		public:
			ProgressCallback(): CCLib::GenericProgressCallback(), QObject() {}

		virtual void update(float percent) override
		{
			Q_EMIT updateSignal(percent);
		}
	
		virtual void setMethodTitle(const char* methodTitle)
		{
			Q_EMIT setMethodTitleSignal(QString(methodTitle));
		}
		
		virtual void setInfo(const char* infoStr)
		{
		}
	
		virtual void start()
		{
			Q_EMIT setMethodTitleSignal(QString("Processing..."));
			Q_EMIT activitySignal(true);
			Q_EMIT updateSignal(0);
		}
	
		virtual void stop()
		{
			Q_EMIT setMethodTitleSignal(QString("Done"));
			Q_EMIT updateSignal(100);
			Q_EMIT activitySignal(false);
	
		}	
		virtual bool isCancelRequested()
		{
			return false;
		}

	Q_SIGNALS:
		void updateSignal(float percent);
		void activitySignal(bool isActive);
		void setMethodTitleSignal(QString title);
		};
	}
}
}

#endif





