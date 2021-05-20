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

struct Person Person_create(char *name, int age, int height, int weight)
{
    struct Person who;

    who.name = strdup(name);
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void person_print(struct Person who){
    printf("Name: %s \n",who.name);
    printf("Age: %d \n",who.age);
    printf("Height: %d \n",who.height);
    printf("Weight: %d \n",who.weight);
}

int main(int argc, char *argv[])
{

    struct Person Joe = Person_create("Joe",30,120,150);
    struct Person Frank = Person_create("Frank",24,130,140);

    person_print(Joe);

    person_print(Frank);

    Joe.age += 20;
    Joe.height -= 2;
    Joe.weight +=40;

    person_print(Joe);

    Frank.age += 20;
    Frank.weight += 20;

    person_print(Frank);


    return 0;
}
