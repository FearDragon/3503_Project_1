#include <stdio.h>
// Basic bit operations
unsigned int SetBit ( unsigned int value , int position ) { // Set bit to 1
    if (position < 0 || position >= 32) {
        return value ;
    }
    return (value | (1U << position));
}
unsigned int ClearBit ( unsigned int value , int position ) { // Set bit to 0
    if (position < 0 || position >= 32) {
        return value ;
    }
    return (value & ~(1U << position));
}
unsigned int ToggleBit ( unsigned int value , int position ) { // Flip bit
    if (position < 0 || position > 32) {
        return value ;
    }
    return (value ^ (1U << position));
}
int GetBit ( unsigned int value , int position ) { // Get bit value
    if (position < 0 || position > 32) {
        return 0 ;
    }
    return (value >> position) & 1U;
}

// Counting and finding
int CountBits ( unsigned int value ) { // Count 1s
    int count = 0;
    while ( value ) {
        if ( GetBit ( value , 0 ) == 1) {
            count++;
        }
        value >>= 1;
    }
    return count;
}

// Shift operations
unsigned int ShiftLeft ( unsigned int value , int positions ) {
    if (positions < 0 || positions > 32) {
        return value ;
    }
    return value << positions ;
}
unsigned int ShiftRight ( unsigned int value , int positions ) {
    if (positions < 0 || positions > 32) {
        return value ;
    }
    return value >> positions ;
}

// Display functions
void PrintBinary ( unsigned int value ) { // Show in binary
    for (int position = 31; position >= 0; position--) {
        wprintf(L"%d", GetBit ( value , position ));
    }
}
void PrintHex ( unsigned int value ) { // Show in hex
    printf("%016llX\n", value );
}