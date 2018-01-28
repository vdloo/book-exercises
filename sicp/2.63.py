def entry(tree):
    return tree[0]

def left_branch(tree):
    return tree[1]

def right_branch(tree):
    return tree[2]

def make_tree(entry, left, right):
    return entry, left, right

def element_of_set(x, s):
    if not s:
        return False
    elif x == entry(s):
        return True
    elif x < entry(s):
        return element_of_set(x, left_branch(s))
    elif x > entry(s):
        return element_of_set(x, right_branch(s))

def adjoin_set(x, s):
    if not s:
        return make_tree(x, (), ())
    elif x == entry(s):
        return s
    elif x < entry(s):
        return make_tree(entry(s), adjoin_set(x, left_branch(s)), right_branch(s))
    elif x > entry(s):
        return make_tree(entry(s), left_branch(s), adjoin_set(x, right_branch(s)))

def tree_list_1(tree):
    if tree:
        left_entries = tree_list_1(left_branch(tree))
        right_entries = tree_list_1(right_branch(tree))
        current_entry = (entry(tree),)    # tuple of 1 (the current entry). Requires trailing , otherwise it's an int
        return left_entries + current_entry + right_entries
    else:
        return ()

def _copy_to_list(tree, result_list):
    if tree:
        return _copy_to_list(left_branch(tree), (entry(tree),) + _copy_to_list(right_branch(tree), result_list))
    else:
        return result_list

def tree_list_2(tree):
        return _copy_to_list(tree, ())

def set_from_list(seq):
    return reduce(lambda p, n: adjoin_set(n, p), seq, ())


tree1 = set_from_list([7, 3, 9, 1, 5, 11])
tree2 = set_from_list([3, 1, 7, 5, 9, 11])
tree3 = set_from_list([5, 3, 9, 1, 7, 11])

# a. The two procedures produce the same result for every tree
assert tree_list_1(tree1) == tree_list_2(tree1)
assert tree_list_1(tree2) == tree_list_2(tree2)
assert tree_list_1(tree3) == tree_list_2(tree3)

# b. 
# tree_list_1 would be O(n log n) if this was scheme and we used the append from the book,
# the second would be O(n) because cons is a O(n) operation. But because I used python builtin 
# tuple.__add__ both functions have O(n) complexity.
