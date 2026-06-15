#pragma once

#include "wrapper/context.hpp"
#include <mupdf/fitz.h>

namespace glean {
class document {
  private:
    fz_context*  _ctx        = nullptr; // borrows context
    fz_document* _doc        = nullptr; // owns the document
    int          _page_count = 0;

  public:
    document(context& ctx, char const* filename);

    ~document();

    document(document const& other)            = delete;
    document& operator=(document const& other) = delete;
    document(document&& other);
    document& operator=(document&& other);

    inline fz_context*  ctx() const { return _ctx; }
    inline fz_document* get() const { return _doc; }
    inline int          page_count() const { return _page_count; };
};
} // namespace glean
