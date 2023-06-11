#pragma once

class Piece
{
	public:

		// kad zinotume kokio tipo yra figura
		std::string Type = "";

		// sito reikia kad zinotume ar tai pirmasis pestininko, karaliaus ir boksto ejimas

		bool FirstMove = true;

		//////////////////////

		// zinoti ar pestininkas bus paaukštintas

		bool BeingPromoted = false;

		///////////////////////////////////

		// zinoti ar pestininkas pajudejo 2 kvadratus

		bool PawnJustMoved2Spaces = false;

		// zinoti ar figura nukirsta

		bool dead = false;

		// zinoti ar karalius dari specelu judesi su Bokstu

		bool DidTheSpecialRookMove = false;
		
		// zinoti ar figura pasirinkta, jei figura pasirinkta uz jo bus padetas kvadratas ir ten kur pele paspaus ten figura eis

		bool selected = false;

		sf::Sprite GetSprite();

		sf::Vector2f GetLocation();

		void SetTexture(std::string textureLocation);

		void SetLocation(sf::Vector2f SetLocation);

		// konstruktorius

		Piece(std::string textureLocation, sf::Vector2f Location, std::string type);

		///////////////////
		
		// Destruktorius

		~Piece();

		//////////////////

		bool Clicked(sf::Vector2f Mouse);

		void HighlightPiece(sf::RectangleShape& rect, Piece** PieceList);

		void MovePawn(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, bool& PawnGonnaBePromoted, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove);

		void MoveBishop(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove);

		void MoveKnight(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove);

		void MoveRook(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove);

		void MoveQueen(sf::Vector2f Mouse, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, sf::Vector2f KingsLocation, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove);

		void MoveKing(sf::Vector2f Mouse, Piece& Rook1, Piece& Rook2, std::string Board[][8], Piece** EnemyPieceList, bool& PlayersTurn, char PieceColor, sf::Vector2f& LastLocation, int& NumberOfRepeatedMove);

		bool CanThePieceMove(int oldX, int oldY, int newX, int newY, std::string Board[][8]);

	private:
		sf::Texture texture;

		sf::Vector2f location;

		sf::Sprite sprite;

};
