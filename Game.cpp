/*Title: Game.cpp
Author: Vy Nguyen
Email: vnguye14@umbc.edu
Section: Lab - 12 David Opie
Date: 3/6/23
Description: This is file builds all of the functions associated with the 
Game.h file
*/

#include "Game.h" //Include for the ingredient struct
using namespace std;

// Name - Game() Default Constructor
// Desc - Does nothing explicitly
// Preconditions - None
// Postconditions - None
Game::Game() //Default Constructor
{

} 

// Name - LoadIngredients
// Desc - Loads each ingredient into m_ingredients from file.
//        Ingredient names can have spaces (check proj doc for delimiter help)
// Preconditions - Requires file with valid ingredient data
// Postconditions - m_ingredient is populated with ingredient structs
void Game::LoadIngredients()
{
    string nameOfIngredient = ""; 
    string typeOfIngredient = "";
    string ingredient1 = "";
    string ingredient2 = ""; 

    ifstream ingredientFileHandler(PROJ2_DATA);

    // loop through the PRO2 size to get the name, type, and ingredients of each item 
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        getline(ingredientFileHandler, nameOfIngredient, ',');
        getline(ingredientFileHandler, typeOfIngredient, ',');
        getline(ingredientFileHandler, ingredient1, ',');
        // getline by default reads \n, so a 3rd param is not needed
        getline(ingredientFileHandler, ingredient2);
        // then assign each index of m_ingredients to the member variables within the Ingredient class
        m_ingredients[i] = Ingredient(nameOfIngredient, typeOfIngredient, ingredient1, ingredient2, 0);
        // then load the elements of m_ingredients through AddIngredients() to add to shop's list
        m_myShop.AddIngredient(m_ingredients[i]);
    }
    ingredientFileHandler.close();
}


// Name - StartGame()
// Desc - Calls GameTitle then loads the file by calling LoadIngredients
//        Manages the game itself continually calling the main menu until the main menu
//        returns 5 (quit)
// Preconditions - Player is placed in game
// Postconditions - Continually checks to see if player has entered 5
void Game::StartGame()
{
    GameTitle(); 
    cout << PROJ2_SIZE << " ingredients loaded. " << endl; 
    LoadIngredients();

    // get and set name 
    string nameOfShop; 
    cout << "What is the name of your Shop? " << endl; 
    getline(cin, nameOfShop);
    m_myShop.SetName(nameOfShop); 

    // until the userChoice is 5, the MainMenue will continue running
    while (MainMenu() != 5) 
    {
        MainMenu(); 
    }

}

// Name: MainMenu()
// Desc - Displays and manages menu. Also checks win condition (Shop reaches S rank).
// Preconditions - Player has a Shop
// Postconditions - Returns number including exit
int Game::MainMenu()
{
    // do while that manages the main menue and its options 
    int userChoice; 
    do
    {
        cout << "What would you like to do in " << m_myShop.GetName() << "'s shop? " << endl
                << "1. Display your Shop's Ingredients " << endl
                << "2. Search for Natural Ingredients " << endl
                << "3. Attempt to Merge Ingredients " << endl
                << "4. See Score " << endl
                << "5. Quit " << endl; 
        cin >> userChoice; 

        // checks to see if between 1 and 3
        (userChoice < 1 || userChoice > 5)?cout << "Please choose again (1-5)." << endl:cout << ""; 

        if (userChoice == 1) { DisplayIngredients(); }
            
        else if (userChoice == 2) { SearchIngredients(); }   

        else if (userChoice == 3) { CombineIngredients(); }

        else if (userChoice == 4) { m_myShop.ShopScore(); }   

        // if the shop rank is 'S', userchoice becomes 5 to end loop
        else if (m_myShop.GetRank() == 'S') {userChoice = 5;}

    }while (userChoice != 5); 

    cout << "Thanks for playing UMBC Potion Craft! " << endl; 
    return 5; 
    
}


// Name: DisplayMyIngredients()
// Desc - Displays the Shop's ingredients (Uses GetIngredient)
// Preconditions - Player's Shop has ingredients
// Postconditions - Displays a numbered list of ingredients
void Game::DisplayIngredients()
{
    // loops through the size of PROJ2 to get the name and quantity of each ingredient 
    for(int i = 0; i < PROJ2_SIZE; i++)
    {
        cout << i + 1 << ". " << m_myShop.GetIngredient(i).m_name << " " << m_myShop.GetIngredient(i).m_quantity << endl; 
    }
}


// Name: SearchIngredients()
// Desc - Attempts to search for natural ingredients (must be type "natural")
// Preconditions - Natural ingredients loaded
// Postconditions - Increases quantity in Shop's possession of ingredients
void Game::SearchIngredients()
{
    bool noIngredientFound = true;
    // while loop that runs on above flag ^ 
    while (noIngredientFound)
    {
        // search through the list of m_ingredients based on an 
        // randomized int 0-size of PROJ2 
        int randomNum = rand() % PROJ2_SIZE; 
        // then, if the randomized int results in an ingredient 
        // that s natural at that index, add the ingredient 
        // with cout statement, and stop loop 
        if (m_ingredients[randomNum].m_type == "natural")
        {
            m_myShop.AddIngredient(m_ingredients[randomNum]);
            cout << m_ingredients[randomNum].m_name << " Found!" << endl; 
            noIngredientFound = false; 
        }
    }
}

// Name: RequestIngredient()
// Desc - Requests ingredient to use to merge
// Preconditions - Shop has ingredients to try and merge
// Postconditions - Returns integer of item selected by user
void Game::RequestIngredient(int &choice)
{
    bool runRequestIngredient = true; 
    while (runRequestIngredient)
    // while loop that runs until the user enters two valid indices 
    // to be combined 
    {
        cout << "Which ingredients would you like to merge? " << endl
            << "(To list known ingredients enter -1) " << endl; 
        cin >> choice;

        // user input validation (choice got out of bounds)
        while (((choice < 1) && (choice != -1)) || choice > PROJ2_SIZE)
        {
            cout << "Which ingredients would you like to merge? " << endl
                << "(To list known ingredients enter -1) " << endl; 
            cin >> choice; 
        }

        if (choice == -1)
        {
            DisplayIngredients(); 
        }

        else
        {
            choice --; 
            runRequestIngredient = false;
        }

    }
}

// Name: SearchRecipes()
// Desc - Searches recipes for two strings (name of item)
// Preconditions - m_ingredients is populated
// Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string nameOfIngredient1, string nameOfIngredient2)
{
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        // condition considers only the potion, reagent, and legendary options
        if (m_ingredients[i].m_type != "natural")
        {
            // if the two requested ingredients match a combination of a recipe, in any order, then return the index
            // of that recipe 
            if (((m_ingredients[i].m_ingredient1 == nameOfIngredient1) && (m_ingredients[i].m_ingredient2 == nameOfIngredient2)) 
            || ((m_ingredients[i].m_ingredient1 == nameOfIngredient2) && (m_ingredients[i].m_ingredient2 == nameOfIngredient1))) 
            {
                return i; 
            }
        }
    }
    // otherwise, return -1, indicating that the recipe does not exist 
    return -1; 
}


// Name: CombineIngredients()
// Desc - Attempts to combine known ingredients. If combined, quantity of ingredient decreased
// Preconditions - Shop is populated with ingredients
// Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineIngredients()
{
    // assign variables to the integers returned from RequestIngredient 
    int ingredientRequestInt1; 
    int ingredientRequestInt2; 
    RequestIngredient(ingredientRequestInt1);
    RequestIngredient(ingredientRequestInt2);

    // then pass the integers to return the ingredient at a specific index 
    // within m_myIngredients[]
    Ingredient ingredientRequest1 = m_myShop.GetIngredient(ingredientRequestInt1);
    Ingredient ingredientRequest2 = m_myShop.GetIngredient(ingredientRequestInt2);

    // then turn the above ^ into strings that will be passed as strings into SearchRecipes 
    string ingredientRequestString1 = ingredientRequest1.m_name;
    string ingredientRequestString2 = ingredientRequest2.m_name;

    int recipeIndex = SearchRecipes(ingredientRequestString1, ingredientRequestString2);
    bool quantityChecker = m_myShop.CheckQuantity(ingredientRequest1, ingredientRequest2);
    
    // condition that recipe does not exist 
    if (recipeIndex == -1)
    {
        cout << "Nothing happened when you tried to combine " << ingredientRequestString1 << " and " << ingredientRequestString2 << endl; 
    }
    
    // condition that the player does not have enough quantity to combined into an item 
    else if (quantityChecker == false)
    {
        cout << "You do not have enough " << ingredientRequestString1 << " or " << ingredientRequestString2 << " to attempt that merge. " << endl; 
    }

    // if the recipe exists and there is enough quantity, add/increment the item to the shop
    // and decrease quantity of the ingredients 
    else
    {
        // get the crafted recipe by passing recipeIndex into GetIngredient 
        Ingredient craftedIngredient = m_myShop.GetIngredient(recipeIndex);
        // then access its name (string) to be used in the cout statements
        string craftedIngredientString = craftedIngredient.m_name; 
        cout << ingredientRequestString1 << " combined with " << ingredientRequestString2 << " to make " << craftedIngredientString << "!" << endl;
        cout << "You have made " << craftedIngredientString << " for your shop." << endl; 
        m_myShop.AddIngredient(craftedIngredient); 
        m_myShop.DecrementQuantity(ingredientRequest1);
        m_myShop.DecrementQuantity(ingredientRequest2);
    }

}


