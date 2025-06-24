#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class User
{
public:
    User()
    {
        username = "";
        email = "";
    }
    User(const string &u, const string &e)
    {
        username = u;
        email = e;
    }
    virtual void printInfo() const
    {
        cout << "[USER] " << username << " - " << email << endl;
    }
    virtual ~User(){}
    string getUsername()
    {
        return username;
    }
    friend ostream &operator<<(ostream &out, const User &u)
    {
        out << u.username << " - " << u.email << endl;
        return out;
    }

protected:
    string username;
    string email;
};

class Admin : public User
{
public:
    Admin(const string &u, const string &e, const vector<string> &p) : User(u, e), permissions(p) {}
    ~Admin(){
        
    }
    void printInfo() const
    {
        cout << "[ADMIN] " << username << " - " << email << endl
             << "Permissions: ";
        for (size_t i = 0; i < permissions.size(); ++i)
        {
            cout << permissions[i];
            if (i < permissions.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }

private:
    vector<string> permissions;
};

int main()
{
    vector<unique_ptr<User>> v;
    vector<string> v1 = {"Thl", "Boss"};
    vector<string> v2 = {"Lefta", "Spitia"};
    v.push_back(make_unique<User>("Barbie", "barbarakoulour@gmail.com"));
    v.push_back(make_unique<User>("Maraki", "mariakoulourio@gmail.com"));
    v.push_back(make_unique<Admin>("Toula", "floridis77@live.com", v1));
    v.push_back(make_unique<Admin>("Principal", "lefteruskoulouriotis1@gmail.com", v2));
    for (int i = 0; i < v.size(); i++)
    {
        v[i]->printInfo();
    }
    return 0;
}