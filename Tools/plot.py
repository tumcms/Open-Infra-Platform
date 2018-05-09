import os
import re
import sys
import argparse
from optparse import OptionParser
import io
from matplotlib import pyplot as ply
import numpy as np

def main(argv):
	parser = argparse.ArgumentParser()
	parser.add_argument("file")

	args = parser.parse_args()
	indices, curvatures, bearings = np.loadtxt(args.file, delimiter='\t',unpack=True)
	
	f, axarr = ply.subplots(2, sharex=True)
	axarr[0].plot(indices, curvatures)
	axarr[1].plot(indices, bearings)
	ply.suptitle(args.file)
	
	#ply.plotfile(args.file, delimiter='\t', cols=(0, 2), names=('index','curvature','bearing'))
	#ply.plotfile(args.file, delimiter='\t', cols=(0, 1), names=('index','curvature','bearing'))
	ply.show()
		
	
		
if __name__ == "__main__":
   main(sys.argv[1:])