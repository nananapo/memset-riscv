#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void *memset_1(void *str, int c, size_t n);
void *memset_2(void *str, int c, size_t n);
void *memset_3(void *str, int c, size_t n);

// Usage
//  -m          : make misaligned pointer
//  memset_num  : number of memset_N
//  c           : argument of memset
//  n           : argument of memset
void print_usage(char* prog) {
    printf("Usage: %s [-m] memset_num c n\n", prog);
    exit(1);
}

int check(void *ptr, int c, size_t n){
    for (size_t i=0; i<n; i++){
        if (*(char*)ptr != c % 256){
            return 1;
        }
    }
    return 0;
}

void check_exit_if_fail(void* ret, void *ptr, int c, size_t n) {
    if (ret == ptr && check(ptr, c, n)){
        printf("Fail!\n");
        exit(1);
    }
}

typedef void *(*memset_func_t)(void *, int, size_t);

int main(int argc, char **argv) {
    // read arguments
    if (argc < 4) print_usage(argv[0]);
    
    int     ac  = 1;
    bool    make_misalign = false;
    if (strcmp("-m", argv[ac]) == 0) {
        make_misalign = true;
        ac += 1;
        if (argc < 5) print_usage(argv[0]);
    }

    int     sel = atoi(argv[ac++]);
    int     c   = atoi(argv[ac++]);
    size_t  n   = atoi(argv[ac++]);

    // select memset
    memset_func_t func = NULL;
    switch (sel) {
        case 1: func = memset_1; break;
        case 2: func = memset_2; break;
        case 3: func = memset_3; break;
        default: {
            printf("memset_%d is not found\n", sel);
            exit(1);
        }
    }

    // call
    if (!make_misalign) {
        // create pointer
        uintptr_t ptr = (uintptr_t)malloc(sizeof(char) * (n * 2));
        ptr = (ptr + 3) / 4 * 4;
        // call and check 
        void* ret = func((void *)ptr, c, n);
        check_exit_if_fail(ret, (void *)ptr, c, n);
    } else {
        for (int i = 0; i < 4; i++) {
            // create misaligned pointer
            char*   ptr = (char *)malloc(sizeof(char) * (n * 2));
            ptr += i;
            // call and check 
            void* ret = func((void *)ptr, c, n);
            check_exit_if_fail(ret, (void *)ptr, c, n);
        }
    }
    
    return 0;
}