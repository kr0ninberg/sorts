#include <iostream>

// Global parameteres

int comp = 0;
int chan = 0;

// Addition functions

void swap(int* a , int* b){
    /* Function that exchanges values of two parameteres */
    int t;
    t = *a;
    *a = *b;
    *b = t;
    return;
}

void print_a(int* a , int size){
    /* Function that prints array */
    std::cout << *a;
    for (int q = 1 ; q < size ; q++){
        std::cout << " " << *(a + q);
    }
    std::cout << "\n";
    return;
}

int bin_f(int* a , int size , int num){
    /* Binary search for first parameter in array that more than num (right-sided)*/
    int l , r , mid;
    l = -1;
    r = size;
    while(l < r - 1){
        mid = l + (r - l) / 2;
        if (*(a + mid) > num) r = mid;
        else l = mid;
        comp++;
    }
    return r;
}

void shift_a(int* a , int size){
    /* Makes shift on one position in array */
    for (int q = size - 1 ; q > 0 ; q--){
        swap(a + q , a + q - 1);
        chan++;
    }
    return;
}

int rand_n(){
    static int seed = 4541;
    seed = 8253729 * seed + 2396403;
    return seed % 1000000;
}

void copy_a(int* a , int* b , int size){
    for (int q = 0 ; q < size ; q++){
        *(b + q) = *(a + q);
    }
    return;
}

void merge_m(int *a , int s1 , int s2){
    int b[s2];
    copy_a(a , b , s2);
    int i = 0;
    int j = s1;
    while(i != s1 || j != s2){
        if (i == s1){
            *(a + i + j - s1) = *(b + j);
            j++;
        }
        else if (j == s2){
            *(a + i + j - s1) = *(b + i);
            i++;
        }
        else if (*(b + i) <= *(b + j)){
            *(a + i + j - s1) = *(b + i);
            i++;
        }
        else{
            *(a + i + j - s1) = *(b + j);
            j++;
        }
        comp++;
        chan++;
    }
    return;
}

int get_med(int* a , int size){
    return (*(a + size - 1) + *a) / 2;
}

bool sorted(int* a , int size){
    for (int q = 0 ; q < size - 1 ; q++){
        if (*(a + q) > *(a + q + 1)) return false;
    }
    return true;
}

void test1(int n);

void task();

// Sort functions

void bubble_s(int* a , int size){
    int t = 0;
    if (size == 1) return;
    for (int q = 0 ; q < size - 1 ; q++){
        if (*(a + q) > *(a + q + 1)) {
            swap(a + q , a + q + 1);
            chan++;
            t++;
        }
        comp++;
    }
    if (t == 0) return;
    bubble_s(a , --size);
}

void insert_s(int* a , int size){
    for (int t = 1 ; t < size ; t++){
        int r = bin_f(a , t , *(a + t));
        shift_a(a + r , t - r + 1);            // insert elem in its position
    }
    return;
}

void merge_s(int* a , int size){
    if (size == 1) return;
    else {
        merge_s(a , size / 2);
        merge_s(a + size / 2 , size - size / 2);
    }
    merge_m(a , size / 2 , size);
    return;
}

void hoar_s(int* a , int size){
    if (size == 1) return;
    if (sorted(a , size)) return;
    int med = get_med(a , size);
    chan++;
    int i = 0;
    int j = size - 1;
    while(i < j){
        if (*(a + i) <= med) {
            i++;
        }
        else if (*(a + j) > med) {
            j--;
        }
        else if (*(a + i) > med && *(a + j) <= med){
            swap(a + i , a + j);
            chan++;
        }
        comp++;
    }
    hoar_s(a , j);
    hoar_s(a + j , size - j);
    return;
}

// Action functions

int main()
{
    test1(100);
    return 0;
}

void test1(int n){
    int a[n];
    for (int q = 0 ; q < n ; q++){
        *(a + q) = rand_n();
    }
    print_a(a , n);
    std::cout << "---" << "\n";
    merge_s(a , n);
    print_a(a , n);
    return;
}

void task(){
    int sizes[16] = {23 , 35 , 300 , 1400 , 4000 , 8243 , 11000 , 13294 , 20000 , 36132 , 45000 , 50000 , 65000 , 79000 , 105000 , 150000};
    for (int q = 0 ; q < 13 ; q++){
        for (int w = 0 ; w < 7 ; w++){
            comp = chan = 0;
            int a[*(sizes + q)];
            for (int e = 0 ; e < *(sizes + q) ; e++){
                *(a + e) = rand_n();
            }
            bubble_s(a , *(sizes + q));
            std::cout << comp << " " << chan << "\n";
        }
        std::cout << "-----\n";
        for (int w = 0 ; w < 7 ; w++){
            comp = chan = 0;
            int a[*(sizes + q)];
            for (int e = 0 ; e < *(sizes + q) ; e++){
                *(a + e) = rand_n();
            }
            insert_s(a , *(sizes + q));
            std::cout << comp << " " << chan << "\n";
        }
        std::cout << "-----\n";
        for (int w = 0 ; w < 7 ; w++){
            comp = chan = 0;
            int a[*(sizes + q)];
            for (int e = 0 ; e < *(sizes + q) ; e++){
                *(a + e) = rand_n();
            }
            merge_s(a , *(sizes + q));
            std::cout << comp << " " << chan << "\n";
        }
        std::cout << "-----\n";
        for (int w = 0 ; w < 7 ; w++){
            comp = chan = 0;
            int a[*(sizes + q)];
            for (int e = 0 ; e < *(sizes + q) ; e++){
                *(a + e) = rand_n();
            }
            hoar_s(a , *(sizes + q));
            std::cout << comp << " " << chan << "\n";
        }
        std::cout << "**********\n";
    }
    return;
}
