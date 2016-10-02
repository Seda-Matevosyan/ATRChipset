#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include <QString>
#include <QVariant>
#include <QMap>


//////////////////////////////////////////////////////////////////////////
//
// Class CConfiguration
//
class CConfiguration
{
public:
    // Default constructor
    CConfiguration();
    // Init Constructor
    CConfiguration(QString const& sName, QString const& sType, double nVersion);
    // Destructor
    ~CConfiguration();

    //
    // Interface
    //
    // Get/Set config information
    void setName(QString const& sName);
    QString getName() const;
    void setType(QString const& sType);
    QString getType() const;
    void setVersion(double nVersion);
    double getVersion() const;

    // Get/Set config parameters
    void setParameter(QString const& sKey, const QVariant& value);
    QVariant getParameter(QString const& sKey) const;

    int getParamCount() const;
    bool isEmpty() const;
    bool isContained(QString const& sKey) const;
    // Clear all parameters
    void clearParameters();
    // Clear config
    void reset();

    // Load configuration from xml file
    bool load(QString const& sPath);
    // Save configuration into xml file
    bool save(QString const& sPath) const;

private:
    //
    // members
    //

    // Information about config
    QString                     m_sName;
    QString                     m_sType;
    double                      m_nVersion;

    // Config parameters
    QMap<QString, QVariant>     m_mapParam;
};
//////////////////////////////////////////////////////////////////////////


#endif // CONFIGURATION_H












