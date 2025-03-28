# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 17:02:11 by okapshai          #+#    #+#              #
#    Updated: 2025/03/28 12:37:32 by okapshai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME = RPN

##############
# SRCS FILES #
##############

# DIRECTORY VARIABLES
SRCS_DIR			:=	src/

# SRCS VARIABLES
SRCS_FILES 			:= \
					Rpn.cpp\
					main.cpp
					
SRCS				:=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

###############
# INGREDIENTS #
###############

# INC
INC_DIR				:=	includes/

# OBJS
OBJS_DIR			:=	objs/
OBJS				:=	$(SRCS:$(SRCS_DIR)%.cpp=$(OBJS_DIR)%.o)

# DEPENDENCIES
DEPS				:=	$(OBJS:$(OBJS_DIR)%.o=$(OBJS_DIR)%.d)

# FLAGS
CXX 				:= 	c++
CXXFLAGS			:= 	-Wall -Wextra -Werror -std=c++98
INCFLAGS			:=	-I$(INC_DIR)

# BASH FUNCTIONS
RM 					:= rm -rf
DIR_DUP 			:= mkdir -p $(@D)

###########
# COLORS #
###########
GREEN = '\033[0;32m'
CYAN = '\033[0;36m'
WHITE = '\033[0;37m'

all: $(NAME)

$(NAME): $(OBJS)
		$(CXX) $(CXXFLAGS) $(INCFLAGS) $(OBJS) -o $@
		@echo ✅ $(GREEN)"Project successfully compiled"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@$(DIR_DUP) $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@

-include $(DEPS)
	

clean:
	@echo 🧹 $(CYAN)"Removing .o files"$(WHITE)
	${RM} $(OBJS) $(DEPS)

fclean: clean
	@echo 🧹 $(CYAN)"Removing all"$(WHITE)
	${RM} $(NAME)
	$(RM) $(OBJS_DIR)


re: fclean all

.PHONY: all clean fclean re