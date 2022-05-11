#include <iostream>
#include "StickerSheet.h"

using namespace std;
namespace cs225 {

    // copy function 
    void StickerSheet::copy(StickerSheet const & other){
        // set all non pointers equal to other. values
        sticker_max = other.sticker_max;
        index = other.index;
        background = other.background;
        //create a new Image pointer array and fill each slot with a new Image pointer
        stickers = new Image*[sticker_max];
        for (unsigned int i = 0; i < sticker_max; i++) {
            stickers[i] = new Image();
        }
        //create new arrays for storing and x and y coords
        xCoor_ = new unsigned int[sticker_max];
        yCoor_ = new unsigned int[sticker_max];
        // check to see if the other.value is null, if so set this.value to null, else set this.value to other.value
        for (unsigned int i = 0; i < sticker_max; i++) {
            if (other.stickers[i] == NULL) {
                stickers[i] = NULL;
            } else {
                *(stickers[i]) = *(other.stickers[i]);
            }
            //set all values in this x and y coords to other x and y coords
            xCoor_[i] = other.xCoor_[i];
            yCoor_[i] = other.yCoor_[i];
        }
    }

    //clear function
    void StickerSheet::clear() {
        //delete each individual Image pointer in Image pointer array
        for (unsigned int i = 0; i  < sticker_max; i++) {
            delete stickers[i];
        }
        // delete the Image pointer array itself and the arrays that store x and y coords.
        delete[] stickers;
        delete[] xCoor_;
        delete[] yCoor_;
    }

    // main constructor
    StickerSheet::StickerSheet(const Image & picture, unsigned max) {
        //set each non point value to a given value or default if not given
        background = picture;
        sticker_max = max;
        index = 0;
        //create a new Image pointer array of size max and loop through to set each value inside to be a new image pointer
        stickers = new Image*[max];
        for (unsigned int i = 0; i < max; i++) {
            stickers[i] = new Image();
        }
        //create new x and y coord holder arrays of size max.
        xCoor_ = new unsigned int[max];
        yCoor_ = new unsigned int[max];
    }

    //destructor, only needs to clear any residual pointers that can cause memory leaks
    StickerSheet::~StickerSheet() {
        clear();
    }

    // copy constructor, only need to use copy function.
    StickerSheet::StickerSheet(const StickerSheet & other) {
        copy(other);
    }

    //operator= function. overriding the = operator to ensure the two are in fact the same and if not, clear and copy the other.
    const StickerSheet& StickerSheet::operator=(const StickerSheet & other){
        if (this != &other) {
            clear();
            copy(other);
        }
        return *this;
    }

    //changeMaxStickers function.
    void StickerSheet::changeMaxStickers(unsigned max){
        //create temporary variable for Image pointer array to store values.
        //iterate through it and set each value to be an image pointer
        Image** tempStickers = new Image*[sticker_max];
        for (unsigned int i = 0; i < sticker_max; i++) {
            tempStickers[i] = new Image();
        }
        //create temporary variables for x and y coords.
        unsigned int* tempX = new unsigned int[sticker_max];
        unsigned int* tempY = new unsigned int[sticker_max];
        //loop through temporary image pointer array and check to see if original array had NULLs, if so set value inside
        //temp array to NULL after deleteing the pointer. else set the temporary = original by dereferencing.
        for (unsigned int i = 0; i  < sticker_max; i++) {
            if (stickers[i] == NULL) {
                delete tempStickers[i];
                tempStickers[i] = NULL;
            } else {
                *(tempStickers[i]) = *(stickers[i]);
            }
            //set temporary x and y coords to original x and y coords
            tempX[i] = xCoor_[i];
            tempY[i] = yCoor_[i];
        }
        //create temporary index to keep track of what index each value is in the array.
        int tempIndex = index;
        //clear and reset the size of original arrays to new size wanted and loop through to fill like before.
        clear();
        stickers = new Image*[max];
        for (unsigned int i = 0; i < max; i++) {
            stickers[i] = new Image();
        }
        xCoor_ = new unsigned int[max];
        yCoor_ = new unsigned int[max];
        //resolve whether max is greater than sticker_max. If so, loop through till sticker_max and check
        //for NULLs within temporary arr. If exists, the new original arr deletes the pointer and replaces with NULL
        if (max > sticker_max) {
            for (unsigned int i = 0; i < sticker_max; i++) {
                if (tempStickers[i] == NULL) {
                    delete stickers[i];
                    stickers[i] = NULL;
                // else dereference the pointers and set the new original arr to match temp arr.    
                } else {
                    *(stickers[i]) = *(tempStickers[i]);
                }
                // match the new original x and y coords to tempX and tempY coords.
                xCoor_[i] = tempX[i];
                yCoor_[i] = tempY[i];
            }
            //set the index to match the temporary index to keep track of where the index is in the new original arr.
            index = tempIndex;
        //resolving if max < sticker_max. The original arr will lose values.
        // check for NULLS -> if so, delete the pointer and replace will null, else dereference and set new original arr to match temp arr.
        } else {
            for (unsigned int i = 0; i < max; i++) {
                if (tempStickers[i] == NULL) {
                    delete stickers[i];
                    stickers[i] = NULL;
                } else {
                    *(stickers[i]) = *(tempStickers[i]);
                }
                //match the new original x and y coords to tempX and tempY coords.
                xCoor_[i] = tempX[i];
                yCoor_[i] = tempY[i];
            }
            //make sure Index is no longer out of bounds and if it is, reset it to be of size max (end of arr)
            if (index >= max) {
                index = max;
            }
        }
        //delete all temporary pointers created.
        for (unsigned int i = 0; i < sticker_max; i++) {
            delete tempStickers[i];
        }
        delete[] tempStickers;
        delete[] tempX;
        delete[] tempY;
        //set the old max to the new max
        sticker_max = max;
    }

    //addSticker function
    int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
        //look for the first available layer to place sticker in
        //once a NULL is found, create a new pointer to that location and place sticker
        //add the new x and y coords from given to the x and y coord arrs and return the location
        for (unsigned int i = 0; i < index; i++) {
            if (stickers[i] == NULL) {
                stickers[i] = new Image();
                *(stickers[i]) = sticker;
                xCoor_[i] = x;
                yCoor_[i] = y;
                return i;
            }
        }
        //if we reach index and no NULL is found. add a new layer as long as within max amount of stickers
        if (index < sticker_max) {
            if (stickers[index] == NULL) {
                stickers[index] = new Image();
            }
            *(stickers[index]) = sticker;
            //add location of x and y coord to respective arrs.
            xCoor_[index] = x;
            yCoor_[index] = y;
            //create a temporary int to hold the current index.
            int temp = index;
            //increment index to account for added sticker
            index++;
            //return the index before the increment
            return temp;
        }
        //if not valid, return -1
        return -1;
    }

    //translate function.
    bool StickerSheet::translate(unsigned index_, unsigned x, unsigned y){
        //if target sticker at the requested index is null, return false
        if (stickers[index] == NULL) {
            return false;
        }
        //if within the bounds, set the new x and y coords within respective arrs and return true
        if (index_ >= 0 && index_ < index) {
            xCoor_[index_] = x;
            yCoor_[index_] = y;
            return true;
        }
        //if not within bounds, return false
        return false;
    }

    //removeSticker function
    void StickerSheet::removeSticker(unsigned index_){
        //make sure index is within bounds, if so delete the sticker at that location and set to NULL
        //if at the end of the arr, decrement index by 1 to ensure not out of bounds
        if (index_ < sticker_max && index_ >= 0) {
            delete stickers[index_];
            stickers[index_] = NULL;
            if (index_ == index - 1) {
                index--;
            }
        }
    }
    
    //getSticker function
    Image * StickerSheet::getSticker(unsigned index_) const{
        //loop to find the sticker at given index. if found and not null return the sticker.
        // if not found, return null
        for (unsigned int i = 0; i < index; i++) {
            if (i == index_ && (stickers[i] != NULL)) {
                return stickers[i];
            }
        }
        return NULL;
    }

    //render function
    Image StickerSheet::render() const{
        //create the first layer
        Image rendr(background);
        //check to see if the current sticker is null, if so continue onto the next value of i
        for (unsigned int i = 0; i < index; i++) {
            if (stickers[i] == NULL) {
                continue;
            }
            // if not null, check to see if sticker is within image boundaries
            // if not within image boundaries, resize to fit the sticker
            if (stickers[i]->width() + xCoor_[i] > rendr.width()) {
                rendr.resize(stickers[i]->width() + xCoor_[i], rendr.height());
            }
            if (stickers[i]->height() + yCoor_[i] > rendr.height()) {
                rendr.resize(rendr.width(), stickers[i]->height() + yCoor_[i]);
            }
            // after getting the boundaries, loop through each sticker and place them onto the image.
            for (unsigned int x = 0; x < stickers[i]->width(); x++) {
                for (unsigned int y = 0; y < stickers[i]->height(); y++) {
                    HSLAPixel &stkrPixel = stickers[i]->getPixel(x, y);
                    HSLAPixel &canvasPixel = rendr.getPixel(x + xCoor_[i], y + yCoor_[i]);
                    //check to see if the alpha of the sticker pixel > 0 to ensure it is supposed to be visible
                    // if it is > 0, set the h s l a of the canvas pixel to the sticker pixel
                    if (stkrPixel.a > 0) {
                        canvasPixel.h = stkrPixel.h;
                        canvasPixel.s = stkrPixel.s;
                        canvasPixel.l = stkrPixel.l;
                        canvasPixel.a = stkrPixel.a;
                    }
                }
            }
        }
        return rendr;
    }
}