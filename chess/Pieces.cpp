#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pieces.h"
#include "functions.h"

// Pajimti sprita

sf::Sprite Piece::GetSprite()
{
	return sprite;
}

// Pajimti positsija

sf::Vector2f Piece::GetLocation()
{
	return location;
}

// Nustatyti koki vaizda figura naudos

void Piece::SetTexture(std::string textureLocation)
{
	texture.loadFromFile(textureLocation);

	sprite.setTexture(texture);

	sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.5, sprite.getTexture()->getSize().y * 0.5));
}

// Nustatyti positsija

void Piece::SetLocation(sf::Vector2f SetLocation)
{
	location = SetLocation;

	sprite.setPosition(location);
}

// Konstruktorius

Piece::Piece(std::string textureLocation, sf::Vector2f Location, std::string type)
{
	SetTexture(textureLocation);

	SetLocation(Location);

	Type = type;
}

// Destruktorius

Piece::~Piece()
{

}

// Grazinti true jei figura yra paspausta

bool Piece::Clicked(sf::Vector2f Mouse)
{
	return sqrt(pow(Mouse.x - sprite.getPosition().x, 2) + pow(Mouse.y - sprite.getPosition().y, 2)) <= 50;
}

// Pajudinti kvadrata uz figuros

void Piece::HighlightPiece(sf::RectangleShape& rect, Piece** PieceList)
{
	if (!selected)
	{

		for (int i = 0; i < 16; i++)
		{
			PieceList[i]->selected = false;
		}

		selected = true;

		rect.setPosition(location);
	}
	else
	{
		selected = false;

		rect.setPosition(sf::Vector2f(-300, 0));
	}
}

// Pestininko ejimo funkcija

void Piece::MovePawn(sf::Vector2f Mouse , std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, bool& PawnGonnaBePromoted, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove)
{
	if (Type == "pawn" && selected)
	{
		float newX = location.x;

		float newY = location.y;

		int oldX = location.x;

		int oldY = location.y;

		int difranceX = 50;

		int difranceY = 50;

		if (Mouse.x - 50 < location.x && Mouse.x + 50 > location.x && Mouse.y < location.y)
		{
			difranceY += location.y - Mouse.y;

			difranceY /= 100;

			if (FirstMove && difranceY <= 2)
			{
				newY -= 100 * difranceY;

				if ((newX != location.x || newY != location.y) && CanThePieceMove(oldX, oldY, int(newX), int(newY), Board) && Board[int(newY) / 100][int(newX) / 100] == "XxX" && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
				{
					FirstMove = false;

					Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

					Board[oldY / 100][oldX / 100] = "XxX";

					if (difranceY == 2)
					{
						PawnJustMoved2Spaces = true;
					}

					if (PlayersTurn)
					{
						PlayersTurn = false;
					}

					SetLocation(sf::Vector2f(newX, newY));
				}

			}
			else if (!FirstMove && difranceY == 1)
			{
				newY -= 100;

				if ((newX != location.x || newY != location.y) && Board[int(newY) / 100][int(newX) / 100] == "XxX" && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
				{
					Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

					Board[oldY / 100][oldX / 100] = "XxX";

					if (newY == 50)
					{
						BeingPromoted = true;

						PawnGonnaBePromoted = true;
					}

					if (PawnJustMoved2Spaces)
					{
						PawnJustMoved2Spaces = false;
					}

					if (PlayersTurn)
					{
						PlayersTurn = false;
					}

					SetLocation(sf::Vector2f(newX, newY));
				}
			}


		}
		else if (Mouse.x < location.x && Mouse.y < location.y)
		{
			difranceY += location.y - Mouse.y;

			difranceY /= 100;

			difranceX += location.x - Mouse.x;

			difranceX /= 100;

			if (difranceX == 1 && difranceY == 1)
			{
				newX -= 100;

				newY -= 100;

				if (Board[int(newY) / 100][int(newX) / 100][0] != Board[int(oldY) / 100][int(oldX) / 100][0] && Board[int(newY) / 100][int(newX) / 100] != "XxX" && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
				{
					if (FirstMove)
					{
						FirstMove = false;
					}

					if (newY == 50)
					{
						BeingPromoted = true;

						PawnGonnaBePromoted = true;
					}

					RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY));

					Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

					Board[oldY / 100][oldX / 100] = "XxX";

					if (PawnJustMoved2Spaces)
					{
						PawnJustMoved2Spaces = false;
					}

					if (PlayersTurn)
					{
						PlayersTurn = false;
					}

					SetLocation(sf::Vector2f(newX, newY));
				}
				else if (Board[int(newY) / 100][int(newX) / 100] == "XxX" && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor) && Board[int(newY + 100) / 100][int(newX) / 100][0] != Board[int(oldY) / 100][int(oldX) / 100][0] && Board[int(newY + 100) / 100][int(newX) / 100][1] == 'P')
				{
					for (int i = 8; i < 16; i++)
					{
						if (EnemyPieceList[i]->location == sf::Vector2f(newX, newY + 100) && EnemyPieceList[i]->PawnJustMoved2Spaces)
						{
							RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY + 100));

							Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

							Board[oldY / 100][oldX / 100] = "XxX";

							Board[int(newY + 100) / 100][int(newX) / 100] = "XxX";

							if (PlayersTurn)
							{
								PlayersTurn = false;
							}

							SetLocation(sf::Vector2f(newX, newY));
						}
					}
				}
			}
		}
		else if (Mouse.x > location.x && Mouse.y < location.y)
		{
			difranceY += location.y - Mouse.y;

			difranceY /= 100;

			difranceX += Mouse.x - location.x;

			difranceX /= 100;

			if (difranceX == 1 && difranceY == 1)
			{
				newX += 100;

				newY -= 100;

				if (Board[int(newY) / 100][int(newX) / 100][0] != Board[int(oldY) / 100][int(oldX) / 100][0] && Board[int(newY) / 100][int(newX) / 100] != "XxX" && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
				{
					if (FirstMove)
					{
						FirstMove = false;
					}

					if (newY == 50)
					{
						BeingPromoted = true;

						PawnGonnaBePromoted = true;
					}

					RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY));

					Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

					Board[oldY / 100][oldX / 100] = "XxX";

					if (PawnJustMoved2Spaces)
					{
						PawnJustMoved2Spaces = false;
					}

					if (PlayersTurn)
					{
						PlayersTurn = false;
					}

					SetLocation(sf::Vector2f(newX, newY));
				}
				else if (Board[int(newY) / 100][int(newX) / 100] == "XxX" && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor) && Board[int(newY + 100) / 100][int(newX) / 100][0] != Board[int(oldY) / 100][int(oldX) / 100][0] && Board[int(newY + 100) / 100][int(newX) / 100][1] == 'P')
				{
					for (int i = 8; i < 16; i++)
					{
						if (EnemyPieceList[i]->location == sf::Vector2f(newX, newY + 100) && EnemyPieceList[i]->PawnJustMoved2Spaces)
						{
							RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY + 100));

							Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

							Board[oldY / 100][oldX / 100] = "XxX";

							Board[int(newY + 100) / 100][int(newX) / 100] = "XxX";

							if (PlayersTurn)
							{
								PlayersTurn = false;
							}

							SetLocation(sf::Vector2f(newX, newY));
						}
					}
				}
			}
		}
	}
	else if (Type == "queen" && selected)
	{
		MoveQueen(Mouse, Board, EnemyPieceList, PlayersTurn, KingsLocation, PieceColor, LastLocation, NumberOfRepeatedMove);
	}
	else if (Type == "knight" && selected)
	{
		MoveKnight(Mouse, Board, EnemyPieceList, PlayersTurn, KingsLocation, PieceColor, LastLocation, NumberOfRepeatedMove);
	}
	else if (Type == "rook" && selected)
	{
		MoveRook(Mouse, Board, EnemyPieceList, PlayersTurn, KingsLocation, PieceColor, LastLocation, NumberOfRepeatedMove);
	}
	else if (Type == "bishop" && selected)
	{
		MoveBishop(Mouse, Board, EnemyPieceList, PlayersTurn, KingsLocation, PieceColor, LastLocation, NumberOfRepeatedMove);
	}

}

// Rikio ejimo funkcija

void Piece::MoveBishop(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove)
{
	if (selected)
	{
		float newX = location.x;

		float newY = location.y;

		int oldX = location.x;

		int oldY = location.y;

		int difranceX = 50;

		int difranceY = 50;

		if (Mouse.x < location.x && Mouse.y < location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX -= 100 * difranceX;

				newY -= 100 * difranceY;
			}
		}
		else if (Mouse.x > location.x && Mouse.y < location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX += 100 * difranceX;

				newY -= 100 * difranceY;
			}
		}
		else if (Mouse.x < location.x && Mouse.y > location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX -= 100 * difranceX;

				newY += 100 * difranceY;
			}
		}
		else if (Mouse.x > location.x && Mouse.y > location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX += 100 * difranceX;

				newY += 100 * difranceY;
			}
		}

		if ((newX != oldX || newY != oldY) && CanThePieceMove(oldX, oldY, int(newX), int(newY), Board) && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
		{
			RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY));

			Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

			Board[oldY / 100][oldX / 100] = "XxX";

			if (newX == LastLocation.x && newY == LastLocation.y)
			{
				NumberOfRepeatedMove++;
			}
			else
			{
				NumberOfRepeatedMove = 0;
			}

			LastLocation.x = oldX;
			LastLocation.y = oldY;

			if (PlayersTurn)
			{
				PlayersTurn = false;
			}

			SetLocation(sf::Vector2f(newX, newY));

		}
	}
}

// Zirgo ejimo funkcija

void Piece::MoveKnight(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove)
{
	if (selected)
	{
		float newX = location.x;

		float newY = location.y;

		int oldX = location.x;

		int oldY = location.y;

		int difranceX = 50;

		int difranceY = 50;


		if (Mouse.x < location.x && Mouse.y < location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == 1 && difranceY == 2)
			{
				newX -= 100;
				newY -= 200;
			}
			else if (difranceX == 2 && difranceY == 1)
			{
				newX -= 200;
				newY -= 100;
			}

		}
		else if (Mouse.x > location.x && Mouse.y < location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == 1 && difranceY == 2)
			{
				newX += 100;
				newY -= 200;
			}
			else if (difranceX == 2 && difranceY == 1)
			{
				newX += 200;
				newY -= 100;
			}

		}
		else if (Mouse.x < location.x && Mouse.y > location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == 1 && difranceY == 2)
			{
				newX -= 100;
				newY += 200;
			}
			else if (difranceX == 2 && difranceY == 1)
			{
				newX -= 200;
				newY += 100;
			}

		}
		else if (Mouse.x > location.x && Mouse.y > location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == 1 && difranceY == 2)
			{
				newX += 100;
				newY += 200;
			}
			else if (difranceX == 2 && difranceY == 1)
			{
				newX += 200;
				newY += 100;
			}

		}

		if ((newX != oldX || newY != oldY) && Board[oldY / 100][oldX / 100][0] != Board[int(newY) / 100][int(newX) / 100][0] && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
		{
			RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY));

			Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

			Board[oldY / 100][oldX / 100] = "XxX";

			if (newX == LastLocation.x && newY == LastLocation.y)
			{
				NumberOfRepeatedMove++;
			}
			else
			{
				NumberOfRepeatedMove = 0;
			}

			LastLocation.x = oldX;
			LastLocation.y = oldY;

			if (PlayersTurn)
			{
				PlayersTurn = false;
			}

			SetLocation(sf::Vector2f(newX, newY));
		}

	}
}

// Boksto ejimo funkcija

void Piece::MoveRook(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove)
{
	if (selected)
	{
		float newX = location.x;

		float newY = location.y;

		int oldX = location.x;

		int oldY = location.y;

		int difranceX = 50;

		int difranceY = 50;

		if (Mouse.x - 50 < location.x && Mouse.x + 50 > location.x && Mouse.y < location.y)
		{
			difranceY += location.y - Mouse.y;

			difranceY /= 100;


			newY -= 100 * difranceY;
		}
		else if (Mouse.x - 50 < location.x && Mouse.x + 50 > location.x && Mouse.y > location.y)
		{
			difranceY += Mouse.y - location.y;

			difranceY /= 100;


			newY += 100 * difranceY;
		}
		else if (Mouse.x < location.x && Mouse.y - 50 < location.y && Mouse.y + 50 > location.y)
		{
			difranceX += location.x - Mouse.x;

			difranceX /= 100;


			newX -= 100 * difranceX;
		}
		else if (Mouse.x > location.x && Mouse.y - 50 < location.y && Mouse.y + 50 > location.y)
		{
			difranceX += Mouse.x - location.x;

			difranceX /= 100;

			
			newX += 100 * difranceX;
		}

		if ((newX != oldX || newY != oldY) && CanThePieceMove(oldX, oldY, int(newX), int(newY), Board) && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
		{
			if (FirstMove)
			{
				FirstMove = false;
			}

			RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY));

			Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

			Board[oldY / 100][oldX / 100] = "XxX";

			if (newX == LastLocation.x && newY == LastLocation.y)
			{
				NumberOfRepeatedMove++;
			}
			else
			{
				NumberOfRepeatedMove = 0;
			}

			LastLocation.x = oldX;
			LastLocation.y = oldY;

			if (PlayersTurn)
			{
				PlayersTurn = false;
			}

			SetLocation(sf::Vector2f(newX, newY));
		}
	}
}

// Karalienes ejimo funkcija

void Piece::MoveQueen(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove)
{
	if (selected)
	{
		float newX = location.x;

		float newY = location.y;

		int oldX = location.x;

		int oldY = location.y;

		int difranceX = 50;

		int difranceY = 50;

		if (Mouse.x < location.x && Mouse.y < location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX -= 100 * difranceX;

				newY -= 100 * difranceY;
			}
			else if (difranceY == 0 && difranceX > 0)
			{
				newX -= 100 * difranceX;
			}
			else if (difranceY > 0 && difranceX == 0)
			{
				newY -= 100 * difranceY;
			}
		}
		else if (Mouse.x > location.x && Mouse.y < location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX += 100 * difranceX;

				newY -= 100 * difranceY;
			}
			else if (difranceY == 0 && difranceX > 0)
			{
				newX += 100 * difranceX;
			}
			else if (difranceY > 0 && difranceX == 0)
			{
				newY -= 100 * difranceY;
			}
		}
		else if (Mouse.x < location.x && Mouse.y > location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX -= 100 * difranceX;

				newY += 100 * difranceY;
			}
			else if (difranceY == 0 && difranceX > 0)
			{
				newX -= 100 * difranceX;
			}
			else if (difranceY > 0 && difranceX == 0)
			{
				newY += 100 * difranceY;
			}
		}
		else if (Mouse.x > location.x && Mouse.y > location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY)
			{
				newX += 100 * difranceX;

				newY += 100 * difranceY;
			}
			else if (difranceY == 0 && difranceX > 0)
			{
				newX += 100 * difranceX;
			}
			else if (difranceY > 0 && difranceX == 0)
			{
				newY += 100 * difranceY;
			}
		}

		if ((newX != oldX || newY != oldY) && CanThePieceMove(oldX, oldY, int(newX), int(newY), Board) && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, KingsLocation, PieceColor))
		{
			RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY));

			Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

			Board[oldY / 100][oldX / 100] = "XxX";

			if (newX == LastLocation.x && newY == LastLocation.y)
			{
				NumberOfRepeatedMove++;
			}
			else
			{
				NumberOfRepeatedMove = 0;
			}

			LastLocation.x = oldX;
			LastLocation.y = oldY;

			if (PlayersTurn)
			{
				PlayersTurn = false;
			}

			SetLocation(sf::Vector2f(newX, newY));
		}
	}
}

// Karaliaus ejimo funkcija

void Piece::MoveKing(sf::Vector2f Mouse, Piece& Rook1, Piece& Rook2, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove)
{
	if (selected)
	{
		float newX = location.x;

		float newY = location.y;

		int oldX = location.x;

		int oldY = location.y;

		int difranceX = 50;

		int difranceY = 50;

		if (Mouse.x < location.x && Mouse.y < location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY && difranceX == 1)
			{
				newX -= 100;

				newY -= 100;

			}
			else if (difranceY == 0 && difranceX == 1)
			{
				newX -= 100;
			}
			else if (difranceY == 0 && difranceX == 2 && FirstMove && Rook1.FirstMove && CanThePieceMove(oldX, oldY, int(Rook1.location.x) + 100, int(newY), Board) && !Rook1.dead && !CheckIfPlayerPieceIsUnderAttackOrProtected(Board, location, PieceColor))
			{
				newX -= 200;

				std::string CopyBoard[8][8];

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, Rook1.location.x, Rook1.location.y, newX + 100, Rook1.location.y);

				if (!CheckIfThePlayerKingIsCheckedAfterAMove(CopyBoard, oldX, oldY, newX, newY, sf::Vector2f(newX, newY), PieceColor))
				{
					Board[int(Rook1.location.y) / 100][int(newX + 100) / 100] = Board[int(Rook1.location.y) / 100][int(Rook1.location.x) / 100];

					Board[int(Rook1.location.y) / 100][int(Rook1.location.x) / 100] = "XxX";

					Rook1.SetLocation(sf::Vector2f(newX + 100, location.y));

					Rook1.FirstMove = false;

					DidTheSpecialRookMove = true;
				}
			}
			else if (difranceY == 1 && difranceX == 0)
			{
				newY -= 100;
			}
		}
		else if (Mouse.x > location.x && Mouse.y < location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += location.y - Mouse.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY && difranceX == 1)
			{
				newX += 100;

				newY -= 100;

			}
			else if (difranceY == 0 && difranceX == 1)
			{
				newX += 100;
			}
			else if (difranceY == 0 && difranceX == 2 && FirstMove && Rook2.FirstMove && CanThePieceMove(oldX, oldY, int(Rook2.location.x) - 100, int(newY), Board) && !Rook2.dead && !CheckIfPlayerPieceIsUnderAttackOrProtected(Board, location, PieceColor))
			{
				newX += 200;

				std::string CopyBoard[8][8];

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, Rook2.location.x, Rook2.location.y, newX - 100, Rook2.location.y);

				if (!CheckIfThePlayerKingIsCheckedAfterAMove(CopyBoard, oldX, oldY, newX, newY, sf::Vector2f(newX, newY), PieceColor))
				{
					Board[int(Rook2.location.y) / 100][int(newX - 100) / 100] = Board[int(Rook2.location.y) / 100][int(Rook2.location.x) / 100];

					Board[int(Rook2.location.y) / 100][int(Rook2.location.x) / 100] = "XxX";

					Rook2.SetLocation(sf::Vector2f(newX - 100, location.y));

					Rook2.FirstMove = false;

					DidTheSpecialRookMove = true;
				}
			}
			else if (difranceY == 1 && difranceX == 0)
			{
				newY -= 100;
			}
		}
		else if (Mouse.x < location.x && Mouse.y > location.y)
		{
			difranceX += location.x - Mouse.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY && difranceX == 1)
			{
				newX -= 100;

				newY += 100;

			}
			else if (difranceY == 0 && difranceX == 1)
			{
				newX -= 100;
			}
			else if (difranceY == 0 && difranceX == 2 && FirstMove && Rook1.FirstMove && CanThePieceMove(oldX, oldY, int(Rook1.location.x) + 100, int(newY), Board) && !Rook1.dead && !CheckIfPlayerPieceIsUnderAttackOrProtected(Board, location, PieceColor))
			{
				newX -= 200;

				std::string CopyBoard[8][8];

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, Rook1.location.x, Rook1.location.y, newX + 100, Rook1.location.y);

				if (!CheckIfThePlayerKingIsCheckedAfterAMove(CopyBoard, oldX, oldY, newX, newY, sf::Vector2f(newX, newY), PieceColor))
				{
					Board[int(Rook1.location.y) / 100][int(newX + 100) / 100] = Board[int(Rook1.location.y) / 100][int(Rook1.location.x) / 100];

					Board[int(Rook1.location.y) / 100][int(Rook1.location.x) / 100] = "XxX";

					Rook1.SetLocation(sf::Vector2f(newX + 100, location.y));

					Rook1.FirstMove = false;

					DidTheSpecialRookMove = true;
				}
			}
			else if (difranceY == 1 && difranceX == 0)
			{
				newY += 100;
			}
		}
		else if (Mouse.x > location.x && Mouse.y > location.y)
		{
			difranceX += Mouse.x - location.x;
			difranceY += Mouse.y - location.y;

			difranceX /= 100;
			difranceY /= 100;

			if (difranceX == difranceY && difranceX == 1)
			{
				newX += 100;

				newY += 100;

			}
			else if (difranceY == 0 && difranceX == 1)
			{
				newX += 100;
			}
			else if (difranceY == 0 && difranceX == 2 && FirstMove && Rook2.FirstMove && CanThePieceMove(oldX, oldY, int(Rook2.location.x) - 100, int(newY), Board) && !Rook2.dead && !CheckIfPlayerPieceIsUnderAttackOrProtected(Board, location, PieceColor))
			{
				newX += 200;

				std::string CopyBoard[8][8];

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, Rook2.location.x, Rook2.location.y, newX - 100, Rook2.location.y);

				if (!CheckIfThePlayerKingIsCheckedAfterAMove(CopyBoard, oldX, oldY, newX, newY, sf::Vector2f(newX, newY), PieceColor))
				{
					Board[int(Rook2.location.y) / 100][int(newX - 100) / 100] = Board[int(Rook2.location.y) / 100][int(Rook2.location.x) / 100];

					Board[int(Rook2.location.y) / 100][int(Rook2.location.x) / 100] = "XxX";

					Rook2.SetLocation(sf::Vector2f(newX - 100, location.y));

					Rook2.FirstMove = false;

					DidTheSpecialRookMove = true;
				}
			}
			else if (difranceY == 1 && difranceX == 0)
			{
				newY += 100;
			}
		}

		if ((newX != oldX || newY != oldY) && (CanThePieceMove(oldX, oldY, int(newX), int(newY), Board) || DidTheSpecialRookMove) && !CheckIfThePlayerKingIsCheckedAfterAMove(Board, oldX, oldY, newX, newY, sf::Vector2f(newX, newY), PieceColor))
		{
			if (FirstMove)
			{
				FirstMove = false;
			}

			if (DidTheSpecialRookMove)
			{
				DidTheSpecialRookMove = false;
			}

			RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(newX, newY));

			Board[int(newY) / 100][int(newX) / 100] = Board[oldY / 100][oldX / 100];

			Board[oldY / 100][oldX / 100] = "XxX";

			if (newX == LastLocation.x && newY == LastLocation.y)
			{
				NumberOfRepeatedMove++;
			}
			else
			{
				NumberOfRepeatedMove = 0;
			}

			LastLocation.x = oldX;
			LastLocation.y = oldY;

			if (PlayersTurn)
			{
				PlayersTurn = false;
			}

			SetLocation(sf::Vector2f(newX, newY));
		}
	}
}

// Paziureti ar gali figura eiti i vieta

bool Piece::CanThePieceMove(int oldX, int oldY, int newX, int newY, std::string Board[][8])
{
	if ((newX > 0 && newX < 800) && (newY > 0 && newY < 800))
	{
		if (Board[newY / 100][newX / 100] == "XxX" || Board[oldY / 100][oldX / 100][0] != Board[newY / 100][newX / 100][0])
		{
			if (newY < oldY && newX < oldX)
			{
				while (newY != oldY && newX != oldX)
				{
					newY += 100;
					newX += 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newY != oldY && newX != oldX)
					{
						return false;
					}
				}
			}
			else if (newY < oldY && newX > oldX)
			{
				while (newY != oldY && newX != oldX)
				{
					newY += 100;
					newX -= 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newY != oldY && newX != oldX)
					{
						return false;
					}
				}
			}
			else if (newY > oldY && newX < oldX)
			{
				while (newY != oldY && newX != oldX)
				{
					newY -= 100;
					newX += 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newY != oldY && newX != oldX)
					{
						return false;
					}
				}
			}
			else if (newY > oldY && newX > oldX)
			{
				while (newY != oldY && newX != oldX)
				{
					newY -= 100;
					newX -= 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newY != oldY && newX != oldX)
					{
						return false;
					}
				}
			}
			else if (newY < oldY && newX == oldX)
			{
				while (newY != oldY)
				{
					newY += 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newY != oldY)
					{
						return false;
					}
				}
			}
			else if (newY > oldY && newX == oldX)
			{
				while (newY != oldY)
				{
					if (Board[newY / 100][newX / 100] != "XxX" && (newY - 100) == oldY && Type == "pawn")
					{
						return false;
					}

					newY -= 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newY != oldY)
					{
						return false;
					}
				}
			}
			else if (newY == oldY && newX < oldX)
			{
				while (newX != oldX)
				{
					newX += 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newX != oldX)
					{
						return false;
					}
				}
			}
			else if (newY == oldY && newX > oldX)
			{
				while (newX != oldX)
				{
					newX -= 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newX != oldX)
					{
						return false;
					}
				}
			}

			return true;
		}
		/*if (Type == "king")
		{
			if (newX > oldX && newY == oldY)
			{
				while (newX != oldX)
				{
					newX -= 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newX != oldX)
					{
						return false;
					}
				}
			}
			else if (newX < oldX && newY == oldY)
			{
				while (newX != oldX)
				{
					newX += 100;

					if (Board[newY / 100][newX / 100] != "XxX" && newX != oldX)
					{
						return false;
					}
				}
			}

			return true;
		}*/
	}

	return false;
}
