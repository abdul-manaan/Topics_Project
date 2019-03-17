#include <jni.h>

JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(JNIEnv *env , jobject instance ,
                                                          jint mem , jint oom , jstring fname_ ,
                                                          jint session) {
    const char *fname = (*env)->GetStringUTFChars(env , fname_ , 0);

    // TODO

    (*env)->ReleaseStringUTFChars(env , fname_ , fname);

    return (*env)->NewStringUTF(env , returnValue);
}