int is_litera(char* ptr_buf, int position);

void totalling_num(int after_dot_index, double multiplier, size_t position, 
                   double* num_total, double* divider, 
                   int* operations_counter, char* ptr_buf);

int analyze_after_space_or_comma(char* ptr_buf, size_t* position, int* after_dot_index, 
                                 int* sign, int* counter_of_read_digits, int* if_me_in_num);

int check_input(char* ptr_buf, size_t len, double* coef_a, double* coef_b, double* coef_c);