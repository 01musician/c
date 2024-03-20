//gcc -o test-glib-tree test-glib-tree.c `pkg-config --cflags --libs glib-2.0`

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

// Define a custom compare function for integer keys
gint compare_int(gconstpointer a, gconstpointer b, gpointer user_data) {
    return *((int*)a) - *((int*)b);
}

// Print function for demonstration purposes
void print_int(gpointer key, gpointer value, gpointer user_data) {
    printf("%d: %d\n", *((int*)key), *((int*)value));
}

int main() {
    GTree *tree;
    tree = g_tree_new_full((GCompareDataFunc)compare_int, NULL, free, free); // Freeing keys and values

    // Insert some elements into the tree
    int *key1 = malloc(sizeof(int)); *key1 = 5;
    int *value1 = malloc(sizeof(int)); *value1 = 50;
    g_tree_insert(tree, key1, value1);

    int *key2 = malloc(sizeof(int)); *key2 = 3;
    int *value2 = malloc(sizeof(int)); *value2 = 30;
    g_tree_insert(tree, key2, value2);

    int *key3 = malloc(sizeof(int)); *key3 = 7;
    int *value3 = malloc(sizeof(int)); *value3 = 70;
    g_tree_insert(tree, key3, value3);

    // Print the contents of the tree (in-order traversal)
    printf("Tree contents after insertion:\n");
    g_tree_foreach(tree, (GTraverseFunc)print_int, NULL);

    // Search for an element
    int search_key = 3;
    int *result = g_tree_lookup(tree, &search_key);
    if (result != NULL) {
        printf("Found value for key %d: %d\n", search_key, *result);
    } else {
        printf("Key %d not found\n", search_key);
    }

    // Delete an element
    int delete_key = 5;
    if (g_tree_remove(tree, &delete_key)) {
        printf("Element with key %d deleted.\n", delete_key);
    } else {
        printf("Element with key %d not found.\n", delete_key);
    }

    // Print the contents of the tree after deletion
    printf("Tree contents after deletion:\n");
    g_tree_foreach(tree, (GTraverseFunc)print_int, NULL);

    // Free memory allocated for the tree
    g_tree_destroy(tree);

    return 0;
}

