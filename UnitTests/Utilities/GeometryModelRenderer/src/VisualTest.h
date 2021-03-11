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

#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <namespace.h>

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

#include <boost/dll/runtime_symbol_info.hpp>

using namespace testing;


/*! \brief The visual test class
*
* This class is used for implementing basic functionality for creating visual tests with the help of the gtest library.
* Child classes implement format specific functionality.
*/
class VisualTest : public Test
{
protected:
    buw::ReferenceCounted<buw::IRenderSystem> renderSystem_ = nullptr;

	//! constructor
    VisualTest();

	//! destructor
    virtual ~VisualTest();

public:
	/*! 
	 * \brief Captures an image of the rendered object.
	 */
	virtual buw::Image4b CaptureImage() = 0;

	/*!
	 * \brief Returns the executable path.
	 */
	boost::filesystem::path executablePath() const;

	/*!
	 * \brief Returns the file path.
	 */
	virtual boost::filesystem::path filePath(const std::string& relPath) const = 0;

	/*!
	 * \brief Returns path where the test file and reference images are stored.
	 */
	boost::filesystem::path dataPath(const std::string& relPath) const;

	/*!
	 * \brief Returns path where test specific data is stored.
	 */
	boost::filesystem::path testPath(const std::string& relPath) const;
};
