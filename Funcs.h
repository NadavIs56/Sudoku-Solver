#include <iostream>
using namespace std;
#define SIZE 9

void Print(int**);

int** Fill() {
	int** matrix = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
		matrix[i] = new int[SIZE];
	cout << "Enter numbers" << endl;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			cin >> matrix[i][j];
	return matrix;
}

void CalcSqrStart(int row, int col, int& nrow, int& ncol){

	nrow = row / 3;
	ncol = col / 3;

	if (nrow == 1)
		nrow = 3;
	else if (nrow == 2)
		nrow = 6;

	if (ncol == 1)
		ncol = 3;
	else if (ncol == 2)
		ncol = 6;
}

bool ZerosCalc(int** matrix) {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (matrix[i][j] == 0)
				return true;
	return false;
}

int EmptyPlaces(int** matrix, int row, int col) {
	int count = 0, nrow, ncol;
	CalcSqrStart(row, col, nrow, ncol);

	for (int i = nrow; i < nrow + 3; i++)
		for (int j = ncol; j < ncol + 3; j++)
			if (matrix[i][j] == 0)
				count++;
	return count;
}

bool SameSqr(int** matrix, int row, int col, int val) {
	int nrow, ncol;
	CalcSqrStart(row, col, nrow, ncol);
	for (int i = nrow; i < nrow + 3; i++)
		for (int j = ncol; j < ncol + 3; j++)
			if (matrix[i][j] == val)
				return true;
	return false;
}

bool SameRow(int** matrix, int row, int val) {
	for (int i = 0; i < SIZE; i++)
		if (matrix[row][i] == val)
			return true;
	return false;
}

bool SameCol(int** matrix, int col, int val) {
	for (int i = 0; i < SIZE; i++)
		if (matrix[i][col] == val)
			return true;
	return false;
}

int NotGoodPlaces(int** matrix, int row, int col, int temp) {
	int count = 0, nrow, ncol;
	CalcSqrStart(row, col, nrow, ncol);
	for (int i = nrow; i < nrow + 3; i++)
		for (int j = ncol; j < ncol + 3; j++)
			if(matrix[i][j]==0)
				if (SameSqr(matrix, i, j, temp) || SameRow(matrix, i, temp) || SameCol(matrix, j, temp))
					count++;
	return count;
}

void SetNumber(int** matrix, int row, int col, int val) {
	int count = 0, nrow, ncol;
	CalcSqrStart(row, col, nrow, ncol);
	for (int i = nrow; i < nrow + 3; i++)
		for (int j = ncol; j < ncol + 3; j++)
			if (SameRow(matrix, i, val)==false && SameCol(matrix, j, val)==false)
				if(matrix[i][j] == 0)
					matrix[i][j] = val;
				
}

void Print(int** matrix) {
	cout << endl;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) {
			cout << matrix[i][j] << " ";
			if (j > 0 && (j+1) % 3 == 0) 
				cout << " ";
			
		}
		if (i > 0 && (i+1) % 3 == 0) 
			cout << endl;
		
		cout << endl;
	}
	cout << endl << endl;
}

int RowEmptyPlcs(int** matrix, int row){
	int count = 0;
	for (int i = 0; i < SIZE; i++)
		if (matrix[row][i] == 0)
			count++;
	return count;
}

int ColEmptyPlcs(int** matrix, int col) {
	int count = 0;
	for (int i = 0; i < SIZE; i++)
		if (matrix[i][col] == 0)
			count++;
	return count;
}

void SetInRow(int** matrix, int row, int val) {
	for (int i = 0; i < SIZE; i++)
		if (SameCol(matrix, i, val) == false && matrix[row][i]==false && SameSqr(matrix, row, i, val)==false)
		{
			matrix[row][i] = val;
			Print(matrix);
			i = SIZE;
		}
}

void SetInCol(int** matrix, int col, int val) {
	for (int i = 0; i < SIZE; i++)
		if (SameRow(matrix, i, val) == false && matrix[i][col] ==  false && SameSqr(matrix, i, col ,val)==false)
		{
			matrix[i][col] = val;
			Print(matrix);
			i = SIZE;
		}
}

int RepInCols(int** matrix, int row, int val) {
	int count = 0;
	for (int i = 0; i < SIZE; i++)
		if (matrix[row][i] == 0)
			if (SameCol(matrix, i, val) || SameSqr(matrix, row, i, val))
				count++;
	return count;
}

int RepInRows(int** matrix, int col, int val) {
	int count = 0;
	for (int i = 0; i < SIZE; i++)
		if (matrix[i][col] == 0)
			if (SameRow(matrix, i, val) || SameSqr(matrix, i , col, val))
				count++;
	return count;
}

void FillLikePro(int** matrix) {
	int empty = 0, rep=0;
	for (int c = 1; c <= SIZE; c++)
		for (int i = 0; i < SIZE; i++)
		{
			empty = RowEmptyPlcs(matrix, i);
			 if ((SameRow(matrix, i, c)) == false)
			{
				rep = RepInCols(matrix, i, c);
				//cout << "c = " << c << " row = " << i << " empty = " << empty << " rep = " << rep << endl;
				if ((empty - rep) == 1)
					SetInRow(matrix, i, c);
			}
			empty = 0;
			rep = 0;
		}

	for (int c = 1; c <= SIZE; c++)
		for (int i = 0; i < SIZE; i++)
		{
			empty = ColEmptyPlcs(matrix, i);
			if ((SameCol(matrix, i, c)) == false)
			{
				rep = RepInRows(matrix, i, c);
				//cout << "c = " << c << " col = " << i << " empty = " << empty << " rep = " << rep << endl;
				if ((empty - rep) == 1)
					SetInCol(matrix, i, c);
			}
			empty = 0;
			rep = 0;
		}
}

void Run() {
	int** matrix = Fill();
	int count = 0;
	bool stop = true;
	system("cls");
	cout << "Before:" << endl;
	Print(matrix);
	while (stop) {
		for (int c = 1; c <= SIZE; c++)
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++) {
					count++;
					if ((EmptyPlaces(matrix, i, j) - NotGoodPlaces(matrix, i, j, c)) == 1)
					{
						SetNumber(matrix, i, j, c);
						//Print(matrix);
						stop = ZerosCalc(matrix);
						count = 0;
					}
					if (count >= 729) {
						FillLikePro(matrix);
						//Print(matrix);
						stop = ZerosCalc(matrix);
						count = 0;
					}
				}

	}
	cout << "After:" << endl;
	Print(matrix);
	
}