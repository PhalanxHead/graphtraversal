# Assignment 1 for Design of Algorithms 2017 S1

## This assignment was in 7 Parts fully specified in specification.pdf

### Excerpts are available below

#### Part 1: Depth-First Traversal (1 mark)

Implement the function `print_dfs()` defined in traverse.c. This function takes as input a connected graph representing a road network, and the index of a starting town. The function should print the contents of the network as seen by a depth-first exploration starting from the given town. To ensure consistent output, process neighbouring towns in order of their appearance in the vertex edge list. The function should print to `stdout` one line with the name of each town, in the order they are visited.

#### Part 2: Breadth-First Traversal (1 mark)

Implement the function `print_bfs()` defined in `traverse.c`. This function takes as input a connected graph representing a road network, and the index of a starting town. This function should print the contents of the network as seen by a breadth-first exploration starting from the given town. To ensure consistent output, process neighbouring towns in order of their appearance in the vertex edge list. The function should print to `stdout` one line with the name of each town, in the order they are visited.

#### Part 3: Finding a Detailed Path (1 mark)

Implement the function `detailed_path()` defined in `traverse.c`. This function takes as input a connected graph representing a road network, the index of a starting town, and the index of a destination town. The function should find any simple path from the starting town to the destination town (a simple path does not contain any repeated vertices). The function should print this path, along with the cumulative distance of each town along the path (measured from the starting town). The function should print to `stdout` one line for each town on the path, from start to destination. Each line should contain the town name, a space, and then the cumulative distance along the path in parentheses.

#### Part 4: Finding All Paths (2 marks)

Implement the function `all_paths()` defined in `traverse.c`. This function takes as input a connected graph representing a road network, the index of a starting town, and the index of a destination town. The function should find and print all simple paths between the starting town and the destination town (a simple path does not contain any repeated vertices). Each path should be printed to `stdout` on a single line, as a list of town names each separated by a comma and a space. There should be no comma or space after the final town in each path.

#### Part 5: Finding the Shortest Path (2 marks)

Implement the function `shortest_path()` defined in `traverse.c`. This function takes as input a connected graph representing a road network, the index of a starting town, and the index of a destination town. The function should find and print the path from the starting town to the destination town with the shortest total distance. If there are multiple such paths, any one of them may be printed. This path should be printed to `stdout` on a single line, as a list of town names separated by a comma and a space. After the final town should be a space and then the total path distance in parentheses.

#### Part 6 and 7 are in report.pdf