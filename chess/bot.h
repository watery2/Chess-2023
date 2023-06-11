#pragma once

void BotMove(Piece** PieceList, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, sf::Vector2f KingsLocation, Piece& Rook1, Piece& Rook2, std::string Board[][8], sf::RenderWindow& window, char PieceColor, bool& BotLost, bool& draw);

double AttackWorth(std::string Board[][8], sf::Vector2f location);

void CheckIfBishopCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points);

void CheckIfRookCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points);

void CheckIfKnightCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points);

void CheckIfKingCanAttackAndCountThePoints(std::string Board[][8], sf::Vector2f location, char PieceColor, double& points);

void CountThePointsOfABishopMove(int x, int y, std::string type, std::string Board[][8], sf::Vector2f location, sf::Vector2f KingsLocation, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveBishiopPoints);

void CountThePointsOfARookMove(int x, int y, std::string type, std::string Board[][8], sf::Vector2f location, sf::Vector2f KingsLocation, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveRookPoints);

void CountThePointsOfAKnightMove(int x, int y, std::string Board[][8], sf::Vector2f location, sf::Vector2f KingsLocation, Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveKnightPoints);

void CountThePointsOfAKingMove(int x, int y, std::string Board[][8], sf::Vector2f location,Piece** EnemyPieceList, sf::Vector2f EnemyKingsLocation, Piece EnemyRook1, Piece EnemyRook2, char EnemyColor, char PieceColor, double& OneMoveKingPoints);
