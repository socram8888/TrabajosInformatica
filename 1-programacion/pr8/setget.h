
#ifndef HAVE_SETGET_H

#define SETTER(class, type, camel, var) void class::asigna##camel(type val) { \
    _##var = val; \
}

#define GETTER(class, type, camel, var) type class::devuelve##camel() { \
    return _##var; \
}

#define SETGET(class, type, camel, var) SETTER(class, type, camel, var); GETTER(class, type, camel, var);

#endif
