AM_CXXFLAGS=`sdl2-config --cflags` $(BULLET_CFLAGS) -std=c++11
bin_PROGRAMS=bricks
bricks_SOURCES=main.cpp World.cpp ObjMesh.cpp \
	EventLoop.cpp ShaderBase.cpp Shader2.cpp \
	BoxMesh.cpp Camera.cpp ViewPort.cpp BodyFactory.cpp RenderBody.cpp Mesh.cpp RenderObject.cpp \
	Axis.cpp Slab.cpp Maze.cpp

bricks_LDFLAGS=$(SDL_LDFLAGS) $(MAGICK_LDFLAGS) $(GL_LDFLAGS)
bricks_LDADD=$(SDL_LDFLAGS) $(MAGICK_LDFLAGS) $(GL_LDFLAGS) $(BULLET_LDFLAGS)