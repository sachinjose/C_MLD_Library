#ifndef __MLD__
#include <assert.h>

//Structure Data base Definition Begin

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

//Enumeration for data types
typedef enum {UINT8, UINT32, INT32, CHAR, OBJ_PTR, FLOAT, DOUBLE, OBJ_STRUCT} data_type;

#define OFFSETOF(struct_name, fld_name)     \
    (unsigned int)&(((struct_name *)0)->fld_name)

#define FIELD_SIZE(struct_name, fld_name)   \
    sizeof(((struct_name *)0)->fld_name)


typedef struct struct_db_rec struct_db_rec_t; //to not keep declaring struct 

// Structure to store the information of one field of a C structure
typedef struct field_info{
    char fname [MAX_FIELD_NAME_SIZE];   //Name of the field
    data_type dtype;                  //Data type of the field
    unsigned int size;                  //Size of the field
    unsigned int offset;                //Offset of the field
    char nested_str_name[MAX_STRUCTURE_NAME_SIZE];  //Only if dtype = OBJ_PTR, Or OBJ_STRUCT
} field_info_t;

//Structure to store the information of one C structure which could have 'n_fields' fields
struct struct_db_rec{
    struct_db_rec_t *next;  //Pointer to the next structure in the linked list
    char struct_name [MAX_STRUCTURE_NAME_SIZE];  // key
    unsigned int ds_size;   //Size of the structure
    unsigned int n_fields;  //No of fields in the structure
    field_info_t *fields;   //pointer to the array of fields
};

//Finally the head of the linked list representing the structure database
typedef struct struct_db{
    struct_db_rec_t *head;
    unsigned int count;
} struct_db_t;

// //Structure Data base Definition Ends

//Function Prototypes

void print_structure_rec (struct_db_rec_t *struct_rec);

void print_structure_db(struct_db_t *struct_db);

//Fn to add the structure record in a structure database

int add_structure_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);

//Structure Registration helping APIs//

#define FIELD_INFO(struct_name, fld_name, dtype, nested_struct_name)    \
   {#fld_name, dtype, FIELD_SIZE(struct_name, fld_name),                \
        OFFSETOF(struct_name, fld_name), #nested_struct_name} 

#define REG_STRUCT(struct_db, st_name, fields_arr)                    \
    do{                                                               \
        struct_db_rec_t *rec = calloc(1, sizeof(struct_db_rec_t));    \
        strncpy(rec->struct_name, #st_name, MAX_STRUCTURE_NAME_SIZE); \
        rec->ds_size = sizeof(st_name);                              \
        rec->n_fields = sizeof(fields_arr)/sizeof(field_info_t);     \
        rec->fields = fields_arr;                                    \
        if(add_structure_to_struct_db(struct_db, rec)){              \
            assert(0);                                               \
        }                                                            \
    }while(0);


//Object Data base Definition Begin

typedef struct object_db_rec object_db_rec_t;

struct object_db_rec{
    object_db_rec_t *next;
    void *ptr;
    unsigned int units;
    struct_db_rec_t *struct_rec;
};

typedef struct object_db{
    struct_db_t *struct_db;
    object_db_rec_t *head;
    unsigned int count;
} object_db_t;

//Structure Data base Definition End
//Function Prototypes

void print_object_rec(object_db_rec_t *obj_rec, int i);

void print_object_db(object_db_t *object_db);

void* xcalloc(object_db_t *object_db, char *struct_name, int units);

#endif 
