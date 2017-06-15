all: cp fork pipe run memory wr
cp: cp_file.c  
	gcc -o cp_file cp_file.c
fork: forkWait.c
	gcc -o forkWait forkWait.c
pipe: pipe.c
	gcc -o pipe pipe.c
run: run.c
	gcc -o run run.c
memory: shmem.c 
	gcc -o shmem shmem.c
wr: wr_file.c
	gcc -o wr_file wr_file.c
