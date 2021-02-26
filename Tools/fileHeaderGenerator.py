#/*
#    This file is part of BlueFramework, a simple 3D engine.
#	 Copyright (c) 2016 Technical University of Munich
#	 Chair of Computational Modeling and Simulation.
#
#    BlueFramework is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License Version 3
#    as published by the Free Software Foundation.
#
#    BlueFramework is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#*/

import uuid
import string
import sys
import argparse

from optparse import OptionParser

#print 'Number of arguments:', len(sys.argv), 'arguments.'
#print 'Argument List:', str(sys.argv)

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

def main(argv):
	parser = argparse.ArgumentParser()
	parser.add_argument("moduleName")
	parser.add_argument("className")
	args = parser.parse_args()
	
	
	className = args.className
	moduleName = args.moduleName
    
	#strUuid = string.replace(str(uuid.uuid4()), "-", "_")
	strUuid = str(uuid.uuid4())
	strUuid = strUuid.replace("-","_")
	
	print(textHeader)
	
	print("#pragma once")
	print("#ifndef OpenInfraPlatform_" + moduleName + "_" + className + "_" + strUuid + "_h")
	print("#define OpenInfraPlatform_" + moduleName + "_" + className + "_" + strUuid + "_h")
	print("")
	print("#include \"OpenInfraPlatform/" + moduleName + "/namespace.h\"")
	print("")
	print("OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_BEGIN")
	
	print("class " + className + "{");
	print("public:")
	
	print(className + "() {" )
	print("}")
	
	print("virtual ~" + className + "() {" )
	print("}")	
	
	print("};")
	print("")
	
	print("OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_END")
	print("")
	
	print("#endif // end define OpenInfraPlatform_" + moduleName + "_" + className + "_" + strUuid + "_h")
	   
if __name__ == "__main__":
   main(sys.argv[1:])
