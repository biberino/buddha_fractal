all:
	g++ --std=c++11 -Ofast -ffast-math ConfReader.cpp BuddhaCalculator.cpp time.cpp save_raw.cpp main.cpp -o buddha -lpthread