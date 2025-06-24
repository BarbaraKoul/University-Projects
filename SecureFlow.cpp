#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

class Role{
    public:
        Role(string n){
            name=n;
        }
        virtual void performTask() const =0;
        virtual ~Role(){}
    protected:
        string name;
};

class Technician: public Role{
    public:
        Technician(string &n, int &s): Role(n), skillLevel(s){}
        void performTask() const override {
            cout<<"[TECHNICIAN] "<<name<<" performs repair task"<<endl;
        }
    private:
        int skillLevel;
};

class Analyst: public Role{
    public:
        void performTask() const override {
            cout<<"[ANALYST] "<<name<<" is interested in "<<field<<endl;
        }
        Analyst(string &n, string &f): Role(n), field(f){}
    private:
        string field;
};
class Inspector: public Role{
    public:
        void performTask() const override{
            cout<<"[INSPECTOR] "<<name<<" checks certifications"<<endl;
        }
    
        Inspector(string &n, vector<string>& c): Role(n), certifications(c){}
    private:
        vector<string> certifications;  
};

class BaseUser {
public:
    virtual void execute() const = 0;
    virtual ~BaseUser() = default;
};

template <typename T>

class User: public BaseUser{
    public:
        User<T>(string u, unique_ptr<T> r): username(u), role(move(r)){}
        void execute() const override{
            cout << "User: " << username << " executing: ";
            this->role->performTask();
        }
    private:
        string username;
        unique_ptr <T> role;
};

int main(){
    vector<unique_ptr<BaseUser>> list;
    cout<<"Give the Users you want to file (username and one of the next Roles: Technician, Analyst, Inspector): "<<endl;
    string username, type;
    while(cin>>username>>type){
        if(type=="Technician"){
            string name;
            int Level;
            cout<<"Give the name and skill Level of the User: "<<endl;
            cin>>name>>Level;
            User<Technician> tech(username, make_unique<Technician>(name,Level));
            list.push_back(move(make_unique<User<Technician>>(move(tech))));
        }
        else if(type=="Analyst"){
            string name, field;
            cout<<"Give the name and the field of the User: "<<endl;
            cin>>name>>field;
            User<Analyst> an(username, make_unique<Analyst>(name, field));
            list.push_back(move(make_unique<User<Analyst>>(move(an))));

        }
        else if(type=="Inspector"){
            string name, singleCert;
            vector<string> certs;
            cout<<"Give the name and the certifications of the User: "<<endl;
            cin>>name;
            while(cin>>singleCert){
                certs.push_back(singleCert);
            }
            User<Inspector> insp(name, make_unique<Inspector>(name, certs));
            list.push_back(move(make_unique<User<Inspector>>(move(insp))));
        }
        else{
            try{
                throw "Invalid Role! Please give a valid Role";
            }
            catch(string &s){
                cout<<s<<endl;
            }
        }
    }
    cout<<"Your Users are: "<<endl;
    for(int i=0; i<list.size(); i++){
        list[i]->execute();
    }
    return 0;
}
