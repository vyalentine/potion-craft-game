//Title: Ingredient.h
//Author: Jeremy Dixon, edited by Gabe Doersam
//Date: 2/10/23
//Description: This is part of the PotionCraft project in CMSC 202 @ UMBC

#ifndef INGREDIENT_H //Include/Header Guard
#define INGREDIENT_H //Include/Header Guard

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

// Name: Ingredient struct
// Desc - Used to store data about ingredients
struct Ingredient{
public: //Public by default
  Ingredient(){} //Default constructor
  Ingredient(string name, string type, string ingredient1, string ingredient2,
	     int quantity){
    m_name = name; //Name of this ingredient
    m_type = type; //Type of the ingredient (natural, potion, reagent, or legendary)
    m_ingredient1 = ingredient1; //Name of first required ingredient to create
    m_ingredient2 = ingredient2; //Name of second required ingredient to create
    m_quantity = quantity; //Quantity of the ingredient
  }
  string m_name; //Name of the ingredient
  string m_type; //Type of the ingredient (natural, potion, reagent, legendary)
  string m_ingredient1; //Required ingredient 1 to create
  string m_ingredient2; //Required ingredient 2 to create
  int m_quantity; //Quantity of ingredient owned
};

#endif
