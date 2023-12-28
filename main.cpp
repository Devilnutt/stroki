#include <iostream>
#include <fstream>
#include <cctype>
#include <exception>
#include <string>

char* function(char* destination, const char* source1, const char* source2) {
    
    if (!destination || !source1 || !source2) {         // проверка
        throw std::invalid_argument("Ошибка обработки данных");
    }
    
    while (*source1 != '\0') {          // символы из первой строки
        *destination = *source1;
        ++destination;
        ++source1;
    }
    
    while (*source2 != '\0') {          // десятичные цифры из второй строки
        if (std::isdigit(*source2)) {
            *destination = *source2;
            ++destination;
        }
        ++source2;
    }

    *destination = '\0';                // завершение строки

    return destination;                 // указатель на начало результата

}

int main() {
    
    setlocale(LC_ALL, "Russian");
    try {
        // открытие файлов
        std::ifstream f1("1.txt"); 
        std::ifstream f2("2.txt");
        // проверка        
        if (!f1.is_open() || !f2.is_open()) {                                         
            throw std::runtime_error("Ошибка открытия файла");                         
        }
        // чтение
        std::string source2;
        std::string  source1;                                                     
        f1 >> source1;
        f2 >> source2;
        // закрытие
        f1.close();                                                                      
        f2.close();
        // максимальный размер строки
        int maxLen = source1.size() + source2.size();                          
        // выделение памяти
        char* result = new char[maxLen];                                           
        // вызов функции
        char* resultPtr = function(result, source1.c_str(), source2.c_str());      
        // открытие файла
        std::ofstream out("out.txt");                                                   
        // проверка
        if (!out.is_open()) {                                                           
            throw std::runtime_error("Ошибка открытия файла");
        }
        // вывод результата
        std::cout << result << std::endl ;
        // запись в файл
        out << result << std::endl;                                                  
        // закрытие
        out.close();
        // освобождение памяти
        delete[] result;                                                                                  
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
