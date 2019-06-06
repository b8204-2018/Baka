#include <iostream>
#include "string.h"

using  namespace std;

class Sort {
public:
    virtual void sortName() = 0;
    virtual void sort(int *arr, int n) = 0;
};

class Cocktail : public Sort {
public:
    void sortName() override {
        cout << "Cocktail Sort : " << endl;
    }
    void sort (int *arr, int n) {
        bool swapped = true;
        int start = 0;
        int end = n - 1;

        while (swapped) {
            swapped = false;
            for (int i = start; i < end; ++i) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
            swapped = false;
            --end;
            for (int i = end - 1; i >= start; --i) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            ++start;
        }
    } ;
};

void printSortedArray(Sort &sort, int *arr, int n){
    int *res = new int[n];
    memcpy(res, arr, n * sizeof(int));
    sort.sortName();
    sort.sort(res, n);
    for (int i = 0; i < n; i++)
        cout << " " << res[i];
    cout << endl;
}

int main() {

    Cocktail cocktail;
    int n;
    cout << "Vvedite razmernost' massiva : " << endl;
    cin >> n;
    cout << "Nachalnii massiv : " << endl;
    int *userArray = new int[n];
    for(size_t i = 0; i < n; i++){
        userArray[i] = rand() % 100;
        cout << userArray[i] << " ";
    }

    cout << endl;
    printSortedArray(cocktail, userArray, n);

    return 0;
}