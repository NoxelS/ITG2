#include <iostream>
#include <vector>

using namespace std;

template <typename T>
vector<T> merge(vector<T> left, vector<T> right) {
    vector<T> v;
    while (left.size() && right.size()) {
        if (left[0] < right[0]) {
            v.push_back(left[0]);
            left.erase(left.begin());
        } else {
            v.push_back(right[0]);
            right.erase(right.begin());
        }
    }

    while (left.size()) {
        v.push_back(left[0]);
        left.erase(left.begin());
    }

    while (right.size()) {
        v.push_back(right[0]);
        right.erase(right.begin());
    }

    return v;
};


template <typename T>
vector<T> mergesort(vector<T> v) {
    if(v.size() <= 1) return v;

    vector<T> left;
    vector<T> right;

    for(auto it = v.begin(); it != v.end(); it++) {
        if(it < v.begin() + v.size() / 2) left.push_back(*it);
        else right.push_back(*it);
    }
    
    left = mergesort(left);
    right = mergesort(right);

    return merge(left, right);
};

int main() {
    vector<int> v = { 1 , 6 , 3 , 2 , 5 , 4 , 7 , 8 , 9 ,1 , 22, -1, 5, 0};
    v = mergesort(v);

    for(auto val : v) {
        cout << val << " ";
    }

    cout << endl;
}
