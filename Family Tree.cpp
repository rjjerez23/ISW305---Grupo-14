#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    string gender;
    vector<Person*> children;

public:
    Person(string name, int age, string gender) {
        this->name = name;
        this->age = age;
        this->gender = gender;
    }

    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    string getGender() {
        return gender;
    }

    void addChild(Person* child) {
        children.push_back(child);
    }

    vector<Person*> getChildren() {
        return children;
    }
};

class FamilyTree {
private:
    Person* root;

public:
    FamilyTree(Person* root) {
        this->root = root;
    }

    Person* getRoot() {
        return root;
    }

    bool insertRelationship(Person* parent, Person* child) {
        if (parent == nullptr) return false;
        parent->addChild(child);
        return true;
    }

    Person* findPerson(Person* current, string name) {
        if (current == nullptr) return nullptr;
        if (current->getName() == name) return current;

        for (Person* child : current->getChildren()) {
            Person* found = findPerson(child, name);
            if (found != nullptr) return found;
        }
        return nullptr;
    }

    void preorder(Person* node, int level) {
        if (node == nullptr) return;

        for (int i = 0; i < level; i++) cout << "  ";
        cout << node->getName() << " (" << node->getAge() << ", " << node->getGender() << ")" << endl;

        for (Person* child : node->getChildren()) {
            preorder(child, level + 1);
        }
    }

    void showTree() {
        preorder(root, 0);
    }
};

int main() {
    Person* grandfather = new Person("Jose", 78, "M");
    Person* grandmother = new Person("Maria", 75, "F");
    Person* father = new Person("Carlos", 50, "M");
    Person* mother = new Person("Ana", 48, "F");
    Person* son = new Person("Luis", 20, "M");
    Person* daughter = new Person("Sofia", 18, "F");

    FamilyTree tree(grandfather);

    tree.insertRelationship(grandfather, father);
    tree.insertRelationship(grandfather, grandmother);
    tree.insertRelationship(father, son);
    tree.insertRelationship(father, daughter);
    tree.insertRelationship(father, mother);

    cout << "Family Tree (Preorder):" << endl;
    tree.showTree();

    delete grandfather;
    delete grandmother;
    delete father;
    delete mother;
    delete son;
    delete daughter;

    return 0;
}