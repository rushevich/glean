#pragma once

#include <mupdf/fitz.h>

namespace glean {
class context {
  private:
    fz_context* _ctx = nullptr;

  public:
    context();
    ~context();

    context(context const& other)            = delete;
    context& operator=(context const& other) = delete;
    context(context&& other);
    context& operator=(context&& other) = delete;

    fz_context* get() const { return _ctx; }
};
} // namespace glean
