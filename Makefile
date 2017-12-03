encrypto:	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -o encrypto -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			rm *.o
			./encrypto
gdb:		src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s -g
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -g -o encrypto-gdb -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			gdb encrypto-gdb
			rm *.o
server: 	src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -o encrypto-server -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			rm *.o
			./encrypto-server -m server
create:		src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h src/*/*/*/*.s
			gcc -c src/*/*/*/*.s
			gcc src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c src/*/*/*/*.h *.o -o encrypto -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			rm *.o