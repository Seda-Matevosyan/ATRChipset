

#ifndef DATA_SELECTION_INTERFACES_H
#define DATA_SELECTION_INTERFACES_H

#include <QVector>

// Forword declaration
class QString;
class QVariantList;


namespace data
{


enum EFieldType
{
    Int				= 0x01,
    String			= 0x02,
    DateTime		= 0x03,
};


struct SField
{
    QString         m_sName;
    EFieldType      m_eType;
};


////////////////////////////////////////////////////////////////
//
// IDataDirectory Interface
//
class IDataDirectory
{
public:
    typedef QVector<SField>  t_filedArray;

	virtual t_filedArray getFields() const = 0;
	virtual QVariantList getFieldValues() const = 0;
};
////////////////////////////////////////////////////////////////


enum ESelectionPatten
{
    valueSelection			= 0x01,
};

////////////////////////////////////////////////////////////////
//
// SFieldValueSelection structure
//
struct SFieldValueSelection : public SFiled
{
	ESelectionPatten    eSelectionType;
	QString				sPattern;
    QVariantList        arrSelectedValues;
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//
// SSelection structure
//
struct SSelection
{
	QVector<SFieldValueSelection>		vecSelection;
};
////////////////////////////////////////////////////////////////


} // data namespace


#endif // DATA_SELECTION_INTERFACES_H
