encrypto:	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h 
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h -o encrypto -lpthread `libgcrypt-config --libs`
			./encrypto
gdb:		src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h 
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h -o encrypto-gdb -lpthread -g `libgcrypt-config --libs`
			gdb encrypto-gdb
server: 	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h 
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h -o encrypto-server -lpthread
			./encrypto-server -m server
