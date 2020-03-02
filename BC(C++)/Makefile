#Makefile BC

CXX = g++
CXXFLAGS = -std=c++11 -Wall

main.exe: main.o Entity.h BC.h
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^

#Entity.o: Entity.h
	#$(CXX) $(CXXFLAGS) -c $^

#BC.o: BC.h
	#$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -f *.o main.exe