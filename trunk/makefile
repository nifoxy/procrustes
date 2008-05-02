OBJS = GridReader.o Procrustes.o PObject.o
LIBS = -lpng -lpngwriter -lz -lfreetype -lm

all: $(OBJS)
	g++ -o procrustes procrustes.cpp $(OBJS) $(LIBS)
test: $(OBJS)
	g++ -o ptest ptest.cpp $(OBJS) $(LIBS)
clean:
	rm -f *.o procrustes ptest
