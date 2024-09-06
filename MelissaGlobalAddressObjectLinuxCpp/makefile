# Melissa Global Address Object Windows C++

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g
LDLIBS = -lmdGlobalAddr -lmdAddr -lmdGeo -lmdRightFielder -ldl
LDFLAGS = -L/mnt/f/TEST/GlobalAddressObject-Cpp-Linux/MelissaGlobalAddressObjectLinuxCpp/Build
RM = rm -f

OUT_DIR = Build

MelissaGlobalAddressObjectLinuxCpp: Main.cpp GlobalAddressObject.cpp mdGlobalAddr.h mdEnums.h | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) Main.cpp GlobalAddressObject.cpp $(LDFLAGS) $(LDLIBS) -o $(OUT_DIR)/$@

clean:
	$(RM) *.o $(OUT_DIR)/MelissaGlobalAddressObjectLinuxCpp



