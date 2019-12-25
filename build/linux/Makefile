# Generate by VCXProjToMake
# Cpp_Compiler
Cpp_Compiler=g++

# Compiler_Flags
Compiler_Flags=-O0 -Wall -ggdb -std=c++11

# Include_Path
Include_Path=\

Output_File=../../publish/dist/AhoCorasick

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
	mkdir -p ../../bin/dist
	mkdir -p ../../publish/dist

# build of AhoCorasick
.PHONE: build
build: init\
	../../bin/dist/main.o
	@echo "|===>RunTarget: build of AhoCorasick"
	g++ \
	../../bin/dist/main.o  -lrt $(Library_Path) $(Link_Library_Static) $(Link_Library_Dynamic) -o $(Output_File)
	@echo "|===>Finish Output $(Output_File)"

# Compile cpp file ../../src/main.cpp
-include ../../bin/dist/main.d
../../bin/dist/main.o: ../../src/main.cpp
	$(Cpp_Compiler) $(Include_Path) $(PreCompile_Macro) $(Compiler_Flags) -c ../../src/main.cpp -o ../../bin/dist/main.o
	$(Cpp_Compiler) $(Include_Path) $(PreCompile_Macro) $(Compiler_Flags) -MM ../../src/main.cpp > ../../bin/dist/main.d

# clean project output content
.PHONY: clean
clean: 
	@echo "|===>RunTarget: clean of AhoCorasick"
	rm -rf ../../bin/*
	rm -rf $(Output_File)
