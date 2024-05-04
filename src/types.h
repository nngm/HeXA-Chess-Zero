#ifndef TYPES_H
    #define TYPES_H

// When compiling with provided Makefile (e.g. for Linux and OSX), configuration
// is done automatically. To get started type 'make help'.
//
// When Makefile is not used (e.g. with Microsoft Visual Studio) some switches
// need to be set manually:
//
// -DNDEBUG      | Disable debugging mode. Always use this for release.
//
// -DNO_PREFETCH | Disable use of prefetch asm-instruction. You may need this to
//               | run on some very old machines.
//
// -DUSE_POPCNT  | Add runtime support for use of popcnt asm-instruction. Works
//               | only in 64-bit mode and requires hardware with popcnt support.
//
// -DUSE_PEXT    | Add runtime support for use of pext asm-instruction. Works
//               | only in 64-bit mode and requires hardware with pext support.

    #include <cassert>
    #include <cstdint>

    #if defined(_MSC_VER)
        // Disable some silly and noisy warnings from MSVC compiler
        #pragma warning(disable: 4127)  // Conditional expression is constant
        #pragma warning(disable: 4146)  // Unary minus operator applied to unsigned type
        #pragma warning(disable: 4800)  // Forcing value to bool 'true' or 'false'
    #endif

// Predefined macros hell:
//
// __GNUC__                Compiler is GCC, Clang or ICX
// __clang__               Compiler is Clang or ICX
// __INTEL_LLVM_COMPILER   Compiler is ICX
// _MSC_VER                Compiler is MSVC
// _WIN32                  Building on Windows (any)
// _WIN64                  Building on Windows 64 bit

    #if defined(__GNUC__) && (__GNUC__ < 9 || (__GNUC__ == 9 && __GNUC_MINOR__ <= 2)) \
      && defined(_WIN32) && !defined(__clang__)
        #define ALIGNAS_ON_STACK_VARIABLES_BROKEN
    #endif

    #define ASSERT_ALIGNED(ptr, alignment) assert(reinterpret_cast<uintptr_t>(ptr) % alignment == 0)

    #if defined(_WIN64) && defined(_MSC_VER)  // No Makefile used
        #include <intrin.h>                   // Microsoft header for _BitScanForward64()
        #define IS_64BIT
    #endif

    #if defined(USE_POPCNT) && defined(_MSC_VER)
        #include <nmmintrin.h>  // Microsoft header for _mm_popcnt_u64()
    #endif

    #if !defined(NO_PREFETCH) && defined(_MSC_VER)
        #include <xmmintrin.h>  // Microsoft header for _mm_prefetch()
    #endif

    #if defined(USE_PEXT)
        #include <immintrin.h>  // Header for _pext_u64() intrinsic
        #define pext(b, m) _pext_u64(b, m)
    #else
        #define pext(b, m) 0
    #endif


namespace chess_hexa{
    #ifdef USE_POPCNT
constexpr bool HasPopCnt = true;
    #else
constexpr bool HasPopCnt = false;
    #endif

    #ifdef USE_PEXT
constexpr bool HasPext = true;
    #else
constexpr bool HasPext = false;
    #endif

    #ifdef IS_64BIT
constexpr bool Is64Bit = true;
    #else
constexpr bool Is64Bit = false;
    #endif

using Key      = uint64_t;
using Bitboard = uint64_t;

constexpr int MAX_MOVES = 256;
constexpr int MAX_PLY   = 246;

enum Color {
    WHITE,
    BLACK,
    COLOR_NB = 2
};

enum CastlingRights {
    NO_CASTLING,
    WHITE_OO,
    WHITE_OOO = WHITE_OO << 1,
    BLACK_OO  = WHITE_OO << 2,
    BLACK_OOO = WHITE_OO << 3,

    KING_SIDE      = WHITE_OO | BLACK_OO,
    QUEEN_SIDE     = WHITE_OOO | BLACK_OOO,
    WHITE_CASTLING = WHITE_OO | WHITE_OOO,
    BLACK_CASTLING = BLACK_OO | BLACK_OOO,
    ANY_CASTLING   = WHITE_CASTLING | BLACK_CASTLING,

    CASTLING_RIGHT_NB = 16
};

enum PieceType {
    NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
    ALL_PIECES = 0,
    PIECE_TYPE_NB = 8
};

enum Piece {
    NO_PIECE,
    W_PAWN = PAWN,     W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = PAWN + 8, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NB = 16
};

enum Square : int {
    SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
    SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
    SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
    SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
    SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
    SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
    SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
    SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
    SQ_NONE,

    SQUARE_ZERO = 0,
    SQUARE_NB   = 64
};


enum Direction : int {
    NORTH = 8,
    EAST  = 1,
    SOUTH = -NORTH,
    WEST  = -EAST,

    NORTH_EAST = NORTH + EAST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST,
    NORTH_WEST = NORTH + WEST
};

enum File : int {
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NB
};

enum Rank : int {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NB
};
}
#endif  // #ifndef TYPES_H
