#include <iostream>
#include <vector>

using namespace std;

vector<double> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

/*
 * Ich verstehe den Pseudo-Code nicht ganz. Scheinbar ist s0 vom Typ T und soll verändert werden, das ginge aber nur mit
 * Referenzen und scheint mir sehr kompliziert. Zudem hätte man das Problem, dass s0 = s1 + s2 nicht mehr die gleiche
 * Referenz ist. Ich habe stattdess einfach mal eine rekursive Summation in meinem Sinne implementiert. Darunter ist noch eine
 * Funktion mit dem Iterator.
 * 
 * P.S.: Der Pseude Code verlangt auch eine globale Variable, was das ganze sehr unpraktisch macht...
 */
template <typename T>
T sum1(int start, int end, vector<T> v) {
    if (start >= end) return v[start];
    int mid = (start + end) / 2;
    return sum1(start, mid, v) + sum1(mid + 1, end, v);
}

template <typename T>
T sum2(vector<T> v) {
    T sum = 0;
    for (auto val : v) sum += val;
    return sum;
};

int main() {
    cout << "Sum1: " << sum1(0, v.size() - 1, v) << endl;
    cout << "Sum2: " << sum2(v) << endl;
}
