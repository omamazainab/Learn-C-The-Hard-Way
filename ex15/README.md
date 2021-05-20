# Exercise 15: Pointers Dreaded Pointers

## How to Break It

### Try to make cur_age point at names. You’ll need to use a C cast to force it, so go look that up and try to figure it out.

```c

#include <stdio.h>

int main(int argc, char *argv[]){ 
    
    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", names[i], ages[i]);

    //set up pointers to the start of the array

    int *curr_age = (int*)names;
    char **curr_name = names;

    //second way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));

    //third way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);

    //fourth way of using pointers
    for (curr_age = ages, curr_name = names; (curr_age - ages) < count; curr_name++, curr_age++)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);

    return 0;
}
```

```
$ ./ex15
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has -210673660 years alive.
Zainab has 21987 years alive.
Ali has -210673654 years alive.
Qureshi has 21987 years alive.
Omama has -210673660 years alive.
Zainab has 21987 years alive.
Ali has -210673654 years alive.
Qureshi has 21987 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
```
### In the final for-loop, try getting the math wrong in weird ways.

```c 
#include <stdio.h>

int main(int argc, char *argv[])
{

    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", names[i], ages[i]);

    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;

    //second way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));

    //third way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);

    //fourth way of using pointers
    for (curr_age = ages, curr_name = names; (curr_age - ages) <= count; curr_name++, curr_age++)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);

    return 0;
}

```

```
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
 has 1845354500 years alive.
```

```c
#include <stdio.h>

int main(int argc, char *argv[])
{

    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", names[i], ages[i]);

    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;

    //second way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));

    //third way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);

    //fourth way of using pointers
    for (curr_age = ages, curr_name = names; (curr_age - ages) < count; curr_name--, curr_age++)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);

    return 0;
}
```

```
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Segmentation fault (core dumped)
```

### Try rewriting the loops so that they start at the end of the arrays and go to the beginning. This is harder than it looks. 

```c
#include <stdio.h>

int main(int argc, char *argv[])
{

    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    for (int i = count-1; i >= 0; i--)
        printf("%s has %d years alive.\n", names[i], ages[i]);

    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;

    //second way of using pointers
    for (int i = count-1; i >= 0; i--)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));

    //third way of using pointers
    for (int i = count-1; i >= 0; i--)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);

    // //fourth way of using pointers
    for (curr_age = ages + count -1, curr_name = names +count-1; (curr_age - ages) >= 0; curr_name--, curr_age--)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);

    return 0;
}
```

```
Qureshi has 33 years alive.
Ali has 25 years alive.
Zainab has 17 years alive.
Omama has 11 years alive.
Qureshi has 33 years alive.
Ali has 25 years alive.
Zainab has 17 years alive.
Omama has 11 years alive.
Qureshi has 33 years alive.
Ali has 25 years alive.
Zainab has 17 years alive.
Omama has 11 years alive.
Qureshi has 33 years alive.
Ali has 25 years alive.
Zainab has 17 years alive.
Omama has 11 years alive.
```

## Extra Credit

### Rewrite all of the arrays in this program as pointers.

```c

#include <stdio.h>

int main(int argc, char *argv[]){ 
    
    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(names + i), *(ages + i) );

    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;

    //second way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));

    //third way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));

    //fourth way of using pointers
    for (curr_age = ages, curr_name = names; (curr_age - ages) < count; curr_name++, curr_age++)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);

    return 0;
}
```

```
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
```
### Rewrite all of the pointers as arrays.

```c

#include <stdio.h>

int main(int argc, char *argv[]){ 
    
    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", names[i], ages[i] );

    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;

    //second way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);

    //third way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);

    //fourth way of using pointers
    for (curr_age = ages, curr_name = names; (curr_age - ages) < count; curr_name++, curr_age++)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);

    return 0;
}
```
```
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
```

### Go back to some of the other programs that use arrays and try to use pointers instead.

ex14

```c
#include <stdio.h>
#include <ctype.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    
    for (i = 0; i < argc; i++) {
        print_letters(*(argv + i));
    }
}

void print_letters(char arg[])
{
    int i = 0;
    
    for (i = 0; *(arg+i) != '\0'; i++) {
        char ch = *(arg + i);
        
        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }
    
    printf("\n");
}

int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
```

```
'e' == 101 'x' == 120 
```

### Process command line arguments using just pointers, similar to how you did names in this one.

using same code I used in last one

```
$ ./ex15 hello omama
'e' == 101 'x' == 120 
'h' == 104 'e' == 101 'l' == 108 'l' == 108 'o' == 111 
'o' == 111 'm' == 109 'a' == 97 'm' == 109 'a' == 97 
```

### Play with combinations of getting the value of and the address of things.


```c

int main(int argc, char *argv[])
{
    char *names[] = { "Omama", "Zainab" , "Ali" };

    int count = sizeof(names)/sizeof(char*);
    for(int i=0;i < count; i++ )
        printf("%d: value == %s position == %p \n",i,names[i], names + i);

    return 0;
}
```

```
0: value == Omama position == 0x7ffe23918750 
1: value == Zainab position == 0x7ffe23918758 
2: value == Ali position == 0x7ffe23918760 
```

### Add another for-loop at the end that prints out the addresses that these pointers are using. You’ll need the %p format for printf.

```c
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){ 
    
    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", names[i], ages[i]);

    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;

    //second way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));

    //third way of using pointers
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);

    //fourth way of using pointers
    for (curr_age = ages, curr_name = names; (curr_age - ages) < count; curr_name++, curr_age++)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);

    for (int i = 0; i < count; i++)
        printf(" name: %s : %p , age: %d : %p \n",names[i],names + i, ages[i],ages+i);

    return 0;
}
```

```
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
 name: Omama : 0x7ffc3455be70 , age: 11 : 0x7ffc3455be60 
 name: Zainab : 0x7ffc3455be78 , age: 17 : 0x7ffc3455be64 
 name: Ali : 0x7ffc3455be80 , age: 25 : 0x7ffc3455be68 
 name: Qureshi : 0x7ffc3455be88 , age: 33 : 0x7ffc3455be6c 
```

### Rewrite this program to use a function for each of the ways you’re printing out things. Try to pass pointers to these functions so that they work on the data. Remember you can declare a function to accept a pointer, but just use it like an array.

```c
#include <stdio.h>
#include <ctype.h>

void firstWay(int count,char *names[],int ages[]);
void secondWay(int count,char *names[],int ages[]);
void thirdWay(int count,char *names[],int ages[]);
void fourthWay(int count,char *names[],int ages[]);


void firstWay(int count,char *names[],int ages[]){
    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", names[i], ages[i]);
}

void secondWay(int count,char *names[],int ages[]){
    
    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;

    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));
}

void thirdWay(int count,char *names[],int ages[]){

    int *curr_age = ages;
    char **curr_name = names;

    for (int i = 0; i < count; i++)
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);
}

void fourthWay(int count,char *names[],int ages[]){
    int *curr_age = ages;
    char **curr_name = names;
    for (; (curr_age - ages) < count; curr_name++, curr_age++)
        printf("%s has %d years alive.\n", *curr_name, *curr_age);
}


int main(int argc, char *argv[]){ 
    
    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);

    //first way of using pointers
    firstWay(count,names,ages);

    //second way of using pointers
    secondWay(count,names,ages);

    //third way of using pointers
    thirdWay(count,names,ages);

    //fourth way of using pointers
    fourthWay(count,names,ages);

    return 0;
}
```

```
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
```

### Change the for-loops to while-loops and see what works better for which kind of pointer usage.

```c
#include <stdio.h>

int main(int argc, char *argv[])
{

    int ages[] = {11, 17, 25, 33};
    char *names[] = {"Omama", "Zainab", "Ali", "Qureshi"};

    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    //first way of using pointers
    while (i < count)
    {
        printf("%s has %d years alive.\n", names[i], ages[i]);
        i++;
    }
    //set up pointers to the start of the array

    int *curr_age = ages;
    char **curr_name = names;
    i = 0;
    //second way of using pointers
    while (i < count)
    {
        printf("%s has %d years alive.\n", *(curr_name + i), *(curr_age + i));
        i++;
    }

    //third way of using pointers
    while (i < count)
    {
        printf("%s has %d years alive.\n", curr_name[i], curr_age[i]);
        i++;
    }

    //fourth way of using pointers
    while ((curr_age - ages) < count)
    {
        printf("%s has %d years alive.\n", *curr_name, *curr_age);
        curr_name++;
        curr_age++;
    }
    return 0;
}
```

```
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
Omama has 11 years alive.
Zainab has 17 years alive.
Ali has 25 years alive.
Qureshi has 33 years alive.
```
