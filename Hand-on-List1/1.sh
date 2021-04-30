#! /bin/bash
rm hrdlnk
rm sftlnk
rm myfifo
touch file1

#a)Soft link
ln -s file1 sftlnk
ls -il

#b) Hard link
ln file1 hrdlnk
ls -il

#c) FIFO(named pipe)
mkfifo myfifo
ls -il