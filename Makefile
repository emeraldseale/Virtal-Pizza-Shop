CC = g++
exe_file = pizza_shop
$(exe_file): pizza.o menu.o restaurant.o driver.o
	$(CC) pizza.o menu.o restaurant.o driver.o -o $(exe_file)
pizza.o: pizza.cpp
	$(CC) -c pizza.cpp
menu.o: menu.cpp
	$(CC) -c menu.cpp
restaurant.o: restaurant.cpp
	$(CC) -c restaurant.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
clean:
	rm -f *.out *.o $(exe_file)
