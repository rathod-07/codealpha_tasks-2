#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[500], date[50];
    char *data[10];
    int year, count = 0;
    int preCount = 0, covidCount = 0;
    float rate, total = 0;
    float preTotal = 0, covidTotal = 0;
    float highest = 0, lowest = 100;

    fp = fopen("unemployment.csv", "r");

    if (fp == NULL) {
        printf("Dataset file not found!\n");
        return 1;
    }

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        int i = 0;
        char *token = strtok(line, ",");

        while (token != NULL && i < 10) {
            data[i++] = token;
            token = strtok(NULL, ",");
        }

        if (i < 5)
            continue;

        strcpy(date, data[1]);

        int len = strlen(date);
        if (len < 4)
            continue;

        year = atoi(date + len - 4);
        rate = atof(data[3]);

        if (year < 1900 || rate < 0 || rate > 100)
            continue;

        total += rate;
        count++;

        if (rate > highest)
            highest = rate;

        if (rate < lowest)
            lowest = rate;

        if (year < 2020) {
            preTotal += rate;
            preCount++;
        } else {
            covidTotal += rate;
            covidCount++;
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No valid data found!\n");
        return 1;
    }

    printf("\nUNEMPLOYMENT ANALYSIS\n");
    printf("-----------------------------\n");

    printf("Total Records: %d\n", count);
    printf("Average Unemployment Rate: %.2f%%\n",
           total / count);

    printf("Highest Unemployment Rate: %.2f%%\n", highest);
    printf("Lowest Unemployment Rate: %.2f%%\n", lowest);

    printf("\nCOVID-19 IMPACT ANALYSIS\n");
    printf("-----------------------------\n");

    if (preCount > 0)
        printf("Before COVID Average: %.2f%%\n",
               preTotal / preCount);

    if (covidCount > 0)
        printf("During/After 2020 Average: %.2f%%\n",
               covidTotal / covidCount);

    printf("\nAnalysis Completed Successfully!\n");

    return 0;
}