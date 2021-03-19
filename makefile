name = main
scriptname = script
picture = pic
deps = matrix.o screen.o edge_matrix.o transform_manager.o parser.o

all: run

run: $(name).out $(scriptname)
	./$(name).out $(scriptname)
	-display $(picture).ppm
	echo $(picture).ppm

$(name).out: $(name).o $(deps)
	g++ -o $(name).out $(name).o $(deps)

$(name).o: $(name).cpp
	g++ -c $(name).cpp

$(deps): %.o: %.cpp
	g++ -c $<

clean:
	-rm $(name).out
	-rm $(picture).ppm
	-rm *.o
	
