import math
import getopt
import os.path
from tkinter import *
from Infrastructure import *
	
def drawAlignmentModel(alignmentModel, canvas):
	
	if len(alignmentModel.getAlignments())== 0:
		return
	
	width = float(canvas["width"])
	height = float(canvas["height"])
	
	ext = alignmentModel.getExtends()
	Min = ext.getMinimum()
	Max = ext.getMaximum()
	
	Length = Max - Min

	Scale = vector2d()
	Scale.x = width / Length.x
	Scale.y = height / Length.y

	Scale = min(Scale.x, Scale.y)
	Border = 0.05
	
	def scaleX(x):
		x = (x - Min.x) * Scale
		x = x * (1-2*Border) + width * Border
		return x
		
	def scaleY(y):
		y = (Max.y - y) * Scale
		y = y * (1-2*Border) + height * Border
		return y
	
	def drawLine(start, end, color):
		canvas.create_line(scaleX(start.x), scaleY(start.y), scaleX(end.x), scaleY(end.y), fill=color)
	
	def drawAlignment3D(alignment):	
		last = None
		step = alignment.getLength() / 200
		s = alignment.getStartStation()
		while(s < alignment.getEndStation()):
			p = alignment.getPosition(s)
			if last != None:
				drawLine(last, p, "blue")
			last = p
			s += step
		drawLine(last, alignment.getPosition(alignment.getEndStation()), "blue")	
		
	
	def drawAlignmentElementLine(element):
		drawLine(element.getStartPosition(), element.getEndPosition(), "green")
		
	def drawAlignmentElementArc(element):
		l = 0
		last = None
		while(l < 1):
			p = element.getPosition(l)
			if last != None:
				drawLine(last, p, "red")
			last = p
			l += 0.02
		drawLine(last, element.getPosition(1), "red")
		
		
	def drawAlignmentElementClothoid(element):
		l = 0
		last = None
		while(l < 1):
			p = element.getPosition(l)
			if last != None:
				drawLine(last, p, "orange")
			last = p
			l += 0.02
		drawLine(last, element.getPosition(1), "orange")
	
	def drawAlignment2D(alignment):
		if not alignment.hasHorizontalAlignment():
			return;
		halignment = alignment.getHorizontalAlignment()
		for i in range(0, halignment.getAlignmentElementCount()):
			element = halignment.getAlignmentElementByIndex(i)
			if element.getAlignmentType() == eHorizontalAlignmentType.Line:
				drawAlignmentElementLine(element)
			elif element.getAlignmentType() == eHorizontalAlignmentType.Arc:
				drawAlignmentElementArc(element)
			elif element.getAlignmentType() == eHorizontalAlignmentType.Clothoid:
				drawAlignmentElementClothoid(element)
	
	for alignment in alignmentModel.getAlignments():
		if alignment.getType() == e3DAlignmentType.e3DBased:
			drawAlignment3D(alignment)
		elif alignment.getType() == e3DAlignmentType.e2DBased:
			drawAlignment2D(alignment)
			
			

def main(argv):
	opts, args = getopt.getopt(argv,"f:w:h:", ["file=", "width=", "height="])
	
	width = 1000
	height = 1000
	filename = "testdata/LandXML/Mainbruecke_Klingenberg.xml"
	
	for o, a in opts:
		if o in ("-w", "--width"):
			width = float(a)
		elif o in ("-h", "--height"):
			height = float(a)
		elif o in ("-f", "--file"):
			filename = a	
	
	if not os.path.isfile(filename): 
		print("file not found: " + filename)
		return
	
	master = Tk()
	canvas = Canvas(master, width=width, height=height)
	canvas.pack()
	
	alignmentModel = simplifiedImport(filename)
	
	drawAlignmentModel(alignmentModel, canvas)
	mainloop()

if __name__ == "__main__":
   main(sys.argv[1:])
