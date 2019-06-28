#include <iostream>

using namespace std;

class Sort {
public:
    virtual void setArray(int n) = 0;
    virtual string sortName() = 0;
};

class Cocktail : public Sort {
    int n;
    int* arr;
public:
    string sortName() override {
        return "CocktailSort";
    }

    void setArray(int n) override;
    void Sort();
    void PrintArray(class Sort &c1);
};


void Cocktail::setArray(int n) {
    this->n = n;
    arr = new int[n];
    for (int i = 0; i < this->n; i++) {
        cout << "Array[" << i << "] - ";
        cin >> arr[i];
    }
};


void Cocktail::Sort() {

    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;

        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;

        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }

};

void Cocktail::PrintArray(class Sort &c1) {
    cout << c1.sortName()<< endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {

    Cocktail c1;
    int n;
    cout << "Number of array elements - ";
    cin >> n;
    c1.setArray(n);
    c1.PrintArray(c1);
    c1.Sort();
    c1.PrintArray(c1);

}