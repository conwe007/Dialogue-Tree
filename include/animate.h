#ifndef __ANIMATE_H
#define __ANIMATE_H

#include <stdio.h>
#include <time.h>

/**
 * Delays program execution for a specified number of milliseconds
 * 
 * @param ms the number of milliseconds to delay
 */
void animate_delay_ms(int ms);

/**
 * Finds the clock value after a specified number of milliseconds
 * 
 * @param ms the number of milliseconds to add to the current clock value
 * @return the clock value 'ms' milliseconds in the future
 */
clock_t animate_clock_val_after_ms(int ms);

/**
 * Prints a string to stdout with a delay of ms between each character
 * 
 * @param string the string to print
 * @param ms the delay between each character in milliseconds
 */
void animate_print_string_delay_ms(char* string, int ms);

#endif /* __ANIMATE_H */
