#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>   // for getch()
using namespace std;

/* ================== COLOR ================== */
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* ================== LOGIC ================== */
bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 0 = Sunday
int firstDayOfYear(int year) {
    int day = 1; // 1900-01-01 was Monday
    for (int i = 1900; i < year; i++) {
        day += isLeap(i) ? 366 : 365;
    }
    return day % 7;
}

/* ================== HEADER ================== */
void printHeader(const string &title) {
    setColor(11);
    cout << "\n+----------------------------------+\n";
    cout << "| " << title;
    for (int i = title.length(); i < 32; i++) cout << " ";
    cout << "|\n";
    cout << "+----------------------------------+\n\n";
    setColor(7);
}

/* ================== MONTH ================== */
void printMonth(int year, int month, int &startDay) {
    string months[] = {
        "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };

    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 1 && isLeap(year)) days[month] = 29;

    time_t t = time(0);
    tm *now = localtime(&t);

    setColor(14);
    cout << "\n        " << months[month] << " " << year << "\n";
    setColor(11);
    cout << "+----------------------------+\n";
    cout << "| Sun Mon Tue Wed Thu Fri Sat|\n";
    cout << "+----------------------------+\n";
    setColor(7);

    for (int i = 0; i < startDay; i++)
        cout << "    ";

    for (int d = 1; d <= days[month]; d++) {

        // Highlight today
        if (d == now->tm_mday &&
            month == now->tm_mon &&
            year == now->tm_year + 1900) {
            setColor(12);
        }
        // Highlight weekend
        else if (startDay % 7 == 0 || startDay % 7 == 6) {
            setColor(9);
        } else {
            setColor(7);
        }

        printf("%3d ", d);
        setColor(7);

        if (++startDay % 7 == 0)
            cout << endl;
    }

    startDay %= 7;
    cout << endl;
}

/* ================== FULL YEAR ================== */
void fullYearCalendar(int year) {
    system("cls");
    int startDay = firstDayOfYear(year);
    for (int m = 0; m < 12; m++) {
        printMonth(year, m, startDay);
    }
    system("pause");
}

/* ================== SINGLE MONTH ================== */
void singleMonthCalendar(int year) {
    int month;
    cout << "Enter month (1-12): ";
    cin >> month;
    month--;

    system("cls");

    int startDay = firstDayOfYear(year);
    for (int i = 0; i < month; i++) {
        int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if (i == 1 && isLeap(year)) days[i] = 29;
        startDay = (startDay + days[i]) % 7;
    }

    printMonth(year, month, startDay);
    system("pause");
}

/* ================== INTERACTIVE (WASD KEYS) ================== */
void interactiveMonthView(int year) {
    int month = 0;

    while (true) {
        system("cls");

        int startDay = firstDayOfYear(year);
        for (int i = 0; i < month; i++) {
            int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
            if (i == 1 && isLeap(year)) days[i] = 29;
            startDay = (startDay + days[i]) % 7;
        }

        printMonth(year, month, startDay);

        setColor(10);
        cout << "\nControls:";
        cout << "\nA Previous Month   D Next Month";
        cout << "\nW Next Year        S Previous Year";
        cout << "\nQ Quit";
        setColor(7);

        char ch = getch();

        if (ch == 'a' || ch == 'A')
            month = (month + 11) % 12;
        else if (ch == 'd' || ch == 'D')
            month = (month + 1) % 12;
        else if (ch == 'w' || ch == 'W')
            year++;
        else if (ch == 's' || ch == 'S')
            year--;
        else if (ch == 'q' || ch == 'Q')
            break;
    }
}

/* ================== MAIN ================== */
int main() {
    int choice, year;

    system("cls");
    printHeader("ADVANCED C++ CALENDAR");

    cout << "Enter Year: ";
    cin >> year;

    while (true) {
        system("cls");
        printHeader("CALENDAR MENU");

        setColor(10);
        cout << "1. View Full Year Calendar\n";
        cout << "2. View Specific Month\n";
        cout << "3. Interactive Month View (W/A/S/D Keys)\n";
        cout << "4. Exit\n";
        setColor(7);

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fullYearCalendar(year); break;
            case 2: singleMonthCalendar(year); break;
            case 3: interactiveMonthView(year); break;
            case 4:
                setColor(11);
                cout << "\nThank you for using Advanced Calendar!\n";
                setColor(7);
                return 0;
            default:
                setColor(12);
                cout << "Invalid Choice!";
                setColor(7);
                Sleep(1000);
        }
    }
}
