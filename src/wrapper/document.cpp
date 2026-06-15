#include "document.hpp"
#include <stdexcept>

namespace glean {
document::document(context& ctx, char const* filename) {
    _ctx              = ctx.get();
    fz_try(_ctx) _doc = fz_open_document(_ctx, filename);
    fz_catch(_ctx) { throw std::runtime_error(fz_caught_message(_ctx)); }
    fz_try(_ctx) _page_count = fz_count_pages(_ctx, _doc);
    fz_catch(_ctx) { throw std::runtime_error(fz_caught_message(_ctx)); }
}

document::~document() {
    if (_doc) fz_drop_document(_ctx, _doc);
}

document::document(document&& other) : _ctx(other._ctx), _doc(other._doc) {
    other._doc = nullptr;
}

document& document::operator=(document&& other) {
    if (this != &other) {
        _ctx       = other._ctx;
        _doc       = other._doc;
        other._doc = nullptr;
    }
    return *this;
}
} // namespace glean
