/*Часть 2, лаба 3, вариант 8.

Разработать две функции, одна из которых вводит с клавиатуры набор данных в произвольной последовательности
и размещает в памяти в заданном формате. Другая функция читает эти данные и выводит на экран.
Программа запрашивает и размещает в памяти несколько наборов данных при помощи первой функции,
а затем читает их и выводит на экран при помощи второй.
Размещение данных производить в выделенном массиве байтов с контролем его переполнения.

Упакованная строка, содержащая символьное представление целых чисел.
Все символы строки, кроме цифр, помещаются в последовательность в исходном виде.
Последовательность цифр преобразуется в целую переменную, которая записывается в упакованную строку,
предваренная символом \0. Конец строки - два подряд идущих символа \0. 
-исходная строка: "aa0x24FFbbb0xAA65"
-упакованная строка: 'a' 'a''\0' 0x24FF 'b' 'b' 'b' '\0' 0xAA65 '\0' '\0'  */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//aa0x24Fbbb0xAA65
//a0x2AAbab0xA6Fnhr

void input(char *strIn, int *len, int lenMax)
{
	printf("Enter a string up to %d:\n\n", lenMax); 
	fgets(strIn, lenMax, stdin);	
	*len = strlen(strIn) - 1;
}

bool isHexNum(char n)
{
	return (n >= '0' && n <= '9' || n >= 'A' && n <= 'F');
}

bool is0x(char o, char x)
{
	return (o == '0' && x == 'x');
}

void outputArr(char *p)
{
	while ((*p != '\0') || (*(p + 1) != '\0'))
	{
		if (*p == '\0')
		{
			printf("'\\0' ");
			p++;
			int *n = (int*)p;
			printf("'%hx' ", *n);
			n++;
			p = (char*)n;
		}
		else
		{
			printf("'%c' ", *p);
			p++;
		}
	}
	printf("'\\0' '\\0' \n\n");
}

char* arrangement(char *strIn, char *strAr, int len)
{
	char *temp = (char*)malloc(len * sizeof(char));

	int i = 0;
	for (unsigned short t = 0, l = 0; l < len; i++, l++)
	{
		if (is0x(strIn[l], strIn[l + 1]))
		{
			if(i > 0)
				strAr[i++] = '\0';
			int j = 0;
			for (int k = l + 2; !is0x(strIn[k], strIn[k + 1]) && isHexNum(strIn[k]) && j < len; j++, k++)
				temp[j] = strIn[k];

			temp[j] = '\0';

			t = strtol(temp, NULL, 16);
			strAr[i] =  t & 0xFF;
			strAr[++i] = (t >> 8) & 0xFF;

			l += strlen(temp) - 1;
		}
		else
			strAr[i] = strIn[l];
	}

	strAr[i++] = '\0';
	strAr[i] = '\0';


	free(temp);
	return strAr;
}

char* backInStr(char *strAr, char *strB, int len)
{
	for (int i = 0, b = 0; i < len +2;  b++)
	{
		if (strAr[i] == '\0')
		{
			i++;
			unsigned short t = strAr[i] | (strAr[i + 1] << 8);
					
			char temp[8] = " ";
			_itoa(t, temp, 16);
			strB[b++] = '0';
			strB[b++] = 'x';
			for(int j = 0; j < strlen(temp); j++, i++)
				strB[b++] = temp[j];
			b--;
			//i--;
		}
		else
		{
			strB[b] = strAr[i];
			i++;
		}
			
	}

	return strB;
}

int main()
{
	int lenMax = 50;
	int len = 0;
	char *strIn = (char*)malloc(lenMax * sizeof(char));
	input(strIn, &len, lenMax);

	char *strAr = (char*)malloc(1.6 * len * sizeof(char));
	strAr = arrangement(strIn, strAr, len);
	outputArr(strAr);

	char *strBack = (char*)malloc(len * sizeof(char));
	strBack = backInStr(strAr, strBack, len);

	for (int i = 0; i < len; i++)
		printf("%c", strBack[i]);
	printf("\n");

	_getch();
	free(strAr);
	free(strIn);
	free(strBack);
	return 0;
}
