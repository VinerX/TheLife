// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random>
#include "windows.h"
#include <ctime>

//Константы, чем больше, тем дольше времени уйдет на просчет логики.

const int Heigh = 25;
const int Weigh = 25;
const int HistorySize = 10; // Как далеко доходи проверка на повторение

int lifeCount = 0;

//Рандом в диапозоне
int random(int start, int end) {
    return (rand() % (end - start + 1) + start);
}
//50% шанс что вернет тру
bool randomB(void) { //50%
    if (random(1, 2) == 1)
        return true;
    else
        return false;
}

// Делает все false в массиве или с шансом 50% ставит true
void initArea(bool Area[Heigh][Weigh], bool withRandom) {
    for (int i = 0; i < Heigh; i++) {
        for (int j = 0; j < Weigh; j++) {
            if (withRandom and randomB()) {
                Area[i][j] = true;
                lifeCount += 1;
            }
            else
                Area[i][j] = false;

        }
    }
}

//Графический вывод
void printArea(bool Area[Heigh][Weigh]) {
    for (int i = 0; i < Heigh; i++) {
        for (int j = 0; j < Weigh; j++) {
            if (Area[i][j]) 
                std::cout << "+ ";
            else 
                std::cout << "# ";

        }
        std::cout << std::endl;
    }
    //std::cout << std::endl;
}

//Безопасная строка
int tR(int row) {
    if (row >= Heigh)
        return row - Heigh;
    else if (row < 0)
        return Heigh + row;
    else return row;
}
//Безопасный столбец
int tC(int column) {
    if (column >= Weigh)
        return column - Weigh;
    else if (column < 0)
        return Weigh + column;
    else return column;
}

//Просчитывает логику и выводит следующее поколение на второй (пустой) массив)
void turnSumulate(bool Area[Heigh][Weigh], bool NextArea[Heigh][Weigh]) {
    for (int row = 0; row < Heigh; row++) {
        for (int column = 0; column < Weigh; column++) {
            int life = 0;
            //Считаем жизнь рядом
            //Верхние
            if (Area[tR(row - 1)][tC(column - 1)])
                life += 1;
            if (Area[tR(row - 1)][tC(column)])
                life += 1;
            if (Area[tR(row - 1)][tC(column + 1)])
                life += 1;
            //Боковые
            if (Area[tR(row)][tC(column - 1)])
                life += 1;
            if (Area[tR(row)][tC(column + 1)])
                life += 1;
            //Нижние
            if (Area[tR(row + 1)][tC(column - 1)])
                life += 1;
            if (Area[tR(row + 1)][tC(column)])
                life += 1;
            if (Area[tR(row + 1)][tC(column + 1)])
                life += 1;


            //std::cout << life << " ";

            //Живая
            if (Area[row][column]) {
                if (life < 2 or life>3) {
                    NextArea[row][column] = false;
                    lifeCount--;// Смерть
                    //std::cout << "0 ";
                    //std::cout << life << " " << row << " " << column << std::endl;
                }
                else {
                    NextArea[row][column] = true;
                    //lifeCount++;
                    //std::cout << "+ ";
                }

            }
            //Мертвая
            else {
                if (life == 3) {
                    NextArea[row][column] = true;
                    lifeCount++;//Жизнь
                    //std::cout << "+ ";
                    //std::cout << tR(row + 1) << " " << tC(column - 1) << std::endl;
                }
                else {
                    NextArea[row][column] = false;
                    //lifeCount--;
                    //std::cout << "0 ";
                }

            }

        }

    }
    std::cout << "Life points: " << lifeCount << std::endl;
}

//Копирует значения из второго массива в первый
void copyArea(bool Area[Heigh][Weigh], bool NextArea[Heigh][Weigh]) {
    for (int i = 0; i < Heigh; i++) {
        for (int j = 0; j < Weigh; j++) {
            Area[i][j] = NextArea[i][j];

        }
    }
}
//Если находит различие в массивах возвращает фалс, иначе тру
bool areAreasEqual(bool Area[Heigh][Weigh], bool NextArea[Heigh][Weigh]) {
    for (int i = 0; i < Heigh; i++) {
        for (int j = 0; j < Weigh; j++) {
            if (Area[i][j] != NextArea[i][j])
                return false;

        }
    }
    return true;
}

//Проверяет, совпадает ли зона с одной их истории
int isSameHistory(bool Area[Heigh][Weigh], bool History[HistorySize][Heigh][Weigh]){
    for (int i = 0; i < HistorySize; i++) {
        if (areAreasEqual(Area, History[i])) {
            return i;
        }
    }
    return -1;
}


//Планер для теста
void figurePlaner(bool Area[Heigh][Weigh], int row, int column) {
    
    Area[tR(row)][tC(column-1)] = true;
    Area[tR(row)][tC(column)] = true;
    Area[tR(row)][tC(column+1)] = true;

    Area[tR(row-1)][tC(column+1)] = true;
    Area[tR(row-2)][tC(column)] = true;
    lifeCount += 5;
}

//Функция игры
void lifeGame(bool randomize, bool newRandom, int turnTime) {
    lifeCount = 0;
    if (newRandom)
        srand(time(0));
    
    bool Area[Heigh][Weigh];
    bool NextArea[Heigh][Weigh];
    bool History[HistorySize][Heigh][Weigh];


    //Заполняю нулями все массивы
    if (randomize)
        initArea(Area, true);
    else
        initArea(Area, false);

    initArea(NextArea, false);
    for (int i = 0; i < HistorySize; i++) {
        initArea(History[i], false);
    }
    
    //Для теста можно было и в ручную прописывать точки
    //Area[1][1] = true;
    //lifeCount++;
    //Area[2][1] = true;
    //Area[3][1] = true;
    //figurePlaner(Area, 5, 5);

    int time = 0;
    while (true) {

        //Основная логика
        system("cls");
        std::cout << "Generation: " << time << std::endl;
        printArea(Area);
        turnSumulate(Area, NextArea);
        for (int i = HistorySize - 1; i > 0; i--) {
            copyArea(History[i], History[i - 1]);
        }
        copyArea(History[0], Area);
        copyArea(Area, NextArea);
        initArea(NextArea, false);


        //Сценарии выхода
        
        //Если нет жизни
        if (lifeCount <= 0) {
            std::cout << std::endl << "Generation: " << time+1<< std::endl;
            printArea(Area);
            std::cout << "End of life." << std::endl;
            break;
        }
        //Повтор в указанной глубине
        int hint = isSameHistory(Area, History);
        if (hint > 0) {
            std::cout << std::endl << "Generation: " << time - (hint+1) << std::endl;
            printArea(History[hint-1]);
            std::cout << std::endl  << "Repeat, depth: " << hint+1 <<"."<< std::endl;
            break;
        }
        //Лишь шаг назад
        else if (hint == 0) {
            std::cout << std::endl << "Generation: " << time - (hint + 1) << std::endl;
            printArea(History[hint]);
            std::cout << std::endl << "Stable situation."<< std::endl;
            break;
        }

        time++;
        Sleep(turnTime);

    }
}




int main()
{
    
    while (true) {
        
        short choice;
        std::cout << "Enter 1 to play, 0 to exit" << std::endl;
        std::cin >> choice;
        system("cls");
        if (choice == 1)
            lifeGame(true, true, 1);
        else
            break;
        
    }
    
    

    
}

