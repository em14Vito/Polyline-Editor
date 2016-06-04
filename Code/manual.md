#Manual

##Before using <br />
* Firstly,you should install Microsoft Visual C++ .NET 2010 and setting property of new project can link to the file ‘GLUT’ in the zip file which includes ‘glut.h’, ‘glut32.dll’ and ‘glut32.lib’.<br /><br />
* Then, Add the ‘project.c’ and ‘glut32.dll’ into the project file that you create just now. 
* Finally, you should change one line in the project.c:<br /><br />
`#include "C:\Users\student\Desktop\GLUT 3.7 for .NET\glut.h"`<br /><br />
*‘C:\Users\student\Desktop\GLUT 3.7 for .NET\glut.h’ is the path of ‘glut.h’ in my disk.*<br />
*In order to use OpenGL, you should change it to the path of ‘glut.h’ in your computer.*<br />
(Perhaps you can put the file ‘glut.h’ in the over path)
<br />
<br />
<br />

## Key point for using:<br />
*	Key ‘b’: creagte a new polyline;
*	Key ‘d’: delete the next point pointed to;
*	Key ‘m’: drag the point pointed to a new location;
*	Key ‘r’: erase the screen and redraw all the polylines;
*	Key ‘i’: insert some new polylines from a point existed.
*	Key ‘r’: clean all polylines you drew before.
*	Right click: save polylines or open the polylines that you saved before.

