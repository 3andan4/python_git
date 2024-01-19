##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## It's our Makefile now
##

# Glados
BINNAME			:=	giti
BINDIR			:=	.

# Tests
# TEST_FUNC		:=	test/func/script.sh

# Coverage
COVPATH		:=	$(shell stack path --local-hpc-root)/giti/giti-test
COVEXT		:=	html
COVDIR		:=	coverage
COVNAME		:=	hpc_index.$(COVEXT)
COVFILE		:=	$(COVDIR)/$(COVNAME)

# Command
RM			:=	rm -rf

# Display
RED				:=	\033[1;31m
GREEN			:=	\033[1;32m
YELLOW			:=	\033[1;33m
BLUE			:=	\033[1;34m
MAGENTA			:=	\033[1;35m
CYAN			:=	\033[1;36m
NC				:=	\033[0m
LINE			:=	\n================================================
INTRO_SUCCES	:=	$(GREEN)➜$(NC)
INTRO_FAILED	:=	$(RED)➜$(NC)

# remove command print
.SILENT:	all	clean	fclean	re	run	\
			unit_tests	func_tests	tests_run	coverage
# safety
.PHONY:		all	clean	fclean	re	run	\
			unit_tests	func_tests	tests_run	coverage
# allow makefile to continue if error occurs
.IGNORE:	unit_tests	func_tests

all:
#	install is a shortcut for 'build --copy-bins'
	stack --local-bin-path $(BINDIR) install

clean:
	stack clean

fclean:
#	purge is a shortcut for 'clean --full'
	stack purge
	$(RM) $(BINNAME)
	$(RM) $(COVDIR)/*

re:		fclean all

run:	all
	stack exec $(BINNAME)

#  TESTS
# =========================================================

unit_tests:
	echo -e "\n${YELLOW} · Unit Tests${LINE}${NC}"
	stack test --coverage --keep-going 2> /dev/null
	cp -r $(COVPATH)/* $(COVDIR)

func_tests:
	echo -e "\n${YELLOW} · Functionnal${LINE}${NC}\n"
	./$(TEST_FUNC)

run_tests:	all	unit_tests

coverage:
	firefox $(COVFILE)
