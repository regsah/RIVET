CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude/gates -Itests

TEST_SRC = \
	src/gates/gates.c \
	src/gates/combinational.c \
	tests/test.c \
	tests/gates/test_gates.c

BUILD_DIR = build

ifeq ($(OS),Windows_NT)
	TEST_TARGET = $(BUILD_DIR)\groundup_cpu_tests.exe
	RM = del /Q
	RMDIR = rmdir /S /Q
	MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	RUN = .\$(TEST_TARGET)
else
	TEST_TARGET = $(BUILD_DIR)/groundup_cpu_tests
	RM = rm -f
	RMDIR = rm -rf
	MKDIR = mkdir -p $(BUILD_DIR)
	RUN = ./$(TEST_TARGET)
endif

all: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(MKDIR)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET)

test: $(TEST_TARGET)
	$(RUN)

clean:
	-$(RM) $(TEST_TARGET)
	-$(RMDIR) $(BUILD_DIR)
