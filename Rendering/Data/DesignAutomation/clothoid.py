from math import factorial, pow, pi, acos, sqrt
from euclid import Vector2, Vector3, Matrix4

##################################
# User Properties
start = Vector2(861.369007, 537.722476)
end = Vector2(930.775243, 503.483954)
length		= 77.500241
startCurvature = 1.0/500
endCurvature = 1.0/367
clockwise = False
##################################

def getClothoidConstant(): 
	clothoidConstant = 0;
		
	if startCurvature < endCurvature: # R1>R2
		clothoidConstant = sqrt(length/(endCurvature-startCurvature))
	elif startCurvature > endCurvature: # R1<R2
		clothoidConstant = sqrt(length/(startCurvature-endCurvature))
	else:
		raise(-13.0)

	return clothoidConstant
		
def sgnEven(number):
    if number%2==0:
        return 1.0 # Even Number
    else:
        return -1.0	
	
def computeX(L,A):
	x = L
	iterations = 5
	for i in range(1, iterations+1):
		sign = sgnEven(i)
		
		L_exponent = 5+(i-1)*4.0

		A_exponent = i*4.0
		factor = factorial(2.0*i) * pow(2.0, 2.0*i) * (5.0+(i-1)*4);
	
		x += sign * pow(L, L_exponent) / (factor * pow(A, A_exponent))

	return x
	
def computeY(L,A):
	y = 0
	iterations = 5
	for i in range(0, iterations):
		sign = sgnEven(i)
		
		L_exponent = 3.0+i*4.0
		A_exponent = 2.0+i*4.0
		factor = factorial(2*i+1) * pow(2.0, i*2.0) * 2.0  * (A_exponent + 1.0);
		
		y += sign * pow(L, L_exponent) / (factor * pow(A, A_exponent));
	return y
	
def minimalComponent(v):
	return min(v.x, v.y, v.z)
	
def calculateAngleBetweenVectorsHalfCircle(v1, v2):
	if v1 == Vector2(0, 0) or v2 == Vector2(0, 0):
		return 0

	a = v1.magnitude_squared()
	b = v2.magnitude_squared()
	
	if a * b == 0.0:
		return 0.0
		
	if a > 0 and b > 0:
		v3_1 = Vector3(v1.x, v1.y, 0)
		v3_2 = Vector3(v2.x, v2.y, 0)
		sign = minimalComponent(v3_1.cross(v3_2))

		if sign < 0:
			return -acos(v1.dot(v2) / sqrt(a * b))
		else:
			return acos(v1.dot(v2) / sqrt(a * b))
		
	return 0

def calculateAngleBetweenVectors(v1,v2):
	angle = calculateAngleBetweenVectorsHalfCircle(v1, v2)
	
	if angle < 0.0:
		angle += 2.0 * pi
	
	return angle;
	
#print("angle = " + str(calculateAngleBetweenVectors(Vector2(1, 0), Vector2(0, -1))))
	
def calculateGlobalRotation():
	A = getClothoidConstant()
		
	signY = 1
	if (clockwise==True and startCurvature < endCurvature) or (clockwise==False and endCurvature < startCurvature):
		signY = -1
	else:
		signY = 1
	
	# calculate length on clothoid at start- and endpoint
	smallerLength = A*A*startCurvature
	greaterLength = A*A*endCurvature
	
	# calculate clothoid end coordinates in local system
	localEndX = computeX(greaterLength, A)-computeX(smallerLength,A)
	localEndY = signY * (computeY(greaterLength, A)-computeY(smallerLength,A))
	
	#print("python: localEndX = " + str(localEndX))
	#print("python: localEndY = " + str(localEndY))
	
	# transfer coordinates in global system
	calculatedEnd = Vector2(localEndX,localEndY) + start;
	
	# calculate angle between expected StartEnd and calculated StartEnd vector
	globalRotationAngle = pi * 2.0 - calculateAngleBetweenVectors(end-start, calculatedEnd-start);

	#print("python: ergebnis = " + str(calculateAngleBetweenVectors(end-start, calculatedEnd-start)))
	#print("python: globalRotationAngle = " + str(globalRotationAngle))
	
	# rotate by 180° if endCurvature<startCurvature
	if endCurvature<startCurvature:
		globalRotationAngle -= pi	
		
	return globalRotationAngle
	
def getLength():
	return length

def lerp(a, b, t) :
	return a+(b-a)*t
	
def getPosition(lerpParameter):
	A = getClothoidConstant()
	
	signY = 1
	
	# flip clothoid vertical if clockwise or endCurvature<startCurvature
	if (clockwise and startCurvature < endCurvature) or (not clockwise and endCurvature < startCurvature):
		signY = -1
	else:
		signY = 1
		
	# calculate length on clothoid at start- and endpoint
	smallerLength=A*A*startCurvature
	greaterLength=A*A*endCurvature
	
	# calculate length on clothoid at interpolation point
	currentLength = lerp(smallerLength,greaterLength,lerpParameter);

	# calculate clothoid coordinates in local system
	localX = computeX(currentLength, A)-computeX(smallerLength,A);
	localY = signY * (computeY(currentLength, A)-computeY(smallerLength,A));

	# calculate the global rotation angle and create rotation matrix
	rotation = Matrix4()
	rotation = rotation.rotatez(calculateGlobalRotation())
	
	#print("python: " + str(calculateGlobalRotation()))
	
	# rotate point with global rotation angle
	tP_3 = rotation.transform(Vector3(localX,localY,0))
	tP = Vector2(tP_3.x, tP_3.y)
	
	# output global coordinates on clothoid intersection point
	if startCurvature < endCurvature:
		return tP + start
	elif endCurvature < startCurvature: 
		return start - tP
	else:
		raise(-66)