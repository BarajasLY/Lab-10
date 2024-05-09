#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <functional>
using namespace std;

void writeTimes(string filename, const vector<double> &times, const vector<int> &n){
    ofstream myFile(filename);

    myFile << "Number of Element (n)\t Time (sec) " << endl;
    for (size_t i = 0; i < times.size(); i++){
        myFile << n[i] << "\t" << times[i] << "\n";
    }

    myFile.close();
    cout << "Wrote to " << filename << endl;
}

int iterativeSearch(vector<int> &v, int elem){
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == elem) {
            return i;
        }
    }
    return -1;
}

int binarySearch(vector<int> &v, int start, int end, int elem) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (v[mid] == elem) {
            return mid;
        } else if (v[mid] < elem) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}

void vecGen(const string &filename, vector<int> &v){
    ifstream file(filename);
    int num;
    v.clear();
    while (file.is_open() && file >> num){
        v.push_back(num);
    }
    file.close();
}

double measureSearchTime(const function<int(vector<int> &, int)> &searchFunc, vector<int> &v, int elem){
    clock_t start = clock();
    searchFunc(v, elem);
    clock_t end = clock();
    return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

int main() {
    vector<int> file_sizes;
    vecGen("sizes.csv", file_sizes);

    vector<int> elem_to_find;
    vecGen("test_elem.csv", elem_to_find);

    vector<int> v;
    vector<double> times, avg;

    // Iterative Search Measurements
    for (size_t i = 0; i < file_sizes.size(); ++i) {
        string filename = to_string(file_sizes[i]) + "_numbers.csv";
        vecGen(filename, v);

        cout << "Testing with file: " << filename << endl;

        // Clear timing results for this file size
        times.clear();

        // Measure time for each element in elem_to_find
        for (int elem : elem_to_find) {
            double elapsed_time = measureSearchTime(iterativeSearch, v, elem);
            times.push_back(elapsed_time);
        }

        // Calculate average search time
        avg.push_back(accumulate(times.begin(), times.end(), 0.0) / times.size());
    }

    // Write iterative search results to CSV
    writeTimes("iterativeSearch_times.csv", avg, file_sizes);

    // Binary Search Measurements
    avg.clear(); // Reset averages for binary search

    for (size_t i = 0; i < file_sizes.size(); ++i) {
        string filename = to_string(file_sizes[i]) + "_numbers.csv";
        vecGen(filename, v);

        cout << "Testing with file: " << filename << endl;

        // Sort vector for binary search
        sort(v.begin(), v.end());

        // Clear timing results for this file size
        times.clear();

        // Measure time for each element in elem_to_find
        for (int elem : elem_to_find) {
            double elapsed_time = measureSearchTime([&](vector<int> &v, int elem) {
                return binarySearch(v, 0, static_cast<int>(v.size()) - 1, elem);
            }, v, elem);
            times.push_back(elapsed_time);
        }

        // Calculate average search time
        avg.push_back(accumulate(times.begin(), times.end(), 0.0) / times.size());
    }

    // Write binary search results to CSV
    writeTimes("binarySearch_times.csv", avg, file_sizes);

    return 0;
}
