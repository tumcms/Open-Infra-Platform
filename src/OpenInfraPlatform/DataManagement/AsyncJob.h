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

#include <boost/signals2.hpp>
#include <QTimer>
#include <QObject>

#include <functional>
#include <deque>
#include <thread>
#include <mutex>

namespace OpenInfraPlatform
{
	class AsyncJob : public QObject
	{
		Q_OBJECT;

		struct AsyncStatus
		{
			AsyncStatus() :
				progress_(-1), message_("")
			{}

			AsyncStatus(float progress, const std::string& message) :
				progress_(progress), message_(message)
			{}


			float		progress_;
			std::string message_;
		};

	public:
		static AsyncJob& getInstance();

		template<typename Function, typename ... Args>
		int startJob(Function&& functionPtr, const Args& ... args)
		{
			if (running_)
				return -1;

			job_ = std::bind(functionPtr, args...);			// Caution: references will be treated as values, use std::ref() to create reference wrappers when calling startJob()
			jobID_++;
			first_ = true;
			cancel_ = running_ = false;

			status_ = AsyncStatus();

			jobStarting();
			thread_ = std::thread(&AsyncJob::run, this);
			refreshTimer_->start();

			return jobID_;
		}

		bool updateStatus(float progress, const std::string& message);

		bool updateStatus(float progress);

		bool updateStatus(const std::string& message);

		void cancelJob();

		boost::signals2::signal<void()> jobStarting;
		boost::signals2::signal<void(int jobID)> jobStarted;
		boost::signals2::signal<void(int jobID, float progress, const std::string& message)> jobRunning;
		boost::signals2::signal<void(int jobID, bool completed)> jobFinishing;
		boost::signals2::signal<void(int jobID, bool completed)> jobFinished;

		Q_SIGNAL void finished();
	
	private:
		AsyncJob()
		{
			jobID_ = 0;
			running_ = cancel_ = false;

			refreshTimer_ = new QTimer();
			refreshTimer_->setInterval(200);
			connect(refreshTimer_, SIGNAL(timeout()), this, SLOT(checkThread()));
		}

		void run();
	
	private Q_SLOTS:
		void checkThread();
		
	private:
		std::function<void()> job_;
		int jobID_;
		
		std::thread thread_;
		bool running_, cancel_, first_;

		std::mutex statusMutex_;
		AsyncStatus status_;

		QTimer*	refreshTimer_;
	};
}
