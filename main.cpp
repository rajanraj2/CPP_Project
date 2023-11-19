#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct User {
    string username;
    string password;
};

struct UserNode {
    User user;
    UserNode* left;
    UserNode* right;
};

vector<User> loadUserData(const string& filename) {
    vector<User> users;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return users;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos == string::npos) {
            cerr << "Error: Invalid data format in the CSV file." << endl;
            continue;
        }

        User user;
        user.username = line.substr(0, pos);
        user.password = line.substr(pos + 1);
        users.push_back(user);
    }

    file.close();
    return users;
}

void saveUserData(const string& filename, const vector<User>& users) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return;
    }

    for (const User& user : users) {
        file << user.username << ',' << user.password << '\n';
    }

    file.close();
}

User* loginUser(const vector<User>& users) {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return const_cast<User*>(&user);
        }
    }

    return nullptr;
}

void registerUser(vector<User>& users, const string& filename) {
    User newUser;
    cout << "Enter a new username: ";
    cin >> newUser.username;
    cout << "Enter a password: ";
    cin >> newUser.password;
    users.push_back(newUser);
    saveUserData(filename, users);
    cout << "Registration successful." << endl;
}


// Define a structure for a product
struct Product {
    string name;
    string company;
    double price;
    // Add other product attributes here
};

// Define a binary tree node for product categories
struct CategoryNode {
    string category;
    vector<Product> products;
    CategoryNode* left;
    CategoryNode* right;
};

// Function to insert a product into the category tree
CategoryNode* insertProduct(CategoryNode* root, Product product, string category) {
    if (root == nullptr) {
        return new CategoryNode{category, {product}, nullptr, nullptr};
    }

    if (category < root->category) {
        root->left = insertProduct(root->left, product, category);
    } else if (category > root->category) {
        root->right = insertProduct(root->right, product, category);
    } else {
        root->products.push_back(product);
    }

    return root;
}

// Function to display categories in a sorted order
void displayCategories(CategoryNode* root) {
    if (root) {
        displayCategories(root->left);
        cout << "Category: " << root->category << endl;
        displayCategories(root->right);
    }
}

// Function to add a new category
CategoryNode* addCategory(CategoryNode* root, string newCategory) {
    if (root == nullptr) {
        return new CategoryNode{newCategory, {}, nullptr, nullptr};
    }

    if (newCategory < root->category) {
        root->left = addCategory(root->left, newCategory);
    } else if (newCategory > root->category) {
        root->right = addCategory(root->right, newCategory);
    }

    return root;
}



// Function to delete a category
CategoryNode* deleteCategory(CategoryNode* root, string targetCategory) {
    if (root == nullptr) {
        return nullptr;
    }

    if (targetCategory < root->category) {
        root->left = deleteCategory(root->left, targetCategory);
    } else if (targetCategory > root->category) {
        root->right = deleteCategory(root->right, targetCategory);
    } else {
        // Category found, delete it
        delete root;
        root = nullptr;
    }

    return root;
}


// In-order traversal of the category tree to display categories
void displayCategories1(CategoryNode* root, map<int, string>& categoryNumbers, int& categoryNumber) {
    if (root) {
        displayCategories1(root->left, categoryNumbers, categoryNumber);
        categoryNumbers[categoryNumber] = root->category;
        cout << categoryNumber << ". " << root->category << endl;
        categoryNumber++;
        displayCategories1(root->right, categoryNumbers, categoryNumber);
    }
}


// Display products within a selected category
void displayProductsInCategory(CategoryNode* root, const string& selectedCategory) {
    if (root) {
        if (selectedCategory < root->category) {
            displayProductsInCategory(root->left, selectedCategory);
        } else if (selectedCategory > root->category) {
            displayProductsInCategory(root->right, selectedCategory);
        } else {
            cout << "\n=== Products in Category: " << root->category << " ===" << endl;
            for (const Product& product : root->products) {
                cout << "Product: " << product.name << " (Company: " << product.company << ", Price: Rs." << product.price << ")" << endl;
            }
        }
    }
}



int main() {
    vector<User> buyerUsers = loadUserData("buyers.csv");
    vector<User> sellerUsers = loadUserData("sellers.csv");

    cout << "\n\n----------------------------------------\n";
    

    cout << "\033[1;31;43m       Welcome to ELECTROVERSE !        \033[0m" << endl;


    while (true) {
        int role;
        cout << "----------------------------------------\n\n";
        cout << "Choose a role:" << endl;
        cout << "1. Seller" << endl;
        cout << "2. Buyer" << endl;
        cout << "3. Quit" << endl;
        cin >> role;

        if (role == 1) { // Seller
    int option;
    cout << "----------------------------------------\n\n";
    cout << "\033[4;34mSeller Interface\033[0m\n" << endl;
    cout << "\033[32mChoose an option:\033[0m" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Go back" << endl;
    cin >> option;

    if (option == 1) { // Seller Login
        User* seller = loginUser(sellerUsers);
        if (seller) {
            cout << "Seller logged in." << endl;
            cout << "----------------------------------------\n\n";
            // seller-specific actions 
            CategoryNode* categoryTree = nullptr;

            // some initial products inserted into the category tree
            categoryTree = insertProduct(categoryTree, Product{"Laptop 1", "Company A", 999.99}, "Electronics/Laptops");
            categoryTree = insertProduct(categoryTree, Product{"Smartphone 1", "Company B", 699.99}, "Electronics/Smartphones");
            categoryTree = insertProduct(categoryTree, Product{"TV 1", "Company C", 499.99}, "Electronics/TV");

            int choice;
            string newCategory;
            string categoryToDelete; // Renamed the variable to avoid conflicts

            while (true) {
                cout << "\033[32mChoose an option:\033[0m" << endl;
                cout << "1. Display Categories" << endl;
                cout << "2. Add a New Category" << endl;
                cout << "3. Delete a Category" << endl;
                cout << "4. Quit" << endl;
                cin >> choice;

                if (choice == 1) {
                    cout << "----------------------------------------\n\n";
                    cout << "Categories:" << endl;
                    displayCategories(categoryTree);
                    cout << "----------------------------------------\n\n";

                } else if (choice == 2) {
                    cout << "Enter the name of the new category: ";
                    cin.ignore();
                    getline(cin, newCategory);
                    categoryTree = addCategory(categoryTree, newCategory);
                    cout << "----------------------------------------\n\n";

                } else if (choice == 3) {
                    cout << "Enter the name of the category to delete: ";
                    cin.ignore();
                    getline(cin, categoryToDelete); // Renamed variable
                    categoryTree = deleteCategory(categoryTree, categoryToDelete); // Renamed variable
                    cout << "----------------------------------------\n\n";

                } else if (choice == 4) {
                    break;
                } else {
                    cout << "\033[1;31mInvalid choice. Try again.\033[0m" << endl;
                    cout << "----------------------------------------\n\n";

                }
            }

            delete categoryTree;
        } else {
            cout << "\033[1;31mSeller login failed. User not found or password is incorrect.\033[0m" << endl;
            cout << "----------------------------------------\n";
        }
    } else if (option == 2) { // Seller Registration
        registerUser(sellerUsers, "sellers.csv");
    } else if (option == 3) { // Go back
        continue;
    } else {
        cout << "\033[1;31mInvalid choice. Try again.\033[0m" << endl;
        cout << "----------------------------------------\n\n";

    }
    }
    else if (role == 2) { // Buyer
            int option;
            cout << "----------------------------------------\n";
            cout << "\n\033[4;34mBuyer Interface\033[0m\n" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Go back" << endl;
            cin >> option;

            if (option == 1) { // Buyer Login
                User* buyer = loginUser(buyerUsers);
                if (buyer) {
                    cout << "Buyer logged in." << endl;
                    // cout << "----------------------------------------\n";
                    // Implement buyer-specific actions here
                    CategoryNode* categoryTree = nullptr;
    int categoryNumber = 1;
    map<int, string> categoryNumbers;

    // Insert products into the category tree
    categoryTree = insertProduct(categoryTree, Product{"HP Pavilion", "HP", 89999.99}, "Electronics/Laptops");
    categoryTree = insertProduct(categoryTree, Product{"Asus Vivobook 14", "Asus", 63599.99}, "Electronics/Laptops");
    categoryTree = insertProduct(categoryTree, Product{"Samsung M32", "Samsung", 22999.99}, "Electronics/Smartphones");
    categoryTree = insertProduct(categoryTree, Product{"Motorola edge 40", "Motorola", 29999.99}, "Electronics/Smartphones");
    categoryTree = insertProduct(categoryTree, Product{"Samsung Crystal 55'", "Samsung", 44999.99}, "Electronics/TV");
    categoryTree = insertProduct(categoryTree, Product{"Sony Bravia 43'", "Sony", 59999.99}, "Electronics/TV");

    int choice;
    string selectedCategory;

    while (true) {
        
        cout << "\033[34m----------------------------------------------------\033[0m\n";
        cout << "\n\033[33m=== Product Categories ===\033[0m" << endl;
        displayCategories1(categoryTree, categoryNumbers, categoryNumber);
        cout << categoryNumber << ". Quit" << endl;
        cout << "Enter the number of your choice: ";
        cin >> choice;

        if (choice == categoryNumber) {
            cout << "Exiting the program." << endl;
            break;
        } else if (categoryNumbers.find(choice) != categoryNumbers.end()) {
            selectedCategory = categoryNumbers[choice];
            displayProductsInCategory(categoryTree, selectedCategory);
        } else {
            cout << "\033[1;31mInvalid choice. Try again.\033[0m" << endl;
        }
    }


                } else {
                    cout << "Buyer login failed. User not found or password is incorrect." << endl;
                    cout << "----------------------------------------\n";
                }
            } else if (option == 2) { // Buyer Registration
                registerUser(buyerUsers, "buyers.csv");
            } else if (option == 3) { // Go back
                continue;
            } else {
                cout << "\033[1;31mInvalid choice. Try again.\033[0m" << endl;
            }
        } else if (role == 3) { // Quit
            break;
        } else {
            cout << "\033[1;31mInvalid choice. Try again.\033[0m" << endl;
        }
    }
    return 0;
}
