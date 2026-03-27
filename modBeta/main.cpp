#include <iostream>
#include <limits>
#include "routeCipher.h"

// Функция для безопасного ввода числа
int getValidIntegerInput() {
    int value;
    while (true) {
        std::cin >> value;
        
        if (std::cin.fail()) {
            // Если ввод не является числом
            std::cin.clear(); // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
            std::cout << "Ошибка: введите целое число: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер после успешного ввода
            break;
        }
    }
    return value;
}

int main()
{
    try {
        int key;
        std::string text;
        
        // Ввод ключа с проверкой
        std::cout << "Введите ключ (число столбцов): ";
        key = getValidIntegerInput();
        
        // Создание шифратора (здесь может выброситься исключение для отрицательных ключей)
        RouteCipher cipher(key);

        int op;
        // Главный цикл программы
        do {
            std::cout << "Операция (0-выход, 1-шифровать, 2-расшифровать): ";
            
            // Проверяем корректность ввода операции
            while (!(std::cin >> op) || (op != 0 && op != 1 && op != 2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: введите 0, 1 или 2: ";
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
            
            if (op == 1 || op == 2) {
                // Ввод текста
                std::cout << "Введите текст: ";
                std::getline(std::cin, text);
                
                try {
                    if (op == 1) {
                        std::cout << "Зашифрованный текст: " << cipher.encrypt(text) << std::endl;
                    } else {
                        std::cout << "Расшифрованный текст: " << cipher.decrypt(text) << std::endl;
                    }
                } catch (const cipher_error& e) {
                    std::cerr << "Ошибка шифрования: " << e.what() << std::endl;
                }
            }
        } while (op != 0);
        
    } catch (const cipher_error& e) {
        std::cerr << "Ошибка инициализации: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
