main: main.o entity.o  render.o snake.o texture.o deque.o
	 gcc  main.o entity.o render.o snake.o texture.o deque.o -o main  -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image

main.o: main.c
	    gcc -c  main.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image	


entity.o: entity.c includes/Entity.h
	    gcc -c entity.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image	


render.o: render.c includes/Render.h
	    gcc -c render.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image	


snake.o: snake.c includes/Snake.h
	    gcc -c snake.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image	


texture.o: texture.c includes/Texture.h
	    gcc -c texture.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image	


deque.o: deque.c includes/Deque.h
	    gcc -c deque.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image	

clean:
	rm *.o main