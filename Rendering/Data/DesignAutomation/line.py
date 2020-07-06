from math import factorial, pow, pi, acos, sqrt
from euclid import Vector2, Vector3, Matrix4

##################################
# User Properties
start = Vector2(861.369007, 537.722476)
end = Vector2(930.775243, 503.483954)
length		= 77.500241
radiusStart	= 500
radiusEnd	= 367
clockwise = False
##################################

def getLength():
	return (start - end).length()

def lerp(_a, _b, _t):
  return _a+(_b-_a)*_t
	
def getPosition(lerpParameter):
	dir = end-start
	dir.normalize()
	tmp =   Vector2(lerpParameter * dir.x,
					lerpParameter * dir.y)
	return tmp + start