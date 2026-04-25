#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char* my_strcpy(char* pd, char* ps);
char* my_strcat(char* pd, char* ps);
int my_strlen(char* ps);
int my_strcmp(char* pa, char* pb);


int main(void)
{
	char str[80] = "strawberry";

	printf("바꾸기 전 문자열 : %s\n", str);
	my_strcpy(str, "apple");
	printf("바꾼 후 문자열 : %s\n", str);
	printf("다른 문자열 대입 : %s\n", my_strcpy(str, "kiwi"));

	return 0;
}

char* my_strcpy(char* pd, char* ps)
{
	char* po = pd;

	while (*ps != '\0')
	{
		*pd = *ps;
		pd++;
		ps++;
	}

	*pd = '\0';

	return po;
}

char* my_strcat(char* pd, char* ps)
{
	char* po = pd;

	while (*pd != '\0')		//	널 문자 나올때까지 포인터 이동
	{
		pd++;
	}
	while (*ps != '\0')
	{
		*pd = *ps;
		pd++;
		ps++;
	}
	*pd = '\0';
	return po;
}

int my_strlen(char* ps)
{
	int cnt = 0;
	while (*ps != '\0')
	{
		cnt++;
		ps++;
	}
	return cnt;
}

int my_strcmp(char* pa, char* pb)
{
	while ((*pa == *pb) && (*pa != '\0'))
	{
		pa++;
		pb++;
	}

	if (*pa > *pb) return 1;
	else if (*pa < *pb) return -1;
	else return 0;
}
