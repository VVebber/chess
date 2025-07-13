#include "ChessInfoJson.h"

#include <QJsonDocument>
#include <QFile>
#include <QDebug>

ChessInfoJson& ChessInfoJson::instance() {
    static ChessInfoJson instance;
    return instance;
}

void ChessInfoJson::addOrUpdateKey(const QString& key, const QJsonValue& value) {
    m_data[key] = value;
}

void ChessInfoJson::mergeObject(const QJsonObject& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        m_data[it.key()] = it.value();
    }
}

QJsonObject ChessInfoJson::getData() const {
    return m_data;
}

void ChessInfoJson::setData(const QJsonObject& data) {
    m_data = data;
}

QJsonValue ChessInfoJson::getValue(const QString& key) const {
    return m_data.value(key);
}

bool ChessInfoJson::saveToFile(const QString& fileName) const {
    QString filePath = "/home/daniel/Документы/JSON/";
    QFile file(filePath + fileName + ".json");
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot open file for writing:" << filePath + fileName + ".json";
        return false;
    }
    QJsonDocument doc(m_data);
    file.write(doc.toJson(QJsonDocument::Indented));
    return true;
}

bool ChessInfoJson::loadFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file for reading:" << filePath;
        return false;
    }
    QByteArray data = file.readAll();
    QJsonParseError parseError;

    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return false;
    }

    m_data = doc.object();
    return true;
}

void ChessInfoJson::debugDump() const {
    // QJsonDocument doc(m_data);
    // qDebug().noquote() << doc.toJson(QJsonDocument::Indented);
  qDebug()<<m_data;
}
