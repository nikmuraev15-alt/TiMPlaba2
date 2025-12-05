#include <iostream>
#include <string>
#include <locale>
#include "RouteCipher.h"

using namespace std;

void ShowMenu() {
    wcout << L"\n=== Шифр Маршрутной Перестановки ===" << endl;
    wcout << L"1. Зашифровать текст" << endl;
    wcout << L"2. Расшифровать текст" << endl;
    wcout << L"3. Выйти" << endl;
    wcout << L"Выберите операцию: ";
}
void TestGronsfeldCases() {
    wcout << L"\n=== Тестирование обработки исключений для шифра Гронсфельда ===" << endl;
    try {
        RouteCipher cipher(4);
        wstring result = cipher.Encrypt(L"ПРИВЕТ");
        wcout << L"ТЕСТ 1 ПРОЙДЕН" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 1 ПРОЙДЕН: Ожидалось нормальное выполнение " << e.what() << endl;
    }
    try {
        RouteCipher cipher(2);
        wstring result = cipher.Encrypt(L"123456");
        wcout << L"ТЕСТ 2 НЕ ПРОЙДЕН: Ожидалось исключение для текста без букв" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 2 ПРОЙДЕН " << e.what() << endl;
    }
    try {
        RouteCipher cipher(3);
        wstring result = cipher.Decrypt(L"АБВ123");
        wcout << L"ТЕСТ 3 НЕ ПРОЙДЕН: Ожидалось исключение для шифротекста с цифрами" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 3 ПРОЙДЕН " << e.what() << endl;
    }
    try {
        RouteCipher cipher(4);
        wstring result = cipher.Decrypt(L"АБВ ГДЕ");
        wcout << L"ТЕСТ 4 НЕ ПРОЙДЕН: Ожидалось исключение для шифротекста с пробелами" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 4 ПРОЙДЕН " << e.what() << endl;
    }
    try {
        RouteCipher cipher(3);
        wstring original = L"ШИФРОВАНИЕ";
        wstring encrypted = cipher.Encrypt(original);
        wstring decrypted = cipher.Decrypt(encrypted);
        if (decrypted == L"ШИФРОВАНИЕ") {
            wcout << L"ТЕСТ 5 ПРОЙДЕН" << endl;
            wcout << L"Исходный: " << original << L" -> Зашифрованный: " << encrypted << L" -> Расшифрованный: " << decrypted << endl;
        } else {
            wcout << L"ТЕСТ 5 НЕ ПРОЙДЕН: Неправильное дешифрование" << endl;
        }
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 5 НЕ ПРОЙДЕН: " << e.what() << endl;
    }
}

void TestCases() {
    wcout << L"\n=== Тестирование обработки исключений ===" << endl;
    
    try {
        RouteCipher cipher(-5);
        wcout << L"ТЕСТ 1 НЕ ПРОЙДЕН: Ожидалось исключение для отрицательного ключа" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 1 ПРОЙДЕН " << e.what() << endl;
    }
    try {
        RouteCipher cipher(0);
        wcout << L"ТЕСТ 2 НЕ ПРОЙДЕН: Ожидалось исключение для ключа = 0" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 2 ПРОЙДЕН " << e.what() << endl;
    }
    try {
        RouteCipher cipher(3);
        wstring result = cipher.Encrypt(L"");
        wcout << L"ТЕСТ 3 НЕ ПРОЙДЕН: Ожидалось исключение для пустого текста" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 3 ПРОЙДЕН " << e.what() << endl;
    }
    try {
        RouteCipher cipher(3);
        wstring result = cipher.Encrypt(L"  ,.! 123 ");
        wcout << L"ТЕСТ 4 НЕ ПРОЙДЕН: Ожидалось исключение для текста без букв" << endl;
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 4 ПРОЙДЕН " << e.what() << endl;
    }
    try {
        RouteCipher cipher(3);
        wstring original = L"ПРИВЕТМИР";
        wstring encrypted = cipher.Encrypt(original);
        wstring decrypted = cipher.Decrypt(encrypted);
        if (decrypted == L"ПРИВЕТМИР") {
            wcout << L"ТЕСТ 5 ПРОЙДЕН" << endl;
            wcout << L"Исходный: " << original << L" -> Зашифрованный: " << encrypted << L" -> Расшифрованный: " << decrypted << endl;
        } else {
            wcout << L"ТЕСТ 5 НЕ ПРОЙДЕН: Неправильное дешифрование" << endl;
        }
    } catch (const CipherError& e) {
        wcout << L"ТЕСТ 5 НЕ ПРОЙДЕН: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    wcout << L"=== Система Шифрования Маршрутной Перестановки ===" << endl;
    wcout << L"Автоматически удаляются: пробелы, знаки препинания, цифры" << endl;

    TestGronsfeldCases();    
    TestCases();

    
    try {
        int Key;
        wcout << L"\nВведите ключ (количество столбцов): ";
        wcin >> Key;
        wcin.ignore();
        
        RouteCipher Cipher(Key);
        wcout << L"Шифр инициализирован с ключом: " << Key << endl;
        
        int Choice;
        wstring Text;
        
        do {
            ShowMenu();
            wcin >> Choice;
            wcin.ignore();
            
            switch (Choice) {
                case 1: {
                    wcout << L"Введите текст для шифрования: ";
                    getline(wcin, Text);
                    
                    try {
                        wstring Encrypted = Cipher.Encrypt(Text);
                        wcout << L"Зашифрованный текст: " << Encrypted << endl;
                    } catch (const CipherError& e) {
                        wcout << L"Ошибка при шифровании: " << e.what() << endl;
                    }
                    break;
                }
                case 2: {
                    wcout << L"Введите текст для расшифрования: ";
                    getline(wcin, Text);
                    
                    try {
                        wstring Decrypted = Cipher.Decrypt(Text);
                        wcout << L"Расшифрованный текст: " << Decrypted << endl;
                    } catch (const CipherError& e) {
                        wcout << L"Ошибка при расшифровании: " << e.what() << endl;
                    }
                    break;
                }
                case 3:
                    wcout << L"Выход из программы." << endl;
                    break;
                default:
                    wcout << L"Неверный выбор. Попробуйте снова." << endl;
            }
        } while (Choice != 3);
        
    } catch (const CipherError& e) {
        wcout << L"Ошибка инициализации шифра: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        wcout << L"Неожиданная ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
