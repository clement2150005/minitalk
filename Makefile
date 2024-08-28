# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 16:19:44 by ccolin            #+#    #+#              #
#    Updated: 2024/08/28 12:50:05 by ccolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program names
NAME_SERVER	= server
NAME_CLIENT	= client

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes #-fsanitize=address

# Directories
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBFT_INC	= -I$(LIBFT_DIR) -I$(LIBFT_DIR)/includes

# Source files
SERVER_SRC	= server.c
CLIENT_SRC	= client.c

# Object files
SERVER_OBJS	= $(SERVER_SRC:.c=.o)
CLIENT_OBJS	= $(CLIENT_SRC:.c=.o)

# Remove command
RM			= rm -f

# Colors
BOLD_GREEN	= \033[1;32m
BOLD_YELLOW	= \033[1;33m
BOLD_PURPLE	= \033[1;35m
BOLD_CYAN	= \033[1;36m
NO_COLOR	= \033[0m

# Messages
COMP_START	= echo "$(BOLD_YELLOW)Compiling $<...$(NO_COLOR)"
COMPLETE	= echo "$(BOLD_GREEN)Compilation complete!$(NO_COLOR)"
CLEAN_MSG	= echo "$(BOLD_PURPLE)Cleaning up...$(NO_COLOR)"
FCLEAN_MSG	= echo "$(BOLD_PURPLE)Full clean up...$(NO_COLOR)"
LIBFT_MSG	= echo "$(BOLD_CYAN)Compiling libft...$(NO_COLOR)"

# Ensure all is the first target
all: $(NAME_SERVER) $(NAME_CLIENT)
	@$(COMPLETE)

# Build the server program
$(NAME_SERVER): $(LIBFT_LIB) $(SERVER_OBJS)
	@echo "$(BOLD_CYAN)Linking $(NAME_SERVER)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $(NAME_SERVER) $(SERVER_OBJS) $(LIBFT_LIB)
	@echo "$(BOLD_GREEN)$(NAME_SERVER) is ready!$(NO_COLOR)"

# Build the client program
$(NAME_CLIENT): $(LIBFT_LIB) $(CLIENT_OBJS)
	@echo "$(BOLD_CYAN)Linking $(NAME_CLIENT)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(CLIENT_OBJS) $(LIBFT_LIB)
	@echo "$(BOLD_GREEN)$(NAME_CLIENT) is ready!$(NO_COLOR)"

# Build the libft library
$(LIBFT_LIB):
	@$(LIBFT_MSG)
	@make -C $(LIBFT_DIR)

# Compile object files
%.o: %.c
	@$(COMP_START)
	@$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

# Clean object files
clean:
	@$(CLEAN_MSG)
	@$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	@make clean -C $(LIBFT_DIR)
	@echo "$(BOLD_GREEN)Cleaned up object files.$(NO_COLOR)"

# Clean everything, including executables
fclean: clean
	@$(FCLEAN_MSG)
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(BOLD_GREEN)Full clean up complete.$(NO_COLOR)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re


