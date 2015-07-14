
SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:%.c=../obj/%.o)

all: dirs ../bin/esed

dirs:
	@mkdir -p ../obj

../bin/esed: $(OBJ_FILES)
	@echo Linking esed...
	@gcc $(OBJ_FILES) -o $@
	
$(OBJ_FILES): ../obj/%.o: %.c
	@echo Compiling $<...
	@gcc $< -c -o $@

clean:
	@echo Cleaning...
	@rm -rf ../obj
	@rm ../bin/esed

install: ../bin/esed
	@cp ../bin/esed /usr/local/bin
