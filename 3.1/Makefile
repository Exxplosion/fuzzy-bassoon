#тип компилятора 
CC = g++
#инструкции
№CFLAGS = -Wall
#название цели (слева)
PROG = try.o
#цель справа
PROG_OBJ = try.cpp


all: hello

hello: try.o
	g++ try.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app
#прибавление @ в начале команды(типа @echo ...) команда работает
#в сайлент режиме, т.е. не выводиться в консоль

#$(PROG): $(PROG_OBJ)
#	$(CC) -c $@
$try.o: try.cpp
	g++ -c try.cpp


#$sfml-app: main.o
#	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
do:
	./sfml-app
#$@цель слева $@цель справа

#clear:
#	rm *.o