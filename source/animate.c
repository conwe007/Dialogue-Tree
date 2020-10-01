#include "animate.h"

/**
 * Delays program execution for a specified number of milliseconds
 * 
 * @param ms the number of milliseconds to delay
 */
void animate_delay_ms(int ms)
{
    clock_t end = animate_clock_val_after_ms(ms);

    while(clock() < end);
}

/**
 * Finds the clock value after a specified number of milliseconds
 * 
 * @param ms the number of milliseconds to add to the current clock value
 * @return the clock value 'ms' milliseconds in the future
 */
clock_t animate_clock_val_after_ms(int ms)
{
    clock_t begin = clock();
    int clock_ticks = ms * CLOCKS_PER_SEC / (1000);

    return (clock_t)((int)begin + clock_ticks);
}

/**
 * Prints a string to stdout with a delay of ms between each character
 * 
 * @param string the string to print
 * @param ms the delay between each character in milliseconds
 */
void animate_print_string_delay_ms(char* string, int ms)
{
    clock_t end;
    int index_string = 0;
    
    while(string[index_string] != '\0')
    {
        end = animate_clock_val_after_ms(ms);

        printf("%c", string[index_string]);
        fflush(stdout);
        index_string++;

        while(clock() < end);
    }
}



