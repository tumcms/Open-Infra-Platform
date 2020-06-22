#
#    Copyright (c) 2020 Technical University of Munich
#    Chair of Computational Modeling and Simulation.
#
#    TUM Open Infra Platform is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License Version 3
#    as published by the Free Software Foundation.
#
#    TUM Open Infra Platform is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#

include(CreateUnitTests)

# get all subdirectories (that is, unit tests)
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

# add to the solution
FOREACH(subdir ${SUBDIRS})
  # only if the schema has been included in the project and built already
  if(EXISTS ${CMAKE_BINARY_DIR}/EarlyBinding/${subdir})
    ADD_SUBDIRECTORY(${subdir})
  endif()
ENDFOREACH()
