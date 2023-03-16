#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;

const int M = 5, N = 8;

void view_file(char* name) // Переглянути файл
{
    char s[100]; FILE* f;
    f = fopen(name, "rt");
    if (f == NULL) { puts("Cannot open file to view"); return; }
    printf("\nПерегляд файлу: %s\n", name);
    while (fgets(s, 100, f))
    {
        s[strlen(s) - 1] = '\0';
        puts(s);
    }
    fclose(f);
}

void create_matrix(double matr[M][N], char* name) // Заповнити матрицю значеннями із файлу
{
    FILE* f;
    char s[100], * t;
    int i = 0, j;
    f = fopen(name, "rt");
    if (f == NULL) { puts("Cannot open file to view"); return; }
    while (fgets(s, 100, f))
    {
        j = 0;
        t = strtok(s, " \t");
        while (t != NULL)
        {
            matr[i][j] = atof(t);
            t = strtok(NULL, " \t");
            j++;
        }
        i++;
    }
    fclose(f);
    return;
}

void output_matrix(double matr[M][N], char* name2) // Вивести матрицю на екран та у файл
{
    FILE* f2;
    int i, j;
    f2 = fopen(name2, "wt");
    if (f2 == NULL) { puts("Cannot open file"); return; }
    printf("\n\nПерегляд матрицi:\n");
    fprintf(f2, "Перегляд матрицi:\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        { // Вивести елемент матриці на екран
            printf("%7.1f\t", matr[i][j]);
            // Записати елемент у файл
            fprintf(f2, "%7.1f\t", matr[i][j]);
        }
        puts("");
        fprintf(f2, "%s", "\n");
    }
    fclose(f2);
    return;
}

void amount(double matr[M][N], char* name2) //Обчислити к-ть + елементів і к-ть 0 показників вимірювань датчиків (елементів матриці).
{
    FILE* f2;
    int i, j;
    f2 = fopen(name2, "at");
    if (f2 == NULL)
    {
        puts("Cannot open file to append data\n"); return;
    }
    int d = 0, n = 0;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matr[i][j] >= 0) d++;
            if (matr[i][j] == 0) n++;
        }
    }
    printf("\nКількість додатніх елементів:  %i\t", d);
    fprintf(f2, "\nКількість додатніх елементів: %i\n", d);
    printf("\nКількість 0 показників: %i\t", n);
    fprintf(f2, "\nКількість 0 показників: %i\n", n);
    fclose(f2);
}

void obchusleny(double matr[M][N], char* name2) //Обчислити сер. арифметичне вимірювання (стовпця матриці),який містить min значення матриці.
{
    FILE* f2;
    f2 = fopen(name2, "at"); // Відкрити файл для читання як текстовий
    if (f2 == NULL)
    {
        puts("Cannot open file to append data\n"); return;
    }
    puts("\nСер.арифметичне:");
    fprintf(f2, "\nСер.арифметичне:\n");
    double min = 0, sum = 0, ser = 0; int kol = 0, h = 0;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        
            if (matr[i][j] < min) 
            {
                min = matr[i][j];
                h = j;
            }
    }
        for (int i = 0; i < M; i++)
        {
            kol++;
            sum += matr[i][h];
        }
    ser = sum / kol;
    printf("%7.1f\t", ser); 
    fprintf(f2, "%7.1f\t", ser); 
    fclose(f2);
}

void create_vector(double matr[M][N], double vekt[M], char* name2) //Обчислити елементи вектора як суми елементів рядків матриці з парними індексами стовпців
{
    FILE* f2;
    f2 = fopen(name2, "at"); // Відкрити файл для читання як текстовий
    if (f2 == NULL)
    {
        puts("Cannot open file to append data\n"); return;
    }
    puts("\nСтворений вектор:");
    fprintf(f2, "\nСтворений вектор:\n");
    for (int i = 0; i < M; i++)
    {
        double sum = 0;
        for (int j = 1; j < N; j+=2)
        {
            sum += matr[i][j];
        }
        vekt[i] = sum;
        printf("%7.1f\t", vekt[i]); 
        fprintf(f2, "%7.1f\t", vekt[i]); 
    }
    fclose(f2);
}

void create_masiv(double matr[M][N], char* name2) //дин.мас. з чисел, розміщених після 1-го двоциф. числа матриці
{
    FILE* f2;
    f2 = fopen(name2, "at"); // Відкрити файл для читання як текстовий
    if (f2 == NULL)
    {
        puts("Cannot open file to append data\n"); return;
    }
    puts("\nСтворений динамічний масив:");
    fprintf(f2, "\nСтворений динамічний масив:\n");
    int count = 0, g=0;
    int k, h;
    bool p = false;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (abs(matr[i][j]) > 9 && abs(matr[i][j]) < 100 && !p) //проверка до первого двухзначного числа
            {
                p = true;
                k = i; h = j;
            }
            if (p)
            {
                count++;
            }
        }
    }
    double* arr = new double[count];
    for (int i = k, g = 0; i < M; i++)
    {
        int j;
        if (g == 0)
            j = h;
        else
            j = 0;
        for ( j ; j < N; j++)
        {
            arr[g++] = matr[i][j];
        }
    }
    for (int i = 0; i < count; i++)
    {
        printf("%7.1f\t", arr[i]); 
        fprintf(f2, "%7.1f\t", arr[i]); 
    }
    fclose(f2);
}

void indexsu(char* name3, char* name2) //Вивести індекси всіх ком та крапок, які є у рядках
{
    FILE* f3, * f2; 
    char s[100]; int sum = 0;
    f3 = fopen(name3, "rt"); 
    if (f3 == NULL) { puts("Cannot open file to view"); return; }
    f2 = fopen(name2, "at"); 
    if (f2 == NULL) { puts("Cannot open file to append\n"); return; }
    puts("\nІндекси всіх ком та крапок:");
    fputs("\nІндекси всіх ком та крапок:\n", f2);
    while (fgets(s, 100, f3))
    {
        for (int i = 0; i < strlen(s); i++)
        {
            if (s[i] == ',' || s[i] == '.') 
            {
                printf("%i\t", i+sum); 
                fprintf(f2, "%i\t", i+sum);
            }
        }
        sum += strlen(s);
    }
    fclose(f2); 
    fclose(f3);
}

void slova(char* name3, char* name2) //Вивести слова файлу з довжиною > 7 симв. та обчислити їхню к-ть
{
    FILE* f3, * f2; 
    int k = 0;
    f3 = fopen(name3, "rt"); 
    if (f3 == NULL) { puts("Cannot open file to view"); return; }
    f2 = fopen(name2, "at"); 
    if (f2 == NULL) { puts("Cannot open file to append\n"); return; }
    char s[100], * t = new char[100];
    puts("\nСлова з довжиною > 7 символів:");
    fputs("\nСлова з довжиною > 7 символів:\n", f2);
    while (fgets(s, 100, f3))
    {
        t = strtok(s, " ,.;-^=:!?");
        while (t != NULL)
        {
            if (strlen(t) > 7)
            {
                t = strtok(t, " ,.;-^=:!?");
                k++;
                puts(t);
                fprintf(f2, "%s\n", t);
            }
            t = strtok(NULL, " ,.;-^=:!?");
        }
    }
    puts("\nЇх кількість:");
    fputs("\nЇх кількість:\n", f2);
    printf("%i\t", k);
    fprintf(f2, "%i\t", k);
    fclose(f2); 
    fclose(f3);
}

void redaguvany(char* name3) //Редагувати файл F3.txt з текстовими даними
{
    char s[100];
    char s_text[100]; char text[100];
    int choiсe = 0, num = 0, i = 0, p = 0, n = 0;
    FILE* f3;
    f3 = fopen(name3, "rt");
    if (f3 == NULL) { puts ("Cannot open file to view"); return; }
    while (fgets(s, 100, f3)) p++;
    char** temp = new char* [p];
    for (int i = 0; i < p; i++)
        temp[i] = new char[100];
    fseek(f3, 0, SEEK_SET);
    while (fgets(s,100,f3) && p>n) 
    {
        s[strlen(s) - 1] = '\0';
        strcpy(temp[n], s);
        n++;
    }
    fclose(f3);
    f3 = fopen(name3, "wt");
    cout<<"\nДля редагування по номеру рядка, введіть: 1\n" << "Для редагування по тексту які вони містять, введіть: 2\n";
    cin >> choiсe;
    if (choiсe == 1)
    {
        cout<<"\nВведіть текст:\n";
        getchar();
        gets_s(text, 100);
        cout<<"\nВведіть номер рядка, який потрібно редагувати:\n";
        cin >> num;
        for (int i = 0; i < p; i++)
            if (i + 1 != num) fprintf(f3, "%s\n", temp[i]);
            else fprintf(f3, "%s\n", text);
        fclose(f3);
        return;
    }
    else
    {
        cout<<"\nВведіть текст:\n";
        getchar();
        gets_s(text, 100);
        cout<<"\nВведіть текст для пошуку рядків з його вмістом для редагування:\n";
        gets_s(s_text, 100);
        for (int i = 0; i < p; i++)
            if (!strstr(temp[i], s_text)) fprintf(f3, "%s\n", temp[i]);
            else fprintf(f3, "%s\n", text);
        fclose(f3);
        return;
    }
}

void vudaleny(char* name3) //Видалення
{
    char s[100];
    char text[100];
    int choiсe = 0, num = 0, p = 0, n = 0;
    FILE* f3;
    f3 = fopen(name3, "rt");
    if (f3 == NULL) { puts("Cannot open file to view"); return; }
    while (fgets(s, 100, f3)) p++;
    char** temp = new char* [p];
    for (int i = 0; i < p; i++)
        temp[i] = new char[100];
    fseek(f3, 0, SEEK_SET);
    while (fgets(s, 100, f3) && p > n)
    {
        s[strlen(s) - 1] = '\0';
        strcpy(temp[n], s);
        n++;
    }
    fclose(f3);
    f3 = fopen(name3, "wt");
    cout << "\nДля видалення по номеру рядка, введіть: 1\n" << "Для видалення по тексту які вони містять, введіть: 2\n";
    cin >> choiсe;
    if (choiсe == 1)
    {
        cout << "\nВведіть номер рядка, який потрібно видалити:\n";
        cin >> num;
        for (int i = 0; i < p; i++)
            if (i + 1 != num) fprintf(f3, "%s\n", temp[i]);
        fclose(f3);
        return;
    }
    else
    {
        cout << "\nВведіть текст для пошуку рядків з його вмістом для видалення:\n";
        getchar();
        gets_s(text, 100);
        for (int i = 0; i < p; i++)
            if (!strstr(temp[i], text)) fprintf(f3, "%s\n", temp[i]);
        fclose(f3);
        return;
    }
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    double A[M][N], B[N];
    char name1[] = "E:\\F1.txt";
    char name2[] = "E:\\F2.txt";
    char name3[] = "E:\\F3.txt";

    view_file(name1); // Перегляд файлу
    create_matrix(A, name1); // Заповнити матрицю числами із файлу
    output_matrix(A, name2); // Вивести матрицю на екран та у файл
    amount(A, name2); //Обчислити к-ть + елементів і к-ть 0 показників вимірювань датчиків (елементів матриці).
    obchusleny(A, name2); //Обчислити сер. арифметичне вимірювання (стовпця матриці),який містить min значення матриці.
    create_vector(A, B, name2); //Обчислити елементи вектора як суми елементів рядків матриці з парними індексами стовпців
    create_masiv(A, name2); //дин.мас. з чисел, розміщених після 1-го двоциф. числа матриці
    view_file(name3); // Переглянути файл
    indexsu(name3, name2); //Вивести індекси всіх ком та крапок, які є у рядках
    slova(name3, name2); //Вивести слова файлу з довжиною > 7 симв. та обчислити їхню к-ть
    view_file(name2); // Переглянути файл
    redaguvany(name3); //Редагувати файл F3.txt з текстовими даними
    view_file(name3); // Переглянути файл
    vudaleny(name3); //Видалення
    view_file(name3); // Переглянути файл
}


/*Біла хмара в синій блузі
Низько-низько так висить:
Що там робиться на лузі?
Може, квіточки полить?
Може, вже засохли віти?
Травам нічого попить?
Будуть верби зеленіти,
Ось лиш дощик прилетить.*/