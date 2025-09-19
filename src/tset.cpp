// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of range");
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of range");
    }
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of range");
    }
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower) {
        if (BitField == s.BitField) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower) {
        if (BitField == s.BitField) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return 1;
    }
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TELEM NMaxP = max(MaxPower, s.MaxPower);
    TSet Res(NMaxP);
    Res.BitField = BitField | s.BitField;
    return Res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0) {
        throw std::out_of_range("Element should be positive");
    }
    TELEM NMaxP = max(MaxPower, Elem);
    TSet Res(NMaxP);
    Res.BitField = BitField;
    Res.InsElem(Elem);
    return Res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet Res(*this);
    Res.DelElem(Elem);
    return Res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TELEM NMaxP = max(MaxPower, s.MaxPower);
    TSet Res(NMaxP);
    Res.BitField = BitField & s.BitField;
    return Res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet Res(MaxPower);
    Res.BitField = ~BitField;
    return Res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int El;
    char c;
    for (int i = 0; i < s.MaxPower; i++)
        s.DelElem(i);
    while (istr >> El)
    {
        if (El >= 0 && El < s.MaxPower)
            s.InsElem(El);

        c = istr.peek();
        if (c == '\n' || c == EOF)
            break;
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << "{";
    bool flag = true;
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            if (!flag) {
                ostr << ", ";
                flag = false;
            }
            ostr << i;
        }
    }
    ostr << "}";
    return ostr;
}
