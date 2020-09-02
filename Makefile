NAME = unitTester
INCLUDES = includes
STD = -D LIBRARY=std
ALL = -D FLAGS=511
BONUS = -D FLAGS=480

basic:
	@ clang++ -lgtest -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 
all: 
	@ clang++ -lgtest -I ${INCLUDES} ${ALL}  test/UnitTest.cpp -o ${NAME} 
bonus:
	@ clang++ -lgtest ${BONUS} -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 

stdlib: # MAKE WITH STD::LIBRARY TO TEST THE TESTER
	@ clang++ -lgtest ${STD} ${ALL} -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 

# TEST SPECIFICALLY ONE CONTAINER
vector:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=1 test/UnitTest.cpp -o ${NAME} 
list:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=2 test/UnitTest.cpp -o ${NAME} 
stack:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=4 test/UnitTest.cpp -o ${NAME} 
queue:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=8 test/UnitTest.cpp -o ${NAME} 
map:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=16 test/UnitTest.cpp -o ${NAME} 
deque:
	@ clang++ -lgtest -fsanitize=address -I ${INCLUDES} -D FLAGS=32 test/UnitTest.cpp -o ${NAME} 
set:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=64 test/UnitTest.cpp -o ${NAME} 
multiset:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=128 test/UnitTest.cpp -o ${NAME} 
multimap:
	@ clang++ -lgtest -I ${INCLUDES} -D FLAGS=256 test/UnitTest.cpp -o ${NAME} 
clean:
	rm ${NAME}
