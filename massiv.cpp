#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	int massiv[9];
	int n;
	cin >> n;
	int first, last, count;
	first = 0; last = 9;
	while (first >= last) {
		if (massiv[first] + massiv[last] == n) {
			count++;
			first++;
		}
		else{
			if (massiv[first] + massiv[last] < n) { first++; }
			else { last--; }
		}
		
		cout << count;
	}

}
