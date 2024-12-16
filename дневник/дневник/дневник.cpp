#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <Windows.h>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

vector<string> readFramesFromFile(const string& filename, const string& delimiter) {
    vector<string> frames;
    ifstream file(filename);

    if (!file) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return frames;
    }

    string line, frame;
    while (getline(file, line)) {
        if (line == delimiter) {
            if (!frame.empty()) {
                frames.push_back(frame);
                frame.clear();
            }
        }
        else {
            frame += line + "\n";
        }
    }
    if (!frame.empty()) {
        frames.push_back(frame);
    }

    return frames;
}

void animate(const vector<string>& frames) {
    const int numFrames = frames.size();
    for (int i = 0; i < numFrames; ++i) {
        clearScreen();
        cout << frames[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int randomInt(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

void play_animation(vector<string>& frames1, vector<string>& frames2,vector<string>& frames3) {
    int random_number = randomInt(0, 100);
    if (random_number % 3 == 0)
    {
        animate(frames1);
    }
    else if (random_number % 3 == 0) {
        animate(frames2);
    }
    else {
        animate(frames3);
    }
}

void getFileContents(const std::string& filename, std::string& fileContents) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    std::ostringstream oss;
    oss << file.rdbuf();
    fileContents = oss.str();
    file.close();
}

void saveToFile(const std::string& filename, const std::string& newContent) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    file << newContent;
    file.close();
}

void diary() {
    std::string input;
    std::string content;
    getFileContents("today_dairy.txt", content);
    while (true) {
        std::cout << content;
        std::cout << "Введите что-нибудь";
        std::getline(std::cin, input);
        if (input == "end") {
            saveToFile("today_diary.txt", content);
            break;
        }
        content += input;
        clearScreen();
    }
}

int main() {
    setlocale(0, "ru");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    string filename1 = "for.txt";
    string delimiter1 = ",";
    vector<string> frames1 = readFramesFromFile(filename1, delimiter1);

    string filename2 = "tytyty.txt";
    string delimiter2 = "?";
    vector<string> frames2 = readFramesFromFile(filename2, delimiter2);
     
    string filename3 = "go.txt";
    string delimiter3 = "r";
    vector<string> frames3 = readFramesFromFile(filename3, delimiter3);

    if (!frames1.empty() && !frames3.empty()) {
        std::string input = "";
        while (true) {
            std::cout << "Введите что угодно\n";
            std::getline(std::cin, input);
            if (input == "exit")
            {
                break;
            }
            if (input == "animation") {
                play_animation(frames1, frames2, frames3);
            }
            if (input == "Hello")
            {
                std::cout << "Hey baby? i am I-i-igor\n";
            }
            if (input == "Что ты умеешь")
            {
                std::cout << "Много чего\n";
            }
            if (input == "How are you")
            {
                std::cout << "Hey there beautiful, how is your day ?\n";
            }
            if (input == "Who are you" or input=="who are you")
            {
                std::cout << "1. Ввести задачи дня\n";
                std::cout << "2. Поиск соответствующих задач\n";
                std::cout << "3. Просмотр всех задач\n";
                std::cout << "4. Блокнот\n";
                std::cout << "5. Показ анимации\n";
            }
        }
    }
    else {
        cout << "Нет кадров для анимации." << endl;
    }




    return 0;
}
