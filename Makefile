build:
	g++ -Wall ./src/*.cpp -Ilib -o worldzer
run:
	./worldzer
clean:
	rm worldzer