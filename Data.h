#ifndef DATA_H
#define DATA_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"

class Data {
public:
    Data();
    Data(Type);
    Type getType();
    void setVal(Address);
    Size getSize();
    Address getAddress();
    void setAddress(Address);
    void setSize(Size);

    void operator = (Data &data2);
    void operator += (Data &data2);
    void operator -= (Data &data2);
    void operator *= (Data &data2);
    void operator /= (Data &data2);
    void operator %= (Data &data2);
    void operator += (Size data2);
    void operator -= (Size data2);
    void operator *= (Size data2);
    void operator /= (Size data2);
    void operator %= (Size data2);

    bool operator == (Data &data2)
    {
        Address address2 = data2.address;

        switch (type)
        {
        case BOX_CHAR:
            return *address == *address2;
        case BOX_INT:
            return *(int *)address == *(int *)address2;
        case BOX_FLOAT:
            return *(float *)address == *(float *)address2;
        case BOX_LONG:
            return *(long *)address == *(long *)address2;
        case BOX_DOUBLE:
            return *(double *)address == *(double *)address2;
        case BOX_STRING:
            return (strcmp(address, address2) == 0);
        }

        return false;
    }

    bool operator != (Data &data2)
    {
        Address address2 = data2.address;
        switch (type)
        {
        case BOX_CHAR:
            return *address != *address2;
        case BOX_INT:
            return *(int *)address != *(int *)address2;
        case BOX_FLOAT:
            return *(float *)address != *(float *)address2;
        case BOX_LONG:
            return *(long *)address != *(long *)address2;
        case BOX_DOUBLE:
            return *(double *)address != *(double *)address2;
        case BOX_STRING:
            return (strcmp(address, address2) != 0);
        }

        return false;
    }

    bool operator >= (Data &data2)
    {
        Address address2 = data2.address;

        switch (type)
        {
        case BOX_CHAR:
            return *address >= *address2;
        case BOX_INT:
            return *(int *)address >= *(int *)address2;
        case BOX_FLOAT:
            return *(float *)address >= *(float *)address2;
        case BOX_LONG:
            return *(long *)address >= *(long *)address2;
        case BOX_DOUBLE:
            return *(double *)address >= *(double *)address2;
        case BOX_STRING:
            return (strcmp(address, address2) >= 0);
        }

        return false;
    }

    bool operator <= (Data &data2)
    {
        Address address2 = data2.address;

        switch (type)
        {
        case BOX_CHAR:
            return *address <= *address2;
        case BOX_INT:
            return *(int *)address <= *(int *)address2;
        case BOX_FLOAT:
            return *(float *)address <= *(float *)address2;
        case BOX_LONG:
            return *(long *)address <= *(long *)address2;
        case BOX_DOUBLE:
            return *(double *)address <= *(double *)address2;
        case BOX_STRING:
            return (strcmp(address, address2) <= 0);
        }

        return false;
    }

    bool operator > (Data &data2)
    {
        Address address2 = data2.address;

        switch (type)
        {
        case BOX_CHAR:
            return *address > *address2;
        case BOX_INT:
            return *(int *)address > *(int *)address2;
        case BOX_FLOAT:
            return *(float *)address > *(float *)address2;
        case BOX_LONG:
            return *(long *)address > *(long *)address2;
        case BOX_DOUBLE:
            return *(double *)address > *(double *)address2;
        case BOX_STRING:
            return (strcmp(address, address2) > 0);
        }

        return false;
    }

    bool operator < (Data &data2)
    {
        Address address2 = data2.address;

        switch (type)
        {
        case BOX_CHAR:
            return *address < *address2;
        case BOX_INT:
            return *(int *)address < *(int *)address2;
        case BOX_FLOAT:
            return *(float *)address < *(float *)address2;
        case BOX_LONG:
            return *(long *)address < *(long *)address2;
        case BOX_DOUBLE:
            return *(double *)address < *(double *)address2;
        case BOX_STRING:
            return (strcmp(address, address2) < 0);
        }

        return false;
    }

    void print();
    void println();
    void scan();
    void random();
protected:

    template <typename T>
    void addOp(T *, T *);
    template <typename T>
    void addOp(T *, Size);
    template <typename T>
    void subOp(T *, T *);
    template <typename T>
    void subOp(T *, Size);
    template <typename T>
    void mulOp(T *, T *);
    template <typename T>
    void mulOp(T *, Size);
    template <typename T>
    void divOp(T *, T *);
    template <typename T>
    void divOp(T *, Size);
    template <typename T>
    void modOp(T *, T *);
    template <typename T>
    void modOp(T *, Size);
    template <typename T>
    void movOp(T *, T *);

    Address address;
    Type type;
    Size size;
};

void Data::operator = (Data &data2)
{
    Address addr2 = data2.address;

    switch (type)
    {
    case BOX_CHAR:
        movOp(address, addr2);
        break;
    case BOX_INT:
        movOp((int *)address, (int *)addr2);
        break;
    case BOX_LONG:
        movOp((long *)address, (long *)addr2);
        break;
    case BOX_FLOAT:
        movOp((float *)address, (float *)addr2);
        break;
    case BOX_DOUBLE:
        movOp((double *)address, (double *)addr2);
        break;
    case BOX_STRING:
        strcpy(address, addr2);
        break;
    }
}

void Data::operator += (Data &data2)
{
    Address addr2 = data2.address;

    switch (type)
    {
    case BOX_CHAR:
        addOp(address, addr2);
        break;
    case BOX_INT:
        addOp((int *)address, (int *)addr2);
        break;
    case BOX_LONG:
        addOp((long *)address, (long *)addr2);
        break;
    case BOX_FLOAT:
        addOp((float *)address, (float *)addr2);
        break;
    case BOX_DOUBLE:
        addOp((double *)address, (double *)addr2);
        break;
    case BOX_STRING:
        strcat(address, addr2);
        break;
    }
}

void Data::operator -= (Data &data2)
{
    Address addr2 = data2.address;

    switch (type)
    {
    case BOX_CHAR:
        subOp(address, addr2);
        break;
    case BOX_INT:
        subOp((int *)address, (int *)addr2);
        break;
    case BOX_LONG:
        subOp((long *)address, (long *)addr2);
        break;
    case BOX_FLOAT:
        subOp((float *)address, (float *)addr2);
        break;
    case BOX_DOUBLE:
        subOp((double *)address, (double *)addr2);
        break;
    }
}

void Data::operator *= (Data &data2)
{
    Address addr2 = data2.address;

    switch (type)
    {
    case BOX_CHAR:
        mulOp(address, addr2);
        break;
    case BOX_INT:
        mulOp((int *)address, (int *)addr2);
        break;
    case BOX_LONG:
        mulOp((long *)address, (long *)addr2);
        break;
    case BOX_FLOAT:
        mulOp((float *)address, (float *)addr2);
        break;
    case BOX_DOUBLE:
        mulOp((double *)address, (double *)addr2);
        break;
    }
}

void Data::operator /= (Data &data2)
{
    Address addr2 = data2.address;

    switch (type)
    {
    case BOX_CHAR:
        divOp(address, addr2);
        break;
    case BOX_INT:
        divOp((int *)address, (int *)addr2);
        break;
    case BOX_LONG:
        divOp((long *)address, (long *)addr2);
        break;
    case BOX_FLOAT:
        divOp((float *)address, (float *)addr2);
        break;
    case BOX_DOUBLE:
        divOp((double *)address, (double *)addr2);
        break;
    }
}

void Data::operator %= (Data &data2)
{
    Address addr2 = data2.address;

    switch (type)
    {
    case BOX_CHAR:
        modOp(address, addr2);
        break;
    case BOX_INT:
        modOp((int *)address, (int *)addr2);
        break;
    case BOX_LONG:
        modOp((long *)address, (long *)addr2);
        break;
    }
}

void Data::operator += (Size data2)
{
    switch (type)
    {
    case BOX_CHAR:
        addOp(address, data2);
        break;
    case BOX_INT:
        addOp((int *)address, data2);
        break;
    case BOX_LONG:
        addOp((long *)address, data2);
        break;
    case BOX_FLOAT:
        addOp((float *)address, data2);
        break;
    case BOX_DOUBLE:
        addOp((double *)address, data2);
        break;
    case BOX_STRING:
        sprintf(address, "%s%d", address, data2);
        break;
    }
}

void Data::operator -= (Size data2)
{
    switch (type)
    {
    case BOX_CHAR:
        subOp(address, data2);
        break;
    case BOX_INT:
        subOp((int *)address, data2);
        break;
    case BOX_LONG:
        subOp((long *)address, data2);
        break;
    case BOX_FLOAT:
        subOp((float *)address, data2);
        break;
    case BOX_DOUBLE:
        subOp((double *)address, data2);
        break;
    }
}

void Data::operator *= (Size data2)
{
    switch (type)
    {
    case BOX_CHAR:
        mulOp(address, data2);
        break;
    case BOX_INT:
        mulOp((int *)address, data2);
        break;
    case BOX_LONG:
        mulOp((long *)address, data2);
        break;
    case BOX_FLOAT:
        mulOp((float *)address, data2);
        break;
    case BOX_DOUBLE:
        mulOp((double *)address, data2);
        break;
    }
}

void Data::operator /= (Size data2)
{
    switch (type)
    {
    case BOX_CHAR:
        divOp(address, data2);
        break;
    case BOX_INT:
        divOp((int *)address, data2);
        break;
    case BOX_LONG:
        divOp((long *)address, data2);
        break;
    case BOX_FLOAT:
        divOp((float *)address, data2);
        break;
    case BOX_DOUBLE:
        divOp((double *)address, data2);
        break;
    }
}

void Data::operator %= (Size data2)
{
    switch (type)
    {
    case BOX_CHAR:
        divOp(address, data2);
        break;
    case BOX_INT:
        divOp((int *)address, data2);
        break;
    case BOX_LONG:
        divOp((long *)address, data2);
        break;
    }
}

template <typename T>
void Data::addOp(T *operand1, T *operand2)
{
    *operand1 += *operand2;
}

template <typename T>
void Data::addOp(T *operand1, Size increment)
{
    *operand1 += increment;
}

template <typename T>
void Data::subOp(T *operand1, T *operand2)
{
    *operand1 -= *operand2;
}

template <typename T>
void Data::subOp(T *operand1, Size increment)
{
    *operand1 -= increment;
}

template <typename T>
void Data::mulOp(T *operand1, T *operand2)
{
    *operand1 *= *operand2;
}

template <typename T>
void Data::mulOp(T *operand1, Size increment)
{
    *operand1 *= increment;
}

template <typename T>
void Data::divOp(T *operand1, T *operand2)
{
    if (*operand2)
    {
        *operand1 /= *operand2;
    }
    else
    {
        SETERR(DIV_NULL_ERR);
    }
}

template <typename T>
void Data::divOp(T *operand1, Size operand2)
{
    if (operand2)
    {
        *operand1 /= operand2;
    }
    else
    {
        SETERR(DIV_NULL_ERR);
    }
}

template <typename T>
void Data::modOp(T *operand1, T *operand2)
{
    if (*operand2)
    {
        *operand1 %= *operand2;
    }
    else
    {
        SETERR(DIV_NULL_ERR);
    }
}

template <typename T>
void Data::modOp(T *operand1, Size operand2)
{
    if (operand2)
    {
        *operand1 %= operand2;
    }
    else
    {
        SETERR(DIV_NULL_ERR);
    }
}

template <typename T>
void Data::movOp(T *operand1, T *operand2)
{
    *operand1 = *operand2;
}

void Data::println()
{
    switch (type)
    {
    case BOX_CHAR:
        printf("%c\n", *address);
        break;
    case BOX_STRING:
        printf("%s\n", address);
        break;
    case BOX_INT:
        printf("%d\n", *(int *)address);
        break;
    case BOX_LONG:
        printf("%ld\n", *(long *)address);
        break;
    case BOX_FLOAT:
        printf("%f\n", *(float *)address);
        break;
    case BOX_DOUBLE:
        printf("%lf\n", *(double *)address);
        break;
    }
}

void Data::print()
{
    switch (type)
    {
    case BOX_CHAR:
        printf("%c", *address);
        break;
    case BOX_STRING:
        printf("%s", address);
        break;
    case BOX_INT:
        printf("%d", *(int *)address);
        break;
    case BOX_LONG:
        printf("%ld", *(long *)address);
        break;
    case BOX_FLOAT:
        printf("%f", *(float *)address);
        break;
    case BOX_DOUBLE:
        printf("%lf", *(double *)address);
        break;
    }
}

void Data::scan()
{
    switch (type)
    {
    case BOX_CHAR:
        scanf(" %c", address);
        break;
    case BOX_STRING:
        scanf(" %s", address);
        break;
    case BOX_INT:
        scanf(" %d", (int *)address);
        break;
    case BOX_LONG:
        scanf(" %ld", (long *)address);
        break;
    case BOX_FLOAT:
        scanf(" %f", (float *)address);
        break;
    case BOX_DOUBLE:
        scanf(" %lf", (double *)address);
        break;
    }
}

void Data::random()
{
    int randnum = rand();

    switch (type)
    {
    case BOX_CHAR:
        *address = randnum % 128;
        break;
    case BOX_STRING:
        sprintf(address, "%d", randnum);
        break;
    case BOX_INT:
        *(int *)address = randnum;
        break;
    case BOX_LONG:
        *(long *)address = randnum;
        break;
    case BOX_FLOAT:
        *(float *)address = (float)randnum;
        break;
    case BOX_DOUBLE:
        *(double *)address = (double)randnum;
        break;
    }
}

Data::Data()
{
    address = null;
    size = null;
    type = null;
}

Data::Data(Type type)
{
    address = null;
    this->type = type;
    size = 0;
}

void Data::setVal(Address value)
{
    switch (type)
    {
    case BOX_STRING:
        strcpy(address, value);
        break;
    default:
        memcpy(address, value, size);
        break;
    }
}

Type Data::getType()
{
    return type;
}

Address Data::getAddress()
{
    return address;
}

void Data::setAddress(Address address)
{
    this->address = address;
}

void Data::setSize(Size size)
{
    this->size = size;
}

Size Data::getSize()
{
    return size;
}

typedef Data * Data_p;

#endif // DATA_H
