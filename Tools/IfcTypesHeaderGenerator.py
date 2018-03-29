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
	parser.add_argument("header")

	args = parser.parse_args()
	
	in_file = open(args.header,"r")	
	line_number = 0
	print(textHeader)

	for line in in_file:
		if line.split(" ")[0] == "#include":
			first, second = line.split(".h")
			classname = first.split("/")[-1]
			print("#define IFCALIGNMENT1X1_ENTITY_TYPE_" + str(line_number) + " " + classname)
			line_number = line_number + 1
		
	in_file.close()
	
if __name__ == "__main__":
   main(sys.argv[1:])
