<a name="readme-top"></a>
# SudokuSolver

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#running-the-program">Running the Program</a></li>
      </ul>
    </li>
    <li><a href="#sample-output">Sample Output</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>


<!-- ABOUT THE PROJECT -->
## About The Project

![Product Name Screen Shot][product-screenshot]

This is a solver that takes in a partially filled sudoku board as an input and display the solved board as an output if there is a solution.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

All you need is a compiler that is able to compile c++ program. :)

### Running the program

1. Clone the repo
   ```sh
   git clone https://github.com/liangsiwei1994/SudokuSolver.git
   ```
2. Open the `main.cpp` file.
3. Load a sudoku board (in .dat format, "easy.dat" in this example) to be solved using the command
   ```sh
   load_board("easy.dat", board);
   ```
4. To solve the sudoku board, use the following function
   ```sh
   solve_board(board);
   ```
5. To display the sudoku board at any instant, use the following function
   ```js
   display_board(board);
   ```
6. To calculate the number of recursive calls needed and the total possible permutations to solve the board, use the function:
   ```js
   compare_board("easy.dat");
   ```
7. Open the terminal. Go to the folder/directory path and compile the program using the following command
   ```js
   make
   ```
8. In the same path, run the program using
   ```js
   ./sudoku
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- SAMPLE OUTPUT -->
## Sample Output

The following image shows the expected output based on the board is successfully solved.

![Sample Success Output Screenshot][samplesuccessoutput-screenshot]

The following image shows the expected output based on the board cannot be solved.

![Sample Failed Output Screenshot][samplefailedoutput-screenshot]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

SiWei - liang_siwei@hotmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Credits to setter of the project and the readme template designer vi-dev0.

* [Professor William Knottenbelt](https://www.imperial.ac.uk/people/w.knottenbelt)
* Tom Crossland - t.crossland22@imperial.ac.uk
* [vi-dev0](https://github.com/othneildrew/Best-README-Template.git)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
[product-screenshot]: images/SudokuBoard.png
[samplefailedoutput-screenshot]: images/SampleFailedOutput.png
[samplesuccessoutput-screenshot]: images/SampleSuccessOutput.png
