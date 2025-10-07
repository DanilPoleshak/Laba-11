#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

class ATS
{
private:
    string address;
    int subscribers;
    double subscriptionFee;

public:
    ATS(string addr, int subs, double fee) {
        setAddress(addr);
        setSubscribers(subs);
        setSubscriptionFee(fee);
    }

    void setAddress(const string& addr) {
        address = addr;
    }

    void setSubscribers(int subs) {
        subscribers = subs;
    }

    void setSubscriptionFee(double fee) {
        subscriptionFee = fee;
    }

    string getAddress() const { return address; }
    int getSubscribers() const { return subscribers; }
    double getSubscriptionFee() const { return subscriptionFee; }

    double totalFee() const {
        return static_cast<double>(subscribers) * subscriptionFee;
    }

    // Метод для форматирования чисел с разделителями тысяч
    string formatNumber(double number) const {
        string numStr = to_string(static_cast<long long>(number));
        string result = "";
        int count = 0;

        for (int i = numStr.length() - 1; i >= 0; i--) {
            result = numStr[i] + result;
            count++;
            if (count % 3 == 0 && i > 0) {
                result = " " + result;
            }
        }
        return result;
    }

    void displayInfo() const {
        cout << "\n--- Итоговые данные АТС ---\n";
        cout << "Адрес: " << address << endl;
        cout << "Количество абонентов: " << formatNumber(subscribers) << endl;
        cout << "Абонентская плата: " << subscriptionFee << " руб.\n";
        cout << "Итоговая общая абонентская плата: " << formatNumber(totalFee()) << " руб.\n";
    }
};

int safeInputSubscribers() {
    int subscribers;

    while (true) {
        cout << "Введите количество абонентов (1-1000000): ";

        
        if (!(cin >> subscribers)) {
            cout << "Ошибка: введите целое число, и не текст!\n";
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); 
            continue;
        }

        
        if (subscribers <= 0) {
            cout << "Ошибка: количество абонентов должно быть положительным числом!\n";
        }
        else if (subscribers > 1000000) {
            cout << "Ошибка: слишком большое число! Максимум 1 000 000 абонентов.\n";
        }
        else {
            break; 
        }

        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }

    return subscribers;
}


double safeInputFee() {
    double fee;

    while (true) {
        cout << "Введите абонентскую плату: ";

        
        if (!(cin >> fee)) {
            cout << "Ошибка: введите число, и не текст!\n";
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            continue;
        }

        
        if (fee <= 0.1) {
            cout << "Ошибка: абонентская плата должна быть положительной!\n";
        }
        else if (fee > 100000) {
            cout << "Ошибка: слишком большая абонентская плата! Максимум 100 000 руб.\n";
        }
        else {
            break;
        }

      
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }

    return fee;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    string address;
    int subscribers;
    double fee;

    cout << "Введите адрес АТС: ";
    getline(cin, address);

   
    subscribers = safeInputSubscribers();

  
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    fee = safeInputFee();

    ATS ats(address, subscribers, fee);
    ats.displayInfo();

    return 0;
}