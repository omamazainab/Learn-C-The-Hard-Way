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

// #include <stdio.h>
// #include <assert.h>
// #include <stdlib.h>
// #include <string.h>

// struct Person
// {
//     char *name;
//     int age;
//     int height;
//     int weight;
// };

// struct Person *Person_create(char *name, int age, int height, int weight)
// {
//     struct Person *who = malloc(sizeof(struct Person));

//     assert(who != NULL);

//     who->name = strdup(name);
//     who->age = age;
//     who->height = height;
//     who->weight = weight;

//     return who;
// }

// void person_destroy(struct Person *who){
//     assert(who != NULL);

//     free(who->name);
//     free(who);
// }

// void person_print(struct Person *who){
//     printf("Name: %s \n",who->name);
//     printf("Age: %d \n",who->age);
//     printf("Height: %d \n",who->height);
//     printf("Weight: %d \n",who->weight);
// }

// int main(int argc, char *argv[])
// {

//     struct Person *Joe = Person_create("Joe",30,120,150);
//     struct Person *Frank = Person_create("Frank",24,130,140);

//     printf("Joe at position : %p ",Joe);
//     person_print(Joe);

//     printf("Frank at position : %p ",Frank);
//     person_print(Frank);

//     Joe->age += 20;
//     Joe->height -= 2;
//     Joe->weight +=40;

//     person_print(Joe);

//     Frank->age += 20;
//     Frank->weight += 20;

//     person_print(Frank);

//     person_destroy(Joe);
//     person_destroy(Frank);

//     return 0;
// }
