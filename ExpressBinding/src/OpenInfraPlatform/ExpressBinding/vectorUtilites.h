/*! \verbatim
 *  \copyright      Copyright (c) 2017 Technische Universität München
 *                  Chair of Computational Modeling and Simulation. All rights reserved.
 *  \author         Julian Amann <julian.amann@tum.de> (https://www.cms.bgu.tum.de/en/team/amann)
 *  \brief          This file is part of the TUM Open Infra Platform.
 *  \endverbatim
 */

#pragma once
#ifndef OpenInfraPlatform_ExpressBinding_vectorUtilites_d0d23db7_31cc_4ff4_9fe7_7cfd8859b74e_h
#define OpenInfraPlatform_ExpressBinding_vectorUtilites_d0d23db7_31cc_4ff4_9fe7_7cfd8859b74e_h

#include <vector>
#include <memory>

namespace OpenInfraPlatform
{
	namespace ExpressBinding
	{
		//! Finds the first occurrence of T in vector
		template<class T, class U>
		bool findFirstInVector(std::vector<std::shared_ptr<U> > vec, std::shared_ptr<T>& ptr)
		{
			typename std::vector<std::shared_ptr<U> >::iterator it_trim = vec.begin();
			for (; it_trim != vec.end(); ++it_trim)
			{
				std::shared_ptr<U> item = *(it_trim);
				if (std::dynamic_pointer_cast<T>(item))
				{
					ptr = std::dynamic_pointer_cast<T>(item);
					return true;
				}
			}
			return false;
		}
	} // end namespace ExpressBinding
} // end namespace OpenInfraPlatform

namespace buw
{

}

#endif // end define OpenInfraPlatform_ExpressBinding_vectorUtilites_d0d23db7_31cc_4ff4_9fe7_7cfd8859b74e_h