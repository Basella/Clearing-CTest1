#include <stdio.h>
#include <stdlib.h>

//remove the lowest value
int * remove_lowest(int *t, int len, int position_lowest) {
    //remove lowest value
    for (int jk = position_lowest; jk < len; jk++)
    {
        t[jk] = t[jk + 1];
    }
    len--;
    return t;
}

//remove the highest value
int * remove_highest(int *t, int leng, int position_highest) {
    //remove highest value
    for (int kp = position_highest; kp < leng; kp++)
    {
        t[kp] = t[kp + 1];
    }
    leng--;
    return t;
}

// process the array by removing the lowest and highest and doing a sum of the remaining numbers
int process_line(int *t, int rows) {
    int lowest, highest;
    int i, j, l, m;
    int sum = 0;
    lowest = t[0];
    highest = t[0];
    int position_lowest = 0;
    int position_highest = 0;
    int * lowest_removed;
    int * highest_removed;
    int hg = 0;
    int * t_re;
    int * r_te;
    
    // find lowest value
    for (i = 0; i < rows; i++)
    {
        if (t[i] < lowest)
        {
            lowest = t[i];
            position_lowest = i;
        }
    }

    //call lowest remover method
    lowest_removed = remove_lowest(t, rows, position_lowest);
    rows--;

    //find highest value
    for (i = 0; i < rows; i++)
    {
        if (t[i] > highest) {
            highest = t[i];
            position_highest = i;
        }
    }

    //call highest remover method
    highest_removed = remove_highest(lowest_removed, (rows), position_highest);
    rows--;
    
    //remove duplicate lowest and/or highest
    while (hg < rows)
    {
        if (highest_removed[hg] == lowest)
        {
            t_re = remove_lowest(highest_removed, rows, hg);
            highest_removed = t_re;
            rows--;
            hg--;
        } else if (highest_removed[hg] == highest)
        {
            r_te = remove_highest(highest_removed, rows, hg);
            highest_removed = r_te;
            rows--;
            hg--;
        } else
        {
            hg++;
        }
    }
    //sum the remaining numbers
    if (highest_removed)
    {
        //if array length is zero, set sum to zero
        if (rows == 0)
        {
            sum = 0;
        } else
        {
            for (m = 0; m < rows; m++)
            {
                sum = sum + t[m];
            }
        }
    }
    return sum;
}

int main () {
    int values_of_test_case = 0;
    int total_num_test_cases, g, position;
    int end;
    char num[BUFSIZ];
    int* array_of_test_case;
    int outer_array_count =0;
    int h =0;
    int processed_array_result = 0;

    //request the total number of test cases
    // printf("Please enter the number of test cases intended: ");
    scanf( "%d", &total_num_test_cases);
    // printf("\nTotal number of test cases expected: %d\n", total_num_test_cases);
    array_of_test_case = (int*)malloc(sizeof(int)*total_num_test_cases);

    //flush input buffer
    while ((end = getchar()) != '\n' && end != EOF);
    
    do
    {
        int* numbe;
        position = 0;
        g = 0;
        //request the test case
        // printf("\nPlease enter the number of this test case along with its corresponding values, Test case (%d): ", h + 1);
        if ((fgets(num, BUFSIZ, stdin)))
        {
            numbe = (int*)malloc(sizeof(int)*atoi(&num[g]));
            while (num[g] != '\0')
            {                
                if ((num[g] != ' ')) {
                    // if ((num[g] < 1) || (num[g] > 10))
                    // {
                    //     perror("Sorry, only input numbers between 1 and 10");      
                    // }
                    if ((num[g] == '\n')) break;
                    if (g > (sizeof(numbe)/sizeof(int)))
                    {
                        numbe = realloc(numbe, (g + 1)*sizeof(int));
                        if (numbe == NULL)
                        {
                            perror("Insufficient memory");
                            break;
                        }
                    }
                    numbe[position] = atoi (&num[g]);
                    position++; 
                    g++;
                } else g++;
            }
        }

        //remove the first element in the array
        for (int o = 0; o < position-1; o++)
        {
            numbe[o] = numbe[o + 1];
        }
        position--;
        // process test case without the first element
        processed_array_result = process_line(numbe, position);

        if (h > (sizeof(array_of_test_case)/sizeof(int)))
        {
            if (h ==( total_num_test_cases - 1))
            {
                array_of_test_case[h] = processed_array_result;
                break;
            }
            array_of_test_case = realloc(array_of_test_case, (h + 1)*sizeof(int));
            if (array_of_test_case == NULL)
            {
                perror("Insufficient memory");
                break;
            }
        }
        //add test case result to new array
        array_of_test_case[h] = processed_array_result;

        h++;
        free(numbe);
        outer_array_count++;
        values_of_test_case++;
    } while (values_of_test_case < total_num_test_cases); //request test cases not exceeding the total

    //print out result
    for (int u = 0; u < total_num_test_cases; u++)
    {
        printf("\n%d", array_of_test_case[u]);
    }
    free(array_of_test_case);
    return 0;
}