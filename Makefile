all:
	g++ --std=c++11 -Ofast -ffast-math BuddhaCalculator.cpp time.cpp main.cpp -o buddha -lpthread