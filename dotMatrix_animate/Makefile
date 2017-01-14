CC=gcc
#IDIR=../include
#LDIR=../lib
CFLAGS=
LIBS=-lwiringPi
XDIR=../../builds
ODIR=objs
DEPS=

SRCS=dot_matrix_animate.c
OBJS=$(patsubst %,$(ODIR)/%,$(SRCS:.c=.o))

all:build clean

$(ODIR)/%.o:%.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c $< -o $@ $(CFLAGS)

build:$(OBJS)
	mkdir -p $(XDIR)
	$(CC) -o $(XDIR)/dotMatrixAnimate $^ $(CFLAGS) $(LIBS)
	echo "to launch \ncd $(XDIR)\n./dotMatrixAnimate"	
clean:
	rm -rf $(ODIR)
