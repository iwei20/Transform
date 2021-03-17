name = main
deps = matrix.o screen.o edge_matrix.o transform_manager.o

all: run

run: $(name).out
	./$(name).out
	-display $(name).ppm
	echo $(name).ppm

$(name).out: $(name).o $(deps)
	g++ -o $(name).out $(name).o $(deps)

$(name).o: $(name).cpp
	g++ -c $(name).cpp

$(deps): %.o: %.cpp
	g++ -c $<

clean:
	rm $(name).out
	rm $(name).ppm
	rm *.o
	
