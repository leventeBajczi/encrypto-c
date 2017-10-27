encrypto: src/*.c src/*.h
	gcc src/*.c src/*.h -o encrypto -lpthread
	./encrypto
gdb:	src/*.c src/*.h
	gcc src/*.c src/*.h -o encrypto-gdb -lpthread -g
	gdb encrypto-gdb
server: src/*.c src/*.h
	gcc src/*.c src/*.h -o encrypto-server -lpthread
	./encrypto-server -m server
