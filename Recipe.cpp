#include "Recipe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>	
#include <algorithm>
#include <string>
#include <cctype>

//a vector of recipes
vector<Recipe> recipeVector;

Recipe::Recipe(string n, int c, vector<string> in, vector<string> st) {
	setName(n);
	setCalories(c);
	setIngredients(in);
	setSteps(st);
}

//setter function implementation
void Recipe::setName(string n) {
	name = n;
}
void Recipe::setCalories(int c) {
	calories = c;
}
void Recipe::setIngredients(vector<string> in) {
	ingredients = in;
}
void Recipe::setSteps(vector<string> st) {
	steps = st;
}

//getter function implementation
string Recipe::getName() {
	return name;
}
int Recipe::getCalories() {
	return calories;
}
int Recipe::getNumIngredients() {
	return ingredients.size();
}
int Recipe::getNumSteps() {
	return steps.size();
}
vector<string>& Recipe::getIngredients() {
	return ingredients;
}
vector<string>& Recipe::getSteps() {
	return steps;
}

//print function
void Recipe::printRecipe() {
	cout << "--------------------" << endl;
	cout << "Recipe Name: " << name << endl;

	cout << "Calories (kcal): " << calories << endl;

	cout << "\nIngredients list:\n";
	for (int i = 0; i < ingredients.size(); i++) {
		cout << (i+1) << ". " << ingredients[i] << endl;
	}

	cout << "\nSteps list:\n";
	for (int i = 0; i < steps.size(); i++) {
		cout << (i+1) << ". " << steps[i] << endl;
	}
	
	cout << "--------------------" << endl;
}

//view recipe menu function
void viewRecipes() {
	//if there is no recipe, prompt the user to return to main menu
	if (recipeVector.empty()) {
		cout << "No recipes found.\n\n";
		cout << "Select an option:\n"
			<< "[0] Main menu\n\n";
		
		cout << "Please enter the number beside your selection:\n";
		
		int selection;
		cin >> selection;
		validate(selection, 0, 0);
		
		cout << '\n';
		return;
	}
	
	//print options to sort the recipes
	cout << "Sort recipes by:\n"
		<< "[1] Time entered\n"
		<< "[2] Name\n"
		<< "[3] Calories\n"
		<< "[4] Number of ingredients\n"
		<< "[5] Number of steps\n"
		<< "[0] Back\n\n";

	cout << "Please enter the number beside your selection:\n";
	
	int selection;
	cin >> selection;
	cout << '\n';

	validate(selection, 0, 5);
	
	//create a copy of the original vector,  sort it according to the user's selection and print it
	vector<Recipe> recipeVectorSorted = recipeVector;

	switch (selection)
	{
	case 0:
		cout << '\n';
		return;
		break;
	case 1:
		viewRecipesByTime(recipeVectorSorted);
		break;
	case 2:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByName);
		viewRecipesByName(recipeVectorSorted);
		break;
	case 3:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByCalories);
		viewRecipesByCalories(recipeVectorSorted);
		break;
	case 4:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeByIngredients);
		viewRecipesByIngredients(recipeVectorSorted);
		break;
	case 5:
		sort(recipeVectorSorted.begin(), recipeVectorSorted.end(), cmpRecipeBySteps);
		viewRecipesBySteps(recipeVectorSorted);
		break;
	default:
		cerr << "Unexpected error in recipe_definitions.cpp: viewRecipes(): printing sorted recipe list\n";
		return;
	}
	
	//prompt the user to view a recipe in detail or return to main menu
	cout << "Select an option:\n"
		<< "[1-" << recipeVectorSorted.size() << "] View selected recipe\n"
		<< "[0] Main menu\n\n";
		
	cout << "Please enter the number beside your selection:\n";

	cin >> selection;
	validate(selection, 0, recipeVectorSorted.size());

	if (selection == 0) {
		cout << '\n';
		return;
	}
	
	//print the selected recipe
	recipeVectorSorted[selection - 1].printRecipe();

	//prompt the user to return to main menu (continue)
	cout << "Select an option:\n"
		<< "[0] Continue\n\n";
		
	cout << "Please enter the number beside your selection:\n";
	
	cin >> selection;
	validate(selection, 0, 0);
}

// helper - compare functions
bool cmpRecipeByName(Recipe a, Recipe b) {
	return a.getName() < b.getName();
}
bool cmpRecipeByCalories(Recipe a, Recipe b) {
	if (a.getCalories() != b.getCalories()) return a.getCalories() < b.getCalories();
	return a.getName() < b.getName();
}
bool cmpRecipeByIngredients(Recipe a, Recipe b) {
	if (a.getNumIngredients() != b.getNumIngredients()) return a.getNumIngredients() < b.getNumIngredients();
	return a.getName() < b.getName();
}
bool cmpRecipeBySteps(Recipe a, Recipe b) {
	if (a.getNumSteps() != b.getNumSteps()) return a.getNumSteps() < b.getNumSteps();
	return a.getName() < b.getName();
}

//helper - view_sort functions
void viewRecipesByTime(vector<Recipe>& temp) {
	cout << "All recipes sorted by time entered:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesByName(vector<Recipe>& temp) {
	cout << "All recipes sorted by name:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesByCalories(vector<Recipe>& temp) {
	cout << "All recipes sorted by calories:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". " << "[" << temp[i].getCalories() << " kcal] " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesByIngredients(vector<Recipe>& temp) {
	cout << "All recipes sorted by number of ingredients:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". [" << temp[i].getNumIngredients() << " ingredient(s)] " << temp[i].getName() << '\n';
	}
	cout << '\n';
}
void viewRecipesBySteps(vector<Recipe>& temp) {
	cout << "All recipes sorted by number of steps:\n";
	for (int i = 0; i < temp.size(); i++) {
		cout << setw(3) << i + 1 << ". [" << temp[i].getNumSteps() << " step(s)] " << temp[i].getName() << '\n';
	}
	cout << '\n';
}

//validate that selection is between l and r, inclusive
void validate(int& selection, int l, int r) {
	while (selection < l || selection > r) {
		cout << "\nInvalid response.\n"
			<< "Please enter the number beside your selection:\n";
		cin >> selection;
		cout << '\n';
	}
}

//add recipe function
void addRecipe() {
	while (true) {
		string temp_name;
		vector<string> temp_ingredients;
		string temp_ingredient;
		vector<string> temp_steps;
		string temp_step;
		int temp_calories;

		//enter details of the recipe
		cout << "Enter name: ";
		cin.ignore();
		getline(cin, temp_name);

		cout << "Enter calories: ";
		cin >> temp_calories;

		cout << "Enter all ingredients in this recipe. Enter '0' to stop.\n";
		cin.ignore();
		while (true) {
			cout << temp_ingredients.size() + 1 << ". ";
			getline(cin, temp_ingredient);
			if (temp_ingredient == "0") {
				break;
			}
			else {
				temp_ingredients.push_back(temp_ingredient);
			}
		}

		cout << "Enter all steps for this recipe. Enter '0' to stop.\n";
		while (true) {
			cout << temp_steps.size() + 1 << ". ";
			getline(cin, temp_step);
			if (temp_step == "0") {
				break;
			}
			else {
				temp_steps.push_back(temp_step);
			}
		}

		//add the recipe to recipeVector
		Recipe temp_recipe(temp_name, temp_calories, temp_ingredients, temp_steps);
		recipeVector.push_back(temp_recipe);

		cout << "Recipe Created!\n";
		cout << "Add another recipe? (Y/N)\n";
		char poll;
		cin >> poll;

		//prompt the user to either add another recipe or stop
		while (tolower(poll) != 'y' && tolower(poll) != 'n') {
			cout << "Invalid response.\n"
				<< "Add another recipe? (Y/N)\n";
			cin >> poll;
		}

		if (tolower(poll) == 'n') {
			break;
		}
	}
}

void save(){
	int saveCount = 0;	//number of save files
	
	//overview file streams: the overview file stores the number of save files
	ifstream vin("data/overview");
	
	//if overview file exists, read the number of save files
	//otherwise, the number of save files is 0 by default
	if(vin){
		vin >> saveCount;
	}
	
	cout << "Select an option:\n";
	
	//print the option to overwrite a save file if at least one save file exists
	if(saveCount){
		cout << "[1-" << saveCount << "] Overwrite selected save file\n";
	}
	cout << "[" << saveCount+1 <<"] Create new save file\n"
		<< "[0] Main Menu\n\n";
	
	cout << "Please select the number beside your selection:\n";
	
	int selection;
	cin >> selection;
	validate(selection, 0, saveCount+1);
	
	//return to main menu
	if(selection == 0){
		cout << '\n';
		return;
	}
	
	//if a new save file is created, update overview file
	if(selection == saveCount+1){
		ofstream vout("data/overview", ios::trunc);
		saveCount++;
		vout << saveCount << '\n';
		vout.close();
	}
	
	//overwrite the selected save file
	ofstream fout("data/save" + to_string(selection), ios::trunc);
	
	fout << recipeVector.size() << '\n';
	
	for(Recipe r: recipeVector){
		fout << r.getName() << '\n';
		fout << r.getCalories() << '\n';
		fout << r.getNumIngredients() << '\n';
		for(string i: r.getIngredients()){
			fout << i << '\n';
		}
		fout << r.getNumSteps() << '\n';
		for(string s: r.getSteps()){
			fout << s << '\n';
		}
	}	
	
	//close file streams
	vin.close();
	fout.close();
	
	cout << "\nData saved.\n\n";
}

void load(){
	int saveCount = 0;	//number of save files
	
	//read number of save files
	//if the file does not exist, the number of save files is 0 - no change required
	ifstream vin("data/overview");
	if(vin){
		vin >> saveCount;
	}
	
	cout << "Select an option:\n";
	
	//print the option to load save files if at least one save file exists
	if(saveCount){
		cout << "[1-" << saveCount << "] Load selected save file\n";
	}
	cout << "[0] Main Menu\n\n";
	
	cout << "Please enter the number beside your selection:\n";
	
	int index;
	cin >> index;
	validate(index, 0, saveCount);
	
	if(index == 0){
		cout << '\n';
		return;
	}
	
	//open the selected save file
	ifstream fin("data/save" + to_string(index));
	
	//ensures that file is found
	if(!fin){
		cout << "\nError: Save data not found.\n\n";
		return;
	}
	
	//clear recipeVector
	recipeVector = {};
	
	int _size;	//number of recipes
	fin >> _size;
	fin.ignore();
	
	//retrieve save file data
	for(int i=0; i<_size; i++){
		string temp_name;
		int temp_calories;
		vector<string> temp_ingredients;
		vector<string> temp_steps;
		
		getline(fin, temp_name);
		
		fin >> temp_calories;
		
		int ingredientCount;
		fin >> ingredientCount;
		fin.ignore();
		for(int j=0; j<ingredientCount; j++){
			string temp;
			getline(fin, temp);
			temp_ingredients.push_back(temp);
		}
		
		int stepsCount;
		fin >> stepsCount;
		fin.ignore();
		for(int j=0; j<stepsCount; j++){
			string temp;
			getline(fin, temp);
			temp_steps.push_back(temp);
		}
		
		recipeVector.push_back(Recipe(temp_name, temp_calories, temp_ingredients, temp_steps));
	}
	
	cout << "\nSave file loaded.\n\n";
	
	//close file streams
	vin.close();
	fin.close();
}
