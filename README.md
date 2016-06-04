# Polyline-Editor
A simple program that using OpenGL and GLUT to create an interactive graphics application

## Introduction
Drawing programs often allow one to enter polylines using a mouse and then to edit the polylines until they present the desired picture. In the following figure: <br />
1. shows a house in the process of being drawn; the user has just clicked at the position shown, and a line has been drawn from the previous point to the designated by the mouse.
2. shows the effect of moving a point. The user positions the cursor near the vertex of some polyline, presses down the mouse button, and “drags” the chosen point to some other location before releasing the button. Upon release of the button, the previous lines connected to this point are erased, and new lines are drawn to it.
3. shows how a point is deleted from a ployline. The user clicks near the vertex of some polyline, and the two line segments connected to that vertex are erased. Then the two other endpoints of the segments just eased are connected with a line segment.
