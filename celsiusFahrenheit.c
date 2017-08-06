#include <stdio.h>

/* print Celsius-Fahrenheit table
    for celsius = 0, 20, ..., 300 */
main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0; /* lower limit of temperature table */
    upper = 300; /* upper limit */
    step = 20; /* step size */

    printf("Celsius\tFahrenheit\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = ((9.0 / 5.0) * celsius) + 32.0;
        printf("%7.0f\t%10.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
