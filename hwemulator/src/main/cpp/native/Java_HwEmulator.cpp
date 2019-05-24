/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/

#include <jni.h>
#include <android/native_window_jni.h>
#include "HwNESEmulator.h"
#include "HwGamePadEvent.h"

#ifdef __cplusplus
extern "C" {
#endif

static HwNESEmulator *getHandler(jlong handler) {
    return reinterpret_cast<HwNESEmulator *>(handler);
}

JNIEXPORT jlong JNICALL Java_com_lmy_emulator_HwEmulator_create
        (JNIEnv *env, jobject thiz) {
    return reinterpret_cast<jlong>(new HwNESEmulator());
}

JNIEXPORT jint JNICALL Java_com_lmy_emulator_HwEmulator_prepare
        (JNIEnv *env, jobject thiz, jlong handler, jstring rom) {
    int ret = -1;
    if (handler) {
        const char *pRom = env->GetStringUTFChars(rom, nullptr);
        ret = getHandler(handler)->prepare(string(pRom));
        env->ReleaseStringUTFChars(rom, pRom);
    }
    return ret;
}

JNIEXPORT jint JNICALL Java_com_lmy_emulator_HwEmulator_attachWindow
        (JNIEnv *env, jobject thiz, jlong handler, jobject surface) {
    if (handler) {
        ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
        if (win) {
            int width = ANativeWindow_getWidth(win);
            int height = ANativeWindow_getHeight(win);
            return getHandler(handler)->attachWindow(win, width, height);
        }
    }
    return -1;
}

JNIEXPORT jint JNICALL Java_com_lmy_emulator_HwEmulator_start
        (JNIEnv *env, jobject thiz, jlong handler) {
    if (handler) {
        return getHandler(handler)->start();
    }
    return -1;
}

JNIEXPORT jint JNICALL Java_com_lmy_emulator_HwEmulator_stop
        (JNIEnv *env, jobject thiz, jlong handler) {
    if (handler) {
        HwNESEmulator *emulator = getHandler(handler);
        emulator->stop();
        delete emulator;
    }
    return -1;
}

JNIEXPORT void JNICALL Java_com_lmy_emulator_HwEmulator_postEvent
        (JNIEnv *env, jobject thiz, jlong handler, jint event, jint action) {
    if (handler) {
        HwGamePadEvent *e = HwGamePadEvent::create(event, action);
        getHandler(handler)->postEvent(e);
        delete e;
    }
}

#ifdef __cplusplus
}
#endif