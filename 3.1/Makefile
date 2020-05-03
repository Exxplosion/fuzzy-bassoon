ALL = game;

OBJ = main.o objects.o slime.o bulet.o skeleton.o
CXXFLAGS += -std=c++17 -Wall -g 


all: $(ALL)

game: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ -lsfml-graphics -lsfml-window -lsfml-system $^

clean: 
	$(RM) $(OBJ) $(ALL) .depend *~ * .bak *stackdump core*

depend:
	$(CXX) $(CXXFLAGS) -MM $(OBJ:.o=.cpp) >.depend

-include .depend