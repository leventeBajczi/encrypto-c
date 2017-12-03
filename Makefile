encrypto:   src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -o build/encrypto -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			rm *.o
			
gdb:		src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s -g
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -g -o build/encrypto-gdb -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			gdb build/encrypto-gdb
			rm *.o
server: 	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -o build/encrypto-server -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			rm *.o
			build/encrypto-server -m server
install:	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -o build/encrypto -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			rm *.o
			sudo cp build/encrypto /usr/bin/encrypto