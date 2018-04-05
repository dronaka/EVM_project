#include "Header.h"
#include <fstream>
#include <string>
#include <queue>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");
int kompil = 0;
int labelsize = 0;
int endaf;

queue<trait> quq;
labels * lab = new labels[200];
string *proga = new string[2000];

enum { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, xt, yt, ost };
trait* reg = new trait[30];

trait flag; // флаг состояний
//flag.trit[0].bit[0] этот бит отвечает за знак числа
//flag.trit[1] - этот трит отвечает за перенос, по значению. Если = 0, то переноса нет.
//flag.trit[2] и flag.trit[3] - эти триты отвечают за отношение чисел в условиях 

void Not0(trait& a) {
	for (int i = 0; i < 9; i++) {
		a.trit[i].bit[0] = !a.trit[i].bit[0];
	}
	return;
} 

void Notminus(trait& a) {
	for (int i = 0; i < 9; i++) {
		if (a.trit[i].bit[1] == 0) {
			a.trit[i].bit[1] = 1;
			a.trit[i].bit[0] = 1;
		}
		if (a.trit[i].bit[1] == 1 && a.trit[i].bit[0] == 1)
			a.trit[i].bit[1] = 0;
	}
	return;
}

void Notplus(trait& a) {
	for (int i = 0; i < 9; i++) {
		if (a.trit[i].bit[1] == 0) {
			a.trit[i].bit[1] = 1;
			a.trit[i].bit[0] = 0;
		}
		if (a.trit[i].bit[1] == 1 && a.trit[i].bit[0] == 0)
			a.trit[i].bit[1] = 0;
	}
	return;
}

int FromTriInDec(trait a) {
	int b = 0;
	int t = 1;
	for (int i = 0; i < 9; i++) {
		if (!a.trit[i].bit[1]) {}
		else
			if (a.trit[i].bit[0])
				b = b + t;
			else
				b = b - t;
		t = t * 3;
	}
	return b;
}

trait FromDecInTri(int res) {
	if (res < 0) {
		res = abs(res);
		flag.trit[0].bit[0] = 1;  // этот бит отвечает за знак числа
	}

	int t, i = 0;
	trait a;
	while (res>2) {
		t = res % 3;
		res = res / 3;
		if (t == 2)
			res++;
		if (t == 0)
			a.trit[i].bit[1] = 0;
		else {
			if (t == 1) {
				a.trit[i].bit[1] = 1;
				a.trit[i].bit[0] = 1;
			}
			else {
				a.trit[i].bit[1] = 1;
				a.trit[i].bit[0] = 0;
			}
		}
		i++;
	}
	if (res == 0)
		a.trit[i].bit[1] = 0;
	else {
		if (res == 1) {
			a.trit[i].bit[1] = 1;
			a.trit[i].bit[0] = 1;
		}
		else {
			a.trit[i].bit[1] = 1;
			a.trit[i].bit[0] = 0;
			i++;
			a.trit[i].bit[1] = 1;
			a.trit[i].bit[0] = 1;
		}
	}
	if (flag.trit[0].bit[0] == 1) {
		Not0(a);
		flag.trit[0].bit[0] = 0;
	}
	return a;

}

trit xor (trit a, trit b) {
    trit res;
	//flag.trit[1] = '0';
	if (a == '+' && b == '+')
		flag.trit[1] = '+';
	if (a == '-' && b == '-')
		flag.trit[1] = '-';
	if ((a == '0' && b == '0') || (a == '+' && b == '-') || (a =='-' && b == '+'))
		return (res = '0');
	if ((a == '-' && b == '-') || (a == '+' && b == '0') || (a == '0' && b == '+'))
		return (res = '+');
	if ((a == '+' && b == '+') || (a == '0' && b == '-') || (a == '-' && b == '0'))
		return (res = '-');
	
}

trit xand(trit a, trit b) {
	trit res;
	if (a == '0' || b == '0')
		return (res = '0');
	if ((a == '-' && b == '-') || (a == '+' && b == '+'))
		return (res = '+');
	if ((a == '+' && b == '-') || (a == '-' && b == '+'))
		return (res = '-');
}

void add(trait& a, trait& b) {
	flag.trit[1] = '0';
	for (int i = 0; i < 9; i++) {
		trit t = flag.trit[1];
		flag.trit[1] = '0';
		a.trit[i] = xor (xor (a.trit[i], b.trit[i]),t);	
	}
	flag.trit[1] = '0';
	return;
}

void sub(trait& a, trait& b) {
	Not0(b);
	add(a, b);
}

void ShiftLeft(trait& a, trait b){
	int bt = FromTriInDec(b);	
	for (int i = 8; i >= 0; i--) {
		if (i-bt>=0)
			a.trit[i] = a.trit[i-bt];
		else
			a.trit[i] = '0';
	}	
}

void ShiftRight(trait& a, trait b) {
	int bt = FromTriInDec(b);
	for (int i = 0; i <9; i++) {
		if (i + bt < 9)
			a.trit[i] = a.trit[i + bt];
		else
			a.trit[i] = '0';
	}
}

void mul(trait& a, trait& b) {
	trait t,t1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			t1.trit[j] = xand(a.trit[j], b.trit[i]);
		ShiftLeft(t1, FromDecInTri(i));
		add(t, t1);
	}
	a = t;
}

void mov(trait& a, trait b) {
	a = b;
}

void addlabel() {
	string tstr;
	bool done = 0;
	tstr = proga[kompil].substr(1);

	for (int it = 0; it < labelsize; it++)
		if (lab[it].str == tstr) { done = 1; break; }
	if (done == 0) {
		lab[labelsize].str = tstr;
		lab[labelsize].kt = kompil;
		labelsize++;
	}
}

void read() {
	while (cin >> proga[kompil]) {
		if (proga[kompil] == "Q") {
			endaf = kompil;
			break;
		}
		kompil++;
	}
	kompil = 0;
	for (kompil = 0; kompil < endaf; kompil++)
		if (proga[kompil][0] == ':') {
			addlabel();
		}
}

void J() {
	string tstr;
	tstr = proga[kompil].substr(1);
	for (int it = 0; it < labelsize; it++)
		if (lab[it].str == tstr) {
			kompil = lab[it].kt;
			break;
		}

}

void Z() {
	char t;
	string tstr;
	t = proga[kompil][1];
	tstr = proga[kompil].substr(2);
	trait tr;
	if (FromTriInDec(reg[t - 'a']) == 0) {
		for (int it = 0; it < labelsize; it++) {
			if (lab[it].str == tstr) {
				kompil = lab[it].kt;
				break;
			}
		}
	}
}

void E() {
	char t1, t2;
	string tstr;
	t1 = proga[kompil][1];
	t2 = proga[kompil][2];
	tstr = proga[kompil].substr(3);
	if (reg[t1 - 'a'] == reg[t2 - 'a']) {
		for (int it = 0; it < labelsize; it++)
			if (lab[it].str == tstr)
			{
				kompil = lab[it].kt;
				break;
			}
	}
}

void G() {
	char t1, t2;
	string tstr;
	t1 = proga[kompil][1];
	t2 = proga[kompil][2];
	tstr = proga[kompil].substr(3);
	if (FromTriInDec(reg[t1 - 'a']) > FromTriInDec(reg[t2 - 'a'])) {
		for (int it = 0; it < labelsize; it++)
			if (lab[it].str == tstr)
			{
				kompil = lab[it].kt;
				break;
			}
	}
}

void pop() {
	char t;
	t = proga[kompil][1];
	reg[xt] = quq.front();
	quq.pop();
	reg[t - 'a'] = reg[xt];
}

void push() {
	char t;
	t = proga[kompil][1];
	quq.push(reg[t - 'a']);
}

void del(trait& a, trait& b)
{
	/*
	trait t;
	int j = 8;
	while ((b.trit[j] == '0') && (j > 0))
	j--;
	for (int i = 0; i <= j; i++)
	{
	t.trit[i] = a.trit[8 - j + i];
	}
	//if (t < b)
	{
	for (int i = j + 1; i > 0; i++)
	{
	t.trit[i] = a.trit[i-1];
	}
	t.trit[0] = a.trit[8 - j - 1];
	}
	*/
	int x = FromTriInDec(a);
	int y = FromTriInDec(b);
	int cel = x / y;
	int ost = x - cel;
	reg[1] = FromDecInTri(cel);
	reg[0] = FromDecInTri(ost);
}

void P() {
	char t;
	t = proga[kompil][1];
	cout << FromTriInDec(reg[t - 'a']) << endl;
}

void C() {
	char t;
	t = proga[kompil][1];
	for (int i = 8; i >= 0; i--) {
		if (reg[t - 'a'].trit[i] == '+')
			cout << '+';
		if (reg[t - 'a'].trit[i] == '-')
			cout << '-';
		if (reg[t - 'a'].trit[i] == '0')
			cout << '0';
	}
	cout << endl;
}

void Q() {
	exit;
}

void number() {
	quq.push(FromDecInTri(stoi(proga[kompil])));
}

void Inizialization() {
	kompil = 0;
	while (kompil<endaf) {
		switch (proga[kompil][0])
		{
		case '+':
			add(reg[proga[kompil][1] - 'a'], reg[proga[kompil][2] - 'a']);
			break;
		case'-':
				sub(reg[proga[kompil][1] - 'a'], reg[proga[kompil][2] - 'a']);
			break;
		case'*':
			mul(reg[proga[kompil][1] - 'a'], reg[proga[kompil][2] - 'a']);
			break;
		case'/':
			del(reg[proga[kompil][1] - 'a'], reg[proga[kompil][2] - 'a']);
			break;
		case'>':
			pop();
			break;
		case'<':
			push();
			break;
		case'P':
			P();
			break;
		case'C':
			C();
			break;
		case':':
			break;
		case'J':
			J();
			break;
		case'Z':
			Z();
			break;
		case'E':
			E();
			break;
		case'G':
			G();
			break;
		case'Q':
			Q();
			break;
		default:
			number();
			break;
		}
		kompil++;
	}
}