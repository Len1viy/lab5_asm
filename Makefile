AS = /usr/bin/nasm
LD = /usr/bin/ld

CCFLAGS = -c -O3


ASFLAGS = -f elf64
LDFLAGS = -static -z noexecstack

LIBPATH = -L /lib/gcc/x86_64-unknown-linux-gnu/13.2.0 -L /lib
OBJPATH = /usr/lib

LIBS = -lgcc -lgcc_eh -lc -lm

PREOBJ = $(OBJPATH)/crt1.o $(OBJPATH)/crti.o
POSTOBJ = $(OBJPATH)/crtn.o

SRCS = lab.c image.c imageasm.s
HEAD = image.h
OBJS = lab.o image.o imageasm.o


EXE = lab

all: $(SRCS) $(EXE)

clean:
	rm -rf $(EXE) $(OBJS)

$(OBJS): $(HEAD)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $(LIBPATH) $(PREOBJ) $(OBJS) $(POSTOBJ) -\( $(LIBS) -\) -o $@

.c.o:
	$(CC) $(CCFLAGS) $< -o $@

.s.o:
	$(AS) $(ASFLAGS) $< -o $@


