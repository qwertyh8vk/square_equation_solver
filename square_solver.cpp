#include "square_solver.h"
#include "check_input.h"
#include "tests.h"
#include "graphics.h"

// g++ graphics.cpp -o graphics $(pkg-config --cflags --libs raylib) для себя шоб не забыть как компилить графику с рэйлибом

// flags: 
// -s = WITHOUT TESTS, 
// -t = only TESTS, 
// -h = help flag, 2printf'a, return 0
// -f = full version without graphics
// -g = full version with graphics.

// int main(int argc, char *argv[]) {
//     printf("Количество аргументов: %d\n", argc);
//     for (int i = 0; i < argc; i++) {
//         printf("Аргумент %d: %s\n", i, argv[i]);
//     }
//     return 0;
// }

// char* loh = "egor";
// printf("%s", loh);
// *(loh + 1) = 'p';
// // printf("egor");

// "egor"

// print("egor")

// char* loh = "egor"
// printf("%s", loh)
// loh[0] = 'p'
// printf("egor")


struct test_case test_array[AMOUNT_OF_TESTS] = { 
    {.coef_a = 1,    .coef_b = 5,    .coef_c = 7,     .number_of_roots_ref = NEGATIVE_PENALTY,   .x1_ref = NAN,      .x2_ref = NAN},
    {.coef_a = 1,    .coef_b = 8,    .coef_c = 16,    .number_of_roots_ref = ONE_SOLUTION,       .x1_ref = -4,       .x2_ref = -4},
    {.coef_a = 1,    .coef_b = 7,    .coef_c = 12,    .number_of_roots_ref = TWO_SOLUTIONS,      .x1_ref = -4,       .x2_ref = -3},
    {.coef_a = 1,    .coef_b = 11,   .coef_c = 30,    .number_of_roots_ref = TWO_SOLUTIONS,      .x1_ref = -6,       .x2_ref = -5},
    {.coef_a = 0,    .coef_b = 0,    .coef_c = 6,     .number_of_roots_ref = NO_ROOTS,           .x1_ref = NAN,      .x2_ref = NAN},
    {.coef_a = 0,    .coef_b = 5,    .coef_c = 1,     .number_of_roots_ref = ONE_SOLUTION,       .x1_ref = -0.2,     .x2_ref = -0.2},
    {.coef_a = 0,    .coef_b = 0,    .coef_c = 0,     .number_of_roots_ref = ANY_ROOT,           .x1_ref = 0,        .x2_ref = 0},
    {.coef_a = 0,    .coef_b = 0,    .coef_c = 10,    .number_of_roots_ref = NO_ROOTS,           .x1_ref = NAN,      .x2_ref = NAN},
};

struct test_case test_array_rand_real_roots[AMOUNT_OF_TESTS]    = {};
struct test_case test_array_rand_complex_roots[AMOUNT_OF_TESTS] = {};
struct test_case test_array_rand_linear_case[AMOUNT_OF_TESTS]   = {};

int main(int argc, char* argv[]) {
    int graphic_index = 0;

    if (argc != 2) {
        printf("Программа принимает на вход ровно 2 аргумента, включая название файла.\n");
        return 0;
    }

    else {
        if      (!strcmp(argv[1], "-s")) {
            no_tests();
        }

        else if (!strcmp(argv[1], "-t")) {
            only_tests();
        }

        else if (!strcmp(argv[1], "-h")) {
            call_help();            
        }

        else if (!strcmp(argv[1], "-f")) {
            full(graphic_index);
        }

        else if (!strcmp(argv[1], "-g")) {
            graphic_index = 1;

            full(graphic_index);
        }

        else {
            printf("Unknown flag.\n Ebni -h to get help and see list of all the flags available.\n");
        }
    }

    return 0;
}

void no_tests() {
    int inprocess     = 1;
    int mode          = 0;
    int graphic_index = 0;

    printf("\nПохуизм - это хорошо. с флагом -s скипаются тесты.\n");
    printf_slow("Решала квадратных уравнений. Чтобы выйти, нажмите Q (q)\n\n");

    mode = select_mode();

    work_cycle_of_program_graphics(inprocess, mode, graphic_index);
    printf_slow("\nРабота программы успешно завершена.\n");
}

void only_tests() {
    printf_slow("Да здравствует МФТИ.\nСовершим проверку ручных и автоматических тестов.\n");
    printf_slow("И больше нихуя кстати, мы же в флаге -t\n");

    initialize_auto_tests_structs_array();
    int amount_of_passed_tests = run_all_tests();
    check_num_of_passed_tests_tflag(amount_of_passed_tests);
}

void call_help() {
    printf("\nList of available flags:\n"
           "-h: help flag, which you've initialized\n"
           "-f: runs full version without graphics\n"
           "-g: runs full version including graphics\n"
           "-t: runs tests only to check the workability of program\n"
           "-s: skips tests and runs -g version independently of test results.\n\n");
}

void full(int graphic_index) {
    printf_slow("Да здравствует МФТИ.\nСовершим проверку ручных и автоматических тестов.\n\n");
    printf_slow("до скайнета осталось 30 секунд. тебе пиздец\n");

    int inprocess = 1;
    int mode      = 0;

    initialize_auto_tests_structs_array();
    int amount_of_passed_tests = run_all_tests();
    check_num_of_passed_tests(amount_of_passed_tests, &inprocess);

    if (inprocess) { 
        mode = select_mode();
        printf_slow("Решала квадратных уравнений. Чтобы выйти, нажмите Q (q)\n");
    }

    work_cycle_of_program_graphics(inprocess, mode, graphic_index);

    printf_slow("\nРабота программы успешно завершена.\n");
}

void printf_slow(const char* format_string, ...) {
    char string_buffer[DECENT] = {};

    va_list ptr_on_unnessesary;
    va_start(ptr_on_unnessesary, format_string);

    vsnprintf(string_buffer, sizeof(string_buffer) / sizeof(*string_buffer), format_string, ptr_on_unnessesary);

    size_t string_buf_len = strnlen(string_buffer, sizeof(string_buffer) / sizeof(*string_buffer));

    va_end(ptr_on_unnessesary);
    for (size_t i = 0; i < string_buf_len; i++) {
        char symbol = string_buffer[i];
        putc(symbol, stdout);
        fflush(stdout);
        usleep(TIMING);
    }
}

int validate_status(int status, 
                    double coef_a, double coef_b, double coef_c, 
                    double* ptr_root_1, double* ptr_root_2) {

    assert((ptr_root_1 != NULL) && (ptr_root_2 != NULL));

    if (status == EXIT) {
        printf_slow("Первым элементов вы ввели q.\nОсуществляю выход из программы...\n");

        return 0;
    }

    else if (status == USER_SUSPENDED) {
        printf_slow("Пользователь ввёл ctrl+d. Выход из программы н***й...");

        return 0;
    }
    
    else if (status == SUCCESS) {
        int number_of_roots = 0;
        int equation_code = check_equation_type(coef_a);

        if (equation_code == CODE_LINEAR) {
            number_of_roots = solve_linear(coef_b, coef_c, ptr_root_1, ptr_root_2);
        }

        else {
            number_of_roots = solve_quadratic(coef_a, coef_b, coef_c, ptr_root_1, ptr_root_2);
        }

        result_output(number_of_roots, *ptr_root_1, *ptr_root_2);

    }

    return 1;
}

int read_file(char* filename_buf, char* file_content, 
              double* coef_a, double* coef_b, double* coef_c, 
              double* ptr_root_1, double* ptr_root_2, 
              int* inprocess, int file_content_size, int filename_buf_size, int graphic_index) 
{
    assert((filename_buf != NULL)  &&  (file_content != NULL) && 
           (coef_a != NULL)        &&  (coef_b != NULL)       && 
           (coef_c != NULL)        &&  (ptr_root_1 != NULL)   && 
           (ptr_root_2 != NULL)    &&  (inprocess != NULL));

    printf_slow("Введите имя вашего файла (с .txt): ");
    char* ptr_filename = fgets(filename_buf, filename_buf_size, stdin);

    while((ptr_filename[0] != 'q') && (ptr_filename[0] != 'Q')) {

        ptr_filename[strlen(ptr_filename) - 1] = '\0';
        FILE* file_pointer = fopen(ptr_filename, "r");

        if (file_pointer != NULL) {
            char* ptr_file_content = fgets(file_content, file_content_size, file_pointer); // sizeof(file_content) / sizeof(*file_content) не получится

            while (ptr_file_content != NULL) {
                size_t len = strlen(ptr_file_content);
                int status = check_input(ptr_file_content, len, coef_a, coef_b, coef_c);

                if (status == SUCCESS && graphic_index == 1) {
                    initialize_graphica(*coef_a, *coef_b, *coef_c);
                }

                *inprocess = validate_status(status, *coef_a, *coef_b, *coef_c, ptr_root_1, ptr_root_2);

                printf("\nПродолжаем лудоприключения? ");

                while(true) {
                    char check_answer[SMALL];
                    char* ptr_check_ans = fgets(check_answer, sizeof(check_answer) / sizeof(*check_answer), stdin);

                    if (ptr_check_ans[0] == 'Y' || ptr_check_ans[0] == 'y') {
                        printf_slow("\nВычисления продолжаются.\n");

                        break;
                    }

                    else if (ptr_check_ans[0] == 'N' || ptr_check_ans[0] == 'n') {
                        printf_slow("\nЗакончим на этой тройке коэффициентов.\n");

                        return EXIT;
                    }

                    else {
                        printf_slow("\nНу сказали же, Y или N!\nЖду ваш ответ в корректном виде: ");
                    }
                }

                ptr_file_content = fgets(file_content, file_content_size, file_pointer);
            }

            fclose(file_pointer);
            printf_slow("\nВы дошли до конца файла. Вы можете выйти или вписать название другого файла: ");
        }
        
        else {
            printf_slow("Указанный файл не найден.\nВведите название считываемого файла (или кушку):"); 
        }

        ptr_filename = fgets(filename_buf, filename_buf_size, stdin);
    }

    printf_slow("Пользователь ввёл q, поэтому мы выходим из программы н***й.\n");
    return EXIT;
}

void initialize_graphica(double coef_a, double coef_b, double coef_c) 
{
    int multiplier = 40;
    int dmult = 10;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trial window");
    
    SetTargetFPS(25);
    SetExitKey(KEY_Q);

    while (!WindowShouldClose()) {

        BeginDrawing();

            if (GetMouseWheelMove() > 0) {
                if (multiplier <= 600) {
                    multiplier += dmult;
                }

            }

            else if (GetMouseWheelMove() < 0) {
                if (multiplier >= 20) {
                    multiplier -= dmult;
                }
            }

            ClearBackground(WHITE);
            draw_axes(multiplier);
            draw_graph_by_dots(multiplier, coef_a, coef_b, coef_c);

        EndDrawing();
    }

    CloseWindow();
    printf("\n\n");
}

int work_cycle_of_program_graphics(int inprocess, int mode, int graphic_index) {

    double coef_a = 0, coef_b = 0, coef_c = 0;
    double root_1 = 0, root_2 = 0;

    double* ptr_root_1 = &root_1;
    double* ptr_root_2 = &root_2;

    while (inprocess)  {
        if (mode == FROM_KEYBOARD) {

            char stdin_buf[DECENT] = {};
            printf_slow("\nВведите коэффициенты a, b, c: ");
            char* ptr_buf = fgets(stdin_buf, sizeof(stdin_buf) / sizeof(*stdin_buf), stdin);

            size_t len = strlen(stdin_buf);
            int status = check_input(ptr_buf, len, &coef_a, &coef_b, &coef_c);

            if (status == SUCCESS && graphic_index == 1) {
                initialize_graphica(coef_a, coef_b, coef_c);
            }

            inprocess = validate_status(status, coef_a, coef_b, coef_c, ptr_root_1, ptr_root_2);
        }

        else {
            char filename_buf[TINY]  = {};
            char file_content[SMALL] = {};

            int filename_buf_size = sizeof(filename_buf) / sizeof(*filename_buf);
            int file_content_size = sizeof(file_content) / sizeof(*file_content);

            int status = read_file(filename_buf, file_content, 
                                   &coef_a, &coef_b, &coef_c, 
                                   ptr_root_1, ptr_root_2, &inprocess,
                                   file_content_size, filename_buf_size, graphic_index);
            if (status == EXIT) {
                return EXIT;
            }
        }
    }

    return 0;
}

int check_equation_type(double coef_a) {
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
        *root_second = *root_first;

        return ONE_SOLUTION;
    }
}

int solve_quadratic(double coef_a, double coef_b, double coef_c, double* root_first, double* root_second) {

    assert((root_first != NULL) && (root_second != NULL));

    double discriminant = (pow(coef_b, 2) - 4*coef_a*coef_c);

    if (more_than_zero(discriminant)) {

        double sqrt_discr = sqrt(discriminant);

        if (less_than_zero(coef_a)) {
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
        *root_second = *root_first;

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

int less_than_zero(double double_num) {
    if ((double_num - 0) < NEIGHBOURHOOD) {

        return true;
    }

    return false;
}

void result_output(int number_of_roots, double root_1, double root_2) {
    switch (number_of_roots) {

        case ANY_ROOT:
            printf_slow("Выражение вида 0 = 0.\nЛюбой x является решением.\n");
            break;

        case NO_ROOTS:
            printf_slow("Корней нет.\n");
            break;

        case NEGATIVE_PENALTY:
            printf_slow("Дискриминант получился отрицательным.\nРешений в действительных числах нет.\n");
            break;

        case ONE_SOLUTION:
            printf_slow("Единстенное решение x = %.2lf\n", root_1);
            break;

        case TWO_SOLUTIONS:
            printf_slow("Два решения:\nx1 = %.2lf\nx2 = %.2lf\n", root_1, root_2);
            break;

        default:
            assert(false);

    }
}

int select_mode() {
    printf_slow("Вы хотите вводить коэффициенты с клавиатуры (stdin) или у вас есть файл?\n"
           "stdin - 1, а чтение с файла - 2: ");

    char selected_mode[SMALL];
   
    while(true) {
        char* ptr_selected = fgets(selected_mode, sizeof(selected_mode) / sizeof(*selected_mode), stdin);

        if (ptr_selected[2] == '\0') {
            if (ptr_selected[0] == '1') {

                return FROM_KEYBOARD;
            }
            
            else if (ptr_selected[0] == '2') {

                return FROM_FILE;
            }

            else {
                printf_slow("неккоректный ввод! Введите ровно один символ (1) или (2) и нажмите Enter. ");
            }
        }   

        else {
            printf_slow("неккоректный ввод! Введите ровно один символ (1) или (2) и нажмите Enter. ");
        }
    }
}

