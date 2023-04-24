import ast
import functools
import inspect


def count_branches(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        wrapper.branch_count = 0
        
        def count_branches_helper(node):
            if isinstance(node, ast.If):
                wrapper.branch_count += 1
                count_branches_helper(node.body[0])
                if node.orelse:
                    orelse_node = node.orelse[0]
                    if isinstance(orelse_node, ast.If):
                        count_branches_helper(orelse_node) # Recurse on nested if

            elif isinstance(node, ast.IfExp):
                wrapper.branch_count += 1
                count_branches_helper(node.body)
                count_branches_helper(node.orelse)
                
            for child_node in ast.iter_child_nodes(node):
                count_branches_helper(child_node)
            
                    
        source = inspect.getsource(func)
        tree = ast.parse(source)
        count_branches_helper(tree)
        print(wrapper.branch_count)
        result = func(*args, **kwargs)
        return result
        
    return wrapper
@count_branches
def foo(bar):
    if bar:
        if bar == 'foo':
            return 'foobar'

    else:
        return 'bar'

def main():
    # print(foo('bar'))
    t = ast.parse(inspect.getsource(foo))
    print(ast.dump(t, indent=4))
    # print(inspect.getsource(foo))

if __name__ == '__main__':
    main()