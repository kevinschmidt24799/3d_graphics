# 3d_graphics

This project is a 3d graphics engine that generates bitmaps at a pixel level. It contains an interface to write single .bmp files, as well as creating successive frames for animation. I used ffmpeg to combine these frames into videos. 

The interface allows for creating shapes, which contain subshapes, as well as a list of triangles and a transform. Makeframes() will apply the transform, draw the triangles, the recursively call makframes on subshapes with the same transform. Drawing the triangles is done by a series of linearizations which then draw horizontal lines, pixel by pixel. When this is done, a .bmp file is written out. 


<img src="DEMO%20IMAGES/Shapes%20Flowchart.svg" alt="drawing" width="500"/>


## Key Features:

### Matrix Transforms

The matrix library is a template based implementation of matrix arithmetic. We use these for graphics to create a system of affine matrix transforms using 4x4 matrices as transforms, and 4x1 matrices as points in 3d space. We must have an extra dimension that is normalized to 1 in order to represent certain transformations such as translation using a single matrix multiply. The strength of this system of transforms lies in the associative property of matrix multiplies. While the order of the multiplication matters, the sub grouping does not. This means, we can combine all our transformations beforehand into a single matrix, then apply a single transformation of this matrix onto our points. 

### Persepective

The library supports both orthogonal projection (head-on from infinite distance) and a more realistic perspective projection (closer things look bigger). The angle and distance of the viewpoint can be set, or even animated to slowly move throughout successive frames. Perspective is created using an affine matrix transform. 

### Z Depth Buffer

A Bitmap object in the code contains colors at x,y, but also maintains an invisible z buffer. This way, whenever a new pixel is to be drawn, if it is behind the existing pixel, it is ignored. 

### Face Culling

When drawing a 3d shape comprised of triangular faces, around half the faces will be on the back of the shape and completely obscured. This means that rendering them all the way down the data structure before eliminating them on the pixel level is inefficient. This library implements face culling, wherein whether a triangle is clockwise or counter-clockwise determines whether it is "facing" towards or away from the camera. Triangle faces pointing away from the camera will be obscured in polyhedra, so they are omitted from rendering. This is purely an optimization. 

### Bresenham's Algorithm

Linearization uses Bresenham's algorithm, so lines can be drawn using only additions and subtractions (no multiplies). These types of linearizations are used for both location in space, and colors. 

### Shading

The library supports a simple shading scheme in which the direction of the light source can be chosen. Colors are converted from RGB to YUV, and luminance is determined the angle that a face makes with the light source. Then, colors are converted back to RGB. 

## Demo:

<img src="DEMO%20IMAGES/test-200.bmp" alt="drawing" width="500"/>


Animation Video: https://youtu.be/_tqcd8wNkLk

Colors and Perspective 
