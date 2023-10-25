#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int value;
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;

} TreeNode;

void InorderTraversal(const TreeNode* root);
int InsertValue(TreeNode* root, int value);
int DeleteValue(TreeNode* root, int value);

int main(void)
{
    int n;
    TreeNode root = { 50, NULL, NULL, NULL };

    printf("Enter no of values to insert in Tree: ");
    scanf("%d", &n);

    printf("Enter the values: ");
    for (int i = 0; i < n; i++)
    {
        int value;

        scanf("%d", &value);
        InsertValue(&root, value);
    }

    printf("Values inserted: ");
    InorderTraversal(&root);
    printf("\n");

    int value;
    printf("\nEnter the value to delete: ");
    scanf("%d", &value);

    DeleteValue(&root, value);

    printf("After deletion: ");
    InorderTraversal(&root);
    printf("\n");

    return 0;
}

void InorderTraversal(const TreeNode* root)
{
    if (root != NULL)
    {
        InorderTraversal(root->left);
        printf("%d ", root->value);
        InorderTraversal(root->right);
    }
}

int InsertValue(TreeNode* root, int value)
{
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));

    if (temp == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    temp->value = value;
    temp->left = NULL;
    temp->right = NULL;

    TreeNode* curr = root;
    TreeNode* parent = NULL;

    while (curr != NULL)
    {
        parent = curr;

        if (value < curr->value)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    if (parent != NULL)
    {
        if (value < parent->value)
        {
            parent->left = temp;
        }
        else
        {
            parent->right = temp;
        }

        temp->parent = parent;
    }
    else
    {
        root = temp;
    }
}

int DeleteValue(TreeNode* root, int value)
{
    TreeNode* curr = root;
    TreeNode* parent = NULL;

    while (curr != NULL && curr->value != value)
    {
        parent = curr;

        if (value < curr->value)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    if (curr != NULL)
    {
        TreeNode* temp;

        if (curr->left != NULL && curr->right != NULL)
        {
            temp = parent = curr;
            curr = curr->right;

            while (curr->left != NULL)
            {
                parent = curr;
                curr = curr->left;
            }

            temp->value = curr->value;
        }

        temp = curr;

        if (curr == parent->left)
        {
            if (curr->left != NULL)
            {
                parent->left = curr->left;
                curr->left->parent = parent;
            }
            else if (curr->right != NULL)
            {
                parent->left = curr->right;
                curr->right->parent = parent;
            }
            else
            {
                parent->left = NULL;
                free(temp);
            }
        }
        else if (curr == parent->right)
        {
            if (curr->right != NULL)
            {
                parent->right = curr->right;
                curr->right->parent = parent;
            }
            else if (curr->left != NULL)
            {
                parent->right = curr->left;
                curr->left->parent = parent;
            }
            else
            {
                parent->right = NULL;
                free(temp);
            }
        }
    }
}
