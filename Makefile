NAME = unitTester
INCLUDES = includes
STD = -D LIBRARY=std
FT = -D LIBRARY=ft
BASIC = -D BASIC
BONUS = -D BONUS

all: 
	@ clang++ -lgtest ${FT} -I ${INCLUDES} ${BASIC} ${BONUS}  test/UnitTest.cpp -o ${NAME} 
basic:
	@ clang++ -lgtest ${FT} -I ${INCLUDES} ${BASIC} test/UnitTest.cpp -o ${NAME} 
bonus:
	@ clang++ -lgtest ${FT} ${BONUS} -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 
stdlib:
	@ clang++ -lgtest ${STD} ${BASIC} ${BONUS} -I ${INCLUDES} test/UnitTest.cpp -o ${NAME} 
clean:
	rm ${NAME}
