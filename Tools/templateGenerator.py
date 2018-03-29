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

def main(argv):
	print(textHeader)
	for x in range(1,803):
		x = 803 - x
		text = pattern
		text = text.replace("__n__",str(x))
		text = text.replace("__n-1__", str(x-1))
		print(text)
		
if __name__ == "__main__":
   main(sys.argv[1:])
	
