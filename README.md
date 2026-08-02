# sixChess

A Go (Weiqi) AI engine for 19x19 board games that uses heuristic-based strategies and line analysis to make moves.

## Description

sixChess is a computer Go program designed to play a 19x19 board Go game. It employs a scoring system to evaluate board positions by analyzing horizontal, vertical, and diagonal lines for potential "roads" (similar to Gomoku). The AI selects moves that optimize its scoring function, promoting favorable board states while countering the opponent's strategies. It communicates with a Go platform via standard input/output, responding to commands like `name?`, `new`, and `move`.

## Installation

To compile the AI, you need a C++ compiler (e.g., g++):

```bash
g++ -o sixChess chess.cpp
```

This generates an executable named `sixChess`.

## Usage

The AI interacts with a Go platform using text-based commands:

### Supported Commands

1. **`name?`**  
   - Triggers the AI to respond with its name (default: `name SixChess`).

2. **`new <color>`**  
   - Starts a new game.  
   - `<color>` can be `black` or `white`.  
   - Example: `new black` (AI plays as Black).

3. **`move <move>`**  
   - Opponent's move is provided.  
   - AI evaluates the board and outputs its move in the format `move <x1><y1><x2><y2>`, where coordinates follow Go notation (e.g., `move A9A10` for placing stones at A9 and A10).  

4. **`error`**  
   - Indicates an invalid move from the opponent. The AI ignores this and re-enters the move phase.

5. **`end`**  
   - Ends the current game. The AI resets for a new game.

6. **`quit`**  
   - Exit the AI session (outputs `Quit!`).

### Example Interaction

```plaintext
name?
name SixChess
new white
move A9
move B10B11
error
end
quit
```

## Key Features

- **Line Analysis**: Evaluates horizontal, vertical, and diagonal lines for strategic positioning.
- **Scoring System**: Uses predefined rules to weigh different "road" configurations (e.g., 1-stone road, 6-stone road).
- **Search Strategy**: Performs a lookahead search to choose moves that maximize AI score while minimizing opponent score.

## Notes

- The AI is designed to work with a Go platform that supports text-based command communication.
- Coordinates are encoded as uppercase letters for rows and columns (e.g., `A1` = row 0, column 0).
- The movement logic allows for both single-stone moves and captures (e.g., second move for capturing stones). 

## License

This project is open-source. Contributions or modifications should be discussed with the repository owner.
