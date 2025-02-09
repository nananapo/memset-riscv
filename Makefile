OUTPUT=a.out
GCC=riscv64-unknown-elf-gcc

compile:
	${GCC} memset_1.S memset_2.S memset_3.S test.c -o ${OUTPUT}

clean:
	rm ${OUTPUT}

# export PATH=$PATH:/home/kanataso/Documents/riscv-gnu-toolchain/bin
# ../spike/bin/spike ../riscv-pk/build/pk a.out
