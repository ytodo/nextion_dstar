###################################################
# Makefile for compiling nextion for dmonitor
###################################################

# Program Name and object files
PROGRAM	= nextion
OBJECTS = main.o functions.o nextion.o getconfig.o getstatus.o

# Redefine MACRO
CC	= gcc

# Define extention of Suffix Rules
.SUFFIXES	: .c .o

# Rule of compiling program
$(PROGRAM)	: $(OBJECTS)
	$(CC) -o $(PROGRAM) $^

# Sufix Rule
.c.o	:
	$(CC) -c $<

# Target of Delete files
.PHONY	: clean
clean	:
	$(RM)  $(PROGRAM) $(OBJECTS)

# Dependency of Header Files
$(OBJECTS)	: nextion.h
