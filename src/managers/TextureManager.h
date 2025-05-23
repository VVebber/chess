#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QPixmap>
#include <QString>
#include <QList>

class TextureManager
{
private:
  struct Texture
  {
    QPixmap m_textur;
    QString m_path;
    QString m_name;
    Texture(const QString& path, const QString& name)
    {
      m_name = name;
      m_path = path;
    }

    bool load()
    {
      if (!m_textur.load(m_path))
      {
        qWarning("Failed to load texture: %s", qPrintable(m_path));
        return false;
      }
      return true;
    }
  };

public:
  static TextureManager& instance()
  {
    static TextureManager instance;
    return instance;
  }

  void setupTexturs();

  const QPixmap& getTexture(const QString& name)
  {
    for(int i = 0; i < m_textures.size();i++)
      if(m_textures[i].m_name== name)
        return m_textures[i].m_textur;

    static QPixmap dummy;
    return dummy;
  }

  const QPixmap& getTexture(const QString& path, const QString& name)
  {
    for(int i = 0; i < m_textures.size();i++)
      if(m_textures[i].m_path== path)
        return m_textures[i].m_textur;

    Texture textur(path, name);
    if (!textur.load()) {
      static QPixmap dummy;
      return dummy;
    }

    m_textures.push_back(std::move(textur));
    return m_textures.last().m_textur;
  }

private:
  TextureManager();
  TextureManager(const TextureManager&) = delete;
  TextureManager& operator=(const TextureManager&) = delete;

  QList<Texture> m_textures;
};

#endif // TEXTURMANAGERS_H
