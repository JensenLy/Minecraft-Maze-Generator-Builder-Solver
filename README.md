[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Jwdk2u8p)
# cosc2804-assignment3-template

Member 1 - Talin Russo-Christoffelsz (s4106649)

    Base Program: Maze Generation

        Read Maze from terminal:
            During my implementation of read maze from terminal I made an effort
            to validate the users input strictly to reduce any errors. I did 
            this by checking the input of the user and ensuring it adhered to
            the requirements to succesfully create a maze from the users input.
            I ensured the user knew what to do if there were problems as there 
            clear output indicating what is expected of the input from the user
            to create a maze.I created test case test_generateMaze3, 
            highlighting the validation outputs I used.

        Generate Random Maze:
            When generating the maze I used the recursive backtracking algorithm
            . I Implemented this through the class GenerateMaze. The 
            backtracking algorithm uses different functions that have been
            broken down to reduce repetitive code. The generation of the maze
            is highlighted in test_generateMaze1.
            

    Enhancement: E3
        During the implementation of the enhancement used the algorithm, flood
        fill to flood the maze, I was the able to identify if any isolations
        or loops existed. I also utelised some functions that I already had 
        implemented from generating random maze. The randomMove function allowed
        me to fix the loops and isolations, passing in a 'mode' char, where I
        could alter what the isValid function checked for. This reduced my need
        for creating new functions that did this. 

