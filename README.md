# CS-63500 Engine
Boilerplate code for projects that require you to work in C++ with OpenGL.


# Notes
1. Right now MinGW seems to be only able to build 32-bit applications. Linking with the x64 version of glfw3.a causes the linker to think that the references are still undefined.
2. You have to initialize GLAD **after** calling glfwMakeContextCurrent(). An OpenGL context is what OpenGL lives in. It's the reference to OpenGL.

So I think what happens is.
GLFW creates an OpenGL context when you call glfwCreateWindow()
When you need to draw to the specific context, you call glfwMakeContextCurrent(). (i.e. it's the OpenGL object that you're calling functions to right now)

GLAD loads the function pointers to the OpenGL calls (?), but since we didn't know which OpenGL context we're referring to, GLAD fails to load.

# Projective Texture Mapping?
1. My goal is to find the orientation (position and rotation) of the camera in the room.

I need to establish a correspondence, which is what we say is where something is. The corners of a table are the establishments?

(u, v) in image
(x, y, z) in triangle?

Project(PHC, x, y, z) projects the correspondences into 2D, which gives us a u and a v.

We then compare how close the u and v are to the actual image.

where u\* and v\* are the correct answers on the image (selected by person)
we want (x, y, z) of the polygons to match (also selected by person)

Error Function = (sum of (u\* - u)(u\* - u) + (v\* - v)(v\* -v)) / num_correspondences


#### STEP 1
The user has to select the points on the image that correspond to the vertices of the polygons.

Therefore the user tells the program what the correct coordinates on the screen (in (u,v)) are.

#### STEP 2
The vertices of the polygons are already in the program (as (x, y, z)). You need to project the point (x, y, z) to the camera (world space -> camera -> 2D projection matrix). This results in a 2D coordinate (u, v).

Compare the (u, v) from the camera to the (u\* , v\* ) (the correct solutions as provided by the user).

The error function is 
Error Function = (sum of (u\* - u)(u\* - u) + (v\* - v)(v\* -v)) / num_correspondences


#### STEP 3
Keep comparing and repositioning/rotating the camera (AKA updating the camera matrix) until the error is minimized. Now that you have a minimal error, this is where the camera will project the 2D image from.

* Use downhill simplex to find the minimal error.
* Update the view matrix (which converts the world to camera space) to move/rotate the camera.
* Update the projection matrix (which converts camera to screen space) to update the camera intrinsics (field of view)

How do you deal with pan, tilt, **and** roll?

#### STEP 4
Use the math we did in class to project from the camera position to the player camera position.

In OpenGL with shaders, apparently this can be done in the fragment shader.


##### QUESTIONS
1. How do you move around between ray tracing and rasterization?
2. How do I do Step 4 with the fragment shader?


2. I need an error function


# Implementations
1. Create a window
2. Be able to load textures and meshes
3. Be able to rely on a camera
4. Be able to walk around
