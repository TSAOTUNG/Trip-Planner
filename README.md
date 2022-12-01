# Trip-Planner

Description

First, the users is going to make a wish lists about the places they would want to go. Each tourist attraction is scored by their preference from 1 to 5. The system is hope to spend less time traveling among tourist attractions. Also, system assumes that the users prefer popular trip itineraries, so they will visit the tourist attractions base on the constant tourist flow. 

The system should help users find an optimal path given the origin and destination. When concerning the travel time, the path that costs the least time will be optimal. When concerning the tourist flow, the path that is the most possible to be taken will be optimal.

The system will accept 5 kinds of instructions, described as follows.
1. SET_ORIGIN : Assign a place as the origin of the traveling itinerary.The origin will not change until we reset it. 
2. MARK_STATE : Mark the state for a set of places with “open” or “close”. If a place is open, that place can be visited; otherwise, that place cannot be visited. All the places are open in the beginning. 
3. OPTIMAL_PATH : Choose a place as the destination of the trip. In terms of the assigned consideration, find the optimal path.
4. LIMITED_PATH : Choose a place as the destination of the trip. Decide a number K (2≦K≦100), which is the maximum number of stops the user wants to visit. 
5. END_OF_INSTRUCTION : Stop receiving instructions.
