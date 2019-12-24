# Generate by VCXProjToMake
# Cpp_Compiler
Cpp_Compiler=g++

# Compiler_Flags
Compiler_Flags=-O0 -Wall -ggdb -std=c++11

# Include_Path
Include_Path=\

Output_File=../../dist/AhoCorasick.exe

# PreCompile_Macro
PreCompile_Macro=-DGCC_BUILD -DLINUX -D_DEBUG 

# Compiler_Flags
Compiler_Flags=-O0 -Wall -ggdb -std=c++11

# Library_Path
Library_Path=\


# Link_Library_Static
Link_Library_Static=-Wl,-Bstatic -Wl,--start-group -pthread -Wl,--end-group

# Link_Library_Dynamic
Link_Library_Dynamic=-Wl,-Bdynamic -Wl,--start-group -Wl,--end-group

.PHONY: entry
entry: build

# Creates the intermediate and output folders
.PHONY: init
init:
	@echo "|===>RunTarget: init of AhoCorasick"
	mkdir -p ../../bin/Dist
	mkdir -p ../../publish/Dist

# build of AhoCorasick
.PHONE: build
build: init\
	../../bin/Dist/main.o
	@echo "|===>RunTarget: build of AhoCorasick"
	g++ \
	../../bin/Dist/main.o  -lrt $(Library_Path) $(Link_Library_Static) $(Link_Library_Dynamic) -o $(Output_File)
	@echo "|===>Finish Output $(Output_File)"

# Compile cpp file ../../src/main.cpp
-include ../../bin/Dist/main.d
../../bin/Dist/main.o: ../../src/main.cpp
	$(Cpp_Compiler) $(Include_Path) $(PreCompile_Macro) $(Compiler_Flags) -c ../../src/main.cpp -o ../../bin/Dist/main.o
	$(Cpp_Compiler) $(Include_Path) $(PreCompile_Macro) $(Compiler_Flags) -MM ../../src/main.cpp > ../../bin/Dist/main.d

# clean project output content
.PHONY: clean
clean: 
	@echo "|===>RunTarget: clean of AhoCorasick"
	rm -rf ../../bin/*
	rm -rf $(Output_File)
