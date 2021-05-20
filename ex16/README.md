# Exercise 16. Structs And Pointers to Them

## How to Break It

### Try passing NULL to Person_destroy see what it does. If it doesn’t abort, then you must not have the -g option in your Makefile's CFLAGS.

```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));

    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void person_destroy(struct Person *who){
    assert(who != NULL);

    free(who->name);
    free(who);
}

void person_print(struct Person *who){
    printf("Name: %s \n",who->name);
    printf("Age: %d \n",who->age);
    printf("Height: %d \n",who->height);
    printf("Weight: %d \n",who->weight);
}

int main(int argc, char *argv[])
{

    struct Person *Joe = Person_create("Joe",30,120,150);
    struct Person *Frank = Person_create("Frank",24,130,140);

    printf("Joe at position : %p ",Joe);
    person_print(Joe);

    printf("Frank at position : %p ",Frank);
    person_print(Frank);

    Joe->age += 20;
    Joe->height -= 2;
    Joe->weight +=40;

    person_print(Joe);

    Frank->age += 20;
    Frank->weight += 20;

    person_print(Frank);

    person_destroy(NULL);
    person_destroy(Frank);

    return 0;
}
```

```
(gdb) run
Starting program: /home/omama/Documents/Cprograms/ex16/ex16 
Joe at position : 0x5555555592a0 Name: Joe 
Age: 30 
Height: 120 
Weight: 150 
Frank at position : 0x5555555592e0 Name: Frank 
Age: 24 
Height: 130 
Weight: 140 
Name: Joe 
Age: 50 
Height: 118 
Weight: 190 
Name: Frank 
Age: 44 
Height: 130 
Weight: 160 
ex16: ex16.c:29: person_destroy: Assertion `who != NULL' failed.

Program received signal SIGABRT, Aborted.
__GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:50
50      ../sysdeps/unix/sysv/linux/raise.c: No such file or directory.
```

### Forget to call Person_destroy at the end, and then run it under the debugger to see it report that you forgot to free the memory. Figure out the options you need to pass to the debugger to get it to print how you leaked this memory.

```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));

    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void person_destroy(struct Person *who){
    assert(who != NULL);

    free(who->name);
    free(who);
}

void person_print(struct Person *who){
    printf("Name: %s \n",who->name);
    printf("Age: %d \n",who->age);
    printf("Height: %d \n",who->height);
    printf("Weight: %d \n",who->weight);
}

int main(int argc, char *argv[])
{

    struct Person *Joe = Person_create("Joe",30,120,150);
    struct Person *Frank = Person_create("Frank",24,130,140);

    printf("Joe at position : %p ",Joe);
    person_print(Joe);

    printf("Frank at position : %p ",Frank);
    person_print(Frank);

    Joe->age += 20;
    Joe->height -= 2;
    Joe->weight +=40;

    person_print(Joe);

    Frank->age += 20;
    Frank->weight += 20;

    person_print(Frank);

    person_destroy(Joe);
    // person_destroy(Frank);

    return 0;
}

```
--leak-check=full can also be used for detail
```
$ valgrind ./ex16
==41197== Memcheck, a memory error detector
==41197== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==41197== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==41197== Command: ./ex16
==41197== 
Joe at position : 0x4a52040 Name: Joe 
Age: 30 
Height: 120 
Weight: 150 
Frank at position : 0x4a520f0 Name: Frank 
Age: 24 
Height: 130 
Weight: 140 
Name: Joe 
Age: 50 
Height: 118 
Weight: 190 
Name: Frank 
Age: 44 
Height: 130 
Weight: 160 
==41197== 
==41197== HEAP SUMMARY:
==41197==     in use at exit: 58 bytes in 4 blocks
==41197==   total heap usage: 5 allocs, 1 frees, 1,082 bytes allocated
==41197== 
==41197== LEAK SUMMARY:
==41197==    definitely lost: 48 bytes in 2 blocks
==41197==    indirectly lost: 10 bytes in 2 blocks
==41197==      possibly lost: 0 bytes in 0 blocks
==41197==    still reachable: 0 bytes in 0 blocks
==41197==         suppressed: 0 bytes in 0 blocks
==41197== Rerun with --leak-check=full to see details of leaked memory
==41197== 
==41197== For lists of detected and suppressed errors, rerun with: -s
==41197== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


### Forget to free who->name in Person_destroy and compare the output. Again, use the right options to see how the debugger tells you exactly where you messed up.

```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));

    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void person_destroy(struct Person *who){
    assert(who != NULL);

    // free(who->name);
    free(who);
}

void person_print(struct Person *who){
    printf("Name: %s \n",who->name);
    printf("Age: %d \n",who->age);
    printf("Height: %d \n",who->height);
    printf("Weight: %d \n",who->weight);
}

int main(int argc, char *argv[])
{

    struct Person *Joe = Person_create("Joe",30,120,150);
    struct Person *Frank = Person_create("Frank",24,130,140);

    printf("Joe at position : %p ",Joe);
    person_print(Joe);

    printf("Frank at position : %p ",Frank);
    person_print(Frank);

    Joe->age += 20;
    Joe->height -= 2;
    Joe->weight +=40;

    person_print(Joe);

    Frank->age += 20;
    Frank->weight += 20;

    person_print(Frank);

    person_destroy(Joe);
    person_destroy(Frank);

    return 0;
}
```


```
$ valgrind --leak-check=full ./ex16
==41957== Memcheck, a memory error detector
==41957== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==41957== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==41957== Command: ./ex16
==41957== 
Joe at position : 0x4a52040 Name: Joe 
Age: 30 
Height: 120 
Weight: 150 
Frank at position : 0x4a520f0 Name: Frank 
Age: 24 
Height: 130 
Weight: 140 
Name: Joe 
Age: 50 
Height: 118 
Weight: 190 
Name: Frank 
Age: 44 
Height: 130 
Weight: 160 
==41957== 
==41957== HEAP SUMMARY:
==41957==     in use at exit: 10 bytes in 2 blocks
==41957==   total heap usage: 5 allocs, 3 frees, 1,082 bytes allocated
==41957== 
==41957== 4 bytes in 1 blocks are definitely lost in loss record 1 of 2
==41957==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==41957==    by 0x48FF50E: strdup (strdup.c:42)
==41957==    by 0x109221: Person_create (ex16.c:20)
==41957==    by 0x10933E: main (ex16.c:45)
==41957== 
==41957== 6 bytes in 1 blocks are definitely lost in loss record 2 of 2
==41957==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==41957==    by 0x48FF50E: strdup (strdup.c:42)
==41957==    by 0x109221: Person_create (ex16.c:20)
==41957==    by 0x10935D: main (ex16.c:46)
==41957== 
==41957== LEAK SUMMARY:
==41957==    definitely lost: 10 bytes in 2 blocks
==41957==    indirectly lost: 0 bytes in 0 blocks
==41957==      possibly lost: 0 bytes in 0 blocks
==41957==    still reachable: 0 bytes in 0 blocks
==41957==         suppressed: 0 bytes in 0 blocks
==41957== 
==41957== For lists of detected and suppressed errors, rerun with: -s
==41957== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

```

### This time, pass NULL to Person_print and see what the debugger thinks of that. You’ll figure out that NULL is a quick way to crash your program.

```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));

    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void person_destroy(struct Person *who){
    assert(who != NULL);

    free(who->name);
    free(who);
}

void person_print(struct Person *who){
    printf("Name: %s \n",who->name);
    printf("Age: %d \n",who->age);
    printf("Height: %d \n",who->height);
    printf("Weight: %d \n",who->weight);
}

int main(int argc, char *argv[])
{

    struct Person *Joe = Person_create("Joe",30,120,150);
    struct Person *Frank = Person_create("Frank",24,130,140);

    printf("Joe at position : %p ",Joe);
    person_print(Joe);

    printf("Frank at position : %p ",Frank);
    person_print(Frank);

    Joe->age += 20;
    Joe->height -= 2;
    Joe->weight +=40;

    person_print(Joe);

    Frank->age += 20;
    Frank->weight += 20;

    person_print(NULL);

    person_destroy(Joe);
    person_destroy(Frank);

    return 0;
}
```
GDB

```
(gdb) run
Starting program: /home/omama/Documents/Cprograms/ex16/ex16 
Joe at position : 0x5555555592a0 Name: Joe 
Age: 30 
Height: 120 
Weight: 150 
Frank at position : 0x5555555592e0 Name: Frank 
Age: 24 
Height: 130 
Weight: 140 
Name: Joe 
Age: 50 
Height: 118 
Weight: 190 

Program received signal SIGSEGV, Segmentation fault.
0x00005555555552b8 in person_print (who=0x0) at ex16.c:36
36          printf("Name: %s \n",who->name);
```

Valgrind

```
$ valgrind --leak-check=full ./ex16
==42341== Memcheck, a memory error detector
==42341== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==42341== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==42341== Command: ./ex16
==42341== 
Joe at position : 0x4a52040 Name: Joe 
Age: 30 
Height: 120 
Weight: 150 
Frank at position : 0x4a520f0 Name: Frank 
Age: 24 
Height: 130 
Weight: 140 
Name: Joe 
Age: 50 
Height: 118 
Weight: 190 
==42341== Invalid read of size 8
==42341==    at 0x1092B8: person_print (ex16.c:36)
==42341==    by 0x109423: main (ex16.c:63)
==42341==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==42341== 
==42341== 
==42341== Process terminating with default action of signal 11 (SIGSEGV)
==42341==  Access not within mapped region at address 0x0
==42341==    at 0x1092B8: person_print (ex16.c:36)
==42341==    by 0x109423: main (ex16.c:63)
==42341==  If you believe this happened as a result of a stack
==42341==  overflow in your program's main thread (unlikely but
==42341==  possible), you can try to increase the size of the
==42341==  main thread stack using the --main-stacksize= flag.
==42341==  The main thread stack size used in this run was 8388608.
==42341== 
==42341== HEAP SUMMARY:
==42341==     in use at exit: 58 bytes in 4 blocks
==42341==   total heap usage: 5 allocs, 1 frees, 1,082 bytes allocated
==42341== 
==42341== LEAK SUMMARY:
==42341==    definitely lost: 0 bytes in 0 blocks
==42341==    indirectly lost: 0 bytes in 0 blocks
==42341==      possibly lost: 0 bytes in 0 blocks
==42341==    still reachable: 58 bytes in 4 blocks
==42341==         suppressed: 0 bytes in 0 blocks
==42341== Reachable blocks (those to which a pointer was found) are not shown.
==42341== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==42341== 
==42341== For lists of detected and suppressed errors, rerun with: -s
==42341== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)
```