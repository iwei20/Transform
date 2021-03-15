name = main
deps = matrix.o screen.o edge_matrix.o

all: run

run: $(name).out
	./$(name).out
	-display $(name).ppm
	echo $(name).ppm

$(name).out: $(name).o $(deps)
	g++ -o $(name).out $(name).o $(deps)

$(name).o: $(name).cpp
	g++ -c $(name).cpp

screen.o: screen.cpp screen.hpp
	g++ -c screen.cpp

edge_matrix.o: edge_matrix.cpp edge_matrix.hpp
	g++ -c edge_matrix.cpp

matrix.o: matrix.cpp matrix.hpp
	g++ -c matrix.cpp

clean:
	rm $(name).out
	rm $(name).ppm
	rm *.o
	
