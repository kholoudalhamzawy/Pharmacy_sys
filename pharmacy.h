#ifndef PHARMACY_PHARMACY_H
#define PHARMACY_PHARMACY_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class med{
protected:
    string name,type;
    int id;
    double price;
public:
    med();
    med(const string& name,const int& id,const double& price);

    void set_name(const string& name);
    const string& get_name() const;
    void set_id(const int& id);
    const int& get_id() const;
    void set_price(const double& price);
    const double& get_price() const;
    virtual const string& get_type()=0;
    virtual void show_dosage()const=0;
    virtual med* clone()const=0;
    virtual ~med();

};


class inject: public med{
protected:
    int num_of_injects;
    double size_of_needle;
public:
    inject();
    inject(const string& name,const int& id,const double& price,const int& num_of_injects,const double& size_of_needle);
    const string& get_type() override;

    void set_needle_size(const double& size);
    const double& get_needle_size()const ;
    void set_injection_times(const int& num);
    const int& get_injection_times() const;
    void show_dosage()const override;//
    med* clone() const override ;

    ~inject();

};

class pill: public med {
protected:
    int pills_num;
    double med_concentration;
public:
    pill();
    pill(const string &name, const int &id, const double &price, const int &pills_num, const double &cons);
    const string& get_type() override;
    const int &get_pills_num() const ;
    void set_pills_num(const int &num);
    const double &get_med_concentration() const;

    void set_med_concentration(const double &cons);

    void show_dosage() const override ;

    med *clone() const override ;

    ~pill();

};

class med_manager {
protected:
    vector<med *> all_meds;
public:
    med_manager();

    const vector<med*>& get_meds()const;
    bool valid_id(const int &id)const;
    void show_med(const int &id)const;
    void show_all_meds()const;
    void add_med( med &medicine);
    void delete_med( const int &id);
    void update_price(int id,double new_price);
    void show_injects()const;
    void show_pills()const;
    ~med_manager();

};

class my_system {
private:
    med_manager pharmacy;
public:
    void run();//
};

#endif //PHARMACY_PHARMACY_H
