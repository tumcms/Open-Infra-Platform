# Copyright (c) 2018 Technical University of Munich
# Chair of Computational Modeling and Simulation.
# 
# TUM Open Infra Platform is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License Version 3
# as published by the Free Software Foundation.
# 
# TUM Open Infra Platform is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

import uuid
import string
import sys
import argparse

from optparse import OptionParser

#print 'Number of arguments:', len(sys.argv), 'arguments.'
#print 'Argument List:', str(sys.argv)

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
	parser.add_argument("moduleName")
	args = parser.parse_args()
		
	moduleName = args.moduleName
    
	strUuid = str(uuid.uuid4())
	strUuid = strUuid.replace("-","_")
	
	print(textHeader)	
	print("#pragma once")
	print("#ifndef OpenInfraPlatform_" + moduleName + "_namespace_" + strUuid + "_h")
	print("#define OpenInfraPlatform_" + moduleName + "_namespace_" + strUuid + "_h")    
	print("#if !defined OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_BEGIN")
	print("#define OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_BEGIN \\")
	print("namespace OpenInfraPlatform { \\")
	print("namespace " + moduleName + " {")
	print("#endif")
	print("#if !defined OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_END")
	print("#define OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_END \\")
	print("}\\")
	print("}")
	print("#endif")
	print("#if !defined EMBED_INTO_OIP_NAMESPACE")
	print("#define EMBED_INTO_OIP_NAMESPACE(X) \\")
	print("namespace oip { \\")
	print("using OpenInfraPlatform::" + moduleName + "::X; \\")
	print("}")
	print("#endif")   
	print("#endif // end define OpenInfraPlatform_" + moduleName + "_namespace_" + strUuid + "_h")
	   
if __name__ == "__main__":
   main(sys.argv[1:])