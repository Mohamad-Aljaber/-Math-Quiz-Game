#include <iostream>
#include <cstdlib>
#include <iomanip> // For better formatting

using namespace std;

enum levelQuestion { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum typeOperation { Add = 1, Sub = 2, Mul = 3, Div = 4, Max = 5 };

struct questioninfo {
    int number1 = 0;
    char opTy;
    int number2 = 0;
    int answer = 0;
};

struct RoundInfo {
    short round = 0;
    string questionLevel;
    string operationType;
    int rightAnswer = 0;
    int wrongAnswer = 0;
};

int ReadNumber(string message, int from, int to) {
    int number = 0;
    do {
        cout << message;
        cin >> number;
    } while (number < from || number > to);
    return number;
}

int RandomNumber(int from, int to) {
    return rand() % (to - from + 1) + from;
}

string levelName(levelQuestion name) {
    string arrLevel[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrLevel[name - 1];
}

string operationName(typeOperation opr) {
    string arrTypes[5] = { "Add", "Sub", "Mul", "Div", "Max" };
    return arrTypes[opr - 1];
}

char operationChar(typeOperation p) {
    char arrTypes[4] = { '+', '-', '*', '/' };
    if (p == Max) {
        return arrTypes[RandomNumber(0, 3)];
    }
    return arrTypes[p - 1];
}

int choiceQuestion(levelQuestion lq) {
    switch (lq) {
    case Easy:
        return RandomNumber(1, 10);
    case Med:
        return RandomNumber(10, 100);
    case Hard:
        return RandomNumber(100, 1000);
    case Mix:
        return RandomNumber(1, 1000);
    default:
        return 0;
    }
}

void printQuestion(questioninfo QInfo) {
    cout << "\n   Question: " << QInfo.number1 << " " << QInfo.opTy << " " << QInfo.number2 << " = ?\n";
    cout << "   Your Answer: ";
}

int Result(int n1, int n2, char op) {
    switch (op) {
    case '+': return n1 + n2;
    case '-': return n1 - n2;
    case '*': return n1 * n2;
    case '/': return n1 / n2;
    default: return 0;
    }
}

bool checkAnswer(int correctAnswer, int playerAnswer) {
    return correctAnswer == playerAnswer;
}

void showFeedback(bool isCorrect) {
    if (isCorrect) {
        system("color 2F"); // Green for correct
        cout << "   Correct! :)\n";
    }
    else {
        system("color 4F"); // Red for wrong
        cout << "   Wrong! :(\n";
    }
}

void printFinalResult(RoundInfo RInfo) {
    cout << "\n   ====================================\n";
    cout << "\t\t Final Result\n";
    cout << "   ====================================\n";
    cout << "   Total Questions: " << RInfo.round << "\n";
    cout << "   Question Level: " << RInfo.questionLevel << "\n";
    cout << "   Operation Type: " << RInfo.operationType << "\n";
    cout << "   Right Answers: " << RInfo.rightAnswer << "\n";
    cout << "   Wrong Answers: " << RInfo.wrongAnswer << "\n";
    cout << "   ====================================\n";
}

RoundInfo startPlaying() {
    RoundInfo RInfo;
    questioninfo QInfo;

    RInfo.round = ReadNumber("\n   How many questions do you want to answer? (1-100): ", 1, 100);
    short questionLevel = ReadNumber("\n   Select difficulty level [1] Easy, [2] Medium, [3] Hard, [4] Mix: ", 1, 4);
    short operationType = ReadNumber("\n   Choose operation type [1] Add, [2] Subtract, [3] Multiply, [4] Divide, [5] Random: ", 1, 5);

    RInfo.questionLevel = levelName((levelQuestion)questionLevel);
    RInfo.operationType = operationName((typeOperation)operationType);

    for (int i = 1; i <= RInfo.round; i++) {
        cout << "\n   Question [" << i << "/" << RInfo.round << "]\n";

        QInfo.number1 = choiceQuestion((levelQuestion)questionLevel);
        QInfo.number2 = choiceQuestion((levelQuestion)questionLevel);
        QInfo.opTy = operationChar((typeOperation)operationType);

        printQuestion(QInfo);
        cin >> QInfo.answer;

        int correctAnswer = Result(QInfo.number1, QInfo.number2, QInfo.opTy);
        bool isCorrect = checkAnswer(correctAnswer, QInfo.answer);

        showFeedback(isCorrect);

        if (isCorrect) {
            RInfo.rightAnswer++;
        }
        else {
            RInfo.wrongAnswer++;
        }
    }

    printFinalResult(RInfo);
    return RInfo;
}

void clearScreen() {
    system("cls");
    system("color 0F"); // Reset color
}

void startGame() {
    char playAgain = 'y';

    do {
        clearScreen();
        cout << "\n   Welcome to the Math Quiz Game!\n";
        cout << "   ====================================\n";
        startPlaying();
        cout << "\n   Do you want to play again? (Y/N): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\n   Thank you for playing! Goodbye!\n";
}

int main() {
    srand((unsigned)time(NULL));
    startGame();
    return 0;
}
