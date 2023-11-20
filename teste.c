#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct TreeNode {
    int key;                // Valor do nó
    struct TreeNode* left;  // Ponteiro para o filho esquerdo
    struct TreeNode* right; // Ponteiro para o filho direito
};

// Função para criar um novo nó
struct TreeNode* newNode(int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->key = value;
    node->left = node->right = NULL;
    return node;
}

// Função para inserir um novo valor na árvore
struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        return newNode(value);
    }

    if (value < root->key) {
        root->left = insert(root->left, value);
    } else if (value > root->key) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Função para buscar um valor na árvore
int search(struct TreeNode* root, int value) {
    if (root == NULL) {
        return 0;
    }

    if (root->key == value) {
        return 1;
    } else if (value < root->key) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Função para percorrer a árvore em ordem (inorder)
void inorder(struct TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Função para percorrer a árvore em pré-ordem (preorder)
void preorder(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Função para percorrer a árvore em pós-ordem (postorder)
void postorder(struct TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

// Função para encontrar o valor mínimo na árvore
struct TreeNode* minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Função para remover um valor da árvore
struct TreeNode* deleteNode(struct TreeNode* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->key) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->key) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Função para encontrar o valor máximo na árvore
struct TreeNode* maxValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current && current->right != NULL) {
        current = current->right;
    }
    return current;
}

// Função para liberar a memória alocada para a árvore
void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct TreeNode* root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    printf("Search for 70: %s\n", search(root, 70) ? "Found" : "Not found");
    printf("Search for 25: %s\n", search(root, 25) ? "Found" : "Not found");

    printf("Minimum value in the tree: %d\n", minValueNode(root)->key);
    printf("Maximum value in the tree: %d\n", maxValueNode(root)->key);

    root = deleteNode(root, 20);
    printf("Inorder traversal after deleting 20: ");
    inorder(root);
    printf("\n");

    freeTree(root); // Liberando memória

    return 0;
}
