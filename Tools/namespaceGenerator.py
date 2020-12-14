# Copyright (c) 2021 Technical University of Munich
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
import io

from optparse import OptionParser

#print 'Number of arguments:', len(sys.argv), 'arguments.'
#print 'Argument List:', str(sys.argv)

textHeader = u"""/*
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

    NOTE: This file has been generated with Tools/namespaceGenerator.py .
*/
"""

def writeLine(file, str):
    file.write(str + "\n")

def main(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument("moduleName")
    parser.add_argument("fileName")
    args = parser.parse_args()
        
    moduleName = args.moduleName
    fileName = args.fileName
    
    strUuid = str(uuid.uuid4())
    strUuid = strUuid.replace("-","_")
    
    with io.open(fileName, 'w', encoding='utf8') as f:
       writeLine(f, textHeader)
       writeLine(f, u"#pragma once")
       writeLine(f, u"#ifndef OpenInfraPlatform_" + moduleName + "_namespace_" + strUuid + "_h")
       writeLine(f, u"#define OpenInfraPlatform_" + moduleName + "_namespace_" + strUuid + "_h")    
       writeLine(f, u"#if !defined OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_BEGIN")
       writeLine(f, u"#define OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_BEGIN \\")
       writeLine(f, u"namespace OpenInfraPlatform { \\")
       writeLine(f, u"namespace " + moduleName + " {")
       writeLine(f, u"#endif")
       writeLine(f, u"#if !defined OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_END")
       writeLine(f, u"#define OIP_NAMESPACE_OPENINFRAPLATFORM_" + moduleName.upper() + "_END \\")
       writeLine(f, u"}\\")
       writeLine(f, u"}")
       writeLine(f, u"#endif")
       writeLine(f, u"#if !defined EMBED_" + moduleName.upper() + "_INTO_OIP_NAMESPACE")
       writeLine(f, u"#define EMBED_" + moduleName.upper() + "_INTO_OIP_NAMESPACE(X) \\")
       writeLine(f, u"namespace oip { \\")
       writeLine(f, u"using OpenInfraPlatform::" + moduleName + "::X; \\")
       writeLine(f, u"}")
       writeLine(f, u"#endif")   
       writeLine(f, u"#endif // end define OpenInfraPlatform_" + moduleName + "_namespace_" + strUuid + "_h")
       
    print("Wrote the namespace header of " + moduleName + " to " + fileName)

if __name__ == "__main__":
   main(sys.argv[1:])
