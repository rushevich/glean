#pragma once

#include "wrapper/document.hpp"
#include <mupdf/fitz.h>

namespace glean {
// Responsible effectively just for the pixmap
class pixmap {
  private:
    fz_context* _ctx = nullptr;
    fz_pixmap*  _pm  = nullptr;

  public:
    pixmap() = default;
    pixmap(fz_context* ctx, fz_pixmap* pm);
    ~pixmap();

    pixmap(pixmap const& other)            = delete;
    pixmap& operator=(pixmap const& other) = delete;
    pixmap(pixmap&& other) noexcept;
    pixmap& operator=(pixmap&& other) noexcept;

    inline fz_pixmap* get() const { return _pm; }
    inline bool       valid() const { return _pm != nullptr; }
    inline int        width() const { return _pm->w; }
    inline int        height() const { return _pm->h; }
    inline int stride() const { return _pm->stride; } // # of bytes per row
    inline unsigned char* samples() const { return _pm->samples; }
};

pixmap render_page(document& doc, int page_number, float zoom = 100,
                   float rotate = 0);
} // namespace glean
