CXX=g++
CXXFLAGS=-c -Wall -std=c++17
LDFLAGS=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

TMP=tmp/
SRC=src/

TTT: $(TMP) $(TMP)main.o $(TMP)TTT.o $(TMP)TTTBot.o
	$(CXX) $(TMP)main.o $(TMP)TTT.o $(TMP)TTTBot.o $(LDFLAGS) -o TTT

$(TMP)main.o: $(SRC)main.cpp
	$(CXX) $(CXXFLAGS) $(SRC)main.cpp -o $(TMP)main.o

$(TMP)TTT.o: $(SRC)TTT.cpp
	$(CXX) $(CXXFLAGS) $(SRC)TTT.cpp -o $(TMP)TTT.o

$(TMP)TTTBot.o: $(SRC)TTTBot.cpp
	$(CXX) $(CXXFLAGS) $(SRC)TTTBot.cpp -o $(TMP)TTTBot.o

$(TMP):
	mkdir $(TMP)

clear:
	$(RM) -r $(TMP)*.o TTT
