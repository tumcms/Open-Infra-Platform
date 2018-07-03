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

def main(argv):
	parser = argparse.ArgumentParser()
	parser.add_argument("directory")

	args = parser.parse_args()
	
	onlyfiles = [f for f in listdir(args.directory) if isfile(join(args.directory, f))]
			
	dir_path = os.path.dirname(os.path.realpath(__file__))
	
	emtBasicFile = open("EMTBasicIfc4x1EntityTypes.h", "w")
	print(textHeader, file=emtBasicFile)
	print("#pragma once", file=emtBasicFile)
	print("", file=emtBasicFile)
	print("namespace emt", file=emtBasicFile)
	print("{", file=emtBasicFile)
	print("\ttemplate <", file=emtBasicFile)

	classnames = ["\t\ttypename " + file[0:len(file) - 2] + "T" for file in onlyfiles]
	print(*classnames,sep=",\n",file=emtBasicFile)
	print("\t>", file=emtBasicFile)
	print("\tstruct BasicIfc4x1EntityTypes", file=emtBasicFile)
	print("\t{", file=emtBasicFile)
	classnames = ["\t\ttypedef " + file[0:len(file) - 2] + "T " + file[0:len(file) - 2] + ";" for file in onlyfiles]
	print(*classnames,sep="\n",file=emtBasicFile)
	print("\t};",file=emtBasicFile)
	print("}",file=emtBasicFile)
	emtBasicFile.close()
	
	emtFile = open("EMTIfc4x1EntityTypes.h", "w")
	print(textHeader, file=emtFile)
	print("#pragma once", file=emtFile)
	print("", file=emtFile)
	print("#include \"EMTBasicIfc4x1EntityTypes.h\"", file=emtFile)
	print("", file=emtFile)
	print("namespace OpenInfraPlatform", file=emtFile)
	print("{", file=emtFile)
	print("\tnamespace IfcAlignment1x1", file=emtFile)
	print("\t{", file=emtFile)

	classnames = ["\t\tclass " + file[0:len(file) - 2] + ";" for file in onlyfiles]
	print(*classnames,sep="\n",file=emtFile)
	print("\t}",file=emtFile)
	print("}",file=emtFile)
	
	print("namespace emt", file=emtFile)
	print("{", file=emtFile)
	print("\ttypedef BasicIfc4x1EntityTypes<", file=emtFile)
	classnames = ["\t\tOpenInfraPlatform::IfcAlignment1x1::" + file[0:len(file) - 2] for file in onlyfiles]
	print(*classnames,sep=",\n",file=emtFile)
	print("\t>",file=emtFile)
	print("\tIfc4x1EntityTypes;",file=emtFile)
	print("}",file=emtFile)
	emtFile.close()	
		
if __name__ == "__main__":
   main(sys.argv[1:])