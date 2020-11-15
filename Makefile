# Project: 		Migrating Birds Optimization Solving Knapsack Problem
# File: 		Makefile
# Version: 		0.1
# Course: 		SFC - Soft Computing
# Organisation:	Brno University of Technology - Faculty of Information Technology
# Author: 		Daniel Konecny (xkonec75)
# Date: 		13. 11. 2020

# Macros
PP = g++
SUFFIX = cpp
PFLAGS = -Wall -Wextra -pedantic -O3
LIB = 
PROJECT = mbo
LOGIN = xkonec75

# Options
all: $(PROJECT)

run: $(PROJECT)
	./$(PROJECT)

clean:
	rm *.o $(PROJECT)

clear:
	rm *.o $(PROJECT)

pack:
	zip $(LOGIN).zip *.$(SUFFIX) *.h Makefile docs.pdf

zip:
	zip $(LOGIN).zip *.$(SUFFIX) *.h Makefile docs.pdf

# Binary
$(PROJECT): $(PROJECT).o params.o
	$(PP) $(PFLAGS) $^ -o $@

# Object files
$(PROJECT).o: $(PROJECT).$(SUFFIX) $(PROJECT).h
	$(PP) $(PFLAGS) -c $< -o $@

params.o: params.$(SUFFIX) params.h
	$(PP) $(PFLAGS) -c $< -o $@


