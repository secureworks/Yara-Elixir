#include "yara_elixir.h"
#include <sys/errno.h>
#include <yara/compiler.h>

static ErlNifResourceType *YARA_COMPILER;

ERL_NIF_TERM atomize(ErlNifEnv *env, const char *name) {
    debug_func_start;
    ERL_NIF_TERM atom;
    if (enif_make_existing_atom(env, name, &atom, ERL_NIF_LATIN1)) {
        return atom;
    }
    return enif_make_atom(env, name);
}

ErlNifResourceType * open_resource_type(ErlNifEnv *env, const char *name) {
    debug_func_start;
    ErlNifResourceFlags flags = ERL_NIF_RT_CREATE;
    ErlNifResourceType *ret;
    ret = enif_open_resource_type(env, NULL, name, NULL, flags, NULL);
    return ret;
}

static int nif_load(ErlNifEnv * env, void **priv_data, ERL_NIF_TERM load_info) {
    debug_func_start;
    const char *name = "Yara-Elixir";
    YARA_COMPILER = open_resource_type(env, name);
    return 0;
}

// Call this function when you start using Yara.
static ERL_NIF_TERM init_yara_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    debug_func_start;
    int ret;
    ret = yr_initialize();
    debug("yr_initialize: %d\n", ret);
    return enif_make_int(env, ret);
}

// Call this function when you are finished using Yara.
static ERL_NIF_TERM destroy_yara_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    debug_func_start;
    int ret;
    ret = yr_finalize();
    debug("yr_finalize: %d\n", ret);
    return enif_make_int(env, ret);
}

// Creates a YARA compiler.
static ERL_NIF_TERM create_compiler(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    debug_func_start;
    YR_COMPILER **compiler = enif_alloc_resource(YARA_COMPILER, sizeof(YR_COMPILER *));
    if (yr_compiler_create(compiler) != ERROR_SUCCESS) {
        perror("yr_compiler_create");
        exit(EXIT_FAILURE);
    }
    ERL_NIF_TERM term = enif_make_resource(env, compiler);
    return term;
}

// Destroys a YARA compiler.
static ERL_NIF_TERM destroy_compiler(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    debug_func_start;
    if (argc != 1) {
        return enif_make_badarg(env);
    }
    if (!enif_is_ref(env, argv[0])) {
        ERL_NIF_TERM err = atomize(env, "error");
        ERL_NIF_TERM not_a_ref = atomize(env, "not_a_reference");
        return enif_make_tuple2(env, err, not_a_ref);
    }
    YR_COMPILER **compiler_res = NULL;
    enif_get_resource(env, argv[0], YARA_COMPILER, (void *) &compiler_res);
    YR_COMPILER *compiler = *compiler_res;
    yr_compiler_destroy(compiler);
    return atomize(env, "ok");
}

// Compile rules from a string putting them into the default namespace.
static ERL_NIF_TERM compile_string(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
//int yr_compiler_add_string(YR_COMPILER* compiler, const char* string, const char* namespace_)
    debug_func_start;
    if (argc != 2) {
        return enif_make_badarg(env);
    }
    if (!enif_is_ref(env, argv[0])) {
        ERL_NIF_TERM err = atomize(env, "error");
        ERL_NIF_TERM not_a_ref = atomize(env, "not_a_reference");
        return enif_make_tuple2(env, err, not_a_ref);
    }
    if (!enif_is_binary(env, argv[1])) {
        ERL_NIF_TERM err = atomize(env, "error");
        ERL_NIF_TERM not_a_binary = atomize(env, "not_a_binary");
        return enif_make_tuple2(env, err, not_a_binary);
    }
    ErlNifBinary string_binary;
    if (!enif_inspect_binary(env, argv[1], &string_binary)) {
        return enif_make_badarg(env);
    }
    char *string = strndup((char *) string_binary.data, string_binary.size);
    if (string == NULL) {
        perror("strndup");
        exit(EXIT_FAILURE);
    }
    YR_COMPILER **compiler_res = NULL;
    enif_get_resource(env, argv[0], YARA_COMPILER, (void *) &compiler_res);
    YR_COMPILER *compiler = *compiler_res;
    int ret = yr_compiler_add_string(compiler, string, NULL);
    free(string);
    return enif_make_int(env, ret);
}

// Compile rules from a string putting them into the specified namespace.
static ERL_NIF_TERM compile_string_ns(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
//int yr_compiler_add_string(YR_COMPILER* compiler, const char* string, const char* namespace_)
    return atomize(env, "ok");
}

static ErlNifFunc nif_funcs[] = {
    {"init_yara", 0, init_yara_nif},
    {"destroy_yara", 0, destroy_yara_nif},
    {"create_compiler", 0, create_compiler},
    {"destroy_compiler", 1, destroy_compiler},
    {"compile_string", 2, compile_string},
    {"compile_string_ns", 3, compile_string_ns}
};

// ERL_NIF_INIT args
//     yara_elixir - C identifier converted to a string
//     nif_funcs - name, arity, and function pointer of each NIF
ERL_NIF_INIT(Elixir.YaraElixir, nif_funcs, nif_load, NULL, NULL, NULL)
