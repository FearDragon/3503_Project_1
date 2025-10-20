#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

unsigned int SetBit ( unsigned int value , int position ) ;
unsigned int ClearBit ( unsigned int value , int position ) ;
unsigned int ToggleBit ( unsigned int value , int position ) ;
int GetBit ( unsigned int value , int position ) ;
int CountBits ( unsigned int value ) ;
unsigned int ShiftLeft ( unsigned int value , int positions ) ;
unsigned int ShiftRight ( unsigned int value , int positions ) ;
void PrintBinary ( unsigned int value ) ;
void PrintHex ( unsigned int value ) ;

int main () {
    setlocale ( LC_ALL, "en_US.UTF-8" ) ;
    _setmode(_fileno(stdout), _O_U8TEXT);
    // Graphics
    wchar_t white = L'⛂';
    wchar_t black = L'⛀';
    wchar_t white_king = L'⛃';
    wchar_t black_king = L'⛁';
    wchar_t black_square = L'▭';
    wchar_t white_square = L'▬';

    // Set up the board
    unsigned int black_pieces = 4095;
    unsigned int white_pieces = 4293918720;
    unsigned int black_kings = 0;
    unsigned int white_kings = 0;
    while (true) {
        // Print board
        wprintf(L"   1  2  3  4  5  6  7  8\n");
        for (int row = 0; row < 8; row++) {
            wprintf(L"%c ", 'A' + row);
            for (int col = 0 + row * 4; col < 4 + row * 4; col++) {
                if (row % 2 == 0) {
                    if (GetBit ( black_pieces , col ) == 0 && GetBit ( white_pieces , col ) == 0) {
                        wprintf(L"%lc", black_square);
                    } else if (GetBit ( black_pieces , col ) == 1 && GetBit ( black_kings , col ) == 0) {
                        wprintf (L"%lc", black);
                    } else if (GetBit ( white_pieces , col ) == 1 && GetBit ( white_kings , col ) == 0) {
                        wprintf (L"%lc", white);
                    } else if (GetBit ( white_pieces , col ) == 1 && GetBit ( white_kings , col ) == 1) {
                        wprintf (L"%lc", white_king);
                    } else if (GetBit ( black_pieces , col ) == 1 && GetBit ( black_kings , col ) == 1) {
                        wprintf (L"%lc", black_king);
                    }
                }
                wprintf (L"%lc", white_square);
                if (row % 2 == 1) {
                    if (GetBit ( black_pieces , col ) == 0 && GetBit ( white_pieces , col ) == 0) {
                        wprintf (L"%lc", black_square);
                    } else if (GetBit ( black_pieces , col ) == 1 && GetBit ( black_kings , col ) == 0) {
                        wprintf (L"%lc", black);
                    } else if (GetBit ( white_pieces , col ) == 1 && GetBit ( white_kings , col ) == 0) {
                        wprintf (L"%lc", white);
                    } else if (GetBit ( white_pieces , col ) == 1 && GetBit ( white_kings , col ) == 1) {
                        wprintf (L"%lc", white_king);
                    } else if (GetBit ( black_pieces , col ) == 1 && GetBit ( black_kings , col ) == 1) {
                        wprintf (L"%lc", black_king);
                    }
                }
            }
            wprintf (L"\n") ;
        }
        // Game inputs
        char from[16];
        char to[16];
        wprintf (L"What piece to move ex: A1\n") ;
        scanf ( "%s" , from );
        wprintf (L"Where to move it Right: R, Left: L, Right Back: RB, Left Back: LB\n") ;
        scanf ( "%s" , to );
        int from_row = toupper(from[0]) - 'A';
        int from_col = from[1] - '1';
        int position;
        // Convert "to" to uppercase
        for (int i = 0; to[i]; i++) {
            to[i] = toupper((unsigned char) to[i]);
        }
        // Error handling
        if (strcmp(to, "R") != 0 && strcmp(to, "L") != 0 && strcmp(to, "RB") != 0 && strcmp(to, "LB") != 0) {
            wprintf (L"Invalid Input!\n") ;
            continue;
        }
        if ((from_row % 2 == 0 && from_col % 2 == 1) || (from_row % 2 == 1 && from_col % 2 == 0)) {
            wprintf (L"Invalid Number!\n") ;
            continue;
        }
        // Get position of piece
        position = from_row * 4 + from_col / 2;
        if (GetBit(black_pieces, position) == 0 && GetBit(white_pieces, position) == 0) {
            wprintf (L"There is no piece there!\n");
        }
        // Piece movement
        if (GetBit(black_pieces, position) == 1 && GetBit(black_kings, position) == 0) {
            if (strcmp(to, "L") == 0) {
                int target = from_row % 2 ? position + 4 : position + 3;
                // Error handling
                if (position % 8 == 0) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(black_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(white_pieces, target) == 0) {
                    black_pieces = ClearBit(black_pieces, position);
                    black_pieces = SetBit(black_pieces, target);
                } else {
                    // Capture piece
                    if (target % 8 == 0 || GetBit(white_pieces, target + (from_row % 2 ? 3 : 4)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    black_pieces = ClearBit(black_pieces, position);
                    white_pieces = ClearBit(white_pieces, target);
                    white_kings = ClearBit(white_kings, target);
                    black_pieces = SetBit(black_pieces, target + (from_row % 2 ? 3 : 4));
                }
            } else if (strcmp(to, "R") == 0) {
                int target = from_row % 2 ? position + 5 : position + 4;
                // Error handling
                if (position % 8 == 3) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(black_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(white_pieces, target) == 0) {
                    black_pieces = ClearBit(black_pieces, position);
                    black_pieces = SetBit(black_pieces, target);
                } else {
                    // Capture piece
                    if (target % 8 == 3 || GetBit(white_pieces, target + (from_row % 2 ? 4 : 5)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    black_pieces = ClearBit(black_pieces, position);
                    white_pieces = ClearBit(white_pieces, target);
                    white_kings = ClearBit(white_kings, target);
                    black_pieces = SetBit(black_pieces, target + (from_row % 2 ? 4 : 5));
                }
            } else {
                // Error handling
                wprintf (L"Invalid Move!\n");
                continue;
            }
            // King promotion
            if (black_pieces >= 268435456) {
                for (int i = 28; i < 32; i++) {
                    if (GetBit(black_pieces , i) == 1) {
                        black_kings = SetBit(black_kings , i);
                    }
                }
            }
        } else if (GetBit(white_pieces, position) == 1 && GetBit(white_kings, position) == 0) {
            if (strcmp(to, "L") == 0) {
                int target = from_row % 2 ? position - 4 : position - 5;
                // Error handling
                if (position % 8 == 0) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(white_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(black_pieces, target) == 0) {
                    white_pieces = ClearBit(white_pieces, position);
                    white_pieces = SetBit(white_pieces, target);
                } else {
                    // Capture piece
                    if (target % 8 == 0 || GetBit(black_pieces, target - (from_row % 2 ? 5 : 4)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    white_pieces = ClearBit(white_pieces, position);
                    black_pieces = ClearBit(black_pieces, target);
                    black_kings = ClearBit(black_kings, target);
                    white_pieces = SetBit(white_pieces, target - (from_row % 2 ? 5 : 4));
                }
            } else if (strcmp(to, "R") == 0) {
                int target = from_row % 2 ? position - 3 : position - 4;
                // Error handling
                if (position % 8 == 7) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(white_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(black_pieces, target) == 0) {
                    white_pieces = ClearBit(white_pieces, position);
                    white_pieces = SetBit(white_pieces, target);
                } else {
                    // Capture piece
                    if (target % 8 == 7 || GetBit(black_pieces, target - (from_row % 2 ? 4 : 3)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    white_pieces = ClearBit(white_pieces, position);
                    black_pieces = ClearBit(black_pieces, target);
                    black_kings = ClearBit(black_kings, target);
                    white_pieces = SetBit(white_pieces, target - (from_row % 2 ? 4 : 3));
                }
            } else {
                // Error handling
                wprintf (L"Invalid Move!\n");
                continue;
            }
            // King promotion
            if (white_pieces <= 8) {
                for (int i = 0; i < 4; i++) {
                    if (GetBit(white_pieces , i) == 1) {
                        white_kings = SetBit(white_kings , i);
                    }
                }
            }
        } else if (GetBit(black_pieces, position) == 1 && GetBit(black_kings, position) == 1) {
            if (strcmp(to, "L") == 0) {
                int target = from_row % 2 ? position + 4 : position + 3;
                // Error handling
                if (position % 8 == 0) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(black_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(white_pieces, target) == 0) {
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    black_pieces = SetBit(black_pieces, target);
                    black_kings = SetBit(black_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 0 || GetBit(white_pieces, target + (from_row % 2 ? 3 : 4)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    white_pieces = ClearBit(white_pieces, target);
                    white_kings = ClearBit(white_kings, target);
                    black_pieces = SetBit(black_pieces, target + (from_row % 2 ? 3 : 4));
                    black_kings = SetBit(black_kings, target + (from_row % 2 ? 3 : 4));
                }
            } else if (strcmp(to, "R") == 0) {
                int target = from_row % 2 ? position + 5 : position + 4;
                // Error handling
                if (position % 8 == 3) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(black_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(white_pieces, target) == 0) {
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    black_pieces = SetBit(black_pieces, target);
                    black_kings = SetBit(black_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 3 || GetBit(white_pieces, target + (from_row % 2 ? 4 : 5)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    white_pieces = ClearBit(white_pieces, target);
                    white_kings = ClearBit(white_kings, target);
                    black_pieces = SetBit(black_pieces, target + (from_row % 2 ? 4 : 5));
                    black_kings = SetBit(black_kings, target + (from_row % 2 ? 4 : 5));
                }
            } else if (strcmp(to, "LB") == 0) {
                int target = from_row % 2 ? position - 4 : position - 5;
                // Error handling
                if (position % 8 == 0) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(black_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(white_pieces, target) == 0) {
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    black_pieces = SetBit(black_pieces, target);
                    black_kings = SetBit(black_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 0 || GetBit(white_pieces, target - (from_row % 2 ? 5 : 4)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    white_pieces = ClearBit(white_pieces, target);
                    white_kings = ClearBit(white_kings, target);
                    black_pieces = SetBit(black_pieces, target - (from_row % 2 ? 5 : 4));
                    black_kings = SetBit(black_kings, target - (from_row % 2 ? 5 : 4));
                }
            } else if (strcmp(to, "RB") == 0) {
                int target = from_row % 2 ? position - 3 : position - 4;
                // Error handling
                if (position % 8 == 7) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(black_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(white_pieces, target) == 0) {
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    black_pieces = SetBit(black_pieces, target);
                    black_kings = SetBit(black_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 7 || GetBit(white_pieces, target - (from_row % 2 ? 4 : 3)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    black_pieces = ClearBit(black_pieces, position);
                    black_kings = ClearBit(black_kings, position);
                    white_pieces = ClearBit(white_pieces, target);
                    white_kings = ClearBit(white_kings, target);
                    black_pieces = SetBit(black_pieces, target - (from_row % 2 ? 4 : 3));
                    black_kings = SetBit(black_kings, target - (from_row % 2 ? 4 : 3));
                }
            } else {
                // Error handling
                wprintf(L"Invalid Move!\n");
                continue;
            }
        } else if (GetBit(white_pieces, position) == 1 && GetBit(white_kings, position) == 1) {
            if (strcmp(to, "L") == 0) {
                int target = from_row % 2 ? position - 4 : position - 5;
                // Error handling
                if (position % 8 == 0) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(white_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move pieces
                if (GetBit(black_pieces, target) == 0) {
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    white_pieces = SetBit(white_pieces, target);
                    white_kings = SetBit(white_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 0 || GetBit(black_pieces, target - (from_row % 2 ? 5 : 4)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    black_pieces = ClearBit(black_pieces, target);
                    black_kings = ClearBit(black_kings, target);
                    white_pieces = SetBit(white_pieces, target - (from_row % 2 ? 5 : 4));
                    white_kings = SetBit(white_kings, target - (from_row % 2 ? 5 : 4));
                }
            } else if (strcmp(to, "R") == 0) {
                int target = from_row % 2 ? position - 3 : position - 4;
                // Error handling
                if (position % 8 == 7) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(white_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(black_pieces, target) == 0) {
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    white_pieces = SetBit(white_pieces, target);
                    white_kings = SetBit(white_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 7 || GetBit(black_pieces, target - (from_row % 2 ? 4 : 3)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    black_pieces = ClearBit(black_pieces, target);
                    black_kings = ClearBit(black_kings, target);
                    white_pieces = SetBit(white_pieces, target - (from_row % 2 ? 4 : 3));
                    white_kings = SetBit(white_kings, target - (from_row % 2 ? 4 : 3));
                }
            } else if (strcmp(to, "LB") == 0) {
                int target = from_row % 2 ? position + 4 : position + 3;
                // Error handling
                if (position % 8 == 0) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(white_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(black_pieces, target) == 0) {
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    white_pieces = SetBit(white_pieces, target);
                    white_kings = SetBit(white_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 0 || GetBit(black_pieces, target + (from_row % 2 ? 3 : 4)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    black_pieces = ClearBit(black_pieces, target);
                    black_kings = ClearBit(black_kings, target);
                    white_pieces = SetBit(white_pieces, target + (from_row % 2 ? 3 : 4));
                    white_kings = SetBit(white_kings, target + (from_row % 2 ? 3 : 4));
                }
            } else if (strcmp(to, "RB") == 0) {
                int target = from_row % 2 ? position + 5 : position + 4;
                // Error handling
                if (position % 8 == 3) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                if (GetBit(white_pieces, target) == 1) {
                    wprintf(L"Invalid Move!\n");
                    continue;
                }
                // Move piece
                if (GetBit(black_pieces, target) == 0) {
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    white_pieces = SetBit(white_pieces, target);
                    white_kings = SetBit(white_kings, target);
                } else {
                    // Capture piece
                    if (target % 8 == 3 || GetBit(black_pieces, target + (from_row % 2 ? 4 : 5)) == 1) {
                        wprintf (L"Invalid Move!\n");
                        break;
                    }
                    white_pieces = ClearBit(white_pieces, position);
                    white_kings = ClearBit(white_kings, position);
                    black_pieces = ClearBit(black_pieces, target);
                    black_kings = ClearBit(black_kings, target);
                    white_pieces = SetBit(white_pieces, target + (from_row % 2 ? 4 : 5));
                    white_kings = SetBit(white_kings, target + (from_row % 2 ? 4 : 5));
                }
            } else {
                // Error handling
                wprintf (L"Invalid Move!\n");
                continue;
            }
        }
        // Win condition
        if (CountBits(black_pieces) == 0) {
            wprintf (L"White Wins!\n");
            break;
        }
        if (CountBits(white_pieces) == 0) {
            wprintf (L"Black Wins!\n");
            break;
        }
    }
}