#include "the4.h"

// DO NOT CHANGE ABOVE THIS LINE!
// You may implement helper functions below

unsigned int alice_cutting_cake(const unsigned short cake_width,
                                const unsigned short cake_height,
                                bool **perfect_cuts){
                                    
    std::vector<std::vector<unsigned int>> table(cake_width + 1, std::vector<unsigned int>(cake_height + 1, 0));
    
    unsigned int result = 0;
    unsigned int waste = 0;
    unsigned int i,j,k = 0;
    
    for (i=1; i <= cake_width; i++) {
        for (k = 1; k <= cake_height; k++) {
            if (perfect_cuts[i][k]) {
                table[i][k] = 0; 
            } else {
                table[i][k] = i*k; 
            }
        }
    }

    for (i = 1; i <= cake_width; i++) {
        for (k=1; k <= cake_height; k++) {
            if (!perfect_cuts[i][k]) {
                for (j = 1; j < i; j++) {
                    waste = table[j][k] + table[i-j][k];
                    if (waste < table[i][k]) {
                        table[i][k] = waste;
                    }
                }
                for (j=1; j < k; j++) {
                    waste = table[i][j] + table[i][k-j];
                    if (waste < table[i][k]) {
                        table[i][k] = waste;
                    }
                }
            }
        }
    }

    result = table[cake_width][cake_height];

    return result;
}
