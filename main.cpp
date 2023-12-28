#include <iostream>
#include <fstream>
#include <cctype>
#include <exception>
#include <string>

char* function(char* destination, const char* source1, const char* source2) {
    
    if (!destination || !source1 || !source2) {         // ��������
        throw std::invalid_argument("������ ��������� ������");
    }
    
    while (*source1 != '\0') {          // ������� �� ������ ������
        *destination = *source1;
        ++destination;
        ++source1;
    }
    
    while (*source2 != '\0') {          // ���������� ����� �� ������ ������
        if (std::isdigit(*source2)) {
            *destination = *source2;
            ++destination;
        }
        ++source2;
    }

    *destination = '\0';                // ���������� ������

    return destination;                 // ��������� �� ������ ����������

}

int main() {
    
    setlocale(LC_ALL, "Russian");
    try {
        // �������� ������
        std::ifstream f1("1.txt"); 
        std::ifstream f2("2.txt");
        // ��������        
        if (!f1.is_open() || !f2.is_open()) {                                         
            throw std::runtime_error("������ �������� �����");                         
        }
        // ������
        std::string source2;
        std::string  source1;                                                     
        f1 >> source1;
        f2 >> source2;
        // ��������
        f1.close();                                                                      
        f2.close();
        // ������������ ������ ������
        int maxLen = source1.size() + source2.size();                          
        // ��������� ������
        char* result = new char[maxLen];                                           
        // ����� �������
        char* resultPtr = function(result, source1.c_str(), source2.c_str());      
        // �������� �����
        std::ofstream out("out.txt");                                                   
        // ��������
        if (!out.is_open()) {                                                           
            throw std::runtime_error("������ �������� �����");
        }
        // ����� ����������
        std::cout << result << std::endl ;
        // ������ � ����
        out << result << std::endl;                                                  
        // ��������
        out.close();
        // ������������ ������
        delete[] result;                                                                                  
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
