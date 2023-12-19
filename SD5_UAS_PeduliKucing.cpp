#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <list>
#include <algorithm>

using namespace std;

int BOARD[10][10];
list<int> markedNumbers;

struct Bingo {
    char name[30];
    int ticket[10];
    int top;
} bingo[5];

void gotoxy(int x, int y);
void marknum(int ticket[10], int num, int &y);
void introduction();
void displayboard(int BOARD[10][10]);
void displaytickets(int ticket[10], int k, const list<int> &markedNumbers);
void sort(int ticket[10]);

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void marknum(int ticket[10], int num, int &y) {
    int flag = 0;

    for (int i = 0; i < y; i++) {
        if (ticket[i] == num) {
            flag = 1;
            int pos = i;
            break;
        }
    }

    if (flag == 1) {
        markedNumbers.push_back(num);
        y--;
    }
}

void introduction() {
    system("cls");

    for (int i = 0; i < 40; i++) {
        cout << "*";
    }
    cout << endl;

    cout << "\t WELCOME TO Batu Goncang" << endl;
    for (int i = 0; i < 40; i++) {
        cout << "*";
    }
    cout << endl;

    getch();
}

void displayboard(int BOARD[10][10]) {
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << endl;
        for (int j = 0; j < 10; j++) {
            int num = BOARD[i][j];
            if (find(markedNumbers.begin(), markedNumbers.end(), num) != markedNumbers.end()) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                cout << num << "\t";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                cout << num << "\t";
            }
        }
    }
}

void displaytickets(int ticket[10], int k, const list<int> &markedNumbers) {
    for (int j = 0; j < k; j++) {
        int currentNumber = ticket[j];
        if (find(markedNumbers.begin(), markedNumbers.end(), currentNumber) != markedNumbers.end()) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            cout << currentNumber << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else {
            cout << currentNumber << " ";
        }
    }
}

void sort(int ticket[10]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (ticket[j] > ticket[j + 1]) {
                int temp = ticket[j];
                ticket[j] = ticket[j + 1];
                ticket[j + 1] = temp;
            }
        }
    }
}

int main() {
    START:
    int n, i, j, k, l, num, a[100];
    char ch;

    system("cls");
    srand(time(0));

    introduction();

    cout << "Enter number of players : ";
    cin >> n;
    
    cin.ignore();
    cout << "\nEnter players' name : " << endl;
    for (i = 0; i < n; i++) {
        cout << "Player " << i + 1 << " : ";
        cin.getline(bingo[i].name, 30);
    }

    k = 1;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            BOARD[i][j] = k;
            k++;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < 10; j++) {
        AGAIN:
            num = rand() % 100 + 1;
            bingo[i].ticket[j] = num;
            for (k = 0; k < j; k++) {
                if (num == bingo[i].ticket[k])
                    goto AGAIN;
            }
        }
        bingo[i].top = 10;
    }

    for (i = 0; i < n; i++) {
        sort(bingo[i].ticket);
    }

    system("cls");

    displayboard(BOARD);
    
    for (l = 0; l < n; l++) {
        cout << "\n\n";
        cout << bingo[l].name << "'s ticket : ";
        displaytickets(bingo[l].ticket, bingo[l].top, markedNumbers);
    }
    
    getch();

    displayboard(BOARD);
    
    i = 0;
    do {
        system("cls");
        AGAIN1:
            num = rand() % 100 + 1;
            a[i] = num;
            for (j = 0; j < i; j++) {
                if (num == a[j])
                    goto AGAIN1;
            }
            markedNumbers.push_back(num);

            displayboard(BOARD);
            
            cout << "\n\nThe Lucky Number is : " << num << endl;

            for (k = 0; k < n; k++) {
                if (all_of(begin(bingo[k].ticket), end(bingo[k].ticket), [&](int num){ return find(markedNumbers.begin(), markedNumbers.end(), num) != markedNumbers.end() || num == -1; })) {
                    cout << "\nBINGO.... " << bingo[k].name << " wins." << endl;

                    getch();
                    system("cls");

                    cout << "\nDo You want to play again? (Y/N) : ";
                    cin >> ch;

                    if (toupper(ch) == 'Y') {
                        markedNumbers.clear();
                        goto START;
                    } else {
                        exit(0);
                    }
                }
        }

        for (l = 0; l < n; l++) {
            cout << "\n";
            cout << bingo[l].name << "'s ticket : ";
            displaytickets(bingo[l].ticket, bingo[l].top, markedNumbers);
            cout << "\n";
        }

        getch();
        i++;
    } while (i <= 100);
    
    getch();
    return 0;
}