.PHONY: all release clean

RELEASE_FLAGS = -lboost_program_options
RELEASE_EXEC  = calc
SOURCE        = main.cpp

all: release

release: $(RELEASE_EXEC)

calc: $(SOURCE)
	g++ $(SOURCE) $(RELEASE_FLAGS) -o $(RELEASE_EXEC)

clean:
	rm -f $(RELEASE_EXEC)
