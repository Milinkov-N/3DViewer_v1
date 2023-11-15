NAME         := 3DViewer

PWD          := $(shell pwd)
BUILD_DIR    := build

LIBS         := utils
LIBNAMES     := $(addprefix lib,$(LIBS))
LIBS_TARGET  := libutils/libutils.a
LIBS_RPT     := $(LIBNAMES:%=%/report.info)
LIBS_INC     := $(LIBNAMES:%=%/include)
INCS         := include $(LIBS_INC)
DIST         := $(addprefix $(NAME)/,v-shader.glsl f-shader.glsl .config)


CC           := gcc
RM           := rm -rf
CFLAGS       := -std=c11 -Wall -Wextra -Werror
CPPFLAGS     := $(addprefix -I,$(INCS))
LDFLAGS      := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS       := $(addprefix -l,$(LIBS))

ifeq ($(shell uname), Linux)
  CKFLAGS   := -lcheck -lm -lpthread -lrt -lsubunit
else
  CKFLAGS   := -lcheck -lm -lpthread
endif

all: run

build: $(LIBS_TARGET)
	mkdir -p $(BUILD_DIR)
	cp $(NAME)/$(NAME).pro $(BUILD_DIR)
	cp $(DIST) $(BUILD_DIR)
	cd $(BUILD_DIR); qmake $(NAME).pro
	make -C $(BUILD_DIR)

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

run: build
	 ./build/$(NAME).app/Contents/MacOS/$(NAME)

install: build
	cp -rf $(BUILD_DIR)/$(NAME).app $(HOME)/Applications/
	# make clean

uninstall: 
	rm -rf $(HOME)/Applications/$(NAME).app

dvi:
	open dvi.html

dist: build
	tar -cvf ./dist/$(NAME).tar build/$(NAME).app build/f-shader.glsl build/v-shader.glsl build/.config dvi.html
	gzip ./dist/$(NAME).tar

tests: report_clean $(LIBNAMES:%=%-tests)
	@true

# for almetate!!!
tests_linux: clean libutils/tests.c $(LIBS_TARGET)
	gcc -O0 -g $(CFLAGS) libutils/tests.c libutils/src/matrix.c libutils/src/obj_parser.c -o run $(CKFLAGS) -lgcov --coverage
	./run

report_linux: tests_linux
	lcov -t "tests_linux" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

cppcheck:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n libutils/src/*.c libutils/include/utils*.h
	rm .clang-format
# for almetate!!!

%-tests:
	$(MAKE) -C $* tests

gcov_report: $(LIBNAMES:%=%-gcov_report)
	genhtml -o report $(LIBS_RPT)
	open ./report/index.html

%-gcov_report:
	$(MAKE) -C $* gcov_report

rebuild: clean all

clean: report_clean $(LIBNAMES:%=%-clean)
	$(RM)                           \
		$(BUILD_DIR)/                 \
		$(BUILD_DIR)/*.app            \
		$(BUILD_DIR)/Makefile         \
		$(BUILD_DIR)/*.cpp            \
		$(BUILD_DIR)/*.h              \
		$(BUILD_DIR)/.qmake*          \
		$(BUILD_DIR)/*.pro            \
		$(BUILD_DIR)/*.o              \
		build-$(NAME)-Desktop*        \
		$(LIBS_TARGET)                \
		$(LIBNAMES:%=%/.$(BUILD_DIR)) \
		$(OBJ)						  \
		dist/*						  \
		run

report_clean:
	$(RM) *.gcno *gcda *.gcov gcov_report.* report report.info

%-clean:
	$(MAKE) -C $* clean

.PHONY: clean vg_clean report_clean dist
