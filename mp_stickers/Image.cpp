#include <iostream>
#include "Image.h"
#include <cmath>

using namespace std;
namespace cs225 {
    void Image::lighten() {
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.l += .1;
                if (pixel.l > 1 ) pixel.l = 1;
            }
        }
    }
    void Image::lighten(double amount) {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.l += amount;
                if (pixel.l < 0) pixel.l = 0;
                if (pixel.l > 1) pixel.l = 1;
            }
        }
    }
    void Image::darken() {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.l -=.1;
                if (pixel.l < 0) pixel.l = 0;
            }
        }
    }
    void Image::darken(double amount) {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.l -= amount;
                if (pixel.l < 0) pixel.l = 0;
                if (pixel.l > 1) pixel.l = 1;
            }
        }
    }
    void Image::saturate() {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.s += .1;
                if (pixel.s > 1) pixel.s = 1;
            }
        }
    }
    void Image::saturate(double amount) {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.s += amount;
                if (pixel.s < 0) pixel.s = 0;
                if (pixel.s > 1) pixel.s = 1;
            }
        }
    }
    void Image::desaturate() {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.s -= .1;
                if (pixel.s < 0) pixel.s = 0;
            }
        }
    }
    void Image::desaturate(double amount) {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.s += amount;
                if (pixel.s < 0) pixel.s = 0;
                if (pixel.s > 1) pixel.s = 1;
            }
        }
    }
    void Image::grayscale() {
        for (unsigned x  = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &pixel = this->getPixel(x , y);
                pixel.s = 0;
            }
        }
    }
    void Image::rotateColor(double degrees) {
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &currentPixel = getPixel(x, y);
                currentPixel.h += degrees;
                currentPixel.h = remainder(currentPixel.h, 360);
                if (currentPixel.h < 0) currentPixel.h += 360;
            }
        }

    }
    void Image::illinify() {
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel & pixel = getPixel(x, y);
                if ((pixel.h >= 0 && pixel.h < 113.5) || (pixel.h > 293.5 && pixel.h <= 360)) pixel.h = 11;
                 else pixel.h = 216;
            }
        }
    }
    void Image::scale(double factor) {
        PNG* original = new PNG(*this);
        this->resize(width() * factor, height() * factor);
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel &oldPixel = original->getPixel(x / factor, y / factor);
                HSLAPixel &newPixel = this->getPixel(x , y);
                newPixel = oldPixel; 
            }
        }
        delete original;
    }
    void Image::scale(unsigned w, unsigned h) {
        double widthFactor = ((double) w) / ((double) width());
        double heightFactor = ((double) h) / ((double) height());
        if (widthFactor < heightFactor) scale(widthFactor);
        else scale(heightFactor);
    } 
}