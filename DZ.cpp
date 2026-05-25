#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

class String {
private:
    char* str;
    size_t length;
    static int objectCount;

public:
    String() {
        length = 80;
        str = new char[length + 1];
        str[0] = '\0';
        objectCount++;
    }

    String(size_t size) {
        length = size;
        str = new char[length + 1];
        str[0] = '\0';
        objectCount++;
    }

    String(const char* userStr) {
        if (userStr) {
            length = std::strlen(userStr);
            str = new char[length + 1];
            std::strcpy(str, userStr);
        }
        else {
            length = 0;
            str = new char[1];
            str[0] = '\0';
        }
        objectCount++;
    }

    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        std::strcpy(str, other.str);
        objectCount++;
    }

    ~String() {
        delete[] str;
        objectCount--;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            std::strcpy(str, other.str);
        }
        return *this;
    }

    void input() {
        std::string temp;
        std::getline(std::cin, temp);
        delete[] str;
        length = temp.length();
        str = new char[length + 1];
        std::strcpy(str, temp.c_str());
    }

    void print() const {
        std::cout << str;
    }

    String concat(const String& obj) const {
        size_t newLength = std::strlen(this->str) + std::strlen(obj.str);
        char* tempBuf = new char[newLength + 1];
        std::strcpy(tempBuf, this->str);
        std::strcat(tempBuf, obj.str);

        String result(tempBuf);
        delete[] tempBuf;
        return result;
    }

    String intersection(const String& obj) const {
        std::string resStr = "";
        bool visited[256] = { false };

        for (size_t i = 0; this->str[i] != '\0'; ++i) {
            char ch = this->str[i];
            if (!visited[static_cast<unsigned char>(ch)]) {
                for (size_t j = 0; obj.str[j] != '\0'; ++j) {
                    if (ch == obj.str[j]) {
                        resStr += ch;
                        visited[static_cast<unsigned char>(ch)] = true;
                        break;
                    }
                }
            }
        }

        return String(resStr.c_str());
    }

    static int getObjectCount() {
        return objectCount;
    }

    static int compare(const String& s1, const String& s2) {
        int res = std::strcmp(s1.str, s2.str);
        if (res == 0) return 0;
        if (res > 0) return 1;
        return -1;
    }

    static void sort(String arr[], size_t size) {
        for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = 0; j < size - i - 1; ++j) {
                if (compare(arr[j], arr[j + 1]) == 1) {
                    String temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
};

int String::objectCount = 0;

int main() {
    std::cout << "Objects count: " << String::getObjectCount() << "\n";

    String s1("Program");
    String s2(" C++");
    std::cout << "Objects count: " << String::getObjectCount() << "\n";

    String s3 = s1.concat(s2);
    std::cout << "Concat result: "; s3.print(); std::cout << "\n";

    String s4("programming");
    String s5("language");
    String s6 = s4.intersection(s5);
    std::cout << "Intersection result: "; s6.print(); std::cout << "\n";

    std::cout << "Compare s1 and s4: " << String::compare(s1, s4) << "\n";

    std::cout << "Enter custom string: ";
    String s7;
    s7.input();
    std::cout << "You entered: "; s7.print(); std::cout << "\n";

    const size_t arrSize = 4;
    String arr[arrSize] = { String("Banana"), String("Apple"), String("Orange"), String("Apricot") };

    std::cout << "Array before sorting:\n";
    for (size_t i = 0; i < arrSize; ++i) {
        arr[i].print(); std::cout << " ";
    }
    std::cout << "\n";

    String::sort(arr, arrSize);

    std::cout << "Array after sorting:\n";
    for (size_t i = 0; i < arrSize; ++i) {
        arr[i].print(); std::cout << " ";
    }
    std::cout << "\n";

    std::cout << "Final objects count: " << String::getObjectCount() << "\n";

    return 0;
}