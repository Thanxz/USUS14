#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

struct Info {
    string carrier;
    int size;
    string title;
    string author;
};

// Для записи в текстовый файл через файловый указатель
void writeToFileTextPointer(FILE* filePointer) {
    Info info = { "USB", 16, "Project", "Ivan" };
    fprintf(filePointer, "%s %d %s %s\n", info.carrier.c_str(), info.size, info.title.c_str(), info.author.c_str());
}

// Для записи в текстовый файл через поток
void writeToFileTextStream(const string& filename) {
    ofstream file(filename, ios::out);
    if (file.is_open()) {
        Info info = { "DVD", 8, "Movie", "John" };
        file << info.carrier << " " << info.size << " " << info.title << " " << info.author << "\n";
        file.close();
    }
}

// Для записи в бинарный файл через файловый указатель
void writeToFileBinaryPointer(FILE* filePointer) {
    Info info = { "HDD", 1024, "Backup", "Alice" };
    fwrite(&info, sizeof(Info), 1, filePointer);
}

// Для записи в бинарный файл через поток
void writeToFileBinaryStream(const string& filename) {
    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        Info info = { "SSD", 512, "OS Image", "Mark" };
        file.write(reinterpret_cast<const char*>(&info), sizeof(Info));
        file.close();
    }
}


// Для чтения из текстового файла через файловый указатель
void readFromFileTextPointer(FILE* filePointer) {
    char carrier[256];
    int size;
    char title[256];
    char author[256];
    while (fscanf_s(filePointer, "%s %d %s %s", carrier, sizeof(carrier), &size, title, sizeof(title), author, sizeof(author)) != EOF) {
        cout << carrier << " " << size << " " << title << " " << author << endl;
    }
}

// Для чтения из текстового файла через поток
void readFromFileTextStream(const string& filename) {
    ifstream file(filename, ios::in);
    if (file.is_open()) {
        string carrier, title, author;
        int size;
        while (file >> carrier >> size >> title >> author) {
            cout << carrier << " " << size << " " << title << " " << author << endl;
        }
        file.close();
    }
}

// Для чтения из бинарного файла через файловый указатель
void readFromFileBinaryPointer(FILE* filePointer) {
    Info info;
    while (fread(&info, sizeof(Info), 1, filePointer)) {
        cout << info.carrier << " " << info.size << " " << info.title << " " << info.author << endl;
    }
}

// Для чтения из бинарного файла через поток
void readFromFileBinaryStream(const string& filename) {
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        Info info;
        while (file.read(reinterpret_cast<char*>(&info), sizeof(Info))) {
            cout << info.carrier << " " << info.size << " " << info.title << " " << info.author << endl;
        }
        file.close();
    }
}

//функция, которая удаляет первый элемент с заданным объемом
void deleteFirstWithSize(const string& filename, int sizeToDelete) {
    ifstream file(filename, ios::in); // Открываем файл для чтения
    ofstream tempFile("temp.txt", ios::out); // Открываем временный файл для записи
    if (file.is_open() && tempFile.is_open()) {
        string carrier, title, author;
        int size;
        bool deleted = false; // Флаг для отслеживания, был ли удалён элемент
        while (file >> carrier >> size >> title >> author) {
            if (!deleted && size == sizeToDelete) {
                deleted = true; // Устанавливаем флаг в true, чтобы пропустить этот элемент
                continue;
            }
            // Записываем данные в временный файл
            tempFile << carrier << " " << size << " " << title << " " << author << "\n";
        }
        file.close();
        tempFile.close();
        // Удаляем старый файл и переименовываем временный файл в исходный
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
}

//функция, которая добавляет K элементов в конец файла
void addKElements(const string& filename, int k) {
    cerr << "Пытаемся открыть файл: " << filename << endl;  // Выводим, что пытаемся открыть файл
    ofstream file(filename, ios::app);// Открываем файл в режиме добавления

    if (file.fail()) {  // Проверка на ошибку при открытии файла
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;  // Если файл не открылся, выходим из функции
    }

        for (int i = 0; i < k; ++i) {

            Info info;
            
            cout << "Введите носитель (например, USB, HDD, DVD): ";
            getline(cin, info.carrier);

            cout << "Введите объем (например, 16, 1024): ";
            cin >> info.size;
            cin.ignore();  // Очищаем буфер после ввода числа

            cout << "Введите название (например, 'Проект', 'Фильм'): ";
            cin >> info.title;
            getline(cin, info.title);  // Используем getline для ввода строк с пробелами

            cout << "Введите автора (например, 'Иван', 'Алиса'): ";
            cin >> info.author;
            getline(cin, info.author);  // Используем getline для ввода строк с пробелами

            //cin >> info.carrier >> info.size >> info.title >> info.author;

            file << info.carrier << " " << info.size << " " << info.title << " " << info.author << "\n";
        }

        file.close();
        cerr << "Файл успешно закрыт." << endl;  // Выводим сообщение, что файл был успешно закрыт
}

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");

    string filename = "data.txt";

    // Создание и запись файла в текстовом режиме через файловый указатель
    FILE* filePointer;
    if (fopen_s(&filePointer, filename.c_str(), "w") != 0) {
        cerr << "Ошибка при открытии файла для записи!" << endl;
    }
    else {
        writeToFileTextPointer(filePointer);
        fclose(filePointer);
    }

    // Чтение файла в текстовом режиме через файловый указатель и вывод на экран
    filePointer = fopen(filename.c_str(), "r");
    if (filePointer) {
        cout << "Содержимое файла после записи:\n";
        readFromFileTextPointer(filePointer);
        fclose(filePointer);
    }
    else {
        cerr << "Не удалось открыть файл для чтения!" << endl;
    }

    // Добавление элементов
    addKElements(filename, 2);

    // Удаление первого элемента с заданным объемом
    deleteFirstWithSize(filename, 16);

    // Вывод измененного файла (текстовый режим через поток)
    cout << "\nСодержимое файла после изменений (текстовый режим):\n";
    readFromFileTextStream(filename);

    return 0;
}
