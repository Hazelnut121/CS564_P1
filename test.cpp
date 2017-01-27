#include<iostream>
#include<string>

using namespace std;

string* test() {
	string* st;
	st = new string[2];
	st[0] = "12345";
	st[1] = "1234";
	return st;
}
int main() {
	string* st = test();
	delete[] st;
	return 0;
}
