#include "pharmacy.h"
Dosage_behavior::Dosage_behavior(/*Dosage_behavior* db*/){//3aiza thote fe elconstructor object bei inherate mn el constructor da aslan ? enty 3abyta ??
}
void Dosage_behavior::show_dosage() const {} //canttttt make them unimplemented, haiza3a2lek >:))
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
//no writing override or virtual or shit
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


// cant make em virtual, da 3ade ?
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
void med::set_dosage_behavior(Dosage_behavior* db){
    this->dosageBehavior=db;
}
void med::set_preservation_behavior(Preservation_behavior* pb){
    this->preservationBehavior=pb;
//        pb= nullptr; //will this prevent the mimory leak? // did it in main
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
    dosageBehavior= nullptr;
    preservationBehavior= nullptr;
}


Vitamins::Vitamins(const int& id,const double& price):med(id,price){
    pd=new Pill_dosage();
    mp=new Moderate_preservation();
    set_dosage_behavior(pd);
    set_preservation_behavior(mp);

}
void Vitamins::show_type()const{
    cout<<"vitamin\n";
}
Vitamins::~Vitamins(){
    pd= nullptr;
    mp = nullptr;
}


Sedatives::Sedatives(const int& id,const double& price):med(id,price){
    Id= new Inject_dosage();
    cp= new Cold_preservation();
    set_dosage_behavior(Id);
    set_preservation_behavior(cp);
}
void Sedatives::show_type()const{
    cout<<"sedative\n";
}
Sedatives::~Sedatives(){
    Id= nullptr;
    cp= nullptr;
}

med_manager::med_manager(){}
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
            delete *it;
            all_meds.erase(it);
            ///wtf ? told me libc++abi.dylib: Pure virtual function called! w m4a w sabny !! :(
            //delete *it;
            cout<<"med was deleted\n";
            return;}
        it++;
    }
    cout<<"med not found\n";
    return;

}
void med_manager::add_med( med *medicine){
    all_meds.push_back(medicine);
    cout<<"med was inserted\n";
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
        for (const auto element:all_meds) {
            cout << "\t# id: " << element->get_id()<<"\n";
            this->show_med(element->get_id());
        }
    return;
}
void med_manager::change_preservation_behavior(int id,Preservation_behavior *pb){
    if (!valid_id(id))
        cout<<"med not found\n";
    else{
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                medecine->set_preservation_behavior(pb);
                cout<<"behavior was updated\n";
                return;
            }
        }
    }
    return;

}
void med_manager::change_dosage_behavior(int id,Dosage_behavior *db){
    if (!valid_id(id))
        cout<<"med not found\n";
    else{
        for (const auto &medecine:all_meds){
            if(medecine->get_id()==id){
                medecine->set_dosage_behavior(db);
                cout<<"Dosage was updated\n";
                return;
            }
        }
    }
    return;

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

med_manager::~med_manager(){
    for ( auto &element:all_meds) {
        delete element;
        element= nullptr;
    }
    all_meds.clear();
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
                    cout << "enter a type num from 1 to 2\n1: vitamin\t2: Sedative\t";
                    cin >> type;
                    if (type == 1) {
                        valid=1;
                        Vitamins* med=new Vitamins(id, price);
                        pharmacy.add_med(med);
                    } else if (type == 2) {
                        valid=1;
                        Sedatives* med=new Sedatives(id,price);
                        pharmacy.add_med(med);
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
                            Inject_dosage* dosage=new Inject_dosage();
                            pharmacy.change_dosage_behavior(id,dosage);
                            dosage= nullptr;
                        }
                        else if(option==2){
                            Pill_dosage* dosage=new Pill_dosage();
                            pharmacy.change_dosage_behavior(id,dosage);
                            dosage= nullptr;
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
                            Moderate_preservation* preservation=new Moderate_preservation();
                            pharmacy.change_preservation_behavior(id,preservation);
                            preservation= nullptr;

                        }
                        else if(option==2){
                            Cold_preservation* preservation=new Cold_preservation();
                            pharmacy.change_preservation_behavior(id,preservation);
                            preservation= nullptr;
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