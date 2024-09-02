CC=gcc
CFLAGS=-Wall -Wextra -pedantic -Ofast


INCLUDE_PATH=
LIB_PATH=


ifeq ($(UNAME), Linux)	
	INCLUDE_PATH+=/usr/include/
	LIB_PATH+=/usr/lib64/
else
	INCLUDE_PATH+=/usr/include/
	LIB_PATH+=/usr/lib/
endif


TARGET=libcontainer.a
CACHE=.cache
OUTPUT=$(CACHE)/release

TEST += test.o
TEST += vector_test.o


T_OBJ=$(addprefix $(CACHE)/,$(TEST))


exec: env $(T_OBJ)
	$(CC) $(T_OBJ) $(OBJ) $(LIBS) -o $(OUTPUT)/test
	$(OUTPUT)/test



%.o:
	$(CC) $(CFLAGS) -c $< -o $@


-include dep.list



.PHONY: env dep clean


dep:
	$(CC) -MM test/*.c | sed 's|[a-zA-Z0-9_-]*\.o|$(CACHE)/&|' > dep.list


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(OUTPUT)

install:
	cp -vr src/interface $(INCLUDE_PATH)

clean: 
	rm -rvf $(OUTPUT)
	rm -vf $(CACHE)/*.o



