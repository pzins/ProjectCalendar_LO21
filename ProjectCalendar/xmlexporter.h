#ifndef XMLEXPORTER_H
#define XMLEXPORTER_H
#include <QString>
#include <QFile>
#include <QXmlStreamReader>

/**
 * @class XmlExporter
 * @brief Interface permettant à une classe d'être exportée en XML
 */
class XmlExporter
{

public:
    XmlExporter();
    ~XmlExporter();
    /**
     * @brief save : sauvegarde en XML
     * @param f
     * @param contraintes
     */
    virtual void save(const QString& f, bool contraintes=false)const =0;
    virtual void load(const QString& f)=0;
};

#endif // XMLEXPORTER_H
