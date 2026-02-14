#include <iostream>
#include <fstream>
#include <chrono>

int main() 
{
    std::ifstream randomNum("random.txt");
    if (!randomNum) {
        std::cerr << "Unable to open file random.txt";
        return 1;
    }

    const int n = 500000;
    int arr[n];

    int counter = 0;

    for (int i = 0; i < n; i++) {
        randomNum >> arr[i];
    }

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            counter++;
        }
    }

    auto end = std::chrono::steady_clock::now();

    for (int a : arr) {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    std::chrono::duration<double> elapsedSeconds = end - start;
    std::cout << "sort time: " << elapsedSeconds.count() << " seconds\n";
    std::cout << "number of swaps: " << counter << std::endl;

    return 0;

}