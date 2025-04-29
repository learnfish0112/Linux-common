Srcs := $(wildcard *.c)
Exes := $(patsubst %.c, %, $(Srcs))
CFLAGS := -g

all: $(Exes)
%: %.c
	gcc $^ -o $@ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(Exes)
