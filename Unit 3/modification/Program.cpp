#include <iostream>
#include <string>
using namespace std;

// Singly Linked List
struct SNode {
    string song;
    SNode* next;
};

class Singly {
    SNode* head = NULL;

public:
    void insert(string s) {
        SNode* n = new SNode{s, NULL};
        if (!head) head = n;
        else {
            SNode* p = head;
            while (p->next) p = p->next;
            p->next = n;
        }
    }

    void remove(string s) {
        SNode *p = head, *prev = NULL;
        while (p && p->song != s) {
            prev = p;
            p = p->next;
        }
        if (!p) {
            cout << "Song not found.\n";
            return;
        }
        if (prev) prev->next = p->next;
        else head = p->next;
        delete p;
        cout << "Song deleted.\n";
    }

    void search(string s) {
        SNode* p = head;
        int pos = 1;
        while (p) {
            if (p->song == s) {
                cout << "Found at position " << pos << "\n";
                return;
            }
            p = p->next;
            pos++;
        }
        cout << "Song not found.\n";
    }

    void display() {
        SNode* p = head;
        if (!p) { cout << "Playlist is empty.\n"; return; }
        while (p) {
            cout << p->song;
            if (p->next) cout << " -> ";
            p = p->next;
        }
        cout << "\n";
    }

    void middle() {
        SNode *slow = head, *fast = head;
        if (!head) { cout << "Playlist is empty.\n"; return; }
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        cout << "Middle song: " << slow->song << "\n";
    }
};

// Circular Linked List
struct CNode {
    string song;
    CNode* next;
};

class Circular {
    CNode* tail = NULL;

public:
    void insert(string s) {
        CNode* n = new CNode{s, NULL};
        if (!tail) {
            tail = n;
            n->next = n;
        } else {
            n->next = tail->next;
            tail->next = n;
            tail = n;
        }
    }

    void remove(string s) {
        if (!tail) { cout << "Song not found.\n"; return; }
        CNode* cur = tail->next;
        CNode* prev = tail;

        do {
            if (cur->song == s) {
                if (cur == tail && cur->next == cur) {
                    tail = NULL;
                } else {
                    prev->next = cur->next;
                    if (cur == tail) tail = prev;
                }
                delete cur;
                cout << "Song deleted.\n";
                return;
            }
            prev = cur;
            cur = cur->next;
        } while (cur != tail->next);

        cout << "Song not found.\n";
    }

    void search(string s) {
        if (!tail) { cout << "Song not found.\n"; return; }
        CNode* p = tail->next;
        int pos = 1;
        do {
            if (p->song == s) {
                cout << "Found at position " << pos << "\n";
                return;
            }
            p = p->next;
            pos++;
        } while (p != tail->next);
        cout << "Song not found.\n";
    }

    void display() {
        if (!tail) { cout << "Playlist is empty.\n"; return; }
        CNode* p = tail->next;
        do {
            cout << p->song;
            p = p->next;
            if (p != tail->next) cout << " -> ";
        } while (p != tail->next);
        cout << " -> (back to start)\n";
    }

    void middle() {
        if (!tail) { cout << "Playlist is empty.\n"; return; }
        CNode* slow = tail->next;
        CNode* fast = tail->next;

        do {
            if (fast->next == tail->next ||
                fast->next->next == tail->next)
                break;
            slow = slow->next;
            fast = fast->next->next;
        } while (true);

        cout << "Middle song: " << slow->song << "\n";
    }
};

// Doubly Linked List
struct DNode {
    string song;
    DNode *prev, *next;
};

class Doubly {
    DNode* head = NULL;

public:
    void insert(string s) {
        DNode* n = new DNode{s, NULL, NULL};
        if (!head) head = n;
        else {
            DNode* p = head;
            while (p->next) p = p->next;
            p->next = n;
            n->prev = p;
        }
    }

    void remove(string s) {
        DNode* p = head;
        while (p && p->song != s) p = p->next;
        if (!p) { cout << "Song not found.\n"; return; }

        if (p->prev) p->prev->next = p->next;
        else head = p->next;
        if (p->next) p->next->prev = p->prev;

        delete p;
        cout << "Song deleted.\n";
    }

    void search(string s) {
        DNode* p = head;
        int pos = 1;
        while (p) {
            if (p->song == s) {
                cout << "Found at position " << pos << "\n";
                return;
            }
            p = p->next;
            pos++;
        }
        cout << "Song not found.\n";
    }

    void display() {
        DNode* p = head;
        if (!p) { cout << "Playlist is empty.\n"; return; }
        while (p) {
            cout << p->song;
            if (p->next) cout << " <-> ";
            p = p->next;
        }
        cout << "\n";
    }

    void middle() {
        if (!head) { cout << "Playlist is empty.\n"; return; }
        DNode* p = head;
        int count = 0;
        while (p) { count++; p = p->next; }

        p = head;
        for (int i = 0; i < count / 2; i++)
            p = p->next;

        cout << "Middle song: " << p->song << "\n";
    }
};

int main() {
    Singly s;
    Circular c;
    Doubly d;
    int choice;
    string name;

    do {
        cout << "\n--- PLAYLIST MENU ---\n";
        cout << "1. Insert song\n";
        cout << "2. Delete song\n";
        cout << "3. Search song\n";
        cout << "4. Display playlists\n";
        cout << "5. Find middle song\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter song name: ";
            getline(cin >> ws, name);
            s.insert(name);
            c.insert(name);
            d.insert(name);
            cout << "Song inserted in all lists.\n";
            break;

        case 2:
            cout << "Enter song name to delete: ";
            getline(cin >> ws, name);
            cout << "Singly: "; s.remove(name);
            cout << "Circular: "; c.remove(name);
            cout << "Doubly: "; d.remove(name);
            break;

        case 3:
            cout << "Enter song name to search: ";
            getline(cin >> ws, name);
            cout << "Singly: "; s.search(name);
            cout << "Circular: "; c.search(name);
            cout << "Doubly: "; d.search(name);
            break;

        case 4:
            cout << "Singly: "; s.display();
            cout << "Circular: "; c.display();
            cout << "Doubly: "; d.display();
            break;

        case 5:
            cout << "Singly linked list: "; s.middle();
            cout << "Circular linked list: "; c.middle();
            cout << "Doubly linked list: "; d.middle();
            break;

        case 6:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
