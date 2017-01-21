src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))

ALL: $(target)

$(target): %: %.c
	gcc $< -o $@

clean:
	-rm -rf $(target)

.PHONY: clean
