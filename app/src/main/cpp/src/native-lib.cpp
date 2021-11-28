#include <jni.h>
#include <string>
#include "native-lib.h"

using namespace std;

/*
 * Static Initialization of Callback functions from low level library to Kotlin
 */
function_map functions_[] = {
        {action_alias::on_function_first, "onFunctionFirst","(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" },
        {action_alias::on_function_second, "onFunctionSecond","(Ljava/lang/String;)V" },
        {action_alias::on_function_third, "onFunctionThird", "(Ljava/lang/String;)V" },
        {action_alias::on_function_fourth, "onFunctionFourth", "(ILjava/lang/String;)V"},
        {action_alias::on_function_fith, "onFunctionFifth", "()V"},
        {action_alias::on_get_instance, "getInstance", "()Lcom/tutorial/androidcpp/MainActivity;"},
};
const unsigned int functions_size_ = sizeof(functions_) / sizeof(function_map);

jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved){

    JNIEnv *env;
    if(vm->GetEnv((void**) &env, JNI_VERSION_1_6 ) != JNI_OK){
        return JNI_ERR;
    }
    auto clz = env->FindClass(CLASSNAME);

    auto [static_name, static_sig] = get_function_information(action_alias::on_get_instance);
    jmethodID method = env->GetStaticMethodID(clz, static_name.c_str(), static_sig.c_str());
    jobject handler = env->CallStaticObjectMethod(clz, method);
    manager_object_ = env->NewGlobalRef(handler);

    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_tutorial_androidcpp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

template<typename... T>
void execute_function(JNIEnv *env, action_alias action,  T... params){

    //Get the function name and signature
    auto [ func_name, func_signature ] = get_function_information(action);

    jclass clz = env->FindClass(CLASSNAME);
    if( env->ExceptionOccurred()){
        return;
    }

    jmethodID method = env->GetMethodID(clz, func_name.c_str(), func_signature.c_str());
    env->CallVoidMethod(manager_object_, method, params... );
    releaseAll(env, &clz);
}

/*
 * Helper function template function to release all refenences
 */
template<typename Index, typename... T>
void releaseAll(JNIEnv *env, Index I, T... references) {

    releaseRef(env, *I);
    if constexpr (!sizeof...(T)) {
        return;
    } else {
        releaseAll(env, references...);
    }
}

/*
 * Helper function get function name and signature defined
 */
std::tuple<std::string, std::string> get_function_information( action_alias action){
    for( const auto& func: functions_){
        if( func.action == action )
            return std::make_tuple( func.function_name, func.function_signature );
    }
    return std::make_tuple("no_implementation", "()V"); //Handle default implementation if not found
}
