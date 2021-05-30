#ifndef LINEPOINTMODEL_H
#define LINEPOINTMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>
#include <QList>

class LinePointModel : public QAbstractListModel
{
    Q_OBJECT

    struct LinePoint {
        double x{};
        double y{};
        double cp1x{};
        double cp1y{};
        double cp2x{};
        double cp2y{};
        bool hasCp1{false};
        bool hasCp2{false};
    };

    QList<LinePoint> m_points;

public:
    enum LinePointRole {
        XRole = Qt::UserRole,
        YRole,
        Cp1xRole,
        Cp1yRole,
        Cp2xRole,
        Cp2yRole,
        HasCp1Role,
        HasCp2Role
    };
    Q_ENUM(LinePointRole)
    explicit LinePointModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;
    void fromJson(QJsonArray array);

    QString svgPath() const;
};

#endif // LINEPOINTMODEL_H
