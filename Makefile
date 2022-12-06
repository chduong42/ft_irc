#########################################
#		EXEC NAME, COMMANDS & FLAGS		#
#########################################
NAME		=	ircserv
PORT		=	6667
PASSWORD	=	a
EXEC		=	./$(NAME) $(PORT) $(PASSWORD)

CXX			=	c++ -c
LINK		=	c++
MKDIR		=	mkdir -p
AR			=	ar rcs
RM			= 	rm -rf

CXXFLAGS	=	-Wall -Wextra -Werror $(VX) $(INC) $(DEPFLAG)
VX			=	-std=c++98
INC			=	-I inc
DEPFLAG		=	-MMD -MP
DEBUG		=	-g3 -fsanitize=address,undefined

LFLAGS		=	

VALGRIND	=	valgrind $(FD) $(LEAK)
FD			=	--track-fds=yes
LEAK		=	--leak-check=yes --show-reachable=yes
MEMCHECK	=	--tool=memcheck

#########################################
#	SOURCES - OBJECTS - DEPENDENCIES	#
#########################################
SRC		=	main.cpp		utils.cpp\
${addprefix class/,\
			Server.cpp		Client.cpp		Channel.cpp}\
${addprefix cmdChannel/,\
			PART.cpp		LIST.cpp		NAMES.cpp		TOPIC.cpp\
			KICK.cpp		MODE.cpp		JOIN.cpp}\
${addprefix cmdServer/,\
			NICK.cpp 		USER.cpp 		PASS.cpp		PRVMSG.cpp\
			OPER.cpp		PING.cpp		KILL.cpp		NOTICE.cpp}

SRC_DIR		=	src/
OBJ_DIR		=	obj/
OBJ			=	$(SRC:%.cpp=%.o)
OBJ			:=	$(addprefix $(OBJ_DIR), $(OBJ))
DEP			=	${OBJ:.o=.d}

#########################################
#			MAKE	RULES				#
#########################################
$(NAME): $(OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(LINK) $(LFLAGS) -o $@ $^
	@echo "> $(CYAN)Compilation$(END) : \t\t[$(YELLOW)COMPLETE$(END)]"

-include ${DEP}

${OBJ_DIR}%.o:	${SRC_DIR}%.cpp
	@${MKDIR} ${@D}
	${CXX} ${CXXFLAGS} $< -o $@

all: $(NAME)

test:
	$(EXEC)

check:
	$(VALGRIND) $(EXEC)

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
GREY		=   $'\033[0;30m
RED			=   $'\033[0;31m
GREEN		=   $'\033[0;92m
YELLOW		=   $'\033[0;33m
BLUE		=   $'\033[0;34m
U_BLUE		=   $'\033[4;34m
PURPLE		=   $'\033[0;35m
CYAN		=   $'\033[0;96m
WHITE		=   $'\033[0;37m
END			=   $'\033[0;m
BOLD		=   $'\e[1m
