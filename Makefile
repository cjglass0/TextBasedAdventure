run: Utilities.o Player.o Menu.o Location.o LocationElffor.o \
LocationRoadToElffor.o Game.o Main.o
	g++ -Wall -o $@ $^

push:
	git push origin master

Utilities.o: Utilities.h Utilities.cpp

Player.o: Player.h Player.cpp

Menu.o: Menu.h Menu.cpp

Location.o: Location.h Location.cpp

LocationElffor.o: LocationElffor.h LocationElffor.cpp

LocationRoadToElffor.o: LocationRoadToElffor.h LocationRoadToElffor.cpp

Game.o: Menu.h Game.h Game.cpp

Main.o: Game.h Main.cpp

clean:
	rm run *.o *~ *.h.gch

clear:
	rm *~