

#include <configuration.h>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>


CConfiguration::CConfiguration()
    : m_sName(),
      m_sType(),
      m_nVersion(0.0),
      m_mapParam()
{

}


CConfiguration::CConfiguration(QString const& sName, QString const& sType, double nVersion)
    : m_sName(sName),
      m_sType(sType),
      m_nVersion(nVersion),
      m_mapParam()
{

}


CConfiguration::~CConfiguration()
{

}


void CConfiguration::setName(QString const& sName)
{
    m_sName = sName;
}


QString CConfiguration::getName() const
{
    return m_sName;
}


void CConfiguration::setType(QString const& sType)
{
    m_sType = sType;
}


QString CConfiguration::getType() const
{
    return m_sType;
}


void CConfiguration::setVersion(double nVersion)
{
    m_nVersion = nVersion;
}


double CConfiguration::getVersion() const
{
    return m_nVersion;
}


void CConfiguration::setParameter(QString const& sKey, QVariant const& value)
{
    m_mapParam[sKey] = value;
}


QVariant CConfiguration::getParameter(QString const& sKey) const
{
    auto it = m_mapParam.find(sKey);
    if (it != m_mapParam.end())
        return it.value();
    return QVariant();
}


int CConfiguration::getParamCount() const
{
    return m_mapParam.count();
}


bool CConfiguration::isEmpty() const
{
    return m_mapParam.isEmpty();
}


bool CConfiguration::isContained(QString const& sKey) const
{
    if (m_mapParam.find(sKey) != m_mapParam.end())
        return true;
    return false;
}


void CConfiguration::reset()
{
    m_sName.clear();
    m_sType.clear();
    m_nVersion = 0.0;
    m_mapParam.clear();
}


void CConfiguration::clearParameters()
{
    m_mapParam.clear();
}


bool CConfiguration::load(QString const& sPath)
{
    QFile xmlConfig(sPath);
    // Open file only for reading
    if (xmlConfig.open(QFile::ReadOnly))
    {
        // Creat xml reader
        QXmlStreamReader xmlReader(&xmlConfig);
        while(!xmlReader.atEnd())
        {
            xmlReader.readNext();
            if (xmlReader.isStartDocument())
               continue;

            if (xmlReader.isStartElement() && xmlReader.name() == "Configuration")
            {   // Read config information
                QXmlStreamAttributes oAttr = xmlReader.attributes();
                m_sName = oAttr.value("Name").toString();
                m_sType = oAttr.value("Type").toString();
                m_nVersion = oAttr.value("Version").toDouble();

            }
            else if (xmlReader.isStartElement() && xmlReader.name() == "Parameters")
            {   // Read config parameters
                xmlReader.readNext();
                while(!xmlReader.atEnd())
                {
                    QString sKey = xmlReader.name().toString();
                    QString sType = xmlReader.attributes().value("ParamType").toString();
                    QString sValue = xmlReader.readElementText();
                    QVariant value;
                    if (sKey.isEmpty() || sType.isEmpty() && sValue.isEmpty())
                    {
                        xmlReader.readNext();
                        continue;
                    }

                    if (sType == "bool")
                    {
                        if (sValue == "true")
                            value = QVariant(true);
                        else
                            value = QVariant(false);
                        m_mapParam.insert(sKey, value);
                    }
                    else if (sType == "int")
                    {
                        value = QVariant(sValue.toInt());
                        m_mapParam.insert(sKey, value);
                    }
                    else if (sType == "double")
                    {
                        value = QVariant(sValue.toDouble());
                        m_mapParam.insert(sKey, value);
                    }
                    else if (sType == "QString")
                    {
                        value = QVariant(sValue);
                        m_mapParam.insert(sKey, value);
                    }
                    xmlReader.readNext();
                }
            }
        }

        xmlReader.clear();
        xmlConfig.close();

        return true;
    }

    return false;
}


bool CConfiguration::save(QString const& sPath) const
{
    // Create File
    QFile xmlConfig(sPath);
    // Open file only for writing
    if (xmlConfig.open(QFile::WriteOnly))
    {
        // Create xml write
        QXmlStreamWriter xmlWriter(&xmlConfig);
        xmlWriter.setAutoFormatting(true);

        // Write config information
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Configuration");
        xmlWriter.writeAttribute("Name", m_sName);
        xmlWriter.writeAttribute("Type", m_sType);
        xmlWriter.writeAttribute("Version", QString::number(m_nVersion));

        // Write parameters
        xmlWriter.writeStartElement("Parameters");
        for (auto it = m_mapParam.begin(); it != m_mapParam.end(); ++it)
        {
            xmlWriter.writeStartElement(it.key());
            xmlWriter.writeAttribute("ParamType", it.value().typeName());
            xmlWriter.writeCharacters(it.value().toString());
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        xmlConfig.close();

        return true;
    }
    return false;
}



































