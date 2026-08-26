#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define NEIGHBOURHOOD 1e-5

#define COEFF_AMOUNT 3

#define USER_SUSPENDED 501

#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define BLUE   "\033[34m"
#define RESET  "\033[0m"

enum test_consts {
    TEST_PASSED      = 1,
    TEST_FAILED      = 0,
    AMOUNT_OF_TESTS  = 8,
};

enum solution_amount {
    ONE_SOLUTION     =  1,
    TWO_SOLUTIONS    =  2,
    ANY_ROOT         =  3,
    NO_ROOTS         = -1,
    NEGATIVE_PENALTY = -2,
};   

enum input_status {
    SUCCESS          = 200,
    EXIT             = 503,
    FILE_NOT_FOUND   = 404,
    INCORRECT_INPUT  = -3,
};

enum equation_codes {
    CODE_LINEAR      = 10,
    CODE_QUADRATIC   = 20,
};

enum array_sizes {
    TINY = 64,
    SMALL = 256,
    DECENT = 4096,
};

struct test_case {
    double              a, b, c;
    int     number_of_roots_ref;
    double       x1_ref, x2_ref;
};

extern struct test_case test1;
extern struct test_case test2;
extern struct test_case test3;
extern struct test_case test4;

extern struct test_case test5;
extern struct test_case test6;
extern struct test_case test7;
extern struct test_case test8;


int check_equation_type(double a, double b, double c);
int solve_linear(double b, double c, double* root_first, double* root_second);
int solve_quadratic(double a, double b, double c, double* root_first, double* root_second);

void result_output(int solver_result, double root_1, double root_2);

int equal_to_zero_abs(double dbl);
int more_than_zero(double dbl);
int is_litera(char* ptr_buf, int position);
int validate_status(int status,
                    double a, double b, double c, 
                    double* ptr_root_1, double* ptr_root_2);

int read_file(char* filename_buf, char* file_content, 
              double* coef_a, double* coef_b, double* coef_c, 
              double* ptr_root_1, double* ptr_root_2, 
              int* inprocess, size_t file_content_size, size_t filename_buf_size);

int work_cycle_of_program(double* coef_a, double* coef_b, double* coef_c, 
                          double* ptr_root_1, double* ptr_root_2, 
                          int* inprocess, int mode);

int selectmode();