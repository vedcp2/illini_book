The IlliniBook Library is meant for social network analysis, specifically made for exploring relationships within a network. It efficiently handles tasks such as determining connections between individuals, analyzing the depth of relationships, and identifying distinct groups within the network.

Features:
- Constructor (IlliniBook): Initializes the IlliniBook instance by reading people and their relationships from files.
- Graph Retrieval (GetGraph): Returns the underlying graph representing the network.
- Vertex Addition (AddVertex): Adds a new vertex to the network graph.
- Edge Addition (AddEdges): Establishes connections between vertices in the graph.
- Relation Checkers (AreRelated): Checks whether two individuals are related, with an option to specify the type of relationship.
- Relation Depth (GetRelated): Determines the degree of separation between two individuals.
- N-Step Connection (GetSteps): Finds all individuals at 'n' steps away from a given individual.
- DFS Utilities (DFS): Depth-First Search implementations for various relationship analysis.
- Group Counting (CountGroups): Counts the number of distinct groups or subnetworks within the graph.
