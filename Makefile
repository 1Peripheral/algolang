CXX = g++
FLAGS = -std=c++11 -Werror -Wall
OUT = algol

default:	
	$(CXX) -o build/$(OUT) src/* $(FLAGS)

debug:	
	$(CXX) -o build/$(OUT) src/* $(FLAGS) -g
