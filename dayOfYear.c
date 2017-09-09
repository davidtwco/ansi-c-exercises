static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;
    char *p;

    if (year < 1 || month < 1 || month > 12 || day < 1)
        return -1;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (day > daytab[leap][month])
        return -1;

    p = &daytab[leap][1];

    for (i = 1; i < month; i++) {
        day += *p;
        ++p;
    }
    return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    char *p;

    if (year < 1 || yearday < 1)
        return -1;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if ((leap && yearday > 356) || (!leap && yearday > 355))
        return -1;

    p = &daytab[leap][1];

    for (i = 1; yearday > *p; i++) {
        yearday -= *p;
        ++p;
    }
    *pmonth = i;
    *pday = yearday;
    return 0;
}
