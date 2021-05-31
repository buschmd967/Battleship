SHELL = /bin/sh

CLIENT_CPP = src/Client/ship.cpp src/Client/client.cpp src/Client/render.cpp src/Client/button.cpp
CC = g++
LIBS = -lglfw3 -lsfml-graphics -lsfml-window -lsfml-system
CLIENT_OUT = -o bin/Client

client:${OBJ}
	${CC} ${INCLUDES} ${CLIENT_CPP} ${LIBS} ${CLIENT_OUT}

