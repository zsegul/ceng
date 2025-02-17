import random

#Function to get actions.
def get_actions():
    return ['>', '∨', '<', '∧']

#Function to read the file.
def read_mdp(file_name):
    mdp_info = {}
    file = open(file_name, 'r')
    section = None
    for line in file:
        line = line.strip()
        if line.startswith('[') and line.endswith(']'):
            section = line[1:-1]
            mdp_info[section] = []
        elif section == 'environment':
            mdp_info[section].extend(map(int,line.strip().split()))
        elif section=='action noise' or section=='learning rate' or section=='episode count' or section=='gamma' or section=='epsilon' or section=='reward':
            if '.' in line:
                mdp_info[section].append(float(line.strip()))
            else:
                mdp_info[section].append(int(line.strip()))
        elif section == 'start state':
            mdp_info[section].append( tuple(map(int, line.strip()[1:-1].split(','))))
        elif  section == 'goal states':
            state_reward_pairs = line.split('|')
            for pair in state_reward_pairs:
                pair_split = pair.split(':')
                state = tuple(map(int, pair_split[0].strip()[1:-1].split(',')))
                if len(pair_split) == 2:
                    reward = float(pair_split[1])
                else:
                    reward = None
                mdp_info[section].append((state, reward))
        else:
            states = line.split('|')
            for state in states:
                mdp_info[section].append(tuple(map(int, state.strip('()').split(','))))
    file.close()
    return mdp_info

#Function to define epsilon-greedy policy 
def epsilon_greedy_policy(state, Q_values, epsilon):
    if random.random() < epsilon:
        return random.choice(get_actions())
    else:
        return max(get_actions(), key=lambda a: Q_values[(state, a)])
    
#Q-learning algorithm implementation function
def q_learning(mdp_info, Q_values):
    epsilon = mdp_info['epsilon'][0]
    gamma = float(mdp_info['gamma'][0])
    learning_rate = float(mdp_info['learning rate'][0])
    episode_count = mdp_info['episode count'][0]
    for _ in range(episode_count):
        state = mdp_info['start state'][0]
        while state not in [goal_state[0] for goal_state in mdp_info['goal states']]:
            #Using epsilon-greedy policy to determine action.
            action = epsilon_greedy_policy(state, Q_values, epsilon)
            next_state, reward = perform_action(mdp_info, state, action)
            best_next_action = max(get_actions(), key=lambda a: Q_values[(next_state, a)])
            Q_values[(state, action)] += learning_rate * (reward + gamma * Q_values[(next_state, best_next_action)] - Q_values[(state, action)])
            state = next_state
    return Q_values


def perform_action(mdp_info, state, action):
    # Implement action noise.
    action_index = get_actions().index(action)
    actions = [action_index, (action_index - 1) % 4, (action_index + 1) % 4]
    action_noise = mdp_info['action noise']
    chosen_action_index = random.choices(actions, weights=action_noise)[0]
    chosen_action = get_actions()[chosen_action_index]
    
    next_state = get_next_state(state, chosen_action, mdp_info)
    reward = mdp_info['reward'][0]  
    
    if next_state in mdp_info['obstacle states']:
        reward = 0.0  
    elif next_state in [goal_state[0] for goal_state in mdp_info['goal states']]:
        reward = get_reward_for_goal_state(next_state, mdp_info)
    
    return next_state, reward   

def get_next_state(state, action, mdp_info):
    i, j = state
    M, N = mdp_info['environment']
    if action == '>':
        j = min(j + 1, N - 1)
    elif action == '∨':
        i = min(i + 1, M - 1)
    elif action == '<':
        j = max(j - 1, 0)
    elif action == '∧':
        i = max(i - 1, 0)
    next_state = (i, j)
    if next_state in mdp_info['obstacle states']:
        return state  
    return next_state

def get_reward_for_goal_state(state, mdp_info):
    for goal_state, reward in mdp_info['goal states']:
        if state == goal_state:
            return reward
    return 0.0

def extract_policy(mdp_info, Q_values):
    goals = []
    for (one, two) in mdp_info['goal states']:
        goals.append(tuple(one))
    policy = {}
    for state, action in Q_values.keys():
        if state not in mdp_info['obstacle states'] and state not in goals:
            if state not in policy:
                policy[state] = action
            else:
                if Q_values[(state, action)] > Q_values[(state, policy[state])]:
                    policy[state] = action
    return policy

def calculate_utility_scores(mdp_info, Q_values):
    goals = []
    for (one, two) in mdp_info['goal states']:
        goals.append(tuple(one))
    utility_scores = {}
    for state_action, value in Q_values.items():
        state, _ = state_action
        if state not in mdp_info['obstacle states']:
            if state not in goals:
                if state not in utility_scores:
                    utility_scores[state] = value
                else:
                    utility_scores[state] = max(utility_scores[state], value)
    return utility_scores

def SolveMDP(problem_file_name, random_seed):
    mdp_info = read_mdp(problem_file_name)
    random.seed(random_seed)

    #Initialize Q-values for all state-action pairs
    Q_values = {}
    for i in range(mdp_info['environment'][0]):
        for j in range(mdp_info['environment'][1]):
            state = (i, j)
            if state not in mdp_info['obstacle states']:
                for action in get_actions():
                    Q_values[(state, action)] = 0.0

    Q_values = q_learning(mdp_info, Q_values)    
    policy = extract_policy(mdp_info, Q_values)    
    utility_scores = calculate_utility_scores(mdp_info, Q_values)

    return utility_scores, policy

print(SolveMDP("mdp1.txt",462))