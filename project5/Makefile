CFLAGS=-Wall -O9 -std=c99 -Wno-unused-function
LDFLAGS=
LDLIBS= -lc -lopencv_core -lopencv_highgui -lopencv_imgproc

all: solve_image  make_steg

clean:
	rm *.o

OBJS=image_to_array.o

%.o: %.c
	gcc -g -c $(CFLAGS) $<

make_steg: $(OBJS) make_steg.o 
	gcc $(LDFLAGS) -o make_steg $(OBJS) make_steg.o $(LDLIBS)

solve_image: $(OBJS) solve_image.o
	gcc $(LDFLAGS) -o solve_image $(OBJS) solve_image.o $(LDLIBS)

