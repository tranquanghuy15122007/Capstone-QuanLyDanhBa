#pragma once
#include <iostream>
#include <string>
#include "date.h"
class Contact
{
private:
    string Name;
    string Phone;
    string Relationship; // quanhe
    Date Birthday;
    string Note;
public:
    Contact(string _name = "", string _phone = "", string _Relationship = "", Date _birth = Date(), string _note = "")
        : Name(_name), Phone(_phone), Relationship(_Relationship), Birthday(_birth), Note(_note)
    {

    }
    const string& GetName() const { return Name; }
    void SetName(const string& _name) { Name = _name; }
    const string& GetPhone() const { return Phone; }
    void SetPhone(const string& _phone) { Phone = _phone; }
    const string& GetRelationship() const { return Relationship; }
    void SetRelationship(const string& _Relationship) { Relationship = _Relationship; }
    const string& GetNote() const { return Note; }
    void SetNote(const string& _note) { Note = _note; }
    const Date& GetBirthday() const { return Birthday; }
    void SetBirthday(const Date& _birth) { Birthday = _birth; }
};

