

#ifndef DATA_SELECTION_INTERFACES_H
#define DATA_SELECTION_INTERFACES_H

#include <QVector>
#include <QSharedPointer>

// Forword declaration
class QString;
class QVariantList;


namespace data
{


enum EFieldType
{
    Int				= 0x01,
    String			= 0x02,
    DateTime			= 0x03,
};


typedef QString Field;
typedef QStringList FieldList;

struct SFieldInfo
{
	Field		fieldID;
	QString		sName;
	EFieldType	eType;
}


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
	// Default selection (all Field's valus are selected)
	Default		0x01;
	// Coustom selection
	Custom		0x02;
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
		QString			sPattern;
    		QVariantList        	arrSelectedValues;
	};

privte:
	QVector<SFieldValueSelection>		vecSelection;
};
////////////////////////////////////////////////////////////////

// This interface provide data which was selected and loaded
class IDataContainer;
typedef QSharedPointer<IDataContainer*> IDataContainerPtr;

////////////////////////////////////////////////////////////////
//
// Interfaces IDataProvider
//
class IDataProvider
{
privte:
	// Set field's data selection
	void setSelection(CSelection const& oSelection) = 0;
	// Get Data corresponding of selection
	IDataContainer GetData(FieldList const& oFiledList) = 0;
};
////////////////////////////////////////////////////////////////


} // data namespace


#endif // DATA_SELECTION_INTERFACES_H
