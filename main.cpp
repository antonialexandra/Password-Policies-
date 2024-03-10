#include <iostream>
#include<vector>

using namespace std;

class Policy {
protected:
    bool isChecked;
public:
    virtual void check(const string &parola) = 0;

    bool getCheck() const {
        return isChecked;
    }
};

class LengthPolicy : public Policy {
private:
    uint16_t minLength, maxLength;

//- clasa trebuie să conțină un constructor public cu 1 parametru, care să inițializeze minimul cu valoarea dată și maximul cu valoarea 255.
//- clasa trebuie să conțină un constructor public cu 2 parametri, care să inițializeze minimul și maximul cu valorile date.
//- clasele trebuie să implementeze metoda check din clasa de bază. Aceasta trebuie să verifice ceea ce este specificat în cerință.
public:
    LengthPolicy(uint16_t minim) {
        minLength = minim;
        maxLength = 255;
    }

    LengthPolicy(uint16_t min, uint16_t max) {
        minLength = min;
        maxLength = max;
    }

    void check(const string &parola) {
        if (parola.size() >= minLength && parola.size() <= maxLength) {
            isChecked = true;
        } else {
            isChecked = false;
        }
    }
};

//Să se creeze o clasă cu numele ClassPolicy cu următoarele specificații:
//- clasa trebuie să fie moștenită din clasa Policy.
//- clasa trebuie să conțină 1 atribut privat numit minClassCount, acesta fiind un număr întreg fără semn pe 16 biți.
//- clasa trebuie să conțină un constructor public cu 1 parametru, care să inițializeze atributul cu valoarea specificată.
//- clasele trebuie să implementeze metoda check din clasa de bază. Aceasta trebuie să verifice ceea ce este specificat în cerință.
class ClassPolicy : public Policy {
private:
    uint16_t minClassCount = 0;
public:
    ClassPolicy(uint16_t x) {
        minClassCount = x;
    }

    void check(const string &parola) override {
        int majuscula = 0, mic = 0, cifra = 0, altcv = 0;
        for (int i = 0; i < parola.size(); i++) {
            if (isupper(parola[i])) {
                majuscula = 1;
            } else if (islower(parola[i])) {
                mic = 1;
            } else if (isdigit(parola[i])) {
                cifra = 1;
            } else altcv = 1;
        }
        int nr_caractere = 0;
        nr_caractere = majuscula + mic + cifra + altcv;
        if (nr_caractere > 0 && nr_caractere >= minClassCount) {
            isChecked = true;
        } else isChecked = false;
    }
};

class IncludePolicy : public Policy {
private:
    char characterType;
public:
    IncludePolicy(char caracter) {
        characterType = caracter;
    }

    void check(const string &parola) override {
        int ok = 0;
        for (int i = 0; i < parola.size(); i++) {
            if (characterType == 'A') {
                if (isupper(parola[i])) {
                    // isChecked = true;
                    ok = 1;
                }
            } else if (characterType == 'a') {
                if (islower(parola[i])) {
                    //isChecked = true;
                    ok = 1;
                }
            } else if (characterType == '0') {
                if (isdigit(parola[i])) {
                    //isChecked = true;
                    ok = 1;
                }
            } else if (characterType == '$') {
                if (!isupper(parola[i]) && !islower(parola[i]) && !isdigit(parola[i])) {
                    //isChecked = true;
                    ok = 1;
                }
            } else /*isChecked = false;*/ok = 0;
        }
        if (ok >= 1) {
            isChecked = true;
        } else isChecked = false;

    }
};

class NotIncludePolicy : public Policy {
private:
    char characterType;
public:
    NotIncludePolicy(char caracter) {
        characterType = caracter;
    }

    void check(const string &parola) override {
        int ok1 = 1;
        for (int i = 0; i < parola.size(); i++) {
            if (characterType == 'A') {
                if (isupper(parola[i])) {
                    // isChecked = true;
                    ok1 = 0;
                }
            } else if (characterType == 'a') {
                if (islower(parola[i])) {
                    // isChecked = true;
                    ok1 = 0;
                }
            } else if (characterType == '0') {
                if (isdigit(parola[i])) {
                    //isChecked = true;
                    ok1 = 0;
                }
            } else if (characterType == '$') {
                if (!isupper(parola[i]) && !islower(parola[i]) && !isdigit(parola[i])) {
                    // isChecked = true;
                    ok1 = 0;
                }
            } else /*isChecked = false;*/ok1 = 1;

        }
        if (ok1 == 0) {
            isChecked = false;
        } else {
            isChecked = true;
        }

    }
};

class RepetitionPolicy : public Policy {
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t x) {
        maxCount = x;
    }

    void check(const string &parola) override {
        int z = 1, max = 0;

        for (int i = 0; i < parola.length(); i++) {
            if (parola[i] == parola[i + 1]) {
                z++;
                if (max < z) {
                    max = z;
                }
            } else {
                z = 1;
            }
            if (max <= maxCount)
                isChecked = true;
            else
                isChecked = false;
        }
    }
};

class ConsecutivePolicy : public Policy {
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t x) {
        maxCount = x;
    }

    void check(const string &parola) override {


        int max = 0, z = 1;
        for (int i = 0; i < parola.size(); i++) {
            if (parola[i] == parola[i + 1] - 1) {
                z++;
                if (max < z)
                    max = z;
            } else {
                z = 1;
            }
        }
        if (max <= maxCount) isChecked = true;
        else isChecked = false;
    }
};

string checkPassword(string parola, vector<Policy *> v) {
    for (int i = 0; i < v.size(); i++) {
        v[i]->check(parola);
        if (v[i]->getCheck() == false) {
            return "NOK";
        }
    }
    return "OK";
}

int main() {

    int n, c1, c2;
    cin >> n;
    char a;
    vector<Policy *> cerinte;
    string conditie, parola;
    for (int i = 0; i < n; i++) {
        cin >> conditie;
        if (conditie == "length") {
            cin >> c1;
            if (getchar() == ' ') {
                cin >> c2;
                cerinte.push_back(new LengthPolicy(c1, c2));
            } else
                cerinte.push_back((new LengthPolicy(c1)));
        }


        if (conditie == "class") {
            cin >> c1;
            cerinte.push_back(new ClassPolicy(c1));
        }
        if (conditie == "include") {
            cin >> a;
            cerinte.push_back(new IncludePolicy(a));
        }
        if (conditie == "ninclude") {
            cin >> a;
            cerinte.push_back(new NotIncludePolicy(a));
        }
        if (conditie == "repetition") {
            cin >> c1;
            cerinte.push_back(new RepetitionPolicy(c1));
        }
        if (conditie == "consecutive") {
            cin >> c1;
            cerinte.push_back(new ConsecutivePolicy(c1));
        }
    }
    while(cin>>parola){
        cout<<checkPassword(parola, cerinte)<<endl;
    }


    return 0;
}
