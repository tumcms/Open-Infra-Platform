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

pattern = """
template <> struct unrolled_dynamic_visitor<__n__> {
	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F const& f)
	{
		const std::type_info& t0 = (typeid(*(ptr.get())));
		const std::type_info& t1 = (typeid(GET_IFCALIGNMENT1X1_ENTITY_TYPE(__n__)));
		if(t0 == t1) {
			GET_IFCALIGNMENT1X1_ENTITY_TYPE(__n__) entity = *(std::dynamic_pointer_cast<GET_IFCALIGNMENT1X1_ENTITY_TYPE(__n__)>(ptr));
			f(entity);
		}
		else {
			unrolled_dynamic_visitor<__n-1__>::castAndCall(ptr, f);
		}
	}
};
"""

declaration = """
using namespace OpenInfraPlatform::IfcAlignment1x1;
template <typename F> void castAndCall(std::shared_ptr<IfcAlignment1x1Entity> ptr, F &f) {
	switch (ptr->m_entity_enum) {"""

pattern1 = """
		case __enum__:
			f(*(std::dynamic_pointer_cast<__classname__>(ptr)));
			break;"""

ending = """
		default: break;
	}
}
"""
def main(argv):

	parser = argparse.ArgumentParser()
	parser.add_argument("header")

	args = parser.parse_args()
	
	in_file = open(args.header,"r")	
	line_number = 0
	print(textHeader)
	
	print(declaration)

	for line in in_file:
		if line.split(" ")[0] == "#include":
			first, second = line.split(".h")
			classname = first.split("/")[-1]
			
			text = pattern1
			text = text.replace("__classname__",classname)
			text = text.replace("__enum__", classname.upper())
			print(text)
	
	print(ending)
	in_file.close()
	
		
if __name__ == "__main__":
   main(sys.argv[1:])
	
