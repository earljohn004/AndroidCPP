#ifndef ANDROIDCPP_NATIVE_LIB_H
#define ANDROIDCPP_NATIVE_LIB_H

const static char *const CLASSNAME {"com/tutorial/androidcpp/MainActivity"};

enum class action_alias{
    on_function_first,
    on_function_second,
    on_function_third,
    on_function_fourth,
    on_function_fith,
    on_get_instance,
};

struct function_map{
    action_alias action;
    std::string function_name;
    std::string function_signature;
};
extern function_map functions_[];
extern const unsigned int functions_size_;


std::tuple<std::string, std::string> get_function_information( action_alias action);

template<typename... T>
void execute_function(JNIEnv *env, action_alias action,  T... params);

template<typename Index, typename... T>
void releaseAll(JNIEnv *env, Index I, T... references);

static jobject manager_object_;

#endif //ANDROIDCPP_NATIVE_LIB_H
