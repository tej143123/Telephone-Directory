#include <iostream>
#include <cstring>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

struct TreeNode
{
    int id;
    int contactno;
    char name[20];
    char address[50];

    TreeNode *left;
    TreeNode *right;
};

class td // class for functions or operations
{
private:
    TreeNode* root;
    int totalperson;

public:
    td();
    bool respond();
    int showmenu();
    bool insertobject();
    bool addtoarray(int, char*, char*, int);
    bool listdirectory();
    bool searchTreeNode();
    bool updateTreeNode();
    bool deleteTreeNode();
    bool importContacts(const string& filename);

    bool insertnode(TreeNode *newNode);
    bool insertdata(int, char*, char*, int);
    bool inputnode();

    void PrintOne(TreeNode *T);
    bool PrintTree();
    void PrintAll(TreeNode *T);
    bool Searchnode(int id);
    bool Search();

    bool Deletenode(int id);
    bool Deletee();

    bool Updatenode(int id);
    bool Update();
};

td::td() // default constructor
{
    root = nullptr;
    totalperson = 0;
}

bool td::insertnode(TreeNode *newNode)
{
    TreeNode *temp = root;
    TreeNode *back = nullptr;

    while (temp != nullptr) // Loop till temp falls out of the tree
    {
        back = temp;
        if (newNode->id < temp->id)
            temp = temp->left;
        else
            temp = temp->right;
    }

    // Now attach the new node to the node that back points to
    if (back == nullptr) // Attach as root node in a new tree
        root = newNode;
    else
    {
        if (newNode->id < back->id)
            back->left = newNode;
        else
            back->right = newNode;
    }
    return true;
}

bool td::insertdata(int id, char *name, char *address, int contactno)
{
    TreeNode *newNode = new TreeNode();

    // Create the new node and copy data into it
    newNode->id = id;
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0'; // Ensure null termination
    strncpy(newNode->address, address, sizeof(newNode->address) - 1);
    newNode->address[sizeof(newNode->address) - 1] = '\0'; // Ensure null termination
    newNode->contactno = contactno;
    newNode->left = newNode->right = nullptr;

    // Call other Insert() to do the actual insertion
    return insertnode(newNode);
}

bool td::inputnode()
{
    cout << "*" << endl;
    cout << "  Telephone Directory: Insert Menu" << endl;
    cout << "*" << endl;

    int id;
    char name[20];
    char address[50];
    int contactno;
    int optionofsave;

    // Takes the value of the record
    cout << "Enter Id: ";
    cin >> id;
    cin.ignore(); // Ignore the newline character left in the buffer

    cout << "Enter Name: ";
    cin.getline(name, sizeof(name));

    cout << "Enter Contact No: ";
    cin >> contactno;
    cin.ignore(); // Ignore the newline character left in the buffer

    cout << "Enter Address: ";
    cin.getline(address, sizeof(address));

    cout << "Press 1 to save, 0 to not save: ";
    cin >> optionofsave;

    if (optionofsave == 1) // if want to save then send values to the addtoarray function
    {
        insertdata(id, name, address, contactno);
        cout << "Record saved successfully." << endl;
    }
    else if (optionofsave == 0)
    {
        return true;
    }

    char insertagain;
    cout << "Want to insert another record? [y/n]: ";
    cin >> insertagain;

    return insertagain != 'y';
}

bool td::respond() // function to get the response of the user for particular functions
{
    int option = showmenu();
    bool result = true;

    switch (option)
    {
    case 1:
        do {
            system("CLS"); // clear screen
            result = inputnode(); // calls the insert function
        } while (!result);
        break;
    case 2:
        do {
            system("CLS");
            result = PrintTree();
        } while (!result);
        break;
    case 3:
        do {
            system("CLS");
            result = Search();
        } while (!result);
        break;
    case 4:
        do {
            system("CLS");
            result = Update();
        } while (!result);
        break;
    case 5:
        do {
            system("CLS");
            result = Deletee();
        } while (!result);
        break;
    case 6:
        {
            system("CLS");
            string filename;
            cout << "Enter filename to import contacts: ";
            cin >> filename;
            importContacts(filename);
        }
        break;
    case 7:
        return false;
    }
    return true;
}

int td::showmenu() // shows menu of the program
{
    system("CLS");
    int option;

    cout << "*" << endl;
    cout << "   Telephone Directory: Main Menu" << endl;
    cout << "*" << endl;

    cout << "\n\n1. Insert a new record\n2. List Records\n3. Search a Record\n";
    cout << "4. Update a record(using name or ID)\n5. Delete a Record\n6. Import Contacts\n7. Exit program";

    cout << "\n\nSelect Option [1, 2, 3, 4, 5, 6, 7]: ";
    cin >> option;

    return option;
}

void td::PrintOne(TreeNode *T)
{
    cout << T->id << "\t\t" << T->name << "\t\t" << T->address << "\t\t" << T->contactno << "\t\t\n";
}

void td::PrintAll(TreeNode *T)
{
    if (T != nullptr)
    {
        PrintAll(T->left);
        PrintOne(T);
        PrintAll(T->right);
    }
}

bool td::PrintTree()
{
    PrintAll(root);

    cout << "\nPress 'm' to go to Main menu:" << endl;
    char m;
    cin >> m;
    return m == 'm';
}

bool td::Searchnode(int id)
{
    TreeNode *curr = root;
    while (curr != nullptr)
    {
        if (curr->id == id)
            break;

        if (curr->id < id)
            curr = curr->right;
        else
            curr = curr->left;
    }
    if (curr == nullptr)
    {
        cout << "\nID not found:\n";
        return true;
    }
    cout << "\nFound the record:\n";
    PrintOne(curr);

    return true;
}

bool td::Search()
{
    cout << "*" << endl;
    cout << "  Telephone Directory: Search Menu" << endl;
    cout << "*" << endl;

    int idtofind;
    cout << "\nEnter id to be found: ";  // takes id to be searched
    cin >> idtofind;
    if (Searchnode(idtofind))
    {
        // Additional logic can be placed here if needed
    }

    char searchagain;
    cout << "\nDo you want to search another record? [y/n]: ";    // search again
    cin >> searchagain;
    return searchagain != 'y';
}

bool td::Deletenode(int id)
{
    TreeNode *curr = root;
    TreeNode *parent = nullptr;

    while (curr != nullptr)
    {
        if (curr->id == id)
            break;

        parent = curr;
        if (curr->id < id)
            curr = curr->right;
        else
            curr = curr->left;
    }

    if (curr == nullptr)
    {
        cout << "\nID not found:\n";
        return true;
    }

    if (curr->left == nullptr && curr->right == nullptr)
    {
        if (parent == nullptr)
        {
            root = nullptr;
        }
        else if (parent->left == curr)
        {
            parent->left = nullptr;
        }
        else
        {
            parent->right = nullptr;
        }
        delete curr;
    }
    else if (curr->left == nullptr)
    {
        if (parent == nullptr)
        {
            root = curr->right;
        }
        else if (parent->left == curr)
        {
            parent->left = curr->right;
        }
        else
        {
            parent->right = curr->right;
        }
        delete curr;
    }
    else if (curr->right == nullptr)
    {
        if (parent == nullptr)
        {
            root = curr->left;
        }
        else if (parent->left == curr)
        {
            parent->left = curr->left;
        }
        else
        {
            parent->right = curr->left;
        }
        delete curr;
    }
    else
    {
        TreeNode *succ = curr->right;
        TreeNode *succParent = curr;

        while (succ->left != nullptr)
        {
            succParent = succ;
            succ = succ->left;
        }

        curr->id = succ->id;
        strcpy(curr->name, succ->name);
        strcpy(curr->address, succ->address);
        curr->contactno = succ->contactno;

        if (succParent->left == succ)
        {
            succParent->left = succ->right;
        }
        else
        {
            succParent->right = succ->right;
        }

        delete succ;
    }

    cout << "Record deleted successfully." << endl;
    return true;
}

bool td::Deletee()
{
    cout << "*" << endl;
    cout << "  Telephone Directory: Delete Menu" << endl;
    cout << "*" << endl;

    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    Deletenode(id);

    char deleteagain;
    cout << "\nDo you want to delete another record? [y/n]: ";
    cin >> deleteagain;
    return deleteagain != 'y';
}

bool td::Updatenode(int id)
{
    TreeNode *curr = root;
    while (curr != nullptr)
    {
        if (curr->id == id)
            break;

        if (curr->id < id)
            curr = curr->right;
        else
            curr = curr->left;
    }
    if (curr == nullptr)
    {
        cout << "\nID not found:\n";
        return true;
    }
    cout << "\nFound the record:\n";
    PrintOne(curr);

    cout << "\nEnter new details:\n";

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(curr->name, sizeof(curr->name));

    cout << "Enter Contact No: ";
    cin >> curr->contactno;

    cout << "Enter Address: ";
    cin.ignore();
    cin.getline(curr->address, sizeof(curr->address));

    cout << "\nRecord updated successfully." << endl;

    return true;
}

bool td::Update()
{
    cout << "*" << endl;
    cout << "  Telephone Directory: Update Menu" << endl;
    cout << "*" << endl;

    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    Updatenode(id);

    char updateagain;
    cout << "\nDo you want to update another record? [y/n]: ";
    cin >> updateagain;
    return updateagain != 'y';
}

bool td::importContacts(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Failed to open file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        int id, contactno;
        string name, address;

        if (ss >> id >> ws && getline(ss, name, ',') && ss >> contactno >> ws && getline(ss, address))
        {
            if (!insertdata(id, &name[0], &address[0], contactno))
            {
                cout << "Failed to insert contact: " << name << endl;
            }
        }
        else
        {
            cout << "Invalid line format: " << line << endl;
        }
    }

    infile.close();
    cout << "Contacts imported successfully from " << filename << "." << endl;
    return true;
}

int main() // main function
{
    td t;

    while (t.respond()); // loop until exit is selected

    return 0;
}
