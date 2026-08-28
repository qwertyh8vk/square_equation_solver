#include "square_solver.h"
#include "tests.h"

int compare_wided(double x_i, double x_i_ref) {

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

    int equation_code = check_equation_type(test.a);

    if (equation_code == CODE_LINEAR) {
        number_of_roots = solve_linear(test.b, test.c, &x1, &x2);
    }

    else {
        number_of_roots = solve_quadratic(test.a, test.b, test.c, &x1, &x2);
    }

    if    ((number_of_roots != test.number_of_roots_ref) 
        || (compare_wided(x1, test.x1_ref) == 0) 
        || (compare_wided(x2, test.x2_ref) == 0 )) 
    {
        printf(RED "TEST %d FAILED!\na = %lg, b = %lg, c = %lg"
                   "\nexpected amount of roots: %d"
                   "\nexpected roots: x1_ref = %lg, x2_ref = %lg"
                   "\ncalculated amount of roots: %d"
                   "\ncalculated: x1 = %lg, x2 = %lg\n\n" RESET,
                    (number+1), test.a, test.b, test.c, test.number_of_roots_ref, 
                    test.x1_ref, test.x2_ref, number_of_roots, x1, x2);

        return TEST_FAILED;
    }

    else {
        printf(GREEN "TEST %d WAS PASSED SUCCESFULLY.\n" RESET, (number+1));

        return TEST_PASSED;
    } 
}

int run_all_tests() {

    // assert(amount_of_passed_tests);
    int amount_of_passed_tests = 0;

    /*
        todo
    */

    printf("\nDoing manual tests.\n\n");

    // for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
    //     single_test_result_arr[i] = run_one_test(test_array[i], i);
    //     *amount_of_passed_tests += single_test_result_arr[i];
    // }
    amount_of_passed_tests += count_passed_tests(test_array);

    printf("\nTesting real roots equations.\n\n");

    // for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
    //     single_test_result_arr[i] = run_one_test(test_array_rand_real_roots[i], i);
    //     *amount_of_passed_tests += single_test_result_arr[i];
    // }

    amount_of_passed_tests += count_passed_tests(test_array_rand_real_roots);

    printf("\nTesting complex roots equations.\n\n");

    // for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
    //     single_test_result_arr[i] = run_one_test(test_array_rand_complex_roots[i], i);
    //     *amount_of_passed_tests += single_test_result_arr[i];
    // }

    amount_of_passed_tests += count_passed_tests(test_array_rand_complex_roots);


    printf("\nTesting linear equations\n\n");

    // for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
    //     single_test_result_arr[i] = run_one_test(test_array_rand_linear_case[i], i);
    //     *amount_of_passed_tests += single_test_result_arr[i];
    // }

    amount_of_passed_tests += count_passed_tests(test_array_rand_linear_case);
    /*
       todo
    */

    return amount_of_passed_tests;

}

int count_passed_tests(struct test_case array[]) {
    int single_test_result_arr[AMOUNT_OF_TESTS]  = {0};
    int num_of_passed_tests_single_set = 0;

    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        single_test_result_arr[i] = run_one_test(array[i], i);
        num_of_passed_tests_single_set += single_test_result_arr[i];
    }

    return num_of_passed_tests_single_set;
}

void vieta_solving(double coef_a, double x1_ref_rand, double x2_ref_rand, double* coef_b, double* coef_c) {
    *coef_b = -(x1_ref_rand + x2_ref_rand)*(coef_a);
    *coef_c =  (x1_ref_rand * x2_ref_rand)*(coef_a);
}

void coef_c_solving(double discr, double coef_a, double coef_b, double* coef_c) {
    *coef_c = (pow(coef_b, 2) - discr)/(4*coef_a);
}

int find_coef_b_when_linear(double coef_c, double x1_ref_rand, double* coef_b) {
    if (equal_to_zero_abs(coef_c) && equal_to_zero_abs(x1_ref_rand)) {
        *coef_b = (rand() % LIMIT_ROOT) - (LIMIT_ROOT / 2);

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
        *coef_a = (rand() % LIMIT_DISCR)  - (LIMIT_DISCR + 1);
    }
}

void initialize_auto_tests_array() {    
    srand(time(NULL));

    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        double coef_b, coef_c, coef_a = 0;

        rand_without_zero(&coef_a);
        double x1_ref_rand = (rand() % LIMIT_ROOT) - (LIMIT_ROOT / 2);
        double x2_ref_rand = (rand() % LIMIT_ROOT) - (LIMIT_ROOT / 2);

        if(x1_ref_rand > x2_ref_rand) {
            double temp = x1_ref_rand;
            x1_ref_rand = x2_ref_rand;
            x2_ref_rand = temp;
        }

        vieta_solving(coef_a, x1_ref_rand, x2_ref_rand, &coef_b, &coef_c);

        if (fabs(x1_ref_rand - x2_ref_rand) < NEIGHBOURHOOD) {
            test_array_rand_real_roots[i] = 
                {.a = coef_a, .b = coef_b, .c = coef_c, 
                 .number_of_roots_ref = ONE_SOLUTION, 
                 .x1_ref = x1_ref_rand, .x2_ref = x1_ref_rand};
        }

        else {
            test_array_rand_real_roots[i] = 
                {.a = coef_a, .b = coef_b, .c = coef_c, 
                 .number_of_roots_ref = TWO_SOLUTIONS, 
                 .x1_ref = x1_ref_rand, .x2_ref = x2_ref_rand};
        }
    }

    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        double coef_c, coef_a = 0;

        rand_without_zero(&coef_a);
        double discr  = (rand() % LIMIT_DISCR)  - (LIMIT_DISCR + 1);
        double coef_b = (rand() % LIMIT_COEF_A) - (LIMIT_COEF_A / 2);

        coef_c_solving(discr, coef_a, coef_b, &coef_c);

        test_array_rand_complex_roots[i] = 
        {.a = coef_a, .b = coef_b, .c = coef_c, 
         .number_of_roots_ref = NEGATIVE_PENALTY, .x1_ref = NAN, .x2_ref = NAN};
    }

    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        double coef_b = 0;

        double coef_c      = (rand() % LIMIT_COEF_A) - (LIMIT_COEF_A / 2);
        double x1_ref_rand = (rand() % LIMIT_ROOT)   - (LIMIT_ROOT / 2);

        int situation = find_coef_b_when_linear(coef_c, x1_ref_rand, &coef_b);

        if (situation == ANY_ROOT) {
            test_array_rand_linear_case[i] = 
            {.a = 0, .b = coef_b, .c = coef_c, .number_of_roots_ref = ANY_ROOT, 
             .x1_ref = 0, .x2_ref = 0};
        }

        else if (situation == NO_ROOTS) {
            test_array_rand_linear_case[i] = 
            {.a = 0, .b = 0, .c = coef_c, .number_of_roots_ref = NO_ROOTS, 
             .x1_ref = NAN, .x2_ref = NAN};
        }

        else {
            test_array_rand_linear_case[i] = 
            {.a = 0, .b = coef_b, .c = coef_c, .number_of_roots_ref = ONE_SOLUTION, 
             .x1_ref = x1_ref_rand, .x2_ref = x1_ref_rand};
        }
    }
}


void check_am_of_pt(int amount_of_passed_tests, int* inprocess) {

    assert(inprocess != NULL);

    if (amount_of_passed_tests != 4 * AMOUNT_OF_TESTS) {
        printf("\nПрограмма прошла НЕ ВСЕ тесты. (%d из %d)"
               "\nВы уверены, что хотите пользоваться этой хуетой,"
               "\nкоторая медленная, да ещё и решает неправильно? ", amount_of_passed_tests, 4 * AMOUNT_OF_TESTS);

        while(true) {
            char check_answer[SMALL];
            char* ptr_check_ans = fgets(check_answer, sizeof(check_answer) / sizeof(*check_answer), stdin);

            if (ptr_check_ans[0] == 'Y' || ptr_check_ans[0] == 'y') {
                printf("делайте домашку с этой хуетой на свой страх и риск.\n");

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
        printf("\nВсе тесты пройдены успешно. Фатамафу можно доверять.\n");
    }
}


// формат ввода: x1, x2, желаемое a
// по теореме виета восстанавливаются b, c. по a b c решается уравнение. смотрится совпадение x1 = x1 ref, x2 = x2 ref.
// с учётом эпсилон погрешности
// b = -(x1+x2)*a
// c = (x1*x2)*a
// a b c восстановлены, 