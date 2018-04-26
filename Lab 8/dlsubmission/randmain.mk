OPTIMIZE = -O2

CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

randlibsw.o: randlibsw.c
	$(CC) $(CFLAGS) -fPIC -c randlibsw.c

randlibsw.so: randlibsw.o
	$(CC) -shared randlibsw.o -o randlibsw.so 

randlibhw.o: randlibhw.c
	$(CC) $(CFLAGS) -fPIC -c randlibhw.c

randlibhw.so: randlibhw.o
	$(CC) -shared randlibhw.o -o randlibhw.so

randmain.o: randmain.c
	$(CC) -c randmain.c 

randcpuid.o: randcpuid.c
	$(CC) -c randcpuid.c 

randmain: randmain.o randcpuid.o
	$(CC) randmain.o randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain
