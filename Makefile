
SRC_DIR		=	src
GNL_DIR		= 	getNextLine
BUILD_DIR	=	build
NAME		=	cub3d
CFLAG		=	-Wall -Wextra -Werror -I./includes -g3

SRC			=	$(SRC_DIR)/main.c\
				$(SRC_DIR)/split.c\
				$(SRC_DIR)/t_file_printer.c\
				$(SRC_DIR)/t_file_utils.c\
				$(SRC_DIR)/t_file.c\
				$(SRC_DIR)/t_lines_utils.c\
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