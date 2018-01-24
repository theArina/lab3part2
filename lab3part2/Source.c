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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void input(char *strIn, int *len, int lenMax)
{
	printf("Enter a string up to %d:\n\n", lenMax); 
	fgets(strIn, lenMax, stdin);
	//strIn = "aa0x24FFbbb0xAA65";
	*len = strlen(strIn);
}

bool isHexNum(char n)
{
	return (n >= '0' && n <= '9' || n >= 'A' && n <= 'F');
}

bool is0x(char o, char x)
{
	return (o == '0' && x == 'x');
}

void arrangement(char *strIn, int len, int lenMax)
{
	char *strAr = (char*)malloc(len * sizeof(char));
	char *temp = (char*)malloc(len * sizeof(char));

	for (int i = 0; i < len; i++)
	{
		if (is0x(strIn[i], strIn[i + 1]))
		{
			int j = 0;
			for (int k = i + 2; is0x(strIn[k], strIn[k + 1]) == 0 && isHexNum(strIn[k]) == 1 && j < len; j++, k++)
				temp[j] = strIn[k];

			temp[j] = '\0';
			(int)strAr[i] = strtol(temp, NULL, 16);
			printf("%x ", strAr[i]);

		}
		else
			strAr[i] = strIn[i];
	}

	//for (int i = 0; i < len; i++)
	//	printf("%c ", strAr[i]);
	printf("\n");

	free(temp);
	free(strAr);

}

int main()
{
	int lenMax = 50;
	int len = 0;
	char *strIn = (char*)malloc(lenMax * sizeof(char));

	input(strIn, &len, lenMax);
	arrangement(strIn, len, lenMax);

	_getch();
	free(strIn);
	return 0;
}