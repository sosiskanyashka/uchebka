#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Определение структуры "Электронная книга"
struct Ebook {
    string manufacturer; // Фирма-производитель
    float screenSize;    // Размер экрана (дюймы)
    bool hasBacklight;   // Наличие подсветки экрана
};

// Функция ввода данных о электронной книге из консоли
void inputEbook(Ebook *book) {
    cout << "Введите данные электронной книги:" << endl;

    cout << "Фирма-производитель: ";
    getline(cin >> ws, book->manufacturer); // Используем getline для ввода строк с пробелами

    cout << "Размер экрана (дюймы): ";
    cin >> book->screenSize;
    cin.ignore(); // Очистка буфера ввода после ввода числа

    cout << "Наличие подсветки экрана (1 - да, 0 - нет): ";
    int backlightChoice;
    cin >> backlightChoice;
    cin.ignore();
    book->hasBacklight = (backlightChoice == 1);
}

// Функция вывода информации об электронной книге
void printEbook(const Ebook &book) {
    cout << "Фирма-производитель: " << book.manufacturer << endl;
    cout << "Размер экрана: " << book.screenSize << " дюймов" << endl;
    cout << "Подсветка экрана: " << (book.hasBacklight ? "Да" : "Нет") << endl;
}

// Функция создания динамических экземпляров структуры и сохранения их в векторе
void createEbooksAndAddToVector(vector<Ebook *> &ebooks, int count) {
    for (int i = 0; i < count; ++i) {
        Ebook *newBook = new Ebook; // Динамическое выделение памяти
        inputEbook(newBook);       // Ввод данных для новой книги
        ebooks.push_back(newBook);   // Добавление указателя на книгу в вектор
    }
}

// Функция для освобождения памяти, выделенной под динамические объекты
void freeEbookMemory(vector<Ebook *> &ebooks) {
    for (Ebook *book : ebooks) {
        delete book;
    }
    ebooks.clear();  // Очищаем вектор от указателей, чтобы избежать повторного удаления
}


int main() {
    // Создание двух экземпляров структуры
    Ebook book1, book2;

    // Создание вектора для хранения динамических экземпляров
    vector<Ebook *> ebookVector;

    // Заполнение первых двух экземпляров данными через функцию ввода
    cout << "Введите данные для первой электронной книги:" << endl;
    inputEbook(&book1);

    cout << "Введите данные для второй электронной книги:" << endl;
    inputEbook(&book2);

    // Псевдоменю
    int choice;
    do {
        cout << "\nМеню:" << endl;
        cout << "1. Вывести информацию о первой книге" << endl;
        cout << "2. Вывести информацию о второй книге" << endl;
        cout << "3. Создать и добавить книги в вектор" << endl;
        cout << "4. Вывести информацию о книгах в векторе" << endl;
        cout << "5. Освободить память и очистить вектор (удалить динамические объекты)" << endl;
        cout << "0. Выйти" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "\nИнформация о первой книге:" << endl;
                printEbook(book1);
                break;
            case 2:
                cout << "\nИнформация о второй книге:" << endl;
                printEbook(book2);
                break;
            case 3:
                int numToCreate;
                cout << "Введите количество книг для создания: ";
                cin >> numToCreate;
                cin.ignore();
                createEbooksAndAddToVector(ebookVector, numToCreate);
                cout << "Книги успешно созданы и добавлены в вектор." << endl;
                break;
            case 4:
                cout << "\nИнформация о книгах в векторе:" << endl;
                if (ebookVector.empty()) {
                    cout << "Вектор пуст." << endl;
                } else {
                    for (size_t i = 0; i < ebookVector.size(); ++i) {
                        cout << "Книга " << i + 1 << ":" << endl;
                        printEbook(*ebookVector[i]); // Разыменовываем указатель для доступа к данным
                    }
                }
                break;
            case 5:
                freeEbookMemory(ebookVector);
                cout << "Память освобождена, вектор очищен." << endl;
                break;
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, выберите пункт меню." << endl;
        }
    } while (choice != 0);

    // Освобождение памяти, выделенной под экземпляры структуры, созданные динамически (если не сделано в меню)
    freeEbookMemory(ebookVector);  // Важно: освобождаем память в конце программы

    return 0;
}