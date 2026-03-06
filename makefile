
CC = g++
CFLAGS = -g 
CPPFLAGS =  -O2  

%.o  :  %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	rm *.o


FileReaderTest.o : FileReaderTest.cpp  FileReader.h 

FileReaderTest :  FileReaderTest.o 


