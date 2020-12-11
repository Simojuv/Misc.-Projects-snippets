#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <conio.h>
#include <fstream>

struct database
{
    std::map<std::string,std::vector<std::string>> dataMap;
    std::vector<std::string> Position;
    std::vector<std::string> Department;
};

struct textCoordinates
{
    COORD startTextPos;
    COORD endTextPos;
};

struct consoleInfo
{
    HANDLE handle;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
};

void initDatabase(database& data)
{
    std::vector<std::string> names;
    std::vector<std::string> surname;
    std::vector<std::string> gender;
    std::vector<std::string> position;
    std::vector<std::string> department;
    std::vector<std::string> birthday;
    std::vector<std::string> telephone;
    std::vector<std::string> salary;

    data.dataMap["Name"] = names;
    data.dataMap["Surname"] = surname;
    data.dataMap["Gender"] = gender;
    data.dataMap["Position"] = position;
    data.dataMap["Department"] = department;
    data.dataMap["Birthday"] = birthday;
    data.dataMap["Telephone"] = telephone;
    data.dataMap["Salary"] = salary;

    data.Position.push_back("Mechanical Engineer");
    data.Position.push_back("Software Engineer");
    data.Position.push_back("Electrical Engineer");
    data.Position.push_back("Salesman");
    data.Position.push_back("Product Manager");
    data.Position.push_back("Project Manager");

    data.Department.push_back("Development");
    data.Department.push_back("Production");
    data.Department.push_back("Marketing");
    data.Department.push_back("Sales");
    data.Department.push_back("Human resources");
    data.Department.push_back("Administration");
}

std::string getKey()
{

    int pressedKey = _getch();
    if(pressedKey == 224)
    {
        int temp = _getch();
        if(temp == 72) return "Up";
        else if(temp == 75) return "Left";
        else if(temp == 77) return "Right";
        else if(temp == 80) return "Down";
    }
    else if(pressedKey == 13) return "Confirm";
    else if(pressedKey == 110) return "Newline";
    else if(pressedKey == 115) return "Save";
    else if(pressedKey == 114) return "Remove";
    else if(pressedKey == 27) return "Exit";
    return "";
}

std::string chooseGender(consoleInfo& console)
{
    COORD cursorPosition = console.csbi.dwCursorPosition;
    SetConsoleTextAttribute(console.handle,(BACKGROUND_BLUE|BACKGROUND_GREEN));
    std::cout << "\b:";
    SetConsoleTextAttribute(console.handle,15);
    std::string currentOption = "M";
    while(1)
    {
        std::string choice = getKey();
        if(choice == "Left" || choice == "Right")
        {
            if (currentOption == "M") currentOption = "F";
            else if (currentOption == "F") currentOption = "M";
        }
        else if(choice == "Confirm")
        {
            std::cout << "\b ";
            return currentOption;
        }
        std::cout << currentOption;
        SetConsoleCursorPosition(console.handle,cursorPosition);
    }
    return "Error";
}

std::string choosePosition(database& data,consoleInfo& console)
{
    unsigned int tempChoice = 0;
    COORD cursorPosition = console.csbi.dwCursorPosition;
    std::string currentOption = data.Position.at(tempChoice);
    SetConsoleTextAttribute(console.handle,(BACKGROUND_BLUE|BACKGROUND_GREEN));
    std::cout << "\b:";
    SetConsoleTextAttribute(console.handle,15);
    std::cout << data.Position.at(tempChoice);
    while(1)
    {
        std::string choice = getKey();

        if(choice == "Left")
        {
            if(tempChoice > 0) tempChoice -= 1;
            currentOption = data.Position.at(tempChoice);
        }
        else if(choice == "Right")
        {
            if(tempChoice < 5) tempChoice += 1;
            currentOption = data.Position.at(tempChoice);
        }
        else if(choice == "Confirm")
        {
            SetConsoleCursorPosition(console.handle,cursorPosition);
            std::cout << "\b ";
            return currentOption;
        }
        SetConsoleCursorPosition(console.handle,cursorPosition);
        std::cout << std::string(19,' ');
        SetConsoleCursorPosition(console.handle,cursorPosition);
        std::cout << data.Position.at(tempChoice);
    }
    return "Error";
}

std::string chooseDepartment(database& data,consoleInfo& console)
{
    unsigned int tempChoice = 0;
    COORD cursorPosition = console.csbi.dwCursorPosition;
    SetConsoleTextAttribute(console.handle,(BACKGROUND_BLUE|BACKGROUND_GREEN));
    std::cout << "\b:";
    SetConsoleTextAttribute(console.handle,15);
    std::cout << data.Department.at(tempChoice);
    std::string currentOption = data.Department.at(tempChoice);
    while(1)
    {
        std::string choice = getKey();

        if(choice == "Left")
        {
            if(tempChoice > 0) tempChoice -= 1;
            currentOption = data.Department.at(tempChoice);
        }
        else if(choice == "Right")
        {
            if(tempChoice < 5) tempChoice += 1;
            currentOption = data.Department.at(tempChoice);
        }
        else if(choice == "Confirm")
        {
            SetConsoleCursorPosition(console.handle,cursorPosition);
            std::cout << "\b ";
            return currentOption;
        }
        SetConsoleCursorPosition(console.handle,cursorPosition);
        std::cout << std::string(19,' ');
        SetConsoleCursorPosition(console.handle,cursorPosition);
        std::cout << data.Department.at(tempChoice);
    }
    return "Error";
}

std::string getColumn(consoleInfo& console)
{
    GetConsoleScreenBufferInfo(console.handle,&console.csbi);
    COORD cursorPosition = console.csbi.dwCursorPosition;
    switch(cursorPosition.X)
    {
        case(1): return "Name";
        case(13): return "Surname";
        case(25): return "Gender";
        case(37): return "Position";
        case(59): return "Department";
        case(81): return "Birthday";
        case(93): return "Telephone";
        case(105): return "Salary";
    }
    return "Error";
}

void makeCsvFile(database& data,textCoordinates& TextCoord, consoleInfo& console)
{
    std::string csvFileName;
    COORD cursorPosition = console.csbi.dwCursorPosition;
    SetConsoleCursorPosition(console.handle,TextCoord.endTextPos);

    std::cout << "Enter the csv file name: ";
    std::cin >> csvFileName;
    std::cout << "Saving database .csv file...\n";

    std::ofstream fileOutput(csvFileName);
    for (unsigned int i = 0;i<data.dataMap["Name"].size()+1;i++)
    {
        std::string choice;
        for (int j = 0;j < 8;j++)
        {
            switch(j)
            {
                case 0: choice = "Name"; break;
                case 1: choice = "Surname"; break;
                case 2: choice = "Gender"; break;
                case 3: choice = "Position"; break;
                case 4: choice = "Department"; break;
                case 5: choice = "Birthday"; break;
                case 6: choice = "Telephone"; break;
                case 7: choice = "Salary"; break;
            }
            if(i==0) fileOutput << choice << ";";
            else fileOutput << data.dataMap[choice].at(i-1) << ";";
        }
        fileOutput << "\n";
    }
    std::cout << "Done!\n";
    TextCoord.endTextPos.Y = static_cast<short>(TextCoord.endTextPos.Y + 3);
    SetConsoleCursorPosition(console.handle,cursorPosition);

    fileOutput.close();
}

void insertInstructions(consoleInfo& console)
{
    std::cout << "Navigate using arrow keys, press '";
    SetConsoleTextAttribute(console.handle,10);
    std::cout << "enter";
    SetConsoleTextAttribute(console.handle,15);
    std::cout << "' to edit field.\n";

    std::cout << "Press '";
    SetConsoleTextAttribute(console.handle,10);
    std::cout << "s";
    SetConsoleTextAttribute(console.handle,15);
    std::cout << "' to save to file.\n";

    std::cout << "Press '";
    SetConsoleTextAttribute(console.handle,10);
    std::cout << "n";
    SetConsoleTextAttribute(console.handle,15);
    std::cout << "' to add new line.\n";

    std::cout << "Press '";
    SetConsoleTextAttribute(console.handle,10);
    std::cout << "r";
    SetConsoleTextAttribute(console.handle,15);
    std::cout << "' to remove current line.\n";

    std::cout << "Press '";
    SetConsoleTextAttribute(console.handle,10);
    std::cout << "esc";
    SetConsoleTextAttribute(console.handle,15);
    std::cout << "' to exit.\n";

}

void printHeadersAndText(textCoordinates& textCoord,consoleInfo& console)
{
    SetConsoleTextAttribute(console.handle,11);

    std::string choice;
    size_t cellLength = 10;

    for (int j = 0;j < 8;j++)
    {
        switch(j)
        {
            case 0: choice = "Name"; break;
            case 1: choice = "Surname"; break;
            case 2: choice = "Gender"; break;
            case 3: choice = "Position"; break;
            case 4: choice = "Department"; break;
            case 5: choice = "Birthday"; break;
            case 6: choice = "Telephone"; break;
            case 7: choice = "Salary"; break;
        }
        if(choice == "Position" || choice == "Department") std::cout << " " << choice << std::string(2*cellLength - choice.length(),' ')  << "|";
        else std::cout << " " << choice << std::string(cellLength - choice.length(),' ')  << "|";
    }
    SetConsoleTextAttribute(console.handle,15);
    std::cout << "\n" << std::string(20 + 8*(2+cellLength),'-') << "\n";

    GetConsoleScreenBufferInfo(console.handle,&console.csbi);
    textCoord.startTextPos = console.csbi.dwCursorPosition;
    insertInstructions(console);
    GetConsoleScreenBufferInfo(console.handle,&console.csbi);
    textCoord.endTextPos = console.csbi.dwCursorPosition;
}

void insertEmptyLine()
{
    size_t cellLength = 11;
    for (int j = 0;j < 8;j++)
    {
        if(j == 3 || j == 4) std::cout << std::string(2* cellLength-1,' ')  << "|";
        else std::cout << std::string(cellLength,' ')  << "|";
    }
    std::cout << "\n" << std::string(20 + 8*(1+cellLength),'-') << "\n";
}

void newLine(database& data, textCoordinates& textCoord,consoleInfo& console)
{
    GetConsoleScreenBufferInfo(console.handle,&console.csbi);
    COORD start;
    start.X = 1;
    start.Y = 2;
    unsigned long charsWritten;
    unsigned int tempRightCoord = static_cast<unsigned int>(console.csbi.srWindow.Right);
    for (auto v: data.dataMap) data.dataMap[v.first].push_back("");

    FillConsoleOutputCharacterA(console.handle,' ',static_cast<unsigned long>(textCoord.endTextPos.Y-textCoord.startTextPos.Y) * tempRightCoord,textCoord.startTextPos,&charsWritten);
    SetConsoleCursorPosition(console.handle,textCoord.startTextPos);
    textCoord.startTextPos.Y = static_cast<short>(textCoord.startTextPos.Y + 2);
    textCoord.endTextPos.Y = static_cast<short>(textCoord.endTextPos.Y + 2);
    insertEmptyLine();
    insertInstructions(console);

    SetConsoleCursorPosition(console.handle,start);
}

void move(database& data, std::string direction,consoleInfo& console)
{
    GetConsoleScreenBufferInfo(console.handle,&console.csbi);
    COORD cursorPosition = console.csbi.dwCursorPosition;
    int numberOfRows = static_cast<int>(data.dataMap["Name"].size());
    std::string column = getColumn(console);

    if(direction == "Up")
    {
        if(cursorPosition.Y >2) cursorPosition.Y = static_cast<short>(cursorPosition.Y - 2);
    }
    else if(direction == "Left")
    {
        if(cursorPosition.X > 12)
        {
            if(column == "Birthday" || column == "Department") cursorPosition.X = static_cast<short>(cursorPosition.X -22);
            else cursorPosition.X = static_cast<short>(cursorPosition.X -12);
        }
    }
    else if(direction == "Right")
    {
        if(cursorPosition.X < 105)
        {
            if(column == "Department" || column == "Position") cursorPosition.X = static_cast<short>(cursorPosition.X +22);
            else cursorPosition.X = static_cast<short>(cursorPosition.X + 12);
        }
    }
    else if(direction == "Down")
    {
        if(cursorPosition.Y < numberOfRows*2) cursorPosition.Y = static_cast<short>(cursorPosition.Y + 2);
    }
    SetConsoleCursorPosition(console.handle,cursorPosition);
}

void enterData(database& data,consoleInfo& console)
{
    GetConsoleScreenBufferInfo(console.handle,&console.csbi);
    COORD cursorPosition = console.csbi.dwCursorPosition;
    std::string temp;
    std::string column = getColumn(console);
    if(column != "Gender" && column != "Position" && column != "Department")
    {
        SetConsoleTextAttribute(console.handle,(BACKGROUND_BLUE|BACKGROUND_GREEN));
        std::cout << "\b:";
        SetConsoleTextAttribute(console.handle,15);
        std::cin >> temp;
        data.dataMap[column].at(static_cast<unsigned long>((cursorPosition.Y-1)/2)) = temp;
        SetConsoleCursorPosition(console.handle,cursorPosition);
        std::cout << "\b ";
    }
    else if(column == "Gender") data.dataMap[column].at(static_cast<unsigned long>((cursorPosition.Y-1)/2)) = chooseGender(console);
    else if(column == "Position") data.dataMap[column].at(static_cast<unsigned long>((cursorPosition.Y-1)/2)) = choosePosition(data,console);
    else if(column == "Department") data.dataMap[column].at(static_cast<unsigned long>((cursorPosition.Y-1)/2)) = chooseDepartment(data,console);
}

void deleteLine(database& data, textCoordinates &textCoord,consoleInfo& console)
{
    if(data.dataMap["Name"].size() > 0)
    {
        GetConsoleScreenBufferInfo(console.handle,&console.csbi);
        COORD cursorPosition = console.csbi.dwCursorPosition;

        unsigned long currentRow = static_cast<unsigned long>(cursorPosition.Y/2);
        unsigned long charsWritten;
        short height;
        if(currentRow < 6) height = static_cast<short>(15*(textCoord.startTextPos.Y - 2 - cursorPosition.Y));
        else height = static_cast<short>(cursorPosition.Y*(textCoord.startTextPos.Y - 2 - cursorPosition.Y));
        short width = console.csbi.dwSize.X;
        short bufferY = static_cast<short>(textCoord.endTextPos.Y + 1);
        PCHAR_INFO buffer = new CHAR_INFO[static_cast<unsigned int>(width*height)];
        COORD buffer_size = {width, height};
        COORD buffer_index = {0,bufferY};
        SMALL_RECT read_rectangle{0,static_cast<short>(cursorPosition.Y+2),console.csbi.srWindow.Right,static_cast<short>(textCoord.startTextPos.Y-1)};
        SMALL_RECT write_rectangle{0,static_cast<short>(cursorPosition.Y),console.csbi.srWindow.Right,static_cast<short>(textCoord.startTextPos.Y-3)};

        for(auto v: data.dataMap) data.dataMap[v.first].erase(data.dataMap[v.first].begin()+currentRow-1);

        if(currentRow <= data.dataMap["Name"].size()) ReadConsoleOutputA(console.handle,buffer,buffer_size,buffer_index,&read_rectangle);

        short temp = cursorPosition.X;
        cursorPosition.X = static_cast<short>(0);
        FillConsoleOutputCharacterA(console.handle,' ',static_cast<unsigned long>(textCoord.endTextPos.Y-cursorPosition.Y) * static_cast<unsigned long>(console.csbi.dwSize.X),cursorPosition,&charsWritten);
        cursorPosition.X = temp;
        textCoord.startTextPos.Y = static_cast<short>(textCoord.startTextPos.Y - 2);
        textCoord.endTextPos.Y = static_cast<short>(textCoord.endTextPos.Y - 2);

        if(currentRow <= data.dataMap["Name"].size())  WriteConsoleOutputA(console.handle,buffer,buffer_size,buffer_index,&write_rectangle);

        SetConsoleCursorPosition(console.handle,textCoord.startTextPos);
        insertInstructions(console);

        if(cursorPosition.Y > 3) cursorPosition.Y = static_cast<short>(cursorPosition.Y -2);
        SetConsoleCursorPosition(console.handle,cursorPosition);
    }
}

int main()
{
    consoleInfo console;
    console.handle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string action;

    database myDatabase;
    textCoordinates myTextCoord;

    initDatabase(myDatabase);
    printHeadersAndText(myTextCoord,console);

    while(1)
    {
        action = getKey();
        if(action == "Newline") newLine(myDatabase,myTextCoord,console);
        else if(action =="Confirm") enterData(myDatabase,console);
        else if(action =="Save") makeCsvFile(myDatabase,myTextCoord,console);
        else if(action =="Remove") deleteLine(myDatabase,myTextCoord,console);
        else if(action =="Exit")
        {
            SetConsoleCursorPosition(console.handle,myTextCoord.endTextPos);
            return 0;
        }
        else move(myDatabase,action,console);
    }
}
