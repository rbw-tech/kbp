#include <iostream>
#include <string>
#include <vector>

using namespace std;

string balikString(string str) {
    string hasil = "";
    for (int i = str.length() - 1; i >= 0; i--) {
        hasil += str[i];
    }
    return hasil;
}

int main() {
    vector<string> inputs;
    string input;

    cout << "// Harap enter 2x seusai memasukkan semua string yang diinginkan\n";
    cout << "Masukkan string (Misal: Nama, NIM, Umur, Asal Daerah (enter pada setiap string)):\n";

    while (getline(cin, input) && !input.empty()) {
        inputs.push_back(input);
    }

    cout << "\nHasil pembalikan string:\n";

    for (int i = 0; i < inputs.size(); i++) {
        cout << "Asli: " << inputs[i] << endl;
        cout << "Terbalik: " << balikString(inputs[i]) << endl << endl;
    }

    return 0;
}
