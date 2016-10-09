

#ifndef DATA_SELECTION_INTERFACES_H
#define DATA_SELECTION_INTERFACES_H


#include <QString>
#include <QVector>
#include <QVariant>
#include <QVariantList>
#include <QSharedPointer>



enum EFieldType
{
    Int				= 0x01,
    String			= 0x02,
    DateTime		= 0x03,
};


typedef QString Field;
typedef QStringList FieldList;

struct SFieldInfo
{
	Field			FieldID;
	QString			sName;
	EFieldType		eType;
};


////////////////////////////////////////////////////////////////
//
// IDataDirectory Interface
//
class IDataDirectory
{
public:
	// Get field list of all field types
	virtual FieldList getFields() const = 0;
	// Get values as QVariant of field
	virtual QVariantList getFieldValues() const = 0;
};
////////////////////////////////////////////////////////////////


enum ESelectionPatten
{
	// Default selection (all Field valus are selected)
	All					= 0x01,
	// Coustom selection
	ValueSelection		= 0x02
};

////////////////////////////////////////////////////////////////
//
// class CSelection
//
class CSelection
{
public:
	struct SFieldValueSelection
	{	
		ESelectionPatten    	eSelectionType;
		QString					sPattern;
    	QVariantList        	arrSelectedValues;
	};

private:
	QVector<SFieldValueSelection>		vecSelection;
};
////////////////////////////////////////////////////////////////


// This interface provide data which was selected and loaded
class IFieldCollection;
typedef QSharedPointer<IFieldCollection> IFieldCollectionPtr;

////////////////////////////////////////////////////////////////
//
// Interfaces IDataProvider
//
class IDataProvider
{
public:
	// Set field data selection
	virtual void setSelection(CSelection const& oSelection) = 0;
	// Get Data corresponding of selection
	virtual IFieldCollectionPtr GetData(FieldList const& lstField) = 0;
};
////////////////////////////////////////////////////////////////


#endif // DATA_SELECTION_INTERFACES_H
