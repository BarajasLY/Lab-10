#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

// Linear search function for finding an integer element in the given vector
int iterativeSearch(const vector<int>& v, int elem) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == elem) {
            return i; // Element found, return index
        }
    }
    return -1; // Element not found
}

// Binary search function that takes a reference to the vector, a start and end index, and the element to find
int binarySearch(const vector<int>& v, int start, int end, int elem) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (v[mid] == elem) {
            return mid; // Element found, return index
        } else if (v[mid] < elem) {
            start = mid + 1; // Move to the right half
        } else {
            end = mid - 1; // Move to the left half
        }
    }
    return -1; // Element not found
}

// Function to read integers from a file and store them into a vector
void vecGen(const string& filename, vector<int>& v) {
    ifstream file(filename);
    int num;
    v.clear(); // Clear any existing data before reading new data
    while (file.is_open() && file >> num) {
        v.push_back(num);
    }
    file.close();
}

int main() {
    // Vector containing the main data to search within
    vector<int> v;
    vecGen("10000_numbers.csv", v);

    // Vector containing the elements to be searched for
    vector<int> elem_to_find;
    vecGen("test_elem.csv", elem_to_find);

    // Timing and searching with iterative search
    cout << "Iterative Search Results:\n";
    for (int elem : elem_to_find) {
        clock_t start = clock();
        int index_if_found = iterativeSearch(v, elem);
        clock_t end = clock();

        double elapsed_time_in_sec = double(end - start) / CLOCKS_PER_SEC;
        cout << index_if_found << ":" << elapsed_time_in_sec << " sec\n";
    }

    // Timing and searching with binary search
    cout << "\nBinary Search Results:\n";
    for (int elem : elem_to_find) {
        clock_t start = clock();
        int index_if_found2 = binarySearch(v, 0, v.size() - 1, elem);
        clock_t end = clock();

        double elapsed_time_in_sec = double(end - start) / CLOCKS_PER_SEC;
        cout << index_if_found2 << ":" << elapsed_time_in_sec << " sec (binary)\n";
    }

    return 0;
}
