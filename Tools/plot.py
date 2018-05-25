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
	chainages, curvatures, bearings = np.loadtxt(args.file, delimiter='\t',unpack=True)
	
	N = np.size(chainages)
	# sample spacing
	T = (chainages[N-1] - chainages[0])
	Ts = T / N
	Fs = 1 / Ts
	f, axarr = ply.subplots(3)
	xf = np.linspace(-Fs/2,Fs/2,N)
	yf = np.abs(np.fft.fftshift(np.fft.fft(curvatures)))
	axarr[0].plot(chainages, curvatures)
	axarr[1].plot(chainages, bearings)
	axarr[2].plot(xf, yf)
	#axarr[0][1].plot(indices, dStationing)
	#axarr[1][1].plot(indices, distances)
	ply.suptitle(args.file)
	
	#ply.plotfile(args.file, delimiter='\t', cols=(0, 2), names=('index','curvature','bearing'))
	#ply.plotfile(args.file, delimiter='\t', cols=(0, 1), names=('index','curvature','bearing'))
	ply.show()
		
	
		
if __name__ == "__main__":
   main(sys.argv[1:])