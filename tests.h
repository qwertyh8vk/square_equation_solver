#ifndef TESTS_H
#define TESTS_H

int run_one_test(struct test_case test, int number); // файл тесты.спп
int run_all_tests(); // файл тесты.спп
int compare_wided(double x_i, double x_i_ref); // файл тесты.спп
void check_am_of_pt(int amount_of_passed_tests, int* inprocess); // файл тесты.спп

#endif