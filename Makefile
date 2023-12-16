SOURCE=ultrafuck.c
CC=gcc
CCFLAGS=
OUT=ultrafuck

all: linux32 linux64 win32 win64

ultrafuck:
	$(CC) $(SOURCE) $(CCFLAGS) -o $(OUT)
	
linux32:
	make ultrafuck CCFLAGS=-m32 OUT=ultrafuck
	
linux64:
	make ultrafuck CCFLAGS=-m64 OUT=ultrafuck64
	
win32:
	make ultrafuck CC=i686-w64-mingw32-gcc OUT=ultrafuck.exe

win64:
	make ultrafuck CC=x86_64-w64-mingw32-gcc OUT=ultrafuck64.exe
	
.PHONY: all ultrafuck linux32 linux64 win32 win64
