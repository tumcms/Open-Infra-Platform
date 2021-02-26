#
#  Copyright (c) 2021 Technical University of Munich
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

#include <memory>
#include <typeinfo>
#include <OpenInfraPlatform\__schema__\__schema__Entities.h>
#include <OpenInfraPlatform\__schema__\__schema__Types.h>

namespace OpenInfraPlatform {
	namespace __schema__ {"""


headerCastToDerivedAndCall = """
		template <typename F, typename T> T castToDerivedAndCall(std::shared_ptr<__schema__Entity> ptr, F &f) {
			std::string name = std::string(typeid(*ptr).name());"""
			
headerCastToVisitableAndCall = """
		template <typename F, typename T> T castToVisitableAndCall(std::shared_ptr<__schema__Entity> ptr, F &f) {
			std::string name = std::string(typeid(*ptr).name());"""

pattern = """
			if (name == "class OpenInfraPlatform::__schema__::__classname__") {
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
	
	pathlist = args.directory.split("\\")
	
	if len(pathlist) == 1:
		pathlist = args.directory.split("/")
	
	schema = pathlist[len(pathlist) - 2]
	
	
	onlyfiles = [f for f in listdir(args.directory) if isfile(join(args.directory, f))]
	notAbstractClass = [f for f in listdir(args.directory) if not "// abstract class" in open(join(args.directory, f)).read()]
	visitableClass = [f for f in listdir(args.directory) if "VISITABLE_STRUCT" in open(join(args.directory, f)).read()]
	
	filename = schema + "Caster.h"
	file = open(filename, "w")
	
	print(textHeader.replace("__schema__", schema), file=file)	
	print(headerCastToDerivedAndCall.replace("__schema__", schema), file=file)
	
	for elem in notAbstractClass:
		classname = elem[0:len(elem) - 2]			
		text = pattern
		text = text.replace("__classname__",classname)
		text = text.replace("__schema__", schema)
		print(text, file=file)
	
	print(endFunction, file=file)
	
	print(headerCastToVisitableAndCall.replace("__schema__", schema), file=file)

	for elem in visitableClass:
		classname = elem[0:len(elem) - 2]			
		text = pattern
		text = text.replace("__classname__",classname)
		text = text.replace("__schema__", schema)
		print(text, file=file)
	
	print(endFunction, file=file)
	print(endFile, file=file)
	file.close()
		
if __name__ == "__main__":
   main(sys.argv[1:])
	
