#pragma once
#include <string>
using namespace std;
struct trit {
	bool bit[2] = { 0, 0 };
	trit operator= (char s) {
		if (s == '+') {
			this->bit[0] = 1;
			this->bit[1] = 1;
		}
		if (s == '-') {
			this->bit[0] = 0;
			this->bit[1] = 1;
		}
		if (s == '0') {
			this->bit[0] = 0;
			this->bit[1] = 0;
		}
		return *this;
	}
	bool operator== (char s) {
		if (s == '+') {
			if (this->bit[0] == 1 && this->bit[1] == 1)
				return 1;
			else
				return 0;
		}
		if (s == '-') {
			if (this->bit[0] == 0 && this->bit[1] == 1)
				return 1;
			else return 0;
		}
		if (s == '0') {
			if (this->bit[1] == 0)
				return 1;
			else
				return 0;
		}
	}

	bool operator==(trit s) {
		if (this->bit[1] == s.bit[1]) {
			if (this->bit[0] == s.bit[0])
				return 1;
			else
				if (s.bit[1] == 0)
					return 1;
				else
					return 0;
		}
		else
			return 0;
	}
};



//bit[1] - управляющий бит, если он = 0, то значение = 0. Второй бит показывает знак: 0 = -; 1 = +;

struct trait { // 9 тритов 3^9 = 9841
	trit trit[9];
	bool operator== (trait s) {
		for (int i = 0; i < 9; i++)
			if (!(this->trit[i] == s.trit[i]))
				return 0;
		return 1;
	}
};

 //структура меток
struct labels {
	string str;
	int kt;
};





// Операции инверсии
void Not0(trait& a);
void Notminus(trait& a);
void Notplus(trait& a);

int FromTriInDec(trait a); // перевод из троичной в десятичной
trait FromDecInTri(int res); // перевод из десятичной в троичную

trit xor (trit a, trit b);// логическое сложениес по модулю три двух тритов с пометкой о переносе в флаге
trit xand(trit a, trit b);// логическое умножение по модулю три двух тритов
 

void add(trait& a, trait& b); // сложение двух регистров типа trait с записью результата в первый регистр

void sub(trait& a, trait& b);// разность двух регистров типа trait с записью результата в первый регистр

void mul(trait& a, trait& b);// умножение двух регистров типа trait с записью результата в первый регистр

void ShiftLeft(trait& a, trait b); // сдвиг влево числа а на значение b. Результат сохранияется в первый регистр

void ShiftRight(trait& a, trait b); // сдвиг вправо числа а на значение b. Результат сохранияется в первый регистр

void mov(trait& a, trait b); // присваивание регистру а значение регистра b

void del(trait& a, trait& b); // деление двух регистров, частное записывается в первый регистр, остаток в специальный регистр reg[ost]

void read(); // рабочая функция загрузки кода в память

void Inizialization(); //выполение основного кода

/*
+[reg1][reg2] // сумма
-[reg1][reg2] // вычмтание
/[reg1][reg2] //деление 
*[reg1][reg2]
=[reg][number]
Q // конец программы
>[reg] // добавить в стек
<[reg] // вынуть из стека
:[label] // задать метку
J[label] // переход
Z[reg][label] // переход, если reg == 0
E[reg1][reg2][label] // переход, если reg1 == reg2
G[reg1][reg2][label] // переход, если reg1>reg2
*/