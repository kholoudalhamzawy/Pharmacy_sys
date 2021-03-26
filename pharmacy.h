#ifndef PHARMACY_PHARMACY_H
#define PHARMACY_PHARMACY_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Dosage_behavior{
public:
    Dosage_behavior();
    virtual void show_dosage() const;
    virtual void set_dosage();
    ~Dosage_behavior();
};

class Inject_dosage : public Dosage_behavior{
protected:
    int num_of_injects;
    double size_of_needle;
public:
    Inject_dosage();
    void show_dosage()const override;
    void set_dosage() override;
    ~Inject_dosage();
};

class Pill_dosage: public Dosage_behavior{
protected:
    int pills_num;
    double med_concentration;
public:
    Pill_dosage();
    void show_dosage()const override;
    void set_dosage() override;
    ~Pill_dosage();
};

class Preservation_behavior{
public:
    virtual void show_preservation () const;
};

class Moderate_preservation: public Preservation_behavior{
public:
    void show_preservation  () const override;
};

class Cold_preservation: public Preservation_behavior{
public:
    void show_preservation() const override;
};

class med{
protected:
    int id;double price;
    Dosage_behavior* dosageBehavior;
    Preservation_behavior* preservationBehavior;
public:
    med();
    med(const int& id,const double& price);
    void set_id(const int& id);
    const int &get_id() const;
    void set_price(const double& price);
    const double& get_price() const;
    virtual void show_type()const;
    void set_dosage_behavior(Dosage_behavior* db);
    void set_preservation_behavior(Preservation_behavior* pb);
    void show_preservation() const;
    void show_dosage()const;
    void set_dosage();
    ~med();
    
};

class Vitamins: public med {
protected:
    Pill_dosage *pd;
    Moderate_preservation *mp;
public:
    Vitamins(const int &id, const double &price);
    void show_type() const override;
    ~Vitamins();
};

class Sedatives: public med{
protected:
    Inject_dosage* Id;
    Cold_preservation* cp;
public:
    Sedatives(const int& id,const double& price);
    void show_type()const override;
    ~Sedatives();
};

class med_manager{
protected:
    vector<med *> all_meds;
public:
    med_manager();
    bool valid_id(const int &id)const;
    void delete_med( const int &id);
    void add_med( med *medicine);
    void update_price(int id,double new_price);
    void show_med(const int &id)const;
    void show_all_meds()const;
    void change_preservation_behavior(int id,Preservation_behavior *pb);
    void change_dosage_behavior(int id,Dosage_behavior *db);
    void update_dosage(int id);
    ~med_manager();
};

class my_system {
private:
    med_manager pharmacy;
public:
    void run();
};

#endif //PHARMACY_PHARMACY_H
