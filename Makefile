PATHFILEC = src/FruitRainSDLEdition
ifeq ($(OS),Windows_NT)
    EXECUTABLE = $(PATHFILEC).exe
else
    EXECUTABLE = $(PATHFILEC)
endif
all:
	make compile
compile:
	g++ Main.cpp -o $(EXECUTABLE) -lSDL2 -lSDL2_mixer -lSDL2_image
clean:
	rm -fr src/*
run:
	$(EXECUTABLE)
clean-compile-run:
	make clean
	make compile
	make run