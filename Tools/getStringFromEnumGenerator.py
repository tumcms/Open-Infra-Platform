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
#from string import maketrans

rmspace = str.maketrans("","",'\s')
rmtab = str.maketrans("","",'\t')
rmnewline =str.maketrans("","",'\n')
rmcomma = str.maketrans("","",',')
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
"""
header = """static std::string getStringFromEnum(std::string name, int value) {"""

pattern = """
	if(name == \"__name__\" && value == __value__)
		return \"__str_value__\";"""

ending = """
	return "";
}"""

def main(argv):

	parser = argparse.ArgumentParser()
	parser.add_argument("directory")

	args = parser.parse_args()
	
	onlyfiles = [f for f in listdir(args.directory) if isfile(join(args.directory, f))]
			
	print(textHeader)	
	print(header)
		
	for file in onlyfiles:
		in_file = open(join(args.directory,file), "r")
		line_number = 0
		first = 0
		name = str(0)
		value = 0
		str_value = str(0)
		
		for line in in_file:
			if name == str(0):
				tokens = line.translate(rmtab).split(" ")
				if tokens[0] == "enum":
					name = tokens[1].translate(rmnewline)
			else:
				line_filtered = line.translate(rmtab)
				line_filtered = line_filtered.translate(rmcomma)
				line_filtered = line_filtered.translate(rmnewline)
				line_filtered = line_filtered.strip()
				if line_filtered.split("_")[0] == "ENUM":
					str_value = line_filtered[5:]
					if first == 0:
						first = line_number
					value = line_number - first
					text = pattern
					text = text.replace("__name__", name)
					text = text.replace("__str_value__", str_value)
					text = text.replace("__value__", str(value))
					print(text)
			
			line_number = line_number + 1
			
		in_file.close()
	print(ending)
		
if __name__ == "__main__":
   main(sys.argv[1:])
