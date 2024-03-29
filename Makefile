# CXX=g++ 
# CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
# SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
# OBJECTS=${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
# DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=straights

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC):
	cd src && make && mv $(EXEC) ../ && make clean

.PHONY: clean
.PHONY: DD2
DD2:
	mkdir DD2-zip
	cp src/* DD2-zip
	cp DD2-pdfs/demo/demo.pdf DD2-zip
	cp DD2-pdfs/DesignDoc/design.pdf DD2-zip
	cp DD2-pdfs/UML/uml-final.pdf DD2-zip
	cd DD2-zip && zip straights.zip *
	cp DD2-zip/straights.zip .
	rm -r DD2-zip
clean:
	rm  -f $(EXEC)
