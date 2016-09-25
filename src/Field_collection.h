#ifndef __IFIELDCOLLECTION__
#define __IFIELDCOLLECTION__

class QVariant;
class QString;

/***
 *
 * Declaration of interfaces `
 * IVector
 * IIntVector    (inherited from IVector)
 * IStringVector (inherited From IVector)
 *
 ***/
class IVector
{
public:
    virtual  QVariant get_at (int index) = 0;
    virtual  int count() = 0;
};

class IIntVector : public IVector
{
public:
    int at(int index);
    int count();
};

class IStringVector: public IVector
{
public:
    QString at(int index);
    int count();
};

/***
 *
 * Declaration of interfaces `
 * IFieldData
 * IFieldCollection
 *
 ***/
class IFieldData
{
public:
    //Returns count of rows in field
    virtual int get_count() = 0;
    //Returns field name
    virtual Field get_field() = 0;
    //Returns element by index
    virtual QVariant get_at() = 0;
    //Returns whole field in vector<int>
    virtual IIntVector get_int_vector() = 0;
    //Returns whole field in vector<string>
    virtual IStringVector get_string_vector() = 0;
};

class IFieldCollection
{
public:
    //Returns field from collection by name
    virtual IFieldData get_by_field(Field field) = 0; // i suggest rename this function name to more descriptive name -> get_filed_data
    //Returns count of fields in collection
    virtual int get_count () = 0;
    //Returns field by index in collection
    virtual Field get_field(int index) = 0;
    //Returns index of field in collection
    virtual Field get_field_index(int index) = 0;
};

#endif // __IFIELDCOLLECTION__
