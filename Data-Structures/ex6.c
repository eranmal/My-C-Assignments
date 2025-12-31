#include "ex6.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define INT_BUFFER 128

void trimWhitespace(char *str)
{
    // Remove leading spaces/tabs/\r
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r')
        start++;

    if (start > 0)
    {
        int idx = 0;
        while (str[start])
            str[idx++] = str[start++];
        str[idx] = '\0';
    }

    // Remove trailing spaces/tabs/\r
    int len = (int)strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\r'))
    {
        str[--len] = '\0';
    }
}

char *myStrdup(const char *src)
{
    if (!src)
        return NULL;
    size_t len = strlen(src);
    char *dest = (char *)malloc(len + 1);
    if (!dest)
    {
        printf("Memory allocation failed in myStrdup.\n");
        return NULL;
    }
    strcpy(dest, src);
    return dest;
}

int readIntSafe(const char *prompt)
{
    char buffer[INT_BUFFER];
    int value;
    int success = 0;

    while (!success)
    {
        printf("%s", prompt);

        // If we fail to read, treat it as invalid
        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            printf("Invalid input.\n");
            clearerr(stdin);
            continue;
        }

        // 1) Strip any trailing \r or \n
        //    so "123\r\n" becomes "123"
        size_t len = strlen(buffer);
        if (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r'))
            buffer[--len] = '\0';
        if (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n'))
            buffer[--len] = '\0';
        // 2) Check if empty after stripping
        if (len == 0)
        {
            printf("Invalid input.\n");
            continue;
        }
        // 3) Attempt to parse integer with strtol
        char *endptr;
        value = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\0')
        {
            printf("Invalid input.\n");
        }
        else
        {
            // We got a valid integer
            success = 1;
        }
    }
    return value;
}

const char *getTypeName(PokemonType type)
{
    switch (type)
    {
    case GRASS:
        return "GRASS";
    case FIRE:
        return "FIRE";
    case WATER:
        return "WATER";
    case BUG:
        return "BUG";
    case NORMAL:
        return "NORMAL";
    case POISON:
        return "POISON";
    case ELECTRIC:
        return "ELECTRIC";
    case GROUND:
        return "GROUND";
    case FAIRY:
        return "FAIRY";
    case FIGHTING:
        return "FIGHTING";
    case PSYCHIC:
        return "PSYCHIC";
    case ROCK:
        return "ROCK";
    case GHOST:
        return "GHOST";
    case DRAGON:
        return "DRAGON";
    case ICE:
        return "ICE";
    default:
        return "UNKNOWN";
    }
}

char *getDynamicInput()
{
    char *input = NULL;
    size_t size = 0, capacity = 1;
    input = (char *)malloc(capacity);
    if (!input)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (size + 1 >= capacity)
        {
            capacity *= 2;
            char *temp = (char *)realloc(input, capacity);
            if (!temp)
            {
                printf("Memory reallocation failed.\n");
                free(input);
                return NULL;
            }
            input = temp;
        }
        input[size++] = (char)c;
    }
    input[size] = '\0';

    // Trim any leading/trailing whitespace or carriage returns
    trimWhitespace(input);

    return input;
}

// Function to print a single Pokemon node
void printPokemonNode(PokemonNode *node)
{
    if (!node)
        return;
    printf("ID: %d, Name: %s, Type: %s, HP: %d, Attack: %d, Can Evolve: %s\n",
           node->data->id,
           node->data->name,
           getTypeName(node->data->TYPE),
           node->data->hp,
           node->data->attack,
           (node->data->CAN_EVOLVE == CAN_EVOLVE) ? "Yes" : "No");
}
// BFS on the binary tree and send the current nose to a function
void BFSGeneric(PokemonNode *root, VisitNodeFunc visit) {
    int front = 0, rear = 0;
    if (!root) {
        return;
    }
    int size = sizeOfBinTree(root);
    // using queue for the BFS
    PokemonNode **queue = malloc(sizeof(PokemonNode *) * size);
    queue[rear++] = root;
    // if there are no more nodes
    while (front < rear) {
        PokemonNode *current = queue[front++];
        // print the father
        visit(current);
        // if there are childrens entering them to the queue, first left and than right
        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }
    free(queue);
}

// pre order on the binary tree and send the current node to a function
void preOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (!root) {
        return;
    }
    visit(root);
    preOrderGeneric(root->left, visit);
    preOrderGeneric(root->right, visit);
}
// in order on the binary tree and send the current nose to a function
void inOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (!root) {
        return;
    }
    inOrderGeneric(root->left, visit);
    visit(root);
    inOrderGeneric(root->right, visit);
}
// post order on the binary tree and send the current nose to a function
void postOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (!root) {
        return;
    }
    postOrderGeneric(root->left, visit);
    postOrderGeneric(root->right, visit);
    visit(root);
}
//initialize the Node array
void initNodeArray(NodeArray *na, int cap) {
    na->nodes = (PokemonNode **)malloc(cap * sizeof(PokemonNode *));
    na->size = 0;
    na->capacity = cap;
}

// adding node to the node array
void addNode(NodeArray *na, PokemonNode *node) {
    // if there is not enough space to more node
    if (na->size == na->capacity) {
        na->capacity *= RESIZE;
        na->nodes = (PokemonNode **)realloc(na->nodes, na->capacity * sizeof(PokemonNode *));
        if (!na->nodes) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
    // inserting the node in the next place in the array
    na->nodes[na->size++] = node;
}
// add every node in the tree to the node array, using recursion
void collectAll(PokemonNode *root, NodeArray *na) {
    if (root == NULL) {
        return;
    }
    addNode(na, root);
    collectAll(root->left, na);
    collectAll(root->right, na);
}

// printing the pokemons in alphabetic name
void displayAlphabetical(PokemonNode *root) {
    NodeArray nodeArr;
    // getting the size of the tree
    int capacity = sizeOfBinTree(root);
    // initialize the node array with the mount of pokemons in the tree
    initNodeArray(&nodeArr, capacity);
    // inserting all the pokemons to the array
    collectAll(root, &nodeArr);

    // sorting by name
    sortByName(&nodeArr, nodeArr.size);
    // printing the pokemons in their alphabetic order
    for (int i = 0; i < nodeArr.size; i++) {
        printPokemonNode(nodeArr.nodes[i]);
    }

    free(nodeArr.nodes);
}
// sorting the array by the pokemon names
void sortByName(NodeArray *nodeArr, int size) {
    PokemonNode* tempNode = NULL;
    int currentPlace = 0;
    // while the function didn't sort the whole array
    while (currentPlace < size) {
        for (int i = 0; i < size - currentPlace - 1; i++) {
            // compare the pokemon name using strcmp
            if (strcmp(nodeArr->nodes[i]->data->name, nodeArr->nodes[i+1]->data->name)> 0) {
                // if the word in the next place is bigger from the current, replace them
                tempNode = nodeArr->nodes[i];
                nodeArr->nodes[i] = nodeArr->nodes[i+1];
                nodeArr->nodes[i+1] = tempNode;
            }
        }
        // moving to the next word index
        currentPlace++;
    }
}
// printing the display options and sending to the one the user chose
void displayMenu(OwnerNode *owner)
{
    if (!owner->pokedexRoot)
    {
        printf("Pokedex is empty.\n");
        return;
    }

    printf("Display:\n");
    printf("1. BFS (Level-Order)\n");
    printf("2. Pre-Order\n");
    printf("3. In-Order\n");
    printf("4. Post-Order\n");
    printf("5. Alphabetical (by name)\n");

    int choice = readIntSafe("Your choice: ");

    switch (choice)
    {
    // BFS printing
    case 1:
        BFSGeneric(owner->pokedexRoot, printPokemonNode);
        break;
    // pre order printing
    case 2:
        preOrderGeneric(owner->pokedexRoot, printPokemonNode);
        break;
    // in order printing
    case 3:
        inOrderGeneric(owner->pokedexRoot, printPokemonNode);
        break;
    // post order printing
    case 4:
        postOrderGeneric(owner->pokedexRoot, printPokemonNode);
        break;
    // alphabetical printing
    case 5:
        displayAlphabetical(owner->pokedexRoot);
        break;
    default:
        printf("Invalid choice.\n");
    }
}
// function the checking if the pokemon the user chose is already in the tree
int idDuplicate(PokemonNode *node, int check) {
    // if the program checked the whole tree
    if (node == NULL) {
        return 1;
    }
    // if the id is already exist in the tree
    if (node->data->id == check) {
        return 0;
    }
    // if the id is smaller than the current node
    if (check < node->data->id) {
        return idDuplicate(node->left, check);
    }
    // if the id is bigger than the current node
    return idDuplicate(node->right, check);
}
// adding a new pokemon to the pokedex after the whole checking before
void addToPokdex(PokemonNode **node, int id) {
    // if the tree is empty or this is the place for the pokemon
    if (*node == NULL) {
        // creating a new node for the new pokemon
        *node = createPokemonNode(&pokedex[id-1], id);
        return;
    }

    // finding the right place using recursion call
    if (id < (*node)->data->id) {
        addToPokdex(&((*node)->left), id);
    } else if (id > (*node)->data->id) {
        addToPokdex(&((*node)->right), id);
    }
}
// adding new pokemon
void addPokemon(OwnerNode *owner) {
    // receive the id from the user
    int newPokemon = readIntSafe("Enter ID to add: ");
    // check if the id is legit
    if (newPokemon < 1 || newPokemon > MAX_POKEMON) {
        printf("Invalid ID.\n");
        return;
    }
    // if the pokedex is empty
    if (owner->pokedexRoot == NULL) {
        owner->pokedexRoot = createPokemonNode(pokedex, newPokemon);
        printf("Pokemon %s (ID %d) added.\n", pokedex[newPokemon-1].name, newPokemon);
        return;
    }
    // check if this pokemon is already in the tree
    if (idDuplicate(owner->pokedexRoot, newPokemon) == 0) {
        printf("Pokemon with ID %d is already in the Pokedex. No changes made.\n", newPokemon);
        return;
    }
    // adding the new pokemon
    addToPokdex(&owner->pokedexRoot, newPokemon);
    printf("Pokemon %s (ID %d) added.\n", pokedex[newPokemon-1].name, newPokemon);
}
// pokemon fight function
void pokemonFight(OwnerNode *owner) {
    // if there is no pokemon in the tree
    if (!owner->pokedexRoot) {
        printf("Pokedex is empty.\n");
        return;
    }
    int firstID = readIntSafe("Enter ID of the first Pokemon: ");
    int secondID = readIntSafe("Enter ID of the second Pokemon: ");
    // check if the user even have the pokemons he chose
    if (idDuplicate(owner->pokedexRoot, firstID) == 1 ||
        idDuplicate(owner->pokedexRoot, secondID) == 1) {
        printf("One or both Pokemon IDs not found.\n");
        return;
        }
    // calculating and printing the score of each pokemon
    float firstScore = ATTACK * pokedex[firstID-1].attack + HP * pokedex[firstID-1].hp;
    float secondScore = ATTACK * pokedex[secondID-1].attack + HP * pokedex[secondID-1].hp;
    printf("Pokemon 1: %s (Score = %.2f)", pokedex[firstID-1].name, firstScore);
    printf("\nPokemon 2: %s (Score = %.2f)", pokedex[secondID-1].name, secondScore);
    // declaring on the winner
    if (firstScore > secondScore) {
        printf("\n%s wins!\n", pokedex[firstID-1].name);
    } else if (firstScore < secondScore) {
        printf("\n%s wins!\n", pokedex[secondID-1].name);
    } else {
        printf("\nIt's a tie!\n");
    }
}
// freeing a pokemon from the tree
void freePokemon(OwnerNode *owner) {
    // if there is no pokemons in the tree
    if (!owner->pokedexRoot) {
        printf("No Pokemon to release.\n");
        return;
    }
    int deleteID = readIntSafe("Enter Pokemon ID to release: ");
    // check if the pokemon exists before removeing it
    if (idDuplicate(owner->pokedexRoot, deleteID) == 1) {
        printf("No Pokemon with ID %d found\n", deleteID);
        return;
    }
    printf("Removing Pokemon %s (ID %d).\n", pokedex[deleteID-1].name, deleteID);
    // remove the pokemon using a function
    owner->pokedexRoot = removePokemonByID(&(owner->pokedexRoot), deleteID);
}
// freeing node in a tree
void freePokemonNode(PokemonNode* node) {
    // if the node is null
    if (node == NULL) return;
    if (node->data != NULL) {
        //freeing the name, data and the node
        free(node->data->name);
        free(node->data);
    }
    free(node);
}
// removing pokemon by receiving his id
PokemonNode* removePokemonByID(PokemonNode** root, int id) {
    if (root == NULL || *root == NULL) {
        return NULL;
    }
    // finding the node of the given id by recursive search
    if (id < (*root)->data->id) {
        (*root)->left = removePokemonByID(&(*root)->left, id);
    } else if (id > (*root)->data->id) {
        (*root)->right = removePokemonByID(&(*root)->right, id);
      // finding the right node
    } else {
        PokemonNode* temp;
        // if the chosen node dosent have left child
        if ((*root)->left == NULL) {
            temp = (*root)->right;
            // freeing the root and replace him with the root who wased his right root
            freePokemonNode(*root);
            *root = temp;
        // if the chosen node dosent have left child
        } else if ((*root)->right == NULL) {
            temp = (*root)->left;
            // the same thing like the left root before
            freePokemonNode(*root);
            *root = temp;
        // if the chosen node have right and left childrens
        } else {
            // going one step right and thand just left for the right switch
            PokemonNode* successor = findMinimum((*root)->right);
            // replacing the successor with the deleted node
            (*root)->data->id = successor->data->id;
            free((*root)->data->name);
            (*root)->data->name = myStrdup(successor->data->name);
            (*root)->right = removePokemonByID(&(*root)->right, successor->data->id);
        }
    }
    return *root;
}
// find the minimum value in the tree
PokemonNode *findMinimum(PokemonNode *node) {
    if (!node) return NULL;
    // node is already went one right and now he goes just left for the minimun
    while (node->left) {
        node = node->left;
    }
    return node;
}
// evolving a pokemon
void evolvePokemon(OwnerNode *owner) {
    // if the user dosent have pokemons
    if (!owner->pokedexRoot) {
        printf("Cannot evolve. Pokedex empty.\n");
        return;
    }
    int evolveId = readIntSafe("Enter ID of Pokemon to evolve: ");
    // check if the user have the id he chose
    if (idDuplicate(owner->pokedexRoot, evolveId) == 1) {
        printf("No Pokemon with ID %d found.\n", evolveId);
        return;
    }
    // check if the pokemon can evolve
    if (pokedex[evolveId-1].CAN_EVOLVE == CANNOT_EVOLVE) {
        printf("%s cannot evolve.\n", pokedex[evolveId-1].name);
        return;
    }
    // check if the the user has already the evolution of the chosen pokemon
    if (idDuplicate(owner->pokedexRoot, evolveId+1) == 0) {
        // if the evolve id is in the tree, than relese it
        printf("Evolution ID %d (%s) already in the Pokedex. Releasing %s (ID %d).",
               evolveId+1, pokedex[evolveId].name, pokedex[evolveId-1].name, evolveId);
        printf("Removing Pokemon %s (ID %d).\n",pokedex[evolveId-1].name, evolveId);
        removePokemonByID(&owner->pokedexRoot, evolveId);
        return;
    }
    // removing the pokemon before the evolution
    removePokemonByID(&owner->pokedexRoot, evolveId);

    // adding the evolve from to the pokedex
    addToPokdex(&owner->pokedexRoot, evolveId+1);
    printf("Pokemon evolved from %s (ID %d) to %s (ID %d).\n",pokedex[evolveId-1].name, pokedex[evolveId-1].id,
        pokedex[evolveId].name, pokedex[evolveId].id );
}
// printing the owners
int printOwners() {
    // if there is no owners
    if (!ownerHead || !ownerHead->next) {
        printf("No existing Pokedexes.\n");
        return 0;
    }
    // declaring on to pointers to point the first owner
    OwnerNode *first = ownerHead->next;
    OwnerNode *current = first;
    int count = 0;
    // while the two pointers doesn't equal keep printing the owners
    do {
        count++;
        printf("%d. %s\n", count, current->ownerName);
        current = current->next;
    } while (current != first);

    return count;
}
// entering to exists owner
void enterExistingPokedexMenu()
{
    // printing the owners
    int num = printOwners();
    int choice;
    OwnerNode *cur = ownerHead;
    choice = readIntSafe("Choose a Pokedex by number:");
    while (choice > num || choice < 1) {
        printf("Invalid choice.\n");
        choice = readIntSafe("Choose a Pokedex by number:");
    }
    // select the owner the user chose by moving through the list 'choice' times
    for (int i = 0; i < choice; i++) {
        cur = cur->next;
    }
    printf("\nEntering %s's Pokedex...\n", cur->ownerName);
    int subChoice;
    do
    {
        printf("\n-- %s's Pokedex Menu --\n", cur->ownerName);
        printf("1. Add Pokemon\n");
        printf("2. Display Pokedex\n");
        printf("3. Release Pokemon (by ID)\n");
        printf("4. Pokemon Fight!\n");
        printf("5. Evolve Pokemon\n");
        printf("6. Back to Main\n");
        subChoice = readIntSafe("Your choice: ");

        switch (subChoice)
        {
        case 1:
            addPokemon(cur);
            break;
        case 2:
            displayMenu(cur);
            break;
        case 3:
            freePokemon(cur);
            break;
        case 4:
            pokemonFight(cur);
            break;
        case 5:
            evolvePokemon(cur);
            break;
        case 6:
            printf("Back to Main Menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (subChoice != 6);
}
// entering new owner
void openPokedexMenu() {
    int starter;
    // allocate memory for the new owner
    OwnerNode *owner = (OwnerNode *)malloc(sizeof(OwnerNode));
    if (!owner) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    printf("Your name: ");
    owner->ownerName = getDynamicInput();
    if (!owner->ownerName) {
        free(owner);
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // if this isnt the first owner
    if (ownerHead) {
        OwnerNode *current = ownerHead->next;
        // check if the owner is already exists
        do {
            // compering the user chosen name to the names that are already in
            if (current && strcmp(owner->ownerName, current->ownerName) == 0) {
                printf("Owner '%s' already exists. Not creating a new Pokedex.\n", owner->ownerName);
                free(owner->ownerName);
                free(owner);
                return;
            }
            current = current->next;
        } while (current && current != ownerHead->next);
    // if this is the first owner
    } else {
        // allocate memory for the owenr
        ownerHead = malloc(sizeof(OwnerNode));
        if (!ownerHead) {
            free(owner->ownerName);
            free(owner);
            printf("Memory allocation failed.\n");
            exit(1);
        }
        // initialize the values of the new owner
        ownerHead->prev = NULL;
        ownerHead->ownerName = NULL;
        ownerHead->pokedexRoot = NULL;
        ownerHead->next = NULL;
    }
    // choose the first pokemon
    do {
        starter = readIntSafe("Choose Starter:\n1. Bulbasaur\n2. Charmander\n3. Squirtle\nYour choice: ");
        if (starter < 1 || starter > 3) {
            printf("Invalid choice. Please choose 1-3.\n");
        }
    } while (starter < 1 || starter > 3);
    // change to the chosen pokemon id in the pokedex
    switch (starter) {
        case 1: {
            starter = BULBASAUR;
            break;
        }
        case 2: {
            starter = CHARMANDER;
            break;
        }
        case 3: {
            starter = SQUIRTLE;
            break;
        }
    }
    printf("New Pokedex created for %s with starter %s.\n",owner->ownerName, pokedex[starter-1].name);
    // create a new node for the new pokemon
    owner->pokedexRoot = createPokemonNode(&pokedex[starter-1], starter);
    // link the owner to the list
    linkOwnerInCircularList(owner);
}
// create new node for new pokemon
PokemonNode *createPokemonNode(const PokemonData *data, int id) {
    if (id < 1 || id > MAX_POKEMON || !data) {
        return NULL;
    }
    // allocate memory for the new node
    PokemonNode *node = (PokemonNode *)malloc(sizeof(PokemonNode));
    if (!node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // allocate memory for the pokemon data
    node->data = (PokemonData *)malloc(sizeof(PokemonData));
    if (!node->data) {
        free(node);
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // enter the pokemon name by his id
    node->data->name = myStrdup(pokedex[id-1].name);
    if (!node->data->name) {
        free(node->data);
        free(node);
        exit(1);
    }
    // entering the pokemon all his data according to his id
    node->data->id = id;
    node->data->TYPE = pokedex[id-1].TYPE;
    node->data->hp = pokedex[id-1].hp;
    node->data->attack = pokedex[id-1].attack;
    node->data->CAN_EVOLVE = pokedex[id-1].CAN_EVOLVE;
    node->left = NULL;
    node->right = NULL;
    return node;
}
// link new owner to the list
void linkOwnerInCircularList(OwnerNode *newOwner) {
    // if the list is empty
    if (ownerHead->next == NULL) {
        // point the global pointer to the new owner
        ownerHead->next = newOwner;
        // point the new owner on himself
        newOwner->next = newOwner;
        newOwner->prev = newOwner;
    // if the list not empty
    } else {
        // point the last owner in the list
        OwnerNode *temp = ownerHead->next->prev;
        // the last owner point next to the new one
        temp->next = newOwner;
        // the new owner point next on the first owner
        newOwner->next = ownerHead->next;
        // the new owner point perv on the last owner
        newOwner->prev = temp;
        // the first owner point perv on the new owner
        ownerHead->next->prev = newOwner;
    }
}
// deleting pokedex
void deletePokedex() {
    // if there is no pokedex
    if (!ownerHead || !ownerHead->next) {
        printf("No existing Pokedexes to delete.\n");
        return;
    }
    printf("\n=== Delete a Pokedex ===\n");
    // printing the options and saving the num of them
    int numOwners = printOwners();
    int choice = readIntSafe("Choose a Pokedex to delete by number: ");
    if( choice < 1 || choice > numOwners) {
        printf("Invalid choice.\n");
        return;
    }
    // getting the address of the chosen owner
    OwnerNode *cur = ownerHead->next;
    for (int i = 1; i < choice; i++) {
        cur = cur->next;
    }
    printf("Deleting %s's entire Pokedex...\n", cur->ownerName);
    // free the owner memory
    freeOwnerNode(cur);
    printf("Pokedex deleted.\n");
}
void freeOwnerNode(OwnerNode *owner) {
    if (!owner) return;
    // if there is only one owner
    if (owner->next == owner && owner->prev == owner) {
        ownerHead->next = NULL;
    } else {
        // point the prev owner to the next and the opposite
        owner->prev->next = owner->next;
        owner->next->prev = owner->prev;

        // if this is he first owner point the global pointer to the next
        if (ownerHead->next == owner) {
            ownerHead->next = owner->next;
        }
    }
    // freeing the tree
    freePokemonTree(owner->pokedexRoot);
    // free the name
    free(owner->ownerName);
    // free the owner
    free(owner);
}
// freeing the pokedex recursively
void freePokemonTree(PokemonNode *root) {
    if (root == NULL) {
        return;
    }
    freePokemonTree(root->left);
    freePokemonTree(root->right);
    // func that freeing the pokemon values
    freePokemonNode(root);
}
void mergePokedexMenu() {
    char ownerOne[MAX_NAME], ownerTwo[MAX_NAME];
    // if there is not enough pokemon owners to merge
    if (!ownerHead || !ownerHead->next || ownerHead->next == ownerHead->next->next) {
        printf("Not enough owners to merge.\n");
        return;
    }
    printf("\n=== Merge Pokedexes ===\n");
    // receiving the owners name from the user
    printf("Enter name of first owner: ");
    scanf("%s", ownerOne);
    printf("Enter name of second owner: ");
    scanf("%s", ownerTwo);

    // check if the owners exist in the list
    OwnerNode *own1 = NULL, *own2 = NULL;
    OwnerNode *current = ownerHead->next;
    do {
        // if he exist point to his place
        if (strcmp(current->ownerName, ownerOne) == 0) {
            own1 = current;
        }
        if (strcmp(current->ownerName, ownerTwo) == 0) {
            own2 = current;
        }
        // keep searching until full round
        current = current->next;
    } while (current != ownerHead->next);

    // check if the two owners founded
    if (!own1 || !own2) {
        printf("One or both owners not found.\n");
        return;
    }
    printf("Merging %s and %s...\n", own1->ownerName, own2->ownerName);
    // merge the owners
    mergePokedex(own2->pokedexRoot, &own1->pokedexRoot);
    printf("Merge completed.\n");
    printf("Owner '%s' has been removed after merging.\n", own2->ownerName);
    // delete the second owner
    freeOwnerNode(own2);
}
// func that calculate the size of the tree recursive
int sizeOfBinTree(PokemonNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + sizeOfBinTree(root->left) + sizeOfBinTree(root->right);
}
// merging owners pokedex
void mergePokedex(PokemonNode *first, PokemonNode **second) {
    int front = 0, rear = 0;
    if (!first) {
        return;
    }
    int size = sizeOfBinTree(first);
    // creating a queue in the size of the first bin tree
    PokemonNode **queue = malloc(sizeof(PokemonNode *) * size);
    if (!queue) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // entering the first node to the queue
    queue[rear++] = first;
    // while we checked all the tree
    while (front < rear) {
        // point to the next node
        PokemonNode *current = queue[front++];
        // check if the pokemon exist in the second pokedex
        if (idDuplicate(*second, current->data->id)) {
            // if he dosent exit, add him
            addToPokdex(second, current->data->id);
        }
        // if there are left and right childrens, add them to the queue
        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }
    free(queue);
}
// sorting owners by name
void sortOwners() {
    // if there is no owners or there is one owner
    if (!ownerHead || !ownerHead->next || ownerHead->next == ownerHead->next->next) {
        return;
    }
    int swapped;
    OwnerNode *current;
    do {
        swapped = 0;
        // pointing to the first owner
        current = ownerHead->next;
        // while we didnt checked the whole list
        while (current->next != ownerHead->next) {
            // if the next owner name is 'bigger', the owners need to swap places, else, move to the next owner
            if (strcmp(current->ownerName, current->next->ownerName) > 0) {
                // saving the values of the current owner
                char* tempName = current->ownerName;
                PokemonNode* tempPokedex = current->pokedexRoot;
                // swapping the values
                current->ownerName = current->next->ownerName;
                current->pokedexRoot = current->next->pokedexRoot;
                // inserting the saved value to the owner
                current->next->ownerName = tempName;
                current->next->pokedexRoot = tempPokedex;
                swapped = 1;
            }
            // moving to the next owner
            current = current->next;
        }
    } while (swapped);
    printf("Owners sorted by name.\n");
}
// swapping the owners data at the sorting
void swapOwnerData(OwnerNode *a, OwnerNode *b) {
    if (a == NULL || b == NULL || a == b) {
        printf("Invalid nodes\n");
        return;
    }
    // saving the name of the a owner
    char *tempName = a->ownerName;
    // replacing the names
    a->ownerName = b->ownerName;
    // insert the saved name
    b->ownerName = tempName;
    // same like the names but for the tree adress
    PokemonNode *tempPokedex = a->pokedexRoot;
    a->pokedexRoot = b->pokedexRoot;
    b->pokedexRoot = tempPokedex;
}
// printing the owners in the wanted direction and times
void printOwnersCircular() {
    int num = 1;
    char choice;
    // receiving the wanted direction from the user
    printf("Enter direction (F or B): ");
    scanf("%c", &choice);
    scanf("%*c");
    while (choice != 'f' && choice != 'b' && choice != 'F' && choice != 'B') {
        printf("Invalid direction, must be L or R.\n");
        printf("Enter direction (F or B): ");
        scanf("%c", &choice);
        scanf("%*c");
    }
    // recieving the num of times
    int numOfRounds = readIntSafe("How many prints? ");
    // pointer to the first owner
    OwnerNode *cur = ownerHead->next;
    // if there is only one owner
    if(cur->next == cur) {
        printf("[%d] %s\n",num, cur->ownerName);
    // if there is more than one owner
    }else {
        if(choice=='b' || choice=='B') {
            // printing 'back' in the wanted rounds, by pointing to the prev adrres
            for (int i = 0; i < numOfRounds; i++) {
                printf("[%d] %s\n",num, cur->ownerName);
                num++;
                cur = cur->prev;
            }
        }
        // same like the b printing
        if(choice=='f' || choice=='F') {
            for (int i = 0; i < numOfRounds; i++) {
                printf("[%d] %s\n",num, cur->ownerName);
                num++;
                cur = cur->next;
            }
        }
    }
}
// freeing all the owners
void freeAllOwners(void) {
    if (!ownerHead) return;
    // if there is no owners
    if (!ownerHead->next) {
        free(ownerHead);
        return;
    }
    // pointer to the first owner, help us by not entering to endless loop
    OwnerNode *first = ownerHead->next;
    // also pointing to the first, we will use it to free the owners
    OwnerNode *current = first;
    // pointer for not losing the next owner while deleting
    OwnerNode *next;

    // going through the whole list and free every owner
    do {
        next = current->next;
        // func that free the binary tree
        freePokemonTree(current->pokedexRoot);
        // freeing the name
        free(current->ownerName);
        // free the owner himself
        free(current);
        // moving to the next owner
        current = next;
    } while (current != first);

    // free the global pointer
    free(ownerHead);
    ownerHead = NULL;
}
void mainMenu()
{
    int choice, numOfOwner=0;
    do
    {
        printf("\n=== Main Menu ===\n");
        printf("1. New Pokedex\n");
        printf("2. Existing Pokedex\n");
        printf("3. Delete a Pokedex\n");
        printf("4. Merge Pokedexes\n");
        printf("5. Sort Owners by Name\n");
        printf("6. Print Owners in a direction X times\n");
        printf("7. Exit\n");
        choice = readIntSafe("Your choice: ");

        switch (choice)
        {
        // starting a new pokedex
        case 1:
            openPokedexMenu();
            // rising the num of owners
            numOfOwner++;
            break;
        // entering to exist pokedex
        case 2:
            // if there is no owners
            if(numOfOwner== 0) {
                printf("No existing Pokedexes.\n");
                break;
            }
            printf("\nExisting Pokedexes:\n");
            enterExistingPokedexMenu();
            break;
        // delete entire pokedex
        case 3:
            // if there is no pokedex to delete
            if(numOfOwner== 0) {
                printf("No existing Pokedexes to delete.\n");
                break;
            }
            deletePokedex();
            // reduce the num of owners
            numOfOwner--;
            break;
        // merge owners
        case 4:
            // if there is not enough owners
            if(numOfOwner <= 1) {
                printf("Not enough owners to merge.\n");
                break;
            }
            mergePokedexMenu();
            scanf("%*c");
            break;
        // sort by name
        case 5:
            // if there is no need of sort
            if(numOfOwner <= 1) {
                printf("0 or 1 owners only => no need to sort.\n");
                break;
            }
            sortOwners();
            break;
        // printing the owners circular
        case 6:
            if(numOfOwner== 0) {
                printf("No owners.\n");
                break;
            }
            printOwnersCircular();
            break;
        // break
        case 7:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid.\n");
        }
    } while (choice != 7);
}

int main()
{
    mainMenu();
    freeAllOwners();
    return 0;
}