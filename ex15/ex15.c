#include <stdio.h>

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

    return 0;
}