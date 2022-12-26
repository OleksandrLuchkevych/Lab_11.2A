#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialty { КомпНауки, Інформатика, МатематикаТаЕкономіка, ФізикаТаІнформатика, ТрудовеНавчання };

string specialtyStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика",
"Трудове навчання" };

struct Student
{
    char Surname[99];
    short unsigned course;
    Specialty specialty;
    short unsigned physics;
    short unsigned mathematics;
    short unsigned informatics;

};

void EnterSave(char* fname);
void LoadPrint(char* fname);
void CountMarks(char* fname, int& countInformatics5, int& countInformatics4, int& countInformatics3);
void MinAverage(char* fname, double& Procent);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[61];
    char ch;
    double Procent = 0.0;
    int countInformatics5 = 0;
    int countInformatics4 = 0;
    int countInformatics3 = 0;

    do
    {
        //cout << "Виберіть дію:\n"
        cout << "1. Заповнити дані\n"
            << "2. Вивести на екран дані\n"
            << "3. Процент студентів що мають і з фізики і з математики оцінки 4 або 5\n"
            << "4. Кількість оцінок 5,4 i 3 з інформатики:\n"
            << "0. Завершити роботу програми\n\n";
        cout << "Виберіть дію:\n"; cin >> ch; cout << "\n";
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "Введіть ім'я файлу: "; cin.getline(fname, 100);
            EnterSave(fname);
            cout << "\n\n";
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу для зчитування даних: "; cin.getline(fname, 100);
            LoadPrint(fname);
            cout << "\n\n";
            break;
        case '3':
            MinAverage(fname, Procent);
            cout << "Відсоток студентів: " << Procent << " %" << "\n";
            cout << "\n\n";
            break;
        case '4':
            CountMarks(fname, countInformatics5, countInformatics4, countInformatics3);
            cout << "Кількість оцінок 5 з інформатики: " << countInformatics5 << "\n";
            cout << "Кількість оцінок 4 з інформатики: " << countInformatics4 << "\n";
            cout << "Кількість оцінок 3 з інформатики: " << countInformatics3 << "\n";
            cout << "\n\n";
            break;
        default:
            cout << "Нерозпізнана команда!\n\n";
        }
    } while (ch != '0');

    system("pause");
    return 0;
}

void EnterSave(char* fname)
{
    ofstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;

    int specialty;
    char ch;
    int i = 0;
    do
    {
        cout << "Студент №" << i + 1 << ":\n";
        i++;
        cin.sync();
        cout << "Прізвище: "; cin >> student.Surname;
        cout << "Курс: "; cin >> student.course;
        cout << "Спеціальність (КомпНауки - 0, Інформатика - 1, Математика та економіка - 2, Фізика та інформатика - 3, Трудове навчання - 4): ";
        cin >> specialty;
        student.specialty = (Specialty)specialty;
        cout << "Оцінка з фізики: "; cin >> student.physics;
        cout << "Оцінка з математики: "; cin >> student.mathematics;
        cout << "Оцінка з інформатики: "; cin >> student.informatics; cout << "\n";

        if (!f.write((char*)&student, sizeof(Student)))
        {
            cerr << "Помилка відкриття файлу" << endl;
        }
        cout << "Введіть \'y\', щоб продовжити введення:\n\n "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "Не вдалося відкрити файл \'" << fname << "'" << endl;
        return;
    }

    Student student;
    int i = 0;

    cout << "+-----------------------------------------------------------------------------------------------------------+"
        << "\n";
    cout << "| №   |   Прізвище   |   Курс   |       Спеціальність       |   Фізика   |   Математика   |   Інформатика   |"
        << "\n";
    cout << "+-----------------------------------------------------------------------------------------------------------+"
        << "\n";

    while (f.read((char*)&student, sizeof(Student)))
    {
        cout << "| " << setw(2) << right << i + 1 << setw(2) << " ";
        cout << "| " << setw(9) << left << student.Surname << setw(6)
            << "| " << setw(5) << left << student.course << setw(4) << " "
            << "| " << setw(10) << right << specialtyStr[student.specialty] << setw(10) << " "
            << "| " << setw(6) << left << student.physics << setw(5) << " "
            << "| " << setw(8) << left << student.mathematics << setw(7) << " "
            << "| " << setw(8) << left << student.informatics << setw(8) << " " << "|" << "\n";
        cout << "+-----------------------------------------------------------------------------------------------------------+"
            << "\n";
        ++i;
    }
}

void CountMarks(char* fname, int& countInformatics5, int& countInformatics4, int& countInformatics3)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;

    while (f.read((char*)&student, sizeof(Student)))
    {
        if (student.informatics == 5)
            countInformatics5++;
        if (student.informatics == 4)
            countInformatics4++;
        if (student.informatics == 3)
            countInformatics3++;
    }
}

void MinAverage(char* fname, double& Procent)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;
    int NumberOfStudents = 0;
    int kilkist = 0;
    while (f.read((char*)&student, sizeof(Student)))
    {
        NumberOfStudents++;
        if ((student.physics == 4 && student.mathematics == 4) || (student.physics == 4 && student.mathematics == 5) || (student.physics == 5 && student.mathematics == 4) || (student.physics == 5 && student.mathematics == 5))
            kilkist++;

    }
    Procent = 100.0 * kilkist / NumberOfStudents;

}
