#include "linepointmodel.h"
#include <QJsonObject>

LinePointModel::LinePointModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int LinePointModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_points.size();
}

QVariant LinePointModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount()) {
        return {};
    }

    const LinePoint &point = m_points[index.row()];

    switch (static_cast<LinePointRole>(role)) {
    case XRole:
        return point.x;
    case YRole:
        return point.y;
    case Cp1xRole:
        return point.cp1x;
    case Cp1yRole:
        return point.cp1y;
    case Cp2xRole:
        return point.cp2x;
    case Cp2yRole:
        return point.cp2y;
    case HasCp1Role:
        return point.hasCp1;
    case HasCp2Role:
        return point.hasCp2;
    }

    return {};
}

bool LinePointModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount()) {
        return false;
    }

    LinePoint &point = m_points[index.row()];

    switch (static_cast<LinePointRole>(role)) {
    case LinePointModel::XRole: {
        double newX = value.toDouble();
        if (point.x != newX) {
            point.x = newX;
            emit dataChanged(index, index, {XRole});
            return true;
        }
        break;
    }
    case LinePointModel::YRole: {
        double newY = value.toDouble();
        if (point.y != newY) {
            point.y = newY;
            emit dataChanged(index, index, {YRole});
            return true;
        }
        break;
    }
    case LinePointModel::Cp1xRole: {
        double newCp1x = value.toDouble();
        if (point.cp1x != newCp1x) {
            point.cp1x = newCp1x;
            emit dataChanged(index, index, {Cp1xRole});
            return true;
        }
        break;
    }
    case LinePointModel::Cp1yRole: {
        double newCp1y = value.toDouble();
        if (point.cp1y != newCp1y) {
            point.cp1y = newCp1y;
            emit dataChanged(index, index, {Cp1yRole});
            return true;
        }
        break;
    }
    case LinePointModel::Cp2xRole: {
        double newCp2x = value.toDouble();
        if (point.cp2x != newCp2x) {
            point.cp2x = newCp2x;
            emit dataChanged(index, index, {Cp2xRole});
            return true;
        }
        break;
    }
    case LinePointModel::Cp2yRole: {
        double newCp2y = value.toDouble();
        if (point.cp2y != newCp2y) {
            point.cp2y = newCp2y;
            emit dataChanged(index, index, {Cp2yRole});
            return true;
        }
        break;
    }
    case LinePointModel::HasCp1Role: {
        bool newHasCp1 = value.toDouble();
        if (point.hasCp1 != newHasCp1) {
            point.hasCp1 = newHasCp1;
            emit dataChanged(index, index, {HasCp1Role});
            return true;
        }
        break;
    }
    case LinePointModel::HasCp2Role: {
        bool newHasCp2 = value.toDouble();
        if (point.hasCp2 != newHasCp2) {
            point.hasCp2 = newHasCp2;
            emit dataChanged(index, index, {HasCp2Role});
            return true;
        }
        break;
    }
    }
    return false;
}

QHash<int, QByteArray> LinePointModel::roleNames() const {
    return {
        {XRole, "xRole"},
        {YRole, "yRole"},
        {Cp1xRole, "cp1xRole"},
        {Cp1yRole, "cp1yRole"},
        {Cp2xRole, "cp2xRole"},
        {Cp2yRole, "cp2yRole"},
        {HasCp1Role, "hasCp1Role"},
        {HasCp2Role, "hasCp2Role"}
    };
}

void LinePointModel::fromJson(QJsonArray array) {
    beginResetModel();
    m_points.clear();
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject current = array[i].toObject();
        QJsonObject next = i+1 < array.size() ? array[i+1].toObject() : QJsonObject{};
        LinePoint linePoint;
        QJsonArray point = current["point"].toArray();
        linePoint.x = point[0].toDouble();
        linePoint.y = point[1].toDouble();
        if (next.contains("cp1")) {
            QJsonArray cp1 = next["cp1"].toArray();
            linePoint.cp1x = cp1[0].toDouble();
            linePoint.cp1y = cp1[1].toDouble();
            linePoint.hasCp1 = true;
        }
        if (current.contains("cp2")) {
            QJsonArray cp2 = current["cp2"].toArray();
            linePoint.cp2x = cp2[0].toDouble();
            linePoint.cp2y = cp2[1].toDouble();
            linePoint.hasCp2 = true;
        }
        m_points << linePoint;
    }
    endResetModel();
}

QString LinePointModel::svgPath() const {
    if (m_points.size() < 2) {
        return {};
    }
    QString path;
    for (int i = 0; i < m_points.size()-1; ++i) {
        const LinePoint &p = m_points[i];
        const LinePoint &next = m_points[i+1];
        if (i == 0) {
            path = QString("M %1 %2").arg(p.x).arg(p.y);
        }
        if (!p.hasCp1) {
            path += QString(" L %1 %2").arg(next.x).arg(next.y);
        } else {
            path += QString(" C %1 %2, %3 %4, %5 %6").arg(p.cp1x).arg(p.cp1y).arg(next.cp2x).arg(next.cp2y).arg(next.x).arg(next.y);
        }
    }
    return path;
}
