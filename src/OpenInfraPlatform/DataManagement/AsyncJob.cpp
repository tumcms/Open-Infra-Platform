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

#include "AsyncJob.h"

OpenInfraPlatform::AsyncJob& OpenInfraPlatform::AsyncJob::getInstance()
{
	static AsyncJob job;
	return job;
}

bool OpenInfraPlatform::AsyncJob::updateStatus(float progress, const std::string& message)
{
	if (std::this_thread::get_id() != thread_.get_id())
		return true;

	statusMutex_.lock();
	status_.progress_ = progress;
	status_.message_ = message;
	statusMutex_.unlock();

	return !cancel_;
}

void OpenInfraPlatform::AsyncJob::cancelJob()
{
	if (running_)
		cancel_ = true;
}

void OpenInfraPlatform::AsyncJob::run()
{
	running_ = true;
	job_();
	running_ = false;
	Q_EMIT finished();
}

void OpenInfraPlatform::AsyncJob::checkThread()
{
	if (first_)
	{
		jobStarted(jobID_);
		first_ = false;
	}
	if (!running_)
	{
		thread_.join();
		refreshTimer_->stop();
		jobFinishing(jobID_, !cancel_);
		jobFinished(jobID_, !cancel_);
	}
	else
	{
		statusMutex_.lock();
		jobRunning(jobID_, status_.progress_, status_.message_);
		statusMutex_.unlock();
	}
}

bool OpenInfraPlatform::AsyncJob::updateStatus(const std::string& message)
{
	if (std::this_thread::get_id() != thread_.get_id())
		return true;

	statusMutex_.lock();
	status_.message_ = message;
	statusMutex_.unlock();

	return !cancel_;
}

bool OpenInfraPlatform::AsyncJob::updateStatus(float progress)
{
	if (std::this_thread::get_id() != thread_.get_id())
		return true;

	statusMutex_.lock();
	status_.progress_ = progress;
	statusMutex_.unlock();

	return !cancel_;
}
