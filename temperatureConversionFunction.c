#include <stdio.h>

#define UPPER 300 /* upper limit */
#define LOWER 0 /* lower limit of temperature table */
#define STEP 20 /* step size */

float convertToFahrenheit(float celsius);
float convertToCelsius(float fahrenheit);

/* print Celsius-Fahrenheit and Fahrenheit-Celsius tables */
main() {
    float fahr, celsius;

    printf("Celsius\tFahrenheit\n");
    celsius = LOWER;
    while (celsius <= UPPER) {
        fahr = convertToFahrenheit(celsius);
        printf("%7.0f\t%10.1f\n", celsius, fahr);
        celsius = celsius + STEP;
    }

    printf("\nFahrenheit\tCelsius\n");
    fahr = LOWER;
    while (fahr <= UPPER) {
        celsius = convertToCelsius(fahr);
        printf("%10.0f\t%7.1f\n", fahr, celsius);
        fahr = fahr + STEP;
    }

    return 0;
}

float convertToFahrenheit(float celsius) {
    return ((9.0 / 5.0) * celsius) + 32.0;
}

float convertToCelsius(float fahrenheit) {
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}
