#include "TextureManager.h"
#include "../Common.h"

TextureManager::TextureManager()
{
  setupTexturs();
}

void TextureManager::setupTexturs()
{
  getTexture(LINK_IMG_PAWN, PAWN);
  getTexture(LINK_IMG_KNIGHT, KNIGHT);
  getTexture(LINK_IMG_BISHOP, BISHOP);
  getTexture(LINK_IMG_KING, KING);
  getTexture(LINK_IMG_QUEEN, QUEEN);
  getTexture(LINK_IMG_ROOK, ROOK);

  getTexture(LINK_IMG_ARROW_START, ARROW_START);
}

// getTexture(LINK_IMG)
