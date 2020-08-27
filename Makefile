NAME = unitTester
INCLUDES = includes
STD = -D LIBRARY=std
FT = -D LIBRARY=ft
BONUS = -D BONUS=1

all: check

check:
	@ clang++ -lgtest ${STD} ${BONUS} -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 
basic:
	@ clang++ -lgtest ${FT} -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 
bonus:
	@ clang++ -lgtest ${FT} ${BONUS} -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 

clean:
	rm ${NAME}
