
SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:%.c=../obj/%.o)

C_FLAGS = -std=c99 -g

all: dirs ../bin/esed

dirs:
	@mkdir -p ../obj
	@mkdir -p ../bin

../bin/esed: $(OBJ_FILES) 
	@echo Linking esed...
	@gcc $(OBJ_FILES) -o $@
	
$(OBJ_FILES): ../obj/%.o: %.c
	@echo Compiling $<...
	@gcc $(C_FLAGS) $< -c -o $@

clean:
	@echo Cleaning...
	@rm -rf ../obj
	@rm -f ../bin/esed && echo esed directory successfully cleaned!
	
install: dirs ../bin/esed
	@echo Installing esed...
	@cp ../bin/esed /usr/local/bin && echo esed successfully installed!
	
uninstall:
	@echo Uninstalling esed...
	@rm -f /usr/local/bin/esed && echo esed successfully uninstalled!
	
