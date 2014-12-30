AM_CXXFLAGS=`sdl2-config --cflags` $(BULLET_CFLAGS) -std=c++11
bin_PROGRAMS=bricks
bricks_SOURCES=main.cpp World.cpp Ground.cpp Body.cpp EventLoop.cpp GroundGL.cpp Renderer.cpp

bricks_LDFLAGS=$(SDL_LDFLAGS) $(MAGICK_LDFLAGS) $(GL_LDFLAGS)
bricks_LDADD=$(SDL_LDFLAGS) $(MAGICK_LDFLAGS) $(GL_LDFLAGS) $(BULLET_LDFLAGS)