# 3DViewer V1.0

Program to view 3D wireframe models (3D Viewer) written in the C programming language. The models themselves loads from .obj files and be viewable on the screen with the ability to rotate, scale and translate.

It correctly processes and allows user to view models with details up to 100, 1000, 10,000, 100,000, 1,000,000 vertices without freezing.

## .obj file format for representing the definition of 3D objects

.obj file is a geometry definition file format first developed by Wavefront Technologies. The file format is open and accepted by many 3D graphics application vendors.
The .obj file format is a simple data format that represents only three-dimensional geometry, specifically the position of each vertex, the UV of each texture coordinate vertex, vertex normals and the faces that define each polygon as a list of vertices and texture vertices. Obj coordinates have no units, but Obj files can contain scale information in a readable comment line.
The example of .obj file format:

```
  # List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.0.
  v 0.123 0.234 0.345 1.0
  v ...
  ...
  # Texture coordinates (u, [,v ,w]), w is optional and default to 0.
  vt 0.500 -1.352 [0.234]
  vt ...
  ...
  # Normals (x,y,z)
  vn 0.707 0.000 0.707
  vn ...
  ...
  # Parameter space vertices (u [,v] [,w])
  vn 0.707 0.000 0.707
  vn ...
  ...
  # Polygonal face element
  f v1 v2 v3
  f ...
  ...
  # Group
  g Group1
  ...
  # Object
  o Object1
```

## Feautres

- developed in C11 Standard using gcc compiler.
- GUI via Qt framework.
- source code follows the Google style.
- full coverage of modules related to model loading and affine transformations with unit-tests.
- program displays only one model on the screen at a time.
- loads a wireframe model from an obj file (vertices and surfaces list support only).
- model translation by a given distance in relation to the X, Y, Z axes.
- model rotation the model by a given angle relative to its X, Y, Z axes.
- model scaling by a given value.
- program allows to select the type of projection (parallel and central).
- program allows setting up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices.
- program allows choosing the background color
- program allows saving the captured (rendered) images as .bmp and .jpg files.
- program allows recording small screencasts by a special button - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s)

The graphical user interface contains:

- a button to select the model file and a field to output its name.
- a visualisation area for the wireframe model.
- sliders and input fields for translating the model.
- sliders and input fields for rotating the model.
- sliders and input fields for scaling the model.
- information about the uploaded model - file name, number of vertices and edges.
