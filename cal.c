#include <stdio.h>

int main(void)
{
	int first_num;
	int sec_num;

	printf("Enter first number: ");
	scanf("%d", &first_num);
	printf("%d divided by: ", first_num);
	scanf("%d", &sec_num);

	int total = first_num / sec_num;

	printf("%d / %d = %d\n", first_num, sec_num, total);

	int ans = total % 10;

	printf("Ans = ", ans);

	if (ans == 0)
	{
		printf("No remainder\n");
	}
	else
	{
		printf("Remainder %d", ans);
	}
}