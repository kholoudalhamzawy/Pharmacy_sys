//
// Created by KH on 4/8/21.
//

#ifndef PHARMACY_PHARMA_H
#define PHARMACY_PHARMA_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstddef>
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
    unique_ptr<Dosage_behavior> dosageBehavior;
    unique_ptr<Preservation_behavior> preservationBehavior;
public:
    med();
    med(const int& id,const double& price);
    void set_id(const int& id);
    const int &get_id() const;
    void set_price(const double& price);
    const double& get_price() const;
    virtual void show_type()const;
    void set_dosage_behavior(unique_ptr<Dosage_behavior> db);
    void set_preservation_behavior(unique_ptr<Preservation_behavior> pb);
    void show_preservation() const;
    void show_dosage()const;
    void set_dosage();
    ~med();

};

class Vitamins_cairo: public med {
protected:
    unique_ptr<Inject_dosage> Inject_Dosage;
    unique_ptr<Cold_preservation> Cold_Preservation;
public:
    Vitamins_cairo(const int &id, const double &price);
    void show_type() const override;
    ~Vitamins_cairo();
};

class Vitamins_alex: public med {
protected:
    unique_ptr<Pill_dosage> Pill_Dosage;
    unique_ptr<Moderate_preservation> Moderate_Preservation;
public:
    Vitamins_alex(const int &id, const double &price);
    void show_type() const override;
    ~Vitamins_alex();
};

class Sedatives_cairo: public med{
protected:
    unique_ptr<Inject_dosage> Inject_Dosage;
    unique_ptr<Cold_preservation> Cold_Preservation;
public:
    Sedatives_cairo(const int& id,const double& price);
    void show_type()const override;
    ~Sedatives_cairo();
};

class Sedatives_alex: public med{
protected:
    unique_ptr<Pill_dosage> Pill_Dosage;
    unique_ptr<Moderate_preservation> Moderate_Preservation;
public:
    Sedatives_alex(const int& id,const double& price);
    void show_type()const override;
    ~Sedatives_alex();
};

class med_factory{
protected:
    unique_ptr<med> medecation;
public:
    med_factory();
    virtual unique_ptr<med> create_med(string type,int id,double price); //virtual but written with practices, cant be pure???????
    ~med_factory();
};

class alex_factory: public med_factory{
public:
    unique_ptr<med> create_med(string type,int id,double price)override;
    ~alex_factory();
};

class cairo_factory: public med_factory{
public:
    unique_ptr<med> create_med(string type,int id,double price)override;
};

class med_manager{
protected:
    unique_ptr<med_factory> factory;
    vector<unique_ptr<med>> all_meds;
public:
    med_manager();
    void set_factory(string type);
    bool valid_id(const int &id)const;
    void delete_med( const int &id);
    void add_med(string type,int id,double price);
    void update_price(int id,double new_price);
    void show_med(const int &id)const;
    void show_all_meds()const;
    bool change_preservation_behavior(int id,unique_ptr<Preservation_behavior>pb);
    bool change_dosage_behavior(int id,unique_ptr<Dosage_behavior>db);
    void update_dosage(int id);
    vector<unique_ptr<med>>::size_type get_meds_num();
    unique_ptr<med> get_med(int id);



    ~med_manager();
};

class my_system {
private:
    med_manager pharmacy;

public:
    void run();
};

#endif //PHARMACY_PHARMA_H
