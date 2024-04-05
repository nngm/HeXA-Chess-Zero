#ifndef POSITION_H
#define POSITION_H

#include <string>

#include "types.h"

class Position {
  public:
    Position &set(const std::string fen);
    std::string fen() const;

  private:
    Piece           board[SQUARE_NB];
    Color           sideToMove;
    CastlingRights  castlingRights;
    Square          epSquare;
    int             Halfmove;
    int             fullmove;
};

std::ostream &operator<<(std::ostream &os, const Position &pos);

#endif  // #ifndef POSITION_H