# Define the compiler to use
CXX = g++

# Define compile flags
CXXFLAGS = -Wall -g

# Define the libraries to link against
LIBS = -lws2_32

# Define the source files
SRCS = httpServer.cpp

# Define exe
MAIN = server

.PHONY: depend clean

all:    $(MAIN)
	@echo  $(MAIN) has been compiled

$(MAIN): $(SRCS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(SRCS) $(LFLAGS) $(LIBS)

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^