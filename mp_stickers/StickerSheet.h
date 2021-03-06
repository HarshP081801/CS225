/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
namespace cs225 {
class StickerSheet{
  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index) const;
    Image render() const;

  private:
    Image* *stickers;
    Image background;
    void copy(StickerSheet const & other);
    void clear();
    unsigned int sticker_max;
    unsigned int index;
    unsigned int *xCoor_;
    unsigned int *yCoor_;
};
}