encrypto:   src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c
			$(MAKE) -C src/text/
			mkdir build
			gcc -Isrc/text src/*.c src/*.h src/threads/*.c src/networking/*.c src/misomosi/*.c src/interfaces/*.c src/file/*.c src/*/*/*.h src/*/*/*.c src/text/build/libtext.a -o build/encrypto -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt

gdb:		src/*.c src/*.h src/*/*.c src/*/*/*.h src/*/*/*.c
			$(MAKE) -C src/text/
			gcc -g -Isrc/text src/*.c src/*.h src/threads/*.c src/networking/*.c src/misomosi/*.c src/interfaces/*.c src/file/*.c src/*/*/*.h src/*/*/*.c src/text/build/libtext.a -o build/encrypto-gdb -lpthread `pkg-config --cflags --libs gtk+-3.0` -lgcrypt
			gdb build/encrypto-gdb

clean:		
			rm -rf build messages keyfiles *.o *.bin

install:
			$(MAKE)
			sudo -E cp build/encrypto /usr/bin/