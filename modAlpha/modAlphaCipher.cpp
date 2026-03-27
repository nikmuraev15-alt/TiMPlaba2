#include "modAlphaCipher.h"
#include <iostream>
#include <cwctype>

// Конструктор
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

// Шифрование
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

// Дешифрование
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

// Преобразование строка -> вектор
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

// Преобразование вектор -> строка
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

// Валидация ключа - ТОЛЬКО русские буквы
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            wchar_t upper_c = towupper(c);
            // Проверяем, что символ есть в русском алфавите
            if (alphaNum.find(upper_c) != alphaNum.end()) {
                tmp.push_back(upper_c);
            } else {
                throw cipher_error("Ключ содержит не русские буквы");
            }
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Ключ не содержит русских букв");
    }
    
    return tmp;
}

// Валидация открытого текста - ТОЛЬКО русские буквы
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            wchar_t upper_c = towupper(c);
            // Проверяем, что символ есть в русском алфавите
            if (alphaNum.find(upper_c) != alphaNum.end()) {
                tmp.push_back(upper_c);
            } else {
                throw cipher_error("Текст содержит не русские буквы");
            }
        } else if (!iswspace(c)) {
            // Игнорируем пробелы, но бросаем исключение для других символов
            throw cipher_error("Текст содержит недопустимые символы (только русские буквы и пробелы)");
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Текст не содержит русских букв");
    }
    
    return tmp;
}

// Валидация шифротекста - ТОЛЬКО русские буквы
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой шифротекст");
    }
    
    for (auto c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            throw cipher_error("Шифротекст содержит недопустимые символы");
        }
    }
    
    return s;
}
