#include<stdio.h>



struct __attribute__((__packed__)) Address
{
    char *name;
    char *email;
    int id;
    int set;
    int ma;
};

int main(int argc, char *argv[]){
    
    struct Address address = {.id = 1,.set = 0, .name = "omama", .email = "omama@gmail.com",.ma=9e4};
    printf("%ld",sizeof(address));

    return 0;
}