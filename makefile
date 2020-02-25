CXXFLAGS = -std=c++14 -MMD -O0 -g
LIBS = -lpthread -lX11


CPP=g++
LD=g++

.SUFFIXES:
.SUFFIXES: .o .cpp

EXECS = example_cimg shape_main shape_test

SRCS_example_cimg = example_cimg.cpp
OBJS_example_cimg = ${SRCS_example_cimg:.cpp=.o}
DEP_example_cimg = ${OBJS_example_cimg:.o=.d}

SRCS_shape = shape.cpp
OBJS_shape = ${SRCS_shape:.cpp=.o}

SRCS_shape_main = main.cpp
OBJS_shape_main = ${SRCS_shape_main:.cpp=.o}

SRCS_test = test.cpp
OBJS_test = ${SRCS_test:.cpp=.o}


all: $(EXECS)

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $<

-include ${DEP_example_cimg}

example_cimg: $(OBJS_example_cimg) $(OBJS_example_cimg)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

shape_main: $(OBJS_shape) $(OBJS_shape_main)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

shape_test: $(OBJS_shape) $(OBJS_test) 
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o
	rm -rf $(EXECS)

cleanedit:
	rm -rf *~
