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



//bit[1] - ����������� ���, ���� �� = 0, �� �������� = 0. ������ ��� ���������� ����: 0 = -; 1 = +;

struct trait { // 9 ������ 3^9 = 9841
	trit trit[9];
	bool operator== (trait s) {
		for (int i = 0; i < 9; i++)
			if (!(this->trit[i] == s.trit[i]))
				return 0;
		return 1;
	}
};

 //��������� �����
struct labels {
	string str;
	int kt;
};





// �������� ��������
void Not0(trait& a);
void Notminus(trait& a);
void Notplus(trait& a);

int FromTriInDec(trait a); // ������� �� �������� � ����������
trait FromDecInTri(int res); // ������� �� ���������� � ��������

trit xor (trit a, trit b);// ���������� ��������� �� ������ ��� ���� ������ � �������� � �������� � �����
trit xand(trit a, trit b);// ���������� ��������� �� ������ ��� ���� ������
 

void add(trait& a, trait& b); // �������� ���� ��������� ���� trait � ������� ���������� � ������ �������

void sub(trait& a, trait& b);// �������� ���� ��������� ���� trait � ������� ���������� � ������ �������

void mul(trait& a, trait& b);// ��������� ���� ��������� ���� trait � ������� ���������� � ������ �������

void ShiftLeft(trait& a, trait b); // ����� ����� ����� � �� �������� b. ��������� ������������ � ������ �������

void ShiftRight(trait& a, trait b); // ����� ������ ����� � �� �������� b. ��������� ������������ � ������ �������

void mov(trait& a, trait b); // ������������ �������� � �������� �������� b

void del(trait& a, trait& b); // ������� ���� ���������, ������� ������������ � ������ �������, ������� � ����������� ������� reg[ost]

void read(); // ������� ������� �������� ���� � ������

void Inizialization(); //��������� ��������� ����

/*
+[reg1][reg2] // �����
-[reg1][reg2] // ���������
/[reg1][reg2] //������� 
*[reg1][reg2]
=[reg][number]
Q // ����� ���������
>[reg] // �������� � ����
<[reg] // ������ �� �����
:[label] // ������ �����
J[label] // �������
Z[reg][label] // �������, ���� reg == 0
E[reg1][reg2][label] // �������, ���� reg1 == reg2
G[reg1][reg2][label] // �������, ���� reg1>reg2
*/