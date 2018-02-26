//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include "intal.h"

int main() {
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal* i3 = create_intal();
	intal* i4 = create_intal();

	read_intal(i1, "-1234");
	read_intal(i2, "+12345678");
	read_intal(i3, "+99999999");
	read_intal(i4, "+6");

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("i3 = ");
	print_intal(i3);
	printf("\n");
	
	printf("i4 = ");
	print_intal(i4);
	printf("\n");
	
	printf("Sum of i2,i3 = ");
	print_intal(add_intal(i2,i3));
	printf("\n");
	printf("Difference of i3,i2 = ");
	print_intal(subtract_intal(i3,i2));
	printf("\n");
	printf("Product of i2,i3 = ");
	print_intal(multiply_intal(i2,i3));
	printf("\n");
	printf("Quotient of i2/i1 = ");
	print_intal(divide_intal(i2,i1));
	printf("\n");
	printf("i2 to the power i4 = ");
	print_intal(pow_intal(i2,i4));
	printf("\n");
	
	delete_intal(&i1);
	delete_intal(&i2);
	delete_intal(&i3);
	delete_intal(&i4);

	return 0;
}
