#!/bin/sh
rm *.o *.so *.a 

gcc -c libhello.c  #get libhello.o

echo "#########"
ar crv libhello.a libhello.o #get libhello.a
gcc  -o hello main.c main1.c -L. -lhello
./hello

rm *.a

echo "#########"
gcc -shared -fPCI -o libhello.so libhello.o
gcc  -o hello main.c main1.c -L. -lhello
./hello

rm *.o *.so *.a 
