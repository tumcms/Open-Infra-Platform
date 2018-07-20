#
#  Copyright (c) 2018 Technical University of Munich
#  Chair of Computational Modeling and Simulation.
#
#  TUM Open Infra Platform is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License Version 3
#  as published by the Free Software Foundation.
#
#  TUM Open Infra Platform is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>.
#

import uuid
import string
import sys
import argparse
import os
import io
import filecmp 

from optparse import OptionParser
from os import listdir
from os.path import isfile, join

textHeader = """/*
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

#include <memory>
#include <typeinfo>
#include <OpenInfraPlatform\IfcAlignment1x1\IfcAlignment1x1Entities.h>
#include <OpenInfraPlatform\IfcAlignment1x1\IfcAlignment1x1Types.h>

namespace OpenInfraPlatform {
	namespace IfcAlignment1x1 {"""


headerCastToDerivedAndCall = """
		template <typename F, typename T> T castToDerivedAndCall(std::shared_ptr<IfcAlignment1x1Entity> ptr, F &f) {
			std::string name = std::string(typeid(*ptr).name());"""
			
headerCastToVisitableAndCall = """
		template <typename F, typename T> T castToVisitableAndCall(std::shared_ptr<IfcAlignment1x1Entity> ptr, F &f) {
			std::string name = std::string(typeid(*ptr).name());"""

pattern = """
			if (name == "class OpenInfraPlatform::IfcAlignment1x1::__classname__") {
				return f(*(std::dynamic_pointer_cast<__classname__>(ptr)));				
			}"""

endFunction = """
			}"""

endFile = """		
	}
}
"""
def main(argv):
	parser = argparse.ArgumentParser()
	parser.add_argument("directory")

	args = parser.parse_args()
	
	
	onlyfiles = [f for f in listdir(args.directory) if isfile(join(args.directory, f))]
	notAbstractClass = [f for f in listdir(args.directory) if not "// abstract class" in open(join(args.directory, f)).read()]
	visitableClass = [f for f in listdir(args.directory) if "VISITABLE_STRUCT" in open(join(args.directory, f)).read()]
	print(textHeader)	
	print(headerCastToDerivedAndCall)
	
	for elem in notAbstractClass:
		classname = elem[0:len(elem) - 2]			
		text = pattern
		text = text.replace("__classname__",classname)
		print(text)
	
	print(endFunction)
	
	print(headerCastToVisitableAndCall)

	for elem in visitableClass:
		classname = elem[0:len(elem) - 2]			
		text = pattern
		text = text.replace("__classname__",classname)
		print(text)
	
	print(endFunction)
	print(endFile)
		
if __name__ == "__main__":
   main(sys.argv[1:])
	
