#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include "modAlphaCipher.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    try {
        std::wstring key, text;
        
        // Ввод ключа
        std::wcout << L"Введите ключ (русские буквы): ";
        std::getline(std::wcin, key);
        
        // Создание шифратора
        modAlphaCipher cipher(key);
        
        // Ввод текста
        std::wcout << L"Введите текст для шифрования: ";
        std::getline(std::wcin, text);

        std::wcout << L"Исходный текст: " << text << std::endl;
        
        std::wstring encrypted = cipher.encrypt(text);
        std::wcout << L"Зашифрованный текст: " << encrypted << std::endl;
        
        std::wstring decrypted = cipher.decrypt(encrypted);
        std::wcout << L"Расшифрованный текст: " << decrypted << std::endl;
        
    } catch (const cipher_error& e) {
        std::cerr << "Ошибка шифрования: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
