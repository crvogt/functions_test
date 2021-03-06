from Tkinter import *
from PIL import ImageTk, Image

import os

root = Tk()

root.title("Simple Graph")

root.resizable(0,0)

path = "/home/carson/functions_test/python_gui/tkinter/ughFlann.jpg"
img = ImageTk.PhotoImage(Image.open(path))

points = []
spline = 0
tag1 = "theline"

class Draw:
	def __init__(self, master):

		def point(event):
			c.create_oval(event.x, event.y, event.x+1, event.y+1, fill="black")
			points.append(event.x)
			points.append(event.y)
			print(points)
			return points

		def canxy(event):
			print event.x, event.y

		def graph(event):
		        c.create_line(points, tags="theline")

		def toggle(event):
		        global spline
			if spline == 0:
				c.itemconfigure(tag1, smooth=1)
				print(c.itemcget(tag1, "splinesteps"))
				spline = 1
			elif spline == 1:
				c.itemconfigure(tag1, smooth=0)
				print(points)
				spline = 0
			return spline

		c = Canvas(root, bg="white", width = 640, height = 400)

		c.configure(cursor="crosshair")

		c.grid(row = 0, column = 0, columnspan = 2)

		c.bind("<Button-1>", point)

		c.bind("<Button-3>", graph)

		c.bind("<Button-2>", toggle)

class DrawSend:
	def __init__(self, master, val):
		def listCom():
			os.system("ls -l")
			newval = "echo " + str(val) + " " + str(val)
			os.system(newval)

		save = Button(
			text = "SEND", fg = "black", command=listCom)
		save.grid(row = 1, column = 0)
		
		erase = Button(
			text = "ERASE", fg = "black")
		erase.grid(row = 1, column = 1)

class Viewer:
	def __init__(self, master, img):

		panel = Label(root, image = img, width = 640, height = 400)
		panel.grid(row = 2, column = 0, columnspan = 2)

class ViewerSelect:
	def __init__(self, master):

		rayView = Radiobutton(text = "RAY VIEW")
		rayView.grid(row = 3, column = 0)

		imageView = Radiobutton(text = "IMAGE VIEW")
		imageView.grid(row = 3, column = 1)

		

val = 10456

drawApp = Draw(root)

sendSketch = DrawSend(root, val)

viewApp = Viewer(root, img)

viewAppSelect = ViewerSelect(root)



root.mainloop()
root.destroy()