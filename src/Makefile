
MAKEFLAGS += --silent

CC = gcc  # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -fstack-protector-all -fstack-protector -D_FORTIFY_SOURCE=2 -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-security -Wnull-dereference -Wstack-protector -Wtrampolines -Walloca -Wvla -Warray-bounds=2 -Wimplicit-fallthrough=3 -Wtraditional-conversion -Wshift-overflow=2 -Wcast-qual -Wstringop-overflow=4 -Wconversion -Warith-conversion -Wlogical-op -Wduplicated-cond -Wduplicated-branches -Wformat-signedness -Wshadow -Wstrict-overflow=4 -Wundef -Wswitch-default -Wswitch-enum -Wstack-usage=1000000 -Wcast-align=strict  # C flags
LDFLAGS = -shared  -ldl -Wl,-z,relro,-z,now# linking flags
RM = rm -f   # rm command
TARGET_LIB = libfakehostname.so  # fakehostname lib

SRCS = fakehostname.c  # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
