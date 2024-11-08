Video:

https://rmiteduau-my.sharepoint.com/:v:/g/personal/s4106649_student_rmit_edu_au/EeTJxcRatcxJn-1Ny-GKkQoBOizTaK26bV_XeCGlvq_Y5Q?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=RciGG3

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

Member 2 - Kien Hung Ly (s3977367)

    Base Program: Agent

        Manual Solve:
            Consist of manualSolve() and manualSolveTest(). These function 
            teleports the player to a point inside a builed maze (random or 
            pre-determined). For manualSolveTest(), the pre-determined position
            is calculated by using the formula of the distance between 2 points: 
            sqrt((x2 – x1)^2 + (y2 – y1)^2), but since one of 2 points used is 
            the origin of the maze (0,0), so I simplified it to sqrt(x^2 + y^2). 

            manualSolve() and manualSolveTest() will not work without the maze 
            built, it instead prints "Please build the maze first before 
            teleporting, doing so by pressing "2" on the main menu". 

        Wall Follower Solving (Right Hand):
            In the wall follower solving, I use an integer named "orientation"
            to indicate where the player is facing (the front, not right hand).
            For each step, I check the current position's (currPos) right, 
            front, back, and left respectively and take a step if there's 
            a free space (since it's right-hand wall follower so I have to
            prioritise/check the right hand side first). 
            
            Orientation is responsible to where the player is facing. Treat it
            like a circle where each number in orientation equals 90-degree.
            E.g. orientation = 5 = 450-degree = 90-degree (3 o-clock or east).

            The solver (Show Escape Path option) will not work before the player
            being teleported by "Manual Solve", it instead prints "Please use 
            "Manual Solve" before attempting to show the escape path by 
            pressing "1" in "Solve Maze" menu"


    Enhancement: E2 (Shortest Path - Breadth First Search)
        **TO DO: complete E2 description**

