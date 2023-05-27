PATHFILEC = src/FruitRainSDLEdition
ifeq ($(OS),Windows_NT)
    EXECUTABLE = $(PATHFILEC).exe
else
    EXECUTABLE = $(PATHFILEC)
endif
all:
	make compile
compile:
	g++ Main.cpp -o $(EXECUTABLE) -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
compileWin:
	ifeq ($(OS),Windows_NT)
		g++ Windows.cpp -o $(EXECUTABLE) -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lSDL2main -lSDL2 -lSDL2_ttf
	else:
		echo "Target is not supported"
	endif
clean:
	rm -fr src/*
run:
	$(EXECUTABLE)
clean-compile-run:
	make clean
	make compile
	make run
