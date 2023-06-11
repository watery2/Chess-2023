#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieces.h"
#include "bot.h"
#include "functions.h"

int main()
{

	// Lentos masyvai

	static std::string BoardWhite[8][8] = { {"BR1", "BK1", "BB1", "BQU", "BKI", "BB2", "BK2", "BR2"},
											{"BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"},
											{"WR1", "WK1", "WB1", "WQU", "WKI", "WB2", "WK2", "WR2"} };

	static std::string BoardBlack[8][8] = { {"WR1", "WK1", "WB1", "WKI", "WQU", "WB2", "WK2", "WR2"},
											{"WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
											{"BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"},
											{"BR1", "BK1", "BB1", "BKI", "BQU", "BB2", "BK2", "BR2"} };

	static std::string OriginalBoardWhite[8][8] = { {"BR1", "BK1", "BB1", "BQU", "BKI", "BB2", "BK2", "BR2"},
													{"BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"},
													{"WR1", "WK1", "WB1", "WQU", "WKI", "WB2", "WK2", "WR2"} };

	static std::string OriginalBoardBlack[8][8] = { {"WR1", "WK1", "WB1", "WKI", "WQU", "WB2", "WK2", "WR2"},
													{"WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX", "XxX"},
													{"BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"},
													{"BR1", "BK1", "BB1", "BKI", "BQU", "BB2", "BK2", "BR2"} };

	float x, y;

	// 1 yra Baltas 2 yra Juodas

	int Player = 0;

	// Ar zaidejo eile

	bool PlayersTurn = false;

	// Zinoti ar pestininkas bus paukstintas, jei true tai programa sustabdys pokol pasirinks pasiaukstinima

	bool PawnGonnaBePromoted = false;

	// Zinoti ar botas pralaimejo, jei true ismeta "You Win" vaizda

	bool BotLost = false;

	// Zinoti ar nieks nelaimejo, jei true ismeta "Draw" vaizda

	bool draw = false;

	// Zinoti ar zaidejas paspaude ant klaustuko, jei paspaude ismeta vaizda kuriamia parasyta kaip pradeti

	bool HelpSelected = false;

	// Paskutine positsija

	sf::Vector2f LastLocation(0, 0);

	// Zinoti kiek judesiu kartojasi, jei 5 tada ismeta "Draw" vaizda

	int NumberOfRepeatedMove = 0;

	// Ekranas

	sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Dominykas Orlovas P1/2V", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	// Lenta

	sf::Sprite background;

	sf::Texture backgroundTexture;

	backgroundTexture.loadFromFile("img/board.jpeg");

	background.setScale(0.8, 0.8);

	background.setTexture(backgroundTexture);

	// Help Img
	
	sf::Texture HelpTextTexture;

	sf::Sprite HelpText;

	HelpTextTexture.loadFromFile("img/Help.png");

	HelpText.setTexture(HelpTextTexture);

	HelpText.setPosition(sf::Vector2f(0, 0));

	sf::Texture HelpButtonTexture;

	sf::Sprite HelpButton;

	HelpButtonTexture.loadFromFile("img/HelpButton.png");

	HelpButton.setTexture(HelpButtonTexture);

	HelpButton.setOrigin(HelpButton.getTexture()->getSize().x * 0.5, HelpButton.getTexture()->getSize().y * 0.5);

	HelpButton.setPosition(sf::Vector2f(750, 400));

	// 
	
	// Text

	sf::Texture ChoseTextTexture;

	sf::Sprite ChoseText;

	ChoseTextTexture.loadFromFile("img/playas.png");

	ChoseText.setTexture(ChoseTextTexture);

	ChoseText.setOrigin(ChoseText.getTexture()->getSize().x * 0.5, ChoseText.getTexture()->getSize().y * 0.5);

	ChoseText.setPosition(sf::Vector2f(400, 350));

	sf::Texture WinTextTexture;

	sf::Sprite WinText;

	WinTextTexture.loadFromFile("img/YouWin.png");

	WinText.setTexture(WinTextTexture);

	WinText.setOrigin(WinText.getTexture()->getSize().x * 0.5, WinText.getTexture()->getSize().y * 0.5);

	WinText.setPosition(-300, 0);

	sf::Texture LoseTextTexture;

	sf::Sprite LoseText;

	LoseTextTexture.loadFromFile("img/YouLose.png");

	LoseText.setTexture(LoseTextTexture);

	LoseText.setOrigin(LoseText.getTexture()->getSize().x * 0.5, LoseText.getTexture()->getSize().y * 0.5);

	LoseText.setPosition(-300, 0);

	sf::Texture DrawTextTexture;

	sf::Sprite DrawText;

	DrawTextTexture.loadFromFile("img/Draw.png");

	DrawText.setTexture(DrawTextTexture);

	DrawText.setOrigin(DrawText.getTexture()->getSize().x * 0.5, DrawText.getTexture()->getSize().y * 0.5);

	DrawText.setPosition(-300, 0);

	///////////////////

	// Paspaudus juos nustatomas zaidejaus spalva

	Piece Chose_King_W("img/kingW.png", sf::Vector2f(350, 550), "king");

	Piece Chose_King_B("img/kingB.png", sf::Vector2f(450, 550), "king");

	//

	// Figuros
	
	// Black
	Piece B_Rook1("img/towB.png", sf::Vector2f(50, 50), "rook");

	Piece B_Knight1("img/KniB.png", sf::Vector2f(150, 50), "knight");

	Piece B_Bishop1("img/bishB.png", sf::Vector2f(250, 50), "bishop");

	Piece B_Queen("img/queenB.png", sf::Vector2f(350, 50), "queen");

	Piece B_King("img/kingB.png", sf::Vector2f(450, 50), "king");

	Piece B_Bishop2("img/bishB.png", sf::Vector2f(550, 50), "bishop");

	Piece B_Knight2("img/KniB.png", sf::Vector2f(650, 50), "knight");

	Piece B_Rook2("img/towB.png", sf::Vector2f(750, 50), "rook");

	Piece B_Pawn1("img/pawnB.png", sf::Vector2f(50, 150), "pawn");

	Piece B_Pawn2("img/pawnB.png", sf::Vector2f(150, 150), "pawn");

	Piece B_Pawn3("img/pawnB.png", sf::Vector2f(250, 150), "pawn");

	Piece B_Pawn4("img/pawnB.png", sf::Vector2f(350, 150), "pawn");

	Piece B_Pawn5("img/pawnB.png", sf::Vector2f(450, 150), "pawn");

	Piece B_Pawn6("img/pawnB.png", sf::Vector2f(550, 150), "pawn");

	Piece B_Pawn7("img/pawnB.png", sf::Vector2f(650, 150), "pawn");

	Piece B_Pawn8("img/pawnB.png", sf::Vector2f(750, 150), "pawn");

	// White
	
	Piece W_Rook1("img/towW.png", sf::Vector2f(50, 750), "rook");

	Piece W_Knight1("img/KniW.png", sf::Vector2f(150, 750), "knight");

	Piece W_Bishop1("img/bishW.png", sf::Vector2f(250, 750), "bishop");

	Piece W_Queen("img/queenW.png", sf::Vector2f(350, 750), "queen");

	Piece W_King("img/kingW.png", sf::Vector2f(450, 750), "king");

	Piece W_Bishop2("img/bishW.png", sf::Vector2f(550, 750), "bishop");

	Piece W_Knight2("img/KniW.png", sf::Vector2f(650, 750), "knight");

	Piece W_Rook2("img/towW.png", sf::Vector2f(750, 750), "rook");

	Piece W_Pawn1("img/pawnW.png", sf::Vector2f(50, 650), "pawn");

	Piece W_Pawn2("img/pawnW.png", sf::Vector2f(150, 650), "pawn");

	Piece W_Pawn3("img/pawnW.png", sf::Vector2f(250, 650), "pawn");

	Piece W_Pawn4("img/pawnW.png", sf::Vector2f(350, 650), "pawn");

	Piece W_Pawn5("img/pawnW.png", sf::Vector2f(450, 650), "pawn");

	Piece W_Pawn6("img/pawnW.png", sf::Vector2f(550, 650), "pawn");

	Piece W_Pawn7("img/pawnW.png", sf::Vector2f(650, 650), "pawn");

	Piece W_Pawn8("img/pawnW.png", sf::Vector2f(750, 650), "pawn");

	Piece* White[16] = { &W_Rook1, &W_Knight1, &W_Bishop1, &W_Queen, &W_King, &W_Bishop2, &W_Knight2, &W_Rook2, &W_Pawn1, &W_Pawn2, &W_Pawn3, &W_Pawn4, &W_Pawn5, &W_Pawn6, &W_Pawn7, &W_Pawn8};
	Piece* Black[16] = { &B_Rook1, &B_Knight1, &B_Bishop1, &B_Queen, &B_King, &B_Bishop2, &B_Knight2, &B_Rook2, &B_Pawn1, &B_Pawn2, &B_Pawn3, &B_Pawn4, &B_Pawn5, &B_Pawn6, &B_Pawn7, &B_Pawn8 };

	// kai paspaus kazkoki Figura jis bus uz ju
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(100, 100));

	rect.setOrigin(sf::Vector2f(rect.getSize().x * 0.5, rect.getSize().y * 0.5));

	rect.setFillColor(sf::Color(255, 255, 0, 80));

	rect.setPosition(sf::Vector2f(-300, 0));

	//////////////////////////////////////////////////////////////////////

	// taskas kuris rodis kur galima Eiti

	sf::CircleShape circle;

	circle.setRadius(20.0f);

	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));

	circle.setFillColor(sf::Color(0, 0, 0, 80));

	circle.setPosition(sf::Vector2f(-300, 0));

	sf::CircleShape circleAttack;

	circleAttack.setRadius(30.0f);

	circleAttack.setOrigin(sf::Vector2f(circleAttack.getRadius(), circleAttack.getRadius()));

	circleAttack.setFillColor(sf::Color(0, 0, 0, 0));

	circleAttack.setOutlineThickness(10.0f);

	circleAttack.setOutlineColor(sf::Color(0, 0, 0, 80));

	circleAttack.setPosition(sf::Vector2f(-300, 0));

	///////////////////////////////////////////////////////////

	sf::Mouse::setPosition(sf::Vector2i(100, 200), window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			// The mouse being pressed event 
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				x = sf::Mouse::getPosition(window).x;

				y = sf::Mouse::getPosition(window).y;

				if (Chose_King_W.Clicked(sf::Vector2f(x, y)) && !HelpSelected)
				{
					Player = 1;

					PlayersTurn = true;

					BotLost = false;

					draw = false;

					LastLocation = sf::Vector2f(0, 0);

					NumberOfRepeatedMove = 0;

					ChoseText.setPosition(sf::Vector2f(-300, 0));

					HelpButton.setPosition(sf::Vector2f(-300, 0));

					Chose_King_W.SetLocation(sf::Vector2f(-300, 0));
					Chose_King_B.SetLocation(sf::Vector2f(-300, 0));

					SetupBoard(White, Black, Player);

				}
				else if (Chose_King_B.Clicked(sf::Vector2f(x, y)) && !HelpSelected)
				{
					Player = 2;

					PlayersTurn = false;

					BotLost = false;

					draw = false;

					LastLocation = sf::Vector2f(0, 0);

					NumberOfRepeatedMove = 0;

					ChoseText.setPosition(sf::Vector2f(-300, 0));

					HelpButton.setPosition(sf::Vector2f(-300, 0));

					Chose_King_W.SetLocation(sf::Vector2f(-300, 0));
					Chose_King_B.SetLocation(sf::Vector2f(-300, 0));

					SetupBoard(White, Black, Player);
				}

				if (sqrt(pow(x - HelpButton.getPosition().x, 2) + pow(y - HelpButton.getPosition().y, 2)) <= 50 && !HelpSelected)
				{
					HelpSelected = true;
				}
				else if (HelpSelected)
				{
					HelpSelected = false;
				}

				if (sqrt(pow(x - LoseText.getPosition().x, 2) + pow(y - LoseText.getPosition().y, 2)) <= 150)
				{
					LoseText.setPosition(sf::Vector2f(-300, 0));

					ChoseText.setPosition(sf::Vector2f(400, 350));

					HelpButton.setPosition(sf::Vector2f(750, 400));

					Chose_King_W.SetLocation(sf::Vector2f(350, 550));
					Chose_King_B.SetLocation(sf::Vector2f(450, 550));

					CopyBoardToAnothereArray(OriginalBoardWhite, BoardWhite);
					CopyBoardToAnothereArray(OriginalBoardBlack, BoardBlack);

					SetupBoard(White, Black, 1);
				}
				else if (sqrt(pow(x - WinText.getPosition().x, 2) + pow(y - WinText.getPosition().y, 2)) <= 150)
				{
					WinText.setPosition(sf::Vector2f(-300, 0));

					ChoseText.setPosition(sf::Vector2f(400, 350));

					HelpButton.setPosition(sf::Vector2f(750, 400));

					Chose_King_W.SetLocation(sf::Vector2f(350, 550));
					Chose_King_B.SetLocation(sf::Vector2f(450, 550));

					CopyBoardToAnothereArray(OriginalBoardWhite, BoardWhite);
					CopyBoardToAnothereArray(OriginalBoardBlack, BoardBlack);

					SetupBoard(White, Black, 1);
				}
				else if (sqrt(pow(x - DrawText.getPosition().x, 2) + pow(y - DrawText.getPosition().y, 2)) <= 150)
				{
					DrawText.setPosition(sf::Vector2f(-300, 0));

					ChoseText.setPosition(sf::Vector2f(400, 350));

					HelpButton.setPosition(sf::Vector2f(750, 400));

					Chose_King_W.SetLocation(sf::Vector2f(350, 550));
					Chose_King_B.SetLocation(sf::Vector2f(450, 550));

					CopyBoardToAnothereArray(OriginalBoardWhite, BoardWhite);
					CopyBoardToAnothereArray(OriginalBoardBlack, BoardBlack);

					SetupBoard(White, Black, 1);
				}

				if (Player == 1 && PlayersTurn && !PawnGonnaBePromoted)
				{

					if (W_Rook1.Clicked(sf::Vector2f(x, y)))
					{
						W_Rook1.HighlightPiece(rect, White);
					}
					else if (W_Knight1.Clicked(sf::Vector2f(x, y)))
					{
						W_Knight1.HighlightPiece(rect, White);
					}
					else if (W_Bishop1.Clicked(sf::Vector2f(x, y)))
					{
						W_Bishop1.HighlightPiece(rect, White);
					}
					else if (W_Queen.Clicked(sf::Vector2f(x, y)))
					{
						W_Queen.HighlightPiece(rect, White);
					}
					else if (W_King.Clicked(sf::Vector2f(x, y)))
					{
						W_King.HighlightPiece(rect, White);
					}
					else if (W_Bishop2.Clicked(sf::Vector2f(x, y)))
					{
						W_Bishop2.HighlightPiece(rect, White);
					}
					else if (W_Knight2.Clicked(sf::Vector2f(x, y)))
					{
						W_Knight2.HighlightPiece(rect, White);
					}
					else if (W_Rook2.Clicked(sf::Vector2f(x, y)))
					{
						W_Rook2.HighlightPiece(rect, White);
					}
					else if (W_Pawn1.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn1.HighlightPiece(rect, White);
					}
					else if (W_Pawn2.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn2.HighlightPiece(rect, White);
					}
					else if (W_Pawn3.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn3.HighlightPiece(rect, White);
					}
					else if (W_Pawn4.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn4.HighlightPiece(rect, White);
					}
					else if (W_Pawn5.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn5.HighlightPiece(rect, White);
					}
					else if (W_Pawn6.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn6.HighlightPiece(rect, White);
					}
					else if (W_Pawn7.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn7.HighlightPiece(rect, White);
					}
					else if (W_Pawn8.Clicked(sf::Vector2f(x, y)))
					{
						W_Pawn8.HighlightPiece(rect, White);
					}
					else
					{
						W_King.MoveKing(sf::Vector2f(x, y), W_Rook1, W_Rook2, BoardWhite, Black, PlayersTurn, 'W', LastLocation, NumberOfRepeatedMove);

						W_Queen.MoveQueen(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Rook1.MoveRook(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Rook2.MoveRook(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Knight1.MoveKnight(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Knight2.MoveKnight(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Bishop1.MoveBishop(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Bishop2.MoveBishop(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn1.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn2.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn3.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn4.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn5.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn6.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn7.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						W_Pawn8.MovePawn(sf::Vector2f(x, y), BoardWhite, Black, PlayersTurn, PawnGonnaBePromoted, W_King.GetLocation(), 'W', LastLocation, NumberOfRepeatedMove);

						std::cout << std::endl;

						for (int i = 0; i < 8; i++)
						{

							for (int j = 0; j < 8; j++)
							{
								std::cout << BoardWhite[i][j] << " ";
							}

							std::cout << std::endl;
						}

						DeSelect(White, rect);

					}
				}

				if (Player == 2 && PlayersTurn && !PawnGonnaBePromoted)
				{

					if (B_Rook1.Clicked(sf::Vector2f(x, y)))
					{
						B_Rook1.HighlightPiece(rect, Black);
					}
					else if (B_Knight1.Clicked(sf::Vector2f(x, y)))
					{
						B_Knight1.HighlightPiece(rect, Black);
					}
					else if (B_Bishop1.Clicked(sf::Vector2f(x, y)))
					{
						B_Bishop1.HighlightPiece(rect, Black);
					}
					else if (B_Queen.Clicked(sf::Vector2f(x, y)))
					{
						B_Queen.HighlightPiece(rect, Black);
					}
					else if (B_King.Clicked(sf::Vector2f(x, y)))
					{
						B_King.HighlightPiece(rect, Black);
					}
					else if (B_Bishop2.Clicked(sf::Vector2f(x, y)))
					{
						B_Bishop2.HighlightPiece(rect, Black);
					}
					else if (B_Knight2.Clicked(sf::Vector2f(x, y)))
					{
						B_Knight2.HighlightPiece(rect, Black);
					}
					else if (B_Rook2.Clicked(sf::Vector2f(x, y)))
					{
						B_Rook2.HighlightPiece(rect, Black);
					}
					else if (B_Pawn1.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn1.HighlightPiece(rect, Black);
					}
					else if (B_Pawn2.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn2.HighlightPiece(rect, Black);
					}
					else if (B_Pawn3.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn3.HighlightPiece(rect, Black);
					}
					else if (B_Pawn4.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn4.HighlightPiece(rect, Black);
					}
					else if (B_Pawn5.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn5.HighlightPiece(rect, Black);
					}
					else if (B_Pawn6.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn6.HighlightPiece(rect, Black);
					}
					else if (B_Pawn7.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn7.HighlightPiece(rect, Black);
					}
					else if (B_Pawn8.Clicked(sf::Vector2f(x, y)))
					{
						B_Pawn8.HighlightPiece(rect, Black);
					}
					else
					{	
						B_King.MoveKing(sf::Vector2f(x, y), B_Rook1, B_Rook2, BoardBlack, White, PlayersTurn, 'B', LastLocation, NumberOfRepeatedMove);

						B_Queen.MoveQueen(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Rook1.MoveRook(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Rook2.MoveRook(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Knight1.MoveKnight(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Knight2.MoveKnight(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Bishop1.MoveBishop(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Bishop2.MoveBishop(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn1.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn2.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn3.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn4.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn5.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn6.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn7.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						B_Pawn8.MovePawn(sf::Vector2f(x, y), BoardBlack, White, PlayersTurn, PawnGonnaBePromoted, B_King.GetLocation(), 'B', LastLocation, NumberOfRepeatedMove);

						std::cout << std::endl;

						for (int i = 0; i < 8; i++)
						{

							for (int j = 0; j < 8; j++)
							{
								std::cout << BoardBlack[i][j] << " ";
							}

							std::cout << std::endl;
						}

						DeSelect(Black, rect);
					}
				}

				if (PawnGonnaBePromoted)
				{
					if (Player == 1)
					{
						PromotePawnIfClicked(sf::Vector2f(x, y), White, 'W', PawnGonnaBePromoted, BoardWhite);
					}
					else if (Player == 2)
					{
						PromotePawnIfClicked(sf::Vector2f(x, y), Black, 'B', PawnGonnaBePromoted, BoardBlack);
					}
				}
			}
		}


		//render
		window.clear();

		window.draw(background);

		window.draw(ChoseText);

		window.draw(Chose_King_W.GetSprite());

		window.draw(Chose_King_B.GetSprite());

		window.draw(rect);

		for (int i = 0; i < 16; i++)
		{
			window.draw(White[i]->GetSprite());

			window.draw(Black[i]->GetSprite());
		}
		
		if (NumberOfRepeatedMove >= 5 && Player != 0)
		{
			PlayersTurn = false;

			Player = 0;

			DrawText.setPosition(sf::Vector2f(430, 370));
		}

		if (!PlayersTurn && Player != 0 && !PawnGonnaBePromoted)
		{
			if (Player == 1)
			{
				BotMove(Black, White, W_King.GetLocation(), W_Rook1, W_Rook2, 'W', B_King.GetLocation(), B_Rook1, B_Rook2, BoardWhite, window, 'B', BotLost, draw);
			}
			else if (Player == 2)
			{
				BotMove(White, Black, B_King.GetLocation(), B_Rook1, B_Rook2, 'B', W_King.GetLocation(), W_Rook1, W_Rook2, BoardBlack, window, 'W', BotLost, draw);
			}

			if (!BotLost && !draw)
			{
				PlayersTurn = true;
			}
			else if (draw)
			{
				PlayersTurn = false;

				Player = 0;

				DrawText.setPosition(sf::Vector2f(430, 370));
			}
			else
			{
				PlayersTurn = false;

				Player = 0;

				WinText.setPosition(sf::Vector2f(430, 370));
			}
		}

		if (Player == 1)
		{
			if (CheckIfPlayerPieceIsUnderAttackOrProtected(BoardWhite, W_King.GetLocation(), 'W'))
			{
				if (KingCheckMated(White, BoardWhite, W_Rook1, W_Rook2, W_King.GetLocation(), 'W'))
				{
					PlayersTurn = false;

					Player = 0;

					LoseText.setPosition(sf::Vector2f(430, 370));
				}
			}
			else
			{
				if (KingCheckMated(White, BoardWhite, W_Rook1, W_Rook2, W_King.GetLocation(), 'W'))
				{
					PlayersTurn = false;

					Player = 0;

					DrawText.setPosition(sf::Vector2f(430, 370));
				}

			}
		}
		else if (Player == 2)
		{
			if (CheckIfPlayerPieceIsUnderAttackOrProtected(BoardBlack, B_King.GetLocation(), 'B'))
			{
				if (KingCheckMated(Black, BoardBlack, B_Rook1, B_Rook2, B_King.GetLocation(), 'B'))
				{
					PlayersTurn = false;

					Player = 0;

					LoseText.setPosition(sf::Vector2f(430, 370));
				}
			}
			else
			{
				if (KingCheckMated(Black, BoardBlack, B_Rook1, B_Rook2, B_King.GetLocation(), 'B'))
				{
					PlayersTurn = false;

					Player = 0;

					DrawText.setPosition(sf::Vector2f(430, 370));
				}
			}
		}
		
		if (PawnGonnaBePromoted)
		{
			if (Player == 1)
			{
				DrawPromotionPieces(window, White, W_Queen, W_Knight1, W_Rook1, W_Bishop1);
			}
			else if (Player == 2)
			{
				DrawPromotionPieces(window, Black, B_Queen, B_Knight1, B_Rook1, B_Bishop1);
			}
		}

		if (Player == 1)
		{
			PutCircles(White, window, circle, circleAttack, BoardWhite, W_Rook1, W_Rook2, 'W', Black);
		}
		else if (Player == 2)
		{
			PutCircles(Black, window, circle, circleAttack, BoardBlack, B_Rook1, B_Rook2, 'B', White);
		}

		window.draw(WinText);

		window.draw(LoseText);

		window.draw(DrawText);

		window.draw(HelpButton);

		if (HelpSelected)
		{
			window.draw(HelpText);
		}

		window.display();
	}


	return 0;
}




