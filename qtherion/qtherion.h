#ifndef QTHERION_H
#define QTHERION_H

#include <QObject>
#include <QUrl>

#include "scrapmodel.h"

// TODO move control points in sync with line point
// TODO scaling
// TODO graphics config dialog
// TODO selection models (e.g. cps visible only on select)

class QTherion : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(ScrapModel* scrapModel READ scrapModel WRITE setScrapModel NOTIFY scrapModelChanged)
    Q_PROPERTY(int canvasWidth READ canvasWidth WRITE setCanvasWidth NOTIFY canvasWidthChanged)
    Q_PROPERTY(int canvasHeight READ canvasHeight WRITE setCanvasHeight NOTIFY canvasHeightChanged)

    ScrapModel *m_scrapModel;

    QString m_projectName{"QTherion"};

    int m_canvasWidth{0};

    int m_canvasHeight{0};

public:
    explicit QTherion(QObject *parent = nullptr);

    QString projectName() const
    {
        return m_projectName;
    }

    ScrapModel* scrapModel() const
    {
        return m_scrapModel;
    }

    int canvasWidth() const
    {
        return m_canvasWidth;
    }

    int canvasHeight() const
    {
        return m_canvasHeight;
    }

public slots:
    void openProject(QUrl url);
    void processIndexFile(QString filename);
    void processDrawingFile(QString filename);

    void setProjectName(QString projectName)
    {
        if (m_projectName == projectName)
            return;

        m_projectName = projectName;
        emit projectNameChanged(m_projectName);
    }

    void setScrapModel(ScrapModel* scrapModel)
    {
        if (m_scrapModel == scrapModel)
            return;

        m_scrapModel = scrapModel;
        emit scrapModelChanged(m_scrapModel);
    }

    void setCanvasWidth(int canvasWidth)
    {
        if (m_canvasWidth == canvasWidth)
            return;

        m_canvasWidth = canvasWidth;
        emit canvasWidthChanged(m_canvasWidth);
    }

    void setCanvasHeight(int canvasHeight)
    {
        if (m_canvasHeight == canvasHeight)
            return;

        m_canvasHeight = canvasHeight;
        emit canvasHeightChanged(m_canvasHeight);
    }

signals:
    void projectNameChanged(QString projectName);
    void scrapModelChanged(ScrapModel* scrapModel);
    void canvasWidthChanged(int canvasWidth);
    void canvasHeightChanged(int canvasHeight);
};

#endif // QTHERION_H
