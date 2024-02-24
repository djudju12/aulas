#!/usr/bin/python3

def parse_action(str_action: str):
    action = str_action.split(' ')
    if len(action) > 1: return (action[0], int(action[1]))
    else: return (action[0],)

def parse_set(str_set):
    return {int(n) for n in str_set.split(' ')}

def main():
    n = int(input())
    sed = parse_set(input())
    n_actions = int(input())
    for _ in range(n_actions):
        action = parse_action(input())
        action_name = action[0]
        try:
            if action_name == "remove": sed.remove(action[1])
            elif action_name == "discard": sed.discard(action[1])
            elif action_name == "pop": sed.pop()
        except:
            continue

    print(sum(sed))

if __name__ == '__main__':
    main()
