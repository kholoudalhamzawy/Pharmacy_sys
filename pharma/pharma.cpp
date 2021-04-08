#include "pharma.h"
Dosage_behavior::Dosage_behavior(){}
void Dosage_behavior::show_dosage() const {}
void Dosage_behavior:: set_dosage(){}
Dosage_behavior::~Dosage_behavior(){}

Inject_dosage::Inject_dosage():Dosage_behavior(){
    this->set_dosage();
}
void Inject_dosage::show_dosage()const{
    cout<<num_of_injects<<" injects a day with a needle of size "<<size_of_needle<<" ml\n";
}
void Inject_dosage::set_dosage() {
    int num=0;double size=0;
    cout<<"enter num of injects and needle size\n";
    cin>>num>>size;
    this->num_of_injects=num;
    this->size_of_needle=size;
}
Inject_dosage::~Inject_dosage(){}

Pill_dosage::Pill_dosage():Dosage_behavior(){
    this->set_dosage();
}
void Pill_dosage:: show_dosage()const  {
    cout << pills_num << " pills a day of concentration " << med_concentration << " ml\n";
}
void Pill_dosage:: set_dosage() {
    double cons=0;int num=0;
    cout<<"enter num of pills and med concentration\n";
    cin>>num>>cons;
    this->pills_num = num;
    this->med_concentration = cons;
}
Pill_dosage::~Pill_dosage(){}


void Preservation_behavior::show_preservation () const{}
void Moderate_preservation::show_preservation  () const {
    cout<<"keep in moderate temp\n";
}
void Cold_preservation::show_preservation() const {
    cout<<"keep in low temp\n";
}

med::med(){}
med::med(const int& id,const double& price):id(id),price(price){}
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
void med::show_type()const {}
void med::set_dosage_behavior(unique_ptr<Dosage_behavior> db){
    this->dosageBehavior= move(db);
}
void med::set_preservation_behavior(unique_ptr<Preservation_behavior> pb){
    this->preservationBehavior= move(pb);
}
void med::show_preservation()const{
    preservationBehavior->show_preservation();
}
void med::show_dosage()const{
    dosageBehavior->show_dosage();
}
void med::set_dosage(){
    dosageBehavior->set_dosage();
}
med::~med(){
}


Vitamins_cairo::Vitamins_cairo(const int& id,const double& price):med(id,price){
// two ways
    Cold_Preservation=make_unique<Cold_preservation>();
    set_dosage_behavior(make_unique<Inject_dosage>());
    set_preservation_behavior(move(Cold_Preservation));

}
void Vitamins_cairo::show_type()const{
    cout<<"vitamin\n";
}
Vitamins_cairo::~Vitamins_cairo(){
}

Vitamins_alex::Vitamins_alex(const int& id,const double& price):med(id,price){
    set_dosage_behavior(make_unique<Pill_dosage>());
    set_preservation_behavior(make_unique<Moderate_preservation>());

}
void Vitamins_alex::show_type()const{
    cout<<"vitamin\n";
}
Vitamins_alex::~Vitamins_alex(){
}


Sedatives_cairo::Sedatives_cairo(const int& id,const double& price):med(id,price){
    set_dosage_behavior(make_unique<Inject_dosage>());
    set_preservation_behavior(make_unique<Cold_preservation>());

}
void Sedatives_cairo::show_type()const{
    cout<<"sedative\n";
}
Sedatives_cairo::~Sedatives_cairo(){
}
Sedatives_alex::Sedatives_alex(const int &id, const double &price):med(id,price) {

    set_dosage_behavior(make_unique<Pill_dosage>());
    set_preservation_behavior(make_unique<Moderate_preservation>());
}
void Sedatives_alex::show_type()const{
    cout<<"sedative\n";
}
Sedatives_alex::~Sedatives_alex(){
}


med_manager::med_manager(){
}
bool med_manager::valid_id(const int &id)const{
    for (const auto &element:all_meds) {
        if (element->get_id() == id) {
            return true;
        }
    }
    return false;
}
void med_manager::delete_med( const int &id){
    auto it = all_meds.begin();
    while (it != all_meds.end()){
        if ((*it)->get_id() == id) {
            (*it).reset();
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
void med_manager::show_med(const int &id)const{
    if (all_meds.empty()){
        cout << "no meds\n";
        return;}
    else
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                cout<<"price: "<<medecine->get_price()<<" LE \t type: ";
                medecine->show_type();
                cout<<"dosage: ";medecine->show_dosage();
                cout<<"preservation: ";medecine->show_preservation();
                return;}

        }
    cout<<"med not found\n";
    return;

}
void med_manager::show_all_meds()const{
    if (all_meds.empty())
        cout << "no meds\n";
    else
        for (const auto &element:all_meds) {
            cout << "\t# id: " << element->get_id()<<"\n";
            this->show_med(element->get_id());
        }
    return;
}
bool med_manager::change_preservation_behavior(int id,unique_ptr<Preservation_behavior> pb){
    if (!valid_id(id))
        cout<<"med not found\n";
    else{
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                medecine->set_preservation_behavior(move(pb));
                cout<<"behavior was updated\n";
                return 1;
            }
        }
    }
    return 0;

}
bool med_manager::change_dosage_behavior(int id,unique_ptr<Dosage_behavior> db){
    if (!valid_id(id))
        cout<<"med not found\n";
    else{
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                medecine->set_dosage_behavior(move(db));
                cout<<"Dosage was updated\n";
                return 1;
            }
        }
    }
    return 0;

}
unique_ptr<med> med_factory::create_med(string type,int id,double price){
}

med_factory::med_factory(){
}
med_factory::~med_factory(){
}
void med_manager::update_dosage(int id){
    if (!valid_id(id))
        cout<<"med not found\n";
    else{
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                medecine->set_dosage();
                cout<<"Dosage was updated\n";
                return;
            }
        }
    }
    return;

}
void med_manager::set_factory(string type){
    if (type=="alex"){
        this->factory=make_unique<alex_factory>();
    }
    else if(type=="cairo"){
        this->factory=make_unique<cairo_factory>();
    }
}
vector<unique_ptr<med>>::size_type med_manager::get_meds_num(){
    return all_meds.size();
}
unique_ptr<med> med_manager::get_med(int id){
    if(valid_id(id))
        for (auto &medecine:all_meds)
            if (medecine->get_id() == id) {
                return move(medecine);
            }
    return nullptr;
}
void med_manager::add_med(string type,int id,double price){
    all_meds.push_back(factory->create_med(type,id,price));
    cout<<"med was inserted\n";
}
med_manager::~med_manager(){
}
unique_ptr<med> alex_factory::create_med(string type,int id,double price){
    if (type=="Vitamins"){
        medecation=make_unique<Vitamins_cairo>(id,price);
    }
    else if(type=="Sedatives"){
        medecation=make_unique<Sedatives_cairo>(id,price);
    }
    return move(medecation);
}

alex_factory::~alex_factory(){
}
unique_ptr<med> cairo_factory::create_med(string type,int id,double price){
    if (type=="Vitamins"){
        medecation=make_unique<Vitamins_cairo>(id,price);
    }
    else if(type=="Sedatives"){
        medecation=make_unique<Sedatives_cairo>(id,price);
    }
    return move(medecation);
}

void my_system ::run() {
    while(true){
        cout<< "enter from 0 to 6:\n1: insert new med\n2: update price\n3: update behavior\n4: show meds\n5: search\n6: delete\n0: terminate\n";
        int option;
        cin >> option;
        switch (option) {
            case 1: {
                cout << "enter med price and id\n";
                double price;
                int id;
                int type;
                cin >> price >> id;
                while(pharmacy.valid_id(id)){
                    cout<<"already existing id, enter another one\n";
                    cin>>id;
                }
                bool valid=0;
                while (!valid){
                    cout<<"enter type of pharmacy, cairo or alex\n";
                    string pharma_type;cin>>pharma_type;
                    pharmacy.set_factory(pharma_type);
                    cout << "enter a type num from 1 to 2\n1: Vitamin\t2: Sedative\t";
                    cin >> type;
                    if (type == 1) {
                        valid=1;
                        pharmacy.add_med("Vitamins",id,price);
                    } else if (type == 2) {
                        valid=1;
                        pharmacy.add_med("Sedatives",id,price);
                    } else{
                        cout << "invalid number\n";
                    }
                }
                break;
            }
            case 2: {
                cout << "enter the med id and the new price\n";
                int id; double price;
                cin>>id>>price;
                if(!pharmacy.valid_id(id))
                    cout<<"id not valid\n";
                else
                    pharmacy.update_price(id, price);

                break;
            }
            case 3:{
                cout << "enter the med id\n";
                int id;cin>>id;
                if(!pharmacy.valid_id(id))
                    cout<<"id not valid\n";
                else{
                    cout<<"press 1 to change dosage behavior, 2 to change preservation behavior\n";
                    int option;cin>>option;
                    if (option==1){
                        cout<<"press 1 to change to injects, 2 to pills, 3 to update dosage\n";
                        cin>>option;
                        if (option==1){
                            pharmacy.change_dosage_behavior(id,make_unique<Inject_dosage>());
                        }
                        else if(option==2){
                            pharmacy.change_dosage_behavior(id,make_unique<Pill_dosage>());
                        }
                        else if(option==3){
                            pharmacy.update_dosage(id);
                        }
                        else
                            cout<<"invalid number\n";

                    }
                    else if(option==2){
                        cout<<"press 1 to change to moderate, 2 to cold\n";
                        cin>>option;
                        if (option==1){
                            pharmacy.change_preservation_behavior(id,make_unique<Moderate_preservation>());

                        }
                        else if(option==2){
                            pharmacy.change_preservation_behavior(id,make_unique<Cold_preservation>());
                        }
                        else
                            cout<<"invalid number\n";
                    }
                    else
                        cout<<"invalid number\n";
                }
                break;


            }
            case 4: {
                pharmacy.show_all_meds();
                break;
            }
            case 5: {
                cout << "enter med id\n";
                int id;
                cin >> id;
                pharmacy.show_med(id);
                break;
            }
            case 6: {
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
