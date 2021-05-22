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

void address_Print(struct Address *address)
{
    printf("%d %d\n", address->id, address->set);
}

void die(char *message)
{
    if (errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Database_load(struct Connection *conn)
{
    int read_count = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (read_count != 1)
        die("Failed to load database.\n");
}

struct Connection *Database_open(const char *filename, char mode)
{

    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die("Memory error");
    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die("Memory error");

    if (mode == 'c')
        conn->file = fopen(filename, "w");
    else
    {
        conn->file = fopen(filename, "r+");

        if (conn->file)
            Database_load(conn);
    }

    if (!conn->file)
        die("Failed to open the file");

    return conn;
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

void Database_write(struct Connection *conn)
{

    rewind(conn->file);
    int read_count = fread(conn->db, sizeof(struct Database), 1, conn->file);

    if (read_count != 1)
        die("Failed to write database.\n");
    read_count = fflush(conn->file);
    if (read_count == -1)
        die("Cannot flush the database.\n");
}

void Database_create(struct Connection *conn)
{

    for (int i = 0; i < MAX_ROWS; i++)
    {
        struct Address address = {.id =i,.set=0};
        conn->db->rows[i] = address;
    }
}

void Database_set(struct Connection *conn, int id,const char *email, const char *name ){

    struct Address *address = &conn->db->rows[id];
    if(address->set) die("Already set delete it first\n");
    address->set = 1;
    
    char *res = strncpy(address->name,name,MAX_DATA);

    if(!res) die("Name copy failed.\n");
    
    res = strncpy(address->email,email,MAX_DATA);

    if(!res) die("Email copy failed.\n");
}

void Database_get(struct Connection *conn,int id){
    struct Address *address = &conn->db->rows[id];
    if(address->set)
        address_Print(address);
    else die("ID is not set.\n");
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
        if(cur->set) address_Print(cur);
    }
}

int main(int argc, char *argv[])
{

    if(argc < 3) die("USAGE: ./ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];

    char action = argv[2][0];

    struct Connection *conn = Database_open(filename,action);

    int id = 0;

    if(argc > 3) id = atoi(argv[2]);
    if(id>=MAX_ROWS) die("That's not that many records.\n");

    switch (action)
    {
    case 'c':
        Database_create(conn);
        Database_write(conn);
        break;

    case 'g':
        if(argc != 4) die("Need an id to get.\n");
        Database_get(conn,id);
        break;

    case 's':
        if(argc != 6) die("Need an id, name, email to set.\n");
        Database_set(conn,id,argv[4],argv[5]);
        Database_write(conn);
        break;

    case 'd':
        if(argc != 4) die("Need an id to delete.\n");
        Database_delete(conn,id);
        Database_write(conn);
        break;

    case 'l':
        Database_list(conn);
    
    default:
        die("Invalid action: c=create, g=get, s=set, d=del, l=list");
        break;
    }

    return 0;
}