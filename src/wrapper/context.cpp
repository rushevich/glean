#include "context.hpp"
#include <stdexcept>

namespace glean {
context::context() {
    _ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    if (!_ctx) { throw std::runtime_error("Failed to create context"); }
    fz_try(_ctx) fz_register_document_handlers(_ctx);
    fz_catch(_ctx) {
        throw std::runtime_error(fz_caught_message(_ctx));
        fz_drop_context(_ctx);
    }
}

context::~context() {
    if (_ctx) fz_drop_context(_ctx);
}

context::context(context&& other) : _ctx(other._ctx) { other._ctx = nullptr; }
} // namespace glean
