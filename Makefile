encrypto:	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h 
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h -o encrypto -lpthread `pkg-config --cflags --libs gtk+-3.0`
			./encrypto
gdb:		src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h 
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h -o encrypto-gdb -lpthread -g `pkg-config --cflags --libs gtk+-3.0`
			gdb encrypto-gdb
server: 	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h 
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h -o encrypto-server -lpthread `pkg-config --cflags --libs gtk+-3.0`
			./encrypto-server -m server
create:		src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h 
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h -o encrypto -lpthread `pkg-config --cflags --libs gtk+-3.0`