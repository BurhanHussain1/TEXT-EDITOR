# TEXT-EDITOR (Console Notepad with Autocomplete + Compression)

A **Windows console-based notepad** written in C++ that supports:

- **Autocomplete suggestions** using a **Trie** (dictionary loaded from `outfile.txt`)
- **Save / Load** using **Huffman coding** (compressed text files)

## Quick Start (Windows)

1. Make sure `outfile.txt` exists in the same folder as the executable (or your working directory).
2. Build and run (see [Building & Running](#building--running-windows)).
3. Type using **lowercase letters** (`a`–`z`). Suggestions appear on the right.
4. Use the shortcuts below to select suggestions, save, and load.

## Features

- **Interactive typing UI** in the console (cursor movement + bordered layout)
- **Word suggestions** while typing (dictionary-backed)
- **Select a suggestion** to complete the current word
- **Save** current document to a file (compressed with Huffman codes)
- **Read** (decode) a previously saved file back into the editor
- **New document** without restarting the program

## Controls (Keyboard Shortcuts)

While the editor is running:

| Key | Action |
|---|---|
| `a`–`z` | Type (only lowercase letters are supported) |
| `Space` | Finish current word |
| `/` | Next suggestion (cycle) |
| `;` | Select highlighted suggestion |
| `=` | Save (prompts for file name) |
| `-` | Read / Load (prompts for file name) |
| `+` | New document (clears current text) |
| `Esc` | Exit (asks for confirmation) |

## Dictionary File (`outfile.txt`)

The autocomplete dictionary is loaded from `outfile.txt` at startup:

- Put **one word per whitespace** (spaces/newlines are fine).
- Words should be **lowercase `a`–`z`**.
- Example:

```txt
hello
help
helmet
world
word
work
```

## How It Works (High Level)

- **Trie autocomplete**: as you type a prefix, the program traverses the Trie and collects possible completions to show in the Suggestions panel.
- **Huffman save/load**:
  - **Save (`=`)**: counts letter frequencies, builds a Huffman tree, writes the frequency header, then writes Huffman codes for your text.
  - **Load (`-`)**: reads the frequency header to rebuild the same Huffman tree, then decodes the stored bits back into text.

## Building & Running (Windows)

This project uses Windows-specific headers (`Windows.h`) and console APIs, so it is intended for **Windows**.

### Option A: Visual Studio (recommended)

1. Create a new **Console App** project (C++) in Visual Studio.
2. Add these files to the project:
   - `main.cpp`
   - `consoleDesign.cpp`, `consoleDesign.h`
   - `trieTree.cpp`, `trieTree.h`
   - `huffMan.cpp`, `huffMan.h`
3. Ensure `outfile.txt` is present in the **working directory** (next to the `.exe` when you run).
4. Build and run.

### Option B: g++ / MinGW-w64

From the project folder:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o TEXT-EDITOR.exe main.cpp consoleDesign.cpp trieTree.cpp huffMan.cpp
.\TEXT-EDITOR.exe
```

## Project Structure

- `main.cpp`: program entry; loads dictionary and starts the editor loop
- `consoleDesign.*`: console UI + input handling + suggestion box rendering
- `trieTree.*`: Trie implementation + suggestion generation
- `huffMan.*`: Huffman tree generation + encode/decode for save/load
- `outfile.txt`: dictionary word list used for suggestions

## Notes / Limitations

- The editor is designed for **lowercase letters only** (`a`–`z`).
- Saved files store:
  - a header line containing **26 frequencies** (for Huffman reconstruction)
  - followed by the encoded bitstrings for the text (with spaces separating words)

## Troubleshooting

- **No suggestions show up**: make sure `outfile.txt` exists and contains lowercase words.
- **“File not found” when loading**: the program looks in the **current working directory**; put your saved file next to the `.exe` or run the program from the folder containing the file.
- **Weird output / missing letters**: only `a`–`z` + spaces are handled reliably in this implementation.

## Contributing

Pull requests and improvements are welcome. Good starter ideas:

- Support uppercase + punctuation
- Better cursor editing (backspace, arrow keys, multi-line editing)
- Cross-platform terminal support (remove `Windows.h` dependency)

## License

No license has been added yet. If you plan to share this publicly, consider adding a `LICENSE` file (e.g., MIT).

## Author

Made by **Burhan Hussain**.

