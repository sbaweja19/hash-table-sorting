CXX=clang++

CXXFLAGS = -Wall -Wextra -Werror

BINARIES=testWordCount2

all: ${BINARIES}

tests: ${BINARIES}
	./testWordCount2

testWordCount2: testWordCount2.o WordCount.o tddFuncs.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o