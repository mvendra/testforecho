
#ifndef __TESTFORECHO_COMPAT_H__
#define __TESTFORECHO_COMPAT_H__

#include <memory>

struct subject_code {
    subject_code() {};
    virtual ~subject_code(){};
    subject_code(const subject_code&) = delete;
    subject_code(subject_code&&) = delete;
    subject_code& operator=(const subject_code&) = delete;
    subject_code& operator=(subject_code&&) = delete;
    virtual void run() = 0;
};

#define T4E_MAKE(A, ...) class aux_class_##A : public subject_code { virtual void run() override { __VA_ARGS__ } };  std::unique_ptr<subject_code> A {std::make_unique<aux_class_##A>()};
#define T4E_GET(A) A.get()

// EXCEPTION TESTING

// Calls |testcase|
// Success: Exception of type |T| is thrown.
// Failures: Any other type of exception, or no exception is thrown.

template <typename T>
bool test_ex(const std::string &msg, subject_code *testcase){
    try {
        testcase->run();
        FAIL(msg);
    } catch (const T& ex){ 
        PASS(msg);
    } catch (...){
        FAIL(msg);
    }
}

// Calls |testcase|
// Success: A different type of exception than |T| is thrown, or no exception is thrown.
// Failures: Exception of type |T| is thrown.

template <typename T>
bool test_no_ex(const std::string &msg, subject_code *testcase){
    try {
        testcase->run();
        PASS(msg);
    } catch (const T& ex){
        FAIL(msg);
    } catch (...){
        PASS(msg);
    }
}

// Calls |testcase|
// Success: Any exception is thrown.
// Failures: No exception is thrown.

bool test_any_ex(const std::string &msg, subject_code *testcase){
    try {
        testcase->run();
        FAIL(msg);
    } catch (...){ 
        PASS(msg);
    }
}

// Calls |testcase|
// Success: No exception is thrown.
// Failures: Any exception is thrown.

bool test_any_no_ex(const std::string &msg, subject_code *testcase){
    try {
        testcase->run();
        PASS(msg);
    } catch (...){
        FAIL(msg);
    }
}

// HELPERS

template <typename X>
bool test_true(const std::string &msg, X param){

    // reporting
    std::string t1 = handy_conversion(param);
    std::string t2 = handy_conversion(true);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param == true){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X>
bool test_false(const std::string &msg, X param){

    // reporting
    std::string t1 = handy_conversion(param);
    std::string t2 = handy_conversion(false);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param == false){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
bool test_eq(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param1 == param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
bool test_ne(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param1 != param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
bool test_gt(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param1 > param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
bool test_ge(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param1 >= param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
bool test_lt(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param1 < param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
bool test_le(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (param1 <= param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

// INTERFACE EXTENSIONS

template <typename T>
void test_ex(bool &total, const std::string &msg, subject_code *testcase){
    total &= test_ex<T>(msg, testcase);
}

template <typename T>
void test_no_ex(bool &total, const std::string &msg, subject_code *testcase){
    total &= test_no_ex<T>(msg, testcase);
}

void test_any_ex(bool &total, const std::string &msg, subject_code *testcase){
    total &= test_any_ex(msg, testcase);
}

void test_any_no_ex(bool &total, const std::string &msg, subject_code *testcase){
    total &= test_any_no_ex(msg, testcase);
}

template <typename X>
void test_true(bool &total, const std::string &msg, X param){
    total &= test_true<X>(msg, param);
}

template <typename X>
void test_false(bool &total, const std::string &msg, X param){
    total &= test_false<X>(msg, param);
}

template <typename X, typename Y>
void test_eq(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_eq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ne(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_ne<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_gt(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_gt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ge(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_ge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_lt(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_lt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_le(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_le<X, Y>(msg, param1, param2);
}

#endif //__TESTFORECHO_COMPAT_H__