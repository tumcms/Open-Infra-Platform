#
#    Copyright (c) 2018 Technical University of Munich
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

# Once done this will define
#
#  TCLAP_FOUND
#  TCLAP_INCLUDE_DIR

find_path(TCLAP_DIR NAMES include/tclap/Arg.h aclocal.m4 HINTS "C:/thirdparty/tclap-1.2.2" REQUIRED)

if(TCLAP_DIR)
	find_path(TCLAP_INCLUDE_DIR NAMES tclap/Arg.h Makefile.am PATHS ${TCLAP_DIR}/include REQUIRED)	
endif()

if(TCLAP_INCLUDE_DIR)
	set(TCLAP_FOUND 1)
endif()