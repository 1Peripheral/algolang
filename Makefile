CXX = g++
FLAGS = -std=c++11 -Werror -Wall -pedantic
OUT = algol

default:	
	$(CXX) -o build/$(OUT) src/* $(FLAGS)

final : 
	$(CXX) -o build/$(OUT) src/* $(FLAGS) -O2

debug:	
	$(CXX) -o build/$(OUT) src/* $(FLAGS) -g
