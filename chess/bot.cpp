#include <SFML/Graphics.hpp>
#include <iostream>

#include "Pieces.h"
#include "functions.h"
#include "bot.h"

// Funkcija kuri suranda geriausia judesi kur eiti ir ji ivykdo, nezaidejo figuroms

void BotMove(Piece** PieceList, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, sf::Vector2f KingsLocation, Piece& Rook1, Piece& Rook2, std::string Board[][8], sf::RenderWindow& window, char PieceColor, bool& BotLost, bool& draw)
{
	std::string CopyBoard[8][8];

	CopyBoardToAnothereArray(Board, CopyBoard);

	int BestPieceToMoveIndeks = 0;

	double BestPoints = -30;

	float BestX;

	float BestY;

	int BestPawnPointsIndeks;

	int BestPawnPoints;

	double OneMoveBishiopPoints = 0;

	double OneMoveRookPoints = 0;

	double OneMoveQueenPoints = 0;

	double OneMoveKnightPoints = 0;

	double OneMoveKingPoints = 0;

	double points;

	int x = 0;

	int y = 0;

	bool FrenchMoveIsPosible = false;

	for (int i = 0; i < 16; i++)
	{
		points = -30;

		if (PieceList[i]->Type == "pawn" && !PieceList[i]->dead)
		{
			BestPawnPointsIndeks = 2;

			BestPawnPoints = -30;

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			int PawnPoints[4] = { -30, -30, 0, 0};

			if (CheckIfPawnCanAttack(Board, PieceList[i]->GetLocation(), PieceColor) == 1)
			{
				PawnPoints[0] = 0;

				PawnPoints[0] += AttackWorth(Board, sf::Vector2f(x - 100, y + 100));

				if (y + 100 == 750)
				{
					PawnPoints[0] += 3;
				}

				if (CheckIfTheKingIsCheckedAfterAMove(Board, x, y, x - 100, y + 100, KingsLocation, PieceColor))
				{
					PawnPoints[0] = -30;
				}

			}
			else if (CheckIfPawnCanAttack(Board, PieceList[i]->GetLocation(), PieceColor) == 2)
			{
				PawnPoints[1] = 0;
				
				PawnPoints[1] += AttackWorth(Board, sf::Vector2f(x + 100, y + 100));
				
				if (y + 100 == 750)
				{
					PawnPoints[1] += 3;
				}

				if (CheckIfTheKingIsCheckedAfterAMove(Board, x, y, x + 100, y + 100, KingsLocation, PieceColor))
				{
					PawnPoints[1] = -30;
				}
			}
			else if (CheckIfPawnCanAttack(Board, PieceList[i]->GetLocation(), PieceColor) == 12)
			{
				PawnPoints[0] = 0;

				PawnPoints[0] += AttackWorth(Board, sf::Vector2f(x - 100, y + 100));

				if (y + 100 == 750)
				{
					PawnPoints[0] += 3;
				}

				if (CheckIfTheKingIsCheckedAfterAMove(Board, x, y, x - 100, y + 100, KingsLocation, PieceColor))
				{
					PawnPoints[0] = -30;
				}

				PawnPoints[1] = 0;

				PawnPoints[1] += AttackWorth(Board, sf::Vector2f(x + 100, y + 100));

				if (y + 100 == 750)
				{
					PawnPoints[1] += 3;
				}

				if (CheckIfTheKingIsCheckedAfterAMove(Board, x, y, x + 100, y + 100, KingsLocation, PieceColor))
				{
					PawnPoints[1] = -30;
				}

			}

			if (Board[y / 100][(x - 100) / 100][0] != Board[y / 100][x / 100][0] && Board[y / 100][(x - 100) / 100][1] == 'P' && Board[(y + 100) / 100][(x - 100) / 100] == "XxX")
			{
				if (!CheckIfTheKingIsCheckedAfterAMove(Board, x, y, x - 100, y + 100, KingsLocation, PieceColor))
				{
					for (int j = 8; j < 16; j++)
					{
						if (EnemyPieceList[j]->GetLocation() == sf::Vector2f(x - 100, y) && EnemyPieceList[j]->PawnJustMoved2Spaces)
						{
							PawnPoints[0] = 0;

							PawnPoints[0] += 2;
						}
					}
				}
			}

			if (Board[y / 100][(x + 100) / 100][0] != Board[y / 100][x / 100][0] && Board[y / 100][(x + 100) / 100][1] == 'P' && Board[(y + 100) / 100][(x + 100) / 100] == "XxX")
			{
				if (!CheckIfTheKingIsCheckedAfterAMove(Board, x, y, x + 100, y + 100, KingsLocation, PieceColor))
				{
					for (int j = 8; j < 16; j++)
					{
						if (EnemyPieceList[j]->GetLocation() == sf::Vector2f(x + 100, y) && EnemyPieceList[j]->PawnJustMoved2Spaces)
						{
							PawnPoints[1] = 0;

							PawnPoints[1] += 2;
						}
					}
				}
			}

			y += 100;

			if (PieceList[i]->CanThePieceMove(x, PieceList[i]->GetLocation().y, x, y, Board) && Board[y / 100][x / 100] == "XxX")
			{
				if ((x == 350 && (y) == 350) || (x == 350 && (y) == 450) || (x == 450 && (y) == 350) || (x == 450 && (y) == 450))
				{
					PawnPoints[2] += 1;
				}

				if (CheckIfPieceIsUnderAttack(Board, PieceList[i]->GetLocation(), PieceColor))
				{
					PawnPoints[2] += 0.5;
				}

				if (CheckIfPawnCanAttack(Board, sf::Vector2f(x, y), PieceColor) == 1)
				{
					PawnPoints[2] += AttackWorth(Board, sf::Vector2f(x - 100, y + 100)) / 2;
				}
				else if (CheckIfPawnCanAttack(Board, sf::Vector2f(x, y), PieceColor) == 2)
				{
					PawnPoints[2] += AttackWorth(Board, sf::Vector2f(x + 100, y + 100)) / 2;
				}
				else if (CheckIfPawnCanAttack(Board, sf::Vector2f(x, y), PieceColor) == 12)
				{
					if (AttackWorth(Board, sf::Vector2f(x - 100, y + 100)) > AttackWorth(Board, sf::Vector2f(x + 100, y + 100)))
					{
						PawnPoints[2] += AttackWorth(Board, sf::Vector2f(x - 100, y + 100)) / 2;
					}
					else
					{
						PawnPoints[2] += AttackWorth(Board, sf::Vector2f(x + 100, y + 100)) / 2;
					}
				}

				if (CheckIfPieceIsUnderAttack(Board, sf::Vector2f(x, y), PieceColor))
				{
					if (CheckIfPieceIsProtected(Board, sf::Vector2f(x, y), PieceColor))
					{
						PawnPoints[2] += 0.5;
					}
				}

				if (y == 750)
				{
					PawnPoints[2] += 3;
				}

				if (CheckIfTheKingIsCheckedAfterAMove(Board, x, PieceList[i]->GetLocation().y, x, y, KingsLocation, PieceColor))
				{
					PawnPoints[2] = -30;
				}
			}
			else
			{
				PawnPoints[2] = -30;
			}

			y = PieceList[i]->GetLocation().y;

			y += 200;

			if (PieceList[i]->CanThePieceMove(x, PieceList[i]->GetLocation().y, x, y, Board) && PieceList[i]->FirstMove && Board[y / 100][x / 100] == "XxX")
			{
				if ((x == 350 && (y) == 350) || (x == 350 && (y) == 450) || (x == 450 && (y) == 350) || (x == 450 && (y) == 450))
				{
					PawnPoints[3] += 1;
				}

				if (CheckIfPieceIsUnderAttack(Board, PieceList[i]->GetLocation(), PieceColor))
				{
					PawnPoints[3] += 0.5;
				}

				if (CheckIfPawnCanAttack(Board, sf::Vector2f(x, y), PieceColor) == 1)
				{
					PawnPoints[3] += AttackWorth(Board, sf::Vector2f(x - 100, y + 100)) / 2;
				}
				else if (CheckIfPawnCanAttack(Board, sf::Vector2f(x, y), PieceColor) == 2)
				{
					PawnPoints[3] += AttackWorth(Board, sf::Vector2f(x + 100, y + 100)) / 2;
				}
				else if (CheckIfPawnCanAttack(Board, sf::Vector2f(x, y), PieceColor) == 12)
				{
					if (AttackWorth(Board, sf::Vector2f(x - 100, y + 100)) > AttackWorth(Board, sf::Vector2f(x + 100, y + 100)))
					{
						PawnPoints[3] += AttackWorth(Board, sf::Vector2f(x - 100, y + 100)) / 2;
					}
					else
					{
						PawnPoints[3] += AttackWorth(Board, sf::Vector2f(x + 100, y + 100)) / 2;
					}
				}

				if (CheckIfPieceIsUnderAttack(Board, sf::Vector2f(x, y), PieceColor))
				{
					if (CheckIfPieceIsProtected(Board, sf::Vector2f(x, y), PieceColor))
					{
						PawnPoints[3] += 0.5;
					}
				}

				if (CheckIfTheKingIsCheckedAfterAMove(Board, x, PieceList[i]->GetLocation().y, x, y, KingsLocation, PieceColor))
				{
					PawnPoints[3] = -30;
				}
			}
			else
			{
				PawnPoints[3] = -30;
			}

			y = PieceList[i]->GetLocation().y;

			for (int j = 0; j < 4; j++)
			{
				if (PawnPoints[j] > BestPawnPoints && PawnPoints[j] > -30)
				{
					BestPawnPoints = PawnPoints[j];

					BestPawnPointsIndeks = j;
				}
			}

			if (BestPawnPointsIndeks == 0)
			{
				x -= 100;

				y += 100;
			}
			else if (BestPawnPointsIndeks == 1)
			{
				x += 100;

				y += 100;
			}
			else if (BestPawnPointsIndeks == 2)
			{
				y += 100;
			}
			else if (BestPawnPointsIndeks == 3)
			{
				y += 200;
			}

			points = BestPawnPoints;


			if (points >= BestPoints)
			{
				BestPoints = points;

				BestPieceToMoveIndeks = i;

				BestX = x;

				BestY = y;
				
			}
			
		}
		else if (PieceList[i]->Type == "bishop" && !PieceList[i]->dead)
		{
			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveBishiopPoints = 0;

			/////////////////////////////////////////
			// zemyn kaire

			while (x > 50 && y < 750)
			{
				OneMoveBishiopPoints = 0;

				x -= 100;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);

					if (OneMoveBishiopPoints >= BestPoints)
					{
						BestPoints = OneMoveBishiopPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);
				
				if (OneMoveBishiopPoints >= BestPoints)
				{
					BestPoints = OneMoveBishiopPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			/////////////////////////////////////////
			// zemyn desine

			while (x < 750 && y < 750)
			{
				OneMoveBishiopPoints = 0;

				x += 100;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);

					if (OneMoveBishiopPoints >= BestPoints)
					{
						BestPoints = OneMoveBishiopPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);

				if (OneMoveBishiopPoints >= BestPoints)
				{
					BestPoints = OneMoveBishiopPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			/////////////////////////////////////////
			// aukstyn kaire

			while (x > 50 && y > 50)
			{
				OneMoveBishiopPoints = 0;

				x -= 100;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);
					
					if (OneMoveBishiopPoints >= BestPoints)
					{
						BestPoints = OneMoveBishiopPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);

				if (OneMoveBishiopPoints >= BestPoints)
				{
					BestPoints = OneMoveBishiopPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			/////////////////////////////////////////
			// aukstyn desine

			while (x < 750 && y > 50)
			{
				OneMoveBishiopPoints = 0;

				x += 100;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);
					
					if (OneMoveBishiopPoints >= BestPoints)
					{
						BestPoints = OneMoveBishiopPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "bishop", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveBishiopPoints);

				if (OneMoveBishiopPoints >= BestPoints)
				{
					BestPoints = OneMoveBishiopPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}
		}
		else if (PieceList[i]->Type == "rook" && !PieceList[i]->dead)
		{
			OneMoveRookPoints = 0;

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			while (x > 50)
			{
				OneMoveRookPoints = 0;

				x -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

					if (OneMoveRookPoints >= BestPoints)
					{
						BestPoints = OneMoveRookPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

				if (OneMoveRookPoints >= BestPoints)
				{
					BestPoints = OneMoveRookPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			while (x < 750)
			{
				OneMoveRookPoints = 0;

				x += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

					if (OneMoveRookPoints >= BestPoints)
					{
						BestPoints = OneMoveRookPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

				if (OneMoveRookPoints >= BestPoints)
				{
					BestPoints = OneMoveRookPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			while (y > 50)
			{
				OneMoveRookPoints = 0;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

					if (OneMoveRookPoints >= BestPoints)
					{
						BestPoints = OneMoveRookPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

				if (OneMoveRookPoints >= BestPoints)
				{
					BestPoints = OneMoveRookPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			y = PieceList[i]->GetLocation().y;

			while (y < 750)
			{
				OneMoveRookPoints = 0;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

					if (OneMoveRookPoints >= BestPoints)
					{
						BestPoints = OneMoveRookPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "rook", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveRookPoints);

				if (OneMoveRookPoints >= BestPoints)
				{
					BestPoints = OneMoveRookPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}
		}
		else if (PieceList[i]->Type == "queen" && !PieceList[i]->dead)
		{
			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveQueenPoints = 0;

			while (x > 50 && y < 750)
			{
				OneMoveQueenPoints = 0;

				x -= 100;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);
					
					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			while (x < 750 && y < 750)
			{
				OneMoveQueenPoints = 0;

				x += 100;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);
					
					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			while (x > 50 && y > 50)
			{
				OneMoveQueenPoints = 0;

				x -= 100;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			while (x < 750 && y > 50)
			{
				OneMoveQueenPoints = 0;

				x += 100;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfABishopMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);
				
				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			// Rook Moves

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			while (x > 50)
			{
				OneMoveQueenPoints = 0;

				x -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			while (x < 700)
			{
				OneMoveQueenPoints = 0;

				x += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			while (y > 50)
			{
				OneMoveQueenPoints = 0;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			y = PieceList[i]->GetLocation().y;

			while (y < 750)
			{
				OneMoveQueenPoints = 0;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
				{
					CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

					if (OneMoveQueenPoints >= BestPoints)
					{
						BestPoints = OneMoveQueenPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}

					break;
				}
				else if (Board[y / 100][x / 100] != "XxX")
				{
					break;
				}

				CountThePointsOfARookMove(x, y, "queen", Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveQueenPoints);

				if (OneMoveQueenPoints >= BestPoints)
				{
					BestPoints = OneMoveQueenPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

		}
		else if (PieceList[i]->Type == "knight" && !PieceList[i]->dead)
		{
			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (x - 200 > 0 && y - 100 > 0)
			{
				x -= 200;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (x - 200 > 0 && y + 100 < 800)
			{
				x -= 200;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (x + 200 < 800 && y - 100 > 0)
			{
				x += 200;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (x + 200 < 800 && y + 100 < 800)
			{
				x += 200;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (y - 200 > 0 && x - 100 > 0)
			{
				y -= 200;

				x -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (y - 200 > 0 && x + 100 < 800)
			{
				y -= 200;

				x += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (y + 200 < 800 && x - 100 > 0)
			{
				y += 200;

				x -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKnightPoints = 0;

			if (y + 200 < 800 && x + 100 < 800)
			{
				y += 200;

				x += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKnightMove(x, y, Board, PieceList[i]->GetLocation(), KingsLocation, EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKnightPoints);

					if (OneMoveKnightPoints >= BestPoints)
					{
						BestPoints = OneMoveKnightPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}
		}
		else if (PieceList[i]->Type == "king" && !PieceList[i]->dead)
		{
			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			OneMoveKingPoints = 0;
			
			if (y - 100 > 0)
			{
				OneMoveKingPoints = 0;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			if (y - 100 > 0 && x - 100 > 0)
			{
				OneMoveKingPoints = 0;

				x -= 100;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			if (x - 100 > 0)
			{
				OneMoveKingPoints = 0;

				x -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			if (y + 100 < 800 && x - 100 > 0)
			{
				OneMoveKingPoints = 0;

				x -= 100;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			if (y + 100 < 800)
			{
				OneMoveKingPoints = 0;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			if (y + 100 < 800 && x + 100 < 800)
			{
				OneMoveKingPoints = 0;

				x += 100;

				y += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			if (x + 100 < 800)
			{
				OneMoveKingPoints = 0;

				x += 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			if (y - 100 > 0 && x + 100 < 800)
			{
				OneMoveKingPoints = 0;

				x += 100;

				y -= 100;

				if (Board[y / 100][x / 100][0] != PieceColor)
				{
					CountThePointsOfAKingMove(x, y, Board, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

					if (OneMoveKingPoints >= BestPoints)
					{
						BestPoints = OneMoveKingPoints;

						BestPieceToMoveIndeks = i;

						BestX = x;

						BestY = y;
					}
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			x += 200;

			if (PieceList[i]->FirstMove && PieceList[i]->CanThePieceMove(PieceList[i]->GetLocation().x, y, Rook2.GetLocation().x - 100, y, Board) && Rook2.FirstMove && !CheckIfPieceIsUnderAttack(Board, PieceList[i]->GetLocation(), PieceColor))
			{
				OneMoveKingPoints = 0;

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, Rook2.GetLocation().x, y, x - 100, y);

				CountThePointsOfAKingMove(x, y, CopyBoard, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, PieceList[i]->GetLocation().x, y, x, y);

				CountThePointsOfARookMove(x - 100, y, "rook", CopyBoard, Rook2.GetLocation(), sf::Vector2f(x, y), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

				if (OneMoveKingPoints >= BestPoints)
				{
					BestPoints = OneMoveKingPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}

			x = PieceList[i]->GetLocation().x;

			y = PieceList[i]->GetLocation().y;

			x -= 200;

			if (PieceList[i]->FirstMove && PieceList[i]->CanThePieceMove(PieceList[i]->GetLocation().x, y, Rook1.GetLocation().x + 100, y, Board) && Rook1.FirstMove && !CheckIfPieceIsUnderAttack(Board, PieceList[i]->GetLocation(), PieceColor))
			{
				OneMoveKingPoints = 0;

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, Rook1.GetLocation().x, y, x + 100, y);

				CountThePointsOfAKingMove(x, y, CopyBoard, PieceList[i]->GetLocation(), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

				CopyBoardToAnothereArray(Board, CopyBoard);

				MovePieceOnBoard(CopyBoard, PieceList[i]->GetLocation().x, y, x, y);

				CountThePointsOfARookMove(x + 100, y, "rook", CopyBoard, Rook1.GetLocation(), sf::Vector2f(x, y), EnemyPieceList, EnemyKingsLocation, EnemyRook1, EnemyRook2, EnemyColor, PieceColor, OneMoveKingPoints);

				if (OneMoveKingPoints >= BestPoints)
				{
					BestPoints = OneMoveKingPoints;

					BestPieceToMoveIndeks = i;

					BestX = x;

					BestY = y;
				}
			}
		}

	}

	if (PieceList[BestPieceToMoveIndeks]->GetLocation().x != BestX || PieceList[BestPieceToMoveIndeks]->GetLocation().y != BestY)
	{
		if (BestPoints != -30)
		{
			if (PieceList[BestPieceToMoveIndeks]->PawnJustMoved2Spaces)
			{
				PieceList[BestPieceToMoveIndeks]->PawnJustMoved2Spaces = false;
			}

			if (PieceList[BestPieceToMoveIndeks]->FirstMove)
			{
				PieceList[BestPieceToMoveIndeks]->FirstMove = false;

				if (PieceList[BestPieceToMoveIndeks]->Type == "pawn" && BestY - PieceList[BestPieceToMoveIndeks]->GetLocation().y == 200)
				{
					PieceList[BestPieceToMoveIndeks]->PawnJustMoved2Spaces = true;
				}
			}

			if (BestY == 750 && PieceList[BestPieceToMoveIndeks]->Type == "pawn")
			{
				if (PieceColor == 'B')
				{
					PieceList[BestPieceToMoveIndeks]->SetTexture("img/queenB.png");

					PieceList[BestPieceToMoveIndeks]->Type = "queen";

					Board[int(PieceList[BestPieceToMoveIndeks]->GetLocation().y / 100)][int(PieceList[BestPieceToMoveIndeks]->GetLocation().x) / 100][1] = 'Q';
					Board[int(PieceList[BestPieceToMoveIndeks]->GetLocation().y / 100)][int(PieceList[BestPieceToMoveIndeks]->GetLocation().x) / 100][2] = 'U';
				}
				else if (PieceColor == 'W')
				{
					PieceList[BestPieceToMoveIndeks]->SetTexture("img/queenW.png");

					PieceList[BestPieceToMoveIndeks]->Type = "queen";

					Board[int(PieceList[BestPieceToMoveIndeks]->GetLocation().y / 100)][int(PieceList[BestPieceToMoveIndeks]->GetLocation().x) / 100][1] = 'Q';
					Board[int(PieceList[BestPieceToMoveIndeks]->GetLocation().y / 100)][int(PieceList[BestPieceToMoveIndeks]->GetLocation().x) / 100][2] = 'U';
				}
			}

			if (PieceList[BestPieceToMoveIndeks]->Type == "pawn" && Board[int(BestY) / 100][int(BestX) / 100] == "XxX" && Board[int(BestY - 100) / 100][int(BestX) / 100][0] != Board[int(PieceList[BestPieceToMoveIndeks]->GetLocation().y) / 100][int(PieceList[BestPieceToMoveIndeks]->GetLocation().x) / 100][0] && Board[int(BestY - 100) / 100][int(BestX) / 100][1] == 'P')
			{
				Board[int(BestY - 100) / 100][int(BestX) / 100] = "XxX";

				RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(BestX, BestY - 100));
			}

			if (PieceList[BestPieceToMoveIndeks]->Type == "king" && fabs(BestX - PieceList[BestPieceToMoveIndeks]->GetLocation().x) == 200)
			{
				if (PieceList[BestPieceToMoveIndeks]->GetLocation().x < BestX)
				{
					MovePieceOnBoard(Board, Rook2.GetLocation().x, Rook2.GetLocation().y, BestX - 100, BestY);

					Rook2.SetLocation(sf::Vector2f(BestX - 100, BestY));
				}
				else if (PieceList[BestPieceToMoveIndeks]->GetLocation().x > BestX)
				{
					MovePieceOnBoard(Board, Rook1.GetLocation().x, Rook1.GetLocation().y, BestX + 100, BestY);

					Rook1.SetLocation(sf::Vector2f(BestX + 100, BestY));
				}
			}

			Board[int(BestY) / 100][int(BestX) / 100] = Board[int(PieceList[BestPieceToMoveIndeks]->GetLocation().y) / 100][int(PieceList[BestPieceToMoveIndeks]->GetLocation().x) / 100];

			Board[int(PieceList[BestPieceToMoveIndeks]->GetLocation().y) / 100][int(PieceList[BestPieceToMoveIndeks]->GetLocation().x) / 100] = "XxX";

			PieceList[BestPieceToMoveIndeks]->SetLocation(sf::Vector2f(BestX, BestY));

			RemoveEnemyPieceIfPossible(EnemyPieceList, sf::Vector2f(BestX, BestY));

			window.draw(PieceList[BestPieceToMoveIndeks]->GetSprite());

		}
		else
		{
			if (CheckIfPieceIsUnderAttack(Board, KingsLocation, PieceColor))
			{
				BotLost = true;
			}
			else
			{
				draw = true;
			}
		}
	}

}

// Paziuri lentoi kokia figura ir grazina jos verte

double AttackWorth(std::string Board[][8], sf::Vector2f location)
{
	double points = 0;

	int x = location.x;

	int y = location.y;

	if (Board[y / 100][x / 100][1] == 'P')
	{
		points = 2;
	}
	else if (Board[y / 100][x / 100][1] == 'K' && Board[y / 100][x / 100][2] != 'I')
	{
		points = 3;
	}
	else if (Board[y / 100][x / 100][1] == 'B')
	{
		points = 3;
	}
	else if (Board[y / 100][x / 100][1] == 'R')
	{
		points = 5;
	}
	else if (Board[y / 100][x / 100][1] == 'Q')
	{
		points = 9;
	}
	else if (Board[y / 100][x / 100][1] == 'K' && Board[y / 100][x / 100][2] == 'I')
	{
		points = 12;
	}

	return points;
}

// Paziuri aplinkui Riki ar jis gali pulti, jei randa figura pulti padalina tos figuros verta per 2 ir prideda prie tasku

void CheckIfBishopCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points)
{
	int X = location.x;
	
	int Y = location.y;

	while (X > 50 && Y > 50)
	{
		X -= 100;
		Y -= 100;

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
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

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
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

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	X = location.x;

	Y = location.y;

	while (X < 700 && Y < 750)
	{
		X += 100;
		Y += 100;

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}
}

// Paziuri aplinkui Boksta ar jis gali pulti, jei randa figura pulti padalina tos figuros verta per 2 ir prideda prie tasku

void CheckIfRookCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points)
{
	int X = location.x;

	int Y = location.y;

	while (X > 50)
	{
		X -= 100;

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	X = location.x;

	while (X < 750)
	{
		X += 100;

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	X = location.x;

	while (Y < 750)
	{
		Y += 100;

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}

	Y = location.y;

	while (Y > 50)
	{
		Y -= 100;

		if (Board[Y / 100][X / 100][0] != PieceColor && Board[Y / 100][X / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(X, Y)) / 2;

			break;
		}
		else if (Board[Y / 100][X / 100] != "XxX")
		{
			break;
		}
	}
}

// Paziuri aplinkui Zirga ar jis gali pulti, jei randa figura pulti padalina tos figuros verta per 2 ir prideda prie tasku

void CheckIfKnightCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points)
{
	int x = location.x;

	int y = location.y;

	if (x - 200 > 0 && y - 100 > 0)
	{
		x -= 200;

		y -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}

	x = location.x;

	y = location.y;

	if (x - 200 > 0 && y + 100 < 800)
	{
		x -= 200;

		y += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}

	x = location.x;

	y = location.y;

	if (x + 200 < 800 && y - 100 > 0)
	{
		x += 200;

		y -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}

	x = location.x;

	y = location.y;

	if (x + 200 < 800 && y + 100 < 800)
	{
		x += 200;

		y += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}

	x = location.x;

	y = location.y;

	if (y - 200 > 0 && x - 100 > 0)
	{
		y -= 200;

		x -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}

	x = location.x;

	y = location.y;

	if (y - 200 > 0 && x + 100 < 800)
	{
		y -= 200;

		x += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}

	x = location.x;

	y = location.y;

	if (y + 200 < 800 && x - 100 > 0)
	{
		y += 200;

		x -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}

	x = location.x;

	y = location.y;

	if (y + 200 < 800 && x + 100 < 800)
	{
		y += 200;

		x += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
		else if (Board[y / 100][x / 100][0] == PieceColor)
		{
			points += 0.3;
		}
	}
}

// Paziuri aplinkui Karaliu ar jis gali pulti, jei randa figura pulti padalina tos figuros verta per 2 ir prideda prie tasku

void CheckIfKingCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points)
{
	int x = location.x;

	int y = location.y;

	if (y - 100 > 0)
	{
		y -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}

	x = location.x;

	y = location.y;

	if (y - 100 > 0 && x - 100 > 0)
	{
		x -= 100;

		y -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}

	x = location.x;

	y = location.y;

	if (x - 100 > 0)
	{
		x -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}

	x = location.x;

	y = location.y;

	if (y + 100 < 800 && x - 100 > 0)
	{
		x -= 100;

		y += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}

	x = location.x;

	y = location.y;

	if (y + 100 < 800)
	{
		y += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}

	x = location.x;

	y = location.y;

	if (y + 100 < 800 && x + 100 < 800)
	{
		x += 100;

		y += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}

	x = location.x;

	y = location.y;

	if (x + 100 < 800)
	{
		x += 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}

	x = location.x;

	y = location.y;

	if (y - 100 > 0 && x + 100 < 800)
	{
		x += 100;

		y -= 100;

		if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
		{
			points += AttackWorth(Board, sf::Vector2f(x, y)) / 2;
		}
	}
}

// Pajudina figura ant nukopijuotos lentos ir skaicuoja imanomus taskus

void CountThePointsOfABishopMove(int x, int y, std::string type, std::string Board[][8], sf::Vector2f location, sf::Vector2f KingsLocation, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveBishiopPoints)
{
	std::string CopyBoard[8][8];

	if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
	{
		CopyBoardToAnothereArray(Board, CopyBoard);

		MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

		if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			if (CheckIfPieceIsProtected(CopyBoard, sf::Vector2f(x, y), PieceColor))
			{
				OneMoveBishiopPoints += 0.5;
			}

			if (type == "queen")
			{
				OneMoveBishiopPoints += AttackWorth(Board, sf::Vector2f(x, y)) - 9;
			}
			else
			{
				OneMoveBishiopPoints += AttackWorth(Board, sf::Vector2f(x, y)) - 3;
			}

		}
		else
		{
			OneMoveBishiopPoints += 1.5;

			CheckIfBishopCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveBishiopPoints);

			OneMoveBishiopPoints += AttackWorth(Board, sf::Vector2f(x, y));
		}

		if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
		{
			if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
			{
				OneMoveBishiopPoints += 30;
			}
		}

		if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, KingsLocation, PieceColor))
		{
			OneMoveBishiopPoints = -30;
		}

		return;

	}
	
	CopyBoardToAnothereArray(Board, CopyBoard);

	MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

	if (CheckIfPieceIsUnderAttack(Board, location, PieceColor))
	{
		if (!CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			if (type == "queen")
			{
				OneMoveBishiopPoints += 3;
			}
			else
			{
				OneMoveBishiopPoints += 2;
			}
		}
	}

	if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
	{
		if (CheckIfPieceIsProtected(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			OneMoveBishiopPoints += 0.5;
		}
		else
		{
			OneMoveBishiopPoints -= 1;
		}
	}
	else
	{
		CheckIfBishopCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveBishiopPoints);
	}

	if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
	{
		if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
		{
			OneMoveBishiopPoints += 30;
		}
	}

	if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, KingsLocation, PieceColor))
	{
		OneMoveBishiopPoints = -30;
	}

}

// Pajudina figura ant nukopijuotos lentos ir skaicuoja imanomus taskus

void CountThePointsOfARookMove(int x, int y, std::string type, std::string Board[][8], sf::Vector2f location, sf::Vector2f KingsLocation, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveRookPoints)
{
	std::string CopyBoard[8][8];

	if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
	{
		CopyBoardToAnothereArray(Board, CopyBoard);

		MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

		if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			if (CheckIfPieceIsProtected(CopyBoard, sf::Vector2f(x, y), PieceColor))
			{
				OneMoveRookPoints += 0.5;
			}

			if (type == "queen")
			{
				OneMoveRookPoints += AttackWorth(Board, sf::Vector2f(x, y)) - 9;
			}
			else
			{
				OneMoveRookPoints += AttackWorth(Board, sf::Vector2f(x, y)) - 5;
			}
		}
		else
		{
			OneMoveRookPoints += 1.5;

			CheckIfRookCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveRookPoints);

			OneMoveRookPoints += AttackWorth(Board, sf::Vector2f(x, y));
		}

		if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
		{
			if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
			{
				OneMoveRookPoints += 30;
			}
		}

		if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, KingsLocation, PieceColor))
		{
			OneMoveRookPoints = -30;
		}

		return;

	}

	CopyBoardToAnothereArray(Board, CopyBoard);

	MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

	if (CheckIfPieceIsUnderAttack(Board, location, PieceColor))
	{
		if (!CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			if (type == "queen")
			{
				OneMoveRookPoints += 3;
			}
			else
			{
				OneMoveRookPoints += 1.5;
			}
		}
	}

	if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
	{
		if (CheckIfPieceIsProtected(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			OneMoveRookPoints += 0.5;
		}
		else
		{
			OneMoveRookPoints -= 1;
		}
	}
	else
	{
		CheckIfRookCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveRookPoints);
	}

	if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
	{
		if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
		{
			OneMoveRookPoints += 30;
		}
	}

	if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, KingsLocation, PieceColor))
	{
		OneMoveRookPoints = -30;
	}
}

// Pajudina figura ant nukopijuotos lentos ir skaicuoja imanomus taskus

void CountThePointsOfAKnightMove(int x, int y, std::string Board[][8], sf::Vector2f location, sf::Vector2f KingsLocation, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveKnightPoints)
{
	std::string CopyBoard[8][8];

	if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
	{
		CopyBoardToAnothereArray(Board, CopyBoard);

		MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

		if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			if (CheckIfPieceIsProtected(CopyBoard, sf::Vector2f(x, y), PieceColor))
			{
				OneMoveKnightPoints += 0.5;
			}

			OneMoveKnightPoints += AttackWorth(Board, sf::Vector2f(x, y)) - 3;
		}
		else
		{
			OneMoveKnightPoints += 1.5;

			CheckIfKnightCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveKnightPoints);

			OneMoveKnightPoints += AttackWorth(Board, sf::Vector2f(x, y));
		}

		if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
		{
			if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
			{
				OneMoveKnightPoints += 30;
			}
		}

		if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, KingsLocation, PieceColor))
		{
			OneMoveKnightPoints = -30;
		}

		return;

	}

	CopyBoardToAnothereArray(Board, CopyBoard);

	MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

	if (CheckIfPieceIsUnderAttack(Board, location, PieceColor))
	{
		if (!CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			OneMoveKnightPoints += 1.5;
		}
	}

	if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
	{
		if (CheckIfPieceIsProtected(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			OneMoveKnightPoints += 0.5;
		}
		else
		{
			OneMoveKnightPoints -= 1;
		}
	}
	else
	{
		CheckIfKnightCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveKnightPoints);
	}

	if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
	{
		if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
		{
			OneMoveKnightPoints += 30;
		}
	}

	if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, KingsLocation, PieceColor))
	{
		OneMoveKnightPoints = -30;
	}
}

// Pajudina figura ant nukopijuotos lentos ir skaicuoja imanomus taskus

void CountThePointsOfAKingMove(int x, int y, std::string Board[][8], sf::Vector2f location, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveKingPoints)
{
	std::string CopyBoard[8][8];

	if (Board[y / 100][x / 100][0] != PieceColor && Board[y / 100][x / 100][0] != 'X')
	{
		CopyBoardToAnothereArray(Board, CopyBoard);

		MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

		if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			OneMoveKingPoints = -30;
		}
		else
		{
			OneMoveKingPoints += 1.5;

			CheckIfKingCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveKingPoints);

			OneMoveKingPoints += AttackWorth(Board, sf::Vector2f(x, y));

			if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
			{
				if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
				{
					OneMoveKingPoints += 30;
				}
			}
		}

		if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, sf::Vector2f(x, y), PieceColor))
		{
			OneMoveKingPoints = -30;
		}

		return;

	}

	CopyBoardToAnothereArray(Board, CopyBoard);

	MovePieceOnBoard(CopyBoard, location.x, location.y, x, y);

	if (CheckIfPieceIsUnderAttack(Board, location, PieceColor))
	{
		if (!CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
		{
			OneMoveKingPoints += 1.5;
		}
	}

	if (CheckIfPieceIsUnderAttack(CopyBoard, sf::Vector2f(x, y), PieceColor))
	{
		OneMoveKingPoints = -30;
	}
	else
	{
		CheckIfKingCanAttackAndCountThePoints(CopyBoard, sf::Vector2f(x, y), PieceColor, OneMoveKingPoints);

		if (CheckIfPlayerPieceIsUnderAttackOrProtected(CopyBoard, EnemyKingsLocation, EnemyColor))
		{
			if (KingCheckMated(EnemyPieceList, CopyBoard, EnemyRook1, EnemyRook2, EnemyKingsLocation, EnemyColor))
			{
				OneMoveKingPoints += 30;
			}
		}
	}

	if (CheckIfTheKingIsCheckedAfterAMove(Board, location.x, location.y, x, y, sf::Vector2f(x, y), PieceColor))
	{
		OneMoveKingPoints = -30;
	}
}

