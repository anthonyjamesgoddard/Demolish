OBJS = demolish/demolish.o \
       demolish/ContactPoint.o \
       demolish/math.o \
	   demolish/Mesh.o \
	   demolish/Vertex.o \
       demolish/Object.o \
       demolish/World.o \
	   demolish/Timer.o \
	   demolish/visuals/antmath.o \
	   demolish/visuals/DEMDriver.o \
	   demolish/visuals/GeometryGenerator.o \
	   demolish/visuals/MathHelper.o \
	   demolish/visuals/GLnixAPP.o \
	   demolish/operators/mesh.o \
	   demolish/operators/physics.o \
	   demolish/operators/vertex.o \
       demolish/primitives/Sphere.o \
       demolish/primitives/Cylinder.o \
       demolish/primitives/Cube.o \
       
       
CFLAGS = -fPIC -std=c++17
LDFLAGS=-lm -lX11 -lGL -lGLU -lXext -lXrender


all:	release

release: CFLAGS+=-O3
release: LIBNAME=libdemolish.so
release: build

debug: CFLAGS+=-O0 -g3
debug: LIBNAME=libdemolish_debug.so
debug: build

test: CFLAGS+=-O0 -g3 -DDELTA_DEBUG=8
test: LIBNAME=libdemolish_debug.so
test: build
test: 
	$(CXX) -c demolish/test.cpp -o demolish/test.o
	$(CXX) $(OBJS) demolish/test.o -o  demolish-test $(LDFLAGS)


build:	$(OBJS)
	mkdir -p lib
	$(CXX) -shared -o $(LIBNAME) $^
	mv $(LIBNAME) lib

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr src-demolish $(OBJS)
