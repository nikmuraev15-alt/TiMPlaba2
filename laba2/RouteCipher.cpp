#include "RouteCipher.h"
#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>

RouteCipher::RouteCipher(int Key) {
    Columns = GetValidKey(std::to_string(Key));
}

void RouteCipher::ValidateKey(int Key) {
    if (Key <= 0) {
        throw CipherError("Ключ должен быть положительным числом");
    }
    if (Key > 50) {
        throw CipherError("Слишком большой ключ");
    }
}

void RouteCipher::ValidateText(const std::wstring& Text) {
    if (Text.empty()) {
        throw CipherError("Текст не может быть пустым");
    }
}

int RouteCipher::GetValidKey(const std::string& Key) {
    if (Key.empty()) {
        throw CipherError("Пустой ключ");
    }
    
    for (auto c : Key) {
        if (!isdigit(c)) {
            throw CipherError("Ключ должен содержать только цифры");
        }
    }
    
    int keyValue = std::stoi(Key);
    ValidateKey(keyValue);
    return keyValue;
}

int RouteCipher::GetValidKey(const std::wstring& Key) {
    if (Key.empty()) {
        throw CipherError("Пустой ключ");
    }
    
    for (auto c : Key) {
        if (!iswdigit(c)) {
            throw CipherError("Ключ должен содержать только цифры");
        }
    }
    
    std::string keyStr(Key.begin(), Key.end());
    int keyValue = std::stoi(keyStr);
    ValidateKey(keyValue);
    return keyValue;
}

std::wstring RouteCipher::GetValidOpenText(const std::wstring& Text) {
    if (Text.empty()) {
        throw CipherError("Пустой открытый текст");
    }
    
    std::wstring result;
    for (auto c : Text) {
        if (iswalpha(c) || iswspace(c) || iswpunct(c) || iswdigit(c)) {
            result += c;
        } else {
            throw CipherError("Открытый текст содержит недопустимые символы");
        }
    }
    
    std::wstring cleaned = RemoveSpacesAndPunctuation(result);
    if (cleaned.empty()) {
        throw CipherError("После удаления пробелов и знаков препинания текст пуст");
    }
    
    return result;
}

std::wstring RouteCipher::GetValidCipherText(const std::wstring& Text) {
    if (Text.empty()) {
        throw CipherError("Пустой зашифрованный текст");
    }
    
    for (auto c : Text) {
        if (!iswalpha(c)) {
            throw CipherError("Зашифрованный текст должен содержать только буквы");
        }
    }
    
    return Text;
}

std::wstring RouteCipher::RemoveSpacesAndPunctuation(const std::wstring& Text) {
    std::wstring Result;
    for (wchar_t c : Text) {
        if (!std::iswspace(c) && !std::iswpunct(c) && !std::iswdigit(c)) {
            Result += c;
        }
    }
    return Result;
}

std::wstring RouteCipher::ToUpperCase(const std::wstring& Text) {
    std::wstring Result = Text;
    std::locale loc("ru_RU.UTF-8");
    for (wchar_t& c : Result) {
        c = std::toupper(c, loc);
    }
    return Result;
}

std::wstring RouteCipher::PrepareText(const std::wstring& Text) {
    std::wstring Cleaned = RemoveSpacesAndPunctuation(Text);
    if (Cleaned.empty()) {
        throw CipherError("После удаления пробелов и знаков препинания текст пуст");
    }
    return ToUpperCase(Cleaned);
}

std::wstring RouteCipher::Encrypt(const std::wstring& Text) {
    std::wstring validText = GetValidOpenText(Text);
    std::wstring PreparedText = PrepareText(validText);
    
    int TextLength = PreparedText.length();
    int Rows = (TextLength + Columns - 1) / Columns;
    
    std::vector<std::vector<wchar_t>> Table(Rows, std::vector<wchar_t>(Columns));
    
    int index = 0;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            if (index < TextLength) {
                Table[i][j] = PreparedText[index++];
            } else {
                Table[i][j] = L'X';
            }
        }
    }
    
    std::wstring Result;
    for (int j = Columns - 1; j >= 0; j--) {
        for (int i = 0; i < Rows; i++) {
            Result += Table[i][j];
        }
    }
    
    return Result;
}

std::wstring RouteCipher::Decrypt(const std::wstring& Text) {
    std::wstring validText = GetValidCipherText(Text);
    std::wstring PreparedText = ToUpperCase(validText);
    
    int TextLength = PreparedText.length();
    int Rows = (TextLength + Columns - 1) / Columns;
    
    std::vector<std::vector<wchar_t>> Table(Rows, std::vector<wchar_t>(Columns));
    
    int index = 0;
    for (int j = Columns - 1; j >= 0; j--) {
        for (int i = 0; i < Rows; i++) {
            if (index < TextLength) {
                Table[i][j] = PreparedText[index++];
            } else {
                Table[i][j] = L'X';
            }
        }
    }
    
    std::wstring Result;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            Result += Table[i][j];
        }
    }
    
    while (!Result.empty() && Result.back() == L'X') {
        Result.pop_back();
    }
    
    return Result;
}
