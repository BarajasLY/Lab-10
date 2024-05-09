#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

// Linear search function for finding an element in the given vector
template <typename T>
int iterativeSearch(const vector<T>& v, T elem) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == elem) {
            return i; // Element found, return index
        }
    }
    return -1; // Element not found
}

// Function to compare two strings and determine their ordering
int compareStrings(const string &s1, const string &s2) {
    size_t length = min(s1.length(), s2.length());
    for (size_t i = 0; i < length; ++i) {
        if (s1[i] < s2[i]) {
            return -1; // s1 comes before s2
        } else if (s1[i] > s2[i]) {
            return 1; // s1 comes after s2
        }
    }
    // If all compared characters are the same, the shorter string comes first
    if (s1.length() < s2.length()) return -1;
    if (s1.length() > s2.length()) return 1;
    return 0; // The strings are equivalent
}

// Binary search function for different data types
template <typename T>
int binarySearch(const vector<T>& v, int start, int end, T elem) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (v[mid] == elem) {
            return mid; // Found the element
        } else if (v[mid] < elem) {
            start = mid + 1; // Move to the right half
        } else {
            end = mid - 1; // Move to the left half
        }
    }
    return -1; // Element not found
}

// Overloaded binary search function for strings, using custom comparison
int binarySearch(const vector<string>& v, int start, int end, const string &elem) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        int comparisonResult = compareStrings(v[mid], elem);
        if (comparisonResult == 0) {
            return mid; // Found the element
        } else if (comparisonResult < 0) {
            start = mid + 1; // Move to the right half
        } else {
            end = mid - 1; // Move to the left half
        }
    }
    return -1; // Element not found
}

// Function to read integers from a file and store them into a vector
void vecGen(const string &filename, vector<int> &v) {
    ifstream file(filename);
    int num;
    v.clear(); // Clear any existing data before reading new data
    while (file.is_open() && file >> num) {
        v.push_back(num);
    }
    file.close();
}

// Function to generate a vector of strings
void stringVecGen(vector<string> &v) {
    v = {"Al", "Be", "Bea", "Bob", "Cat", "Ci"};
}

int main() {
    // Integer test
    vector<int> v;
    vecGen("10000_numbers.csv", v);

    vector<int> elem_to_find;
    vecGen("test_elem.csv", elem_to_find);

    cout << "Binary Search for Integers:\n";
    for (int elem : elem_to_find) {
        clock_t startInt = clock();
        int index_if_found = binarySearch(v, 0, v.size() - 1, elem);
        clock_t endInt = clock();

        double elapsed_time_in_sec = double(endInt - startInt) / CLOCKS_PER_SEC;
        cout << index_if_found << ":" << elapsed_time_in_sec << " sec\n";
    }

    // String test
    vector<string> string_data;
    stringVecGen(string_data);

    string target = "Bea"; // String to search for

    clock_t startStr = clock();
    int index_if_found = binarySearch(string_data, 0, string_data.size() - 1, target);
    clock_t endStr = clock();

    double elapsed_time_in_sec = double(endStr - startStr) / CLOCKS_PER_SEC;

    cout << "\nBinary Search for Strings:\n";
    cout << index_if_found << ":" << elapsed_time_in_sec << " sec (string)\n";

    return 0;
}
