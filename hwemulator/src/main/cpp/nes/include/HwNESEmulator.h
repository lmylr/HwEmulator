/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HWEMULATOR_HWNESEMULATOR_H
#define HWEMULATOR_HWNESEMULATOR_H

#include <string>
#include <cstring>
#include <android/native_window.h>
#include "HwGamePadEvent.h"
#include "../../common/include/SimpleLock.h"

using namespace std;

class HwNESEmulator {
public:
    HwNESEmulator();

    virtual ~HwNESEmulator();

    int prepare(string rom, ANativeWindow *win, int width, int height);

    int start();

    int stop();

    int load();

    int save();

    int draw(uint8_t *rgba, size_t size);

    void postEvent(HwGamePadEvent *event);

private:
    void handleEvent(int event, int action);

private:
    string rom;
    ANativeWindow *win = nullptr;
    int width = 0;
    int height = 0;
    SimpleLock simpleLock;

    unsigned long dwKeyPad1 = 0;
    unsigned long dwKeyPad2 = 0;
    unsigned long dwKeySystem = 0;
};


#endif //HWEMULATOR_HWNESEMULATOR_H
