# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/21 20:31:07 by tbruinem      #+#    #+#                  #
#    Updated: 2020/10/20 16:03:08 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		42cpp
SRCDIR =	src
OBJDIR =	obj
INCLDIR =	incl
CXX =		g++
SRC :=		main \
			utils \
			source \
			Function \
			header

OBJ :=		$(SRC:%=$(OBJDIR)/%.o)
SRC	:=		$(SRC:%=$(SRCDIR)/%.cpp)
FLAGS =		-Wall -Wextra -Werror

ifeq ($(DEBUG),1)
	FLAGS += -g -fsanitize=address
endif

all: $(NAME)

obj/%.o: src/%.cpp
	@echo $(SRC)
	@echo $(OBJ)
	@mkdir -p $(@D)
	$(CXX) -c $(FLAGS) -I $(INCLDIR) $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(FLAGS) -I $(INCLDIR) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
