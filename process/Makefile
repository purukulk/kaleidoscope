obj-m += current.o
obj-m += family.o
obj-m += three.o
obj-m += files.o
obj-m += rename.o
obj-m += ps.o
obj-m += test_ps.o
obj-m += pid.o
obj-m += pstree.o
obj-m += sigkill.o
obj-m += kthread.o
obj-m += kthread_cpu.o
obj-m += sighand.o
obj-m += block_kill.o
obj-m += lockit.o
obj-m += exit.o
obj-m += threads.o
obj-m += kthr_atomic.o
obj-m += temp.o
obj-m += child_testing.o
obj-m += pids.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
