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

// ��� ������ � ��������� ���� ����� �������� ���������
void writeToFileTextPointer(FILE* filePointer) {
    Info info = { "USB", 16, "Project", "Ivan" };
    fprintf(filePointer, "%s %d %s %s\n", info.carrier.c_str(), info.size, info.title.c_str(), info.author.c_str());
}

// ��� ������ � ��������� ���� ����� �����
void writeToFileTextStream(const string& filename) {
    ofstream file(filename, ios::out);
    if (file.is_open()) {
        Info info = { "DVD", 8, "Movie", "John" };
        file << info.carrier << " " << info.size << " " << info.title << " " << info.author << "\n";
        file.close();
    }
}

// ��� ������ � �������� ���� ����� �������� ���������
void writeToFileBinaryPointer(FILE* filePointer) {
    Info info = { "HDD", 1024, "Backup", "Alice" };
    fwrite(&info, sizeof(Info), 1, filePointer);
}

// ��� ������ � �������� ���� ����� �����
void writeToFileBinaryStream(const string& filename) {
    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        Info info = { "SSD", 512, "OS Image", "Mark" };
        file.write(reinterpret_cast<const char*>(&info), sizeof(Info));
        file.close();
    }
}


// ��� ������ �� ���������� ����� ����� �������� ���������
void readFromFileTextPointer(FILE* filePointer) {
    char carrier[256];
    int size;
    char title[256];
    char author[256];
    while (fscanf_s(filePointer, "%s %d %s %s", carrier, sizeof(carrier), &size, title, sizeof(title), author, sizeof(author)) != EOF) {
        cout << carrier << " " << size << " " << title << " " << author << endl;
    }
}

// ��� ������ �� ���������� ����� ����� �����
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

// ��� ������ �� ��������� ����� ����� �������� ���������
void readFromFileBinaryPointer(FILE* filePointer) {
    Info info;
    while (fread(&info, sizeof(Info), 1, filePointer)) {
        cout << info.carrier << " " << info.size << " " << info.title << " " << info.author << endl;
    }
}

// ��� ������ �� ��������� ����� ����� �����
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

//�������, ������� ������� ������ ������� � �������� �������
void deleteFirstWithSize(const string& filename, int sizeToDelete) {
    ifstream file(filename, ios::in); // ��������� ���� ��� ������
    ofstream tempFile("temp.txt", ios::out); // ��������� ��������� ���� ��� ������
    if (file.is_open() && tempFile.is_open()) {
        string carrier, title, author;
        int size;
        bool deleted = false; // ���� ��� ������������, ��� �� ����� �������
        while (file >> carrier >> size >> title >> author) {
            if (!deleted && size == sizeToDelete) {
                deleted = true; // ������������� ���� � true, ����� ���������� ���� �������
                continue;
            }
            // ���������� ������ � ��������� ����
            tempFile << carrier << " " << size << " " << title << " " << author << "\n";
        }
        file.close();
        tempFile.close();
        // ������� ������ ���� � ��������������� ��������� ���� � ��������
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
}

//�������, ������� ��������� K ��������� � ����� �����
void addKElements(const string& filename, int k) {
    cerr << "�������� ������� ����: " << filename << endl;  // �������, ��� �������� ������� ����
    ofstream file(filename, ios::app);// ��������� ���� � ������ ����������

    if (file.fail()) {  // �������� �� ������ ��� �������� �����
        cerr << "�� ������� ������� ���� ��� ������: " << filename << endl;
        return;  // ���� ���� �� ��������, ������� �� �������
    }

        for (int i = 0; i < k; ++i) {

            Info info;
            
            cout << "������� �������� (��������, USB, HDD, DVD): ";
            getline(cin, info.carrier);

            cout << "������� ����� (��������, 16, 1024): ";
            cin >> info.size;
            cin.ignore();  // ������� ����� ����� ����� �����

            cout << "������� �������� (��������, '������', '�����'): ";
            cin >> info.title;
            getline(cin, info.title);  // ���������� getline ��� ����� ����� � ���������

            cout << "������� ������ (��������, '����', '�����'): ";
            cin >> info.author;
            getline(cin, info.author);  // ���������� getline ��� ����� ����� � ���������

            //cin >> info.carrier >> info.size >> info.title >> info.author;

            file << info.carrier << " " << info.size << " " << info.title << " " << info.author << "\n";
        }

        file.close();
        cerr << "���� ������� ������." << endl;  // ������� ���������, ��� ���� ��� ������� ������
}

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");

    string filename = "data.txt";

    // �������� � ������ ����� � ��������� ������ ����� �������� ���������
    FILE* filePointer;
    if (fopen_s(&filePointer, filename.c_str(), "w") != 0) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
    }
    else {
        writeToFileTextPointer(filePointer);
        fclose(filePointer);
    }

    // ������ ����� � ��������� ������ ����� �������� ��������� � ����� �� �����
    filePointer = fopen(filename.c_str(), "r");
    if (filePointer) {
        cout << "���������� ����� ����� ������:\n";
        readFromFileTextPointer(filePointer);
        fclose(filePointer);
    }
    else {
        cerr << "�� ������� ������� ���� ��� ������!" << endl;
    }

    // ���������� ���������
    addKElements(filename, 2);

    // �������� ������� �������� � �������� �������
    deleteFirstWithSize(filename, 16);

    // ����� ����������� ����� (��������� ����� ����� �����)
    cout << "\n���������� ����� ����� ��������� (��������� �����):\n";
    readFromFileTextStream(filename);

    return 0;
}
