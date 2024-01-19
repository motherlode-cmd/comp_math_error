#include <iostream>
#include "math.h"
#include <cmath>

double two_sum(double * delta, double a, double b) {//сумма двух чисел
    /*                /           |           \
                для остатка     слагаемое 1     слагаемое 2     */

    //std::cout<<d_a<<" "<<d_b<<std::endl;
    double s = a + b;
    double bs = s - b;
    double as = s - a;
    *delta = (b - bs) + (a - as); //Xвост, остаток
    return s;
}

double sum_n(const double * arr, int size) {//сумма н чисел
    double sum = 0.0, c = 0.0, e = 0.0;/*
 *             /            \       \
 *         сумма    СУММА ОСТАТКОВ  ОСТАТОК*/
    for(int i = 0; i < size; i++) {
        e = 0.0;
        double d_a = arr[i] - floor(arr[i]);
        sum = two_sum(&e, sum, arr[i]);
        if(e == 0 && d_a != 0 && sum - floor(sum) == 0.0)e += d_a;
        c += e;//добавили остаток
    }
    std::cout<<sum<<" "<<c<<std::endl;
    //return sum + c;
    double tmp = 0.0;
    sum = two_sum(&tmp, sum, c);
    return sum + tmp;
}

double two_mult(double * delta, double a, double b) {//умножение двух чисел
    /*                /           |           \
                для остатка   множитель 1  множитель 2     */
    double p = a * b;
    *delta = fma(a, b, -p);//отбошенный хвост
    return p;
}


double f(double * vec1, double * vec2, int size) {
    double * prod = new double [size];
    double * delta = new double [size];
    for(int i = 0; i < size; i++) {
        prod[i] = two_mult(&delta[i], vec1[i], vec2[i]);
    }//умножаем соответствующие коодинаты
    double sum_delt = sum_n(delta, size);
    double sum_prod = sum_n(prod, size);
    double d = 0.0;
    double sum = two_sum(&d,sum_delt, sum_prod);
    //складываем учитывая остатки от умножения
    delete [] prod;
    delete [] delta;
    return sum + d;
}

//Для тестиования
void swap(double * a, double * b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}
//меняем местами, должен быть тот же ответ
void swap(double * vec1, double * vec2, int size){
    for(int i = 0; i < size; i++) {
        int index = (rand() % size + size) % size;
        swap(&vec1[i], &vec1[index]);
        swap(&vec2[i], &vec2[index]);
    }
}
//тестиуем
void print_vec(double * vec1, double * vec2, int size) {
    for(int i = 0; i < size; i++) {
        printf(" [%.15lf] ", vec1[i]);
    }
    printf(" \n");
    for(int i = 0; i < size; i++) {
        printf(" [%.15lf] ", vec2[i]);
    }
}
void test(double * vec1, double * vec2, int size) {
    //print_vec(vec1, vec2, size);
    printf(" \nresult \n %.15lf\n", f(vec1,vec2,size));
    swap(vec1, vec2, size);
    //print_vec(vec1, vec2, size);
    printf(" \nresult after swap \n %.15lf\n", f(vec2,vec1,size));
}
//для ввода
void test_console(int size) {
    double * vec1 = new double [size];
    double * vec2 = new double [size];
    printf(" input %d double vec1:\n", size);
    for(int i = 0; i < size; i++) {
        std::cin>>vec1[i];
    }
    printf(" input %d double vec2:\n", size);
    for(int i = 0; i < size; i++) {
        std::cin>>vec2[i];
    }
    test(vec1, vec2, size);
    delete [] vec1;
    delete [] vec2;
}

//для случайных чисел

void test_random(int size) {
    double * vec1 = new double [size];
    double * vec2 = new double [size];
    for(int i = 0; i < size; i++) {
        vec1[i] =  10.0 / (rand() % 100);
        vec2[i] =  10.0 / (rand() % 100);
    }
    test(vec1, vec2, size);
    delete [] vec1;
    delete [] vec2;
}

int main() {
    //test_random(10);
    test_console(3);
    return 0;
}
