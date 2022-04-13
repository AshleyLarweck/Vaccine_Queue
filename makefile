project2: yya310p2.o Queue.o
	gcc yya310p2.o Queue.o -o project2
yya310p2.o: yya310p2.c Queue.h
	gcc -c yya310p2.c -o yya310p2.o 
Queue.o: Queue.c Queue.h
	gcc -c Queue.c -o Queue.o  
clean:
	rm -rf *.o 
	rm project2