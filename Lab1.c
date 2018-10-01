/*
 *
 * Lab1.c
 * Takes three numbers as input and calculates mean
 * and standard deviation.
 *
 * Author: Naveed Ashfaq
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getMean(double, double, double);
double getStdDev(double, double, double, double);

int main(void)
{
	double num1, num2, num3, mean, stdDev;
	printf("Enter three numbers: ");
	scanf("%lf %lf %lf", &num1, &num2, &num3);
	mean = getMean(num1, num2, num3);
	stdDev = getStdDev(num1, num2, num3, mean);
	printf("The mean is %0.2lf and the standard deviation is %0.2lf", mean, stdDev);
	return 0;
}

double getMean(double num1, double num2, double num3)
{
	double inputSum = num1 + num2 + num3;
	return inputSum/3;
}

double getStdDev(double num1, double num2, double num3, double mean)
{
	double inputNumbers[3]={num1, num2, num3}, summation=0;
	for (int i = 0; i < 3; i++) {
		summation += pow((inputNumbers[i] - mean), 2);
	}
	return sqrt(summation/(3-1));
}
