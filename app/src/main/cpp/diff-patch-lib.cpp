#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "zza-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型
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
