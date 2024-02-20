int tree_size(node_t *tree)
{
    int n1, n2;
    if (tree == NULL)
        return 0; // empty tree 
    n1 = tree_size(tree->left); // left subtree size
    n2 = tree_size(tree->right); // right subtree size
    return n1 + n2 + 1; // total size
}