# Project: 		Migrating Birds Optimization Solving Knapsack Problem
# File: 		Makefile
# Version: 		0.5
# Course: 		SFC - Soft Computing
# Organisation:	Brno University of Technology - Faculty of Information Technology
# Author: 		Daniel Konecny (xkonec75)
# Date: 		13. 11. 2020

# Macros
PP = g++
SUFFIX = cpp
PFLAGS = -Wall -Wextra -pedantic
LIB = 
PROJECT = knapsack
LOGIN = xkonec75

# Options
all: $(PROJECT)

run: $(PROJECT)
	./$(PROJECT)

# Run like "make test TEST=xx" with 'xx' as the number of test (now 01-08, 10-14 and 16-20).
test: $(PROJECT)
	./$(PROJECT) -C "datasets/p$(TEST)_c.txt" -W "datasets/p$(TEST)_w.txt" -P "datasets/p$(TEST)_p.txt" -S "datasets/p$(TEST)_s.txt"

clean:
	rm *.o $(PROJECT)

clear:
	rm *.o $(PROJECT)

pack:
	zip $(LOGIN).zip *.$(SUFFIX) *.h Makefile docs.pdf

zip:
	zip $(LOGIN).zip *.$(SUFFIX) *.h Makefile docs.pdf

# Binary
$(PROJECT): $(PROJECT).o mbo.o Bird.o params.o
	$(PP) $(PFLAGS) $^ -o $@

# Object files
$(PROJECT).o: $(PROJECT).$(SUFFIX) $(PROJECT).h
	$(PP) $(PFLAGS) -c $< -o $@

mbo.o: mbo.$(SUFFIX) mbo.h
	$(PP) $(PFLAGS) -c $< -o $@

Bird.o: Bird.$(SUFFIX) Bird.h
	$(PP) $(PFLAGS) -c $< -o $@

params.o: params.$(SUFFIX) params.h
	$(PP) $(PFLAGS) -c $< -o $@


