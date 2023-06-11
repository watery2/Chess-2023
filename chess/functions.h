#pragma once

void SetupBoard(Piece** White, Piece** Black, int Player);

void DeSelect(Piece** PieceList, sf::RectangleShape& rect);

void PutCircles(Piece** PieceList, sf::RenderWindow& window, sf::CircleShape& circle, sf::CircleShape& circleAttack, std::string Board[][8], Piece Rook1, Piece Rook2, char PieceColor, Piece** EnemyPieceList);

void DrawPromotionPieces(sf::RenderWindow& window, Piece** PieceList, Piece Queen, Piece Knight, Piece Rook, Piece Bishop);

void PromotePawnIfClicked(sf::Vector2f Mouse, Piece** PieceList, char PieceColor, bool& PawnGonnaBePromoted, std::string Board[][8]);

void RemoveEnemyPieceIfPossible(Piece** PieceList, sf::Vector2f Location);

void CopyBoardToAnothereArray(std::string Board[][8], std::string CopyBoard[][8]);

void MovePieceOnBoard(std::string Board[][8], int OldX, int OldY, int NewX, int NewY);

// ne zaidejui
int CheckIfPawnCanAttack(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

// ne zaidejui
bool CheckIfPieceIsUnderAttackByPawn(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

bool CheckIfPieceIsUnderAttackOrProtectedByKnight(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

bool CheckIfPieceIsUnderAttackOrProtectedByKing(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

bool CheckIfPieceIsUnderAttackOrProtectedByRook(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

bool CheckIfPieceIsUnderAttackOrProtectedByBishop(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

bool CheckIfPieceIsUnderAttackOrProtectedByQueen(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

// ne zaidejui
bool CheckIfPieceIsUnderAttack(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

//ne zaidejui
bool CheckIfTheKingIsCheckedAfterAMove(std::string Board[][8], int OldX, int OldY, int NewX, int NewY, sf::Vector2f KingsLocation, char PieceColor);

// ne zaidejui
bool CheckIfPieceIsProtectedByPawn(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

// ne zaidejui
bool CheckIfPieceIsProtected(std::string Board[][8], sf::Vector2f location, char PieceColor);

bool CheckIfPlayerPieceIsUnderAttackedByPawn(std::string Board[][8], sf::Vector2f location, char ColorToIgnore);

bool CheckIfPlayerPieceIsUnderAttackOrProtected(std::string Board[][8], sf::Vector2f location, char PieceColor);

bool CheckIfThePlayerKingIsCheckedAfterAMove(std::string Board[][8], int OldX, int OldY, int NewX, int NewY, sf::Vector2f KingsLocation, char PieceColor);

bool KingCheckMated(Piece** PieceList, std::string Board[][8], Piece Rook1, Piece Rook2, sf::Vector2f KingLocation, char PieceColor);