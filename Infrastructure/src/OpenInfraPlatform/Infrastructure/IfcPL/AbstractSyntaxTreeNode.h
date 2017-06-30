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
#ifndef OpenInfraPlatform_Infrastructure_AbstractSyntaxTreeNode_17d40bab_f014_4c25_8fd3_6c18acd80a15_h
#define OpenInfraPlatform_Infrastructure_AbstractSyntaxTreeNode_17d40bab_f014_4c25_8fd3_6c18acd80a15_h

#include "OpenInfraPlatform/Infrastructure/IfcPL/token.h"
#include "OpenInfraPlatform/Infrastructure/IfcPL/variant.h"
#include <BlueFramework/Core/memory.h>
#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct AbstractSyntaxTreeNode
		{
			static buw::ReferenceCounted<AbstractSyntaxTreeNode> create(const token& t)
			{
				return std::make_shared<AbstractSyntaxTreeNode>(t);
			}

			AbstractSyntaxTreeNode(
				const token& t)
			{
				this->token_ = t;
				this->left = nullptr;
				this->right = nullptr;
				isUnary = false;
			}

			AbstractSyntaxTreeNode(
				const token& t,
				buw::ReferenceCounted<AbstractSyntaxTreeNode> left,
				buw::ReferenceCounted<AbstractSyntaxTreeNode> right)
			{
				this->token_ = t;
				this->left = left;
				this->right = right;
				isUnary = false;
			}

			eTokenType::Enum getTokenType() const
			{
				return token_.type;
			}

			//eTokenType::Enum			type;
			buw::ReferenceCounted<AbstractSyntaxTreeNode> left;
			buw::ReferenceCounted<AbstractSyntaxTreeNode> right;
			bool						isUnary;

			// needed by interpreter
			VariantType					value;
			token						token_;
		};
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::AbstractSyntaxTreeNode;
}

#endif // end define OpenInfraPlatform_Infrastructure_AbstractSyntaxTreeNode_17d40bab_f014_4c25_8fd3_6c18acd80a15_h
