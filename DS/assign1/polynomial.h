// CSE221 Assignment 1

#ifndef polynomial_h
#define polynomial_h

#include <typeinfo>
#include <iostream>
#include <math.h>

template <typename T>
class Polynomial
{
public:
    // Default constructor p(x) = 0
    Polynomial();
    
    // Copy constructor
    Polynomial(const Polynomial& source);
    
    // Destructor
    ~Polynomial();
    
    // Assignment operator
    Polynomial& operator = (const Polynomial& source);
    
    // Sum of *this and source polynomials
    Polynomial operator+(const Polynomial& source);
    
    // Subtract of source polynomials from *this
    Polynomial operator-(const Polynomial& source);
    
    // Product of *this and source polynomials
    Polynomial operator*(const Polynomial& source);
    
    // Evaluate polynomial *this at x and return the result
    T Eval(T x);
    
    // Print polynomial
    void Print();
    
    // Create a new term. If the term exists, overwrite its coefficient.
    void CreateTerm(const T coef, const int exp);
    
    T GetCoef(int exp) const;
    
    int GetSize() const;
private:
    T* coef_list;
    int size;
};

//
// Implementation
//

// Default constructor
template <typename T>
Polynomial<T>::Polynomial() {
    size = 0;
    coef_list = new T[1];
    coef_list[0] = 0;
}

// Copy constructor
template <typename T>
Polynomial<T>::Polynomial(const Polynomial& source)
{
    size = source.GetSize();
    coef_list = new T[size];
    for (int i = 0; i < size; i++) {
        coef_list[i] = source.GetCoef(i);
    }
}

// Assignment operator
template <typename T>
Polynomial<T>& Polynomial<T>::operator = (const Polynomial& source)
{
    delete[] coef_list;
    size = source.GetSize();
    coef_list = new T[size];
    for (int i = 0; i < size; i++) {
        coef_list[i] = source.GetCoef(i);
    }
    
    return *this;
}

template <typename T>
Polynomial<T>::~Polynomial()
{
    delete[] coef_list;
}

template <typename T>
void Polynomial<T>::Print()
{
    for (int i = size - 1; i >= 0; i--) {
        // next if coefficient is zero
        if (coef_list[i] == 0)
            continue;
        
        // print sign +
        if (i < size - 1 && coef_list[i] > 0)
            std::cout << "+";
        
        // print coefficient
        std::cout << coef_list[i];
        
        // print term
        if (i > 0)
            std::cout << "x" << "^" << i;
    }
    std::cout << std::endl;
}

// Sum of *this and source polynomials
template <typename T>
Polynomial<T>
Polynomial<T>::operator+(const Polynomial& source)
{
    Polynomial<T> result = *this;
    
    for (int i = 0; i < source.GetSize(); i++) {
        result.CreateTerm(result.GetCoef(i) + source.GetCoef(i), i);
    }
    
    return result;
}

template <typename T>
Polynomial<T>
Polynomial<T>::operator-(const Polynomial& source)
{
    Polynomial<T> result = *this;
    
    for (int i = 0; i < source.GetSize(); i++) {
        result.CreateTerm(result.GetCoef(i) - source.GetCoef(i), i);
    }
    
    return result;
}

template <typename T>
Polynomial<T>
Polynomial<T>::operator*(const Polynomial& source)
{
    Polynomial<T> result;
    
    for (int i = 0; i < this->GetSize(); i++) {
        for (int j = 0; j < source.GetSize(); j++) {
            result.CreateTerm(result.GetCoef(i + j) + (this->GetCoef(i) * source.GetCoef(j)), i + j);
        }
    }
    
    return result;
}

template <typename T>
T Polynomial<T>::Eval(T x)
{
    T result = 0;
    
    for (int i = 0; i < size; i++) {
        result += coef_list[i] * pow(x, i);
    }
    
    return result;
}

template <typename T>
void Polynomial<T>::CreateTerm(const T coef, const int exp)
{
    if (size < exp + 1) {
        T* temp = new T[exp + 1];
        for (int i = 0; i < exp + 1; i++)
            temp[i] = 0;
        
        for (int i = 0; i < size; i++) {
            temp[i] = coef_list[i];
        }
        temp[exp] = coef;
        delete[] coef_list;
        coef_list = temp;
        size = exp + 1;
    } else {
        coef_list[exp] = coef;
    }
}

template <typename T>
T Polynomial<T>::GetCoef(int exp) const {
    return (size < exp + 1) ? 0 : coef_list[exp];
}

template <typename T>
int Polynomial<T>::GetSize() const {
    return size;
}


#endif