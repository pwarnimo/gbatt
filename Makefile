MKDIR_P = mkdir -p
OUT_DIR = bin
OBJ_DIR = obj

.PHONY: directories clean

all: directories gbatt

gbatt: src/main.c
	gcc -o bin/gbatt src/main.c `pkg-config --libs --cflags gtk+-2.0`

directories: ${OUT_DIR} ${OBJ_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}
	${MKDIR_P} ${OBJ_DIR}

clean:
	rm -rf bin
	rm -rf obj
