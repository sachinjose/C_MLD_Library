#ifndef __MLD__
#include <assert.h>
#include <string.h>

//Structure Data base Definition Begin

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

//Enumeration for data types
typedef enum { UINT8,UINT32,INT32,CHAR,OBJ_PTR,VOID_PTR,FLOAT,DOUBLE,OBJ_STRUCT} data_type_t;
typedef enum{ MLD_FALSE, MLD_TRUE } mld_boolean_t;

#define OFFSETOF(struct_name, fld_name)     \
    (unsigned long)&(((struct_name *)0)->fld_name)

#define FIELD_SIZE(struct_name, fld_name)   \
    sizeof(((struct_name *)0)->fld_name)


typedef struct _struct_db_rec_ struct_db_rec_t;


typedef struct _field_info_{
    char fname [MAX_FIELD_NAME_SIZE];   //Name of the field
    data_type_t dtype;                  //Data type of the field
    unsigned int size;                  //Size of the field
    unsigned int offset;                //Offset of the field
    char nested_str_name[MAX_STRUCTURE_NAME_SIZE];     // Below field is meaningful only if dtype = OBJ_PTR, Or OBJ_STRUCT
} field_info_t;

struct _struct_db_rec_{
    struct_db_rec_t *next;  //Pointer to the next structure in the linked list
    char struct_name [MAX_STRUCTURE_NAME_SIZE];  // key
    unsigned int ds_size;   //Size of the structure//
    unsigned int n_fields;  //No of fields in the structure//
    field_info_t *fields;   //pointer to the array of fields//
};

//structure database
typedef struct _struct_db_{
    struct_db_rec_t *head;
    unsigned int count;
} struct_db_t;



// Printing functions
void print_structure_rec (struct_db_rec_t *struct_rec);

void print_structure_db(struct_db_t *struct_db);

// Fn to add the structure record in a structure database

int add_structure_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);

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

//Structure Data base Definition Ends


//Object Database structure definitions Starts here

typedef struct _object_db_rec_ object_db_rec_t;

struct _object_db_rec_{
    object_db_rec_t *next;
    void *ptr;
    unsigned int units;
    struct_db_rec_t *struct_rec;
    mld_boolean_t is_visited; //Used for Graph traversal
    mld_boolean_t is_root;    //Is this object is Root object
};

typedef struct _object_db_{
    struct_db_t *struct_db;
    object_db_rec_t *head;
    unsigned int count;
} object_db_t;



void print_object_rec(object_db_rec_t *obj_rec, int i);

void print_object_db(object_db_t *object_db);

void* xcalloc(object_db_t *object_db, char *struct_name, int units);


void mld_register_root_object (object_db_t *object_db, void *objptr, char *struct_name, unsigned int units);

void set_mld_object_as_global_root(object_db_t *object_db, void *obj_ptr);

//Object Database structure definitions Ends

/*APIs for MLD Algorithm*/
void run_mld_algorithm(object_db_t *object_db);

void report_leaked_objects(object_db_t *object_db);

void mld_set_dynamic_object_as_root(object_db_t *object_db, void *obj_ptr);

void mld_init_primitive_data_types_support(struct_db_t *struct_db);

#endif /* __MLD__ */
