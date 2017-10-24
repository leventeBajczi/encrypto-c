encrypto: src/*.c src/*.h
	gcc src/*.c src/*.h -o encrypto -lpthread
	./encrypto
gdb:	  src/*.c src/*.h
	gcc src/*.c src/*.h -o encrypto -lpthread -g
	gdb encrypto