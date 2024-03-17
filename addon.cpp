#include <node_api.h>
#include <iostream>
#include <string>

napi_value Method(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value argv[4];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    if (argc < 4) {
        napi_throw_error(env, nullptr, "You must provide four arguments");
        return nullptr;
    }

    // Extracting float
    double a;
    napi_get_value_double(env, argv[0], &a);
    std::cout << "Float value: " << a << std::endl;

    // Extracting double
    double b;
    napi_get_value_double(env, argv[1], &b);
    std::cout << "Double value: " << b << std::endl;

    // Extracting int
    int c;
    napi_get_value_int32(env, argv[2], &c);
    std::cout << "Int value: " << c << std::endl;

    // Extracting string
    size_t str_length;
    napi_get_value_string_utf8(env, argv[3], nullptr, 0, &str_length);
    char* str = new char[str_length + 1];
    napi_get_value_string_utf8(env, argv[3], str, str_length + 1, nullptr);
    std::string d(str);
    delete[] str;
    std::cout << "String value: " << d << std::endl;

    return nullptr;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, nullptr, 0, Method, nullptr, &fn);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to create function");
        return nullptr;
    }

    status = napi_set_named_property(env, exports, "method", fn);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to set method");
        return nullptr;
    }

    return exports;
}

NAPI_MODULE(addon, Init)
