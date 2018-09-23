obj-m += current.o
obj-m += family.o
obj-m += three.o
obj-m += numproc.o
obj-m += files.o
obj-m += ps.o
obj-m += pid.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
