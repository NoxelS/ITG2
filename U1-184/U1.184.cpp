// Übung: Doppelt verkettete Listen

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Datastructure
struct person {
    string name;
    uint16_t gebtag;
    uint16_t gebmon;
    uint16_t gebjahr;
    person* next;
    person* prev;
    string toString() { return name + " " + to_string(gebtag) + "." + to_string(gebmon) + "." + to_string(gebjahr); }
};

// Beginning and current running person:
person* root;
person* current;

// Static data
#define ANZAHL 6
string list_name[ANZAHL] = {"Alpha", "Konrad Zuse", "Tim OReilly", "Bill Gates", "Mark Zuckerberg ", "Omega"};
uint16_t list_gebtag[ANZAHL] = {1, 22, 06, 28, 14, 31};
uint16_t list_gebmon[ANZAHL] = {1, 06, 06, 10, 5, 12};
uint16_t list_gebjahr[ANZAHL] = {0, 1910, 1954, 1955, 1984, 3600};

// Function to generate an empty person
person* gen_person() {
    person* temp = new person;  // Here you could also use malloc
    temp->name = "";
    temp->gebtag = 0;
    temp->gebmon = 0;
    temp->gebjahr = 0;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

// Function to initialize a list
int init_list() {
    // Create first element
    person* temp = gen_person();

    // Set properties of the first person
    temp->name = list_name[0];
    temp->gebjahr = list_gebjahr[0];
    temp->gebmon = list_gebmon[0];
    temp->gebtag = list_gebtag[0];

    // Set current root pointer to the first person
    root = temp;
    person* prevRunner = temp;

    // Loop through the list and add the other persons
    for (int i = 1; i < ANZAHL; i++) {
        temp->next = gen_person();

        temp = temp->next;
        temp->prev = prevRunner;
        prevRunner = temp;

        temp->name = list_name[i];
        temp->gebjahr = list_gebjahr[i];
        temp->gebmon = list_gebmon[i];
        temp->gebtag = list_gebtag[i];
    }
}

int print_list(string message = "User list") {
    cout << "======" + message + "======\n";
    current = root;
    cout << setw(32) << current->toString() << setw(32) << "(" << current->prev << "->" << current << "->"
         << current->next << ")" << endl;
    while (current->next != NULL) {
        current = current->next;
        cout << setw(32) << current->toString() << setw(32) << "(" << current->prev << "->" << current << "->"
             << current->next << ")" << endl;
    }
    cout << "============\n";
}

int add_person() {
    string nname, vorname, nachname;
    uint16_t ngebjahr;

    cout << "Vorname ( '-' zum Überspringen ) : ";
    cin >> vorname;

    if (vorname == "-") {
        return (0);
    }
    cout << "Nachname: ";
    cin >> nachname;
    nname = vorname + " " + nachname;
    cout << "Jahr: ";
    cin >> ngebjahr;

    current = root;

    /** Urspünglicher Code der nicht richtig funktioniert hat */
    // while (!(current->gebjahr<=ngebjahr && current->next->gebjahr>=ngebjahr))
    // {
    //     current = current->next;
    //     person *temp = gen_person();
    //     temp->name = nname;
    //     temp->gebjahr = ngebjahr;
    //     temp->next = current->next;
    //     current->next = temp;

    //     // For prev
    //     temp->prev = current;
    //     temp->next->prev = temp;
    // }

    while (current != NULL && current->next != NULL && current->next->gebjahr < ngebjahr) {
        current = current->next;
    }

    if (current->next == NULL) {
        // Person is the oldest
        person* temp = gen_person();
        temp->name = nname;
        temp->gebjahr = ngebjahr;
        temp->next = NULL;
        current->next = temp;
        // For prev
        temp->prev = current;
    } else {
        person* temp = gen_person();
        temp->name = nname;
        temp->gebjahr = ngebjahr;
        temp->next = current->next;
        current->next = temp;
        // For prev
        temp->prev = current;
        temp->next->prev = temp;
    }

    return 1;
}

int remove_person() {
    string serach_name;
    cout << "Name zum Löschen ( '-' zum Überspringen ): ";

    // Get user input but accept space seperated values
    // This does seperate spaces cin >> serach_name;
    cin.ignore();
    getline(cin, serach_name);

    if (serach_name == "-") {
        return (0);
    }

    if (serach_name.length() > 0) {
        current = root;
        while (current != NULL && current->name != serach_name) {
            current = current->next;
        }

        if (current != NULL) {
            // Ask the user to confirm
            cout << "Soll der Nutzer \"" + current->toString() + "\" wirklich gelöscht werden? (y/n) ";
            string answer;
            cin >> answer;
            if (answer == "y") {
                person* userToDelete = current;
                current = root;
                while (current != NULL && current->next != userToDelete) {
                    current = current->next;
                }

                if (current == NULL) {
                    // This is the first element and we only need to reset the root
                    // pointer
                    root = userToDelete->next;

                    // Make next element the root element
                    userToDelete->next->prev = NULL;
                } else {
                    // This is not the first element and we need to reset the next pointer
                    // of the previous element
                    current->next = userToDelete->next;

                    // And we need to reset the prev pointer of the next element
                    userToDelete->next->prev = current;
                }

                // Free up memory
                delete userToDelete;

                // Print the new user list
                print_list("User list (-1)");

                return 1;
            }
        } else {
            cout << "Person not found" << endl;
            return 1;
        }
    }
}

int printOlderPerson() {
    string serach_name;
    cout << "Name um ältere Personen zu finden ( '-' zum Überspringen ): ";

    // Get user input but accept space seperated values
    // This does seperate spaces cin >> serach_name;
    getline(cin, serach_name);

    if (serach_name == "-") {
        return (0);
    }

    if (serach_name.length() > 0) {
        current = root;
        while (current != NULL && current->name != serach_name) {
            current = current->next;
        }

        if (current != NULL) {
            // The current pointer points to the user we are looking for
            cout << "Alle älteren Personen von " + current->toString() + ":\n";
            while (current->prev != NULL) {
                current = current->prev;
                cout << current->toString() << endl;
            }
        }
        return (1);
    }
}

int main() {
    person* test = gen_person();
    init_list();
    print_list();
    while (add_person()) {
        print_list("User list (+1)");
    }
    while (remove_person()) {
    }
    while (printOlderPerson()) {
    }
}