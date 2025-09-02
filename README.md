# <strong>Minecraft Maze Generator-Builder-Solver (C++)</strong>

Demonstration Video:

https://rmiteduau-my.sharepoint.com/:v:/g/personal/s4106649_student_rmit_edu_au/EeTJxcRatcxJn-1Ny-GKkQoBOizTaK26bV_XeCGlvq_Y5Q?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=RciGG3

Member 1 - Talin Russo-Christoffelsz (s4106649)

    Base Program: Maze Generation, GenerateMaze

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

Member 2 - Kien Hung Ly (s3977367) (JensenLy on GitHub)

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

        Wall Follower Solving (rightHandSolve()):
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


    Enhancement: E2 (Shortest Path - Breadth First Search) (bfsSolve())
        This enhancement is done by using Breadth First Search algorithm. This 
        algorithm will add the current position into a "visited" vector and add 
        every possible steps into a "queue" vector from the current position. 
        Then it will try to step on all of the postions in "queue" vector that 
        is not in "visited" vector, repeat until it reaches the blue carpet.

        For tracing the path, I found out that it's the same thing as doing the
        BFS, but this time it goes from the exit and ends at the player's 
        original position (when I started the BFS) while only allowed to step
        on the positions that is in "visited" vector. Every step during the 
        tracing path part will be stored into a "path" vector. There will be 
        some duplicates in the "path" vector but they are removed by using: 
        vec.erase(std::unique(vec.begin(), vec.end()),vec.end());. Once I have 
        the "path" vector, I use it to set up a lime carpet trails similar to
        the one in rightHandSolve(). 

        When you run the BFS, you will notice the white carpets spawning, those
        are intended and will disappear when the solving is done. This is a 
        design choice to show to the player that the algorithm is working and 
        the agent is not freezing. Because BFS takes times, especially on larger
        mazes. 
        
        **Shout out to this video (https://www.youtube.com/watch?v=KiCBXu4P-2Y)
        for helping me figuring out the algorithm, especially the example from
        7:51 to 9:12 (I rewatched that part hundreds times :> ).**
        

Member 3 - Nathan Yong (s4090456)

    Base Program - Maze, LinkedListCoordinate, Node

        I created validation for building maze by first having a maze generated
        as you cannot build a maze without a generated one first to base of the
        build. I used a linked list as my data structure as it provides many 
        advantages such as dynamic size, efficient insertion and allowing to store
        two objects in one node. Therefore, makes the code more efficient and saves
        memory space as for arrays they will need two separate arrays to store 
        coordinate and blocktype. My program also only stores non-air blocks and thus
        saves more memory as it is not creating a 3D data structure to store every 
        block. 

        Enhancement: E1 Create a Maze Without Flattening the Terrain
        Before generating the maze i used ScanTerrainEnhancemnt()
        which checks blocks that have a a height of greater than 1
        block as a '\' which treats the it as an obstacle and uses
        it as part of the wall structure. Used the back tracking 
        algorithm to generate the maze based on the obstacles and
        builds around them. Then builds the maze like the base 
        program and restores it back to how it was before. 
