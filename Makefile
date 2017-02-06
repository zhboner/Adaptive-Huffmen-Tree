all: ahencode ahdecode
ahencode: ahencode.cpp basic.cpp
	g++ -o ahencode ahencode.cpp
ahdecode: ahdecode.cpp basic.cpp
	g++ -o ahdecode ahdecode.cpp