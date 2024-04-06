MAIN     = src/main.cpp
SRCS    := $(filter-out $(MAIN),$(wildcard src/*.cpp))
PAGES   := $(sort $(wildcard pages/*))
UNITY    = test/unity.c
CPPFLAGS = -Wextra -g -I src/
.PHONY: clean test all run
EXEC     = html-test

$(EXEC): $(MAIN) $(SRCS)
	g++ -o $(EXEC) $(CPPFLAGS) ${SRCS} ${MAIN}

run: $(EXEC)
	./$(EXEC) $(PAGES)

given: $(EXEC)
	./$(EXEC) pages/index.html pages/unbalanced1.html pages/unbalanced2.html pages/csu.html pages/theend.html

%test:
	g++ -I ../src/ ${CPPFLAGS} ${SRCS} ${UNITY} test/$@.cpp -o test-runner
	./test-runner

clean:
	rm -rf $(EXEC) test-runner
