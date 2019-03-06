/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}

bool Sudoku::isSafe(int x, int y, int n) {
	if (!block3x3HasNumber[x/3][y/3][n] && !lineHasNumber[x][n] && !columnHasNumber[y][n])
		return true;
	else
		return false;
}

void Sudoku::mark(int x, int y, int n) {
	numbers[x][y] = n;
	block3x3HasNumber[x/3][y/3][n] = true;
	lineHasNumber[x][n] = true;
	columnHasNumber[y][n] = true;
	countFilled++;
}

void Sudoku::unmark(int x, int y, int n) {
	numbers[x][y] = 0;
	block3x3HasNumber[x/3][y/3][n] = false;
	lineHasNumber[x][n] = false;
	columnHasNumber[y][n] = false;
	countFilled--;
}

/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve()
{
	return solve(0, 0);
}

bool Sudoku::solve(int x, int y) {
	if (isComplete())
		return true;

	if (numbers[x][y] != 0) {
		if (x == 8 && y == 8)
			return true;

		if (y == 8) {
			x++;
			y = 0;
		}
		else
			y++;

		return solve(x,y);
	}

	for (int n = 1; n < 10; n++) {
		if (!isSafe(x,y,n))
			continue;

		mark(x,y,n);

		int newX(x);
		int newY(y);

		if (y == 8) {
			newX++;
			newY = 0;
		}
		else
			newY++;

		if (solve(newX,newY)) //try inserting n
			return true;
		else {
			unmark(x,y,n); //inserting n did not work
			continue;
		}
	}
	return false; //could not insert any number
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
