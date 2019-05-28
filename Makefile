
target: obj obj/main.o obj/Plansza.o obj/SI.o
	g++ -Wall -pedantic -std=c++11 obj/main.o obj/Plansza.o obj/SI.o

obj:
	mkdir -p obj

obj/main.o: src/main.cpp
	g++ -c -g -Iinc -std=c++11 -Wall -pedantic -o obj/main.o src/main.cpp

obj/Plansza.o: inc/Plansza.hh src/Planszav2.cpp
	g++ -c -g -Iinc -std=c++11 -Wall -pedantic -o obj/Plansza.o src/Planszav2.cpp

obj/SI.o: inc/SI.hh src/SI.cpp
	g++ -c -g -Iinc -std=c++11 -Wall -pedantic -o obj/SI.o src/SI.cpp

clean:
	rm -f obj/*.o
