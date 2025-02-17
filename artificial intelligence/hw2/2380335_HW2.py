# Heuristic function that I use changes according to the distance between the empty tile and the misplaced,non-empty tiles. 
# My heuristic function is admissible because it doesn't overestimate the real cost since it increases the heuristic cost 
# at most 2, when the distance may be 3. For example, if n=2, state is 'WEWBB', and the goal state is 'WWEBB' my heuristic 
# function return 1, the same as the cost, since there is only one misplaced and non-empty tile(index=3) and its distance 
# to the empty tile is 1. 

import heapq

def heuristic_function(state, goal_state):
    heuristic = 0
    for i in range(len(state)):
        if state[i] != goal_state[i] and state[i] != 'E':
            if abs(state.index('E')-i) == 1:
                heuristic += 1
            elif abs(state.index('E')-i) <=3:
                heuristic += 2
    return heuristic
    

def possible_moves(state):
    moves = []
    empty_index = state.index('E')

    for i in range(0,len(state)):
        if state[i] == 'E':
            continue
        for j in range(0,len(state)):
            if abs(i - j) <= 3 and state[j] == 'E':
                cost = abs(j - empty_index)
                moves.append((swap_tiles(state, i, j), cost))
    return moves

def swap_tiles(state, i, j):
    state_list = list(state)
    state_list[i], state_list[j] = state_list[j], state_list[i]
    return ''.join(state_list)

# A*
def astar(start, goal):
    if start == goal:
        return [(start, 0)], 0

    open_set = [(0, start)]
    came_from = {}
    g_score = {start: 0}
    f_score = {start: heuristic_function(start, goal)}

    while open_set:
        current = heapq.heappop(open_set)[1]

        if current == goal:
            path = [current]
            while current in came_from:
                current = came_from[current]
                path.append(current)
            path.reverse()
            return path, g_score[goal]

        for neighbor, cost in possible_moves(current):
            tentative_g_score = g_score[current] + cost
            if neighbor not in g_score or tentative_g_score < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g_score
                f_score[neighbor] = tentative_g_score + heuristic_function(neighbor, goal)
                heapq.heappush(open_set, (f_score[neighbor], neighbor))

    return [], 0

def main():
    n = int(input())
    initial_config = input().strip()
    final_config = input().strip()

    solution_path, total_cost = astar(initial_config, final_config)
    total_cost = 0 
    for i in range(0,len(solution_path)-1):
        if abs(solution_path[i].index('E') - solution_path[i+1].index('E'))==3 or abs(solution_path[i].index('E') - solution_path[i+1].index('E'))==2 :
            total_cost += abs(solution_path[i].index('E') - solution_path[i+1].index('E'))-1
        if abs(solution_path[i].index('E') - solution_path[i+1].index('E')) == 1 :
            total_cost += 1

    if solution_path:
        print(f"({len(solution_path)-1},{total_cost})")
        print(solution_path)
    else:
        print("(0,0)")
        print([initial_config])

main()