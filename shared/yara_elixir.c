#include <stdio.h>
#include <yara.h>
#include <erl_nif.h>

// Wraps the Yara initializer
extern int init_yara();

// Wraps the Yara finalizer
extern int destroy_yara();

// Call this function when you start using Yara.
static ERL_NIF_TERM init_yara_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    int ret;
    ret = yr_initialize();
#ifdef CHATTY
    fprintf(stdout, "yr_initialize: %d\n", ret);
#endif
    return enif_make_int(env, ret);
}

// Call this function when you are finished using Yara.
static ERL_NIF_TERM destroy_yara_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    int ret;
    ret = yr_finalize();
#ifdef CHATTY
    fprintf(stdout, "yr_finalize: %d\n", ret);
#endif
    return enif_make_int(env, ret);
}

// Creates a YARA compiler.
static ERL_NIF_TERM create_compiler(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    YR_COMPILER* compiler = NULL;
    if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
        perror("yr_compiler_create");
        exit(EXIT_FAILURE);
    }
    return enif_make_resource(env, compiler);
}

static ErlNifFunc nif_funcs[] = {
    {"init_yara", 0, init_yara_nif},
    {"destroy_yara", 0, destroy_yara_nif},
    {"create_compiler", 0, create_compiler}
};

// ERL_NIF_INIT args
//     yara_elixir - C identifier converted to a string
//     nif_funcs - name, arity, and function pointer of each NIF
ERL_NIF_INIT(Elixir.YaraElixir, nif_funcs, NULL, NULL, NULL, NULL)
