# Basic Coordinate Geometry with OpenGL

The primary goal of this project is to refresh basic coordinate geometry knowledge and get acquainted with OpenGL. The program allows you to plot points with mouse clicks on a tastefully chosen gray background, fit lines to the points, move the lines, and finally create new points from the intersections of the selected lines. The point size is 10 and the line thickness is 3.

The world coordinate system coincides with the normalized device coordinate system, i.e., the resulting image corresponds to the square with corner points (-1,-1) and (1,1). The image fully covers the application window with a resolution of 600x600. In the CPU program, 2D geometry should be handled by embedding it in 3D space. This means that we assign the type vec3 to 2D points and vectors, with the choice of z = 1 for points and z = 0 for vectors. Then, in the vertex shader, we embed the 3D geometry in 4D with the choice of w = 1.

From the user's side, the program has 4 states, which can be selected in order with the keys 'p', 'l', 'm', 'i':

- 'p': Point drawing, which puts a red point at the cursor's location when the left mouse button is pressed.
- 'l': Line drawing, which requires clicking on two existing red points with the left mouse button.
- 'm': Line shift, which first requires selecting the line with the left mouse button, and if successful, the line follows the cursor, i.e., the movement of the mouse with the button pressed, until we release the mouse button.
- 'i': Intersection, which puts a new red point on the intersection (if it exists) of two selected lines.

The program writes the Cartesian coordinates of the resulting points and the implicit and parametric equations of the resulting lines to the console with printf.
