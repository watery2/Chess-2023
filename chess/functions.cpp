#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pieces.h"
#include "functions.h"


// Nustato kad visi vienos spalvos selecter bool butu false ir pajudina kvadrata ten kur zmogus jo nematys
void DeSelect(Piece** PieceList, sf::RectangleShape& rect)
{
	for (int i = 0; i < 16; i++)
	{
		PieceList[i]->selected = false;
	}

	rect.setPosition(sf::Vector2f(-300, 0));
}

// Padeda visas figuras i savo vietas
void SetupBoard(Piece** White, Piece** Black, int Player)
{
	for (int i = 0; i < 16; i++)
	{
		Black[i]->dead = false;

		Black[i]->FirstMove = true;
	}

	for (int i = 8; i < 16; i++)
	{
		if (Black[i]->Type != "pawn")
		{
			Black[i]->Type = "pawn";

			Black[i]->SetTexture("img/pawnB.png");
		}
	}

	for (int j = 0; j < 16; j++)
	{
		White[j]->dead = false;

		White[j]->FirstMove = true;
	}

	for (int j = 8; j < 16; j++)
	{
		if (White[j]->Type != "pawn")
		{
			White[j]->Type = "pawn";

			White[j]->SetTexture("img/pawnW.png");
		}
	}

	if (Player == 1)
	{

		Black[0]->SetLocation(sf::Vector2f(50, 50));

		Black[1]->SetLocation(sf::Vector2f(150, 50));

		Black[2]->SetLocation(sf::Vector2f(250, 50));

		Black[3]->SetLocation(sf::Vector2f(350, 50));

		Black[4]->SetLocation(sf::Vector2f(450, 50));

		Black[5]->SetLocation(sf::Vector2f(550, 50));

		Black[6]->SetLocation(sf::Vector2f(650, 50));

		Black[7]->SetLocation(sf::Vector2f(750, 50));

		Black[8]->SetLocation(sf::Vector2f(50, 150));

		Black[9]->SetLocation(sf::Vector2f(150, 150));

		Black[10]->SetLocation(sf::Vector2f(250, 150));

		Black[11]->SetLocation(sf::Vector2f(350, 150));

		Black[12]->SetLocation(sf::Vector2f(450, 150));

		Black[13]->SetLocation(sf::Vector2f(550, 150));

		Black[14]->SetLocation(sf::Vector2f(650, 150));

		Black[15]->SetLocation(sf::Vector2f(750, 150));

		/////////////////////////////////////////////

		White[0]->SetLocation(sf::Vector2f(50, 750));

		White[1]->SetLocation(sf::Vector2f(150, 750));

		White[2]->SetLocation(sf::Vector2f(250, 750));

		White[3]->SetLocation(sf::Vector2f(350, 750));

		White[4]->SetLocation(sf::Vector2f(450, 750));

		White[5]->SetLocation(sf::Vector2f(550, 750));

		White[6]->SetLocation(sf::Vector2f(650, 750));

		White[7]->SetLocation(sf::Vector2f(750, 750));

		White[8]->SetLocation(sf::Vector2f(50, 650));

		White[9]->SetLocation(sf::Vector2f(150, 650));

		White[10]->SetLocation(sf::Vector2f(250, 650));

		White[11]->SetLocation(sf::Vector2f(350, 650));

		White[12]->SetLocation(sf::Vector2f(450, 650));

		White[13]->SetLocation(sf::Vector2f(550, 650));

		White[14]->SetLocation(sf::Vector2f(650, 650));

		White[15]->SetLocation(sf::Vector2f(750, 650));

	}
	else
	{
		Black[0]->SetLocation(sf::Vector2f(50, 750));

		Black[1]->SetLocation(sf::Vector2f(150, 750));

		Black[2]->SetLocation(sf::Vector2f(250, 750));

		Black[3]->SetLocation(sf::Vector2f(450, 750));

		Black[4]->SetLocation(sf::Vector2f(350, 750));

		Black[5]->SetLocation(sf::Vector2f(550, 750));

		Black[6]->SetLocation(sf::Vector2f(650, 750));

		Black[7]->SetLocation(sf::Vector2f(750, 750));

		Black[8]->SetLocation(sf::Vector2f(50, 650));

		Black[9]->SetLocation(sf::Vector2f(150, 650));

		Black[10]->SetLocation(sf::Vector2f(250, 650));

		Black[11]->SetLocation(sf::Vector2f(350, 650));

		Black[12]->SetLocation(sf::Vector2f(450, 650));

		Black[13]->SetLocation(sf::Vector2f(550, 650));

		Black[14]->SetLocation(sf::Vector2f(650, 650));

		Black[15]->SetLocation(sf::Vector2f(750, 650));

		/////////////////////////////////////////////

		White[0]->SetLocation(sf::Vector2f(50, 50));

		White[1]->SetLocation(sf::Vector2f(150, 50));

		White[2]->SetLocation(sf::Vector2f(250, 50));

		White[3]->SetLocation(sf::Vector2f(450, 50));

		White[4]->SetLocation(sf::Vector2f(350, 50));

		White[5]->SetLocation(sf::Vector2f(550, 50));

		White[6]->SetLocation(sf::Vector2f(650, 50));

		White[7]->SetLocation(sf::Vector2f(750, 50));

		White[8]->SetLocation(sf::Vector2f(50, 150));

		White[9]->SetLocation(sf::Vector2f(150, 150));

		White[10]->SetLocation(sf::Vector2f(250, 150));

		White[11]->SetLocation(sf::Vector2f(350, 150));

		White[12]->SetLocation(sf::Vector2f(450, 150));

		White[13]->SetLocation(sf::Vector2f(550, 150));

		White[14]->SetLocation(sf::Vector2f(650, 150));

		White[15]->SetLocation(sf::Vector2f(750, 150));
	}
}

// Padeda taskas ten kur figura gali eiti, Apskritimas ten kur galima kirsti

void PutCircles(Piece** PieceList, sf::RenderWindow& window, sf::CircleShape& circle, sf::CircleShape& circleAttack, std::string Board[][8], Piece Rook1, Piece Rook2, char PieceColor, Piece** EnemyPieceList)
{
	int X;

	int Y;

	int oldX;

	int oldY;

	std::string CopyBoard[8][8];

	// PieceList[4] == King

	for (int i = 0; i < 16; i++)
	{
		if (PieceList[i]->selected)
		{
			X = PieceList[i]->GetLocation().x;

			Y = PieceList[i]->GetLocation().y;

			oldX = PieceList[i]->GetLocation().x;

			oldY = PieceList[i]->GetLocation().y;

			if (PieceList[i]->Type == "pawn")
			{
				if (PieceList[i]->FirstMove)
				{
					for (int j = 1; j <= 2; j++)
					{
						Y -= 100;

						if (Y < 0)
						{
							break;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}

						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circle.setPosition(sf::Vector2f(X, Y));

							window.draw(circle);
						}

					}
				}
				else if (!PieceList[i]->FirstMove)
				{
					Y -= 100;

					if (Y > 0)
					{
						if (Board[Y / 100][X / 100] == "XxX")
						{
							if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
							{
								circle.setPosition(sf::Vector2f(X, Y));

								window.draw(circle);
							}
						}
					}
				}

				X = oldX;

				Y = oldY;

				if (Y - 100 > 0 && X - 100 > 0)
				{
					if (Board[(Y - 100) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0] && Board[(Y - 100) / 100][(X - 100) / 100] != "XxX")
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y - 100, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X - 100, Y - 100));

							window.draw(circleAttack);
						}
					}
					else if (Board[Y / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0] && Board[(Y - 100) / 100][(X - 100) / 100] == "XxX" && Board[Y / 100][(X - 100) / 100][1] == 'P')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y - 100, PieceList[4]->GetLocation(), PieceColor))
						{
							for (int i = 8; i < 16; i++)
							{
								if (EnemyPieceList[i]->GetLocation() == sf::Vector2f(X - 100, Y) && EnemyPieceList[i]->PawnJustMoved2Spaces)
								{
									circleAttack.setPosition(sf::Vector2f(X - 100, Y - 100));

									window.draw(circleAttack);
								}
							}
						}
						
					}
				}

				if (Y - 100 > 0 && X + 100 < 800)
				{
					if (Board[(Y - 100) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0] && Board[(Y - 100) / 100][(X + 100) / 100] != "XxX")
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y - 100, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X + 100, Y - 100));

							window.draw(circleAttack);
						}
					}
					else if (Board[Y / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0] && Board[(Y - 100) / 100][(X + 100) / 100] == "XxX" && Board[Y / 100][(X + 100) / 100][1] == 'P')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y - 100, PieceList[4]->GetLocation(), PieceColor))
						{
							for (int i = 8; i < 16; i++)
							{
								if (EnemyPieceList[i]->GetLocation() == sf::Vector2f(X + 100, Y) && EnemyPieceList[i]->PawnJustMoved2Spaces)
								{
									circleAttack.setPosition(sf::Vector2f(X + 100, Y - 100));

									window.draw(circleAttack);
								}
							}
						}

					}
				}
			}
			else if (PieceList[i]->Type == "bishop")
			{
				while (X > 50 && Y > 50)
				{
					X -= 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}

				}

				X = oldX;

				Y = oldY;

				while (X < 750 && Y > 50)
				{
					X += 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}

				}

				X = oldX;

				Y = oldY;

				while (X > 50 && Y < 750)
				{
					X -= 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}

				}

				X = oldX;

				Y = oldY;

				while (X < 700 && Y < 750)
				{
					X += 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}

				}

			}
			else if (PieceList[i]->Type == "knight")
			{
				if (X - 200 > 0 && Y - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 200, Y - 100, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y - 100) / 100][(X - 200) / 100] == "XxX" && X - 200 > 0)
						{
							circle.setPosition(sf::Vector2f(X - 200, Y - 100));

							window.draw(circle);
						}
						else if (Board[(Y - 100) / 100][(X - 200) / 100] != "XxX" && Board[(Y - 100) / 100][(X - 200) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X - 200, Y - 100));

							window.draw(circleAttack);
						}
					}
				}

				if (X - 200 > 0 && Y + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 200, Y + 100, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y + 100) / 100][(X - 200) / 100] == "XxX" && X - 200 > 0)
						{
							circle.setPosition(sf::Vector2f(X - 200, Y + 100));

							window.draw(circle);
						}
						else if (Board[(Y + 100) / 100][(X - 200) / 100] != "XxX" && Board[(Y + 100) / 100][(X - 200) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X - 200, Y + 100));

							window.draw(circleAttack);
						}
					}
				}

				if (X + 200 < 800 && Y - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 200, Y - 100, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y - 100) / 100][(X + 200) / 100] == "XxX" && X + 200 < 800)
						{
							circle.setPosition(sf::Vector2f(X + 200, Y - 100));

							window.draw(circle);
						}
						else if (Board[(Y - 100) / 100][(X + 200) / 100] != "XxX" && Board[(Y - 100) / 100][(X + 200) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X + 200, Y - 100));

							window.draw(circleAttack);
						}
					}
				}

				if (X + 200 < 800 && Y + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 200, Y + 100, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y + 100) / 100][(X + 200) / 100] == "XxX" && X + 200 < 800)
						{
							circle.setPosition(sf::Vector2f(X + 200, Y + 100));

							window.draw(circle);
						}
						else if (Board[(Y + 100) / 100][(X + 200) / 100] != "XxX" && Board[(Y + 100) / 100][(X + 200) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X + 200, Y + 100));

							window.draw(circleAttack);
						}
					}
				}

				if (Y - 200 > 0 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y - 200, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y - 200) / 100][(X - 100) / 100] == "XxX" && Y - 200 > 0)
						{
							circle.setPosition(sf::Vector2f(X - 100, Y - 200));

							window.draw(circle);
						}
						else if (Board[(Y - 200) / 100][(X - 100) / 100] != "XxX" && Board[(Y - 200) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X - 100, Y - 200));

							window.draw(circleAttack);
						}
					}
				}

				if (Y - 200 > 0 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y - 200, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y - 200) / 100][(X + 100) / 100] == "XxX" && Y - 200 > 0)
						{
							circle.setPosition(sf::Vector2f(X + 100, Y - 200));

							window.draw(circle);
						}
						else if (Board[(Y - 200) / 100][(X + 100) / 100] != "XxX" && Board[(Y - 200) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X + 100, Y - 200));

							window.draw(circleAttack);
						}
					}
				}

				if (Y + 200 < 800 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y + 200, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y + 200) / 100][(X - 100) / 100] == "XxX" && Y + 200 < 800)
						{
							circle.setPosition(sf::Vector2f(X - 100, Y + 200));

							window.draw(circle);
						}
						else if (Board[(Y + 200) / 100][(X - 100) / 100] != "XxX" && Board[(Y + 200) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X - 100, Y + 200));

							window.draw(circleAttack);
						}
					}
				}

				if (Y + 200 < 800 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y + 200, PieceList[4]->GetLocation(), PieceColor))
					{
						if (Board[(Y + 200) / 100][(X + 100) / 100] == "XxX" && Y + 200 < 800)
						{
							circle.setPosition(sf::Vector2f(X + 100, Y + 200));

							window.draw(circle);
						}
						else if (Board[(Y + 200) / 100][(X + 100) / 100] != "XxX" && Board[(Y + 200) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X + 100, Y + 200));

							window.draw(circleAttack);
						}
					}
				}
			}
			else if (PieceList[i]->Type == "rook")
			{
				while (Y > 50)
				{
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				Y = oldY;

				while (Y < 750)
				{
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				Y = oldY;

				while (X > 50)
				{
					X -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				X = oldX;

				while (X < 700)
				{
					X += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}
			}
			else if (PieceList[i]->Type == "queen")
			{
				while (X > 50 && Y > 50)
				{
					X -= 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 750 && Y > 50)
				{
					X += 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				X = oldX;

				Y = oldY;

				while (X > 50 && Y < 750)
				{
					X -= 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 700 && Y < 750)
				{
					X += 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				X = oldX;

				Y = oldY;

				while (Y > 50)
				{
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				Y = oldY;

				while (Y < 750)
				{
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				X = oldX;

				Y = oldY;

				while (X > 50)
				{
					X -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 700)
				{
					X += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0] && Board[Y / 100][X / 100][0] != 'X')
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
						{
							circleAttack.setPosition(sf::Vector2f(X, Y));

							window.draw(circleAttack);
						}

						break;
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}

					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, PieceList[4]->GetLocation(), PieceColor))
					{
						circle.setPosition(sf::Vector2f(X, Y));

						window.draw(circle);
					}
				}

			}
			else if (PieceList[i]->Type == "king")
			{
				if (Y - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y - 100, sf::Vector2f(X, Y - 100), PieceColor))
					{
						if (Board[(Y - 100) / 100][X / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X, Y - 100));

							window.draw(circle);
						}
						else if (Board[(Y - 100) / 100][X / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X, Y - 100));

							window.draw(circleAttack);
						}
					}
				}

				if (Y - 100 > 0 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y - 100, sf::Vector2f(X - 100, Y - 100), PieceColor))
					{
						if (Board[(Y - 100) / 100][(X - 100) / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X - 100, Y - 100));

							window.draw(circle);
						}
						else if (Board[(Y - 100) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X - 100, Y - 100));

							window.draw(circleAttack);
						}
					}
				}

				if (X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y, sf::Vector2f(X - 100, Y), PieceColor))
					{
						if (Board[Y / 100][(X - 100) / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X - 100, Y));

							window.draw(circle);
						}
						else if (Board[Y / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X - 100, Y));

							window.draw(circleAttack);
						}
					}

					if (PieceList[i]->FirstMove && Rook1.FirstMove && !CheckIfPlayerPieceIsUnderAttackOrProtected(Board, PieceList[4]->GetLocation(), PieceColor))
					{
						if (PieceList[i]->CanThePieceMove(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, Rook1.GetLocation().x + 100, Rook1.GetLocation().y, Board))
						{
							CopyBoardToAnothereArray(Board, CopyBoard);

							MovePieceOnBoard(CopyBoard, Rook1.GetLocation().x, Rook1.GetLocation().y, X - 100, Rook1.GetLocation().y);

							MovePieceOnBoard(CopyBoard, PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, X - 200, PieceList[i]->GetLocation().y);

							if (!CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, sf::Vector2f(X - 200, Y), PieceColor))
							{
								circle.setPosition(sf::Vector2f(X - 200, Y));

								window.draw(circle);
							}
						}
					}
				}

				if (Y + 100 < 800 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y + 100, sf::Vector2f(X - 100, Y + 100), PieceColor))
					{
						if (Board[(Y + 100) / 100][(X - 100) / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X - 100, Y + 100));

							window.draw(circle);
						}
						else if (Board[(Y + 100) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X - 100, Y + 100));

							window.draw(circleAttack);
						}
					}
				}

				if (Y + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y + 100, sf::Vector2f(X, Y + 100), PieceColor))
					{
						if (Board[(Y + 100) / 100][X / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X, Y + 100));

							window.draw(circle);
						}
						else if (Board[(Y + 100) / 100][X / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X, Y + 100));

							window.draw(circleAttack);
						}
					}
				}

				if (Y + 100 < 800 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y + 100, sf::Vector2f(X + 100, Y + 100), PieceColor))
					{
						if (Board[(Y + 100) / 100][(X + 100) / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X + 100, Y + 100));

							window.draw(circle);
						}
						else if (Board[(Y + 100) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X + 100, Y + 100));

							window.draw(circleAttack);
						}
					}
				}

				if (X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y, sf::Vector2f(X + 100, Y), PieceColor))
					{
						if (Board[Y / 100][(X + 100) / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X + 100, Y));

							window.draw(circle);
						}
						else if (Board[Y / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X + 100, Y));

							window.draw(circleAttack);
						}
					}

					if (PieceList[i]->FirstMove && Rook2.FirstMove && !CheckIfPlayerPieceIsUnderAttackOrProtected(Board, PieceList[4]->GetLocation(), PieceColor))
					{
						if (PieceList[i]->CanThePieceMove(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, Rook2.GetLocation().x - 100, Rook2.GetLocation().y, Board))
						{
							CopyBoardToAnothereArray(Board, CopyBoard);

							MovePieceOnBoard(CopyBoard, Rook2.GetLocation().x, Rook2.GetLocation().y, X + 100, Rook2.GetLocation().y);

							MovePieceOnBoard(CopyBoard, PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, X + 200, PieceList[i]->GetLocation().y);

							if (!CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, sf::Vector2f(X + 200, Y), PieceColor))
							{
								circle.setPosition(sf::Vector2f(X + 200, Y));

								window.draw(circle);
							}
						}
					}
				}

				if (Y - 100 > 0 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y - 100, sf::Vector2f(X + 100, Y - 100), PieceColor))
					{
						if (Board[(Y - 100) / 100][(X + 100) / 100] == "XxX")
						{
							circle.setPosition(sf::Vector2f(X + 100, Y - 100));

							window.draw(circle);
						}
						else if (Board[(Y - 100) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							circleAttack.setPosition(sf::Vector2f(X + 100, Y - 100));

							window.draw(circleAttack);
						}
					}
				}

			}
		}
	}

	circle.setPosition(sf::Vector2f(-300, 0));

	circleAttack.setPosition(sf::Vector2f(-300, 0));

	window.draw(circle);

	window.draw(circleAttack);

}

// Ismeta pasirinkima i kuri gali pestinkas but paukstintas

void DrawPromotionPieces(sf::RenderWindow& window, Piece** PieceList, Piece Queen, Piece Knight, Piece Rook, Piece Bishop)
{
	for (int i = 8; i < 16; i++)
	{
		if (PieceList[i]->BeingPromoted)
		{
			Queen.SetLocation(sf::Vector2f(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y + 100));

			window.draw(Queen.GetSprite());

			Knight.SetLocation(sf::Vector2f(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y + 200));

			window.draw(Knight.GetSprite());

			Rook.SetLocation(sf::Vector2f(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y + 300));

			window.draw(Rook.GetSprite());

			Bishop.SetLocation(sf::Vector2f(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y + 400));

			window.draw(Bishop.GetSprite());

		}
	}
}

// Paspaudus ant vieno is paukstinimo pasirinkimo pavercia pestininka i ta pasirinkima

void PromotePawnIfClicked(sf::Vector2f Mouse, Piece** PieceList, char PieceColor, bool& PawnGonnaBePromoted, std::string Board[][8])
{
	for (int i = 8; i < 16; i++)
	{
		if (PieceList[i]->BeingPromoted)
		{
			if (sqrt(pow(Mouse.x - PieceList[i]->GetLocation().x, 2) + pow(Mouse.y - (PieceList[i]->GetLocation().y + 100), 2)) <= 50)
			{
				if (PieceColor == 'W')
				{
					PieceList[i]->SetTexture("img/queenW.png");
				}
				else if (PieceColor == 'B')
				{
					PieceList[i]->SetTexture("img/queenB.png");
				}

				PieceList[i]->Type = "queen";

				PieceList[i]->BeingPromoted = false;

				PawnGonnaBePromoted = false;

				Board[int(PieceList[i]->GetLocation().y) / 100][int(PieceList[i]->GetLocation().x) / 100][1] = 'Q';
			}
			else if (sqrt(pow(Mouse.x - PieceList[i]->GetLocation().x, 2) + pow(Mouse.y - (PieceList[i]->GetLocation().y + 200), 2)) <= 50)
			{
				if (PieceColor == 'W')
				{
					PieceList[i]->SetTexture("img/kniW.png");
				}
				else if (PieceColor == 'B')
				{
					PieceList[i]->SetTexture("img/kniB.png");
				}

				PieceList[i]->Type = "knight";

				PieceList[i]->BeingPromoted = false;

				PawnGonnaBePromoted = false;

				Board[int(PieceList[i]->GetLocation().y) / 100][int(PieceList[i]->GetLocation().x) / 100][1] = 'K';
			}
			else if (sqrt(pow(Mouse.x - PieceList[i]->GetLocation().x, 2) + pow(Mouse.y - (PieceList[i]->GetLocation().y + 300), 2)) <= 50)
			{
				if (PieceColor == 'W')
				{
					PieceList[i]->SetTexture("img/towW.png");
				}
				else if (PieceColor == 'B')
				{
					PieceList[i]->SetTexture("img/towB.png");
				}

				PieceList[i]->Type = "rook";

				PieceList[i]->BeingPromoted = false;

				PawnGonnaBePromoted = false;

				Board[int(PieceList[i]->GetLocation().y) / 100][int(PieceList[i]->GetLocation().x) / 100][1] = 'R';
			}
			else if (sqrt(pow(Mouse.x - PieceList[i]->GetLocation().x, 2) + pow(Mouse.y - (PieceList[i]->GetLocation().y + 400), 2)) <= 50)
			{
				if (PieceColor == 'W')
				{
					PieceList[i]->SetTexture("img/bishW.png");
				}
				else if (PieceColor == 'B')
				{
					PieceList[i]->SetTexture("img/bishB.png");
				}

				PieceList[i]->Type = "bishop";

				PieceList[i]->BeingPromoted = false;

				PawnGonnaBePromoted = false;

				Board[int(PieceList[i]->GetLocation().y) / 100][int(PieceList[i]->GetLocation().x) / 100][1] = 'B';
			}
		}
	}
}

// Jei toi vietoi yra prieso figura, tai ji nukertama

void RemoveEnemyPieceIfPossible(Piece** PieceList, sf::Vector2f Location)
{
	for (int i = 0; i < 16; i++)
	{
		if (!PieceList[i]->dead && PieceList[i]->GetLocation().x == Location.x && PieceList[i]->GetLocation().y == Location.y)
		{
			PieceList[i]->SetLocation(sf::Vector2f(-300, 0));

			PieceList[i]->dead = true;
		}
	}
}

// Nukopijuoja Lentos masyva i kita masyva

void CopyBoardToAnothereArray(std::string Board[][8], std::string CopyBoard[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			CopyBoard[i][j] = Board[i][j];
		}
	}
}

// pajudina figura ant lentos

void MovePieceOnBoard(std::string Board[][8], int OldX, int OldY, int NewX, int NewY)
{
	Board[NewY / 100][NewX / 100] = Board[OldY / 100][OldX / 100];

	Board[OldY / 100][OldX / 100] = "XxX";
}

// side = 1 == kaire
// side = 2 == desine
// side = 12 == abipuses

int CheckIfPawnCanAttack(std::string Board[][8], sf::Vector2f location, char PieceColor)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	int side = 0;

	if (X - 100 > 0 && Y + 100 < 800)
	{
		X -= 100;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != PieceColor)
		{
			side = 1;
		}
	}

	X = location.x;

	Y = location.y;

	if (X + 100 < 800 && Y + 100 < 800)
	{
		X += 100;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != PieceColor)
		{
			if (side == 0)
			{
				side = 2;
			}
			else
			{
				side = 12;
			}
		}
	}

	return side;
}

// Ziuri ar figura puola Zirgas, ne zaidejui

bool CheckIfPieceIsUnderAttackByPawn(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	if (X - 100 > 0 && Y + 100 < 800)
	{
		X -= 100;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'P')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X + 100 < 800 && Y + 100 < 800)
	{
		X += 100;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'P')
		{
			return true;
		}
	}

	return false;
}

// Ziuri ar figura puola arba apsaugo Zirgas

bool CheckIfPieceIsUnderAttackOrProtectedByKnight(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	if (X - 200 > 0 && Y - 100 > 0)
	{
		X -= 200;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X - 200 > 0 && Y + 100 < 800)
	{
		X -= 200;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X + 200 < 800 && Y - 100 > 0)
	{
		X += 200;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X + 200 < 800 && Y + 100 < 800)
	{
		X += 200;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (Y - 200 > 0 && X - 100 > 0)
	{
		X -= 100;

		Y -= 200;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (Y - 200 > 0 && X + 100 < 800)
	{
		X += 100;

		Y -= 200;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (Y + 200 < 800 && X - 100 > 0)
	{
		X -= 100;

		Y += 200;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (Y + 200 < 800 && X + 100 < 800)
	{
		X += 100;

		Y += 200;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] != 'I')
		{
			return true;
		}
	}


	return false;
}

// Ziuris ar figura puola arba apsaugo Karalius

bool CheckIfPieceIsUnderAttackOrProtectedByKing(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	if (Y - 100 > 0)
	{
		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}
	}

	Y = location.y;

	if (Y - 100 > 0 && X - 100 > 0)
	{
		X -= 100;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X - 100 > 0)
	{
		X -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}
	}

	X = location.x;

	if (Y + 100 < 800 && X - 100 > 0)
	{
		X -= 100;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (Y + 100 < 800)
	{
		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}
	}

	Y = location.y;

	if (Y + 100 < 800 && X + 100 < 800)
	{
		X += 100;

		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X + 100 < 800)
	{
		X += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}
	}

	X = location.x;

	if (Y - 100 > 0 && X + 100 < 800)
	{
		X += 100;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'K' && Board[Y / 100][X / 100][2] == 'I')
		{
			return true;
		}

	}

	return false;
}

// Ziuris ar figura puola arba apsaugo Bokstas

bool CheckIfPieceIsUnderAttackOrProtectedByRook(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	while (Y > 50)
	{
		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'R')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	Y = location.y;

	while (Y < 750)
	{
		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'R')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	Y = location.y;

	while (X > 50)
	{
		X -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'R')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	X = location.x;

	while (X < 700)
	{
		X += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'R')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	return false;
}

// Ziuris ar figura puola arba apsaugo Rikis

bool CheckIfPieceIsUnderAttackOrProtectedByBishop(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	while (X > 50 && Y > 50)
	{
		X -= 100;
		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'B')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	X = location.x;

	Y = location.y;

	while (X < 750 && Y > 50)
	{
		X += 100;
		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'B')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	X = location.x;

	Y = location.y;

	while (X < 750 && Y < 750)
	{
		X += 100;
		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'B')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	X = location.x;

	Y = location.y;

	while (X > 50 && Y < 750)
	{
		X -= 100;
		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'B')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	return false;
}

// Ziuris ar figura puola arba apsaugo Karaliene

bool CheckIfPieceIsUnderAttackOrProtectedByQueen(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	while (Y > 50)
	{
		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	Y = location.y;

	while (Y < 750)
	{
		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	Y = location.y;

	while (X > 50)
	{
		X -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	X = location.x;

	while (X < 700)
	{
		X += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	X = location.x;

	while (X > 50 && Y > 50)
	{
		X -= 100;
		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	X = location.x;

	Y = location.y;

	while (X < 750 && Y > 50)
	{
		X += 100;
		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	X = location.x;

	Y = location.y;

	while (X < 700 && Y < 700)
	{
		X += 100;
		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	X = location.x;

	Y = location.y;

	while (X > 50 && Y < 750)
	{
		X -= 100;
		Y += 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'Q')
		{
			return true;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}

	}

	return false;
}

// Ziuris ar figura puola, 

bool CheckIfPieceIsUnderAttack(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	float x = location.x;

	float y = location.y;

	return CheckIfPieceIsUnderAttackByPawn(Board, sf::Vector2f(x, y), ColorToIgnore) || CheckIfPieceIsUnderAttackOrProtectedByKnight(Board, sf::Vector2f(x, y), ColorToIgnore) || CheckIfPieceIsUnderAttackOrProtectedByKing(Board, sf::Vector2f(x, y), ColorToIgnore) || CheckIfPieceIsUnderAttackOrProtectedByRook(Board, sf::Vector2f(x, y), ColorToIgnore) || CheckIfPieceIsUnderAttackOrProtectedByBishop(Board, sf::Vector2f(x, y), ColorToIgnore) || CheckIfPieceIsUnderAttackOrProtectedByQueen(Board, sf::Vector2f(x, y), ColorToIgnore);
}

// Pajudina figura ant lentos ir ziuri ar boto karalius yra puolamas, ne zaidejui

bool CheckIfTheKingIsCheckedAfterAMove(std::string Board[][8], int OldX, int OldY, int NewX, int NewY, sf::Vector2f KingsLocation, char PieceColor)
{
	std::string CopyBoard[8][8];

	CopyBoardToAnothereArray(Board, CopyBoard);

	MovePieceOnBoard(CopyBoard, OldX, OldY, NewX, NewY);

	if (CheckIfPieceIsUnderAttack(CopyBoard, KingsLocation, PieceColor))
	{
		return true;
	}

	return false;
}

// Ziuri ar figura apsaugo pestininkas, ne zaidejui

bool CheckIfPieceIsProtectedByPawn(std::string Board[][8], sf::Vector2f location, char PieceColor)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	if (X - 100 > 0 && Y - 100 > 0)
	{
		X -= 100;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] == PieceColor && Board[Y / 100][X / 100][1] == 'P')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X + 100 < 800 && Y - 100 > 0)
	{
		X += 100;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] == PieceColor && Board[Y / 100][X / 100][1] == 'P')
		{
			return true;
		}
	}

	return false;
}

// Ziuri ar figura apsaugota, ne zaidejui

bool CheckIfPieceIsProtected(std::string Board[][8], sf::Vector2f location, char PieceColor)
{
	float x = location.x;

	float y = location.y;

	if (PieceColor == 'B')
	{
		return CheckIfPieceIsProtectedByPawn(Board, sf::Vector2f(x, y), 'B') || CheckIfPieceIsUnderAttackOrProtectedByKnight(Board, sf::Vector2f(x, y), 'W') || CheckIfPieceIsUnderAttackOrProtectedByKing(Board, sf::Vector2f(x, y), 'W') || CheckIfPieceIsUnderAttackOrProtectedByRook(Board, sf::Vector2f(x, y), 'W') || CheckIfPieceIsUnderAttackOrProtectedByBishop(Board, sf::Vector2f(x, y), 'W') || CheckIfPieceIsUnderAttackOrProtectedByQueen(Board, sf::Vector2f(x, y), 'W');
	}
	else if (PieceColor == 'W')
	{
		return CheckIfPieceIsProtectedByPawn(Board, sf::Vector2f(x, y), 'W') || CheckIfPieceIsUnderAttackOrProtectedByKnight(Board, sf::Vector2f(x, y), 'B') || CheckIfPieceIsUnderAttackOrProtectedByKing(Board, sf::Vector2f(x, y), 'B') || CheckIfPieceIsUnderAttackOrProtectedByRook(Board, sf::Vector2f(x, y), 'B') || CheckIfPieceIsUnderAttackOrProtectedByBishop(Board, sf::Vector2f(x, y), 'B') || CheckIfPieceIsUnderAttackOrProtectedByQueen(Board, sf::Vector2f(x, y), 'B');
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ziuri ar zaidejo figura puola pestininkas

bool CheckIfPlayerPieceIsUnderAttackedByPawn(std::string Board[][8], sf::Vector2f location, char ColorToIgnore)
{
	int X;

	int Y;

	X = location.x;

	Y = location.y;

	if (X - 100 > 0 && Y - 100 > 0)
	{
		X -= 100;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'P')
		{
			return true;
		}
	}

	X = location.x;

	Y = location.y;

	if (X + 100 < 800 && Y - 100 > 0)
	{
		X += 100;

		Y -= 100;

		if (Board[Y / 100][X / 100] != "XxX" && Board[Y / 100][X / 100][0] != ColorToIgnore && Board[Y / 100][X / 100][1] == 'P')
		{
			return true;
		}
	}

	return false;
}

// Ziuri ar zaidejo figura yra puolama arba apsaugoma

bool CheckIfPlayerPieceIsUnderAttackOrProtected(std::string Board[][8], sf::Vector2f location, char PieceColor)
{
	float x = location.x;

	float y = location.y;

	return CheckIfPlayerPieceIsUnderAttackedByPawn(Board, sf::Vector2f(x, y), PieceColor) || CheckIfPieceIsUnderAttackOrProtectedByBishop(Board, sf::Vector2f(x, y), PieceColor) || CheckIfPieceIsUnderAttackOrProtectedByRook(Board, sf::Vector2f(x, y), PieceColor) || CheckIfPieceIsUnderAttackOrProtectedByKing(Board, sf::Vector2f(x, y), PieceColor) || CheckIfPieceIsUnderAttackOrProtectedByKnight(Board, sf::Vector2f(x, y), PieceColor) || CheckIfPieceIsUnderAttackOrProtectedByQueen(Board, sf::Vector2f(x, y), PieceColor);

}

// Pajudina figura ant lentos ir ziuri ar zaidejaus karalius yra puolamas

bool CheckIfThePlayerKingIsCheckedAfterAMove(std::string Board[][8], int OldX, int OldY, int NewX, int NewY, sf::Vector2f KingsLocation, char PieceColor)
{
	std::string CopyBoard[8][8];

	CopyBoardToAnothereArray(Board, CopyBoard);

	MovePieceOnBoard(CopyBoard, OldX, OldY, NewX, NewY);

	if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, KingsLocation, PieceColor))
	{
		return true;
	}

	return false;
}

// Ziuri ar zaidejus pralaimejo

bool KingCheckMated(Piece** PieceList, std::string Board[][8], Piece Rook1, Piece Rook2, sf::Vector2f KingLocation, char PieceColor)
{
	int X;

	int Y;

	int oldX;

	int oldY;

	std::string CopyBoard[8][8];

	for (int i = 0; i < 16; i++)
	{
		if (!PieceList[i]->dead)
		{
			
			X = PieceList[i]->GetLocation().x;

			Y = PieceList[i]->GetLocation().y;

			oldX = PieceList[i]->GetLocation().x;

			oldY = PieceList[i]->GetLocation().y;
			
			if (PieceList[i]->Type == "pawn")
			{
				if (PieceList[i]->FirstMove)
				{
					for (int j = 1; j <= 2; j++)
					{
						Y -= 100;

						if (Y < 0)
						{
							break;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}

						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

					}
				}
				else if (!PieceList[i]->FirstMove)
				{
					Y -= 100;

					if (Y > 0)
					{
						if (Board[Y / 100][X / 100] == "XxX")
						{
							if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
							{
								return false;
							}
						}
					}
				}

				X = oldX;

				Y = oldY;

				if (Y - 100 > 0 && X - 100 > 0)
				{
					if (Board[(Y - 100) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0] && Board[(Y - 100) / 100][(X - 100) / 100] != "XxX")
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y - 100, KingLocation, PieceColor))
						{
							return false;
						}
					}
				}

				if (Y - 100 > 0 && X + 100 < 800)
				{
					if (Board[(Y - 100) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0] && Board[(Y - 100) / 100][(X + 100) / 100] != "XxX")
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y - 100, KingLocation, PieceColor))
						{
							return false;
						}
					}
				}
			}
			else if (PieceList[i]->Type == "bishop")
			{
				while (X > 50 && Y > 50)
				{
					X -= 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 750 && Y > 50)
				{
					X += 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X > 50 && Y < 750)
				{
					X -= 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 700 && Y < 750)
				{
					X += 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

			}
			else if (PieceList[i]->Type == "knight")
			{
				if (X - 200 > 0 && Y - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 200, Y - 100, KingLocation, PieceColor))
					{
						if (Board[(Y - 100) / 100][(X - 200) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}

				if (X - 200 > 0 && Y + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 200, Y + 100, KingLocation, PieceColor))
					{
						if (Board[(Y + 100) / 100][(X - 200) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}

				if (X + 200 < 800 && Y - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 200, Y - 100, KingLocation, PieceColor))
					{
						if (Board[(Y - 100) / 100][(X + 200) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}

				if (X + 200 < 800 && Y + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 200, Y + 100, KingLocation, PieceColor))
					{
						if (Board[(Y + 100) / 100][(X + 200) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}

				if (Y - 200 > 0 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y - 200, KingLocation, PieceColor))
					{
						if (Board[(Y - 200) / 100][(X - 100) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}

				if (Y - 200 > 0 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y - 200, KingLocation, PieceColor))
					{
						if (Board[(Y - 200) / 100][(X + 100) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}

				if (Y + 200 < 800 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y + 200, KingLocation, PieceColor))
					{
						if (Board[(Y + 200) / 100][(X - 100) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}

				if (Y + 200 < 800 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y + 200, KingLocation, PieceColor))
					{
						if (Board[(Y + 200) / 100][(X + 100) / 100][0] != PieceColor)
						{
							return false;
						}

					}
				}
			}
			else if (PieceList[i]->Type == "rook")
			{
				while (Y > 50)
				{
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				Y = oldY;

				while (Y < 750)
				{
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				Y = oldY;

				while (X > 50)
				{
					X -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				while (X < 700)
				{
					X += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}
			}
			else if (PieceList[i]->Type == "queen")
			{
				while (X > 50 && Y > 50)
				{
					X -= 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 750 && Y > 50)
				{
					X += 100;
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X > 50 && Y < 750)
				{
					X -= 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 700 && Y < 750)
				{
					X += 100;
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (Y > 50)
				{
					Y -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				Y = oldY;

				while (Y < 750)
				{
					Y += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X > 50)
				{
					X -= 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

				X = oldX;

				Y = oldY;

				while (X < 700)
				{
					X += 100;

					if (Board[Y / 100][X / 100][0] != Board[oldY / 100][oldX / 100][0])
					{
						if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y, KingLocation, PieceColor))
						{
							return false;
						}

						if (Board[Y / 100][X / 100] != "XxX")
						{
							break;
						}
					}
					else if (Board[Y / 100][X / 100] != "XxX")
					{
						break;
					}
				}

			}
			else if (PieceList[i]->Type == "king")
			{
				if (Y - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y - 100, sf::Vector2f(X, Y - 100), PieceColor))
					{
						if (Board[(Y - 100) / 100][X / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}
				}

				if (Y - 100 > 0 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y - 100, sf::Vector2f(X - 100, Y - 100), PieceColor))
					{
						if (Board[(Y - 100) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}
				}

				if (X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y, sf::Vector2f(X - 100, Y), PieceColor))
					{
						if (Board[Y / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}

					if (PieceList[i]->FirstMove && Rook1.FirstMove)
					{
						if (PieceList[i]->CanThePieceMove(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, Rook1.GetLocation().x, Rook1.GetLocation().y, Board))
						{
							CopyBoardToAnothereArray(Board, CopyBoard);

							MovePieceOnBoard(CopyBoard, Rook1.GetLocation().x, Rook1.GetLocation().y, X - 100, Rook1.GetLocation().y);

							MovePieceOnBoard(CopyBoard, PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, X - 200, PieceList[i]->GetLocation().y);

							if (!CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, sf::Vector2f(X - 200, Y), PieceColor))
							{
								return false;
							}
						}
					}
				}

				if (Y + 100 < 800 && X - 100 > 0)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X - 100, Y + 100, sf::Vector2f(X - 100, Y + 100), PieceColor))
					{
						if (Board[(Y + 100) / 100][(X - 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}
				}

				if (Y + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X, Y + 100, sf::Vector2f(X, Y + 100), PieceColor))
					{
						if (Board[(Y + 100) / 100][X / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}
				}

				if (Y + 100 < 800 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y + 100, sf::Vector2f(X + 100, Y + 100), PieceColor))
					{
						if (Board[(Y + 100) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}
				}

				if (X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y, sf::Vector2f(X + 100, Y), PieceColor))
					{
						if (Board[Y / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}

					if (PieceList[i]->FirstMove && Rook2.FirstMove)
					{
						if (PieceList[i]->CanThePieceMove(PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, Rook2.GetLocation().x, Rook2.GetLocation().y, Board))
						{
							CopyBoardToAnothereArray(Board, CopyBoard);

							MovePieceOnBoard(CopyBoard, Rook2.GetLocation().x, Rook2.GetLocation().y, X + 100, Rook2.GetLocation().y);

							MovePieceOnBoard(CopyBoard, PieceList[i]->GetLocation().x, PieceList[i]->GetLocation().y, X + 200, PieceList[i]->GetLocation().y);

							if (!CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, sf::Vector2f(X + 200, Y), PieceColor))
							{
								return false;
							}
						}
					}
				}

				if (Y - 100 > 0 && X + 100 < 800)
				{
					if (!CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, X + 100, Y - 100, sf::Vector2f(X + 100, Y - 100), PieceColor))
					{
						if (Board[(Y - 100) / 100][(X + 100) / 100][0] != Board[Y / 100][X / 100][0])
						{
							return false;
						}
					}
				}

			}
		}
	}

	return true;
}