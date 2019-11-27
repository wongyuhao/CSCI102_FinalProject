#pragma once
#include <iostream>
#include <vector>	
#include <string>
using namespace std;

//recipe class
class Recipe {
private:
	//object variables
	string name;
	vector<string> ingredients;
	vector<string> steps;
	int calories;

public:
	//constructor
	Recipe(string, int, vector<string>, vector<string>);

	//member functions

	//set functions
	void setName(string);
	void setCalories(int);
	void setIngredients(vector<string>);
	void setSteps(vector<string>);

	//get functions
	string getName();
	int getCalories();
	int getNumIngredients();
	int getNumSteps();
	vector<string>& getIngredients();
	vector<string>& getSteps();

	//print functions
	void printRecipe();

};

//validation function
void validate(int&, int, int);

//menu display functions
void viewRecipes();

//add recipe function
void addRecipe();

//save and load functions
void save();
void load();

//add recipe helper functions
bool cmpRecipeByName(Recipe, Recipe);
bool cmpRecipeByCalories(Recipe, Recipe);
bool cmpRecipeBySteps(Recipe, Recipe);
bool cmpRecipeByIngredients(Recipe, Recipe);

void viewRecipesByTime(vector<Recipe>&);
void viewRecipesByName(vector<Recipe>&);
void viewRecipesByCalories(vector<Recipe>&);
void viewRecipesBySteps(vector<Recipe>&);
void viewRecipesByIngredients(vector<Recipe>&);
