obj-m += hello.o
obj-m += version.o
obj-m += minmax3.o
obj-m += metadata.o
obj-m += search_mod.o
obj-m += list.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
