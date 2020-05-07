ALL = game;

OBJ = main.o objects.o slime.o bulet.o skeleton.o gun.o
CXXFLAGS += -std=c++17 -Wall -g 


all: $(ALL)



clean: 
	$(RM) $(OBJ) $(ALL) .depend *~ * .bak *stackdump core*

depend:
	$(CXX) $(CXXFLAGS) -MM $(OBJ:.o=.cpp) >.depend

-include .depend