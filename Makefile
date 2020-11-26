# Project: 		Migrating Birds Optimization Solving Knapsack Problem
# File: 		Makefile
# Version: 		1.0
# Course: 		SFC - Soft Computing
# Organisation:	Brno University of Technology - Faculty of Information Technology
# Author: 		Daniel Konecny (xkonec75)
# Date: 		26. 11. 2020

# Macros
PP = g++
SUFFIX = cpp
PFLAGS = -Wall -Wextra -pedantic
PROJECT = sfc_project
LOGIN = xkonec75

all: $(PROJECT)

# Run like "make test TEST=xx" with 'xx' as the number of test (now 01-08, 10-20 and 21-27).
run: $(PROJECT)
	./$(PROJECT) -C "datasets/p$(TEST)_c.txt" -W "datasets/p$(TEST)_w.txt" -P "datasets/p$(TEST)_p.txt" -S "datasets/p$(TEST)_s.txt"

# Run like "make test TEST=xx" with 'xx' as the number of test (now 01-08, 10-20 and 21-27).
inform: $(PROJECT)
	./$(PROJECT) -i -C "datasets/p$(TEST)_c.txt" -W "datasets/p$(TEST)_w.txt" -P "datasets/p$(TEST)_p.txt" -S "datasets/p$(TEST)_s.txt"

# Run like "make test TEST=xx RUNS=y" with 'xx' as the number of test (now 01-08, 10-20 and 21-27) and 'y' as number of test runs.
test: $(PROJECT)
	./$(PROJECT) -t $(RUNS) -C "datasets/p$(TEST)_c.txt" -W "datasets/p$(TEST)_w.txt" -P "datasets/p$(TEST)_p.txt" -S "datasets/p$(TEST)_s.txt"

help: $(PROJECT)
	./$(PROJECT) -h

version: $(PROJECT)
	./$(PROJECT) -v

clean:
	rm *.o $(PROJECT)

clear:
	rm *.o $(PROJECT)

pack:
	zip $(LOGIN).zip *.$(SUFFIX) *.h Makefile docs.pdf

zip:
	zip $(LOGIN).zip *.$(SUFFIX) *.h Makefile docs.pdf

# Binary
$(PROJECT): $(PROJECT).o Knapsack.o Bird.o Mbo.o params.o
	$(PP) $(PFLAGS) $^ -o $@

# Object files
$(PROJECT).o: $(PROJECT).$(SUFFIX) $(PROJECT).h
	$(PP) $(PFLAGS) -c $< -o $@

Knapsack.o: Knapsack.$(SUFFIX) Knapsack.h
	$(PP) $(PFLAGS) -c $< -o $@

Mbo.o: Mbo.$(SUFFIX) Mbo.h
	$(PP) $(PFLAGS) -c $< -o $@

Bird.o: Bird.$(SUFFIX) Bird.h
	$(PP) $(PFLAGS) -c $< -o $@

params.o: params.$(SUFFIX) params.h
	$(PP) $(PFLAGS) -c $< -o $@
