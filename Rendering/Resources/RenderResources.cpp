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

#include "RenderResources.h"

#include <QCoreApplication>
#include <boost/algorithm/string.hpp>
#include <fstream>

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

RenderResources::RenderResources() {

}

void RenderResources::init(buw::ReferenceCounted<buw::IRenderSystem> renderSystem) {
    buw::samplerStateDescription ssd = { buw::eFilter::Linear };
    linearSampler_ = renderSystem->createSampler(ssd);
}

void RenderResources::release() {
    linearSampler_ = nullptr;
}

std::string RenderResources::getResourceRootDir() {
    static bool firstCall = true;
    if (firstCall) {
        firstCall = false;

        // find executable
        resourceRootDir_ = QCoreApplication::applicationDirPath().toStdString();

        bool runingStandalone = true;

        // find out if we run in Debug/Release/RelWithDebInfo mode
        if (boost::algorithm::ends_with(resourceRootDir_, "/Debug")) {
            boost::algorithm::replace_all(resourceRootDir_, "/Debug", "");

            runingStandalone = false;
        }

        if (boost::algorithm::ends_with(resourceRootDir_, "/Release")) {
            boost::algorithm::replace_all(resourceRootDir_, "/Release", "");

            runingStandalone = false;
        }

        if (boost::algorithm::ends_with(resourceRootDir_, "/RelWithDebInfo")) {
            boost::algorithm::replace_all(resourceRootDir_, "/RelWithDebInfo", "");

            runingStandalone = false;
        }

        if (!runingStandalone) {
            // try to read CMakeCache.txt file
            std::ifstream input(resourceRootDir_ + "/CMakeCache.txt");
            for (std::string line; std::getline(input, line); ) {
                if (boost::algorithm::contains(line, "OpenInfraPlatform_SOURCE_DIR:STATIC=")) {
                    boost::algorithm::replace_all(line, "OpenInfraPlatform_SOURCE_DIR:STATIC=", "");
                    resourceRootDir_ = line;
                    break;
                }
            }

            //resourceRootDir_ += "/src/OpenInfraPlatform";
            resourceRootDir_ += "/UserInterface";
        }
    }

    return resourceRootDir_;
}

buw::ReferenceCounted<buw::ISampler> RenderResources::getLinearSampler() const {
    return linearSampler_;
}


OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END