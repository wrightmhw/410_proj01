all: reporter.cpp reporter.h controller.cpp controller.h
	g++ -O2 -Wall -o reporter reporter.cpp
	g++ -O2 -Wall -o controller controller.cpp

clean:
	rm -rf reporter controller
