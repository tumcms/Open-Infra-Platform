import scipy.integrate as integrate
import matplotlib.pyplot as plt
import math
import numpy as np


def posX(K, L, R, l):
	return integrate.quad(lambda l_: math.cos(K(L, R, l_)), 0, l)[0]
	
def posY(K, L, R, l):
	return integrate.quad(lambda l_: math.sin(K(L, R, l_)), 0, l)[0]
		

# clothoid
# k = l / A2
# K = l^2 / (A2 * 2) 

def K_Clothoid(L, R, l):
	A2 = R * L
	return pow(l, 2) / (A2 * 2)
	
def k_Clothoid(L, R, l):
	A2 = R * L
	return l / A2

# calculated with matlab
# needed approxCurve.md
# k = l /(R*L)
# [x, y, X, Y] = approxCurve(k, 4)
def X_Clothoid(L, R, l):
	return l - l**5/(40*L**2*R**2) + l**9/(3456*L**4*R**4) - l**13/(599040*L**6*R**6)
	
def Y_Clothoid(L, R, l):
	return l**3/(6*L*R) - l**7/(336*L**3*R**3) + l**11/(42240*L**5*R**5) - l**15/(9676800*L**7*R**7)
	
# bloss 
# K = l^3 / (R * L^2) - l^4 * (2 * R * L^3) 
# k = l^2 * 3 / (R * L^2) - l^3 * 2 / (R * L^3)
def K_Bloss(L, R, l):
	return pow(l, 3) / (R * pow(L, 2)) - pow(l,4) / (2 * R * pow(L, 3))
	
def k_Bloss(L, R, l):
	return math.pow(l, 2) * 3 / (R * math.pow(L, 2)) - math.pow(l, 3) * 2 / (R * math.pow(L, 3))

# calculated with matlab
# needed approxCurve.md
# k = 3 * l^2 /(R*L^2) - 2 * l^3 /(R*L^3)
# [x, y, X, Y] = approxCurve(k, 4)
def X_Bloss(L, R, l):
	return l - l**7/(14*L**4*R**2) + l**8/(16*L**5*R**2) - l**9/(72*L**6*R**2) + l**13/(312*L**8*R**4) - l**14/(168*L**9*R**4) + l**15/(240*L**10*R**4) - l**16/(768*L**11*R**4) + l**17/(6528*L**12*R**4) - l**19/(13680*L**12*R**6) + l**20/(4800*L**13*R**6) - l**21/(4032*L**14*R**6) + l**22/(6336*L**15*R**6) - l**23/(17664*L**16*R**6) + l**24/(92160*L**17*R**6) - l**25/(1152000*L**18*R**6)
	
def Y_Bloss(L, R, l):
	return l**4/(4*L**2*R) - l**5/(10*L**3*R) - l**10/(60*L**6*R**3) + l**11/(44*L**7*R**3) - l**12/(96*L**8*R**3) + l**13/(624*L**9*R**3) + l**16/(1920*L**10*R**5) - l**17/(816*L**11*R**5) + l**18/(864*L**12*R**5) - l**19/(1824*L**13*R**5) + l**20/(7680*L**14*R**5) - l**21/(80640*L**15*R**5) - l**22/(110880*L**14*R**7) + l**23/(33120*L**15*R**7) - l**24/(23040*L**16*R**7) + l**25/(28800*L**17*R**7) - l**26/(59904*L**18*R**7) + l**27/(207360*L**19*R**7) - l**28/(1290240*L**20*R**7) + l**29/(18708480*L**21*R**7)
	
def getTransitionCurve(K, L, R, n):
	xs = []
	ys = []
	
	for i in range(0, n):
		l = i * (L / (n-1)) + 0.001
		x = posX(K, L, R, l)
		y = posY(K, L, R, l)
		
		xs.append(x)
		ys.append(y)
		
	return xs, ys
	
def calculateCurvature(xs, ys):
	a = np.array([xs, ys]).T
	
	dx = np.gradient(a[:, 0])
	dy = np.gradient(a[:, 1])
	
	ds = np.sqrt(dx * dx + dy * dy)
	
	d2x = np.gradient(dx)
	d2y = np.gradient(dy)
	
	curvature = np.abs(d2x * dy - dx * d2y) / (dx * dx + dy * dy)**1.5
	
	return curvature
	
n = 1500
R = 4.0
L = 10.0

xsC, ysC = getTransitionCurve(K_Clothoid, L, R, n)
xsB, ysB = getTransitionCurve(K_Bloss, L, R, n)

xsC2 = []
ysC2 = []

xsB2 = []
ysB2 = []

# approximation of bloss curve
for i in range(0, n):
	# somewhere in here is an error

	l = i * (L / (n-1)) + 0.001 # length of subcurve
	
	xC = X_Clothoid(L, R, l)
	yC = Y_Clothoid(L, R, l)
	
	xB = X_Bloss(L, R, l)
	yB = Y_Bloss(L, R, l)
	
	xsC2.append(xC)
	ysC2.append(yC)
	
	xsB2.append(xB)
	ysB2.append(yB)
	

if True: # plot transition curves
	plot1 = plt.plot(xsC, ysC, label="clothoid")
	plot2 = plt.plot(xsB, ysB, label="bloss")
	plot3 = plt.plot(xsC2, ysC2, label="clothoid approx")
	plot4 = plt.plot(xsB2, ysB2, label="bloss approx")
	
	for i in range(0, 10):	
		l = L * i / (9)
		angle = K_Bloss(L, R, l)
		x0 = posX(K_Bloss, L, R, l)
		y0 = posY(K_Bloss, L, R, l)
		
		x1 = math.cos(angle) * 0.1 + x0
		y1 = math.sin(angle) * 0.1 + y0
		x2 = math.cos(angle) * -0.1 + x0
		y2 = math.sin(angle) * -0.1 + y0
		
		plt.plot([x2, x1], [y2, y1], color='b')
	
	plt.legend(handles=[plot1[0], plot2[0], plot3[0], plot4[0]], loc=2)
	plt.axes().set_aspect('equal', 'datalim')
	plt.show()
	
if False: # plot xs and ys clothoid separately
	plot1 = plt.plot(xsC, label="x clothoid")
	plot2 = plt.plot(xsC2, label="x clothoid approx")
	
	plot3 = plt.plot(ysC, label="y clothoid")
	plot4 = plt.plot(ysC2, label="y clothoid approx")
	
	plt.legend(handles=[plot1[0], plot2[0], plot3[0], plot4[0]], loc=2)
	plt.show()
	
if False: # plot xs and ys bloss separately
	plot1 = plt.plot(xsB, label="x bloss")
	plot2 = plt.plot(xsB2, label="x bloss approx")
	
	plot3 = plt.plot(ysB, label="y bloss")
	plot4 = plt.plot(ysB2, label="y bloss approx")
	
	plt.legend(handles=[plot1[0], plot2[0], plot3[0], plot4[0]], loc=2)
	plt.show()
	
if False: # plot clothoid curvature
	cC = calculateCurvature(xsC, ysC)
	cC2 = calculateCurvature(xsC2, ysC2)
	
	cC3 = [k_Clothoid(L, R, i * (L/(n-1)) + 0.001) for i in range(0, n)]

	plot1 = plt.plot(cC, label="k")
	plot2 = plt.plot(cC2, label="k approx")
	plot3 = plt.plot(cC3, label="k control")
	
	plt.legend(handles=[plot1[0], plot2[0], plot3[0]], loc=2)
	plt.show()

if False: # plot bloss curvature
	cB = calculateCurvature(xsB, ysB)
	cB2 = calculateCurvature(xsB2, ysB2)
	
	cB3 = [k_Bloss(L, R, i * (L/(n-1)) + 0.001) for i in range(0, n)]

	plot1 = plt.plot(cB, label="k")
	plot2 = plt.plot(cB2, label="k approx")
	plot3 = plt.plot(cB3, label="k control")
	
	plt.legend(handles=[plot1[0], plot2[0], plot3[0]], loc=2)
	plt.show()


