#include "wrapper/pixmap.hpp"
#include "wrapper/document.hpp"
#include <stdexcept>

namespace glean {
pixmap::pixmap(fz_context* ctx, fz_pixmap* pm) : _ctx(ctx), _pm(pm) {}
pixmap::~pixmap() {
    if (_pm) fz_drop_pixmap(_ctx, _pm);
}

pixmap::pixmap(pixmap&& other) noexcept : _ctx(other._ctx), _pm(other._pm) {
    other._pm = nullptr;
}

pixmap& pixmap::operator=(pixmap&& other) noexcept {
    if (this != &other) {
        if (_pm) fz_drop_pixmap(_ctx, _pm);
        _ctx      = other._ctx;
        _pm       = other._pm;
        other._pm = nullptr;
    }
    return *this;
}

pixmap render_page(document& doc, int page_number, float zoom, float rotate) {
    fz_context* ctx = doc.ctx();
    fz_pixmap*  pm  = nullptr;

    // Computes a transformation matrix for the desired zoom & rotation
    // Default resolution w.o. scaling = 72 dpi.
    fz_matrix ctm = fz_scale(zoom / 100, zoom / 100);
    ctm           = fz_pre_rotate(ctm, rotate);

    // Attempt to render the page to an RGB pixmap
    fz_try(ctx) pm = fz_new_pixmap_from_page_number(ctx, doc.get(), page_number,
                                                    ctm, fz_device_rgb(ctx), 0);
    fz_catch(ctx) { throw std::runtime_error(fz_caught_message(ctx)); }
    return pixmap {ctx, pm};
}
} // namespace glean
