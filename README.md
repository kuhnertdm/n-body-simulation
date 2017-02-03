To get opengl and glfw to work with Visual Studio. (As far as I know)
In project properties, go to C/C++ -> General -> Additional Include Directories and include opengl-wrapper\GLFW\include and opengl-wrapper\GLEW\include.
Still in properties, go to Linker -> General -> Additional Library Directories and add opengl-wrapper\GLFW\lib-vc2013 and opengl-wrapper\GLEW\lib\Release\Win32.
Finally, go to Linker -> Input -> Additional Dependencies and add (in this order) opengl32.lib, glew32.lib, glfw3dll.lib