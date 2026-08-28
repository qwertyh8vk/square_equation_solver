#include "square_solver.h"
#include "tests.h"

int compare_including_nans(double x_i, double x_i_ref) {
    if (isnan(x_i) && isnan(x_i_ref)) {
        return 1;
    }
    
    else {
        if (fabs(x_i-x_i_ref) < NEIGHBOURHOOD) {
            return 1;
        }

        else {
            return 0;
        }
    }
}

int run_one_test(struct test_case test, int number) {
    double x1, x2       = 0;
    int number_of_roots = 0;

    int equation_code = check_equation_type(test.coef_a);

    if (equation_code == CODE_LINEAR) {
        number_of_roots = solve_linear(test.coef_b, test.coef_c, &x1, &x2);
    }

    else {
        number_of_roots = solve_quadratic(test.coef_a, test.coef_b, test.coef_c, &x1, &x2);
    }

    if    ((number_of_roots != test.number_of_roots_ref) 
        || (compare_including_nans(x1, test.x1_ref) == 0) 
        || (compare_including_nans(x2, test.x2_ref) == 0)) 
    {
        printf(RED "TEST %d FAILED!\na = %lg, b = %lg, c = %lg"
                   "\nexpected amount of roots: %d"
                   "\nexpected roots: x1_ref = %lg, x2_ref = %lg"
                   "\ncalculated amount of roots: %d"
                   "\ncalculated: x1 = %lg, x2 = %lg\n\n" RESET,
                    (number+1), test.coef_a, test.coef_b, test.coef_c, test.number_of_roots_ref, 
                    test.x1_ref, test.x2_ref, number_of_roots, x1, x2);

        return TEST_FAILED;
    }

    else {
        printf(GREEN "TEST %d WAS PASSED SUCCESFULLY.\n" RESET, (number+1));

        return TEST_PASSED;
    } 
}

int run_all_tests() {

    int amount_of_passed_tests = 0;

    printf("\nDoing manual tests.\n\n");
    amount_of_passed_tests += count_passed_tests(test_array);

    printf("\nTesting real roots equations.\n\n");
    amount_of_passed_tests += count_passed_tests(test_array_rand_real_roots);

    printf("\nTesting complex roots equations.\n\n");
    amount_of_passed_tests += count_passed_tests(test_array_rand_complex_roots);

    printf("\nTesting linear equations\n\n");
    amount_of_passed_tests += count_passed_tests(test_array_rand_linear_case);

    return amount_of_passed_tests;
}

int count_passed_tests(struct test_case *some_test_array) {
    int single_test_result_arr[AMOUNT_OF_TESTS]  = {0};
    int num_of_passed_tests_single_set = 0;

    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        single_test_result_arr[i] = run_one_test(some_test_array[i], i);
        num_of_passed_tests_single_set += single_test_result_arr[i];
    }

    return num_of_passed_tests_single_set;
}

void vieta_reverse(double coef_a, double x1_ref_rand, double x2_ref_rand, 
                   double* coef_b, double* coef_c) 
{
    *coef_b = -(x1_ref_rand + x2_ref_rand)*(coef_a);
    *coef_c =  (x1_ref_rand * x2_ref_rand)*(coef_a);
}

void coef_c_reverse(double discr, double coef_a, double coef_b, double* coef_c) {
    *coef_c = (pow(coef_b, 2) - discr)/(4*coef_a);
}

int find_coef_b_when_linear(double coef_c, double x1_ref_rand, double* coef_b) {
    if (equal_to_zero_abs(coef_c) && equal_to_zero_abs(x1_ref_rand)) {
        *coef_b = ((rand() % LIMIT_COEF_B) - (LIMIT_COEF_B + 1)) / (rand() % 14) * (rand() % 8);

        if (equal_to_zero_abs(*coef_b)) { 

            return ANY_ROOT;
        }

        return ONE_SOLUTION;
    }

    if (!equal_to_zero_abs(coef_c) && equal_to_zero_abs(x1_ref_rand)) {

        return NO_ROOTS;
    }

    else if (equal_to_zero_abs(coef_c) && !equal_to_zero_abs(x1_ref_rand)) {
        *coef_b = 0;

        return ANY_ROOT;
    }

    else {
        *coef_b = -(coef_c / x1_ref_rand);
    }

    return ONE_SOLUTION;
}

void rand_without_zero(double* coef_a) {
    while(equal_to_zero_abs(*coef_a)) {
        *coef_a = ((rand() % LIMIT_COEF_A) - (LIMIT_COEF_A + 1)) / (rand() % 14) * (rand() % 8);
    }
}

void initialize_positive_discr_structs_arr() {
    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        double coef_b, coef_c, coef_a = 0;

        rand_without_zero(&coef_a);
        double x1_ref_rand = ((rand() % LIMIT_ROOT) - (LIMIT_ROOT / 2)) / (rand() % 14) * (rand() % 8);
        double x2_ref_rand = ((rand() % LIMIT_ROOT) - (LIMIT_ROOT / 2)) / (rand() % 14) * (rand() % 8);

        if(x1_ref_rand > x2_ref_rand) {
            double temp = x1_ref_rand;
            x1_ref_rand = x2_ref_rand;
            x2_ref_rand = temp;
        }

        vieta_reverse(coef_a, x1_ref_rand, x2_ref_rand, &coef_b, &coef_c);

        if (fabs(x1_ref_rand - x2_ref_rand) < NEIGHBOURHOOD) {
            test_array_rand_real_roots[i] = 
                {.coef_a = coef_a, .coef_b = coef_b, .coef_c = coef_c, 
                 .number_of_roots_ref = ONE_SOLUTION, 
                 .x1_ref = x1_ref_rand, .x2_ref = x1_ref_rand};
        }

        else {
            test_array_rand_real_roots[i] = 
                {.coef_a = coef_a, .coef_b = coef_b, .coef_c = coef_c, 
                 .number_of_roots_ref = TWO_SOLUTIONS, 
                 .x1_ref = x1_ref_rand, .x2_ref = x2_ref_rand};
        }
    }
}

void initialize_negative_discr_structs_arr() {
    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        double coef_c, coef_a = 0, discr = 0;

        rand_without_zero(&coef_a);

        while (equal_to_zero_abs(discr)) {
            discr  = ((rand() % LIMIT_DISCR)  - (2*LIMIT_DISCR))  / (rand() % 14) * (rand() % 8); // sosal
        }

        double coef_b = ((rand() % LIMIT_COEF_B) - (LIMIT_COEF_B / 2)) / (rand() % 14) * (rand() % 8);

        coef_c_reverse(discr, coef_a, coef_b, &coef_c);

        test_array_rand_complex_roots[i] = 
        {.coef_a = coef_a, .coef_b = coef_b, .coef_c = coef_c, 
         .number_of_roots_ref = NEGATIVE_PENALTY, .x1_ref = NAN, .x2_ref = NAN};
    }
}

void initialize_linear_structs_arr() {
    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        double coef_b = 0;

        double coef_c      = ((rand() % LIMIT_COEF_C) - (LIMIT_COEF_C / 2)) / (rand() % 14) * (rand() % 8);
        double x1_ref_rand = ((rand() % LIMIT_ROOT)   - (LIMIT_ROOT / 2))   / (rand() % 14) * (rand() % 8);

        int situation = find_coef_b_when_linear(coef_c, x1_ref_rand, &coef_b);

        if (situation == ANY_ROOT) {
            test_array_rand_linear_case[i] = 
            {.coef_a = 0, .coef_b = coef_b, .coef_c = coef_c, .number_of_roots_ref = ANY_ROOT, 
             .x1_ref = 0, .x2_ref = 0};
        }

        else if (situation == NO_ROOTS) {
            test_array_rand_linear_case[i] = 
            {.coef_a = 0, .coef_b = 0, .coef_c = coef_c, .number_of_roots_ref = NO_ROOTS, 
             .x1_ref = NAN, .x2_ref = NAN};
        }

        else {
            test_array_rand_linear_case[i] = 
            {.coef_a = 0, .coef_b = coef_b, .coef_c = coef_c, .number_of_roots_ref = ONE_SOLUTION, 
             .x1_ref = x1_ref_rand, .x2_ref = x1_ref_rand};
        }
    }
}

void initialize_auto_tests_structs_array() { 
    srand(time(NULL));
    initialize_positive_discr_structs_arr();
    initialize_negative_discr_structs_arr();
    initialize_linear_structs_arr();
}

void check_num_of_passed_tests(int amount_of_passed_tests, int* inprocess) {

    assert(inprocess != NULL);

    if (amount_of_passed_tests != 4 * AMOUNT_OF_TESTS) {
        printf("\nПрограмма прошла НЕ ВСЕ тесты. (%d из %d)"
               "\nВы уверены, что хотите пользоваться этой х***ей,"
               "\nкоторая медленная, да ещё и решает неправильно? ", amount_of_passed_tests, 4 * AMOUNT_OF_TESTS);

        while(true) {
            char check_answer[SMALL];
            char* ptr_check_ans = fgets(check_answer, sizeof(check_answer) / sizeof(*check_answer), stdin);

            if (ptr_check_ans[0] == 'Y' || ptr_check_ans[0] == 'y') {
                printf("Делайте домашку с этой х***ей на свой страх и риск.\n");

                break;
            }
            else if (ptr_check_ans[0] == 'N' || ptr_check_ans[0] == 'n') {
                printf("Правильное решение.\n");
                *inprocess = 0;

                break;
            }
            else {
                printf("Ну сказали же, Y или N!\nЖду ваш ответ в корректном виде: ");
            }
        }
    }

    else {
        printf("\nВсе тесты пройдены успешно. Фотомафу можно доверять.\n");
    }
}
