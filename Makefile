# main: main.o entity.o  render.o snake.o texture.o deque.o
# 	 gcc  main.o entity.o render.o snake.o texture.o deque.o -o main  -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image

# main.o: main.c
# 	    gcc -c  main.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image


# entity.o: entity.c includes/Entity.h
# 	    gcc -c entity.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image


# render.o: render.c includes/Render.h
# 	    gcc -c render.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image


# snake.o: snake.c includes/Snake.h
# 	    gcc -c snake.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image


# texture.o: texture.c includes/Texture.h
# 	    gcc -c texture.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image


# deque.o: deque.c includes/Deque.h
# 	    gcc -c deque.c -I /usr/local/include/SDL2 -L /usr/local/lib -lSDL2 -lSDL2_image

# clean:
# 	rm *.o main

#  I left your old code for comparison
# This makefile will only recompile if something has changed, however the.h files do not count so you should use make re if you have changed your header files

NAME = snake
# FLAGS = -Wall -Wextra -Werror # These flags turns warnings into errors, I have rwi of the variable so I can comment out the one I don't want (for exmaple sometime you just want to compile without caring for warnings)
FLAGS =
INCLUDES = -I includes/ -I /usr/local/include/SDL2

STATIC_LIB = -l SDL2 -l SDL2_image -L /usr/local/lib

SRCS_DIR = srcs/
BIN_DIR = bin/

# Name of your source files, if you add , remove or modify the name of a file you should update it here
SRCS_NAMES =	\
	deque		\
	entity		\
	main		\
	render		\
	snake		\
	texture		\

# This line means to add $(SRC_DIR) (which I have set to srcs/) in front of every word in SRCS_NAMES, and add ".c" at the end of the word
# The synatx is $(addprefix [what you want to add in front], [what you want to add it to])
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_NAMES)))
# Here $(SRCS:.c=.o) means to convert every ".c" into a ".o"
OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))


# This means to execute the command $(NAME) as prerequisite
all: $(NAME)
# all:
# 	echo $(SRCS)

# This is the command $NAME, it has preqrequisite to exevute $BIN_DIR and $OBJS
$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS)  $(STATIC_LIB)
#This is just compiling

#This command makes the /bin directory if it doesn;t exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Here we will compile our c files into .o files and put then im the /bin directory so it is more clean
# This runs for every word in $BIN_DIR that ends with .o, which is $OBJS. $(BIN_DIR)%.o expands to /bin/filename.o  and is the target
# $< expans to filename.c
# $< means first argument (file ending with .o) $@ is the target
$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

# recompile everything and run the executable
run: re clean
	./$(NAME)

# deletes object files
clean:
	rm -rf $(BIN_DIR)

# deletes the executable and object files
fclean: clean
	rm -f $(NAME)

# This will recompile everything, including headers.
re: fclean all
