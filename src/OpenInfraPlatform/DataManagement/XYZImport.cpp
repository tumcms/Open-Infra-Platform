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

#include "OpenInfraPlatform/DataManagement/XYZImport.h"

#include <iostream>
//#include "buw.BlueEngine.h"
//#include <BlueFramework/Engine/Lexer/SimpleLexer.h>

OpenInfraPlatform::DataManagement::XYZImport::XYZImport(const std::string& filename, const buw::Vector2d& start, const buw::Vector2d& end) :
	buw::Import(filename)
{
	// read the data
	double x, y, z;
	std::vector<buw::Vector3d> positions;
	/*
	buw::SimpleLexer sl(filename.c_str());

	if (!filename.empty())
	{
		sl.SetIgnoreWhitespace(true);
		buw::Token token;

		// read token
		bool eof = false;
		while (sl.ReadToken(token))
		{
			while (token.GetType() == buw::eTokenType::New_Line)
			{
				if (!sl.ReadToken(token))
				{
					eof = true;
					break;
				}
			}

			if (eof)
			{
				break;
			}

			BLUE_ASSERT(token.GetType() == buw::eTokenType::Float ||
				token.GetType() == buw::eTokenType::Integer,
				"Invalid token");
			x = token.GetDoubleValue();

			sl.ReadToken(token);
			BLUE_ASSERT(token.GetType() == buw::eTokenType::Float ||
				token.GetType() == buw::eTokenType::Integer,
				"Invalid token");
			y = token.GetDoubleValue();

			sl.ReadToken(token);
			BLUE_ASSERT(token.GetType() == buw::eTokenType::Float ||
				token.GetType() == buw::eTokenType::Integer,
				"Invalid token");
			z = token.GetDoubleValue();

			buw::Vector3d tempv(x, y, z);
			if (tempv.x() < start.x() || tempv.y() < start.y() ||
				tempv.x() > end.x() || tempv.y() > end.y())
				continue;

			positions.push_back(tempv);
		}

		buw::ReferenceCounted<buw::Surface> surface = buw::createSurfaceFromXYZPoints(positions);
		digitalElevationModel_->addSurface(surface);
	}
	*/
}