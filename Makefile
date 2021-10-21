################################################################################
## OS
################################################################################
OS = LINUX
#OS = OSX

################################################################################
## GCC
################################################################################
CC = g++ -std=c++14
OPTS = -O3
#OPTS = -g
FLAGS = -Wall -Werror
ifeq "$(OS)" "LINUX"
  DEFS = -DLINUX
else
  ifeq "$(OS)" "OSX"
  DEFS = -DOSX
endif
endif

################################################################################
## GL and QT
################################################################################
# Open gl
ifeq "$(OS)" "LINUX"
  GL_LIBS = -lGL -lglfw
else
  ifeq "$(OS)" "OSX"
  GL_LIBS = -framework OpenGL -lglfw
endif
endif

################################################################################
## Rules
################################################################################
INCL = $(GL_INCL)
LIBS = $(GL_LIBS)

OBJS = \
       RayTracer.o \
       Sphere.o \
       main.o

DEPS = ${OBJS:%.o=%.d}

EXECUTABLE = spiderling

default: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(OBJMOC)
	$(CC) $(OPTS) $(FLAGS) $(DEFS) $(OBJS) $(LIBS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJS) $(DEPS)

.cpp.o:
	$(CC) $(OPTS) $(DEFS) -MMD $(INCL) -c $< -o $@

-include $(DEPS)
