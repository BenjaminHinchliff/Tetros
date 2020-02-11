# Tetros

## What Even Is This?

Well, it's a relatively primitive version of Tetris built with only GLFW, GLAD, GLM, and stb_image.h. It doesn't have a score. Because text in OpenGL is a pain and I didn't feel like doing it. I might add it at some point in the future.

It's basically just an experiment to see if I could actually do something like this with only low level graphics frameworks.

Most of the work was writing classes to encapsulate parts of the OpenGL code.

## Is It Impressive?

I think so. This was one of my larger projects just because of the amount of testing and messing to get OpenGL to behave

## So, How Do I Actually Get The Program Running

Use CMake and use a standard compilation process. Nothing weird should be happening. It does require CMake to be able to find:
* GLFW3^3.3.1
* GLAD^0.1.33
* GLM^0.9.9.7
* stb_image.h^2019-08-17

I would install them via vcpkg. The exact versions are just the ones I compiled with. Newer ones should work so long as there aren't any major breaking changes. I'm thinking of adding the libs inside the project, but I just want to get this up right now.

Just make sure the program can find its resources (in the same dir).

## Controls

left and right to move the block, up to rotate, space to drop. Everything else should be intuitive.
