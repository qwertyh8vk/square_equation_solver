#ifndef TESTS_H
#define TESTS_H

int run_one_test(struct test_case test, int number); // файл тесты.спп
int run_all_tests(); // файл тесты.спп
int compare_wided(double x_i, double x_i_ref); // файл тесты.спп

void check_am_of_pt(int amount_of_passed_tests, int* inprocess); // файл тесты.спп
int find_coef_b_when_linear(double coef_c, double x1_ref_rand, double* coef_b);

void vieta_solving(double coef_a, double x1_ref_rand, double x2_ref_rand, double* coef_b, double* coef_c);
void coef_c_solving(double discr, double coef_a, double coef_b, double* coef_c);
void initialize_auto_tests_array();

int count_passed_tests(struct test_case array[]);

#endif
// suetologia, checking how vs code commit works;