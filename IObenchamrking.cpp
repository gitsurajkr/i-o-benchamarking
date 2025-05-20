#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdio>
#include <algorithm>
using namespace std;
// function to benchmark writing data to file
void benchmark_write(const string& filename,size_t file_size_mb, size_t block_size, bool use_random) {
    const size_t total_blocks = (file_size_mb * 1024 * 1024)/block_size;

    vector<char> buffer(block_size);

    if(use_random){
        generate(buffer.begin(), buffer.end(), [](){return rand()%256;});
        cout << "\n--- Benchmarking with Random Data ---\n";
    } else {
        fill(buffer.begin(), buffer.end(), 'A');
        cout<< "\n--- Benchmarking with 'A' Data ---\n";
    }

    ofstream outfile(filename, ios::binary | ios::trunc);
    auto start = chrono::high_resolution_clock::now();

    for(size_t i = 0; i < total_blocks; ++i) outfile.write(buffer.data(), block_size);
    outfile.close();

    auto end = chrono::high_resolution_clock::now();
    double elapsed_sec = chrono::duration<double>(end-start).count();
    double speed_mb_per_sec = file_size_mb / elapsed_sec;

    cout<< "File Size    : " << file_size_mb << " MB\n";
    cout << "Block Size     : " << block_size / 1024 << " KB\n";
    cout << "Time Taken     : " << elapsed_sec << " seconds\n";
    cout << "Write Speed    : " << speed_mb_per_sec << " MB/s\n";

}
// need to control 
// File Name, File Size, Block size(in bytes)

int main() {
    srand(static_cast<unsigned int>(time(0)));

    const string filename = "testfile.bin";
    const size_t file_size_mb = 100;
    const size_t block_size = 64 * 1024;
    
    // Run benchmark with 'A'

    benchmark_write(filename, file_size_mb, block_size, false);
    
    // Run benchmark with 'B'
    benchmark_write(filename, file_size_mb, block_size, true);
    return 0;
}