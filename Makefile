obj-m += hello.o
obj-m += version.o
obj-m += minmax3.o
obj-m += metadata.o
obj-m += search_mod.o
obj-m += list.o
obj-m += crash.o
obj-m += datetime.o
obj-m += export.o
obj-m += export_2.o
obj-m += array.o
obj-m += sort.o
obj-m += elaptime.o
obj-m += log.o
obj-m += nsyscalls.o
obj-m += sizes.o
obj-m += cr.o
obj-m += current.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
