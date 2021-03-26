#include "pharmacy.h"

med::med(){}
med::med(const string& name,const int& id,const double& price):name(name),id(id),price(price){
}

void med::set_name(const string& name){
    this->name=name;
}
const string& med::get_name() const{
    return this->name;
}
void med::set_id(const int& id){
    this->id=id;
}
const int& med::get_id() const{
    return this->id;
}
void med::set_price(const double& price){
    this->price=price;
}
const double& med::get_price() const{
    return this->price;
}

med:: ~med(){}



inject:: inject():med(){};
inject::inject(const string& name,const int& id,const double& price,const int& num_of_injects,const double& size_of_needle):med(name,id,price),num_of_injects(num_of_injects),size_of_needle(size_of_needle){
    this->type="inject";
}

const string& inject::get_type(){
    this->type="inject";
    return this->type;
}

void inject::set_needle_size(const double& size){
    this->size_of_needle=size;
}
const double& inject::get_needle_size() const{
    return this->size_of_needle;
}
void inject::set_injection_times(const int& num){
    this->num_of_injects=num;
}
const int& inject::get_injection_times() const{
    return this->num_of_injects;
}
void inject::show_dosage()const{
    cout<<num_of_injects<<" injects a day with a needle of size "<<size_of_needle<<"\n";
}
med* inject::clone() const{
    return new inject(*this);
}

inject:: ~inject(){}




pill::pill() : med() {
}
pill::pill(const string &name, const int &id, const double &price, const int &pills_num, const double &cons) : med(name, id,price),pills_num(pills_num),med_concentration(cons) {
}
const string& pill::get_type() {
    this->type = "pill";
    return this->type;
}

const int &pill::get_pills_num() const {
    return this->pills_num;
}

void pill::set_pills_num(const int &num) {
    this->pills_num = num;
}

const double &pill::get_med_concentration() const {
    return this->med_concentration;
}

void pill::set_med_concentration(const double &cons) {
    this->med_concentration = cons;
}

void pill::show_dosage() const {
    cout << pills_num << " pills a day of concentration " << med_concentration << " ml\n";
}

med* pill::clone() const {
    return new pill(*this);
}

pill::~pill(){};



med_manager::med_manager() {}

const vector<med*>& med_manager:: get_meds() const{
    return this->all_meds;
}

bool med_manager::valid_id(const int &id)const{
    for (const auto &element:all_meds) {
        if (element->get_id() == id) {
            return true;
        }
    }
    return false;
}
void med_manager::show_med(const int &id)const{
    if (all_meds.empty()){
        cout << "no meds\n";
        return;}
    else
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                cout<<"name: "<<medecine->get_name()<<"\tprice: "<<medecine->get_price()<<"\ttype: "<<medecine->get_type()<<"\n";
                medecine->show_dosage();
                return;}

        }
    cout<<"med not found\n";
    return;
}
void med_manager::add_med( med &medicine){
    all_meds.push_back(medicine.clone()); ///use of clone
    cout<<"med was added\n";}

void med_manager::delete_med( const int &id) {
    auto it = all_meds.begin();
    while (it != all_meds.end()){
        if ((*it)->get_id() == id) {
            delete *it;
            all_meds.erase(it);
           cout<<"med was deleted\n";
            return;}
        it++;
    }
    cout<<"med not found\n";
    return;
}

void med_manager::update_price(int id,double new_price){
    if (!valid_id(id))
        cout<<"med not found\n";
    else{
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                medecine->set_price(new_price);
                cout<<"price was updated\n";
                return;
            }
        }
    }
    return;
}

void med_manager::show_all_meds()const {
    if (all_meds.empty())
        cout << "no meds\n";
    else
        for (const auto element:all_meds) {
            cout << "id: " << element->get_id() << "\tprice: " << element->get_price() << "\ttype: "
                 << element->get_type() << "\n";
        }
    return;

}
void med_manager::show_injects()const{
    bool empty=1;
    for (const auto &element:all_meds) {
        if(element->get_type()=="inject"){
            empty=0;
            this->show_med(element->get_id());
        }
    }
    if(empty)
        cout<<"no injection meds\n";
    return;
}
void med_manager::show_pills()const{
    bool empty=1;
    for (const auto &element:all_meds) {
        if(element->get_type()=="pill"){
            empty=0;
            this->show_med(element->get_id());
        }
    }
    if(empty)
        cout<<"no pill meds\n";
    return;
}
med_manager::~med_manager(){
    for ( auto &element:all_meds) {
        delete element;
        element= nullptr;
    }
    all_meds.clear();
}



void my_system::run() {
    while(true){
        cout<< "enter from 0 to 5:\n1: insert new med\n2: update price\n3: show meds\n4: search\n5: delete\n0: terminate\n";
        int option;
        cin >> option;
        switch (option) {
            case 1: {
                cout << "enter med name, price, id\n";
                string name;
                double price;
                int id;
                int type;
                cin >> name >> price >> id;
                while(pharmacy.valid_id(id)){
                    cout<<"already existing id, enter another one\n";
                    cin>>id;
                }
                bool valid=0;
                while (!valid){
                    cout << "enter a type num from 1 to 2\n1: injections\t2: pills\t";
                    cin >> type;
                    if (type == 1) {
                        valid=1;
                        cout << "enter number of daily doses and size of needle\n";
                        int injection_num;double needle_size;
                        cin >> injection_num >> needle_size;
                        inject med(name, id, price, injection_num, needle_size);
                        pharmacy.add_med(med);
                    } else if (type == 2) {
                        valid=1;
                        cout << "enter number of daily doses and med concentration in ml\n";
                        int doses;double med_concentration;
                        cin >> doses >> med_concentration;
                        pill med(name, price, id, doses, med_concentration);
                        pharmacy.add_med(med);
                    } else{
                        cout << "invalid number\n";
                    }
                }
                break;
            }
            case 2: {
                cout << "enter the med id and the new price\n";
                int id;
                double price;
                cin >> id >> price;
                if(!pharmacy.valid_id(id))
                    cout<<"id not valid\n";
                else{
                    pharmacy.update_price(id, price);
                }
                break;
            }
            case 3: {
                cout << "press 1 to show all meds, 2: injections, 3:pills\n";
                int option;
                cin >> option;
                if (option == 1)
                    pharmacy.show_all_meds();
                else if (option == 2)
                    pharmacy.show_injects();
                else if (option == 3)
                    pharmacy.show_pills();
                else
                    cout << "invaled number\n";
                break;
            }
            case 4: {
                cout << "enter med id\n";
                int id;
                cin >> id;
                pharmacy.show_med(id);
                break;
            }
            case 5: {
                cout << "enter med id\n";
                int id;
                cin >> id;
                pharmacy.delete_med(id);
                break;
            }
            case 0: {
                return;
            }
            default: {
                cout << "invalid number\n";
            }
        }
    }
}

