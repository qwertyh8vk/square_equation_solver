#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include <stdarg.h>
#include <unistd.h>

#define OK 0

#define NEIGHBOURHOOD 1e-5

#define COEFF_AMOUNT 3

#define USER_SUSPENDED 501

#define TIMING 0

#define RED_TEXT    "\033[31m"
#define GREEN_TEXT  "\033[32m"
#define BLUE_TEXT   "\033[34m"
#define RESET  "\033[0m"

enum modes {
    FROM_KEYBOARD = 1,
    FROM_FILE     = 2,
};

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

enum rand_limits {
    LIMIT_COEF_A  = 50,
    LIMIT_COEF_B  = 100,
    LIMIT_COEF_C  = 50,
    LIMIT_ROOT    = 1000,
    LIMIT_DISCR   = 1000,
};

struct test_case {
    double              coef_a, coef_b, coef_c;
    int     number_of_roots_ref;
    double       x1_ref, x2_ref;
};

extern test_case test_array[AMOUNT_OF_TESTS];
extern test_case test_array_rand_real_roots[AMOUNT_OF_TESTS];
extern test_case test_array_rand_complex_roots[AMOUNT_OF_TESTS];
extern test_case test_array_rand_linear_case[AMOUNT_OF_TESTS];

void no_tests();
void only_tests();
void call_help();
void full(int graphic_index);

void initialize_graphica(double coef_a, double coef_b, double coef_c); /* упростить work cycle of program graphics!!!! */

void printf_slow(const char* format_string, ...);

int check_equation_type(double coef_a);
int solve_linear(double coef_b, double coef_c, double* root_first, double* root_second);
int solve_quadratic(double coef_a, double coef_b, double coef_c, double* root_first, double* root_second);

void result_output(int solver_result, double root_1, double root_2);

int equal_to_zero_abs(double dbl);
int more_than_zero(double dbl);
int less_than_zero(double double_num);

int validate_status(int status,
                    double coef_a, double coef_b, double coef_c, 
                    double* ptr_root_1, double* ptr_root_2);

int read_file(char* filename_buf, char* file_content, 
              double* coef_a, double* coef_b, double* coef_c, 
              double* ptr_root_1, double* ptr_root_2, 
              int* inprocess, int file_content_size, int filename_buf_size, int graphic_index);

// int work_cycle_of_program(int inprocess, int mode);
int work_cycle_of_program_graphics(int inprocess, int mode, int graphic_index); // в разработке прямо сейчас

int select_mode();