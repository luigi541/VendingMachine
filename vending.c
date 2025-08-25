#include <stdio.h>
#include <stdlib.h> // Include the necessary header for the exit function

// Dimensions of the machine
#define ROWS 8
#define COLS 8

// Struct for the expiration date
typedef struct expirationDate
{
    int Day;
    int month;
    int year;
} expiration;

// we dicided to use enumeration because we only have this five values, and we wanted to restrict the user options
// if we went with the char option, would alow the user to intruduce any category and we would have to had an extra validation...
typedef enum
{
    C, // cerveja
    A, // agua
    S, // sumo
    R, // refrigerante
    L  // leite
} Category;
// Struct for a vending item
typedef struct VendingItem
{
    char name[20];
    double price;
    int quantity;
    expiration expDate;
    Category category;

} VendingItem;

/**
    HELPER FUNCTIONS
*/
// utility function to be used before printing
void beginPrint()
{
    printf("\n =============== Begin ==============\n\n");
}
// utility function to be used after printing
void endPrint()
{
    printf("\n =============== End ===============\n\n");
}

/**
 * utility function that ensure us that the input of our user is a number and is between our limits
 */
int askMenuOption(int bottomLimit, int topLimit)
{
    int selectedValue;

    do
    {
        printf("Enter your choice: ");
        if (scanf("%d", &selectedValue) != 1)
        {
            // Invalid input, clear the input buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter an integer.\n");
        }
    } while (selectedValue < bottomLimit || selectedValue > topLimit);

    return selectedValue;
}

/**
 * asking a user to choose a row
 * we use do while here to make sure the user selects a valid number
 */

int askRowOrCol(char *type)
{
    int selectedValue;

    do
    {
        printf("Select a %s from 1 to 8: ", type);

        if (scanf("%d", &selectedValue) != 1)
        {
            // Invalid input, clear the input buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter an integer.\n");
        }
    } while (selectedValue < 1 || selectedValue > 8);

    return selectedValue - 1;
}

/** utility function to ask a category to the user*/
Category askCategory()
{
    char category;

    do
    {
        printf("Select one of the following categories [C (cervejas), A (águas), S (sumos), R (refrigerantes), L (leite)]: ");
        scanf(" %c", &category);
    } while (category != 'C' && category != 'A' && category != 'S' && category != 'R' && category != 'L');

    switch (category)
    {
    case 'C':
        return C;
    case 'A':
        return A;
    case 'S':
        return S;
    case 'R':
        return R;
    case 'L':
        return L;
    default:

        return C;
    }
}

/* utility function for printing a vending item*/
void printItem(VendingItem item)
{
    printf("Beverage: %s\n", item.name);
    printf("Price: %.2f\n", item.price);
    printf("Quantity: %d\n", item.quantity);
    printf("Expiration Date: %d/%d/%d\n", item.expDate.Day, item.expDate.month, item.expDate.year);

    switch (item.category)
    {
    case C:
        printf("Category: Cervejas\n\n");
        break;
    case A:
        printf("Category: Aguas\n\n");
        break;
    case S:
        printf("Category: Sumos\n\n");
        break;
    case R:
        printf("Category: Refrigerantes\n\n");
        break;
    case L:
        printf("Category: Leite\n\n");
        break;
    default:
        break;
    }
}

/**
    Function that calculates the price average of all items
*/
double calculateAverage(VendingItem vendingMachine[ROWS][COLS])
{
    int totalItems = 0;
    double totalPrices = 0.0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            // incrementing the total number of items
            totalItems = totalItems + vendingMachine[i][k].quantity;

            // calculating the total price by multiplying the item price with the item quantity and then sum it to the totalPrices
            double itemPrices = vendingMachine[i][k].price * vendingMachine[i][k].quantity;
            totalPrices = totalPrices + itemPrices;
        }
    }

    double average = totalPrices / totalItems;
    return average;
}

/**
    FUNCTIONS
*/
/**
 * 16. Listar os tipos de produtos que estão fora do prazo de validade (opcional);
 */
void ExtraPoints(VendingItem vendingMachine[ROWS][COLS])
{

    beginPrint();
    int CurrentYear;
    int CurrentDay;
    int CurrentMonth;

    printf("============= Enter current date: ===========\n\n\n");
    printf("Current year: ");
    scanf("%d", &CurrentYear);
    printf("Current month: ");
    scanf("%d", &CurrentMonth);
    printf("current day: ");
    scanf("%d", &CurrentDay);
    printf("\n\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {

            if (CurrentYear > vendingMachine[i][k].expDate.year)
            {
                printItem(vendingMachine[i][k]);
                printf("\nitem already expired");
            }
            else if (CurrentYear == vendingMachine[i][k].expDate.year)
            {
                if (vendingMachine[i][k].expDate.month < CurrentMonth || vendingMachine[i][k].expDate.month == CurrentMonth && vendingMachine[i][k].expDate.Day < CurrentDay)
                {
                    printItem(vendingMachine[i][k]);
                    printf("\nitem expired");
                }
                else
                {
                    printf("\nNo items expired");
                }
            }
        }
    }

    endPrint();
}

/**
 * this function adds an item to a position
 * if the position is occupied then it doesn't add anything
 * 1.Inserir um novo produto, dado o número da prateleira e posição
 */
void addItem(VendingItem vendingMachine[ROWS][COLS])
{
    int row = askRowOrCol("row");
    int col = askRowOrCol("col");

    VendingItem item = vendingMachine[row][col];

    if (item.quantity != 0)
    {
        printf("there is already a product in that position !!\n");
        return;
    }

    printf("Enter the name of the new item: ");
    scanf(" %s", &vendingMachine[row][col].name);

    printf("Enter the price of the new item: ");
    scanf("%lf", &vendingMachine[row][col].price);

    int selectedQuantity;
    do
    {
        printf("Enter the quantity of the new item: ");
        scanf("%d", &selectedQuantity);
    } while (selectedQuantity > 10 || selectedQuantity < 0);

    vendingMachine[row][col].quantity = selectedQuantity;

    printf("Enter the expiration date of the new item (DD MM YYYY): ");
    scanf("%d %d %d", &vendingMachine[row][col].expDate.Day, &vendingMachine[row][col].expDate.month, &vendingMachine[row][col].expDate.year);

    vendingMachine[row][col].category = askCategory();

    printf("New item added successfully!\n");
}

/**
 * this function calculates the total stock in the machine
 * and prints the total amount
 * 9. Saber o stock total atual (totalidade de produtos existentes na máquina);
 */
void showTotalStock(VendingItem vendingMachine[ROWS][COLS])
{
    int result = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            result = result + vendingMachine[i][k].quantity;
        }
    }
    beginPrint();
    printf("Total stock amount: %d", result);
    endPrint();
}

/**
 * this function calculates the total stock by category in the machine
 * and prints the total amount
 * 14. Listar para cada tipo de produtos (água, cerveja, etc.), a quantidade de stock atual;
 */
void showTotalStockByCategory(VendingItem vendingMachine[ROWS][COLS])
{
    int result = 0;
    Category userCategory = askCategory(); // we want to compare the category input by the user to the one from our vending machine

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].category == userCategory)
            {
                result = result + vendingMachine[i][k].quantity;
            }
        }
    }
    beginPrint();
    printf("Total stock amount for category: %d", result);
    endPrint();
}

/**
 * 15. Somatório do valor (em €) de todos os produtos armazenados na máquina (ainda não vendidos);
 */
void showTotalAvailableItemsPrice(VendingItem vendingMachine[ROWS][COLS])
{
    double totalPrices = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].quantity > 0)
            {
                totalPrices += vendingMachine[i][k].quantity * vendingMachine[i][k].price;
            }
        }
    }
    beginPrint();
    printf("Total price: %.2f€", totalPrices);
    endPrint();
}

/**
 * function  who recives the vending machine and ask the user to chose an item and print
 * 3. Listar a informação sobre um produto específico, dada a localização (prateleira e posição);
 */
void showItemInfo(VendingItem vendingMachine[ROWS][COLS])
{

    int selectedRow = askRowOrCol("row");
    int selectedCol = askRowOrCol("col");

    VendingItem item = vendingMachine[selectedRow][selectedCol];
    beginPrint();
    printItem(item);
    endPrint();
}

/**
 * this function prints all items from the machine
 * 2. Listar a informação de todos os produtos disponíveis;
 */
void showAllinfo(VendingItem vendingMachine[ROWS][COLS])
{
    beginPrint();
    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            VendingItem item = vendingMachine[i][k];
            printItem(item);
        }
    }
    endPrint();
}

/**
 * 7. Saber o valor, em €, acumulado na máquina até ao momento;
 */
void showTotalBalance(double *machineAmount)
{
    beginPrint();
    printf("Machine total balance: %.2f", *machineAmount);
    endPrint();
}

/**
 * this function allows the user to buy an item from the machine
 * 4. Simular a compra de um produto pelo utilizador, onde deverá somar ao total dinheiro na
máquina o preço do produto;
 */
void buyItem(VendingItem vendingMachine[ROWS][COLS], double *machineAmount)
{
    int row = askRowOrCol("row");
    int col = askRowOrCol("col");
    /**
     * 1- ir buscar o sitio do item onde esta o produto
     * 2- verificar se temos quantidade do produto (>0)
     * 3- decrementar quantidade em 1
     * 4-aumentar ao saldo o preço do produto
     */
    VendingItem item = vendingMachine[row][col];

    if (item.quantity < 1)
    {
        printf("sorry but this Bevarage is out of stock\n");
        return;
    }
    beginPrint();
    printf("dispensing..\n");
    printf("Beverage: %s\n", item.name);
    printf("Price: %.2f\n", item.price);
    printf("Quantity: %d\n", --item.quantity); // --  when this operator is left of the variable, it decreases the value before using it
    printf("Expiration Date: %d/%d/%d\n", item.expDate.Day, item.expDate.month, item.expDate.year);
    endPrint();

    vendingMachine[row][col].quantity--;

    *machineAmount = *machineAmount + item.price;
}

/**
 * this function allows the user to edit all prices in the machine by selecting a percentage
 * 6. Atualizar, numa percentagem, o preço de todos os produtos;
 */
void editPricesPercentage(VendingItem vendingMachine[ROWS][COLS])
{
    int selectedPercentage;
    do
    {
        printf("whats the percentage from 0 to 100 ?\n");
        scanf("%d", &selectedPercentage);

    } while (selectedPercentage < 0 || selectedPercentage > 100);

    if (selectedPercentage == 0)
    {
        return;
    }

    double percentageMultiplier = (selectedPercentage / 100.0) + 1.0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            vendingMachine[i][j].price = vendingMachine[i][j].price * percentageMultiplier;
        }
    }
    printf("Successfully applied the price increase of %d", selectedPercentage);
}

/**
 *this function edits the price for just one item
 5. Atualizar o preço de um determinado produto, identificado pelo utilizador;
 */
void editItemPrice(VendingItem vendingMachine[ROWS][COLS])
{
    int row = askRowOrCol("row");
    int col = askRowOrCol("col");

    printf("Please type the new price: \n");
    scanf("%lf", &vendingMachine[row][col].price);

    printf("Price editing went successfully!");
}

/**
 * in this function we fill the machine and collect the balance if requested by the user
 * 8. Reabastecer a máquina e recolher o dinheiro existente na máquina;
 */
void refuelMachine(VendingItem vendingMachine[ROWS][COLS], double *machineAmount)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            vendingMachine[i][j].quantity = 10;
        }
    }
    printf("Machine is now full.\n\n");

    char value;
    do
    {
        printf("Do you want to collect the balance? Reply with Y (yes) or N (no)");
        scanf(" %c", &value);
    } while (value != 'Y' && value != 'N');

    if (value == 'Y')
    {
        *machineAmount = 0;
        printf("Successfully collected the balance. Current balance is now: 0.00€");
    }
}

/**
 * 10. Saber a informação sobre o(s) produto(s) com quantidade em stock mais baixa;
 */
void showLowestItem(VendingItem vendingMachine[ROWS][COLS])
{
    int lowestQuantity = 10;

    beginPrint();

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].quantity < lowestQuantity)
            {
                lowestQuantity = vendingMachine[i][k].quantity;
            }
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].quantity == lowestQuantity)
            {
                printItem(vendingMachine[i][k]);
            }
        }
    }

    endPrint();
}

/**
    Function that shows the average price of all items
    11. Calcular a média dos preços dos produtos;
*/
void showMediumPrice(VendingItem vendingMachine[ROWS][COLS])
{
    double average = calculateAverage(vendingMachine);

    beginPrint();
    printf("the average price is %.2f", average);
    endPrint();
}

/**
    Function that shows all items above the average price
    12. Listar os produtos com preço acima da média.;
*/
void showItemsAboveTheAverage(VendingItem vendingMachine[ROWS][COLS])
{
    double average = calculateAverage(vendingMachine);

    beginPrint();
    for (int i = 0; i < ROWS; i++)
    {
        for (int t = 0; t < COLS; t++)
        {
            if (average < vendingMachine[i][t].price)
            {
                printItem(vendingMachine[i][t]);
            }
        }
    }
    endPrint();
}

/**
 * this function shows all items with the heighest quanity
 */
void showHighestItem(VendingItem vendingMachine[ROWS][COLS])
{
    int highestQuantity = 0;
    beginPrint();

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].quantity > highestQuantity)
            {
                highestQuantity = vendingMachine[i][k].quantity;
            }
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].quantity == highestQuantity)
            {
                printItem(vendingMachine[i][k]);
            }
        }
    }

    endPrint();
}

/**
 * 13. Saber a informação sobre o(s) produto(s) com preço mais alto;
 */
void showHighestPrice(VendingItem vendingMachine[ROWS][COLS])
{
    double highestPrice = 0.0;
    beginPrint();

    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].price > highestPrice)
            {
                highestPrice = vendingMachine[i][k].price;
            }
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int k = 0; k < COLS; k++)
        {
            if (vendingMachine[i][k].price == highestPrice)
            {
                printItem(vendingMachine[i][k]);
            }
        }
    }

    endPrint();
}

/**
    MENUS
*/
void renderDisplayMenu(VendingItem vendingMachine[ROWS][COLS], double *machineAmount)
{
    int choice;
    do
    {
        beginPrint();
        printf("1. Display all items info\n");
        printf("2. Show one item information\n");
        printf("3. Show total stock value\n");
        printf("4. Show total balance\n");
        printf("5. Back\n\n");

        choice = askMenuOption(1, 5);
        endPrint();

        switch (choice)
        {
        case 1:
            showAllinfo(vendingMachine);
            break;
        case 2:
            showItemInfo(vendingMachine);
            break;
        case 3:
            showTotalAvailableItemsPrice(vendingMachine);
            break;
        case 4:
            showTotalBalance(machineAmount);
            break;
        default:
            break;
        }

    } while (choice < 1 || choice > 5);
}

void renderStockMenu(VendingItem vendingMachine[ROWS][COLS], double *machineAmount)
{
    int choice;
    do
    {
        beginPrint();
        printf("1. Add item\n");
        printf("2. Show total stock amount\n");
        printf("3. Show total amount by categories\n");
        printf("4. Refuel machine and collect balance\n");
        printf("5. Show lowest stock item\n");
        printf("6. Show highest stock item\n");
        printf("7. Back\n\n");

        choice = askMenuOption(1, 7);
        endPrint();

        switch (choice)
        {
        case 1:
            addItem(vendingMachine);
            break;
        case 2:
            showTotalStock(vendingMachine);
            break;
        case 3:
            showTotalStockByCategory(vendingMachine);
            break;
        case 4:
            refuelMachine(vendingMachine, machineAmount);
            break;
        case 5:
            showLowestItem(vendingMachine);
            break;
        case 6:
            showHighestItem(vendingMachine);
            break;
        default:
            break;
        }

    } while (choice < 1 || choice > 7);
}

void renderPricesMenu(VendingItem vendingMachine[ROWS][COLS])
{
    int choice;
    do
    {
        beginPrint();
        printf("1. Edit all prices by percentage\n");
        printf("2. Edit item price\n");
        printf("3. Show medium price\n");
        printf("4. Show items above average price\n");
        printf("5. Show items with highest price\n");
        printf("6. Back\n\n");

        choice = askMenuOption(1, 6);
        endPrint();

        switch (choice)
        {
        case 1:
            editPricesPercentage(vendingMachine);
            break;
        case 2:
            editItemPrice(vendingMachine);
            break;
        case 3:
            showMediumPrice(vendingMachine);
            break;
        case 4:
            showItemsAboveTheAverage(vendingMachine);
            break;
        case 5:
            showHighestPrice(vendingMachine);
            break;
        default:
            break;
        }
    } while (choice > 6 || choice < 1);
}

void initialMenu(VendingItem vendingMachine[ROWS][COLS], double *machineAmount)
{
    int choice;
    do // ciclo encadeado
    {
        beginPrint();
        printf("1. Display products\n");
        printf("2. Buy an item\n");
        printf("3. Stock management\n");
        printf("4. Price management\n");
        printf("5. Check if there are items expired\n");
        printf("6. Exit\n\n");

        choice = askMenuOption(1, 6);

        endPrint();

        switch (choice)
        {
        case 1:
            renderDisplayMenu(vendingMachine, machineAmount);
            break;
        case 2:
            buyItem(vendingMachine, machineAmount);
            break;
        case 3:
            renderStockMenu(vendingMachine, machineAmount);
            break;
        case 4:
            renderPricesMenu(vendingMachine);
            break;
        case 5:
            ExtraPoints(vendingMachine);
            break;
        case 6:
            printf("Quitting program!\n");
            exit(0); // Use the exit function to terminate the program
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
            break;
        }
    } while (choice != 6);
}

/**
 * our main with only our machine and amount
 */
int main()
{
    double machineAmount = 10.0;
    // declarei uma variavel machineAmountPointer e como quero que seja um apontador tenho que adicionar o *
    // este apontador vai apontar para onde? para o endereço em memória da varavel machineAmount então para isso eu uso o & seguido da variavel que quero
    double *machineAmountPointer = &machineAmount;
    // Declare and initialize a 2D array of VendingItem
    VendingItem vendingMachine[ROWS][COLS] = {
        {{"",
          0,
          0,
          {1, 12, 2050},
          S},
         {"Sumo laranja", 1.25, 8, {1, 1, 2024}, S},
         {"Luso", 0.50, 10, {1, 3, 2026}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, R}},
        {{"Guarana",
          1,
          3,
          {1, 12, 2050},
          S},
         {"Sumo laranja", 1.25, 8, {1, 12, 2050}, S},
         {"Luso", 0.50, 10, {1, 12, 2025}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, S}},
        {{"Guarana",
          1,
          3,
          {1, 12, 2050},
          S},
         {"Sumo laranja", 1.25, 8, {1, 12, 2050}, S},
         {"Luso", 0.50, 10, {1, 12, 2025}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, S}},
        {{"Guarana",
          1,
          3,
          {1, 12, 2050},
          S},
         {"Sumo laranja", 1.25, 8, {1, 12, 2050}, S},
         {"Luso", 0.50, 10, {1, 12, 2025}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, S}},
        {{"Guarana",
          1,
          3,
          {1, 12, 2050},
          R},
         {"Sumo laranja", 1.25, 8, {1, 12, 2050}, S},
         {"Luso", 0.50, 10, {1, 12, 2025}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, S}},

        {{"Guarana", 1, 3, {1, 12, 2050}, R},
         {"Sumo laranja", 1.25, 8, {1, 12, 2050}, S},
         {"Luso", 0.50, 10, {1, 12, 2025}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, S}},

        {{"Guarana", 1, 3, {1, 12, 2050}, R},
         {"Sumo laranja", 1.25, 8, {1, 12, 2050}, S},
         {"Luso", 0.50, 10, {1, 12, 2025}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, S}},

        {{"Guarana", 1, 3, {1, 12, 2050}, S},
         {"Sumo laranja", 1.25, 8, {1, 12, 2050}, S},
         {"Luso", 0.50, 10, {1, 12, 2025}, A},
         {"Super Book", 1.50, 10, {1, 12, 2060}, C},
         {"Leite", 1.25, 8, {1, 12, 2026}, L},
         {"Coca cola", 1.00, 5, {1, 12, 2027}, R},
         {"agua", 0.50, 10, {1, 12, 2025}, A},
         {"Sumo laranja", 1.25, 9, {1, 12, 2026}, S}},
    };

    // Display the menu
    initialMenu(vendingMachine, machineAmountPointer);

    return 0;
}
