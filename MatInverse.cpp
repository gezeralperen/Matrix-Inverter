// MatInverse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void getCofactor(const vector<vector<double>> &A, vector<vector<double>> &B, int r, int c)
{
	vector<double> temp;
	for (int row = 0; row < A.size(); row++)
	{
		vector<double> temp;
		for (int col = 0; col < A.size(); col++)
		{
			if (row != r && col != c)
			{
				temp.push_back(A[row][col]);
			}
		}
		if (row != r) {
			B.push_back(temp);
		}
	}
}

double getDet(const vector<vector<double>> &A)
{
	double D = 0;

	if (A.size() == 1)
		return A[0][0];

	for (int p = 0; p < A.size(); p++)
	{
		vector <vector <double>> B;
		getCofactor(A, B, 0, p);
		D += pow(-1,p) * A[0][p] * getDet(B);
	}

	return D;
}

void getAdj(const vector<vector<double>> &A, vector<vector<double>> &B)
{
	for (int y = 0; y < A.size(); y++) {
		vector<double> row;
		for (int x = 0; x < A.size(); x++) {
			vector<vector<double>> cof;
			getCofactor(A, cof, y, x);
			row.push_back(getDet(cof)*pow(-1, x+y));
		}
		B.push_back(row);
	}
}

void MatrixInverse(const vector<vector<double>> &A, vector<vector<double>> &B)
{
	vector<vector<double>> adjs;
	getAdj(A, adjs);
	double det = getDet(A);
	for (int y = 0; y < A.size(); y++) {
		vector<double> row;
		for (int x = 0; x < A.size(); x++) {
			row.push_back(adjs[x][y]/det);
		}
		B.push_back(row);
	}

}


int main()
{
	int length;
    cin >> length; 

	vector<vector<double>> matrix;
	vector<vector<double>> inverse;

	for (int y = 0; y < length; y++) {
		vector<double> row;
		for (int x = 0; x < length; x++) {
			double d;
			cin >> d;
			row.push_back(d);
		}
		matrix.push_back(row);
	}

	double det = getDet(matrix);
	if (det == 0) {
		cout << "Matrix is not invertible" << endl;
		return 0;
	}

	MatrixInverse(matrix, inverse);

	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			cout << setprecision(2) << inverse[y][x] << "\t" ;
		}
		cout << endl;
	}

	return 0;
}
