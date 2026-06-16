#pragma once
#include <mupdf/fitz.h>

#include "wrapper/document.hpp"
#include "wrapper/pixmap.hpp"

namespace glean {

    class pdf {
      private:
        context _ctx;  // not owning
        document _doc;
        int _page_count{};

      public:
        pdf(const char* path);
        // See rule of zero
        // ~pdf();
        // pdf(pdf const& other) = delete;
        // pdf& operator=(pdf const& other) = delete;
        // pdf(pdf&& other);
        // pdf& operator=(pdf&& other);

        inline int page_count() noexcept { return _page_count; }
        inline fz_context* ctx() noexcept { return _ctx.get(); }

        pixmap render(int page_number, float zoom = 100, float rotate = 0);
    };
}  // namespace glean
