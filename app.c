#include "mld.h"
#include <memory.h>
#include <stdlib.h>

/*Application Structures*/

typedef struct emp{
    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp *mgr;
    float salary;
    int *p;
} emp_t;

typedef struct student{

    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student *best_colleage;
} student_t;

int main(){

    //Initialise new structure db
    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0)
    };
    REG_STRUCT(struct_db, emp_t, emp_fields);

    static field_info_t stud_fiels[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleage, OBJ_PTR, student_t)
    };
    REG_STRUCT(struct_db, student_t, stud_fiels);

    print_structure_db(struct_db);

    object_db_t *object_db = calloc(1, sizeof(object_db_t));
    object_db->struct_db = struct_db;
    
    student_t *sachin = xcalloc(object_db, "student_t", 1);
    mld_set_dynamic_object_as_root(object_db, sachin);

    student_t *joe = xcalloc(object_db, "student_t", 1);
    strncpy(joe->stud_name, "joe", strlen("joe"));
    sachin->best_colleage = joe;

    student_t *james = xcalloc(object_db, "student_t", 1);
    strncpy(joe->stud_name, "james", strlen("james"));

    emp_t *shweta = xcalloc(object_db, "emp_t", 2);
    mld_set_dynamic_object_as_root(object_db, shweta);
    shweta->p = xcalloc(object_db, "int", 1);

    print_object_db(object_db);

    run_mld_algorithm(object_db);
    printf("Leaked Objects : \n");
    report_leaked_objects(object_db);

    return 0;
}
