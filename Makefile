NAME = unitTester
FLAGS = -Wall -Werror -Wextra
INCLUDES = includes
STD = -D LIBRARY=std
ALL = -D FLAGS=511
BONUS = -D FLAGS=480

basic:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} test/main.cpp -o ${NAME} 
	@ ./unitTester
all: 
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} ${ALL}  test/main.cpp -o ${NAME} 
	@ ./unitTester
bonus:
	@ clang++ ${FLAGS} -lgtest ${BONUS} -I ${INCLUDES} test/main.cpp -o ${NAME} 
	@ ./unitTester

stdlib: # MAKE WITH STD::LIBRARY TO TEST THE TESTER
	@ clang++ ${FLAGS} -lgtest ${STD} ${ALL} -I ${INCLUDES} test/main.cpp -o ${NAME} 
	@ ./unitTester
	
re: clean basic

# TEST SPECIFICALLY ONE CONTAINER
vector:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=1 test/main.cpp -o ${NAME}
	@ ./unitTester 
list:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=2 test/main.cpp -o ${NAME}
	@ ./unitTester 
stack:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=4 test/main.cpp -o ${NAME}
	@ ./unitTester 
queue:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=8 test/main.cpp -o ${NAME}
	@ ./unitTester 
map:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=16 test/main.cpp -o ${NAME}
	@ ./unitTester 
deque:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=32 test/main.cpp -o ${NAME}
	@ ./unitTester 
set:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=64 test/main.cpp -o ${NAME}
	@ ./unitTester 
multiset:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=128 test/main.cpp -o ${NAME}
	@ ./unitTester 
multimap:
	@ clang++ ${FLAGS} -lgtest -I ${INCLUDES} -D FLAGS=256 test/main.cpp -o ${NAME} 
	@ ./unitTester
clean:
	rm ${NAME}
