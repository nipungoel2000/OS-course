mknod keyboard c 251 5 
      (file name) (character special) (major device number) (minor device number)

a)mknod myfifo p

b)mkfifo myfifo

c)strace mkfifo myfifo (strace -c mkfifo myfifo)
We can see that myfifo internally calls mknod and so mknod is faster than mkfifo.
