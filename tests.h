int run_one_test(struct test_case test, int number); // файл тесты.спп
int run_all_tests(); // файл тесты.спп
int compare_including_nans(double x_i, double x_i_ref); // файл тесты.спп

void check_num_of_passed_tests(int amount_of_passed_tests, int* inprocess); // файл тесты.спп
void check_num_of_passed_tests_tflag(int amount_of_passed_tests); // скорее временное решение!!!

int find_coef_b_when_linear(double coef_c, double x1_ref_rand, double* coef_b);

void vieta_reverse(double coef_a, double x1_ref_rand, double x2_ref_rand, double* coef_b, double* coef_c);
void coef_c_reverse(double discr, double coef_a, double coef_b, double* coef_c);

void initialize_positive_discr_structs_arr();
void initialize_negative_discr_structs_arr();
void initialize_linear_structs_arr();
void initialize_auto_tests_structs_array();

int count_passed_tests(struct test_case test_array[]);
