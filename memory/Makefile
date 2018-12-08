obj-m += vma.o
obj-m += numproc.o
obj-m += read_kmem.o
obj-m += pc.o
obj-m += buddy.o
obj-m += rss.o
obj-m += mmap.o
obj-m += lock.o
obj-m += mem_values.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
