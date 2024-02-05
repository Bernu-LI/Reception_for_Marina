#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct person {
    string full_name;
    long long int passport_details{};
};

struct room {
    room(const string& category_, int area_, int number_of_beds_, int price_):
    category(category_), area(area_), number_of_beds(number_of_beds_), price(price_) {}
    const string& category;
    int area;
    int number_of_beds;
    int price;
    person* guest = nullptr;
};

ostream& operator << (ostream& os, room* room) {
    os << "category: " << room->category << endl;
    os << "area: " << room->area << endl;
    os << "number of beds: " << room->number_of_beds << endl;
    os << "price: " << room->price << endl;
    return os;
}

void request_visitor_details(person& person) {
    cout << "Please enter your full name: ";
    cin.ignore(); getline(cin, person.full_name);
    cout << "Please enter your passport details: ";
    cin >> person.passport_details;
    cout << "\n\n";
}

void suggest_a_number(vector <room*>& available_rooms, vector <room*>& occupied_rooms, person* person) {
    cout << "Hello! What number do you prefer? (If none suits you, enter zero)\n";
    for (int i = 0; i < available_rooms.size(); i++) {
        cout << i + 1 << ".\n";
        cout << available_rooms[i] << endl;
    }
    cout << "Response: ";
    int response;
    cin >> response;
    while (response < 0 or response > available_rooms.size()) {
        cout << "Incorrect data entered. Try again." << endl;
        cout << "Response: ";
        cin >> response;
    }
    if (response == 0) {
        cout << "Sorry. Come back another time!\n\n\n";
    }
    else {
        available_rooms[response - 1]->guest = person;
        occupied_rooms.push_back(available_rooms[response]);
        available_rooms.erase(available_rooms.begin() + response - 1);
        cout << "Excellent choice! Have a good time!\n\n\n";
    }
}

int main() {
    int number_of_rooms;
    cout << "Enter the number of rooms: ";
    cin >> number_of_rooms;
    vector <room*> available_rooms;
    vector <room*> occupied_rooms;
    for (int i = 0; i < number_of_rooms; i++) {
        string category;
        int area;
        int number_of_beds;
        int price;
        cout << "Enter category, area, number of beds and price: ";
        cin >> category >> area >> number_of_beds >> price;
        room* aRoom = new room(category, area, number_of_beds, price);
        available_rooms.push_back(aRoom);
    }
    cout << "\n\n";
    person person;
    request_visitor_details(person);
    while (person.full_name != "0" and person.passport_details != 0) {
        suggest_a_number(available_rooms, occupied_rooms, &person);
        if (available_rooms.empty()) {
            cout << "Sorry, there are no more available places :(";
            break;
        }
        request_visitor_details(person);
    }
    return 0;
}