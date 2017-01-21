src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))

ALL: $(target)

$(target): $(src)
	gcc $< -o $@

clean:
	-rm -rf $(target)

.PHONY: clean
