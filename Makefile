all:	clean compile link 


compile:
	g++ -c *.cpp -I"src/include" -DSFML_STATIC 
#	g++ -c main.cpp -I"src/include" -DSFML_STATIC
#	g++ -c coding/*.cpp -I"src/include" -DSFML_STATIC

link:
	g++ *.o -o main -L"src/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

#	g++ main.o -o main -L"src/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

clean:
	del *.o
#	rm -f C:/PROJET/projetcpp/main.o
#mingw32-make -f Makefile