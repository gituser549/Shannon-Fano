CXX = g++
CXXFLAGS = -std=c++14 -O3 -march=native -flto -DNDEBUG \
           -ICoderSrc -IDeCoderSrc -IErrorsAndConstantsSrc \
           -IExceptionsSrc -IHashTableSrc -IMain -IStringSrc -ISymbolSrc

SRCS = $(wildcard */*.cpp)

program:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

clean:
	rm -f program

run: program
	./program

.PHONY: clean run
