
SRC_DIR		=	src
INIT_DIR	=	init
REF_DIR		=	Refile/src
GNL_DIR		= 	Refile/getNextLine
BUILD_DIR	=	build
NAME		=	cub3d
CFLAG		=	-Wall -Wextra -Werror -I./includes -g3

SRC			=	$(SRC_DIR)/main.c\
				$(SRC_DIR)/free.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/print.c \
				$(SRC_DIR)/$(INIT_DIR)/map_parse.c \
				$(SRC_DIR)/$(INIT_DIR)/config.c \
				$(SRC_DIR)/$(INIT_DIR)/map.c \
				$(REF_DIR)/split.c\
				$(REF_DIR)/t_file_printer.c\
				$(REF_DIR)/t_file_utils.c\
				$(REF_DIR)/t_file.c\
				$(REF_DIR)/t_lines_utils.c\
				$(GNL_DIR)/get_next_line_utils.c\
				$(GNL_DIR)/get_next_line.c\
			
CC			=	cc 

OBJ		=	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRC))


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC)	$(CFLAG)	-c	$< -o	$@
	@clear
	
all: $(NAME)

$(NAME):$(OBJ)
	@echo $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(CFLAG)
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


re: fclean all clear 

.PHONY: all clean fclean re