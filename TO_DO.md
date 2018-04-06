# Engine To Do List
This is an engine intended for use for CS-63500 at Purdue University.

### Finished
1. Added GLFW and GLAD
2. Added a Makefile
3. Be able to create windows.
4. Defined the DEBUG macro in the Makefile for the dev recipe. If you have anything that should only be called during dev (i.e. not in production), put 
```
#ifdef DEBUG
// your code here
#endif
```
5. Created a shader class that abstracts away the process of compiling and linking the shaders
6. Refamiliarized myself with VBOs, VAOs, and EBOs.

## SETTING UP
2. Be able to load in image files **and** make it easy to look at pixel values in a 2D array.
3. Implement the camera class and the associated matrices.

use case for logger is different than I thought, should update it.
I actually just create a bunch of Logger instances and log them to different files, even though I want them to log to the same one without overwriting each other?

NEXT WEEK:
1. Create Visual Studio Project Files
2. Be able to drop in a camera and set that as the main camera
3. Put in default implementations for walking around in the scene and panning around

NEXT NEXT WEEK:
1. Be able to load meshes

## ACTUAL IMPLEMENTATION
1. Add a mouse click callback function for the user to define correspondences. Be able to draw points to indicate that a correspondence has been drawn.
2. Store the correspondences in a std::vector.
3. You should have the polygons in the program already, now you just need to spam the projection, so...
4. Project to the screen (but how do I extract the value of which screen we're at? Can I go into the shader and do transform feedback?)
5. Once you get the set of (u, v) coordinates, calculate the error.
6. Implement downhill simplex ;-;
7. Run until error is minimized.

8. Once it's minimized, implement the math from in class to project the image to the camera (how???)

For each pixel in image
    run math and feed into fragment shader????

### To Do
1. Set up OpenGL so that it can render meshes.

3. Create Visual Studio project files
5. Be able to drop in a camera, and set it as the main camera.
6. Implement default implementations for mouse panning and translation.
7. Be able to load in image files.
8. Be able to load in OBJ files.
9. Good looking basic UI. Buttons
10. Default load functions (i.e. "LoadAllImages")


### LATER
1. Make it so that the Makefile parses for \*.cpp and \*.c files
2. Auto-detect available versions. Figure out how that works


### Load Class
```
LoadAll("png", "my image directory");
LoadAllTextures("my image directory");
LoadAllModels("");
```
