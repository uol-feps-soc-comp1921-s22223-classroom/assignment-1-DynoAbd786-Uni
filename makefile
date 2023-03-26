# set up our compiler settings
# we will be compiling using gcc
CC     = gcc
# setting some useful flags:
# std=c99 is the standard which you should be using
# -Wall means 'report all warnings' which is useful to help you write better code
# -Werror means 'make all warnings into errors' which means your code doesn't compile with warnings
# this is a good idea when code quality is important
# -g enables the use of GDB
CFLAGS = -std=c99 -Wall -Werror -g -lm
# this is your list of executables which you want to compile with all
EXE = ebfEcho ebfComp ebf2ebu ebuEcho ebuComp ebu2ebf ebu2ebc ebcEcho

SRC = ebfEcho.c ebfComp.c ebf2ebu.c ebuEcho.c ebuComp.c ebu2ebf.c ebu2ebc.c ebcEcho.c ebfErrorChecking.c ebfReadFromInputFile.c ebfWriteToOutputFile.c loadFiles.c memoryManagement.c compareFiles.c conversionFunctions.c

OBJ = $(SRCS:.c=.o)

dependencies = ebfStruct.h ebfErrorChecking.h conversionFunctions.h ebfReadFromInputFile.h ebfWriteToOutputFile.h loadFiles.h memoryManagement.h compareFiles.h math.h


# we put 'all' as the first command as this will be run if you just enter 'make'
all: ${EXE}

# clean removes all object files - DO NOT UNDER ANY CIRCUMSTANCES ADD .c OR .h FILES
# rm is NOT REVERSIBLE.
clean: 
	rm -rf *.o ${EXE}

# this is a rule to define how .o files will be compiled
# it means we do not have to write a rule for each .o file
# ebfEcho.o will be compiled by this rule as:
# ebfEcho.o: ebfEcho.c
# gcc -c -std=c99 -g ebfEcho.c -o ebfEcho.o

%.o: %.c $(dependencies)
	$(CC) -c $(CFLAGS) $< -o $@

# for each executable, you need to tell the makefile the 'recipe' for your file
# at the moment, this is very simple as we are only using one .c file
# but as you refactor and add more .c and .h files
# these recipes will become more complex.



ebfEcho: ebfEcho.o ebfErrorChecking.o ebfReadFromInputFile.o ebfWriteToOutputFile.o loadFiles.o memoryManagement.o conversionFunctions.o 
	$(CC) $(CFLAGS) $^ -o $@

ebfErrorChecking: ebfErrorChecking.o 
	$(CC) $(CFLAGS) $^ -o $@

ebfWriteToOutputFile: ebfWriteToOutputFile.o memoryManagement.o conversionFunctions.o ebfErrorChecking.o
	$(CC) $(CFLAGS) $^ -o $@

ebfReadFromInputFile: ebfReadFromInputFile.o memoryManagement.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

loadFiles: loadFiles.o
	$(CC) $(CFLAGS) $^ -o $@

memoryManagement: memoryManagement.o
	$(CC) $(CFLAGS) $^ -o $@

ebfComp: ebfComp.o memoryManagement.o loadFiles.o ebfErrorChecking.o ebfReadFromInputFile.o compareFiles.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

compareFiles: compareFiles.o
	$(CC) $(CFLAGS) $^ -o $@

ebf2ebu: ebf2ebu.o ebfErrorChecking.o ebfReadFromInputFile.o ebfWriteToOutputFile.o loadFiles.o memoryManagement.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

conversionFunctions: conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

ebuEcho: ebuEcho.o ebfErrorChecking.o ebfReadFromInputFile.o ebfWriteToOutputFile.o loadFiles.o memoryManagement.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

ebuComp: ebuComp.o memoryManagement.o loadFiles.o ebfErrorChecking.o ebfReadFromInputFile.o compareFiles.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

ebu2ebf: ebu2ebf.o ebfErrorChecking.o ebfReadFromInputFile.o ebfWriteToOutputFile.o loadFiles.o memoryManagement.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

ebu2ebc: ebu2ebc.o ebfErrorChecking.o ebfReadFromInputFile.o ebfWriteToOutputFile.o loadFiles.o memoryManagement.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@

ebcEcho: ebcEcho.o ebfErrorChecking.o ebfReadFromInputFile.o ebfWriteToOutputFile.o loadFiles.o memoryManagement.o conversionFunctions.o
	$(CC) $(CFLAGS) $^ -o $@