#include <jni.h>
#include <string>

extern "C"
{
#include "bsdiff.h"
#include "bspatch.h"
}

extern "C"
JNIEXPORT jint

JNICALL
Java_dev_hikari_diffpatch_DiffPatchUtils_diff(JNIEnv *env, jclass type, jstring oldPath_,
                                              jstring newPath_, jstring patchPath_) {

    const char *oldPath = env->GetStringUTFChars(oldPath_, 0);
    const char *newPath = env->GetStringUTFChars(newPath_, 0);
    const char *patchPath = env->GetStringUTFChars(patchPath_, 0);

    int argc = 4;
    char *argv[argc];
    argv[0] = (char *) "bsdiff";
    argv[1] = (char *) oldPath;
    argv[2] = (char *) newPath;
    argv[3] = (char *) patchPath;

    int ret = bsdiff_main(argc, argv);

    env->ReleaseStringUTFChars(oldPath_, oldPath);
    env->ReleaseStringUTFChars(newPath_, newPath);
    env->ReleaseStringUTFChars(patchPath_, patchPath);

    return ret;
}

extern "C"
JNIEXPORT jint

JNICALL
Java_dev_hikari_diffpatch_DiffPatchUtils_patch(JNIEnv *env, jclass type, jstring oldPath_,
                                               jstring newPath_, jstring patchPath_) {
    const char *oldPath = env->GetStringUTFChars(oldPath_, 0);
    const char *newPath = env->GetStringUTFChars(newPath_, 0);
    const char *patchPath = env->GetStringUTFChars(patchPath_, 0);

    int argc = 4;
    char *argv[argc];
    argv[0] = (char *) "bspatch";
    argv[1] = (char *) oldPath;
    argv[2] = (char *) newPath;
    argv[3] = (char *) patchPath;


    int ret = bspatch_main(argc, argv);

    env->ReleaseStringUTFChars(oldPath_, oldPath);
    env->ReleaseStringUTFChars(newPath_, newPath);
    env->ReleaseStringUTFChars(patchPath_, patchPath);

    return ret;

}
