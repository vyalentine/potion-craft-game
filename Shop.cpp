/*Title: Shop.cpp
Author: Vy Nguyen
Email: vnguye14@umbc.edu
Section: Lab - 12 David Opie
Date: 3/6/23
Description: This is file builds all of the functions associated with the 
Shop.h file
*/

#include "Shop.h"
using namespace std;

// Name: Shop() - Default Constructor
// Desc: Used to build a new Player Shop
// Preconditions - Requires default values (Name = Test, numIngredients = 0, Rank = F
// Postconditions - Creates a new Player Shop
Shop::Shop()
{
    m_shopName = "Test";
    m_numIngredients = 0;
    m_shopRank = 'F';
}

// Name: Shop(name) - Overloaded constructor
// Desc - Used to build a new Player Shop (m_numIngredients = 0, m_shopRank = F)
// Preconditions - Requires name
// Postconditions - Creates a new Player Shop
Shop::Shop(string name)
{
    SetName(name);
    m_numIngredients = 0; 
    m_shopRank = 'F'; 
}

// Name: GetName()
// Desc - Getter for the Player Shop's name
// Preconditions - Player Shop exists
// Postconditions - Returns the name of the Player Shop
string Shop::GetName()
{
    return m_shopName;
}


// Name: SetName(string)
// Desc - Allows the user to change the name of the Player Shop
// Preconditions - Player Shop exists
// Postconditions - Sets name of Player Shop
void Shop::SetName(string name)
{
    m_shopName = name; 
}

// Name: CheckIngredient(Ingredient)
// Desc - Checks to see if the Shop has a ingredient
// Preconditions - Shop already has ingredients
// Postconditions - Returns index of ingredient if the Shop has it, else -1
int Shop::CheckIngredient(Ingredient nameOfIngredient)
{
    // traverse through the array of m_myIngredients based on the
    // PROJ2_SIZE until the ingredient is found, otherwise, if the 
    // ingredient is not there, -1 is returned 
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        if (nameOfIngredient.m_name == m_myIngredients[i].m_name)
        {
            return i; 
        }
    }
    return -1; 
}

// Name: AddIngredient(string)
// Desc - Inserts a ingredient into the Shop's list of ingredients.
//        Increments m_numIngredients
// Preconditions - Shop exists
// Postconditions - Add a ingredient to the Shop's m_myIngredients with a quantity of 0
void Shop::AddIngredient(Ingredient nameOfIngredient)
{
    // if the ingredient is not already in the list: 
    if (CheckIngredient(nameOfIngredient) == -1)
    {
        // allocate the inserted ingredient into the last/"empty" index of the 
        // m_myIngredients array, and then increment m_numIngredients to increase
        // the size of the array
        m_myIngredients[m_numIngredients] = nameOfIngredient;
        m_numIngredients++;
    }

    //if the ingredient is already in the list: 
    else
    {
        IncrementQuantity(nameOfIngredient);
    }
}

// Name: IncrementQuantity(Ingredient)
// Desc - Increases the quantity for an ingredient the Shop knows
// Preconditions - Shop exists
// Postconditions - Increases quantity of ingredient for the Shop
void Shop::IncrementQuantity(Ingredient nameOfIngredient)
{
    m_myIngredients[CheckIngredient(nameOfIngredient)].m_quantity++;
}

// Name: DecrementQuantity(Ingredient)
// Desc - Reduces quantity from the Shop's inventory with true, if no quantity false
// Preconditions - A Shop exists
// Postconditions - Reduces quantity of ingredient for the Shop
bool Shop::DecrementQuantity(Ingredient nameOfIngredient)
{
    // if the quantity of an ingredient is less than 0, return false
    if (m_myIngredients[CheckIngredient(nameOfIngredient)].m_quantity <= 0)
    {
        return false; 
    }
    // if the quantity of an ingredient is less than 0, return true
    else
    {
        m_myIngredients[CheckIngredient(nameOfIngredient)].m_quantity--; 
        return true; 
    }
}

// Name: CheckQuantity(Ingredient)
// Desc - Checks to see if quantity of two merge ingredients are available
// Preconditions - Shop exists with ingredients
// Postconditions - Returns true if both are available (including two of same ingredient)
bool Shop::CheckQuantity(Ingredient nameOfIngredient1, Ingredient nameOfIngredient2)
{
    if ((CheckIngredient(nameOfIngredient1) != -1) && (CheckIngredient(nameOfIngredient2) != -1))
    {
        // condition that ingredient 1 and ingredient 2 are the same 
        if (nameOfIngredient1.m_name == nameOfIngredient2.m_name)
        {
            // which means that there needs to be at least 2 of the same ingredient for the 
            // requested combination to work 
            if ((nameOfIngredient1.m_quantity >= 2) && (nameOfIngredient2.m_quantity >= 2))
            {
                return true; 
            }
        // if the ingredients are different, program will check that there is at least
        // one of either ingredient for the requested combination 
        }
        else if ((nameOfIngredient1.m_quantity > 0) && (nameOfIngredient2.m_quantity > 0))
        {
            return true; 
        }
    }
    return false; 
}

// Name: GetIngredient(int)
// Desc - Checks to see if the Shop has any ingredients
// Preconditions - The Shop already has ingredients
// Postconditions - Returns ingredient at specific index
Ingredient Shop::GetIngredient(int ingredientIndex)
{
    return m_myIngredients[ingredientIndex]; 
}

// Name: CalcRank()
// Desc - Divides the total available ingredients, by the IngredientCount()
// Updates the rank based on percentages
//      0-29 = F, 30-49 = D, 50-69 = C, 70-89 = B, 90-99 = A, 100 = S
// Preconditions - Shop exists and has a rank
// Postconditions - m_shopRank will be updated
void Shop::CalcRank()
{
    // calculate rankPercent (as a double) found by dividing 
    // Ingredient count (as a double) by PROJ2_SIZE then multiplying by 100
    // and sorting into the following rank categories: 
    double rankPercent = (((double(IngredientCount()))/PROJ2_SIZE) * 100);
    
    if ((rankPercent >= 0) && (rankPercent <= 29)) { m_shopRank = 'F'; }

    else if ((rankPercent >= 30) && (rankPercent <= 49)) { m_shopRank = 'D'; }

    else if ((rankPercent >= 50) && (rankPercent <= 69)) { m_shopRank = 'C'; }

    else if ((rankPercent >= 70) && (rankPercent <= 89)) { m_shopRank = 'B'; }
    
    else if ((rankPercent >= 90) && (rankPercent <= 99)) { m_shopRank = 'A';}

    else { m_shopRank = 'S'; }
}

// Name: GetRank()
// Desc - Returns the current shop's rank
// Preconditions - The shop exists
// Postconditions - Returns the character indicating the rank of the shop
char Shop::GetRank()
{
    CalcRank(); 
    return m_shopRank; 
}

// Name: IngredientCount()
// Desc - Loops through m_myIngredients to see how many ingredients have a quantity > 0
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Returns the count of ingredients with a quantity > 0
int Shop::IngredientCount()
{
    // counts the number of ingredients that have a quantity > 0 by 
    // looping througn m_myIngredients and incrementing 
    //ingredientCounter variable
    int ingredientCounter = 0; 
    for (int i = 0; i < m_numIngredients;  i ++)
    {
        if (m_myIngredients[i].m_quantity > 0)
        {
            ingredientCounter ++; 
        }
    }
    return ingredientCounter; 
}

// Name: ShopScore()
// Desc - Displays information about the shop: name, ingredients found, total available,
//        percentage found, and rank
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Displays name, ingredient count, total ingredients, percentage, and rank
void Shop::ShopScore()
{   
    // prints data associated with the Shop's Score
    cout << "***The Potion Shop***" << endl; 
    cout << "Owned by: " << m_shopName << endl; 
    cout << "There are " << PROJ2_SIZE << " available products." << endl; 
    cout << "This shop has " << IngredientCount() << " products in stock." << endl; 
    cout << "Which is " << (((double(IngredientCount()))/PROJ2_SIZE) * 100) << "%" << endl; 
    cout << "Shop Rank: " << GetRank() << endl; 
    cout << "*********************" << endl; 
}
