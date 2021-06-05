#include "mld.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct emp{

    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_ *mgr;
    float salary;
    int *p;
} emp_t;

typedef struct student{
    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_colleague;
} student_t;

int main(){

    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    mld_init_primitive_data_types_support(struct_db);

    //Create Structure record for structure emp_t
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0),
        FIELD_INFO(emp_t, p, OBJ_PTR, 0)
    };
    //Register the structure in the structure d/b
    REG_STRUCT(struct_db, emp_t, emp_fields);

    static field_info_t stud_fiels[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleague, OBJ_PTR, student_t)
    };
    REG_STRUCT(struct_db, student_t, stud_fiels);

    //print the structure database
    print_structure_db(struct_db);

    //working with object database
    //step 1: Initialise object database
    object_db_t *object_db = calloc(1, sizeof(object_db_t));
    object_db->struct_db = struct_db;
    
    //step2 : create sample object

    student_t *sachin = xcalloc(object_db, "student_t", 1);
    mld_set_dynamic_object_as_root(object_db, sachin);

    student_t *joe = xcalloc(object_db, "student_t", 1);
    strncpy(joe->stud_name, "joe", strlen("joe"));
    // sachin->best_colleague = shivani;

    emp_t *joseph = xcalloc(object_db, "emp_t", 2);
    mld_set_dynamic_object_as_root(object_db, joseph);
    joseph->p = xcalloc(object_db, "int", 1);

    print_object_db(object_db);

    run_mld_algorithm(object_db);
    printf("Leaked Objects : \n");
    report_leaked_objects(object_db);

    return 0;
}
