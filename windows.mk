include common.mk
OUT := out/librgl.dll
LDFLAGS := $(LDFLAGS) -lOpenGL

SRC := $(SRC) -c src/win/*.c
OBJ := $(OBJ) rgl_win_context.o rgl_win_input.o
CC := i686-w64-mingw32-gcc
	
compile:
	$(CC) $(SRC) $(INCS) $(CFLAGS)

link:
	$(CC) -shared $(OBJ) $(LDFLAGS) -o $(OUT)

clean:
	rm -rf *.o

install:
	mkdir -p out
	make -f windows.mk
	sudo mkdir -p /usr/include/rgl
	sudo cp -r include/* /usr/include/rgl/
	sudo cp $(OUT) /usr/lib/
