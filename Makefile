# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msainton <msainton@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 17:16:04 by chduong           #+#    #+#              #
#    Updated: 2022/11/22 18:22:46 by msainton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#			EXEC NAME & FOLDERS			#
#########################################
NAME		=	ircserv
SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	inc/

#########################################
#				COMMANDS				#
#				FLAGS					#
#########################################
CXX			=	c++ -c
LINK		=	c++
MKDIR		=	mkdir -p
AR			=	ar rcs
RM			= 	rm -rf

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS	+=	-MMD -MP -g3

LFLAGS		=	
DEBUG		=	-g3 -fsanitize=address,undefined
INC			=	-I inc

#########################################
#			SOURCES	FILES				#
#           & OBJECT FILES    	        #
#           & DEPENDENCIES    	        #
#########################################
SRC		=	main.cpp	Server.cpp Client.cpp NICK.cpp USER.cpp PASS.cpp

OBJ		=	$(SRC:%.cpp=%.o)
OBJ		:=	$(addprefix $(OBJ_DIR), $(OBJ))

DEP		=	${OBJ:.o=.d}

#########################################
#			MAKE	RULES				#
#########################################
$(NAME): $(OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	$(LINK) $(LFLAGS) -o $@ $^
	@echo "> $(CYAN)Compilation$(END) : \t\t[$(YELLOW)COMPLETE$(END)]"

-include ${DEP}

${OBJ_DIR}%.o:	${SRC_DIR}%.cpp
	@${MKDIR} ${@D}
	${CXX} ${CXXFLAGS} ${INC} $< -o $@

all: $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "> $(PURPLE)Clean objects$(END) : \t\t[$(GREEN)OK$(END)]"
	
fclean: clean
	@$(RM) $(NAME)
	@echo "> $(PURPLE)Delete Exec$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all

.PHONY: all clean fclean re

#########################################
#			SYNTAX COLORS				#
#########################################
GREY       =   $'\033[0;30m
RED        =   $'\033[0;31m
GREEN      =   $'\033[0;92m
YELLOW     =   $'\033[0;33m
BLUE       =   $'\033[0;34m
U_BLUE     =   $'\033[4;34m
PURPLE     =   $'\033[0;35m
CYAN       =   $'\033[0;96m
WHITE      =   $'\033[0;37m
END        =   $'\033[0;m
BOLD       =   $'\e[1m
