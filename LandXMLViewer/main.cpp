/*
    Copyright (c) 2016-2017 Technical University of Munich
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

#include "buw.BlueCore.h"
#include "LandXMLViewer.h"

#include "buw.OIPInfrastructure.h"

int main(int argc,char *argv[])
{
	std::ofstream logfile;
	logfile.open("log.txt");
	buw::LogManager::getInstance().addOutputStream(&logfile);

	// log file should be outputted in XML format
	buw::logMangerSettings settings;
	settings.outputAsXML = true;
	settings.colorConsoleOutput = true;
	buw::LogManager::getInstance().setSettings(settings);

	buw::LifetimeManager lm;

	if (buw::getBlueCoreRevisionVersion() != buw::VERSION_REVISION)
	{
		BLUE_LOG_STREAM_EX("main", buw::eLogSeverityLevel::Error) << "Invalid BlueCore DLL found!";
	}

	buw::renderWindowsDescription rwd;
	rwd.enableMSAA = true;
	rwd.renderSystem = buw::eRenderSystem::Direct3D11;
	rwd.majorVersion = 11;
	rwd.miniorVersion = 0;
	rwd.d3dFeatureLevel = buw::eD3D11FeatureLevel::FeatureLevel10_0;
	rwd.sampleCount = 4;
	rwd.resolution = buw::getResolution(buw::eResolutionType::SVGA);
	LandXMLViewer rxv(rwd);
	rxv.run();

	return 0;
}
