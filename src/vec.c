#include <mysort/vec.h>
#include <stdio.h>

void make_vec(struct vec *v) {
    v->length = 0;
    v->capacity = 0;
    v->data = NULL;
}


char *vec_get(struct vec *v, size_t idx) {
    if (!v || v->length <= idx) {
        if (!v) {
            fprintf(stderr, "AAAAaaA\n");
            return NULL;
        }
        fprintf(stderr, "AAAAA len %d idx %d\n", (int)v->length, (int)idx);
        return NULL;
    }
    fprintf(stderr, "VEC_GET: '%s'\n", v->data[idx]);
    return v->data[idx];
}

int vec_set(struct vec *v, size_t idx, char *str) {
    if (!v || v->length <= idx) {
        return VEC_ERR;
    }
    v->data[idx] = str;
    return VEC_OK;
}

int vec_append(struct vec *v, char *str) {
    if (!v) {
        return VEC_ERR;
    }
    if (v->capacity < v->length + 1) {
        size_t new_capacity = v->capacity > 0 ? v->capacity * 2 : 1;
        fprintf(stderr, "GOING TO REALLOC TO %d\n", (int)new_capacity);
        v->data = realloc(v->data, new_capacity * sizeof(char *));
        if (!v->data) {
            return VEC_BAD;
        }
        v->capacity = new_capacity;
    }
    fprintf(stderr, "SDJJSD '%s' %d\n", str, (int)v->length);
    v->data[v->length] = str;
    ++v->length;
    fprintf(stderr, "SDJ %d\n", (int)v->length);
    return VEC_OK;
}

int vec_pop(struct vec *v) {
    if (!v) {
        return VEC_ERR;
    }
    if (v->length <= 0 || !v->data) {
        return VEC_ERR;
    }
    --v->length;
    return VEC_OK;
}

int vec_shrink(struct vec *v) {
    if (!v) {
        return VEC_ERR;
    }
    if (!v->data && v->length > 0) {
        return VEC_ERR;
    }
    if (v->length == 0) {
        return VEC_OK;
    }

    v->data = realloc(v->data, v->length * sizeof(char *));
    if (!v->data) {
        return VEC_BAD;
    }
    v->capacity = v->length;
    return VEC_OK;
}
