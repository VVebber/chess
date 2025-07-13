#ifndef CHESSINFOJSON_H
#define CHESSINFOJSON_H

#include <QJsonObject>

class ChessInfoJson {
public:
    static ChessInfoJson& instance();

    void addOrUpdateKey(const QString& key, const QJsonValue& value);
    void mergeObject(const QJsonObject& other);
    QJsonObject getData() const;
    QJsonValue getValue(const QString& key) const;

    void setData(const QJsonObject& data);
    bool saveToFile(const QString& fileName) const;
    bool loadFromFile(const QString& filePath);

    void debugDump() const;

private:
    ChessInfoJson() = default;

private:
    QJsonObject m_data;
};

#endif // CHESSINFOJSON_H
