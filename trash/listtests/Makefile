NAME		=	listtest
TEST		=	cleartest \
				mergetest \
				resizetest \
				splicetest \
				sorttest \
				swaptest \
				uniquetest \
				removetest \
				removeiftest \
				test1 \
				test2 \
				test3 \
				test4 \
				test5 \
				#constructors
				#mainlist

SRCS		=	$(addsuffix .cpp, $(TEST))
TESTS		=	$(addsuffix .o, $(TEST))
STD_SRCS	=	$(addprefix std_, $(SRCS))
STD			=	$(addprefix std_, $(TESTS))
EXEC		=	$(addprefix ./, $(TESTS))
DEF			=	-D LIBRARY=std
CC			=	clang++
FLAGS		=	-Wall -O3  -g3 -fsanitize=address

all: ft std

ft: $(TESTS)
	rm ft/*
	mv *.o ft
std: $(TESTS)
	rm std/*
	mv *.o std
%.o: %.cpp
	# $(CC) $(FLAGS) $(DEF) $^ -o $@
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -rf *.dSYM
fclean: clean
	rm -f $(TESTS)

re: clean all
