# Exercise 17. Heap and Stack Memory Allocation

### Heap
The heap is easier to explain since it’s just all the remaining memory in your computer, and you access it with the function malloc to get more. Each time you call malloc, the OS uses internal functions to
register that piece of memory to you, and then returns a pointer to it. When you’re done with it, you use free to return it to the OS so that it can be used by other programs. Failing to do this will cause your program to leak memory.

### Stack 
The stack is a special region of memory that stores temporary variables, which each function creates as
locals to that function. How it works is that each argument to a function is pushed onto the stack and
then used inside the function. It’s really a stack data structure, so the last thing in is the first thing out.
This also happens with all local variables like char action and int id in main. The advantage of using
a stack for this is simply that when the function exits, the C compiler pops these variables off of the
stack to clean up. This is simple and prevents memory leaks if the variable is on the stack.

## How to Break It

### The classic way is to remove some of the safety checks so that you can pass in arbitrary data. For example, remove the check on line 160 that prevents you from passing in any record number.

Removed first condition in main 

```c
$ ./ex17 db.db 
Segmentation fault (core dumped)
```

### You can also try corrupting the data file. Open it in any editor and change random bytes, and then close it.

```c
$ ./ex17 db.db  s 3 joe joe@zedshaw.com
ERROR: Failed to load database.

```

### You could also find ways to pass bad arguments to the program when it’s run. For example, getting the file and action backward will make it create a file named after the action, and then do an action based on the first character.

```c
$ ./ex17 c db.db 
Failed to open the file: No such file or directory
```

### There’s a bug in this program because strncpy is poorly designed. Go read about strncpy and try to find out what happens when the name or address you give is greater than 512 bytes. Fix this by simply forcing the last character to '\0' so that it’s always set no matter what (which is what strncpy should do).

setting a name greater than 512

```c
 ./ex17 db.db l33 joe@zedshaw.com abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr"
```

a double quote appered in the last 

```c
    char *res = strncpy(address->name,name,MAX_DATA);
    address->name[MAX_DATA-1] = '\0';

    if(!res) die("Name copy failed.\n");
    
    res = strncpy(address->email,email,MAX_DATA);
    address->email[MAX_DATA-1] = '\0';
```

### In the Extra Credit section, I have you augment the program to create arbitrary size databases. Try to see what the biggest database is before you cause the program to die due to lack of memory from malloc.

it depends on the physical memory 

## Extra Credit 

### The die function needs to be augmented to let you pass the conn variable, so it can close it and clean up.

```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address
{
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database
{
    struct Address rows[MAX_ROWS];
};

struct Connection
{
    FILE *file;
    struct Database *db;
};

void address_Print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}
void Database_close(struct Connection *conn)
{
    if (conn)
    {
        if (conn->file)
            fclose(conn->file);
        if (conn->db)
            free(conn->db);
        free(conn);
    }
}

void die(char *message, struct Connection *conn)
{
    if (errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    }

    Database_close(conn);

    exit(1);
}

void Database_load(struct Connection *conn)
{
    int read_count = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (read_count != 1)
        die("Failed to load database.\n",conn);
}

struct Connection *Database_open(const char *filename, char mode)
{

    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die("Memory error",conn);
    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die("Memory error",conn);

    if (mode == 'c')
        conn->file = fopen(filename, "w");
    else
    {
        conn->file = fopen(filename, "r+");

        if (conn->file)
            Database_load(conn);
    }

    if (!conn->file)
        die("Failed to open the file",conn);

    return conn;
}


void Database_write(struct Connection *conn)
{

    rewind(conn->file);
    int read_count = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    
    if (read_count != 1)
        die("Failed to write database.\n",conn);
    read_count = fflush(conn->file);
    if (read_count == -1)
        die("Cannot flush the database.\n",conn);
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++)
    {
        struct Address address = {.id =i,.set=0};
        conn->db->rows[i] = address;
    }
}

void Database_set(struct Connection *conn, int id,const char *email, const char *name ){

    struct Address *address = &conn->db->rows[id];
    if(address->set) die("Already set delete it first\n",conn);

    address->set = 1;
    
    char *res = strncpy(address->name,name,MAX_DATA);
    address->name[MAX_DATA-1] = '\0';

    if(!res) die("Name copy failed.\n",conn);
    
    res = strncpy(address->email,email,MAX_DATA);
    address->email[MAX_DATA-1] = '\0';

    if(!res) die("Email copy failed.\n",conn);
}

void Database_get(struct Connection *conn,int id){
    struct Address *address = &conn->db->rows[id];
    if(address->set)
        address_Print(address);
    else die("ID is not set.\n",conn);
}

void Database_delete(struct Connection *conn,int id){
    struct Address address = {.id = id, .set = 0};
    conn->db->rows[id] = address;
}

void Database_list(struct Connection *conn){
    int i = 0;
    struct Database *db = conn->db;

    for(i=0;i<MAX_ROWS;i++){
        struct Address *cur = &db->rows[i];
        if(cur->set) 
        address_Print(cur);
    }
}

int main(int argc, char *argv[])
{

    if(argc < 3) die("USAGE: ./ex17 <dbfile> <action> [action params]",NULL);

    char *filename = argv[1];

    char action = argv[2][0];

    struct Connection *conn = Database_open(filename,action);

    int id=0;

    if(argc > 3) id = atoi(argv[3]);
    if(id>=MAX_ROWS) die("That's not that many records.\n",conn);

    switch (action)
    {
    case 'c':
        Database_create(conn);
        Database_write(conn);
        break;

    case 'g':
        if(argc != 4) die("Need an id to get.\n",conn);
        Database_get(conn,id);
        break;

    case 's':
        if(argc != 6) die("Need an id, name, email to set.\n",conn);
        Database_set(conn,id,argv[4],argv[5]);
        Database_write(conn);
        break;

    case 'd':
        if(argc != 4) die("Need an id to delete.\n",conn);
        Database_delete(conn,id);
        Database_write(conn);
        break;

    case 'l':
        Database_list(conn);
        break;
    default:
        die("Invalid action: c=create, g=get, s=set, d=del, l=list",conn);
        break;
    }

    return 0;
}
```

### Change the code to accept parameters for MAX_DATA and MAX_ROWS, store them in the Database struct, and write that to the file, thus creating a database that can be arbitrarily sized. 

