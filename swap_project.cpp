#include <iostream>

void reference_swap(int& a, int& b){
    int c = a;
    a = b;
    b = c;
}

void pointer_swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

int main(){

    int x = 10;
    int y = 20;

    // reference_swap(x, y);
    pointer_swap(&x, &y);

    std::cout << "x was 10 but now is " << x << std::endl;
    std::cout << "y was 20 but now is " << y << std::endl;
    
    return 0;
}