// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	pMem = new TELEM[len];
	BitLen = len - 1;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	pMem = new TELEM[BitLen + 1];
	for (int i = 0; i < BitLen + 1; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	if (pMem != NULL) {
		delete[] pMem;
		pMem = NULL;
		BitLen = 0;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (BitLen - n);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return pMem[BitLen - n];
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen + 1;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[BitLen - n] = 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[BitLen - n] = 0;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[BitLen - n];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen) {
		delete[] pMem;
		BitLen = bf.BitLen;
		pMem = new TELEM[BitLen + 1];
	}
	for (int i = 0; i < BitLen + 1; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return 0;
	}
	else {
		for (int i = 0; i < BitLen + 1; i++) {
			if (pMem[i] != bf.pMem[i]) {
				return 0;
			}
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return 1;
	}
	else {
		for (int i = 0; i < BitLen + 1; i++) {
			if (pMem[i] != bf.pMem[i]) {
				return 1;
			}
		}
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmp;
	if (BitLen > bf.BitLen) {
		tmp = BitLen;
		TBitField c(tmp + 1);
		for (int i = tmp; i >= 0; i--) {
			if (i - bf.BitLen >= 0 && (pMem[i] == 1 || bf.pMem[i - bf.BitLen] == 1)) {
				c.pMem[i] = 1;
			}
			else if (pMem[i] == 1){
				c.pMem[i] = 1;
			}
			else {
				c.pMem[i] = 0;
			}
		}
		return c;
	}
	else {
		tmp = bf.BitLen;
		TBitField c(tmp + 1);
		for (int i = tmp; i >= 0; i--) {
			if (i - BitLen >= 0 && (bf.pMem[i] == 1 || pMem[i - BitLen] == 1)) {
				c.pMem[i] = 1;
			}
			else if (bf.pMem[i] == 1) {
				c.pMem[i] = 1;
			}
			else {
				c.pMem[i] = 0;
			}
		}
		return c;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmp;
	if (BitLen > bf.BitLen) {
		tmp = bf.BitLen;
		TBitField c(tmp + 1);
		for (int i = tmp; i >= 0; i--) {
			if (pMem[i + tmp] == 1 && bf.pMem[i] == 1) {
				c.pMem[i] = 1;
			}
			else {
				c.pMem[i] = 0;
			}
		}
		return c;
	}
	else {
		tmp = BitLen;
		TBitField c(tmp + 1);
		for (int i = tmp; i >= 0; i--) {
			if (bf.pMem[i + tmp] == 1 && pMem[i] == 1) {
				c.pMem[i] = 1;
			}
			else {
				c.pMem[i] = 0;
			}
		}
		return c;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen + 1);
	for (int i = 0; i < BitLen + 1; i++) {
		if (pMem[i]) {
			res.pMem[i] = 0;
		}
		else {
			res.pMem[i] = 1;
		}
	}
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int StrCount;
	istr >> StrCount;
	if (bf.BitLen + 1 != StrCount) {
		if (bf.pMem != NULL) {
			delete[] bf.pMem;
		}
		bf.BitLen = StrCount - 1;
		bf.pMem = new TELEM[StrCount];
	}
	for (int i = 0; i < bf.BitLen + 1; i++) {
		istr >> bf.pMem[i];
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen + 1; i++) {
		ostr << bf.pMem[i];
	}
	ostr << endl;
	return ostr;
}
