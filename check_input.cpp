#include "square_solver.h"
#include "check_input.h"

int is_litera(char* ptr_buf, size_t position) {

    assert(ptr_buf != NULL);

    if (!isdigit(ptr_buf[position])
    && (ptr_buf[position] != ' ')  && (ptr_buf[position] != ',') 
    && (ptr_buf[position] != '\n') && (ptr_buf[position] != '.') 
    && (ptr_buf[position] != '-')  && (ptr_buf[position] != '+'))
    
        return true;

    return false;
}

void totalling_num(int after_dot_index, double multiplier, size_t position, 
                   double* num_total, double* divider, 
                   int* operations_counter, char* ptr_buf) 
{
    assert((num_total != NULL) && (divider != NULL) && (operations_counter != NULL) && (ptr_buf != NULL));

    if (after_dot_index) {
        *num_total += ((ptr_buf[position] - '0') / *divider);
        *divider *= 10;
        *operations_counter += 1;
    }

    else if (!after_dot_index) {
        *num_total *= multiplier;
        *num_total += (ptr_buf[position] - '0');
        *operations_counter += 1;
    }
    
}

int analyze_after_space_or_comma(char* ptr_buf, size_t* position, int* after_dot_index, 
                                 int* sign, int* counter_of_read_digits, int* if_me_in_num) {
    
    assert((ptr_buf != NULL)  &&  (position != NULL)                &&  (after_dot_index != NULL) && 
           (sign != NULL)     &&  (counter_of_read_digits != NULL)  &&  (if_me_in_num != NULL)); 

    while (!isdigit(ptr_buf[*position])) {

        if (ptr_buf[*position] == ' ' || ptr_buf[*position] == ',') {
            *position += 1;
            *after_dot_index = 0;
        }

        else if (ptr_buf[*position] == '-' || ptr_buf[*position] == '+') {
            if (ptr_buf[*position] == '-')
                *sign *= -1;

            *position += 1;
        }

        else if (ptr_buf[*position] == '\n') {
            break;
        }

        else if (ptr_buf[*position] == '.') {
            *after_dot_index = 1;
            *position += 1;
        }

        else {
            printf("\nНеккоректный ввод!, %d ,Жесткий тип\n", ptr_buf[*position]);

            return INCORRECT_INPUT;
        }
    }
    *if_me_in_num = 1;
    *counter_of_read_digits += 1;

    return 0; // абсолютно необязателен, поскоку я его нигде не сохраняю.
}

int check_input(char* ptr_buf, size_t len, double* coef_a, double* coef_b, double* coef_c) {

    assert((ptr_buf != NULL) && (coef_a != NULL) && (coef_b != NULL) && (coef_c != NULL));

    if (ptr_buf == NULL)  {
        return USER_SUSPENDED;
    }
                                                                                                                                                                                                
    int after_dot_index          = 0;
    int real_number_of_coeffs[3] = {0};
    int counter_of_read_digits   = 0;

    size_t i = 0;

    int if_me_in_num = 0;
    int dots_counter = 0;

    double res_buf[COEFF_AMOUNT] = {0, 0, 0};

    for (int g = 0; g < COEFF_AMOUNT; g++) { //TODO
        double num_total  = 0;
        double multiplier = 10;
        double divider    = 10;

        int sign = 1;
        int operations_counter = 0;

        for (i; i < len; i++) {

            if (ptr_buf[i] == 'q' || ptr_buf[i] == 'Q')  {

                return EXIT;
            }

            else if (is_litera(ptr_buf, i)) {
                printf("Неккоректный ввод!\n");

                return INCORRECT_INPUT;
            }

            else if (ptr_buf[i] == '-') {
                if (if_me_in_num) {
                    printf("Неккоректный ввод! минус внутри/сразу после числа.\n");
                    
                    return INCORRECT_INPUT;
                }
                sign *= -1;
            }
            
            else if (ptr_buf[i] == '+') {
                if (if_me_in_num) {
                    printf("Неккоректный ввод! плюс внутри/сразу после числа.\n");
                    
                    return INCORRECT_INPUT;
                }
            }

            else if (isdigit(ptr_buf[i])) {
                if_me_in_num = 1;
                counter_of_read_digits++;
                totalling_num(after_dot_index, multiplier, i, 
                              &num_total, &divider, 
                              &operations_counter, ptr_buf);
            }

            else if (ptr_buf[i] == '.') {
                dots_counter += 1;

                if (ptr_buf[i-1] == '.') {
                    printf("точки, идущие подряд. некорректный ввод!\n");

                    return INCORRECT_INPUT;
                }

                else if (if_me_in_num && dots_counter > 1) {
                    printf("если эта ошибка прокнула, вы точно дебагер)).\n");
                    
                    return INCORRECT_INPUT;
                }

                after_dot_index = 1;
            }
        
            else if ((ptr_buf[i] == ' ' || ptr_buf[i] == ',') && counter_of_read_digits == 0) {
                if_me_in_num    = 0;
                dots_counter    = 0;
                after_dot_index = 0;
                analyze_after_space_or_comma(ptr_buf, &i, &after_dot_index, &sign, &counter_of_read_digits, &if_me_in_num);
                totalling_num(after_dot_index, multiplier, i, 
                              &num_total, &divider, 
                              &operations_counter, ptr_buf);
            }

            else if ((ptr_buf[i] == ' ' || ptr_buf[i] == ',') && counter_of_read_digits != 0) {
                if_me_in_num = 0;
                dots_counter = 0;
                
                if(isdigit(ptr_buf[i-1])) {
                    i++;
                    after_dot_index = 0;
                    break;
                }

                after_dot_index = 0;
                analyze_after_space_or_comma(ptr_buf, &i, &after_dot_index, &sign, &counter_of_read_digits, &if_me_in_num);
                totalling_num(after_dot_index, multiplier, i, 
                              &num_total, &divider, 
                              &operations_counter, ptr_buf);
            }
        }

        real_number_of_coeffs[g] = operations_counter;
        num_total *= sign;
        res_buf[g] = num_total;
    }

    *coef_a = res_buf[0];
    *coef_b = res_buf[1];
    *coef_c = res_buf[2];

    printf("\nЯ думаю, вы имели в виду: a: %.7f b: %.7f c: %.7f\n", res_buf[0], res_buf[1], res_buf[2]); // отладочный

    for (int l = 0; l < 3; l++) {
        if (real_number_of_coeffs[l] == 0) {
            printf("Кто-то не ввёл коэффициент!\n");

            return INCORRECT_INPUT;
        }
    }
    return SUCCESS;
}