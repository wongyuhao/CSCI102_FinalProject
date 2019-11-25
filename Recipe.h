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
	vector <string> ingredients;
	vector <string> steps;
	int calories;

public:
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

	//print functions
	void printRecipe();

};

//validation function
void validate(int&, int, int);

//menu display functions
void viewRecipes();

//add recipe function
void addRecipe();

void save(int);
