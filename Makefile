
SRC_DIR		=	src
INIT_DIR	=	init
LOOP_DIR	=	loop
REF_DIR		=	ReFile/src
GNL_DIR		= 	ReFile/getNextLine
BUILD_DIR	=	build
NAME		=	cub3d
CFLAG		=	-Wall -Wextra -Werror -I./includes -g3
LDFLAGS 	= 	-L./minilibx-linux -lmlx_Linux -lmlx -lX11 -lXext -lm

SRC			=	$(SRC_DIR)/main.c\
				$(SRC_DIR)/img/img.c \
				$(SRC_DIR)/img/put_string.c \
				$(SRC_DIR)/img/drawing.c \
				$(SRC_DIR)/free.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/print.c \
				$(REF_DIR)/split.c \
				$(REF_DIR)/t_file_printer.c \
				$(REF_DIR)/t_file_utils.c \
				$(REF_DIR)/t_file.c \
				$(REF_DIR)/t_lines_utils.c \
				$(SRC_DIR)/$(LOOP_DIR)/game.c \
				$(SRC_DIR)/$(LOOP_DIR)/raycasting.c \
				$(SRC_DIR)/$(LOOP_DIR)/key.c \
				$(SRC_DIR)/$(INIT_DIR)/map_parse.c \
				$(SRC_DIR)/$(INIT_DIR)/config.c \
				$(SRC_DIR)/$(INIT_DIR)/map.c \
				$(GNL_DIR)/get_next_line_utils.c \
				$(GNL_DIR)/get_next_line.c \
				
			
CC			=	cc 

OBJ		=	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRC))


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC)	$(CFLAG)	-c	$< -o	$@
	@clear
	
all: $(NAME)

$(NAME):$(OBJ)
	@echo $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(CFLAG) $(LDFLAGS)
	@clear

clear :
	@clear
	@echo "42Paris : $(NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@echo "Clean   : *.o in build !"

fclean : clean
	@rm -f $(NAME)
	@echo "Clean   : ./$(NAME)"

aclean : fclean cleanlib clear

minlibx :
	@git clone https://github.com/42Paris/minilibx-linux.git
	@make -C ./minilibx-linux
	clear

cleanlib :
	@rm -rf minilibx-linux

re: fclean all clear 

.PHONY: all clean fclean re