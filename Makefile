##
## EPITECH PROJECT, 2023
## projects
## File description:
## Makefile
##

BIN			:=    giti
GXX			:=    g++
EXT			:=    cpp

SRC_DIR		:=    src/
INC_DIR		:=    include/
OBJ_DIR		:=    obj/
DEP_DIR		:=    dep/

SRC			=    $(shell find $(SRC_DIR) -type f -name "*.$(EXT)")
OBJ			=    $(addprefix $(OBJ_DIR), $(notdir $(SRC:.$(EXT)=.o)))
DEP			=    $(addprefix $(DEP_DIR), $(notdir $(SRC:.$(EXT)=.d)))

CFLAGS		:=    -I$(INC_DIR) -W -Wall -Wextra -lgit2 -g3 -lboost_program_options
CXXFLAGS	:=    -MMD -MP -MF

ifneq ($(wildcard $(OBJ_DIR) $(DEP_DIR)), $(OBJ_DIR) $(DEP_DIR))
.PHONY: dirs
dirs:
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@if [ ! -d $(SRC_DIR) ]; then mkdir -p $(SRC_DIR); fi
	@if [ ! -d $(INC_DIR) ]; then mkdir -p $(INC_DIR); fi
	@touch $(DEP_DIR).gitkeep
	@touch $(OBJ_DIR).gitkeep
endif

$(OBJ_DIR)%.o: $(SRC_DIR)%.$(EXT)
	$(GXX) $(CFLAGS) $(CXXFLAGS) \
		$(patsubst $(OBJ_DIR)%.o, $(DEP_DIR)%.d, $@) -c $< -o $@

all: $(BIN)

$(BIN): $(OBJ)
	$(GXX) $(OBJ) -o $(BIN) $(CFLAGS)

-include $(DEP)

clean:
	@rm -rf $(OBJ) $(DEP)

fclean: clean
	@rm -rf $(BIN)
	@rm -rf $(TESTOBJ) $(TESTDEP)
	@rm -rf $(OBJ_DIR)*.gcda $(OBJ_DIR)*.gcno *.*gc*

re: fclean all

.PHONY: all clean fclean re
