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
"""


header = """
using namespace OpenInfraPlatform::IfcAlignment1x1;
template <typename F, typename T> bool castAndCall(std::shared_ptr<T> ptr, F &f) {
	std::string name = std::string(typeid(T).name());"""

pattern = """
	if (name == "class OpenInfraPlatform::IfcAlignment1x1::__classname__") {
		f(*(std::dynamic_pointer_cast<__classname__>(ptr)));
		return true;
	}"""

ending = """		
	return false;
}
"""
def main(argv):
	parser = argparse.ArgumentParser()
	parser.add_argument("directory")

	args = parser.parse_args()
	
	onlyfiles = [f for f in listdir(args.directory) if isfile(join(args.directory, f))]
			
	print(textHeader)	
	print(header)
	
	for file in onlyfiles:
		classname = file[0:len(file) - 2]			
		text = pattern
		text = text.replace("__classname__",classname)
		print(text)
	
	print(ending)	
		
if __name__ == "__main__":
   main(sys.argv[1:])
	
