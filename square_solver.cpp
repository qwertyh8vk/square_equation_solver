#include "square_solver.h"
#include "check_input.h"
#include "tests.h"

struct test_case test1 = {.a = 1,   .b = 5,    .c = 7,     .number_of_roots_ref = NEGATIVE_PENALTY,   .x1_ref = NAN,      .x2_ref = NAN};
struct test_case test2 = {.a = 1,   .b = 8,    .c = 16,    .number_of_roots_ref = ONE_SOLUTION,       .x1_ref = -4,       .x2_ref = NAN};
struct test_case test3 = {.a = 1,   .b = 7,    .c = 12,    .number_of_roots_ref = TWO_SOLUTIONS,      .x1_ref = -422,       .x2_ref = -3};
struct test_case test4 = {.a = 1,   .b = 11,   .c = 30,    .number_of_roots_ref = TWO_SOLUTIONS,      .x1_ref = -6,       .x2_ref = -5};

struct test_case test5 = {.a = 0,   .b = 0,    .c = 6,     .number_of_roots_ref = NO_ROOTS,           .x1_ref = NAN,      .x2_ref = NAN};
struct test_case test6 = {.a = 0,   .b = 5,    .c = 1,     .number_of_roots_ref = ONE_SOLUTION,       .x1_ref = -0.2,     .x2_ref = NAN};
struct test_case test7 = {.a = 0,   .b = 0,    .c = 0,     .number_of_roots_ref = ANY_ROOT,           .x1_ref = 0,        .x2_ref = 0};
struct test_case test8 = {.a = 0,   .b = 0,    .c = 10,    .number_of_roots_ref = NO_ROOTS,           .x1_ref = NAN,      .x2_ref = NAN};

int main() {
    printf("Да здравствует MIPT.\nСовершим проверку ручных тестов.\n\n");
    int amount_of_passed_tests = run_all_tests();

    int inprocess = 1;
    int mode      = 0;

    double coef_a = 0, coef_b = 0, coef_c = 0;
    double root_1 = 0, root_2 = 0;

    double* ptr_root_1 = &root_1;
    double* ptr_root_2 = &root_2;

    check_am_of_pt(amount_of_passed_tests, &inprocess);

    if (inprocess) { 
        mode = selectmode();
        printf("Решала квадратных уравнений. Чтобы выйти, нажмите Q (q)\n");
    }

    work_cycle_of_program(&coef_a, &coef_b, &coef_c, 
                          ptr_root_1, ptr_root_2, 
                          &inprocess, mode);

    printf("\nРабота программы успешно завершена.\n");
    
    return 0;
}


int validate_status(int status, 
                    double coef_a, double coef_b, double coef_c, 
                    double* ptr_root_1, double* ptr_root_2) {

    assert((ptr_root_1 != NULL) && (ptr_root_2 != NULL));

    if (status == EXIT) {
        printf("Первым элементов вы ввели q.\nОсуществляю выход из программы...\n");

        return 0;
    }

    else if (status == USER_SUSPENDED) {
        printf("пользователь написал ctrl+d. Выход из программы нахуй...");

        return 0;
    }

    else if (status == SUCCESS) {
        int number_of_roots = 0;
        int equation_code = check_equation_type(coef_a, coef_b, coef_c);

        if (equation_code == CODE_LINEAR)
            number_of_roots = solve_linear(coef_b, coef_c, ptr_root_1, ptr_root_2);
        else 
            number_of_roots = solve_quadratic(coef_a, coef_b, coef_c, ptr_root_1, ptr_root_2);

        result_output(number_of_roots, *ptr_root_1, *ptr_root_2);
    }
    
    return 1;
}

int is_litera(char* ptr_buf, int position) {

    assert(ptr_buf != NULL);

    if (!isdigit(ptr_buf[position])
    && (ptr_buf[position] != ' ')  && (ptr_buf[position] != ',') 
    && (ptr_buf[position] != '\n') && (ptr_buf[position] != '.') 
    && (ptr_buf[position] != '-')  && (ptr_buf[position] != '+'))
    
        return true;

    return false;
}


int read_file(char* filename_buf, char* file_content, 
              double* coef_a, double* coef_b, double* coef_c, 
              double* ptr_root_1, double* ptr_root_2, 
              int* inprocess, size_t file_content_size, size_t filename_buf_size) 
{
    assert(filename_buf && file_content && 
coef_a && coef_b && coef_c && ptr_root_1 && ptr_root_2 && inprocess);

    printf("Введите имя вашего файла (с .txt): ");
    char* ptr_filename = fgets(filename_buf, filename_buf_size, stdin);

    while(ptr_filename[0] != 'q') {

        ptr_filename[strlen(ptr_filename) - 1] = '\0';
        FILE* file_pointer = fopen(ptr_filename, "r");

        if (file_pointer == NULL) {
            printf("указанный файл не найден.\nThat's why we leaving нахуй из программы.\n");

            return FILE_NOT_FOUND;
        }

        else {
            char* ptr_file_content = fgets(file_content, file_content_size, file_pointer); // sizeof(file_content) / sizeof(*file_content)

            while (ptr_file_content != NULL) {
                int len = strlen(ptr_file_content);
                int status = check_input(ptr_file_content, len, coef_a, coef_b, coef_c);

                *inprocess = validate_status(status, *coef_a, *coef_b, *coef_c, ptr_root_1, ptr_root_2);

                ptr_file_content = fgets(file_content, file_content_size, file_pointer);
            }

            printf("\nвы дошли до конца файла. Вы можете выйти или въебать название другого файла: ");
            fclose(file_pointer);
            
            char* ptr_filename = fgets(filename_buf, filename_buf_size, stdin);
        }
    }

    printf("пользователь ввёл q, поэтому мы выходим из программы нахуй.\n");
    return EXIT;
}


int work_cycle_of_program(double* coef_a, double* coef_b, double* coef_c, 
                          double* ptr_root_1, double* ptr_root_2, 
                          int* inprocess, int mode) {
 while (*inprocess) {

        if (mode == 1) {
            char stdin_buf[DECENT] = {};

            printf("\nВведите коэффициенты a, b, c: ");
            char* ptr_buf = fgets(stdin_buf, sizeof(stdin_buf) / sizeof(*stdin_buf), stdin);

            int len = strlen(stdin_buf);
            int status = check_input(ptr_buf, len, coef_a, coef_b, coef_c);

            *inprocess = validate_status(status, *coef_a, *coef_b, *coef_c, ptr_root_1, ptr_root_2);
        }

        else {
            char filename_buf[TINY]  = {};
            char file_content[SMALL] = {};

            size_t filename_buf_size = sizeof(filename_buf) / sizeof(*filename_buf);
            size_t file_content_size = sizeof(file_content) / sizeof(*file_content);

            char* ptr_file_content;
            int status = read_file(filename_buf, file_content, 
                                   coef_a, coef_b, coef_c, 
                                   ptr_root_1, ptr_root_2, inprocess,
                                   file_content_size, filename_buf_size);
            if (status == EXIT) {
                   return EXIT;
            }

            return FILE_NOT_FOUND;
        }
    }
}

int check_equation_type(double coef_a, double coef_b, double coef_c) {
    if (equal_to_zero_abs(coef_a))  {
        return CODE_LINEAR;
    }
    else {
        return CODE_QUADRATIC;
    }
}

int solve_linear(double coef_b, double coef_c, double* root_first, double* root_second) {

    assert((root_first != NULL) && (root_second != NULL));

    if (equal_to_zero_abs(coef_b)) {
        if (equal_to_zero_abs(coef_c)) {
            *root_first  = 0;
            *root_second = 0;

            return ANY_ROOT;

        }
        
        else {
            *root_first  = NAN;
            *root_second = NAN;

            return NO_ROOTS;
        }
    }

    else {
        *root_first  = -coef_c/coef_b;
        *root_second = NAN;

        return ONE_SOLUTION;
    }
}

int solve_quadratic(double coef_a, double coef_b, double coef_c, double* root_first, double* root_second) {

    assert((root_first != NULL) && (root_second != NULL));

    double discriminant = (pow(coef_b, 2) - 4*coef_a*coef_c);

    if (more_than_zero(discriminant)) {

        double sqrt_discr = sqrt(discriminant);

        if (coef_a < 0) {
            *root_first  = (-coef_b + sqrt_discr)/(2*coef_a);
            *root_second = (-coef_b - sqrt_discr)/(2*coef_a);
        }

        else {
            *root_first  = (-coef_b - sqrt_discr)/(2*coef_a);
            *root_second = (-coef_b + sqrt_discr)/(2*coef_a);
        }

        return TWO_SOLUTIONS;
    }

    else if (equal_to_zero_abs(discriminant)) {
        *root_first  = -coef_b/(2*coef_a);
        *root_second = NAN;

        return ONE_SOLUTION;
    }

    else {
        *root_first  = NAN;
        *root_second = NAN;

        return NEGATIVE_PENALTY;
    }
}

int equal_to_zero_abs(double double_num) {
    if (fabs(double_num - 0) > NEIGHBOURHOOD) {

        return false;
    }

    return true;
}

int more_than_zero(double double_num) {
    if ((double_num - 0) > NEIGHBOURHOOD) {

        return true;
    }

    return false;
}

void result_output(int number_of_roots, double root_1, double root_2) {
    switch (number_of_roots) {

        case ANY_ROOT:
            printf("Выражение вида 0 = 0.\nЛюбой x является решением.\n");
            break;

        case NO_ROOTS:
            printf("Корней нет.\n");
            break;

        case NEGATIVE_PENALTY:
            printf("Дискриминант получился отрицательным.\nРешений в действительных числах нет.\n");
            break;

        case ONE_SOLUTION:
            printf("Единстенное решение x = %.2lf\n", root_1);
            break;

        case TWO_SOLUTIONS:
            printf("Два решения:\nx1 = %.2lf\nx2 = %.2lf\n", root_1, root_2);
            break;

        default:
            assert(false);

    }
}

int selectmode() {
    printf("Вы хотите вводить коэффициенты с клавиатуры (stdin) или у вас есть файл?\n"
           "stdin - 1, а чтение с файла - 2: ");

    char selected_mode[16];
   
    while(true) {
        char* ptr_selected = fgets(selected_mode, sizeof(selected_mode) / sizeof(*selected_mode), stdin);

        if (ptr_selected[2] == '\0') {
            if (ptr_selected[0] == '1') {

                return 1;
            }
            
            else if (ptr_selected[0] == '2') {

                return 2;
            }

            else {
                printf("неккоректный ввод! введите ровно один символ (1) или (2) и нажмите Enter. ");
            }
        }   

        else {
            printf("неккоректный ввод! введите ровно один символ (1) или (2) и нажмите Enter. ");
        }
    }
}