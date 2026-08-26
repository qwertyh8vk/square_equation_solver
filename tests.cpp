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

    int equation_code = check_equation_type(test.a, test.b, test.c);

    if (equation_code == CODE_LINEAR)
        number_of_roots = solve_linear(test.b, test.c, &x1, &x2);
    else 
        number_of_roots = solve_quadratic(test.a, test.b, test.c, &x1, &x2);

    if ((number_of_roots != test.number_of_roots_ref) || (compare_wided(x1, test.x1_ref) == 0) || (compare_wided(x2, test.x2_ref) == 0 )) {
        printf(RED "TEST %d FAILED!\na = %lg, b = %lg, c = %lg"
                   "\nexpected amount of roots: %d"
                   "\nexpected roots: x1_ref = %lg, x2_ref = %lg"
                   "\ncalculated amount of roots: %d"
                   "\ncalculated: x1 = %lg, x2 = %lg\n" RESET,
                    number, test.a, test.b, test.c, test.number_of_roots_ref, 
                    test.x1_ref, test.x2_ref, number_of_roots, x1, x2);

        return TEST_FAILED;
    }

    else {
        printf(GREEN "TEST %d WAS PASSED SUCCESFULLY.\n" RESET, number);

        return TEST_PASSED;
    } 
}

int run_all_tests() {
    int amount_of_passed_tests    = 0;
    int single_test_result_arr[8] = {0};

    single_test_result_arr[0] = run_one_test(test1, 1);
    single_test_result_arr[1] = run_one_test(test2, 2);
    single_test_result_arr[2] = run_one_test(test3, 3);
    single_test_result_arr[3] = run_one_test(test4, 4);
    single_test_result_arr[4] = run_one_test(test5, 5);
    single_test_result_arr[5] = run_one_test(test6, 6);
    single_test_result_arr[6] = run_one_test(test7, 7);
    single_test_result_arr[7] = run_one_test(test8, 8);
      
    for (int i = 0; i < AMOUNT_OF_TESTS; i++) {
        amount_of_passed_tests += single_test_result_arr[i];
    }

    return amount_of_passed_tests;
}

void check_am_of_pt(int amount_of_passed_tests, int* inprocess) {

    assert(inprocess != NULL);

    if (amount_of_passed_tests != AMOUNT_OF_TESTS) {
        printf("\nПрограмма не прошла некоторые тесты."
               "\nВы уверены, что хотите пользоваться этой хуетой,"
               "\nкоторая медленная, да ещё и решает неправильно? ");

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
