#include <iostream>
#include <string>
#include <Windows.h> 
#include <algorithm>
#include <time.h>


using namespace std;

const int MAX_PLAYERS = 4;

struct Player {
    string name;
    int score;
};

void displayBoard( string& word, bool* guessed, int length) {
    cout << "_____" << endl;
    cout << "|";
    for (int i = 0; i < length; i++) {
        if (guessed[i]) {
            cout << "!";
        }
        else {
            cout << "|";
        }
        cout << "-";
    }
    cout << "|" << endl;
    cout << "-----" << endl;
}

bool isWordGuessed(const bool* guessed, int length) {
    for (int i = 0; i < length; i++) {
        if (!guessed[i]) {
            return false;
        }
    }
    return true;
}

string chooseWord() {
    string wordList[] = { "ЗСУ", "Украина", "Днепр", "Победа", "Футбол", "Мариуполь", "Оплот", "Мяч", "Дом", "Хаос", "Любовь" };
    int index = rand() % (sizeof(wordList) / sizeof(wordList[0]));
    return wordList[index];
}

void playToScore(Player* players, int numPlayers, int target) {
    const int MAX_WORD_LENGTH = 20;
    bool guessedWord[MAX_WORD_LENGTH];
    string word = chooseWord();

    int wordLength = word.length();
    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = false;
    }

    int currentPlayer = 0;
    while (players[currentPlayer].score < target) {
        displayBoard(word, guessedWord, wordLength);
        cout << "Ходит игрок " << players[currentPlayer].name << "." << endl;
        cout << "Текущий счет: " << players[currentPlayer].score << " очков." << endl;
        cout << "Введите букву: ";
        char guess;
        cin >> guess;

        bool correctGuess = false;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess) {
                if (!guessedWord[i]) {
                    guessedWord[i] = true;
                    correctGuess = true;
                    players[currentPlayer].score += 10;
                }
            }
        }

        if (correctGuess) {
            if (isWordGuessed(guessedWord, wordLength)) {
                players[currentPlayer].score += 100;  
                cout << "Поздравляем! Загаданное слово было \"" << word << "\"." << endl;
                word = chooseWord(); 
                wordLength = word.length(); 
                for (int i = 0; i < wordLength; i++) {
                    guessedWord[i] = false; 
                }
            }
        }
        else {
            players[currentPlayer].score -= 2;  
        }

        currentPlayer = (currentPlayer + 1) % numPlayers;
    }

    cout << "Игрок " << players[currentPlayer].name << ", ваш текущий счет: " << players[currentPlayer].score << " очков." << endl;

    cout << "Финальные счета:" << endl;
    for (int i = 0; i < numPlayers; i++) {
        cout << "Игрок " << players[i].name << ": " << players[i].score << " очков" << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    int numPlayers;
    cout << "Введите количество игроков (1-4): ";
    cin >> numPlayers;

    Player players[MAX_PLAYERS];
    for (int i = 0; i < numPlayers; i++) {
        Player player;
        cout << "Введите имя игрока " << i + 1 << ": ";
        cin >> player.name;
        player.score = 0;
        players[i] = player;
    }

    int gameMode;
    cout << "Выберите режим игры:" << endl;
    cout << "1. Кто первый дойдет до 1000" << endl;
    cout << "2. Кто первый угадает слово полностью" << endl;
    cout << "Ваш выбор: ";
    cin >> gameMode;

    if (gameMode == 1) {
        playToScore(players, numPlayers, 1000);
    }
    else if (gameMode == 2) {
        int totalLetters = 25;
        playToScore(players, numPlayers, totalLetters);
    }
    else {
        cout << "Некорректный выбор режима игры." << endl;
    }

    return 0;
}