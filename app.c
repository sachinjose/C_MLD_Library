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
} emp_t;

typedef struct student{
    
    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student *best_colleage;
} student_t;

int main(){

    /*Step 1 : Initialize a new structure database */
    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    
    /*Create structure record for structure emp_t*/
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
    return 0;
}
