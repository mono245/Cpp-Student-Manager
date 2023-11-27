#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>  
#include <fstream> 

using namespace std;

// мейн класс 
class StudentManager {
private:
    string fullname;
    int age;
    float avg;
    vector<string> students;
public:

    // функция для получения имени
    string getName() {
        string name;
        bool validName = false;

        do {
            cout << "Введите имя: ";
            getline(cin, name);
            if (name.length() <= 3 || name.length() >= 20) 
                cerr << "Имя не может быть меньше 3 или больше 20 символов" << endl;         
            else validName = true;
        } while (!validName);

        return name;
    }

    // функция для получения возраста
    int getAge() {
        bool validAge = false;
        string agein;
        int age;

        do {
            cout << "Введите возраст: ";
            getline(cin, agein);

            try {
                age = stoi(agein);
                validAge = true;
                if (age < 1) {
                    validAge = false;
                    cerr << "Возраст не может быть отрицательным или равным нулю" << endl;
                }
            } catch(invalid_argument const &ex) {
                cerr << "Возраст не может быть строкой" << endl;
              }
        } while (!validAge);

        return age;
    }

    // функция для получения среднего балла
    float getAvg() {
        bool validAvg;
        string avgin;
        float avg;

        do {
            cout << "Средний балл: ";
            getline(cin, avgin);

            try {
                avg = stof(avgin);
                validAvg = true;
                if (avg < 1) {
                    validAvg = false;
                    cerr << "Средний балл не может быть отрицательным или равным нулю" << endl;
                }
            } catch(invalid_argument const &ex) {
                cerr << "Средний балл не может быть строкой" << endl;
              }
        } while (!validAvg);

        return avg;
    }

    void addStudent() {
        cout << fixed << setprecision(2);
        string total, agein, avgin;
        string &ptotal = total;
        bool validAvg = false;

        cout << "Введите данные студента" << endl;

        // вставляем значения которые получили в инлайновых функциях
        fullname = getName();
        age = getAge();
        avg = getAvg();

        // адекватно преобразовываем средний балл в строку
        ostringstream ss;
        ss << avg;
        string strAvg = ss.str();

        // создаем переменную для хранения краткой информации
        ptotal = fullname + "(" + to_string(age) + " лет, средний балл: " + strAvg + ")"; 
        cout << endl << "Студент добавлен успешно, для проверки выберите операцию 2" << endl << endl;

        // добавляем в вектор students строку с информацией о студенте
        students.push_back(ptotal);

        cout << defaultfloat;
    }

    void studentsList() {
        cout << "Список студентов:" << endl;
        for (int i = 0; i < students.size(); i++) 
            cout << i + 1 << ". " << students[i] << endl;
        cout << endl;   
    }

    void searchByName() {
        string name;
        bool found = false;
        int results = 0;
        cout << "Введите имя студента для поиска: ";
        getline(cin, name); 

        cout << "Результаты поиска по имени \"" << name << "\":" << endl;

        for (size_t i = 0; i < students.size(); ++i) {
            size_t fi = students[i].find(name);
            if (fi != string::npos) {
                cout << i + 1 << ". " << students[i] << endl;
                found = true;
                results += 1;
            }
        }
        cout << "Найдено " << results << " результатов" << endl << endl;

        if (!found) {
            cout << "Студент с именем '" << name << "' не найден." << endl << endl;
        }
    }
    void saveAsFile() {
        string path;

        cout << "Введите путь для сохранения файла: ";
        getline(cin, path);

        // записываем данные в файл
        ofstream file;
        file.open(path);
        if(file.is_open()) {
            for (int i = 0; i < students.size(); ++i) 
                file << students[i] << "\n";
            cout << "Данные выгружены успешно" << endl << endl;
        }
        else cout << "Ошибка записи в файл" << endl;      
        file.close();
    }
    void readFile() {
        string path;
        string userline; 

        cout << "Введите путь к файлу для считывания: ";
        getline(cin, path);

        // считываем данные из файла
        ifstream file;
        file.open(path);
        
        if (file.is_open()){

            /*
                пока в файле есть символы,
                сохраняем строку в переменную
            */
            while(!file.eof()) {
                getline(file, userline);

                // если строка не пустая, добавляем ее в конец массива students
                if(!userline.empty())
                    students.push_back(userline);
            }
            cout << "Данные загружены успешно" << endl << endl;
        }
        else {
            cout << "Ошибка чтения файла" << endl;
        }
        file.close();
    }
};

int main() {
    setlocale(LC_ALL, "RU");

    cout << "Учет студентов\n";
    cout << "1. Добавить студента\n"
         << "2. Вывести список студентов\n"
         << "3. Поиск студента по имени\n"
         << "4. Сохранить данные в файл\n"
         << "5. Загрузить данные из файла\n"
         << "6. Выйти\n\n";

    int action;
    StudentManager manager;

    do {
        string name;
        int age;
        float avg;

        cout << "Выберите операцию (1-6): ";
        cin >> action;

        // очищаем буфер
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (action < 1 || action > 6) {
            cout << "Недопустимое значение" <<  endl;
        }
        switch (action) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.studentsList();
                break;
            case 3:
                manager.searchByName();
                break;
            case 4:
                manager.saveAsFile();
                break;
            case 5:
                manager.readFile();
                break;
        }
    } while (action != 6);
    cout << "До свидания!\n";
    
    return 0;
}