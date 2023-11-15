NAME        := utils
LIBNAME     := lib$(NAME).a

VG          := valgrind
VGLOG       := RESULT_VALGRIND.txt
VGFLAGS     := \
		--vgdb=no \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=$(VGLOG)

PWD         := $(shell pwd)
SRC_DIR     := src
BUILD_DIR   := .build
TEST_DIR    := .tests

SRC         := matrix.c obj_parser.c
SRC         := $(SRC:%=$(SRC_DIR)/%)
OBJ         := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP         := $(OBJ:.o=.d)

CC          := gcc
CFLAGS      := -std=c11 -Wall -Wextra -Werror
CPPFLAGS    := -I include
ARFLAGS     := -rcs

AR          := ar
RM          := rm -rf

ifeq ($(shell uname), Linux)
  CKFLAGS   := -lcheck -lm -lpthread -lrt -lsubunit
else
  CKFLAGS   := -lcheck -lm -lpthread
endif

all: $(LIBNAME)

$(LIBNAME): $(OBJ)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ)
	$(info CREATED $(LIBNAME))

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

$(VG): vg_clean
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) $@.c -o $@
	CK_FORK=no $(VG) $(VGFLAGS) ./$@

tests: report_clean
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP $(CKFLAGS) -lgcov --coverage $@.c $(SRC) -o $(TEST_DIR)/$@
	$(TEST_DIR)/$@

gcov_report: tests
	lcov -t "$<" -o report.info -c -d .
	lcov --remove report.info $(PWD)/tests.c -o report.info

docker_test:
	docker build -t "$(VG):1.0" . && docker run --rm -v $$PWD:/tmp -w /tmp $(VG):1.0

clean: vg_clean report_clean
	$(RM) $(LIBNAME) $(BUILD_DIR) $(TEST_DIR)

vg_clean:
	$(RM) $(VG) $(VGLOG) $(VG).dSYM

report_clean:
	$(RM) *.gcno *gcda *.gcov gcov_report.* report report.info

get-%:
	$(info $($*))
	@true
