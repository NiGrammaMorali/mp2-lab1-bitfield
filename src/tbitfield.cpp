// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define MEMSIZE (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	if (len <= 0) {
		throw std::out_of_range("Nums should be positive");
	}
	BitLen = len;
	MemLen = (len - 1) / MEMSIZE + 1;
	pMem = new TELEM[MemLen]{0};
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	if (pMem != NULL) {
		delete[] pMem;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / MEMSIZE;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	//cout << (1 << (n % MEMSIZE)) << std::endl;
	return 1 << (n % MEMSIZE);

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Index is out of range");
	}
	int i = GetMemIndex(n);
	TELEM m = GetMemMask(n);
	pMem[i] |= m;
	//cout << this << std::endl;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Index is out of range");
	}
	int i = GetMemIndex(n);
	TELEM m = GetMemMask(n);
	pMem[i] &= ~m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Index is out of range");
	}
	int i = GetMemIndex(n);
	TELEM m = GetMemMask(n);
	return ((pMem[i] & m) != 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) {
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return 0;
	}
	else {
		for (int i = 0; i < MemLen; i++) {
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
		TELEM count = 0;
		for (int i = 0; i < BitLen; i++) {
			if (pMem[i] == bf.pMem[i]) {
				count++;
			}
		}
		if (count == MemLen) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField res(max(BitLen, bf.BitLen));
	int MinMemLen = min(MemLen, bf.MemLen);
	for (int i = 0; i < MinMemLen; i++) {
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}
	if (MemLen > MinMemLen) {
		for (int i = MinMemLen; i < MemLen; i++) {
			res.pMem[i] = pMem[i];
		}
	}
	else if (bf.MemLen > MinMemLen) {
		for (int i = MinMemLen; i < bf.MemLen; i++) {
			res.pMem[i] = bf.pMem[i];
		}
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField res(max(BitLen, bf.BitLen));
	int MinMemLen = min(MemLen, bf.MemLen);
	for (int i = 0; i < MinMemLen; i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}
	TELEM rem = BitLen % MEMSIZE;
	if (rem > 0) {
		TELEM m = (1 << rem) - 1;
		res.pMem[MemLen - 1] &= m;
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c;
	int BitCount = 0;
	for (int i = 0; i < bf.MemLen; i++) {
		bf.pMem[i] = 0;
	}
	while (BitCount < bf.BitLen && istr.get(c)) {
		if (c == '1') {
			bf.SetBit(BitCount);
			BitCount++;
		}
		else if (c == '0') {
			bf.ClrBit(BitCount);
			BitCount++;
		}
		else {
			continue;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = bf.BitLen - 1; i > 0 ; i--) {
		ostr << (bf.GetBit(i) ? '1' : '0');
	}
	return ostr;
}
