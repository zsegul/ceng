#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include "the1.h"


void rand_input_generator(unsigned short *&arr,
                            const int size,
                            unsigned int &index,
                            bool &quick_select_mode,
                            const unsigned short minimum_value,
                            const unsigned short interval,
                            const double same_element_ratio = 0.3){
	arr = new unsigned short [size];
    index = rand() % size;
    quick_select_mode = (rand() % 2 == 0);
    arr[0] = minimum_value + (rand() % interval);
	for(int idx=1; idx < size; idx++)
		arr[idx] = (((double)(rand() % 1000) / 1000.0 <= same_element_ratio) ? arr[rand() % idx]
                                                                               : minimum_value + (rand() % interval));
}


void read_from_file(unsigned short *&input_array,
                    int &size,
                    unsigned int &index,
                    bool &quick_select){
	char addr[]= "inp01.txt";  // You can reach different input cases by changing numbers. 01-10 are available.
	std::ifstream infile (addr);
	if (!infile.is_open()){
		std::cout << "File \'"<< addr 
			<< "\' can not be opened. Make sure that this file exists." << std::endl;
		return;
	}
	infile >> quick_select;
    infile >> index;
    infile >> size;
    input_array = new unsigned short[size];
    for(int j=0; j<size; j++){
        infile >> input_array[j];
    }
    infile.close();
}


bool check_sorted(const unsigned short* arr,
                  const int size){
    for(int idx=1; idx < size; idx++)
        if(arr[idx] < arr[idx-1]) return false;
    return true;
}
	

void test(){
	int size = 1 << 10;
	std::pair<unsigned int ,unsigned int> result;
    long swap = 0;
    unsigned int index;
    bool quick_select = false;
    unsigned short *input_array;
	unsigned short minimum_value = 0;
	auto interval = (unsigned short)((1 << 14) - 1);

    // If you want to work with rand input, mark rand_fill=true
    // else input is read from file
    bool rand_fill = false;

    if(rand_fill)
        rand_input_generator(input_array, size, index, quick_select, minimum_value, interval);
	else
	    read_from_file(input_array, size, index, quick_select);
	
	//Calculate duration and print output
	std::cout << "Size: " << size << std::endl <<
                 (quick_select ? "Using: quick_select3" : "Using: select_k_with_quick_sort3") << std::endl <<
                 "Array elements: {";
    for(int idx=0; idx < size; idx++) std::cout << input_array[idx] << (idx != size-1 ? ", " : "}");
    std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    result = quick_select ? quick_select3(input_array, size, index, swap)
                          : select_k_with_quick_sort3(input_array, size, index, swap);
    auto end = std::chrono::high_resolution_clock::now();

    std::sort(input_array, input_array+size, [](int a, int b){return a < b;});

    std::cout << "Claimed Element at index " << index << " when sorted: " << result.first << std::endl <<
                 "True Element at index " << index << " when sorted: " << input_array[index] << std::endl <<
                 "Swap: " << swap << std::endl <<
                 "Number of recursive calls: " << result.second << std::endl <<
                 "Elapsed time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << " ns" << std::endl;

    delete[] input_array;
}

int main(){
	srand(time(nullptr));
	test();
	return 0;
}