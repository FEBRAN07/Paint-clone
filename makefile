main: src/main.c
	mkdir -p build
	gcc -Wall -Wextra -I ./include -L ./lib -o build/main src/main.c -lraylib -ldl -lc -lm && ./build/main