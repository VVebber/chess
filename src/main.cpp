#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//Wondows
#include "Windows/MainMenu.h"
#include "Windows/PlayMenu.h"
#include "Windows/Setting.h"
#include "Windows/TypeGame.h"

//Fige

#include "GameLogic.h"
#include "Figures/Figure.h"
#include "GameLogic.h"

//Functions
void DownTX(std::vector <sf::Texture> &, std::vector <std::string>);
void DownFont(std::vector <sf::Font> &, std::vector <std::string>);

int main() {
    //for window
    std::string TypeDevise;

#if defined(__ANDROID__)
    TypeDevise = "Android";
#elif defined(SFML_SYSTEM_WINDOWS)
    TypeDevise = "Windows";
#elif defined(SFML_SYSTEM_LINUX)
        TypeDevise = "Linux";
#elif defined(SFML_SYSTEM_MACOS)
        TypeDevise = "macOS";
#else
settings.setTypeDevise("Unknown OS");
#endif

    sf::RenderWindow win(sf::VideoMode(1280, 960), L"Chess");

    int Quant_Players = 2;
    int NPDGT = 16; // number of pieces depending on game type(кол-во фигур от тира игры классика - 16)
      
    int Quant_Pawn = 8, Quant_Knight = 2, Quant_Bishop = 2,
        Quant_Rook = 2, Quant_Queen = 1,  Quant_King = 1;

    int NombeFigure = -1;
    int *prt_NombeFigure = &NombeFigure; //идет в функию logic

    int MoverCounter = 1;
    int *ptr_MoverCounter = &MoverCounter; //идет в функию logic

    bool Press = false;
    bool *ptr_Press = &Press; //идет в функию logic

    bool StrokeLock = true; //идет в функию logic
    bool *ptr_StrokeLock = &StrokeLock;

    bool CreadPlayMenu = false;
    bool *ptr_CreadPlayMenu = &CreadPlayMenu;

    bool PlayLogic = false;
    bool *ptr_PlayLogic = &PlayLogic;

    std::string Color = "black";
    std::string *ptr_Color = &Color; // идут в функию logic

    std::string TypeFigure;
    std::string *prt_TypeFigure = &TypeFigure;//идет в функию logic

    

    //Cread and Downlaud TX in vector
    std::vector <std::string> FileNamesBekgr = {"images/background.png"};
    std::vector <sf::Texture> TxBekgraund;
    DownTX(TxBekgraund, FileNamesBekgr);
    //settings.setTxBackground(TxBekgraund);
    //settings.CreatBackground();

    std::vector <std::string> FileNamesChessBoard = {"images/ChessBoard/WhiteBlack_1.png",
                                                     "images/ChessBoard/WhiteBlack_2.png"};
    std::vector <sf::Texture> TxChessBoard;
    DownTX(TxChessBoard, FileNamesChessBoard);

    std::vector <sf::Texture> TxPawn;
    std::vector <std::string> FileNamesPaw = {"images/Pawns/WhitePawn.png", "images/Pawns/BlackPawn.png"};
    DownTX(TxPawn, FileNamesPaw);

    std::vector <sf::Texture> TxQueen;
    std::vector <std::string> FileNamesQueens = {"images/Queens/WhiteQueen.png", "images/Queens/BlackQueen.png"};
    DownTX(TxQueen, FileNamesQueens);

    std::vector <sf::Texture> TxKing;
    std::vector <std::string> FileNamesKings = {"images/Kings/WhiteKing.png", "images/Kings/BlackKing.png"};
    DownTX(TxKing, FileNamesKings);

    std::vector <sf::Texture> TxRook;
    std::vector <std::string> FileNamesRooks = {"images/Rooks/WhiteRook.png", "images/Rooks/BlackRook.png"};
    DownTX(TxRook, FileNamesRooks);

    std::vector <sf::Texture> TxKnight;
    std::vector <std::string> FileNamesKnights = {"images/Knights/WhiteKnight.png", "images/Knights/BlackKnight.png"};
    DownTX(TxKnight, FileNamesKnights);

    std::vector <sf::Texture> TxBishop;
    std::vector <std::string> FileNamesBishops = {"images/Bishops/WhiteBishop.png", "images/Bishops/BlackBishop.png"};
    DownTX(TxBishop, FileNamesBishops);

    std::vector<sf::Font> Fonts;
    std::vector<std::string> FileNamesFont = {"Font/Arial/arialmt.ttf"};
    DownFont(Fonts,FileNamesFont);

    //cread button
    MainMenu mainMenu({}, 3, Fonts); //|0 - textur| 3 - button| 0 - font|
    PlayMenu playMenu({}, 5, Fonts, TxChessBoard);//
    Setting setting({}, 0, {}, TxBekgraund, TypeDevise);
    TypeGame typeGame;
    mainMenu.CreateAll();
    setting.CreateAll();

    //texture down in typeGame
    
    typeGame.DownTx(TxKing, "King");
    typeGame.DownTx(TxQueen, "Queen");
    typeGame.DownTx(TxRook, "Rook");
    typeGame.DownTx(TxBishop, "Bishop");
    typeGame.DownTx(TxKnight, "Knight");
    typeGame.DownTx(TxPawn, "Pawn");

    //cread Figure
    std::vector <Figure> figures;

    while (win.isOpen()) {
        sf::Event event{};

        //mainMenu.getEvent(event);
        //playMenu.getEvent(event);

        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    //копирование нажотой позиции в классы 
                    mainMenu.setMousePosPres(mousePosition);
                    playMenu.setMousePosPres(mousePosition);
                    typeGame.setMousePosPres(mousePosition);

                    /*for (auto& figure : figures) {
                        figure.setMousePosPres(mousePosition);
                    }*/

                    //нажатия
                    if (mainMenu.getPresAndHor()) {
                        mainMenu.PresMainMenu(win, playMenu,typeGame,figures);
                    } else if (playMenu.getPresAndHor()) {
                        playMenu.PressedPlayMenu(figures, mainMenu, typeGame);
                    } else if (typeGame.getPresAndHor()) {
                        typeGame.PressedTypeGame(playMenu);
                    }
                }
            } else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePosition(event.mouseMove.x, event.mouseMove.y);
                mainMenu.setMousePosHover(mousePosition);
                playMenu.setMousePosHover(mousePosition);

                for (auto& figure : figures) {
                    figure.setMousePosHover(mousePosition);
                }

                // hovers
                mainMenu.hover();
                playMenu.hover();
            }

        }
  
        win.clear();

        win.draw(setting.getBackground());

        mainMenu.WinButton(win);
        playMenu.WinButton(win);
        typeGame.WinAll(win);

        for (auto figure : figures) {
            figure.WinFigure(win);
        }
        
       if (figures.size() != 0) {
           CustomLogic(win,figures,typeGame,playMenu);
       }

        win.display();
    }
    return 0;
}



// ФУНКЦИИ

void DownTX(std::vector <sf::Texture> &TxVector, std::vector <std::string> FileNames) {
    for (const auto &fileName: FileNames) {
        sf::Texture Textur;
        if (Textur.loadFromFile(fileName)) {
            TxVector.push_back(Textur);
        }
    }
}

void DownFont(std::vector <sf::Font> &Fonts, std::vector <std::string> FileNames) {
    for (const auto &fileName: FileNames) {
        sf::Font font;
        if (font.loadFromFile(fileName)) {
            Fonts.push_back(font);
           }
    }
}


