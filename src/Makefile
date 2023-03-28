NAME = s21_decimal.a
TEST = test
REPORT = gcov_report

FLAGS = -Wall -Werror -Wextra -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -g -O0
TEST_LIBS = -lcheck -lm
#TEST_LIBS = -lcheck -lm -lsubunit
CC = gcc

SRC_DIR = .
TEST_SRC_DIR = ./tests

INCLD_DIR = .
TEST_INCLD_DIR = ./tests

OBJ_DIR = $(SRC_DIR)/objs
TEST_OBJ_DIR = $(TEST_SRC_DIR)/test_objs

SRC = $(wildcard $(SRC_DIR)/s21_*.c)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/test*.c)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o))) # ./objs/name.o
TEST_OBJ = $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))
GCOV_OBJ = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

INCLD = $(wildcard $(INCLD_DIR)/*.h)
TEST_INCLD = $(wildcard $(TEST_INCLD_DIR)/*.h)

MKDIR = mkdir -p
RM = rm -f
RMDIR = rm -rf

GCOV_DIR = $(SRC_DIR)/gcov_report
GCOV_OBJ_DIR = $(GCOV_DIR)/objs

$(NAME): $(OBJ)
	ar rc $(NAME) $?
	ranlib $(NAME)


$(TEST): $(NAME) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(TEST_LIBS) -L. $(NAME) -o $@
	./test


all: $(NAME) $(TEST)


clean:
	$(RM) $(OBJ)
	$(RMDIR) $(OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(RM) $(TEST_OBJ)
	$(RMDIR) $(TEST_OBJ_DIR)
	$(RM) -r $(GCOV_OBJ_DIR)
	$(RM) -r $(GCOV_DIR)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD)  # creat object file
	@$(MKDIR) $(@D) 
	$(CC) $(FLAGS) -I$(INCLD_DIR) -c $< -o $@ 


$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c  $(TEST_INCLD)
	@$(MKDIR) $(@D)
	$(CC) $(FLAGS) -I$(INCLD_DIR) -I$(TEST_INCLD_DIR) -c $< -o $@


$(GCOV_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD)
	@$(MKDIR) $(@D)
	$(CC) $(FLAGS) $(GCOV_FLAGS) -I$(INCLD_DIR) -c $< -o $@


$(REPORT): $(GCOV_OBJ) $(TEST_OBJ)
	$(CC) $(GCOV_FLAGS) $(GCOV_OBJ) $(TEST_OBJ)  \
		-o $(GCOV_DIR)/test_coverage $(TEST_LIBS)
	./$(GCOV_DIR)/test_coverage;
	gcov $(GCOV_OBJ_DIR)/*.gcno;
	@mv *.gcov $(GCOV_OBJ_DIR);
	lcov -c -t "s21_decimal" -o $(GCOV_DIR)/report.info -d $(GCOV_OBJ_DIR) \
		--rc lcov_branch_coverage=1;
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/report.info --rc lcov_branch_coverage=1


format:
	cp ../materials/linters/.clang-format $(SRC_DIR)/.
	clang-format -i $(SRC) $(TEST_SRC) $(INCLD) $(TEST_INCLD)
	$(RM) $(SRC_DIR)/.clang-format
