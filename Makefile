CXX = g++
FLAGS = -std=c++11 -Werror -Wall
OUT = program

default:	
	$(CXX) -o build/$(OUT) src/* $(FLAGS)
	build/$(OUT)
