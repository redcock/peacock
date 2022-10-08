#include <iostream>
#include <fstream>
#include <string.h>
#include <stdint.h>     // for uint64 definition
#include <stdlib.h>     // for exit() definition
#include <time.h>       // for clock_gettime

using namespace std;
#define MAXLEN 50000
#define BILLION 1000000000L // for time
char line[MAXLEN];

int main() {

    // for time
    uint64_t diff;
    struct timespec start, end;
    // measure monotonic time
    clock_gettime(CLOCK_MONOTONIC, &start); // mark start time

    
    int count = 0;
    string filename;
    ifstream infile;
    cout << "Enter file name:";
    getline(cin, filename);
    infile.open(filename.c_str());
    
    if (infile.is_open()) {
        infile.getline(line, MAXLEN);
        int mylen = strlen(line);
    
        for (int i = 0; i < mylen; i++) {
            if (line[i] == '(' && line[i+1] == '(') {
                for (int j = 0; i < mylen; j++) {
                    if (line[i] == ')' && line[i+1] == ')') {
                        if (i < j) {
                            count++;
                        }
                     }
                }
            }
        }
        
        cout << count << endl;
        infile.close();
        clock_gettime(CLOCK_MONOTONIC, &end);   // mark the end time 

        diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

        return 0;
    }
    else {
        cout << "Failed to open filename " << filename << endl;
        exit(1);
    }
    
}
