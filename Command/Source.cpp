#include <iostream>
#include <vector>

using namespace std;


class Game
{
public:
    void Create()
    {
        cout << "Create game\n";
    }

    void Open(string file)
    {
        cout << "open game from" << file << "\n";
    }

    void Save(string file)
    {
        cout << "Save game from" << file << "\n";
    }
    void MakeMove(string move)
    {
        cout << "MakeMove game from" << move << "\n";
    }
};

// Интерфейс Команды объявляет метод для выполнения команд.
 
string GetUserInput(string promt)
{
    string input;
    cout << promt;
    cin >> input;
    return input;
}


class Command 
{
protected:
    Game* game;
    Command(Game* game) : game{game} {}
public:
    virtual ~Command(){}
    virtual void Execute()  = 0;
};

// Некоторые команды способны выполнять простые операции самостоятельно.
 

class CreateGameCommand : public Command
{
public:
    CreateGameCommand(Game* game) : Command(game) {}

    void Execute()
    {
        game->Create();
    }
};


class OpenGameCommand : public Command
{
public:
    OpenGameCommand(Game* game) : Command(game) {}

    void Execute()
    {
        game->Open(GetUserInput("Input name of File"));
    }

};

class SaveGameCommand : public Command
{
public:
    SaveGameCommand (Game* game) : Command(game) {}

    void Execute()
    {
        game->Save(GetUserInput("Input name of File"));
    }

};

class MakeMoveGameCommand : public Command
{
public:
    MakeMoveGameCommand(Game* game) : Command(game) {}
    void Execute()
    {
        game->Save("Temp of file");
     game->MakeMove(GetUserInput("Input move"));
    }
};

class UndoCommand : public Command
{
public:
    UndoCommand(Game* game) : Command(game) {}
    void Execute()
    {
        game->Open(" Temp open");
    }
};


int main() {
   
    Game game;

    vector<Command*> player;

    player.push_back(new CreateGameCommand(&game));
    player.push_back(new MakeMoveGameCommand(&game));
    player.push_back(new MakeMoveGameCommand(&game));
    player.push_back(new MakeMoveGameCommand(&game));

    player.push_back(new UndoCommand(&game));

    player.push_back(new MakeMoveGameCommand(&game));

    player.push_back(new SaveGameCommand(&game));

    for (Command* command : player)
        command->Execute();

    for (Command* command : player)
       delete command;

    return 0;
}